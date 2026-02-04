#include <Maths/Vector2.h>
#include <Unitest/Unitest.h>

TEST_CASE(Math, Vector2_DefaultConstructor) {
    nkentseu::math::Vector2 v;
    ASSERT_EQUAL(0.0f, v.x);
    ASSERT_EQUAL(0.0f, v.y);
}

TEST_CASE(Math, Vector2_ValueConstructor) {
    nkentseu::math::Vector2 v(5.0f);
    ASSERT_EQUAL(5.0f, v.x);
    ASSERT_EQUAL(5.0f, v.y);
}

TEST_CASE(Math, Vector2_XYConstructor) {
    nkentseu::math::Vector2 v(3.0f, 4.0f);
    ASSERT_EQUAL(3.0f, v.x);
    ASSERT_EQUAL(4.0f, v.y);
}

TEST_CASE(Math, Vector2_Addition) {
    nkentseu::math::Vector2 v1(1.0f, 2.0f);
    nkentseu::math::Vector2 v2(3.0f, 4.0f);
    nkentseu::math::Vector2 result = v1 + v2;
    
    ASSERT_EQUAL(4.0f, result.x);
    ASSERT_EQUAL(6.0f, result.y);
}

TEST_CASE(Math, Vector2_Subtraction) {
    nkentseu::math::Vector2 v1(5.0f, 5.0f);
    nkentseu::math::Vector2 v2(2.0f, 3.0f);
    nkentseu::math::Vector2 result = v1 - v2;
    
    ASSERT_EQUAL(3.0f, result.x);
    ASSERT_EQUAL(2.0f, result.y);
}

TEST_CASE(Math, Vector2_Multiplication) {
    nkentseu::math::Vector2 v(2.0f, 3.0f);
    nkentseu::math::Vector2 result = v * 2.0f;
    
    ASSERT_EQUAL(4.0f, result.x);
    ASSERT_EQUAL(6.0f, result.y);
}

TEST_CASE(Math, Vector2_Division) {
    nkentseu::math::Vector2 v(6.0f, 8.0f);
    nkentseu::math::Vector2 result = v / 2.0f;
    
    ASSERT_EQUAL(3.0f, result.x);
    ASSERT_EQUAL(4.0f, result.y);
}

TEST_CASE(Math, Vector2_CompoundAssignment) {
    nkentseu::math::Vector2 v(1.0f, 2.0f);
    v += nkentseu::math::Vector2(3.0f, 4.0f);
    
    ASSERT_EQUAL(4.0f, v.x);
    ASSERT_EQUAL(6.0f, v.y);
}

TEST_CASE(Math, Vector2_Comparison) {
    nkentseu::math::Vector2 v1(1.0f, 2.0f);
    nkentseu::math::Vector2 v2(1.0f, 2.0f);
    nkentseu::math::Vector2 v3(3.0f, 4.0f);
    
    ASSERT_TRUE(v1 == v2);
    ASSERT_TRUE(v1 != v3);
    ASSERT_FALSE(v1 == v3);
    ASSERT_FALSE(v1 != v2);
}

TEST_CASE(Math, Vector2_Magnitude) {
    nkentseu::math::Vector2 v(3.0f, 4.0f);
    float magnitude = v.Magnitude();
    
    ASSERT_EQUAL(5.0f, magnitude);
    
    nkentseu::math::Vector2 zero;
    ASSERT_EQUAL(0.0f, zero.Magnitude());
}

TEST_CASE(Math, Vector2_Normalized) {
    nkentseu::math::Vector2 v(3.0f, 4.0f);
    nkentseu::math::Vector2 normalized = v.Normalized();
    
    ASSERT_NEAR(1.0f, normalized.Magnitude(), 0.0001f);
    ASSERT_NEAR(0.6f, normalized.x, 0.0001f);
    ASSERT_NEAR(0.8f, normalized.y, 0.0001f);
}

TEST_CASE(Math, Vector2_Distance) {
    nkentseu::math::Vector2 v1(0.0f, 0.0f);
    nkentseu::math::Vector2 v2(3.0f, 4.0f);
    float distance = v1.Distance(v2);
    
    ASSERT_EQUAL(5.0f, distance);
    
    // Distance entre deux points identiques
    ASSERT_EQUAL(0.0f, v1.Distance(v1));
}

TEST_CASE(Math, Vector2_DotProduct) {
    nkentseu::math::Vector2 v1(1.0f, 2.0f);
    nkentseu::math::Vector2 v2(3.0f, 4.0f);
    float dot = v1.Dot(v2);
    
    ASSERT_EQUAL(11.0f, dot); // 1*3 + 2*4 = 3 + 8 = 11
    
    // Vecteurs orthogonaux
    nkentseu::math::Vector2 up(0.0f, 1.0f);
    nkentseu::math::Vector2 right(1.0f, 0.0f);
    ASSERT_EQUAL(0.0f, up.Dot(right));
}

TEST_CASE(Math, Vector2_Accessors) {
    nkentseu::math::Vector2 v(10.0f, 20.0f);
    
    // Test des différents accesseurs
    ASSERT_EQUAL(10.0f, v.width);
    ASSERT_EQUAL(20.0f, v.height);
    
    ASSERT_EQUAL(10.0f, v.u);
    ASSERT_EQUAL(20.0f, v.v);
    
    ASSERT_EQUAL(10.0f, v.data[0]);
    ASSERT_EQUAL(20.0f, v.data[1]);
    
    // Modification via union
    v.width = 30.0f;
    v.height = 40.0f;
    
    ASSERT_EQUAL(30.0f, v.x);
    ASSERT_EQUAL(40.0f, v.y);
}

TEST_CASE(Math, Vector2_StaticConstants) {
    // Test des constantes statiques
    ASSERT_EQUAL(0.0f, nkentseu::math::Vector2::Zero.x);
    ASSERT_EQUAL(0.0f, nkentseu::math::Vector2::Zero.y);
    
    ASSERT_EQUAL(1.0f, nkentseu::math::Vector2::One.x);
    ASSERT_EQUAL(1.0f, nkentseu::math::Vector2::One.y);
    
    ASSERT_EQUAL(0.0f, nkentseu::math::Vector2::Up.x);
    ASSERT_EQUAL(1.0f, nkentseu::math::Vector2::Up.y);
    
    ASSERT_EQUAL(0.0f, nkentseu::math::Vector2::Down.x);
    ASSERT_EQUAL(-1.0f, nkentseu::math::Vector2::Down.y);
    
    ASSERT_EQUAL(-1.0f, nkentseu::math::Vector2::Left.x);
    ASSERT_EQUAL(0.0f, nkentseu::math::Vector2::Left.y);
    
    ASSERT_EQUAL(1.0f, nkentseu::math::Vector2::Right.x);
    ASSERT_EQUAL(0.0f, nkentseu::math::Vector2::Right.y);
}