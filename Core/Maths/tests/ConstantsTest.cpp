#include <Maths/MathConstants.h>
#include <Unitest/Unitest.h>

TEST_CASE(Math, Constants_PI) {
    // Test des constantes PI
    ASSERT_NEAR(3.14159265f, nkentseu::math::PI, 0.000001f);
    ASSERT_NEAR(6.28318531f, nkentseu::math::TWO_PI, 0.000001f);
    ASSERT_NEAR(1.57079633f, nkentseu::math::HALF_PI, 0.000001f);
    ASSERT_NEAR(0.78539816f, nkentseu::math::Constants::QUARTER_PI, 0.000001f);
}

TEST_CASE(Math, Constants_Conversions) {
    // Test conversions degrés/radians
    float radians = 180.0f * nkentseu::math::DEG_TO_RAD;
    ASSERT_NEAR(nkentseu::math::PI, radians, 0.000001f);
    
    float degrees = nkentseu::math::PI * nkentseu::math::RAD_TO_DEG;
    ASSERT_NEAR(180.0f, degrees, 0.000001f);
    
    // Conversions spécifiques
    ASSERT_NEAR(90.0f, nkentseu::math::HALF_PI * nkentseu::math::RAD_TO_DEG, 0.000001f);
    ASSERT_NEAR(45.0f, nkentseu::math::Constants::QUARTER_PI * nkentseu::math::RAD_TO_DEG, 0.000001f);
}

TEST_CASE(Math, Constants_MathConstants) {
    // Test autres constantes mathématiques
    ASSERT_NEAR(2.71828183f, nkentseu::math::Constants::E, 0.000001f);
    ASSERT_NEAR(1.41421356f, nkentseu::math::Constants::SQRT2, 0.000001f);
    ASSERT_NEAR(1.73205081f, nkentseu::math::Constants::SQRT3, 0.000001f);
    ASSERT_NEAR(1.61803399f, nkentseu::math::Constants::GOLDEN_RATIO, 0.000001f);
}

TEST_CASE(Math, Constants_GlobalAccess) {
    // Test accès global aux constantes
    float pi = nkentseu::math::PI;
    float twoPi = nkentseu::math::TWO_PI;
    float halfPi = nkentseu::math::HALF_PI;
    
    ASSERT_NEAR(3.14159265f, pi, 0.000001f);
    ASSERT_NEAR(6.28318531f, twoPi, 0.000001f);
    ASSERT_NEAR(1.57079633f, halfPi, 0.000001f);
}

TEST_CASE(Math, Constants_UsageInCalculations) {
    // Test utilisation des constantes dans des calculs
    float circleArea = nkentseu::math::PI * 5.0f * 5.0f;
    ASSERT_NEAR(78.53981634f, circleArea, 0.000001f);
    
    float circumference = nkentseu::math::TWO_PI * 5.0f;
    ASSERT_NEAR(31.41592654f, circumference, 0.0001f);
    
    // Conversion d'angle
    float angleDegrees = 45.0f;
    float angleRadians = angleDegrees * nkentseu::math::DEG_TO_RAD;
    ASSERT_NEAR(nkentseu::math::Constants::QUARTER_PI, angleRadians, 0.000001f);
}