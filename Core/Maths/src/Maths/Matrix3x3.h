#pragma once
#include "Vector2.h"

namespace nkentseu {
    namespace math {
        class Matrix3x3 {
            public:
                float m[3][3];
                
                Matrix3x3();
                // Matrix3x3(const Matrix3x3& other);
                
                // Matrice identité
                static Matrix3x3 Identity();
                
                // Matrices de transformation
                static Matrix3x3 Translation(float x, float y);
                static Matrix3x3 Rotation(float angle);
                static Matrix3x3 Scaling(float sx, float sy);
                
                // Opérations matricielles
                Matrix3x3 operator*(const Matrix3x3& other) const;
                Matrix3x3 operator+(const Matrix3x3& other) const;
                Matrix3x3 operator-(const Matrix3x3& other) const;
                Matrix3x3 operator*(float scalar) const;
                Matrix3x3 operator/(float scalar) const;
                
                // Opérations d'affectation
                Matrix3x3& operator+=(const Matrix3x3& other);
                Matrix3x3& operator-=(const Matrix3x3& other);
                Matrix3x3& operator*=(float scalar);
                Matrix3x3& operator/=(float scalar);
                
                // Multiplication par vecteur
                Vector2 operator*(const Vector2& v) const;
                
                Vector2 TransformPoint(const Vector2& point) const;
                Vector2 TransformVector(const Vector2& vector) const;
                
                // Méthodes utilitaires
                Matrix3x3 Inverse() const;
                Matrix3x3 Transpose() const;
                float Determinant() const;

                bool operator==(const Matrix3x3& other) const {
                    for (int i = 0; i < 3; ++i) {
                        for (int j = 0; j < 3; ++j) {
                            if (m[i][j] != other.m[i][j]) {
                                return false;
                            }
                        }
                    }
                    return true;
                }

                bool operator!=(const Matrix3x3& other) const {
                    return !(*this == other);
                }
        };
        
        // Opérateur de multiplication scalaire à gauche (non-membre)
        inline Matrix3x3 operator*(float scalar, const Matrix3x3& matrix) {
            return matrix * scalar;
        }
    }
}