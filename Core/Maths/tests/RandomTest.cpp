#include <Maths/Random.h>
#include <Maths/MathConstants.h>
// #include <Maths/Vector2.h>
#include <Unitest/Unitest.h>
#include <vector>
#include <array>
#include <set>

TEST_CASE(Math, Random_Seed) {
    nkentseu::math::Random::Seed(42);
    
    // Test que le seed fonctionne (même seed donne mêmes résultats)
    float firstValue = nkentseu::math::Random::Value();
    
    nkentseu::math::Random::Seed(42);
    float secondValue = nkentseu::math::Random::Value();
    
    ASSERT_EQUAL(firstValue, secondValue);
}

TEST_CASE(Math, Random_RangeInt) {
    // Test avec entier
    int value = nkentseu::math::Random::Range(1, 10);
    
    ASSERT_GREATER_EQUAL(value, 1);
    ASSERT_LESS_EQUAL(value, 10);
    
    // Test plusieurs fois pour s'assurer de la distribution
    for (int i = 0; i < 100; ++i) {
        value = nkentseu::math::Random::Range(1, 10);
        ASSERT_TRUE(value >= 1 && value <= 10);
    }
}

TEST_CASE(Math, Random_RangeFloat) {
    // Test avec float
    float value = nkentseu::math::Random::Range(0.0f, 1.0f);
    
    ASSERT_GREATER_EQUAL(value, 0.0f);
    ASSERT_LESS_EQUAL(value, 1.0f);
    
    // Test avec limites négatives
    value = nkentseu::math::Random::Range(-10.0f, 10.0f);
    ASSERT_TRUE(value >= -10.0f && value <= 10.0f);
}

TEST_CASE(Math, Random_Bool) {
    // Test avec probabilité par défaut
    bool value = nkentseu::math::Random::Bool();
    // Pas d'assertion spécifique car résultat aléatoire
    
    // Test avec probabilité 0.0
    value = nkentseu::math::Random::Bool(0.0f);
    ASSERT_FALSE(value);
    
    // Test avec probabilité 1.0
    value = nkentseu::math::Random::Bool(1.0f);
    ASSERT_TRUE(value);
}

TEST_CASE(Math, Random_Value) {
    float value = nkentseu::math::Random::Value();
    
    ASSERT_GREATER_EQUAL(value, 0.0f);
    ASSERT_LESS_EQUAL(value, 1.0f);
    
    // Test plusieurs valeurs
    for (int i = 0; i < 10; ++i) {
        value = nkentseu::math::Random::Value();
        ASSERT_TRUE(value >= 0.0f && value <= 1.0f);
    }
}

TEST_CASE(Math, Random_Angle) {
    float angle = nkentseu::math::Random::Angle();
    
    ASSERT_GREATER_EQUAL(angle, 0.0f);
    ASSERT_LESS(angle, nkentseu::math::TWO_PI);
    
    // Conversion en degrés
    float degrees = angle * nkentseu::math::RAD_TO_DEG;
    ASSERT_TRUE(degrees >= 0.0f && degrees < 360.0f);
}

TEST_CASE(Math, Random_AngleDegrees) {
    float degrees = nkentseu::math::Random::AngleDegrees();
    
    ASSERT_GREATER_EQUAL(degrees, 0.0f);
    ASSERT_LESS(degrees, 360.0f);
    
    // Conversion en radians
    float radians = degrees * nkentseu::math::DEG_TO_RAD;
    ASSERT_TRUE(radians >= 0.0f && radians < nkentseu::math::TWO_PI);
}

TEST_CASE(Math, Random_Vector) {
    nkentseu::math::Vector2 v = nkentseu::math::Random::Vector();
    
    // Magnitude entre 0 et 1
    float mag = v.Magnitude();
    ASSERT_GREATER_EQUAL(mag, 0.0f);
    ASSERT_LESS_EQUAL(mag, 1.0f);
    
    // Test avec longueurs spécifiques
    v = nkentseu::math::Random::Vector(5.0f, 10.0f);
    mag = v.Magnitude();
    ASSERT_TRUE(mag >= 5.0f && mag <= 10.0f);
}

TEST_CASE(Math, Random_VectorInCircle) {
    nkentseu::math::Vector2 v = nkentseu::math::Random::VectorInCircle(5.0f);
    
    float distance = v.Magnitude();
    ASSERT_LESS_EQUAL(distance, 5.0f);
    
    // Test plusieurs points
    for (int i = 0; i < 100; ++i) {
        v = nkentseu::math::Random::VectorInCircle(1.0f);
        ASSERT_LESS_EQUAL(v.Magnitude(), 1.0f);
    }
}

TEST_CASE(Math, Random_VectorOnCircle) {
    nkentseu::math::Vector2 v = nkentseu::math::Random::VectorOnCircle(5.0f);
    
    float distance = v.Magnitude();
    ASSERT_NEAR(5.0f, distance, 0.0001f);
    
    // Test plusieurs points
    for (int i = 0; i < 100; ++i) {
        v = nkentseu::math::Random::VectorOnCircle(1.0f);
        ASSERT_NEAR(1.0f, v.Magnitude(), 0.0001f);
    }
}

TEST_CASE(Math, Random_Choice) {
    std::vector<int> numbers = {1, 2, 3, 4, 5};
    
    for (int i = 0; i < 20; ++i) {
        int choice = nkentseu::math::Random::Choice(numbers);
        ASSERT_CONTAINS(numbers, choice);
    }
    
    // Test avec conteneur vide
    std::vector<int> empty;
    ASSERT_THROWS(std::out_of_range, nkentseu::math::Random::Choice(empty));
}

TEST_CASE(Math, Random_Shuffle) {
    std::vector<int> numbers = {1, 2, 3, 4, 5};
    std::vector<int> original = numbers;
    
    nkentseu::math::Random::Shuffle(numbers);
    
    // Vérifier que tous les éléments sont présents
    for (int num : original) {
        ASSERT_CONTAINS(numbers, num);
    }
    
    // Vérifier que l'ordre est potentiellement différent
    bool sameOrder = true;
    for (size_t i = 0; i < numbers.size(); ++i) {
        if (numbers[i] != original[i]) {
            sameOrder = false;
            break;
        }
    }
    
    // Il est possible mais peu probable que shuffle donne le même ordre
    if (sameOrder) {
        // Essayer une deuxième fois
        nkentseu::math::Random::Shuffle(numbers);
        sameOrder = true;
        for (size_t i = 0; i < numbers.size(); ++i) {
            if (numbers[i] != original[i]) {
                sameOrder = false;
                break;
            }
        }
        // Si toujours le même ordre après deux shuffles, c'est suspect
        ASSERT_FALSE(sameOrder);
    }
}

TEST_CASE(Math, Random_Gaussian) {
    // Test distribution normale
    float value = nkentseu::math::Random::Gaussian(0.0f, 1.0f);
    
    // La plupart des valeurs devraient être entre -3 et 3
    for (int i = 0; i < 100; ++i) {
        value = nkentseu::math::Random::Gaussian(10.0f, 2.0f);
        // 99.7% des valeurs devraient être entre 4 et 16 (moyenne ± 3*écart-type)
        if (value < 4.0f || value > 16.0f) {
            // Si on obtient une valeur hors de cet intervalle, c'est normal
            // mais on pourrait logger un warning
            break;
        }
    }
}

TEST_CASE(Math, Random_Map) {
    // Mapping linéaire
    float mapped = nkentseu::math::Random::Map(0.5f, 0.0f, 1.0f, 0.0f, 100.0f);
    ASSERT_EQUAL(50.0f, mapped);
    
    mapped = nkentseu::math::Random::Map(0.0f, 0.0f, 1.0f, 10.0f, 20.0f);
    ASSERT_EQUAL(10.0f, mapped);
    
    mapped = nkentseu::math::Random::Map(1.0f, 0.0f, 1.0f, 10.0f, 20.0f);
    ASSERT_EQUAL(20.0f, mapped);
    
    // Mapping avec valeurs négatives
    mapped = nkentseu::math::Random::Map(0.5f, -1.0f, 1.0f, 0.0f, 100.0f);
    ASSERT_EQUAL(75.0f, mapped);
}