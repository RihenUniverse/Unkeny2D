#include "Matrix3x3.h"
#include <cmath>
#include <cstring>

namespace nkentseu {
    namespace math {
        Matrix3x3::Matrix3x3() {
            for (int i = 0; i < 3; i++)
                for (int j = 0; j < 3; j++)
                    m[i][j] = (i == j) ? 1.0f : 0.0f;
        }

        // Matrix3x3::Matrix3x3(const Matrix3x3& other) {
        //     std::memcpy(m, other.m, sizeof(m));
        // }
        
        Matrix3x3 Matrix3x3::Identity() {
            return Matrix3x3();
        }
        
        Matrix3x3 Matrix3x3::Translation(float x, float y) {
            Matrix3x3 mat = Identity();
            mat.m[0][2] = x;
            mat.m[1][2] = y;
            return mat;
        }
        
        Matrix3x3 Matrix3x3::Rotation(float angle) {
            Matrix3x3 mat = Identity();
            float cosA = std::cos(angle);
            float sinA = std::sin(angle);
            
            mat.m[0][0] = cosA;
            mat.m[0][1] = -sinA;
            mat.m[1][0] = sinA;
            mat.m[1][1] = cosA;
            
            return mat;
        }
        
        Matrix3x3 Matrix3x3::Scaling(float sx, float sy) {
            Matrix3x3 mat = Identity();
            mat.m[0][0] = sx;
            mat.m[1][1] = sy;
            return mat;
        }
        
        Matrix3x3 Matrix3x3::operator*(const Matrix3x3& other) const {
            Matrix3x3 result;
            
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    result.m[i][j] = 0.0f;
                    for (int k = 0; k < 3; k++) {
                        result.m[i][j] += m[i][k] * other.m[k][j];
                    }
                }
            }
            
            return result;
        }
        
        Vector2 Matrix3x3::TransformPoint(const Vector2& point) const {
            float x = m[0][0] * point.x + m[0][1] * point.y + m[0][2];
            float y = m[1][0] * point.x + m[1][1] * point.y + m[1][2];
            float w = m[2][0] * point.x + m[2][1] * point.y + m[2][2];
            
            if (w != 0.0f && w != 1.0f) {
                x /= w;
                y /= w;
            }
            
            return Vector2(x, y);
        }
        
        Vector2 Matrix3x3::TransformVector(const Vector2& vector) const {
            float x = m[0][0] * vector.x + m[0][1] * vector.y;
            float y = m[1][0] * vector.x + m[1][1] * vector.y;
            
            return Vector2(x, y);
        }
        
        float Matrix3x3::Determinant() const {
            // Formule du déterminant 3x3 : a(ei - fh) - b(di - fg) + c(dh - eg)
            return m[0][0] * (m[1][1]*m[2][2] - m[1][2]*m[2][1])
                 - m[0][1] * (m[1][0]*m[2][2] - m[1][2]*m[2][0])
                 + m[0][2] * (m[1][0]*m[2][1] - m[1][1]*m[2][0]);
        }
        
        Matrix3x3 Matrix3x3::Transpose() const {
            Matrix3x3 result;
            for (int i = 0; i < 3; ++i) {
                for (int j = 0; j < 3; ++j) {
                    result.m[i][j] = m[j][i];
                }
            }
            return result;
        }
        
        Matrix3x3 Matrix3x3::Inverse() const {
            float det = Determinant();
            
            // Vérifier si la matrice est inversible
            if (std::abs(det) < 1e-10f) {
                // Retourner la matrice identité comme fallback
                return Matrix3x3::Identity();
            }
            
            float invDet = 1.0f / det;
            Matrix3x3 result;
            
            // Calcul de la matrice des cofacteurs transposée (comatrice)
            result.m[0][0] = invDet * (m[1][1]*m[2][2] - m[1][2]*m[2][1]);
            result.m[0][1] = invDet * (m[0][2]*m[2][1] - m[0][1]*m[2][2]);
            result.m[0][2] = invDet * (m[0][1]*m[1][2] - m[0][2]*m[1][1]);
            
            result.m[1][0] = invDet * (m[1][2]*m[2][0] - m[1][0]*m[2][2]);
            result.m[1][1] = invDet * (m[0][0]*m[2][2] - m[0][2]*m[2][0]);
            result.m[1][2] = invDet * (m[0][2]*m[1][0] - m[0][0]*m[1][2]);
            
            result.m[2][0] = invDet * (m[1][0]*m[2][1] - m[1][1]*m[2][0]);
            result.m[2][1] = invDet * (m[0][1]*m[2][0] - m[0][0]*m[2][1]);
            result.m[2][2] = invDet * (m[0][0]*m[1][1] - m[0][1]*m[1][0]);
            
            return result;
        }
        
        // Opérateurs arithmétiques supplémentaires
        Matrix3x3 Matrix3x3::operator+(const Matrix3x3& other) const {
            Matrix3x3 result;
            for (int i = 0; i < 3; ++i) {
                for (int j = 0; j < 3; ++j) {
                    result.m[i][j] = m[i][j] + other.m[i][j];
                }
            }
            return result;
        }
        
        Matrix3x3 Matrix3x3::operator-(const Matrix3x3& other) const {
            Matrix3x3 result;
            for (int i = 0; i < 3; ++i) {
                for (int j = 0; j < 3; ++j) {
                    result.m[i][j] = m[i][j] - other.m[i][j];
                }
            }
            return result;
        }
        
        Matrix3x3 Matrix3x3::operator*(float scalar) const {
            Matrix3x3 result;
            for (int i = 0; i < 3; ++i) {
                for (int j = 0; j < 3; ++j) {
                    result.m[i][j] = m[i][j] * scalar;
                }
            }
            return result;
        }
        
        Matrix3x3 Matrix3x3::operator/(float scalar) const {
            if (std::abs(scalar) < 1e-10f) {
                // Division par zéro, retourner la matrice identité comme fallback
                return Matrix3x3::Identity();
            }
            
            float invScalar = 1.0f / scalar;
            Matrix3x3 result;
            for (int i = 0; i < 3; ++i) {
                for (int j = 0; j < 3; ++j) {
                    result.m[i][j] = m[i][j] * invScalar;
                }
            }
            return result;
        }
        
        // Opérateurs d'affectation composés
        Matrix3x3& Matrix3x3::operator+=(const Matrix3x3& other) {
            for (int i = 0; i < 3; ++i) {
                for (int j = 0; j < 3; ++j) {
                    m[i][j] += other.m[i][j];
                }
            }
            return *this;
        }
        
        Matrix3x3& Matrix3x3::operator-=(const Matrix3x3& other) {
            for (int i = 0; i < 3; ++i) {
                for (int j = 0; j < 3; ++j) {
                    m[i][j] -= other.m[i][j];
                }
            }
            return *this;
        }
        
        Matrix3x3& Matrix3x3::operator*=(float scalar) {
            for (int i = 0; i < 3; ++i) {
                for (int j = 0; j < 3; ++j) {
                    m[i][j] *= scalar;
                }
            }
            return *this;
        }
        
        Matrix3x3& Matrix3x3::operator/=(float scalar) {
            if (std::abs(scalar) < 1e-10f) {
                // Division par zéro, ne rien faire ou mettre à zéro
                for (int i = 0; i < 3; ++i) {
                    for (int j = 0; j < 3; ++j) {
                        m[i][j] = 0.0f;
                    }
                }
                return *this;
            }
            
            float invScalar = 1.0f / scalar;
            for (int i = 0; i < 3; ++i) {
                for (int j = 0; j < 3; ++j) {
                    m[i][j] *= invScalar;
                }
            }
            return *this;
        }
        
        // Opérateur de multiplication par un vecteur (si utile)
        Vector2 Matrix3x3::operator*(const Vector2& v) const {
            return TransformPoint(v);
        }
    }
}