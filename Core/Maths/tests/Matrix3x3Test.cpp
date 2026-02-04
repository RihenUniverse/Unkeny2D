#include <Maths/Matrix3x3.h>
#include <Maths/MathConstants.h>
#include <Maths/Vector2.h>
#include <Unitest/Unitest.h>

TEST_CASE(Math, Matrix3x3_DefaultConstructor) {
    nkentseu::math::Matrix3x3 m;
    
    // Matrice par défaut devrait être l'identité
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (i == j) {
                ASSERT_EQUAL(1.0f, m.m[i][j]);
            } else {
                ASSERT_EQUAL(0.0f, m.m[i][j]);
            }
        }
    }
}

TEST_CASE(Math, Matrix3x3_Identity) {
    nkentseu::math::Matrix3x3 identity = nkentseu::math::Matrix3x3::Identity();
    
    ASSERT_EQUAL(1.0f, identity.m[0][0]);
    ASSERT_EQUAL(0.0f, identity.m[0][1]);
    ASSERT_EQUAL(0.0f, identity.m[0][2]);
    
    ASSERT_EQUAL(0.0f, identity.m[1][0]);
    ASSERT_EQUAL(1.0f, identity.m[1][1]);
    ASSERT_EQUAL(0.0f, identity.m[1][2]);
    
    ASSERT_EQUAL(0.0f, identity.m[2][0]);
    ASSERT_EQUAL(0.0f, identity.m[2][1]);
    ASSERT_EQUAL(1.0f, identity.m[2][2]);
}

TEST_CASE(Math, Matrix3x3_Translation) {
    nkentseu::math::Matrix3x3 translation = nkentseu::math::Matrix3x3::Translation(5.0f, 10.0f);
    
    // Matrice de translation
    // [1 0 tx]
    // [0 1 ty]
    // [0 0 1]
    ASSERT_EQUAL(1.0f, translation.m[0][0]);
    ASSERT_EQUAL(0.0f, translation.m[0][1]);
    ASSERT_EQUAL(5.0f, translation.m[0][2]);
    
    ASSERT_EQUAL(0.0f, translation.m[1][0]);
    ASSERT_EQUAL(1.0f, translation.m[1][1]);
    ASSERT_EQUAL(10.0f, translation.m[1][2]);
    
    ASSERT_EQUAL(0.0f, translation.m[2][0]);
    ASSERT_EQUAL(0.0f, translation.m[2][1]);
    ASSERT_EQUAL(1.0f, translation.m[2][2]);
}

TEST_CASE(Math, Matrix3x3_Rotation) {
    // Rotation de 90 degrés (π/2 radians)
    nkentseu::math::Matrix3x3 rotation = nkentseu::math::Matrix3x3::Rotation(nkentseu::math::HALF_PI);
    
    // Matrice de rotation 2D
    // [cosθ -sinθ 0]
    // [sinθ  cosθ 0]
    // [0    0    1]
    ASSERT_NEAR(0.0f, rotation.m[0][0], 0.0001f);  // cos(π/2) ≈ 0
    ASSERT_NEAR(-1.0f, rotation.m[0][1], 0.0001f); // -sin(π/2) = -1
    ASSERT_EQUAL(0.0f, rotation.m[0][2]);
    
    ASSERT_NEAR(1.0f, rotation.m[1][0], 0.0001f);  // sin(π/2) = 1
    ASSERT_NEAR(0.0f, rotation.m[1][1], 0.0001f);  // cos(π/2) ≈ 0
    ASSERT_EQUAL(0.0f, rotation.m[1][2]);
    
    ASSERT_EQUAL(0.0f, rotation.m[2][0]);
    ASSERT_EQUAL(0.0f, rotation.m[2][1]);
    ASSERT_EQUAL(1.0f, rotation.m[2][2]);
    
    // Rotation de 180 degrés
    rotation = nkentseu::math::Matrix3x3::Rotation(nkentseu::math::PI);
    ASSERT_NEAR(-1.0f, rotation.m[0][0], 0.0001f);  // cos(π) = -1
    ASSERT_NEAR(0.0f, rotation.m[0][1], 0.0001f);   // -sin(π) = 0
    ASSERT_NEAR(0.0f, rotation.m[1][0], 0.0001f);   // sin(π) = 0
    ASSERT_NEAR(-1.0f, rotation.m[1][1], 0.0001f);  // cos(π) = -1
}

TEST_CASE(Math, Matrix3x3_Scaling) {
    nkentseu::math::Matrix3x3 scaling = nkentseu::math::Matrix3x3::Scaling(2.0f, 3.0f);
    
    // Matrice d'échelle
    // [sx 0  0]
    // [0  sy 0]
    // [0  0  1]
    ASSERT_EQUAL(2.0f, scaling.m[0][0]);
    ASSERT_EQUAL(0.0f, scaling.m[0][1]);
    ASSERT_EQUAL(0.0f, scaling.m[0][2]);
    
    ASSERT_EQUAL(0.0f, scaling.m[1][0]);
    ASSERT_EQUAL(3.0f, scaling.m[1][1]);
    ASSERT_EQUAL(0.0f, scaling.m[1][2]);
    
    ASSERT_EQUAL(0.0f, scaling.m[2][0]);
    ASSERT_EQUAL(0.0f, scaling.m[2][1]);
    ASSERT_EQUAL(1.0f, scaling.m[2][2]);
}

TEST_CASE(Math, Matrix3x3_Multiplication) {
    nkentseu::math::Matrix3x3 a;
    nkentseu::math::Matrix3x3 b;
    
    // Initialiser avec des valeurs testables
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            a.m[i][j] = static_cast<float>(i * 3 + j + 1); // 1-9
            b.m[i][j] = static_cast<float>(9 - (i * 3 + j)); // 9-1
        }
    }
    
    nkentseu::math::Matrix3x3 c = a * b;
    
    // Calcul manuel de la première cellule
    // c[0][0] = a[0][0]*b[0][0] + a[0][1]*b[1][0] + a[0][2]*b[2][0]
    //         = 1*9 + 2*6 + 3*3 = 9 + 12 + 9 = 30
    ASSERT_EQUAL(30.0f, c.m[0][0]);
    
    // c[0][1] = a[0][0]*b[0][1] + a[0][1]*b[1][1] + a[0][2]*b[2][1]
    //         = 1*8 + 2*5 + 3*2 = 8 + 10 + 6 = 24
    ASSERT_EQUAL(24.0f, c.m[0][1]);
}

TEST_CASE(Math, Matrix3x3_TransformPoint) {
    nkentseu::math::Matrix3x3 translation = nkentseu::math::Matrix3x3::Translation(5.0f, 10.0f);
    nkentseu::math::Vector2 point(2.0f, 3.0f);
    
    nkentseu::math::Vector2 transformed = translation.TransformPoint(point);
    
    // Point translaté
    ASSERT_EQUAL(7.0f, transformed.x);  // 2 + 5
    ASSERT_EQUAL(13.0f, transformed.y); // 3 + 10
    
    // Test avec matrice d'identité
    nkentseu::math::Matrix3x3 identity = nkentseu::math::Matrix3x3::Identity();
    transformed = identity.TransformPoint(point);
    ASSERT_EQUAL(2.0f, transformed.x);
    ASSERT_EQUAL(3.0f, transformed.y);
}

TEST_CASE(Math, Matrix3x3_TransformVector) {
    nkentseu::math::Matrix3x3 scaling = nkentseu::math::Matrix3x3::Scaling(2.0f, 3.0f);
    nkentseu::math::Vector2 vector(1.0f, 1.0f);
    
    nkentseu::math::Vector2 transformed = scaling.TransformVector(vector);
    
    // Vecteur mis à l'échelle (la translation ne s'applique pas aux vecteurs)
    ASSERT_EQUAL(2.0f, transformed.x); // 1 * 2
    ASSERT_EQUAL(3.0f, transformed.y); // 1 * 3
    
    // Rotation d'un vecteur
    nkentseu::math::Matrix3x3 rotation = nkentseu::math::Matrix3x3::Rotation(nkentseu::math::PI);
    vector = nkentseu::math::Vector2(1.0f, 0.0f);
    transformed = rotation.TransformVector(vector);
    
    ASSERT_NEAR(-1.0f, transformed.x, 0.0001f); // cos(π) = -1
    ASSERT_NEAR(0.0f, transformed.y, 0.0001f);  // sin(π) = 0
}

TEST_CASE(Math, Matrix3x3_Determinant) {
    // Déterminant d'une matrice identité = 1
    nkentseu::math::Matrix3x3 identity = nkentseu::math::Matrix3x3::Identity();
    ASSERT_EQUAL(1.0f, identity.Determinant());
    
    // Matrice simple
    nkentseu::math::Matrix3x3 m;
    m.m[0][0] = 1; m.m[0][1] = 2; m.m[0][2] = 3;
    m.m[1][0] = 4; m.m[1][1] = 5; m.m[1][2] = 6;
    m.m[2][0] = 7; m.m[2][1] = 8; m.m[2][2] = 9;
    
    // det = 1*(5*9 - 6*8) - 2*(4*9 - 6*7) + 3*(4*8 - 5*7)
    //     = 1*(45-48) - 2*(36-42) + 3*(32-35)
    //     = 1*(-3) - 2*(-6) + 3*(-3)
    //     = -3 + 12 - 9 = 0
    ASSERT_EQUAL(0.0f, m.Determinant());
    
    // Matrice avec déterminant non nul
    m.m[2][2] = 10;
    // det = 1*(5*10 - 6*8) - 2*(4*10 - 6*7) + 3*(4*8 - 5*7)
    //     = 1*(50-48) - 2*(40-42) + 3*(32-35)
    //     = 1*(2) - 2*(-2) + 3*(-3)
    //     = 2 + 4 - 9 = -3
    ASSERT_EQUAL(-3.0f, m.Determinant());
}

TEST_CASE(Math, Matrix3x3_Transpose) {
    nkentseu::math::Matrix3x3 m;
    m.m[0][0] = 1; m.m[0][1] = 2; m.m[0][2] = 3;
    m.m[1][0] = 4; m.m[1][1] = 5; m.m[1][2] = 6;
    m.m[2][0] = 7; m.m[2][1] = 8; m.m[2][2] = 9;
    
    nkentseu::math::Matrix3x3 transposed = m.Transpose();
    
    ASSERT_EQUAL(1.0f, transposed.m[0][0]);
    ASSERT_EQUAL(4.0f, transposed.m[0][1]);
    ASSERT_EQUAL(7.0f, transposed.m[0][2]);
    
    ASSERT_EQUAL(2.0f, transposed.m[1][0]);
    ASSERT_EQUAL(5.0f, transposed.m[1][1]);
    ASSERT_EQUAL(8.0f, transposed.m[1][2]);
    
    ASSERT_EQUAL(3.0f, transposed.m[2][0]);
    ASSERT_EQUAL(6.0f, transposed.m[2][1]);
    ASSERT_EQUAL(9.0f, transposed.m[2][2]);
    
    // Transposer deux fois donne la matrice originale
    ASSERT_TRUE(m == transposed.Transpose());
}

TEST_CASE(Math, Matrix3x3_Inverse) {
    // Matrice identité est son propre inverse
    nkentseu::math::Matrix3x3 identity = nkentseu::math::Matrix3x3::Identity();
    nkentseu::math::Matrix3x3 inverse = identity.Inverse();
    
    ASSERT_TRUE(identity == inverse);
    
    // Test avec une matrice simple inversible
    nkentseu::math::Matrix3x3 m = nkentseu::math::Matrix3x3::Scaling(2.0f, 3.0f);
    inverse = m.Inverse();
    
    // Inverse d'une matrice d'échelle est l'échelle inverse
    nkentseu::math::Matrix3x3 expectedInverse = nkentseu::math::Matrix3x3::Scaling(0.5f, 1.0f/3.0f);
    
    ASSERT_NEAR(expectedInverse.m[0][0], inverse.m[0][0], 0.0001f);
    ASSERT_NEAR(expectedInverse.m[1][1], inverse.m[1][1], 0.0001f);
    
    // Vérifier que m * inverse = identité
    nkentseu::math::Matrix3x3 product = m * inverse;
    
    ASSERT_NEAR(1.0f, product.m[0][0], 0.0001f);
    ASSERT_NEAR(0.0f, product.m[0][1], 0.0001f);
    ASSERT_NEAR(0.0f, product.m[1][0], 0.0001f);
    ASSERT_NEAR(1.0f, product.m[1][1], 0.0001f);
}