

namespace Tiny3D
{
    template <typename T>
    inline void TMatrix3<T>::makeZero()
    {
        mTuples[0] = mTuples[1] = mTuples[2] = T(0.0);
        mTuples[3] = mTuples[4] = mTuples[5] = T(0.0);
        mTuples[6] = mTuples[7] = mTuples[8] = T(0.0);
    }

    template <typename T>
    inline void TMatrix3<T>::makeIdentity()
    {
        mTuples[0] = T(1.0), mTuples[1] = T(0.0), mTuples[2] = T(0.0);
        mTuples[3] = T(0.0), mTuples[4] = T(1.0), mTuples[5] = T(0.0);
        mTuples[6] = T(0.0), mTuples[7] = T(0.0), mTuples[8] = T(1.0);
    }

    template <typename T>
    inline void TMatrix3<T>::makeDiagonal(T m00, T m11, T m22)
    {
        mTuples[0] = m00, mTuples[1] = T(0.0), mTuples[2] = T(0.0);
        mTuples[3] = T(0.0), mTuples[4] = m11, mTuples[5] = T(0.0);
        mTuples[6] = T(0.0), mTuples[7] = T(0.0), mTuples[8] = m22;
    }

    template <typename T>
    inline void TMatrix3<T>::makeTensorProduct(const TVector3<T> &rkU, 
        const TVector3<T> &rkV)
    {
        mTuples[0] = rkU[0] * rkV[0];
        mTuples[1] = rkU[0] * rkV[1];
        mTuples[2] = rkU[0] * rkV[2];
        mTuples[3] = rkU[1] * rkV[0];
        mTuples[4] = rkU[1] * rkV[1];
        mTuples[5] = rkU[1] * rkV[2];
        mTuples[6] = rkU[2] * rkV[0];
        mTuples[7] = rkU[2] * rkV[1];
        mTuples[8] = rkU[2] * rkV[2];
    }

    template <typename T>
    inline void TMatrix3<T>::fromAxisAngle(const TVector3<T> &rkAxis, 
        const TRadian<T> &radians)
    {
        T fCos = TMath<T>::cos(radians);
        T fSin = TMath<T>::sin(radians);
        T fOneMinusCos = T(1.0) - fCos;
        T fX2 = rkAxis[0] * rkAxis[0];
        T fY2 = rkAxis[1] * rkAxis[1];
        T fZ2 = rkAxis[2] * rkAxis[2];
        T fXYM = rkAxis[0] * rkAxis[1] * fOneMinusCos;
        T fXZM = rkAxis[0] * rkAxis[2] * fOneMinusCos;
        T fYZM = rkAxis[1] * rkAxis[2] * fOneMinusCos;
        T fXSin = rkAxis[0] * fSin;
        T fYSin = rkAxis[1] * fSin;
        T fZSin = rkAxis[2] * fSin;

        mTuples[0] = fX2 * fOneMinusCos + fCos;
        mTuples[1] = fXYM - fZSin;
        mTuples[2] = fXZM + fYSin;
        mTuples[3] = fXYM + fZSin;
        mTuples[4] = fY2 * fOneMinusCos + fCos;
        mTuples[5] = fYZM - fXSin;
        mTuples[6] = fXZM - fYSin;
        mTuples[7] = fYZM + fXSin;
        mTuples[8] = fZ2 * fOneMinusCos + fCos;
    }

    template <typename T>
    inline TMatrix3<T>::TMatrix3(bool isZero /* = true */)
    {
        if (isZero)
        {
            makeZero();
        }
        else
        {
            makeIdentity();
        }
    }

    template <typename T>
    inline TMatrix3<T>::TMatrix3(const TMatrix3 &other)
    {
        memcpy(mTuples, other.mTuples, sizeof(mTuples));
    }

    template <typename T>
    inline TMatrix3<T>::TMatrix3(
        T m00, T m01, T m02, 
        T m10, T m11, T m12, 
        T m20, T m21, T m22)
    {
        mTuples[0] = m00;
        mTuples[1] = m01;
        mTuples[2] = m02;
        mTuples[3] = m10;
        mTuples[4] = m11;
        mTuples[5] = m12;
        mTuples[6] = m20;
        mTuples[7] = m21;
        mTuples[8] = m22;
    }

    template <typename T>
    inline TMatrix3<T>::TMatrix3(T tuples[9], bool isRowMajor)
    {
        if (isRowMajor)
        {
            memcpy(mTuples, tuples, sizeof(mTuples));
        }
        else
        {
            mTuples[0] = tuples[0];
            mTuples[1] = tuples[3];
            mTuples[2] = tuples[6];
            mTuples[3] = tuples[1];
            mTuples[4] = tuples[4];
            mTuples[5] = tuples[7];
            mTuples[6] = tuples[2];
            mTuples[7] = tuples[5];
            mTuples[8] = tuples[8];
        }
    }

    template <typename T>
    inline TMatrix3<T>::TMatrix3(const TVector3<T> &rkU, const TVector3<T> &rkV, 
        const TVector3<T> &rkW, bool isColumns)
    {
        if (isColumns)
        {
            mTuples[0] = rkU[0];
            mTuples[1] = rkV[0];
            mTuples[2] = rkW[0];
            mTuples[3] = rkU[1];
            mTuples[4] = rkV[1];
            mTuples[5] = rkW[1];
            mTuples[6] = rkU[2];
            mTuples[7] = rkV[2];
            mTuples[8] = rkW[2];
        }
        else
        {
            mTuples[0] = rkU[0];
            mTuples[1] = rkU[1];
            mTuples[2] = rkU[2];
            mTuples[3] = rkV[0];
            mTuples[4] = rkV[1];
            mTuples[5] = rkV[2];
            mTuples[6] = rkW[0];
            mTuples[7] = rkW[1];
            mTuples[8] = rkW[2];
        }
    }

    template <typename T>
    inline TMatrix3<T>::TMatrix3(const TVector3<T> *akV, bool isColumns)
    {
        if (isColumns)
        {
            mTuples[0] = akV[0][0];
            mTuples[1] = akV[1][0];
            mTuples[2] = akV[2][0];
            mTuples[3] = akV[0][1];
            mTuples[4] = akV[1][1];
            mTuples[5] = akV[2][1];
            mTuples[6] = akV[0][2];
            mTuples[7] = akV[1][2];
            mTuples[8] = akV[2][2];
        }
        else
        {
            mTuples[0] = akV[0][0];
            mTuples[1] = akV[0][1];
            mTuples[2] = akV[0][2];
            mTuples[3] = akV[1][0];
            mTuples[4] = akV[1][1];
            mTuples[5] = akV[1][2];
            mTuples[6] = akV[2][0];
            mTuples[7] = akV[2][1];
            mTuples[8] = akV[2][2];
        }
    }

    template <typename T>
    inline TMatrix3<T>::TMatrix3(T m00, T m11, T m22)
    {
        makeDiagonal(m00, m11, m22);
    }

    template <typename T>
    inline TMatrix3<T>::TMatrix3(const TVector3<T> &rkAxis, const TRadian<T> &rkRadians)
    {
        fromAxisAngle(rkAxis, rkRadians);
    }

    template <typename T>
    inline TMatrix3<T>::TMatrix3(const TVector3<T> &rkU, const TVector3<T> &rkV)
    {
        makeTensorProduct(rkU, rkV);
    }

    template <typename T>
    inline TMatrix3<T>::operator const T *() const
    {
        return mTuples;
    }

    template <typename T>
    inline TMatrix3<T>::operator T *()
    {
        return mTuples;
    }

    template <typename T>
    inline const T *TMatrix3<T>::operator [](size_t nRow) const
    {
        T3D_ASSERT(nRow >= 0 && nRow < 3);
        return &mTuples[nRow * 3];
    }

    template <typename T>
    inline T *TMatrix3<T>::operator [](size_t nRow)
    {
        T3D_ASSERT(nRow < 3);
        return &mTuples[nRow * 3];
    }

    template <typename T>
    inline T TMatrix3<T>::operator ()(size_t nRow, size_t nCol) const
    {
        T3D_ASSERT(nRow < 3 && nCol < 3);
        return mTuples[nRow * 3 + nCol];
    }

    template <typename T>
    inline T &TMatrix3<T>::operator ()(size_t nRow, size_t nCol)
    {
        T3D_ASSERT(nRow < 3 && nCol < 3);
        return mTuples[nRow * 3 + nCol];
    }

    template <typename T>
    inline void TMatrix3<T>::setRow(size_t nRow, const TVector3<T> &rkV)
    {
        T3D_ASSERT(nRow < 3);
        int32_t i = nRow * 3;
        mTuples[i] = rkV[0];
        mTuples[i+1] = rkV[1];
        mTuples[i+2] = rkV[2];
    }

    template <typename T>
    inline TVector3<T> TMatrix3<T>::getRow(size_t nRow) const
    {
        T3D_ASSERT(nRow < 3);
        int32_t i = nRow * 3;
        return TVector3<T>(mTuples[i], mTuples[i+1], mTuples[i+2]);
    }

    template <typename T>
    inline void TMatrix3<T>::setColumn(size_t nCol, const TVector3<T> &rkV)
    {
        T3D_ASSERT(nCol < 3);
        mTuples[nCol] = rkV[0];
        mTuples[nCol+3] = rkV[1];
        mTuples[nCol+6] = rkV[2];
    }

    template <typename T>
    inline TVector3<T> TMatrix3<T>::getColumn(size_t nCol) const
    {
        T3D_ASSERT(nCol >= 0 && nCol < 3);
        return TVector3<T>(mTuples[nCol], mTuples[nCol+3], mTuples[nCol+6]);
    }

    template <typename T>
    inline void TMatrix3<T>::getColumnMajor(T *afColumns) const
    {
        afColumns[0] = mTuples[0];
        afColumns[1] = mTuples[3];
        afColumns[2] = mTuples[6];
        afColumns[3] = mTuples[1];
        afColumns[4] = mTuples[4];
        afColumns[5] = mTuples[7];
        afColumns[6] = mTuples[2];
        afColumns[7] = mTuples[5];
        afColumns[8] = mTuples[8];
    }

    template <typename T>
    inline TMatrix3<T> &TMatrix3<T>::operator =(const TMatrix3 &other)
    {
        memcpy(mTuples, other.mTuples, sizeof(mTuples));
        return *this;
    }

    template <typename T>
    inline int32_t TMatrix3<T>::compareArrays(const TMatrix3 &other) const
    {
        return memcmp(mTuples, other.mTuples, sizeof(mTuples));
    }

    template <typename T>
    inline bool TMatrix3<T>::operator ==(const TMatrix3 &other) const
    {
        return (compareArrays(other) == 0);
    }

    template <typename T>
    inline bool TMatrix3<T>::operator !=(const TMatrix3 &other) const
    {
        return (compareArrays(other) != 0);
    }

    template <typename T>
    inline bool TMatrix3<T>::operator <(const TMatrix3 &other) const
    {
        return (compareArrays(other) < 0);
    }

    template <typename T>
    inline bool TMatrix3<T>::operator <=(const TMatrix3 &other) const
    {
        return (compareArrays(other) <= 0);
    }

    template <typename T>
    inline bool TMatrix3<T>::operator >(const TMatrix3 &other) const
    {
        return (compareArrays(other) > 0);
    }

    template <typename T>
    inline bool TMatrix3<T>::operator >=(const TMatrix3 &other) const
    {
        return (compareArrays(other) >= 0);
    }

    template <typename T>
    inline TMatrix3<T> TMatrix3<T>::operator +(const TMatrix3 &other) const
    {
        return TMatrix3(
            mTuples[0] + other.mTuples[0],
            mTuples[1] + other.mTuples[1],
            mTuples[2] + other.mTuples[2],
            mTuples[3] + other.mTuples[3],
            mTuples[4] + other.mTuples[4],
            mTuples[5] + other.mTuples[5],
            mTuples[6] + other.mTuples[6],
            mTuples[7] + other.mTuples[7],
            mTuples[8] + other.mTuples[8]);
    }

    template <typename T>
    inline TMatrix3<T> TMatrix3<T>::operator -(const TMatrix3 &other) const
    {
        return TMatrix3(
            mTuples[0] - other.mTuples[0],
            mTuples[1] - other.mTuples[1],
            mTuples[2] - other.mTuples[2],
            mTuples[3] - other.mTuples[3],
            mTuples[4] - other.mTuples[4],
            mTuples[5] - other.mTuples[5],
            mTuples[6] - other.mTuples[6],
            mTuples[7] - other.mTuples[7],
            mTuples[8] - other.mTuples[8]);
    }

    template <typename T>
    inline TMatrix3<T> TMatrix3<T>::operator *(const TMatrix3 &other) const
    {
        return TMatrix3(
            mTuples[0] * other.mTuples[0] + mTuples[1] * other.mTuples[3] + mTuples[2] * other.mTuples[6],
            mTuples[0] * other.mTuples[1] + mTuples[1] * other.mTuples[4] + mTuples[2] * other.mTuples[7],
            mTuples[0] * other.mTuples[2] + mTuples[1] * other.mTuples[5] + mTuples[2] * other.mTuples[8],
            mTuples[3] * other.mTuples[0] + mTuples[4] * other.mTuples[3] + mTuples[5] * other.mTuples[6],
            mTuples[3] * other.mTuples[1] + mTuples[4] * other.mTuples[4] + mTuples[5] * other.mTuples[7],
            mTuples[3] * other.mTuples[2] + mTuples[4] * other.mTuples[5] + mTuples[5] * other.mTuples[8],
            mTuples[6] * other.mTuples[0] + mTuples[7] * other.mTuples[3] + mTuples[8] * other.mTuples[6],
            mTuples[6] * other.mTuples[1] + mTuples[7] * other.mTuples[4] + mTuples[8] * other.mTuples[7],
            mTuples[6] * other.mTuples[2] + mTuples[7] * other.mTuples[5] + mTuples[8] * other.mTuples[8]
            );
    }

    template <typename T>
    inline TMatrix3<T> TMatrix3<T>::operator *(T scalar) const
    {
        return TMatrix3(
            mTuples[0] * scalar, mTuples[1] * scalar, mTuples[2] * scalar,
            mTuples[3] * scalar, mTuples[4] * scalar, mTuples[5] * scalar,
            mTuples[6] * scalar, mTuples[7] * scalar, mTuples[8] * scalar);
    }

    template <typename T>
    inline TMatrix3<T> TMatrix3<T>::operator /(T scalar) const
    {
        if (scalar != TReal<T>::ZERO)
            return TMatrix3(
                mTuples[0] / scalar, mTuples[1] / scalar, mTuples[2] / scalar, 
                mTuples[3] / scalar, mTuples[4] / scalar, mTuples[5] / scalar,
                mTuples[6] / scalar, mTuples[7] / scalar, mTuples[8] / scalar);
        return ZERO;
    }

    template <typename T>
    inline TMatrix3<T> TMatrix3<T>::operator -() const
    {
        return TMatrix3(
            -mTuples[0], -mTuples[1], -mTuples[2],
            -mTuples[3], -mTuples[4], -mTuples[5],
            -mTuples[6], -mTuples[7], -mTuples[8]);
    }

    template <typename T>
    inline TMatrix3<T> &TMatrix3<T>::operator +=(const TMatrix3 &other)
    {
        mTuples[0] += other.mTuples[0];
        mTuples[1] += other.mTuples[1];
        mTuples[2] += other.mTuples[2];
        mTuples[3] += other.mTuples[3];
        mTuples[4] += other.mTuples[4];
        mTuples[5] += other.mTuples[5];
        mTuples[6] += other.mTuples[6];
        mTuples[7] += other.mTuples[7];
        mTuples[8] += other.mTuples[8];
        return *this;
    }

    template <typename T>
    inline TMatrix3<T> &TMatrix3<T>::operator -=(const TMatrix3 &other)
    {
        mTuples[0] -= other.mTuples[0];
        mTuples[1] -= other.mTuples[1];
        mTuples[2] -= other.mTuples[2];
        mTuples[3] -= other.mTuples[3];
        mTuples[4] -= other.mTuples[4];
        mTuples[5] -= other.mTuples[5];
        mTuples[6] -= other.mTuples[6];
        mTuples[7] -= other.mTuples[7];
        mTuples[8] -= other.mTuples[8];
        return *this;
    }

    template <typename T>
    inline TMatrix3<T> &TMatrix3<T>::operator *=(T scalar)
    {
        mTuples[0] *= scalar;
        mTuples[1] *= scalar;
        mTuples[2] *= scalar;
        mTuples[3] *= scalar;
        mTuples[4] *= scalar;
        mTuples[5] *= scalar;
        mTuples[6] *= scalar;
        mTuples[7] *= scalar;
        mTuples[8] *= scalar;
        return *this;
    }

    template <typename T>
    inline TMatrix3<T> &TMatrix3<T>::operator /=(T scalar)
    {
        if (scalar != TReal<T>::ZERO)
        {
            mTuples[0] /= scalar;
            mTuples[1] /= scalar;
            mTuples[2] /= scalar;
            mTuples[3] /= scalar;
            mTuples[4] /= scalar;
            mTuples[5] /= scalar;
            mTuples[6] /= scalar;
            mTuples[7] /= scalar;
            mTuples[8] /= scalar;
        }
        else
        {
            makeZero();
        }
        return *this;
    }

    template <typename T>
    inline TVector3<T> TMatrix3<T>::operator *(const TVector3<T> &rkV) const
    {
        return TVector3<T>(
            mTuples[0] * rkV[0] + mTuples[1] * rkV[1] + mTuples[2] * rkV[2], 
            mTuples[3] * rkV[0] + mTuples[4] * rkV[1] + mTuples[5] * rkV[2],
            mTuples[6] * rkV[0] + mTuples[7] * rkV[1] + mTuples[8] * rkV[2]);
    }

    template <typename T>
    inline TMatrix3<T> TMatrix3<T>::transpose() const
    {
        return TMatrix3(
            mTuples[0], mTuples[3], mTuples[6],
            mTuples[1], mTuples[4], mTuples[7],
            mTuples[2], mTuples[5], mTuples[8]);
    }

    template <typename T>
    inline TMatrix3<T> TMatrix3<T>::transposeTimes(const TMatrix3 &other) const
    {
        return TMatrix3(
            mTuples[0] * other.mTuples[0] + mTuples[3] * other.mTuples[3] + mTuples[6] * other.mTuples[6], 
            mTuples[0] * other.mTuples[1] + mTuples[3] * other.mTuples[4] + mTuples[6] * other.mTuples[7], 
            mTuples[0] * other.mTuples[2] + mTuples[3] * other.mTuples[5] + mTuples[6] * other.mTuples[8], 
            mTuples[1] * other.mTuples[0] + mTuples[4] * other.mTuples[3] + mTuples[7] * other.mTuples[6], 
            mTuples[1] * other.mTuples[1] + mTuples[4] * other.mTuples[4] + mTuples[7] * other.mTuples[7], 
            mTuples[1] * other.mTuples[2] + mTuples[4] * other.mTuples[5] + mTuples[7] * other.mTuples[8], 
            mTuples[2] * other.mTuples[0] + mTuples[5] * other.mTuples[3] + mTuples[8] * other.mTuples[6], 
            mTuples[2] * other.mTuples[1] + mTuples[5] * other.mTuples[4] + mTuples[8] * other.mTuples[7], 
            mTuples[2] * other.mTuples[2] + mTuples[5] * other.mTuples[5] + mTuples[8] * other.mTuples[8]);
    }

    template <typename T>
    inline TMatrix3<T> TMatrix3<T>::timesTranspose(const TMatrix3 &other) const
    {
        return TMatrix3(
            mTuples[0] * other.mTuples[0] + mTuples[1] * other.mTuples[1] + mTuples[2] * other.mTuples[2],
            mTuples[0] * other.mTuples[3] + mTuples[1] * other.mTuples[4] + mTuples[2] * other.mTuples[5],
            mTuples[0] * other.mTuples[6] + mTuples[1] * other.mTuples[7] + mTuples[2] * other.mTuples[8],
            mTuples[3] * other.mTuples[0] + mTuples[4] * other.mTuples[1] + mTuples[5] * other.mTuples[2],
            mTuples[3] * other.mTuples[3] + mTuples[4] * other.mTuples[4] + mTuples[5] * other.mTuples[5],
            mTuples[3] * other.mTuples[6] + mTuples[4] * other.mTuples[7] + mTuples[5] * other.mTuples[8],
            mTuples[6] * other.mTuples[0] + mTuples[7] * other.mTuples[1] + mTuples[8] * other.mTuples[2],
            mTuples[6] * other.mTuples[3] + mTuples[7] * other.mTuples[4] + mTuples[8] * other.mTuples[5],
            mTuples[6] * other.mTuples[6] + mTuples[7] * other.mTuples[7] + mTuples[8] * other.mTuples[8]);
    }

    template <typename T>
    inline TMatrix3<T> TMatrix3<T>::inverse() const
    {
        TMatrix3 matInverse;

        T sum, value;
        value = mTuples[4] * mTuples[8];
        sum = value;
        value = mTuples[5] * mTuples[7];
        sum -= value;
        matInverse[0][0] = sum;

        value = mTuples[2] * mTuples[7];
        sum = value;
        value = mTuples[1] * mTuples[8];
        sum -= value;
        matInverse[0][1] = sum;

        value = mTuples[1] * mTuples[5];
        sum = value;
        value = mTuples[2] * mTuples[4];
        sum -= value;
        matInverse[0][2] = sum;

        value = mTuples[5] * mTuples[6];
        sum = value;
        value = mTuples[3] * mTuples[8];
        sum -= value;
        matInverse[1][0] = sum;

        value = mTuples[0] * mTuples[8];
        sum = value;
        value = mTuples[2] * mTuples[6];
        sum -= value;
        matInverse[1][1] = sum;

        value = mTuples[2] * mTuples[3];
        sum = value;
        value = mTuples[0] * mTuples[5];
        sum -= value;
        matInverse[1][2] = sum;

        value = mTuples[3] * mTuples[7];
        sum = value;
        value = mTuples[4] * mTuples[6];
        sum -= value;
        matInverse[2][0] = sum;

        value = mTuples[1] * mTuples[6];
        sum = value;
        value = mTuples[0] * mTuples[7];
        sum -= value;
        matInverse[2][1] = sum;

        value = mTuples[0] * mTuples[4];
        sum = value;
        value = mTuples[1] * mTuples[3];
        sum -= value;
        matInverse[2][2] = sum;

        value = mTuples[0] * matInverse[0][0];
        sum = value;
        value = mTuples[1] * matInverse[1][0];
        sum += value;
        value = mTuples[2] * matInverse[2][0];
        sum += value;

        if (TMath<T>::abs(sum) == TReal<T>::ZERO)
            return ZERO;

        matInverse /= sum;

        return matInverse;
    }

    template <typename T>
    inline T TMatrix3<T>::determinant() const
    {
        // This 3x3 matrix : 
        //        +-        -+
        //    A = | A0 A1 A2 |
        //        | A3 A4 A5 |
        //        | A6 A7 A8 |
        //        +-        -+
        // 
        // det(A) = A0 * A4 * A8 + A1 * A5 * A6 + A2 * A3 * A7 - A2 * A4 * A6 - A1 * A3 * A8 - A0 * A5 * A7
        // equal to
        // det(A) = A0 * (A4 * A8 - A5 * A7) + A1 * (A5 * A6 - A3 * A8) + A2 * (A3 * A7 - A4 * A6)

        T fCofactor00 = mTuples[4] * mTuples[8] - mTuples[5] * mTuples[7];
        T fCofactor01 = mTuples[5] * mTuples[6] - mTuples[3] * mTuples[8];
        T fCofactor02 = mTuples[3] * mTuples[7] - mTuples[4] * mTuples[6];

        return mTuples[0] * fCofactor00 + mTuples[1] * fCofactor01 + mTuples[2] * fCofactor02;
    }

    template <typename T>
    inline T TMatrix3<T>::qform(const TVector3<T> &rkU, const TVector3<T> &rkV) const
    {
        return rkU.dot((*this) * rkV);
    }

    template <typename T>
    inline TMatrix3<T> TMatrix3<T>::timesDiagonal(const TVector3<T> &rkDiag) const
    {
        return TMatrix3(
            mTuples[0] * rkDiag[0], mTuples[1] * rkDiag[1], mTuples[2] * rkDiag[2],
            mTuples[3] * rkDiag[0], mTuples[4] * rkDiag[1], mTuples[5] * rkDiag[2],
            mTuples[6] * rkDiag[0], mTuples[7] * rkDiag[1], mTuples[8] * rkDiag[2]);
    }

    template <typename T>
    inline TMatrix3<T> TMatrix3<T>::diagonalTimes(const TVector3<T> &rkDiag) const
    {
        return TMatrix3(
            rkDiag[0] * mTuples[0], rkDiag[0] * mTuples[1], rkDiag[0] * mTuples[2],
            rkDiag[1] * mTuples[3], rkDiag[1] * mTuples[4], rkDiag[1] * mTuples[5],
            rkDiag[2] * mTuples[6], rkDiag[2] * mTuples[7], rkDiag[2] * mTuples[8]);
    }

    template <typename T>
    inline void TMatrix3<T>::fromEulerAnglesXYZ(const TRadian<T> &rkPitch, const TRadian<T> &rkYaw, const TRadian<T> &rkRoll)
    {
        T fCos, fSin;

        fCos = TMath<T>::cos(rkPitch);
        fSin = TMath<T>::sin(rkPitch);
        TMatrix3 matX(
            1.0, 0.0, 0.0, 
            0.0, fCos, -fSin, 
            0.0, fSin, fCos);

        fCos = TMath<T>::cos(rkYaw);
        fSin = TMath<T>::sin(rkYaw);
        TMatrix3 matY(
            fCos, 0.0, fSin, 
            0.0, 1.0, 0.0, 
            -fSin, 0.0, fCos);

        fCos = TMath<T>::cos(rkRoll);
        fSin = TMath<T>::sin(rkRoll);
        TMatrix3 matZ(
            fCos, -fSin, 0.0, 
            fSin, fCos, 0.0, 
            0.0, 0.0, 1.0);

        *this = matX * (matY * matZ);
    }

    template <typename T>
    inline void TMatrix3<T>::fromEulerAnglesXZY(const TRadian<T> &rkPitch, const TRadian<T> &rkRoll, const TRadian<T> &rkYaw)
    {
        T fCos, fSin;

        fCos = TMath<T>::cos(rkPitch);
        fSin = TMath<T>::sin(rkPitch);
        TMatrix3 matX(
            1.0, 0.0, 0.0,
            0.0, fCos, -fSin,
            0.0, fSin, fCos);

        fCos = TMath<T>::cos(rkRoll);
        fSin = TMath<T>::sin(rkRoll);
        TMatrix3 matZ(
            fCos, -fSin, 0.0,
            fSin, fCos, 0.0,
            0.0, 0.0, 1.0);

        fCos = TMath<T>::cos(rkYaw);
        fSin = TMath<T>::sin(rkYaw);
        TMatrix3 matY(
            fCos, 0.0, fSin,
            0.0, 1.0, 0.0,
            -fSin, 0.0, fCos);

        *this = matX * (matZ * matY);
    }

    template <typename T>
    inline void TMatrix3<T>::fromEulerAnglesYXZ(const TRadian<T> &rkYaw, const TRadian<T> &rkPitch, const TRadian<T> &rkRoll)
    {
        T fCos, fSin;

        fCos = TMath<T>::cos(rkYaw);
        fSin = TMath<T>::sin(rkYaw);
        TMatrix3 matY(
            fCos, 0.0, fSin,
            0.0, 1.0, 0.0,
            -fSin, 0.0, fCos);

        fCos = TMath<T>::cos(rkPitch);
        fSin = TMath<T>::sin(rkPitch);
        TMatrix3 matX(
            1.0, 0.0, 0.0,
            0.0, fCos, -fSin,
            0.0, fSin, fCos);

        fCos = TMath<T>::cos(rkRoll);
        fSin = TMath<T>::sin(rkRoll);
        TMatrix3 matZ(
            fCos, -fSin, 0.0,
            fSin, fCos, 0.0,
            0.0, 0.0, 1.0);

        *this = matY * (matX * matZ);
    }

    template <typename T>
    inline void TMatrix3<T>::fromEulerAnglesYZX(const TRadian<T> &rkYaw, const TRadian<T> &rkRoll, const TRadian<T> &rkPitch)
    {
        T fCos, fSin;

        fCos = TMath<T>::cos(rkYaw);
        fSin = TMath<T>::sin(rkYaw);
        TMatrix3 matY(
            fCos, 0.0, fSin,
            0.0, 1.0, 0.0,
            -fSin, 0.0, fCos);

        fCos = TMath<T>::cos(rkRoll);
        fSin = TMath<T>::sin(rkRoll);
        TMatrix3 matZ(
            fCos, -fSin, 0.0,
            fSin, fCos, 0.0,
            0.0, 0.0, 1.0);

        fCos = TMath<T>::cos(rkPitch);
        fSin = TMath<T>::sin(rkPitch);
        TMatrix3 matX(
            1.0, 0.0, 0.0,
            0.0, fCos, -fSin,
            0.0, fSin, fCos);

        *this = matY * (matZ * matX);
    }

    template <typename T>
    inline void TMatrix3<T>::fromEulerAnglesZXY(const TRadian<T> &rkRoll, const TRadian<T> &rkPitch, const TRadian<T> &rkYaw)
    {
        T fCos, fSin;

        fCos = TMath<T>::cos(rkRoll);
        fSin = TMath<T>::sin(rkRoll);
        TMatrix3 matZ(
            fCos, -fSin, 0.0,
            fSin, fCos, 0.0,
            0.0, 0.0, 1.0);

        fCos = TMath<T>::cos(rkPitch);
        fSin = TMath<T>::sin(rkPitch);
        TMatrix3 matX(
            1.0, 0.0, 0.0,
            0.0, fCos, -fSin,
            0.0, fSin, fCos);

        fCos = TMath<T>::cos(rkYaw);
        fSin = TMath<T>::sin(rkYaw);
        TMatrix3 matY(
            fCos, 0.0, fSin,
            0.0, 1.0, 0.0,
            -fSin, 0.0, fCos);

        *this = matZ * (matX * matY);
    }

    template <typename T>
    inline void TMatrix3<T>::fromEulerAnglesZYX(const TRadian<T> &rkRoll, const TRadian<T> &rkYaw, const TRadian<T> &rkPitch)
    {
        T fCos, fSin;

        fCos = TMath<T>::cos(rkRoll);
        fSin = TMath<T>::sin(rkRoll);
        TMatrix3 matZ(
            fCos, -fSin, 0.0,
            fSin, fCos, 0.0,
            0.0, 0.0, 1.0);

        fCos = TMath<T>::cos(rkYaw);
        fSin = TMath<T>::sin(rkYaw);
        TMatrix3 matY(
            fCos, 0.0, fSin,
            0.0, 1.0, 0.0,
            -fSin, 0.0, fCos);

        fCos = TMath<T>::cos(rkPitch);
        fSin = TMath<T>::sin(rkPitch);
        TMatrix3 matX(
            1.0, 0.0, 0.0,
            0.0, fCos, -fSin,
            0.0, fSin, fCos);

        *this = matZ * (matY * matX);
    }

    template <typename T>
    inline TMatrix3<T> operator *(T scalar, const TMatrix3<T> &rkM)
    {
        return rkM * scalar;
    }

    template <typename T>
    inline TVector3<T> operator *(const TVector3<T> &rkV, const TMatrix3<T> &rkM)
    {
        return TVector3<T>(
            rkV[0] * rkM[0][0] + rkV[1] * rkM[1][0] + rkV[2] * rkM[2][0], 
            rkV[0] * rkM[0][1] + rkV[1] * rkM[1][1] + rkV[2] * rkM[2][1],
            rkV[0] * rkM[0][2] + rkV[1] * rkM[1][2] + rkV[2] * rkM[2][2]);
    }

    template <typename T>
    const TMatrix3<T> TMatrix3<T>::ZERO(
        T(0.0), T(0.0), T(0.0),
        T(0.0), T(0.0), T(0.0),
        T(0.0), T(0.0), T(0.0));

    template <typename T>
    const TMatrix3<T> TMatrix3<T>::IDENTITY(
        T(1.0), T(0.0), T(0.0),
        T(0.0), T(1.0), T(0.0),
        T(0.0), T(0.0), T(1.0));

    template <typename T>
    void TMatrix3<T>::toAxisAngle(TVector3<T> &rAxis, TRadian<T> &rRadians) const
    {
        // Let (x,y,z) be the unit-length axis and let A be an angle of rotation.
        // The rotation matrix is R = I + sin(A)*P + (1-cos(A))*P^2 where
        // I is the identity and
        //
        //       +-        -+
        //   P = |  0 -z +y |
        //       | +z  0 -x |
        //       | -y +x  0 |
        //       +-        -+
        //
        // If A > 0, R represents a counterclockwise rotation about the axis in
        // the sense of looking from the tip of the axis vector towards the
        // origin.  Some algebra will show that
        //
        //   cos(A) = (trace(R)-1)/2  and  R - R^t = 2*sin(A)*P
        //
        // In the event that A = pi, R-R^t = 0 which prevents us from extracting
        // the axis through P.  Instead note that R = I+2*P^2 when A = pi, so
        // P^2 = (R-I)/2.  The diagonal entries of P^2 are x^2-1, y^2-1, and
        // z^2-1.  We can solve these for axis (x,y,z).  Because the angle is pi,
        // it does not matter which sign you choose on the square roots.

        T fTrace = mTuples[0] + mTuples[4] + mTuples[8];
        T fCos = 0.5f * (fTrace - 1.0f);
        rRadians = TMath<T>::acos(fCos);  // in [0,PI]

        if (rRadians > TRadian<T>(0.0))
        {
            if (rRadians < TRadian<T>(TMath<T>::PI))
            {
                rAxis.x() = mTuples[7] - mTuples[5];
                rAxis.y() = mTuples[2] - mTuples[6];
                rAxis.z() = mTuples[3] - mTuples[1];
                rAxis.normalize();
            }
            else
            {
                // angle is PI
                float fHalfInverse;
                if (mTuples[0] >= mTuples[4])
                {
                    // r00 >= r11
                    if (mTuples[0] >= mTuples[8])
                    {
                        // r00 is maximum diagonal term
                        rAxis.x() = 0.5f * TMath<T>::sqrt(mTuples[0] - mTuples[4]
                            - mTuples[8] + 1.0f);
                        fHalfInverse = 0.5f / rAxis.x();
                        rAxis.y() = fHalfInverse * mTuples[1];
                        rAxis.z() = fHalfInverse * mTuples[2];
                    }
                    else
                    {
                        // r22 is maximum diagonal term
                        rAxis.z() = 0.5f * TMath<T>::sqrt(mTuples[8] - mTuples[0]
                            - mTuples[4] + 1.0f);
                        fHalfInverse = 0.5f / rAxis.z();
                        rAxis.x() = fHalfInverse * mTuples[2];
                        rAxis.y() = fHalfInverse * mTuples[5];
                    }
                }
                else
                {
                    // r11 > r00
                    if (mTuples[4] >= mTuples[8])
                    {
                        // r11 is maximum diagonal term
                        rAxis.y() = 0.5f * TMath<T>::sqrt(mTuples[4] - mTuples[0]
                            - mTuples[8] + 1.0f);
                        fHalfInverse = 0.5f / rAxis.y();
                        rAxis.x() = fHalfInverse * mTuples[1];
                        rAxis.z() = fHalfInverse * mTuples[5];
                    }
                    else
                    {
                        // r22 is maximum diagonal term
                        rAxis.z() = 0.5f * TMath<T>::sqrt(mTuples[8] - mTuples[0]
                            - mTuples[4] + 1.0f);
                        fHalfInverse = 0.5f / rAxis.z();
                        rAxis.x() = fHalfInverse * mTuples[2];
                        rAxis.y() = fHalfInverse * mTuples[5];
                    }
                }
            }
        }
        else
        {
            // The angle is 0 and the matrix is the identity.  Any axis will
            // work, so just use the x-axis.
            rAxis.x() = 1.0f;
            rAxis.y() = TReal<T>::ZERO;
            rAxis.z() = TReal<T>::ZERO;
        }
    }

    template <typename T>
    TMatrix3<T> TMatrix3<T>::adjoint() const
    {
        // This 3x3 matrix :
        //          +-        -+
        //          | A0 A1 A2 |
        //      A = | A3 A4 A5 |
        //          | A6 A7 A8 |
        //          +-        -+
        //
        // The adjoint of this 3x3 matrix :
        //
        //          +-                                  -+
        //          |  | A4 A5 |   | A1 A2 |   | A1 A2 | |
        //          | +| A7 A8 |  -| A7 A8 |  +| A4 A5 | |
        //          |                                    |
        // adj(A) = |  | A3 A5 |   | A0 A2 |   | A0 A2 | |
        //          | -| A6 A8 |  +| A6 A8 |  -| A3 A5 | |
        //          |                                    |
        //          |  | A3 A4 |   | A0 A1 |   | A0 A1 | |
        //          | +| A6 A7 |  -| A6 A7 |  +| A3 A4 | |
        //          +-                                  -+

        TMatrix3 matAdjoint;
        T fSum = 0.0;
        T fValue = 0.0;

        fSum = mTuples[4] * mTuples[8];
        fValue = mTuples[5] * mTuples[7];
        fSum -= fValue;
        matAdjoint[0][0] = fSum;

        fSum = mTuples[1] * mTuples[8];
        fValue = mTuples[2] * mTuples[7];
        fSum -= fValue;
        matAdjoint[0][1] = -fSum;

        fSum = mTuples[1] * mTuples[5];
        fValue = mTuples[2] * mTuples[4];
        fSum -= fValue;
        matAdjoint[0][2] = fSum;

        fSum = mTuples[3] * mTuples[8];
        fValue = mTuples[5] * mTuples[6];
        fSum -= fValue;
        matAdjoint[1][0] = -fSum;

        fSum = mTuples[0] * mTuples[8];
        fValue = mTuples[2] * mTuples[6];
        fSum -= fValue;
        matAdjoint[1][1] = fSum;

        fSum = mTuples[0] * mTuples[5];
        fValue = mTuples[2] * mTuples[3];
        fSum -= fValue;
        matAdjoint[1][2] = -fSum;

        fSum = mTuples[3] * mTuples[7];
        fValue = mTuples[4] * mTuples[6];
        fSum -= fValue;
        matAdjoint[2][0] = fSum;

        fSum = mTuples[0] * mTuples[7];
        fValue = mTuples[1] * mTuples[6];
        fSum -= fValue;
        matAdjoint[2][1] = -fSum;

        fSum = mTuples[0] * mTuples[4];
        fValue = mTuples[1] * mTuples[3];
        fSum -= fValue;
        matAdjoint[2][2] = fSum;

        return matAdjoint;
    }

    template <typename T>
    void TMatrix3<T>::orthonormalize()
    {
        // Algorithm uses Gram-Schmidt orthogonalization.  If 'this' matrix is
        // M = [m0|m1|m2], then orthonormal output matrix is Q = [q0|q1|q2],
        //
        //   q0 = m0/|m0|
        //   q1 = (m1-(q0*m1)q0)/|m1-(q0*m1)q0|
        //   q2 = (m2-(q0*m2)q0-(q1*m2)q1)/|m2-(q0*m2)q0-(q1*m2)q1|
        //
        // where |V| indicates length of vector V and A*B indicates dot
        // product of vectors A and B.

        // compute q0
        T fLength = TMath<T>::sqrt(mTuples[0] * mTuples[0]
            + mTuples[3] * mTuples[3] + mTuples[6] * mTuples[6]);

        mTuples[0] /= fLength;
        mTuples[3] /= fLength;
        mTuples[6] /= fLength;

        // compute q1
        T fDot0 = mTuples[0] * mTuples[1] + mTuples[3] * mTuples[4]
            + mTuples[6] * mTuples[7];

        mTuples[1] -= fDot0*mTuples[0];
        mTuples[4] -= fDot0*mTuples[3];
        mTuples[7] -= fDot0*mTuples[6];

        fLength = TMath<T>::sqrt(mTuples[1] * mTuples[1] + mTuples[4] * mTuples[4]
            + mTuples[7] * mTuples[7]);

        mTuples[1] /= fLength;
        mTuples[4] /= fLength;
        mTuples[7] /= fLength;

        // compute q2
        T fDot1 = mTuples[1] * mTuples[2] + mTuples[4] * mTuples[5]
            + mTuples[7] * mTuples[8];

        fDot0 = mTuples[0] * mTuples[2] + mTuples[3] * mTuples[5]
            + mTuples[6] * mTuples[8];

        mTuples[2] -= fDot0*mTuples[0] + fDot1*mTuples[1];
        mTuples[5] -= fDot0*mTuples[3] + fDot1*mTuples[4];
        mTuples[8] -= fDot0*mTuples[6] + fDot1*mTuples[7];

        fLength = TMath<T>::sqrt(mTuples[2] * mTuples[2] + mTuples[5] * mTuples[5]
            + mTuples[8] * mTuples[8]);

        mTuples[2] /= fLength;
        mTuples[5] /= fLength;
        mTuples[8] /= fLength;
    }

    template <typename T>
    bool TMatrix3<T>::toEulerAnglesXYZ(TRadian<T> &rPitch, TRadian<T> &rYaw, TRadian<T> &rRoll) const
    {
        //          +-                                      -+
        //          |  cy*cz          -cy*sz           sy    |
        // rot(A) = |  cz*sx*sy+cx*sz  cx*cz-sx*sy*sz -cy*sx |
        //          | -cx*cz*sy+sx*sz  cz*sx+cx*sy*sz  cx*cy |
        //          +-                                      -+

        rYaw = TMath<T>::asin(mTuples[2]);

        if (rYaw < TRadian<T>(TMath<T>::HALF_PI))
        {
            if (rYaw > TRadian<T>(-TMath<T>::HALF_PI))
            {
                rPitch = TMath<T>::atan2(-mTuples[5], mTuples[8]);
                rRoll = TMath<T>::atan2(-mTuples[1], mTuples[0]);
                return true;
            }
            else
            {
                // WARNING. Not unique
                TRadian<T> rRmY = TMath<T>::atan2(mTuples[3], mTuples[4]);
                rRoll = TRadian<T>(0.0);
                rPitch = rRoll - rRmY;
                return false;
            }
        }
        else
        {
            TRadian<T> rRpY = TMath<T>::atan2(mTuples[3], mTuples[4]);
            rRoll = TRadian<T>(0.0);
            rPitch = rRpY - rRoll;
            return false;
        }

        return true;
    }

    template <typename T>
    bool TMatrix3<T>::toEulerAnglesXZY(TRadian<T> &rPitch, TRadian<T> &rRoll, TRadian<T> &rYaw) const
    {
        //          +-                                      -+
        //          |  cy*cz          -sz     cz*sy          |
        // rot(A) = |  sx*sy+cx*cy*sz  cx*cz -cy*sx+cx*sy*sz |
        //          | -cx*sy+cy*sx*sz  cz*sx  cx*cy+sx*sy*sz |
        //          +-                                      -+

        rRoll = TMath<T>::asin(-mTuples[1]);

        if (rRoll < TRadian<T>(TMath<T>::HALF_PI))
        {
            if (rRoll > TRadian<T>(-TMath<T>::HALF_PI))
            {
                rPitch = TMath<T>::atan2(mTuples[7], mTuples[4]);
                rYaw = TMath<T>::atan2(mTuples[2], mTuples[0]);
            }
            else
            {
                // WARNING.  Not a unique solution.
                TRadian<T> fRmY = TMath<T>::atan2(-mTuples[6], mTuples[8]);
                rYaw = TRadian<T>(0.0);  // any angle works
                rPitch = rYaw - fRmY;
                return false;
            }
        }
        else
        {
            // WARNING.  Not a unique solution.
            TRadian<T> fRpY = TMath<T>::atan2(-mTuples[6], mTuples[8]);
            rYaw = TRadian<T>(0.0);  // any angle works
            rPitch = fRpY - rYaw;
            return false;
        }

        return true;
    }

    template <typename T>
    bool TMatrix3<T>::toEulerAnglesYXZ(TRadian<T> &rYaw, TRadian<T> &rPitch, TRadian<T> &rRoll) const
    {
        //          +-                                      -+
        //          |  cy*cz+sx*sy*sz  cz*sx*sy-cy*sz  cx*sy |
        // rot(A) = |  cx*sz           cx*cz          -sx    |
        //          | -cz*sy+cy*sx*sz  cy*cz*sx+sy*sz  cx*cy |
        //          +-                                      -+

        rPitch = TMath<T>::asin(-mTuples[4]);

        if (rPitch < TRadian<T>(TMath<T>::HALF_PI))
        {
            if (rPitch > TRadian<T>(-TMath<T>::HALF_PI))
            {
                rYaw = TMath<T>::atan2(mTuples[2], mTuples[8]);
                rRoll = TMath<T>::atan2(mTuples[3], mTuples[4]);
            }
            else
            {
                // WARNING.  Not a unique solution.
                TRadian<T> fRmY = TMath<T>::atan2(-mTuples[1], mTuples[0]);
                rRoll = TRadian<T>(0.0);  // any angle works
                rYaw = rRoll - fRmY;
                return false;
            }
        }
        else
        {
            // WARNING.  Not a unique solution.
            TRadian<T> fRpY = TMath<T>::atan2(-mTuples[1], mTuples[0]);
            rRoll = TRadian<T>(0.0);  // any angle works
            rYaw = fRpY - rRoll;
            return false;
        }

        return true;
    }

    template <typename T>
    bool TMatrix3<T>::toEulerAnglesYZX(TRadian<T> &rYaw, TRadian<T> &rRoll, TRadian<T> &rPitch) const
    {
        //          +-                                      -+
        //          |  cy*cz  sx*sy-cx*cy*sz  cx*sy+cy*sx*sz |
        // rot(A) = |  sz     cx*cz          -cz*sx          |
        //          | -cz*sy  cy*sx+cx*sy*sz  cx*cy-sx*sy*sz |
        //          +-                                      -+

        rRoll = TMath<T>::asin(mTuples[3]);

        if (rRoll < TRadian<T>(TMath<T>::HALF_PI))
        {
            if (rRoll > TRadian<T>(-TMath<T>::HALF_PI))
            {
                rYaw = TMath<T>::atan2(-mTuples[6], mTuples[0]);
                rPitch = TMath<T>::atan2(-mTuples[5], mTuples[4]);
                return true;
            }
            else
            {
                // WARNING.  Not a unique solution.
                TRadian<T> fRmY = TMath<T>::atan2(mTuples[7], mTuples[8]);
                rPitch = TRadian<T>(0.0);  // any angle works
                rYaw = rPitch - fRmY;
                return false;
            }
        }
        else
        {
            // WARNING.  Not a unique solution.
            TRadian<T> fRpY = TMath<T>::atan2(mTuples[7], mTuples[8]);
            rPitch = TRadian<T>(0.0);  // any angle works
            rYaw = fRpY - rPitch;
            return false;
        }

        return true;
    }

    template <typename T>
    bool TMatrix3<T>::toEulerAnglesZXY(TRadian<T> &rRoll, TRadian<T> &rPitch, TRadian<T> &rYaw) const
    {
        //          +-                                     -+
        //          | cy*cz-sx*sy*sz -cx*sz  cz*sy+cy*sx*sz |
        // rot(A) = | cz*sx*sy+cy*sz  cx*cz -cy*cz*sx+sy*sz |
        //          | -cx*sy          sx              cx*cy |
        //          +-                                     -+

        rPitch = TMath<T>::asin(mTuples[7]);

        if (rPitch < TRadian<T>(TMath<T>::HALF_PI))
        {
            if (rPitch > TRadian<T>(-TMath<T>::HALF_PI))
            {
                rRoll = TMath<T>::atan2(-mTuples[1], mTuples[4]);
                rYaw = TMath<T>::atan2(-mTuples[6], mTuples[8]);
            }
            else
            {
                // WARNING.  Not a unique solution.
                TRadian<T> fRmY = TMath<T>::atan2(mTuples[2], mTuples[0]);
                rYaw = TRadian<T>(0.0);  // any angle works
                rRoll = rYaw - fRmY;
                return false;
            }
        }
        else
        {
            // WARNING.  Not a unique solution.
            TRadian<T> fRpY = TMath<T>::atan2(mTuples[2], mTuples[0]);
            rYaw = TRadian<T>(0.0);  // any angle works
            rRoll = fRpY - rYaw;
            return false;
        }

        return true;
    }

    template <typename T>
    bool TMatrix3<T>::toEulerAnglesZYX(TRadian<T> &rRoll, TRadian<T> &rYaw, TRadian<T> &rPitch) const
    {
        //          +-                                     -+
        //          | cy*cz  cz*sx*sy-cx*sz  cx*cz*sy+sx*sz |
        // rot(A) = | cy*sz  cx*cz+sx*sy*sz -cz*sx+cx*sy*sz |
        //          | -sy             cy*sx           cx*cy |
        //          +-                                     -+

        rYaw = TMath<T>::asin(-mTuples[6]);
        if (rYaw < TRadian<T>(TMath<T>::HALF_PI))
        {
            if (rYaw > TRadian<T>(-TMath<T>::HALF_PI))
            {
                rRoll = TMath<T>::atan2(mTuples[3], mTuples[0]);
                rPitch = TMath<T>::atan2(mTuples[7], mTuples[8]);
            }
            else
            {
                // WARNING.  Not a unique solution.
                TRadian<T> fRmY = TMath<T>::atan2(-mTuples[1], mTuples[2]);
                rPitch = TRadian<T>(0.0);  // any angle works
                rRoll = rPitch - fRmY;
                return false;
            }
        }
        else
        {
            // WARNING.  Not a unique solution.
            TRadian<T> fRpY = TMath<T>::atan2(-mTuples[1], mTuples[2]);
            rPitch = TRadian<T>(0.0);  // any angle works
            rRoll = fRpY - rPitch;
            return false;
        }

        return true;
    }

    template <typename T>
    void TMatrix3<T>::QDUDecomposition(TMatrix3& kQ, TVector3<T>& kD, TVector3<T>& kU) const
    {
        // Factor M = QR = QDU where Q is orthogonal (rotation), D is diagonal
        // (scaling), and U is upper triangular with ones on its diagonal 
        // (shear).  Algorithm uses Gram-Schmidt orthogonalization (the QR 
        // algorithm).
        //
        // If M = [ m0 | m1 | m2 ] and Q = [ q0 | q1 | q2 ], then
        //
        //   q0 = m0/|m0|
        //   q1 = (m1-(q0*m1)q0)/|m1-(q0*m1)q0|
        //   q2 = (m2-(q0*m2)q0-(q1*m2)q1)/|m2-(q0*m2)q0-(q1*m2)q1|
        //
        // where |V| indicates length of vector V and A*B indicates dot
        // product of vectors A and B.  The matrix R has entries
        //
        //   r00 = q0*m0  r01 = q0*m1  r02 = q0*m2
        //   r10 = 0      r11 = q1*m1  r12 = q1*m2
        //   r20 = 0      r21 = 0      r22 = q2*m2
        //
        // so D = diag(r00,r11,r22) and U has entries u01 = r01/r00,
        // u02 = r02/r00, and u12 = r12/r11.

        // Q = rotation
        // D = scaling
        // U = shear

        // D stores the three diagonal entries r00, r11, r22
        // U stores the entries U[0] = u01, U[1] = u02, U[2] = u12

        // build orthogonal matrix Q
        T fInvLength = TMath<T>::invSqrt(m3x3[0][0] * m3x3[0][0]
            + m3x3[1][0] * m3x3[1][0] + m3x3[2][0] * m3x3[2][0]);

        kQ[0][0] = m3x3[0][0] * fInvLength;
        kQ[1][0] = m3x3[1][0] * fInvLength;
        kQ[2][0] = m3x3[2][0] * fInvLength;

        T fDot = kQ[0][0] * m3x3[0][1] + kQ[1][0] * m3x3[1][1]
            + kQ[2][0] * m3x3[2][1];
        kQ[0][1] = m3x3[0][1] - fDot * kQ[0][0];
        kQ[1][1] = m3x3[1][1] - fDot * kQ[1][0];
        kQ[2][1] = m3x3[2][1] - fDot * kQ[2][0];
        fInvLength = TMath<T>::invSqrt(kQ[0][1] * kQ[0][1] + kQ[1][1] * kQ[1][1]
            + kQ[2][1] * kQ[2][1]);

        kQ[0][1] *= fInvLength;
        kQ[1][1] *= fInvLength;
        kQ[2][1] *= fInvLength;

        fDot = kQ[0][0] * m3x3[0][2] + kQ[1][0] * m3x3[1][2] +
            kQ[2][0] * m3x3[2][2];
        kQ[0][2] = m3x3[0][2] - fDot * kQ[0][0];
        kQ[1][2] = m3x3[1][2] - fDot * kQ[1][0];
        kQ[2][2] = m3x3[2][2] - fDot * kQ[2][0];
        fDot = kQ[0][1] * m3x3[0][2] + kQ[1][1] * m3x3[1][2] +
            kQ[2][1] * m3x3[2][2];
        kQ[0][2] -= fDot * kQ[0][1];
        kQ[1][2] -= fDot * kQ[1][1];
        kQ[2][2] -= fDot * kQ[2][1];
        fInvLength = TMath<T>::invSqrt(kQ[0][2] * kQ[0][2] + kQ[1][2] * kQ[1][2]
            + kQ[2][2] * kQ[2][2]);

        kQ[0][2] *= fInvLength;
        kQ[1][2] *= fInvLength;
        kQ[2][2] *= fInvLength;

        // guarantee that orthogonal matrix has determinant 1 (no reflections)
        T fDet = kQ[0][0] * kQ[1][1] * kQ[2][2]
            + kQ[0][1] * kQ[1][2] * kQ[2][0] + kQ[0][2] * kQ[1][0] * kQ[2][1]
            - kQ[0][2] * kQ[1][1] * kQ[2][0] - kQ[0][1] * kQ[1][0] * kQ[2][2]
            - kQ[0][0] * kQ[1][2] * kQ[2][1];

        if (fDet < TReal<T>::ZERO)
        {
            for (size_t iRow = 0; iRow < 3; iRow++)
                for (size_t iCol = 0; iCol < 3; iCol++)
                    kQ[iRow][iCol] = -kQ[iRow][iCol];
        }

        // build "right" matrix R
        TMatrix3 kR;
        kR[0][0] = kQ[0][0] * m3x3[0][0] + kQ[1][0] * m3x3[1][0]
            + kQ[2][0] * m3x3[2][0];
        kR[0][1] = kQ[0][0] * m3x3[0][1] + kQ[1][0] * m3x3[1][1]
            + kQ[2][0] * m3x3[2][1];
        kR[1][1] = kQ[0][1] * m3x3[0][1] + kQ[1][1] * m3x3[1][1]
            + kQ[2][1] * m3x3[2][1];
        kR[0][2] = kQ[0][0] * m3x3[0][2] + kQ[1][0] * m3x3[1][2]
            + kQ[2][0] * m3x3[2][2];
        kR[1][2] = kQ[0][1] * m3x3[0][2] + kQ[1][1] * m3x3[1][2]
            + kQ[2][1] * m3x3[2][2];
        kR[2][2] = kQ[0][2] * m3x3[0][2] + kQ[1][2] * m3x3[1][2]
            + kQ[2][2] * m3x3[2][2];

        // the scaling component
        kD[0] = kR[0][0];
        kD[1] = kR[1][1];
        kD[2] = kR[2][2];

        // the shear component
        T fInvD0 = 1.0f / kD[0];
        kU[0] = kR[0][1] * fInvD0;
        kU[1] = kR[0][2] * fInvD0;
        kU[2] = kR[1][2] / kD[1];
    }
}
