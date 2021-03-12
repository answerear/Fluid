

namespace Tiny3D
{
    template <typename T>
    inline void TMatrix4<T>::makeIdentity()
    {
        m4x4[0][0] = TReal<T>::ONE;
        m4x4[0][1] = TReal<T>::ZERO;
        m4x4[0][2] = TReal<T>::ZERO;
        m4x4[0][3] = TReal<T>::ZERO;
        m4x4[1][0] = TReal<T>::ZERO;
        m4x4[1][1] = TReal<T>::ONE;
        m4x4[1][2] = TReal<T>::ZERO;
        m4x4[1][3] = TReal<T>::ZERO;
        m4x4[2][0] = TReal<T>::ZERO;
        m4x4[2][1] = TReal<T>::ZERO;
        m4x4[2][2] = TReal<T>::ONE;
        m4x4[2][3] = TReal<T>::ZERO;
        m4x4[3][0] = TReal<T>::ZERO;
        m4x4[3][1] = TReal<T>::ZERO;
        m4x4[3][2] = TReal<T>::ZERO;
        m4x4[3][3] = TReal<T>::ONE;
    }

    template <typename T>
    inline void TMatrix4<T>::makeZero()
    {
        m4x4[0][0] = m4x4[0][1] = m4x4[0][2] = m4x4[0][3] = TReal<T>::ZERO;
        m4x4[1][0] = m4x4[1][1] = m4x4[1][2] = m4x4[1][3] = TReal<T>::ZERO;
        m4x4[2][0] = m4x4[2][1] = m4x4[2][2] = m4x4[2][3] = TReal<T>::ZERO;
        m4x4[3][0] = m4x4[3][1] = m4x4[3][2] = m4x4[3][3] = TReal<T>::ZERO;
    }

    template <typename T>
    inline TMatrix4<T> &TMatrix4<T>::operator =(const TMatrix4 &other)
    {
        memcpy(mTuples, other.mTuples, sizeof(mTuples));
        return *this;
    }

    template <typename T>
    inline void TMatrix4<T>::operator =(const TMatrix3<T> &rkMat)
    {
        m4x4[0][0] = rkMat[0][0], m4x4[0][1] = rkMat[0][1], m4x4[0][2] = rkMat[0][2];
        m4x4[1][0] = rkMat[1][0], m4x4[1][1] = rkMat[1][1], m4x4[1][2] = rkMat[1][2];
        m4x4[2][0] = rkMat[2][0], m4x4[2][1] = rkMat[2][1], m4x4[2][2] = rkMat[2][2];
    }

    template <typename T>
    inline TMatrix4<T>::TMatrix4(bool isZero /* = true */)
    {
        if (isZero)
            makeZero();
        else
            makeIdentity();
    }

    template <typename T>
    inline TMatrix4<T>::TMatrix4(const TMatrix4 &other)
    {
        memcpy(mTuples, other.mTuples, sizeof(mTuples));
    }

    template <typename T>
    inline TMatrix4<T>::TMatrix4(
        T m00, T m01, T m02, T m03, 
        T m10, T m11, T m12, T m13, 
        T other0, T other1, T other2, T other3, 
        T m30, T m31, T m32, T m33)
    {
        m4x4[0][0] = m00;
        m4x4[0][1] = m01;
        m4x4[0][2] = m02;
        m4x4[0][3] = m03;
        m4x4[1][0] = m10;
        m4x4[1][1] = m11;
        m4x4[1][2] = m12;
        m4x4[1][3] = m13;
        m4x4[2][0] = other0;
        m4x4[2][1] = other1;
        m4x4[2][2] = other2;
        m4x4[2][3] = other3;
        m4x4[3][0] = m30;
        m4x4[3][1] = m31;
        m4x4[3][2] = m32;
        m4x4[3][3] = m33;
    }

    template <typename T>
    inline TMatrix4<T>::TMatrix4(const TMatrix3<T> &rkMat)
    {
        operator =(rkMat);
        m4x4[0][3] = m4x4[1][3] = m4x4[2][3] = TReal<T>::ZERO;
        m4x4[3][3] = TReal<T>::ONE;
        m4x4[3][0] = m4x4[3][1] = m4x4[3][2] = TReal<T>::ZERO;
    }

    template <typename T>
    inline TMatrix4<T>::TMatrix4(const TQuaternion<T> &rkRot)
    {
        TMatrix3<T> mat;
        rkRot.toRotationMatrix(mat);
        operator =(mat);
        m4x4[0][3] = m4x4[1][3] = m4x4[2][3] = TReal<T>::ZERO;
        m4x4[3][3] = TReal<T>::ONE;
        m4x4[3][0] = m4x4[3][1] = m4x4[3][2] = TReal<T>::ZERO;
    }

    template <typename T>
    inline TMatrix4<T>::TMatrix4(const TVector3<T> &rkPos)
    {
        m4x4[0][0] = TReal<T>::ONE,  m4x4[0][1] = TReal<T>::ZERO, m4x4[0][2] = TReal<T>::ZERO, m4x4[0][3] = rkPos.x();
        m4x4[1][0] = TReal<T>::ZERO, m4x4[1][1] = TReal<T>::ONE,  m4x4[1][2] = TReal<T>::ZERO, m4x4[1][3] = rkPos.y();
        m4x4[2][0] = TReal<T>::ZERO, m4x4[2][1] = TReal<T>::ZERO, m4x4[2][2] = TReal<T>::ONE,  m4x4[2][3] = rkPos.z();
        m4x4[3][0] = TReal<T>::ZERO, m4x4[3][1] = TReal<T>::ZERO, m4x4[3][2] = TReal<T>::ZERO, m4x4[3][3] = TReal<T>::ONE;
    }

    template <typename T>
    inline TMatrix4<T>::TMatrix4(T m00, T m11, T m22, T m33)
    {
        m4x4[0][0] = m00,       m4x4[0][1] = TReal<T>::ZERO, m4x4[0][2] = TReal<T>::ZERO, m4x4[0][3] = TReal<T>::ZERO;
        m4x4[1][0] = TReal<T>::ZERO, m4x4[1][1] = m11,       m4x4[1][2] = TReal<T>::ZERO, m4x4[1][3] = TReal<T>::ZERO;
        m4x4[2][0] = TReal<T>::ZERO, m4x4[2][1] = TReal<T>::ZERO, m4x4[2][2] = m22,       m4x4[2][3] = TReal<T>::ZERO;
        m4x4[3][0] = TReal<T>::ZERO, m4x4[3][1] = TReal<T>::ZERO, m4x4[3][2] = TReal<T>::ZERO, m4x4[3][3] = m33;
    }

    template <typename T>
    inline TMatrix4<T>::TMatrix4(const TVector3<T> &X, const TVector3<T> &Y, const TVector3<T> &Z)
    {
        m4x4[0][0] = X[0],      m4x4[0][1] = Y[0],      m4x4[0][2] = Z[0],      m4x4[0][3] = TReal<T>::ZERO;
        m4x4[1][0] = X[1],      m4x4[1][1] = Y[1],      m4x4[1][2] = Z[1],      m4x4[1][3] = TReal<T>::ZERO;
        m4x4[2][0] = X[2],      m4x4[2][1] = Y[2],      m4x4[2][2] = Z[2],      m4x4[2][3] = TReal<T>::ZERO;
        m4x4[3][0] = TReal<T>::ZERO, m4x4[3][1] = TReal<T>::ZERO, m4x4[3][2] = TReal<T>::ZERO, m4x4[3][3] = TReal<T>::ONE;
    }

    template <typename T>
    inline TMatrix4<T>::operator const T *() const
    {
        return mTuples;
    }

    template <typename T>
    inline TMatrix4<T>::operator T *()
    {
        return mTuples;
    }

    template <typename T>
    inline const T *TMatrix4<T>::operator [](size_t row) const
    {
        T3D_ASSERT(row < 4);
        return m4x4[row];
    }

    template <typename T>
    inline T *TMatrix4<T>::operator [](size_t row)
    {
        T3D_ASSERT(row < 4);
        return m4x4[row];
    }

    template <typename T>
    inline T TMatrix4<T>::operator ()(size_t row, size_t col) const
    {
        return m4x4[row][col];
    }

    template <typename T>
    inline T &TMatrix4<T>::operator ()(size_t row, size_t col)
    {
        return m4x4[row][col];
    }

    template <typename T>
    inline int32_t TMatrix4<T>::compareArrays(const TMatrix4 &other) const
    {
        return memcmp(mTuples, other.mTuples, sizeof(mTuples));
    }

    template <typename T>
    inline bool TMatrix4<T>::operator ==(const TMatrix4 &other) const
    {
        return compareArrays(other) == 0;
    }

    template <typename T>
    inline bool TMatrix4<T>::operator !=(const TMatrix4 &other) const
    {
        return compareArrays(other) != 0;
    }

    template <typename T>
    inline bool TMatrix4<T>::operator <(const TMatrix4 &other) const
    {
        return compareArrays(other) < 0;
    }

    template <typename T>
    inline bool TMatrix4<T>::operator <=(const TMatrix4 &other) const
    {
        return compareArrays(other) <= 0;
    }

    template <typename T>
    inline bool TMatrix4<T>::operator >(const TMatrix4 &other) const
    {
        return compareArrays(other) > 0;
    }

    template <typename T>
    inline bool TMatrix4<T>::operator >=(const TMatrix4 &other) const
    {
        return compareArrays(other) >= 0;
    }

    template <typename T>
    inline TMatrix4<T> TMatrix4<T>::operator +(const TMatrix4 &other) const
    {
        return TMatrix4(
            m4x4[0][0] + other.m4x4[0][0], m4x4[0][1] + other.m4x4[0][1], m4x4[0][2] + other.m4x4[0][2], m4x4[0][3] + other.m4x4[0][3],
            m4x4[1][0] + other.m4x4[1][0], m4x4[1][1] + other.m4x4[1][1], m4x4[1][2] + other.m4x4[1][2], m4x4[1][3] + other.m4x4[1][3],
            m4x4[2][0] + other.m4x4[2][0], m4x4[2][1] + other.m4x4[2][1], m4x4[2][2] + other.m4x4[2][2], m4x4[2][3] + other.m4x4[2][3],
            m4x4[3][0] + other.m4x4[3][0], m4x4[3][1] + other.m4x4[3][1], m4x4[3][2] + other.m4x4[3][2], m4x4[3][3] + other.m4x4[3][3]
        );
    }

    template <typename T>
    inline TMatrix4<T> TMatrix4<T>::operator -(const TMatrix4 &other) const
    {
        return TMatrix4(
            m4x4[0][0] - other.m4x4[0][0], m4x4[0][1] - other.m4x4[0][1], m4x4[0][2] - other.m4x4[0][2], m4x4[0][3] - other.m4x4[0][3],
            m4x4[1][0] - other.m4x4[1][0], m4x4[1][1] - other.m4x4[1][1], m4x4[1][2] - other.m4x4[1][2], m4x4[1][3] - other.m4x4[1][3],
            m4x4[2][0] - other.m4x4[2][0], m4x4[2][1] - other.m4x4[2][1], m4x4[2][2] - other.m4x4[2][2], m4x4[2][3] - other.m4x4[2][3],
            m4x4[3][0] - other.m4x4[3][0], m4x4[3][1] - other.m4x4[3][1], m4x4[3][2] - other.m4x4[3][2], m4x4[3][3] - other.m4x4[3][3]
        );
    }

    template <typename T>
    inline TMatrix4<T> TMatrix4<T>::operator *(const TMatrix4 &other) const
    {
        return TMatrix4(
            m4x4[0][0] * other.m4x4[0][0] + m4x4[0][1] * other.m4x4[1][0] + m4x4[0][2] * other.m4x4[2][0] + m4x4[0][3] * other.m4x4[3][0],
            m4x4[0][0] * other.m4x4[0][1] + m4x4[0][1] * other.m4x4[1][1] + m4x4[0][2] * other.m4x4[2][1] + m4x4[0][3] * other.m4x4[3][1],
            m4x4[0][0] * other.m4x4[0][2] + m4x4[0][1] * other.m4x4[1][2] + m4x4[0][2] * other.m4x4[2][2] + m4x4[0][3] * other.m4x4[3][2],
            m4x4[0][0] * other.m4x4[0][3] + m4x4[0][1] * other.m4x4[1][3] + m4x4[0][2] * other.m4x4[2][3] + m4x4[0][3] * other.m4x4[3][3],

            m4x4[1][0] * other.m4x4[0][0] + m4x4[1][1] * other.m4x4[1][0] + m4x4[1][2] * other.m4x4[2][0] + m4x4[1][3] * other.m4x4[3][0],
            m4x4[1][0] * other.m4x4[0][1] + m4x4[1][1] * other.m4x4[1][1] + m4x4[1][2] * other.m4x4[2][1] + m4x4[1][3] * other.m4x4[3][1],
            m4x4[1][0] * other.m4x4[0][2] + m4x4[1][1] * other.m4x4[1][2] + m4x4[1][2] * other.m4x4[2][2] + m4x4[1][3] * other.m4x4[3][2],
            m4x4[1][0] * other.m4x4[0][3] + m4x4[1][1] * other.m4x4[1][3] + m4x4[1][2] * other.m4x4[2][3] + m4x4[1][3] * other.m4x4[3][3],

            m4x4[2][0] * other.m4x4[0][0] + m4x4[2][1] * other.m4x4[1][0] + m4x4[2][2] * other.m4x4[2][0] + m4x4[2][3] * other.m4x4[3][0],
            m4x4[2][0] * other.m4x4[0][1] + m4x4[2][1] * other.m4x4[1][1] + m4x4[2][2] * other.m4x4[2][1] + m4x4[2][3] * other.m4x4[3][1],
            m4x4[2][0] * other.m4x4[0][2] + m4x4[2][1] * other.m4x4[1][2] + m4x4[2][2] * other.m4x4[2][2] + m4x4[2][3] * other.m4x4[3][2],
            m4x4[2][0] * other.m4x4[0][3] + m4x4[2][1] * other.m4x4[1][3] + m4x4[2][2] * other.m4x4[2][3] + m4x4[2][3] * other.m4x4[3][3],

            m4x4[3][0] * other.m4x4[0][0] + m4x4[3][1] * other.m4x4[1][0] + m4x4[3][2] * other.m4x4[2][0] + m4x4[3][3] * other.m4x4[3][0],
            m4x4[3][0] * other.m4x4[0][1] + m4x4[3][1] * other.m4x4[1][1] + m4x4[3][2] * other.m4x4[2][1] + m4x4[3][3] * other.m4x4[3][1],
            m4x4[3][0] * other.m4x4[0][2] + m4x4[3][1] * other.m4x4[1][2] + m4x4[3][2] * other.m4x4[2][2] + m4x4[3][3] * other.m4x4[3][2],
            m4x4[3][0] * other.m4x4[0][3] + m4x4[3][1] * other.m4x4[1][3] + m4x4[3][2] * other.m4x4[2][3] + m4x4[3][3] * other.m4x4[3][3]
            );
    }

    template <typename T>
    inline TMatrix4<T> TMatrix4<T>::operator *(T scalar) const
    {
        return TMatrix4(
            m4x4[0][0] * scalar, m4x4[0][1] * scalar, m4x4[0][2] * scalar, m4x4[0][3] * scalar,
            m4x4[1][0] * scalar, m4x4[1][1] * scalar, m4x4[1][2] * scalar, m4x4[1][3] * scalar,
            m4x4[2][0] * scalar, m4x4[2][1] * scalar, m4x4[2][2] * scalar, m4x4[2][3] * scalar,
            m4x4[3][0] * scalar, m4x4[3][1] * scalar, m4x4[3][2] * scalar, m4x4[3][3] * scalar
            );
    }

    template <typename T>
    inline TMatrix4<T> TMatrix4<T>::operator /(T scalar) const
    {
        T fInvertScalar = 0.0;
        if (scalar != TReal<T>::ZERO)
            fInvertScalar = TReal<T>::ONE / scalar;
        return TMatrix4(
            m4x4[0][0] * fInvertScalar, m4x4[0][1] * fInvertScalar, m4x4[0][2] * fInvertScalar, m4x4[0][3] * fInvertScalar,
            m4x4[1][0] * fInvertScalar, m4x4[1][1] * fInvertScalar, m4x4[1][2] * fInvertScalar, m4x4[1][3] * fInvertScalar,
            m4x4[2][0] * fInvertScalar, m4x4[2][1] * fInvertScalar, m4x4[2][2] * fInvertScalar, m4x4[2][3] * fInvertScalar,
            m4x4[3][0] * fInvertScalar, m4x4[3][1] * fInvertScalar, m4x4[3][2] * fInvertScalar, m4x4[3][3] * fInvertScalar
            );
    }

    template <typename T>
    inline TMatrix4<T> TMatrix4<T>::operator -() const
    {
        return TMatrix4(
            -m4x4[0][0], -m4x4[0][1], -m4x4[0][2], -m4x4[0][3],
            -m4x4[1][0], -m4x4[1][1], -m4x4[1][2], -m4x4[1][3],
            -m4x4[2][0], -m4x4[2][1], -m4x4[2][2], -m4x4[2][3],
            -m4x4[3][0], -m4x4[3][1], -m4x4[3][2], -m4x4[3][3]
            );
    }

    template <typename T>
    inline TMatrix4<T> &TMatrix4<T>::operator +=(const TMatrix4 &other)
    {
        m4x4[0][0] += other.m4x4[0][0];
        m4x4[0][1] += other.m4x4[0][1];
        m4x4[0][2] += other.m4x4[0][2];
        m4x4[0][3] += other.m4x4[0][3];

        m4x4[1][0] += other.m4x4[1][0];
        m4x4[1][1] += other.m4x4[1][1];
        m4x4[1][2] += other.m4x4[1][2];
        m4x4[1][3] += other.m4x4[1][3];

        m4x4[2][0] += other.m4x4[2][0];
        m4x4[2][1] += other.m4x4[2][1];
        m4x4[2][2] += other.m4x4[2][2];
        m4x4[2][3] += other.m4x4[2][3];

        m4x4[3][0] += other.m4x4[3][0];
        m4x4[3][1] += other.m4x4[3][1];
        m4x4[3][2] += other.m4x4[3][2];
        m4x4[3][3] += other.m4x4[3][3];

        return *this;
    }

    template <typename T>
    inline TMatrix4<T> &TMatrix4<T>::operator -=(const TMatrix4 &other)
    {
        m4x4[0][0] -= other.m4x4[0][0];
        m4x4[0][1] -= other.m4x4[0][1];
        m4x4[0][2] -= other.m4x4[0][2];
        m4x4[0][3] -= other.m4x4[0][3];

        m4x4[1][0] -= other.m4x4[1][0];
        m4x4[1][1] -= other.m4x4[1][1];
        m4x4[1][2] -= other.m4x4[1][2];
        m4x4[1][3] -= other.m4x4[1][3];

        m4x4[2][0] -= other.m4x4[2][0];
        m4x4[2][1] -= other.m4x4[2][1];
        m4x4[2][2] -= other.m4x4[2][2];
        m4x4[2][3] -= other.m4x4[2][3];

        m4x4[3][0] -= other.m4x4[3][0];
        m4x4[3][1] -= other.m4x4[3][1];
        m4x4[3][2] -= other.m4x4[3][2];
        m4x4[3][3] -= other.m4x4[3][3];

        return *this;
    }

    template <typename T>
    inline TMatrix4<T> &TMatrix4<T>::operator *=(T scalar)
    {
        m4x4[0][0] *= scalar, m4x4[0][1] *= scalar, m4x4[0][2] *= scalar, m4x4[0][3] *= scalar;
        m4x4[1][0] *= scalar, m4x4[1][1] *= scalar, m4x4[1][2] *= scalar, m4x4[1][3] *= scalar;
        m4x4[2][0] *= scalar, m4x4[2][1] *= scalar, m4x4[2][2] *= scalar, m4x4[2][3] *= scalar;
        m4x4[3][0] *= scalar, m4x4[3][1] *= scalar, m4x4[3][2] *= scalar, m4x4[3][3] *= scalar;

        return *this;
    }

    template <typename T>
    inline TMatrix4<T> &TMatrix4<T>::operator /=(T scalar)
    {
        T fInvertScalar = 0.0;
        if (scalar != TReal<T>::ZERO)
            fInvertScalar = TReal<T>::ONE / scalar;
        
        m4x4[0][0] *= fInvertScalar, m4x4[0][1] *= fInvertScalar, m4x4[0][2] *= fInvertScalar, m4x4[0][3] *= fInvertScalar;
        m4x4[1][0] *= fInvertScalar, m4x4[1][1] *= fInvertScalar, m4x4[1][2] *= fInvertScalar, m4x4[1][3] *= fInvertScalar;
        m4x4[2][0] *= fInvertScalar, m4x4[2][1] *= fInvertScalar, m4x4[2][2] *= fInvertScalar, m4x4[2][3] *= fInvertScalar;
        m4x4[3][0] *= fInvertScalar, m4x4[3][1] *= fInvertScalar, m4x4[3][2] *= fInvertScalar, m4x4[3][3] *= fInvertScalar;

        return *this;
    }

    template <typename T>
    inline TVector4<T> TMatrix4<T>::operator *(const TVector4<T> &rkV) const
    {
        return TVector4<T>(
            m4x4[0][0] * rkV.x() + m4x4[0][1] * rkV.y() + m4x4[0][2] * rkV.z() + m4x4[0][3] * rkV.w(), 
            m4x4[1][0] * rkV.x() + m4x4[1][1] * rkV.y() + m4x4[1][2] * rkV.z() + m4x4[1][3] * rkV.w(),
            m4x4[2][0] * rkV.x() + m4x4[2][1] * rkV.y() + m4x4[2][2] * rkV.z() + m4x4[2][3] * rkV.w(),
            m4x4[3][0] * rkV.x() + m4x4[3][1] * rkV.y() + m4x4[3][2] * rkV.z() + m4x4[3][3] * rkV.w()
            );
    }

    template <typename T>
    inline TVector3<T> TMatrix4<T>::operator *(const TVector3<T> &rkV) const
    {
        T w = m4x4[3][0] * rkV.x() + m4x4[3][1] * rkV.y() + m4x4[3][2] * rkV.z() + m4x4[3][3] * T(1.0);

        if (w != T(0.0))
        {
            return TVector3<T>(
                (m4x4[0][0] * rkV.x() + m4x4[0][1] * rkV.y() + m4x4[0][2] * rkV.z() + m4x4[0][3] * T(1.0)) / w, 
                (m4x4[1][0] * rkV.x() + m4x4[1][1] * rkV.y() + m4x4[1][2] * rkV.z() + m4x4[1][3] * T(1.0)) / w,
                (m4x4[2][0] * rkV.x() + m4x4[2][1] * rkV.y() + m4x4[2][2] * rkV.z() + m4x4[2][3] * T(1.0)) / w
                );
        }
        
        return TVector3<T>(
            m4x4[0][0] * rkV.x() + m4x4[0][1] * rkV.y() + m4x4[0][2] * rkV.z() + m4x4[0][3] * T(1.0),
            m4x4[1][0] * rkV.x() + m4x4[1][1] * rkV.y() + m4x4[1][2] * rkV.z() + m4x4[1][3] * T(1.0),
            m4x4[2][0] * rkV.x() + m4x4[2][1] * rkV.y() + m4x4[2][2] * rkV.z() + m4x4[2][3] * T(1.0)
            );
    }

    template <typename T>
    inline TMatrix4<T> TMatrix4<T>::transpose() const
    {
        return TMatrix4(
            m4x4[0][0], m4x4[1][0], m4x4[2][0], m4x4[3][0],
            m4x4[0][1], m4x4[1][1], m4x4[2][1], m4x4[3][1],
            m4x4[0][2], m4x4[1][2], m4x4[2][2], m4x4[3][2],
            m4x4[0][3], m4x4[1][3], m4x4[2][3], m4x4[3][3]
            );
    }

    template <typename T>
    inline bool TMatrix4<T>::isAffine() const
    {
        return m4x4[3][0] == TReal<T>::ZERO && m4x4[3][1] == TReal<T>::ZERO && m4x4[3][2] == TReal<T>::ZERO && m4x4[3][3] == TReal<T>::ONE;
    }

    template <typename T>
    inline bool TMatrix4<T>::hasScale() const
    {
        T t = m4x4[0][0] * m4x4[0][0] + m4x4[1][0] * m4x4[1][0] + m4x4[2][0] * m4x4[2][0];
        if (!TMath<T>::realEqual(t, TReal<T>::ONE, T(1e-04)))
            return true;
        t = m4x4[0][1] * m4x4[0][1] + m4x4[1][1] * m4x4[1][1] + m4x4[2][1] * m4x4[2][1];
        if (!TMath<T>::realEqual(t, TReal<T>::ONE, T(1e-04)))
            return true;
        t = m4x4[0][2] * m4x4[0][2] + m4x4[1][2] * m4x4[1][2] + m4x4[2][2] * m4x4[2][2];
        if (!TMath<T>::realEqual(t, TReal<T>::ONE, T(1e-04)))
            return true;

        return false;
    }

    template <typename T>
    inline TMatrix4<T> TMatrix4<T>::concatenateAffine(const TMatrix4 &other) const
    {
        T3D_ASSERT(isAffine() && other.isAffine());

        return TMatrix4(
            m4x4[0][0] * other.m4x4[0][0] + m4x4[0][1] * other.m4x4[1][0] + m4x4[0][2] * other.m4x4[2][0],
            m4x4[0][0] * other.m4x4[0][1] + m4x4[0][1] * other.m4x4[1][1] + m4x4[0][2] * other.m4x4[2][1],
            m4x4[0][0] * other.m4x4[0][2] + m4x4[0][1] * other.m4x4[1][2] + m4x4[0][2] * other.m4x4[2][2],
            m4x4[0][0] * other.m4x4[0][3] + m4x4[0][1] * other.m4x4[1][3] + m4x4[0][2] * other.m4x4[2][3] + m4x4[0][3],

            m4x4[1][0] * other.m4x4[0][0] + m4x4[1][1] * other.m4x4[1][0] + m4x4[1][2] * other.m4x4[2][0],
            m4x4[1][0] * other.m4x4[0][1] + m4x4[1][1] * other.m4x4[1][1] + m4x4[1][2] * other.m4x4[2][1],
            m4x4[1][0] * other.m4x4[0][2] + m4x4[1][1] * other.m4x4[1][2] + m4x4[1][2] * other.m4x4[2][2],
            m4x4[1][0] * other.m4x4[0][3] + m4x4[1][1] * other.m4x4[1][3] + m4x4[1][2] * other.m4x4[2][3] + m4x4[1][3],

            m4x4[2][0] * other.m4x4[0][0] + m4x4[2][1] * other.m4x4[1][0] + m4x4[2][2] * other.m4x4[2][0],
            m4x4[2][0] * other.m4x4[0][1] + m4x4[2][1] * other.m4x4[1][1] + m4x4[2][2] * other.m4x4[2][1],
            m4x4[2][0] * other.m4x4[0][2] + m4x4[2][1] * other.m4x4[1][2] + m4x4[2][2] * other.m4x4[2][2],
            m4x4[2][0] * other.m4x4[0][3] + m4x4[2][1] * other.m4x4[1][3] + m4x4[2][2] * other.m4x4[2][3] + m4x4[2][3],

            TReal<T>::ZERO, TReal<T>::ZERO, TReal<T>::ZERO, TReal<T>::ONE);
    }

    template <typename T>
    inline void TMatrix4<T>::extractMatrix(TMatrix3<T> &m3x3) const
    {
        m3x3[0][0] = m4x4[0][0];
        m3x3[0][1] = m4x4[0][1];
        m3x3[0][2] = m4x4[0][2];
        m3x3[1][0] = m4x4[1][0];
        m3x3[1][1] = m4x4[1][1];
        m3x3[1][2] = m4x4[1][2];
        m3x3[2][0] = m4x4[2][0];
        m3x3[2][1] = m4x4[2][1];
        m3x3[2][2] = m4x4[2][2];
    }

    template <typename T>
    inline TQuaternion<T> TMatrix4<T>::extractQuaternion() const
    {
        TMatrix3<T> m3x3;
        extractMatrix(m3x3);
        return TQuaternion<T>(m3x3);
    }

    template <typename T>
    inline TVector3<T> TMatrix4<T>::extractTranslation() const
    {
        return TVector3<T>(m4x4[0][3], m4x4[1][3], m4x4[2][3]);
    }

    template <typename T>
    inline void TMatrix4<T>::decomposition(TVector3<T> &position, TVector3<T> &scale, TQuaternion<T> &orientation) const
    {
        T3D_ASSERT(isAffine());

        TMatrix3<T> m3x3;
        extractMatrix(m3x3);

        TMatrix3<T> matQ;
        TVector3<T> vecU;
        m3x3.QDUDecomposition(matQ, scale, vecU); 

        orientation = TQuaternion<T>( matQ );
        position = TVector3<T>(m4x4[0][3], m4x4[1][3], m4x4[2][3]);
    }

    template <typename T>
    inline void TMatrix4<T>::makeTranslate(const TVector3<T> &position)
    {
        m4x4[0][0] = TReal<T>::ONE, m4x4[0][1] = TReal<T>::ZERO, m4x4[0][2] = TReal<T>::ZERO, m4x4[0][3] = position.x();
        m4x4[1][0] = TReal<T>::ZERO, m4x4[1][1] = TReal<T>::ONE, m4x4[1][2] = TReal<T>::ZERO, m4x4[1][3] = position.y();
        m4x4[2][0] = TReal<T>::ZERO, m4x4[2][1] = TReal<T>::ZERO, m4x4[2][2] = TReal<T>::ONE, m4x4[2][3] = position.z();
        m4x4[3][0] = TReal<T>::ZERO, m4x4[3][1] = TReal<T>::ZERO, m4x4[3][2] = TReal<T>::ZERO, m4x4[3][3] = TReal<T>::ONE;
    }

    template <typename T>
    inline void TMatrix4<T>::makeTranslate(T tx, T ty, T tz)
    {
        m4x4[0][0] = TReal<T>::ONE, m4x4[0][1] = TReal<T>::ZERO, m4x4[0][2] = TReal<T>::ZERO, m4x4[0][3] = tx;
        m4x4[1][0] = TReal<T>::ZERO, m4x4[1][1] = TReal<T>::ONE, m4x4[1][2] = TReal<T>::ZERO, m4x4[1][3] = ty;
        m4x4[2][0] = TReal<T>::ZERO, m4x4[2][1] = TReal<T>::ZERO, m4x4[2][2] = TReal<T>::ONE, m4x4[2][3] = tz;
        m4x4[3][0] = TReal<T>::ZERO, m4x4[3][1] = TReal<T>::ZERO, m4x4[3][2] = TReal<T>::ZERO, m4x4[3][3] = TReal<T>::ONE;
    }

    template <typename T>
    inline void TMatrix4<T>::setScale(const TVector3<T> &scale)
    {
        m4x4[0][0] = scale.x();
        m4x4[1][1] = scale.y();
        m4x4[2][2] = scale.z();
    }

    template <typename T>
    inline void TMatrix4<T>::setTranslate(const TVector3<T> &position)
    {
        m4x4[0][3] = position.x();
        m4x4[1][3] = position.y();
        m4x4[2][3] = position.z();
    }

    template <typename T>
    inline TVector3<T> TMatrix4<T>::transformAffine(const TVector3<T> &v) const
    {
        T3D_ASSERT(isAffine());

        return TVector3<T>(
            m4x4[0][0] * v.x() + m4x4[0][1] * v.y() + m4x4[0][2] * v.z() + m4x4[0][3], 
            m4x4[1][0] * v.x() + m4x4[1][1] * v.y() + m4x4[1][2] * v.z() + m4x4[1][3],
            m4x4[2][0] * v.x() + m4x4[2][1] * v.y() + m4x4[2][2] * v.z() + m4x4[2][3]);
    }

    template <typename T>
    inline TVector4<T> TMatrix4<T>::transformAffine(const TVector4<T> &v) const
    {
        T3D_ASSERT(isAffine());

        return TVector4<T>(
            m4x4[0][0] * v.x() + m4x4[0][1] * v.y() + m4x4[0][2] * v.z() + m4x4[0][3] * v.w(), 
            m4x4[1][0] * v.x() + m4x4[1][1] * v.y() + m4x4[1][2] * v.z() + m4x4[1][3] * v.w(),
            m4x4[2][0] * v.x() + m4x4[2][1] * v.y() + m4x4[2][2] * v.z() + m4x4[2][3] * v.w(),
            v.w());
    }

    template <typename T>
    inline TMatrix4<T> operator *(T scalar, const TMatrix4<T> &rkM)
    {
        return TMatrix4<T>(
            scalar * rkM[0][0], scalar * rkM[0][1], scalar * rkM[0][2], scalar * rkM[0][3],
            scalar * rkM[1][0], scalar * rkM[1][1], scalar * rkM[1][2], scalar * rkM[1][3],
            scalar * rkM[2][0], scalar * rkM[2][1], scalar * rkM[2][2], scalar * rkM[2][3],
            scalar * rkM[3][0], scalar * rkM[3][1], scalar * rkM[3][2], scalar * rkM[3][3]
            );
    }

    template <typename T>
    inline TVector4<T> operator *(const TVector4<T> &rkV, const TMatrix4<T> &rkM)
    {
        return TVector4<T>(
            rkV.x() * rkM[0][0] + rkV.y() * rkM[1][0] + rkV.z() * rkM[2][0] + rkV.w() * rkM[3][0],
            rkV.x() * rkM[0][1] + rkV.y() * rkM[1][1] + rkV.z() * rkM[2][1] + rkV.w() * rkM[3][1],
            rkV.x() * rkM[0][2] + rkV.y() * rkM[1][2] + rkV.z() * rkM[2][2] + rkV.w() * rkM[3][2],
            rkV.x() * rkM[0][3] + rkV.y() * rkM[1][3] + rkV.z() * rkM[2][3] + rkV.w() * rkM[3][3]
            );
    }

    template <typename T>
    const TMatrix4<T> TMatrix4<T>::ZERO(
        0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0);

    template <typename T>
    const TMatrix4<T> TMatrix4<T>::IDENTITY(
        1.0, 0.0, 0.0, 0.0,
        0.0, 1.0, 0.0, 0.0,
        0.0, 0.0, 1.0, 0.0,
        0.0, 0.0, 0.0, 1.0
    );

    template <typename T>
    inline static T MINOR(const TMatrix4<T>& m,
        const size_t r0, const size_t r1, const size_t r2,
        const size_t c0, const size_t c1, const size_t c2)
    {
        return m[r0][c0] * (m[r1][c1] * m[r2][c2] - m[r2][c1] * m[r1][c2]) -
            m[r0][c1] * (m[r1][c0] * m[r2][c2] - m[r2][c0] * m[r1][c2]) +
            m[r0][c2] * (m[r1][c0] * m[r2][c1] - m[r2][c0] * m[r1][c1]);
    }

    template <typename T>
    TMatrix4<T> TMatrix4<T>::inverse() const
    {
        T m00 = m4x4[0][0], m01 = m4x4[0][1], m02 = m4x4[0][2], m03 = m4x4[0][3];
        T m10 = m4x4[1][0], m11 = m4x4[1][1], m12 = m4x4[1][2], m13 = m4x4[1][3];
        T m20 = m4x4[2][0], m21 = m4x4[2][1], m22 = m4x4[2][2], m23 = m4x4[2][3];
        T m30 = m4x4[3][0], m31 = m4x4[3][1], m32 = m4x4[3][2], m33 = m4x4[3][3];

        T v0 = m20 * m31 - m21 * m30;
        T v1 = m20 * m32 - m22 * m30;
        T v2 = m20 * m33 - m23 * m30;
        T v3 = m21 * m32 - m22 * m31;
        T v4 = m21 * m33 - m23 * m31;
        T v5 = m22 * m33 - m23 * m32;

        T t00 = +(v5 * m11 - v4 * m12 + v3 * m13);
        T t10 = -(v5 * m10 - v2 * m12 + v1 * m13);
        T t20 = +(v4 * m10 - v2 * m11 + v0 * m13);
        T t30 = -(v3 * m10 - v1 * m11 + v0 * m12);

        T invDet = 1 / (t00 * m00 + t10 * m01 + t20 * m02 + t30 * m03);

        T d00 = t00 * invDet;
        T d10 = t10 * invDet;
        T d20 = t20 * invDet;
        T d30 = t30 * invDet;

        T d01 = -(v5 * m01 - v4 * m02 + v3 * m03) * invDet;
        T d11 = +(v5 * m00 - v2 * m02 + v1 * m03) * invDet;
        T d21 = -(v4 * m00 - v2 * m01 + v0 * m03) * invDet;
        T d31 = +(v3 * m00 - v1 * m01 + v0 * m02) * invDet;

        v0 = m10 * m31 - m11 * m30;
        v1 = m10 * m32 - m12 * m30;
        v2 = m10 * m33 - m13 * m30;
        v3 = m11 * m32 - m12 * m31;
        v4 = m11 * m33 - m13 * m31;
        v5 = m12 * m33 - m13 * m32;

        T d02 = +(v5 * m01 - v4 * m02 + v3 * m03) * invDet;
        T d12 = -(v5 * m00 - v2 * m02 + v1 * m03) * invDet;
        T d22 = +(v4 * m00 - v2 * m01 + v0 * m03) * invDet;
        T d32 = -(v3 * m00 - v1 * m01 + v0 * m02) * invDet;

        v0 = m21 * m10 - m20 * m11;
        v1 = m22 * m10 - m20 * m12;
        v2 = m23 * m10 - m20 * m13;
        v3 = m22 * m11 - m21 * m12;
        v4 = m23 * m11 - m21 * m13;
        v5 = m23 * m12 - m22 * m13;

        T d03 = -(v5 * m01 - v4 * m02 + v3 * m03) * invDet;
        T d13 = +(v5 * m00 - v2 * m02 + v1 * m03) * invDet;
        T d23 = -(v4 * m00 - v2 * m01 + v0 * m03) * invDet;
        T d33 = +(v3 * m00 - v1 * m01 + v0 * m02) * invDet;

        return TMatrix4(
            d00, d01, d02, d03,
            d10, d11, d12, d13,
            d20, d21, d22, d23,
            d30, d31, d32, d33);
    }

    template <typename T>
    TMatrix4<T> TMatrix4<T>::inverseAffine() const
    {
        T3D_ASSERT(isAffine());

        T m10 = m4x4[1][0], m11 = m4x4[1][1], m12 = m4x4[1][2];
        T m20 = m4x4[2][0], m21 = m4x4[2][1], m22 = m4x4[2][2];

        T t00 = m22 * m11 - m21 * m12;
        T t10 = m20 * m12 - m22 * m10;
        T t20 = m21 * m10 - m20 * m11;

        T m00 = m4x4[0][0], m01 = m4x4[0][1], m02 = m4x4[0][2];

        T invDet = 1 / (m00 * t00 + m01 * t10 + m02 * t20);

        t00 *= invDet;
        t10 *= invDet;
        t20 *= invDet;

        m00 *= invDet;
        m01 *= invDet;
        m02 *= invDet;

        T r00 = t00;
        T r01 = m02 * m21 - m01 * m22;
        T r02 = m01 * m12 - m02 * m11;

        T r10 = t10;
        T r11 = m00 * m22 - m02 * m20;
        T r12 = m02 * m10 - m00 * m12;

        T r20 = t20;
        T r21 = m01 * m20 - m00 * m21;
        T r22 = m00 * m11 - m01 * m10;

        T m03 = m4x4[0][3], m13 = m4x4[1][3], m23 = m4x4[2][3];

        T r03 = -(r00 * m03 + r01 * m13 + r02 * m23);
        T r13 = -(r10 * m03 + r11 * m13 + r12 * m23);
        T r23 = -(r20 * m03 + r21 * m13 + r22 * m23);

        return TMatrix4(
            r00, r01, r02, r03,
            r10, r11, r12, r13,
            r20, r21, r22, r23,
            0.0, 0.0, 0.0, 1.0);
    }

    //-----------------------------------------------------------------------
    template <typename T>
    TMatrix4<T> TMatrix4<T>::adjoint() const
    {
        return TMatrix4(MINOR(*this, 1, 2, 3, 1, 2, 3),
            -MINOR(*this, 0, 2, 3, 1, 2, 3),
            MINOR(*this, 0, 1, 3, 1, 2, 3),
            -MINOR(*this, 0, 1, 2, 1, 2, 3),

            -MINOR(*this, 1, 2, 3, 0, 2, 3),
            MINOR(*this, 0, 2, 3, 0, 2, 3),
            -MINOR(*this, 0, 1, 3, 0, 2, 3),
            MINOR(*this, 0, 1, 2, 0, 2, 3),

            MINOR(*this, 1, 2, 3, 0, 1, 3),
            -MINOR(*this, 0, 2, 3, 0, 1, 3),
            MINOR(*this, 0, 1, 3, 0, 1, 3),
            -MINOR(*this, 0, 1, 2, 0, 1, 3),

            -MINOR(*this, 1, 2, 3, 0, 1, 2),
            MINOR(*this, 0, 2, 3, 0, 1, 2),
            -MINOR(*this, 0, 1, 3, 0, 1, 2),
            MINOR(*this, 0, 1, 2, 0, 1, 2));
    }

    template <typename T>
    T TMatrix4<T>::determinant() const
    {
        return
            m4x4[0][0] * MINOR(*this, 1, 2, 3, 1, 2, 3) -
            m4x4[0][1] * MINOR(*this, 1, 2, 3, 0, 2, 3) +
            m4x4[0][2] * MINOR(*this, 1, 2, 3, 0, 1, 3) -
            m4x4[0][3] * MINOR(*this, 1, 2, 3, 0, 1, 2);
    }

    template <typename T>
    void TMatrix4<T>::makeTransform(const TVector3<T> &position, const TVector3<T> &scale, const TQuaternion<T> &orientation)
    {
        // Ordering:
        //    1. Scale
        //    2. Rotate
        //    3. Translate

        TMatrix3<T> rot3x3;
        orientation.toRotationMatrix(rot3x3);

        // Set up final matrix with scale, rotation and translation
        m4x4[0][0] = scale.x() * rot3x3[0][0];
        m4x4[0][1] = scale.y() * rot3x3[0][1];
        m4x4[0][2] = scale.z() * rot3x3[0][2];
        m4x4[0][3] = position.x();

        m4x4[1][0] = scale.x() * rot3x3[1][0];
        m4x4[1][1] = scale.y() * rot3x3[1][1];
        m4x4[1][2] = scale.z() * rot3x3[1][2];
        m4x4[1][3] = position.y();

        m4x4[2][0] = scale.x() * rot3x3[2][0];
        m4x4[2][1] = scale.y() * rot3x3[2][1];
        m4x4[2][2] = scale.z() * rot3x3[2][2];
        m4x4[2][3] = position.z();

        // No projection term
        m4x4[3][0] = TReal<T>::ZERO;
        m4x4[3][1] = TReal<T>::ZERO;
        m4x4[3][2] = TReal<T>::ZERO;
        m4x4[3][3] = TReal<T>::ONE;
    }

    template <typename T>
    void TMatrix4<T>::makeInverseTransform(const TVector3<T>& position, const TVector3<T>& scale, const TQuaternion<T>& orientation)
    {
        // Invert the parameters
        TVector3<T> invTranslate = -position;
        TVector3<T> invScale(1 / scale.x(), 1 / scale.y(), 1 / scale.z());
        TQuaternion<T> invRot = orientation.inverse();

        // Because we're inverting, order is translation, rotation, scale
        // So make translation relative to scale & rotation
        invTranslate = invRot * invTranslate; // rotate
        invTranslate *= invScale; // scale

                                  // Next, make a 3x3 rotation matrix
        TMatrix3<T> rot3x3;
        invRot.toRotationMatrix(rot3x3);

        // Set up final matrix with scale, rotation and translation
        m4x4[0][0] = invScale.x() * rot3x3[0][0];
        m4x4[0][1] = invScale.x() * rot3x3[0][1];
        m4x4[0][2] = invScale.x() * rot3x3[0][2];
        m4x4[0][3] = invTranslate.x();

        m4x4[1][0] = invScale.y() * rot3x3[1][0];
        m4x4[1][1] = invScale.y() * rot3x3[1][1];
        m4x4[1][2] = invScale.y() * rot3x3[1][2];
        m4x4[1][3] = invTranslate.y();

        m4x4[2][0] = invScale.z() * rot3x3[2][0];
        m4x4[2][1] = invScale.z() * rot3x3[2][1];
        m4x4[2][2] = invScale.z() * rot3x3[2][2];
        m4x4[2][3] = invTranslate.z();

        // No projection term
        m4x4[3][0] = TReal<T>::ZERO;
        m4x4[3][1] = TReal<T>::ZERO;
        m4x4[3][2] = TReal<T>::ZERO;
        m4x4[3][3] = TReal<T>::ONE;
    }
}
