/*******************************************************************************
 * This file is part of Tiny3D (Tiny 3D Graphic Rendering Engine)
 * Copyright (C) 2015-2020  Answer Wong
 * For latest info, see https://github.com/answerear/Tiny3D
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 ******************************************************************************/

namespace Tiny3D
{
    template <typename T>
    inline void TMatrix2<T>::makeZero()
    {
        mTuples[0] = T(0.0);
        mTuples[1] = T(0.0);
        mTuples[2] = T(0.0);
        mTuples[3] = T(0.0);
    }

    template <typename T>
    inline void TMatrix2<T>::makeIdentity()
    {
        mTuples[0] = T(1.0);
        mTuples[1] = T(0.0);
        mTuples[2] = T(0.0);
        mTuples[3] = T(1.0);
    }

    template <typename T>
    inline void TMatrix2<T>::makeDiagonal(T m00, T m11)
    {
        mTuples[0] = m00;
        mTuples[1] = T(0.0);
        mTuples[2] = T(0.0);
        mTuples[3] = m11;
    }

    template <typename T>
    inline void TMatrix2<T>::makeTensorProduct(const TVector2<T> &rkU, const TVector2<T> &rkV)
    {
        mTuples[0] = rkU[0] * rkV[0];
        mTuples[1] = rkU[0] * rkV[1];
        mTuples[2] = rkU[1] * rkV[0];
        mTuples[3] = rkU[1] * rkV[1];
    }

    template <typename T>
    inline void TMatrix2<T>::fromAngle(const TRadian<T> &radians)
    {
        mTuples[0] = TMath<T>::cos(radians);
        mTuples[2] = TMath<T>::sin(radians);
        mTuples[1] = -mTuples[2];
        mTuples[3] = mTuples[0];
    }

    template <typename T>
    inline TRadian<T> TMatrix2<T>::toAngle() const
    {
        return TMath<T>::atan2(mTuples[2], mTuples[0]);
    }

    template <typename T>
    inline TMatrix2<T>::TMatrix2(bool isZero /* = true */)
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
    inline TMatrix2<T>::TMatrix2(const TMatrix2 &other)
    {
        memcpy(mTuples, other.mTuples, sizeof(mTuples));
    }

    template <typename T>
    inline TMatrix2<T>::TMatrix2(T m00, T m01, T m10, T m11)
    {
        mTuples[0] = m00;
        mTuples[1] = m01;
        mTuples[2] = m10;
        mTuples[3] = m11;
    }

    template <typename T>
    inline TMatrix2<T>::TMatrix2(T tuple[4], bool isRowMajor)
    {
        if (isRowMajor)
        {
            memcpy(mTuples, tuple, sizeof(mTuples));
        }
        else
        {
            mTuples[0] = tuple[0];
            mTuples[1] = tuple[2];
            mTuples[2] = tuple[1];
            mTuples[3] = tuple[3];
        }
    }

    template <typename T>
    inline TMatrix2<T>::TMatrix2(const TVector2<T> &rkU, const TVector2<T> &rkV, bool isColumns)
    {
        if (isColumns)
        {
            mTuples[0] = rkU[0];
            mTuples[1] = rkV[0];
            mTuples[2] = rkU[1];
            mTuples[3] = rkV[1];
        }
        else
        {
            mTuples[0] = rkU[0];
            mTuples[1] = rkU[1];
            mTuples[2] = rkV[0];
            mTuples[3] = rkV[1];
        }
    }

    template <typename T>
    inline TMatrix2<T>::TMatrix2(const TVector2<T> *akV, bool isColumns)
    {
        if (isColumns)
        {
            mTuples[0] = akV[0][0];
            mTuples[1] = akV[1][0];
            mTuples[2] = akV[0][1];
            mTuples[3] = akV[1][1];
        }
        else
        {
            mTuples[0] = akV[0][0];
            mTuples[1] = akV[0][1];
            mTuples[2] = akV[1][0];
            mTuples[3] = akV[1][1];
        }
    }

    template <typename T>
    inline TMatrix2<T>::TMatrix2(T m00, T m11)
    {
        makeDiagonal(m00, m11);
    }

    template <typename T>
    inline TMatrix2<T>::TMatrix2(const TRadian<T> &rkRadians)
    {
        fromAngle(rkRadians);
    }

    template <typename T>
    inline TMatrix2<T>::TMatrix2(const TVector2<T> &rkU, const TVector2<T> &rkV)
    {
        makeTensorProduct(rkU, rkV);
    }

    template <typename T>
    inline TMatrix2<T>::operator const T *() const
    {
        return mTuples;
    }

    template <typename T>
    inline TMatrix2<T>::operator T *()
    {
        return mTuples;
    }

    template <typename T>
    inline const T *TMatrix2<T>::operator [](int32_t row) const
    {
        T3D_ASSERT(row >= 0 && row < 2);
        return &mTuples[row << 1];
    }

    template <typename T>
    inline T *TMatrix2<T>::operator [](int32_t row)
    {
        T3D_ASSERT(row >= 0 && row < 2);
        return &mTuples[row << 1];
    }

    template <typename T>
    inline T TMatrix2<T>::operator ()(int32_t row, int32_t col) const
    {
        T3D_ASSERT(row >= 0 && row < 2 && col >= 0 && col < 2);
        return mTuples[(row << 1) + col];
    }

    template <typename T>
    inline T &TMatrix2<T>::operator ()(int32_t row, int32_t col)
    {
        T3D_ASSERT(row >= 0 && row < 2 && col >= 0 && col < 2);
        return mTuples[(row << 1) + col];
    }

    template <typename T>
    inline void TMatrix2<T>::setRow(int32_t row, const TVector2<T> &rkV)
    {
        T3D_ASSERT(row >= 0 && row < 2);
        int32_t i = row << 1;
        mTuples[i] = rkV[0];
        mTuples[i+1] = rkV[1];
    }

    template <typename T>
    inline TVector2<T> TMatrix2<T>::getRow(int32_t row) const
    {
        T3D_ASSERT(row >= 0 && row < 2);
        int32_t i = row << 1;
        return TVector2<T>(mTuples[i], mTuples[i+1]);
    }

    template <typename T>
    inline void TMatrix2<T>::setColumn(int32_t col, const TVector2<T> &rkV)
    {
        T3D_ASSERT(col >= 0 && col < 2);
        mTuples[col] = rkV[0];
        mTuples[2+ col] = rkV[1];
    }

    template <typename T>
    inline TVector2<T> TMatrix2<T>::getColumn(int32_t col) const
    {
        T3D_ASSERT(col >= 0 && col < 2);
        return TVector2<T>(mTuples[col], mTuples[2+ col]);
    }

    template <typename T>
    inline void TMatrix2<T>::getColumnMajor(T *columns) const
    {
        columns[0] = mTuples[0];
        columns[1] = mTuples[2];
        columns[2] = mTuples[1];
        columns[3] = mTuples[3];
    }

    template <typename T>
    inline TMatrix2<T> &TMatrix2<T>::operator =(const TMatrix2 &other)
    {
        memcpy(mTuples, other.mTuples, sizeof(mTuples));
        return *this;
    }

    template <typename T>
    inline int32_t TMatrix2<T>::compareArrays(const TMatrix2 &other) const
    {
        return memcmp(mTuples, other.mTuples, sizeof(mTuples));
    }

    template <typename T>
    inline bool TMatrix2<T>::operator ==(const TMatrix2 &other) const
    {
        return (compareArrays(other) == 0);
    }

    template <typename T>
    inline bool TMatrix2<T>::operator !=(const TMatrix2 &other) const
    {
        return (compareArrays(other) != 0);
    }

    template <typename T>
    inline bool TMatrix2<T>::operator <(const TMatrix2 &other) const
    {
        return (compareArrays(other) < 0);
    }

    template <typename T>
    inline bool TMatrix2<T>::operator <=(const TMatrix2 &other) const
    {
        return (compareArrays(other) <= 0);
    }

    template <typename T>
    inline bool TMatrix2<T>::operator >(const TMatrix2 &other) const
    {
        return (compareArrays(other) > 0);
    }

    template <typename T>
    inline bool TMatrix2<T>::operator >=(const TMatrix2 &other) const
    {
        return (compareArrays(other) >= 0);
    }

    template <typename T>
    inline TMatrix2<T> TMatrix2<T>::operator +(const TMatrix2 &other) const
    {
        return TMatrix2(
            mTuples[0] + other.mTuples[0],
            mTuples[1] + other.mTuples[1],
            mTuples[2] + other.mTuples[2],
            mTuples[3] + other.mTuples[3]);
    }

    template <typename T>
    inline TMatrix2<T> TMatrix2<T>::operator -(const TMatrix2 &other) const
    {
        return TMatrix2(
            mTuples[0] - other.mTuples[0],
            mTuples[1] - other.mTuples[1],
            mTuples[2] - other.mTuples[2],
            mTuples[3] - other.mTuples[3]);
    }

    template <typename T>
    inline TMatrix2<T> TMatrix2<T>::operator *(const TMatrix2 &other) const
    {
        return TMatrix2(
            mTuples[0] * other.mTuples[0] + mTuples[1] * other.mTuples[2],
            mTuples[0] * other.mTuples[1] + mTuples[1] * other.mTuples[3],
            mTuples[2] * other.mTuples[0] + mTuples[2] * other.mTuples[2],
            mTuples[2] * other.mTuples[1] + mTuples[2] * other.mTuples[3]);
    }

    template <typename T>
    inline TMatrix2<T> TMatrix2<T>::operator *(T scalar) const
    {
        return TMatrix2(mTuples[0] * scalar, mTuples[1] * scalar, 
            mTuples[2] * scalar, mTuples[3] * scalar);
    }

    template <typename T>
    inline TMatrix2<T> TMatrix2<T>::operator /(T scalar) const
    {
        if (scalar != TReal<T>::ZERO)
            return TMatrix2(mTuples[0] / scalar, mTuples[1] / scalar,
                mTuples[2] / scalar, mTuples[3] / scalar);
        return ZERO;
    }

    template <typename T>
    inline TMatrix2<T> TMatrix2<T>::operator -() const
    {
        return TMatrix2(-mTuples[0], -mTuples[1], -mTuples[2], -mTuples[3]);
    }

    template <typename T>
    inline TMatrix2<T> &TMatrix2<T>::operator +=(const TMatrix2 &other)
    {
        mTuples[0] += other.mTuples[0];
        mTuples[1] += other.mTuples[1];
        mTuples[2] += other.mTuples[2];
        mTuples[3] += other.mTuples[3];
        return *this;
    }

    template <typename T>
    inline TMatrix2<T> &TMatrix2<T>::operator -=(const TMatrix2 &other)
    {
        mTuples[0] -= other.mTuples[0];
        mTuples[1] -= other.mTuples[1];
        mTuples[2] -= other.mTuples[2];
        mTuples[3] -= other.mTuples[3];
        return *this;
    }

    template <typename T>
    inline TMatrix2<T> &TMatrix2<T>::operator *=(T fScalar)
    {
        mTuples[0] *= fScalar;
        mTuples[1] *= fScalar;
        mTuples[2] *= fScalar;
        mTuples[3] *= fScalar;
        return *this;
    }

    template <typename T>
    inline TMatrix2<T> &TMatrix2<T>::operator /=(T scalar)
    {
        if (scalar != TReal<T>::ZERO)
        {
            mTuples[0] /= scalar;
            mTuples[1] /= scalar;
            mTuples[2] /= scalar;
            mTuples[3] /= scalar;
        }
        else
        {
            makeZero();
        }
        return *this;
    }

    template <typename T>
    inline TVector2<T> TMatrix2<T>::operator *(const TVector2<T> &rkV) const
    {
        return TVector2<T>(mTuples[0] * rkV[0] + mTuples[1] * rkV[1], 
            mTuples[2] * rkV[0] + mTuples[3] * rkV[1]);
    }

    template <typename T>
    inline TMatrix2<T> TMatrix2<T>::transpose() const
    {
        return TMatrix2(mTuples[0], mTuples[2], mTuples[1], mTuples[3]);
    }

    template <typename T>
    inline TMatrix2<T> TMatrix2<T>::transposeTimes(const TMatrix2 &other) const
    {
        return TMatrix2(
            mTuples[0] * other.mTuples[0] + mTuples[2] * other.mTuples[2],
            mTuples[0] * other.mTuples[1] + mTuples[2] * other.mTuples[3],
            mTuples[1] * other.mTuples[0] + mTuples[3] * other.mTuples[2],
            mTuples[1] * other.mTuples[1] + mTuples[3] * other.mTuples[3]);
    }

    template <typename T>
    inline TMatrix2<T> TMatrix2<T>::timesTranspose(const TMatrix2 &other) const
    {
        return TMatrix2(
            mTuples[0] * other.mTuples[0] + mTuples[1] * other.mTuples[2],
            mTuples[2] * other.mTuples[0] + mTuples[2] * other.mTuples[2],
            mTuples[0] * other.mTuples[1] + mTuples[1] * other.mTuples[3],
            mTuples[2] * other.mTuples[1] + mTuples[2] * other.mTuples[3]);
    }

    template <typename T>
    inline TMatrix2<T> TMatrix2<T>::inverse() const
    {
        TMatrix2 mat;
        T det = mTuples[0] * mTuples[3] - mTuples[1] * mTuples[2];
        if (det != TReal<T>::ZERO)
        {
            mat.mTuples[0] = mTuples[3] / det;
            mat.mTuples[1] = -mTuples[1] / det;
            mat.mTuples[2] = -mTuples[2] / det;
            mat.mTuples[3] = mTuples[0] / det;
        }
        return mat;
    }

    template <typename T>
    inline TMatrix2<T> TMatrix2<T>::adjoint() const
    {
        return TMatrix2(mTuples[3], -mTuples[1], -mTuples[2], mTuples[0]);
    }

    template <typename T>
    inline T TMatrix2<T>::determinant() const
    {
        return mTuples[0] * mTuples[3] - mTuples[1] * mTuples[2];
    }

    template <typename T>
    inline T TMatrix2<T>::qform(const TVector2<T> &rkU, const TVector2<T> &rkV) const
    {
        return rkU.dot((*this) * rkV);
    }

    template <typename T>
    inline void TMatrix2<T>::orthonormalize()
    {
        // Algorithm uses Gram-Schmidt orthogonalization.  
        // If 'this' matrix is M = [m0|m1], then orthonormal output matrix is 
        // Q = [q0|q1],
        //
        //   q0 = m0/|m0|
        //   q1 = (m1-(q0*m1)q0)/|m1-(q0*m1)q0|
        //
        // where |V| indicates length of vector V and A*B indicates dot product 
        // of vectors A and B.
        
        // compute q0
        T len = TMath<T>::sqrt(mTuples[0] * mTuples[0] + mTuples[2] * mTuples[2]);
        mTuples[0] /= len;
        mTuples[2] /= len;

        // compute q1
        T dot0 = mTuples[0] * mTuples[1] + mTuples[2] * mTuples[3];
        mTuples[1] -= dot0 * mTuples[0];
        mTuples[3] -= dot0 * mTuples[2];

        len = TMath<T>::sqrt(mTuples[1] * mTuples[1] + mTuples[3] * mTuples[3]);
        mTuples[1] /= len;
        mTuples[3] /= len;
    }

    template <typename T>
    inline void TMatrix2<T>::eigendecomposition(TMatrix2 &rRot, TMatrix2 &rDiag) const
    {
        T trace = mTuples[0] + mTuples[3];
        T diff = mTuples[0] - mTuples[3];
        T discr = TMath<T>::sqrt(diff * diff + ((mTuples[1] * mTuples[1]) * 4));
        T val0 = (trace - discr) / 2;
        T val1 = (trace + discr) / 2;
        rDiag.makeDiagonal(val0, val1);
        
        TVector2<T> kRow0(mTuples[0] - val0, mTuples[1]);
        TVector2<T> kRow1(mTuples[1], mTuples[3] - val0);
        T len0 = kRow0.length();
        T len1 = kRow1.length();
        
        if (len0 > len1)
        {
            if (len0 > TReal<T>::ZERO)
            {
                rRot.mTuples[0] = kRow0[1];
                rRot.mTuples[1] = kRow0[0];
                rRot.mTuples[2] = -kRow0[0];
                rRot.mTuples[3] = kRow0[1];
            }
            else
            {
                rRot.makeIdentity();
            }
        }
        else
        {
            if (len1 > TReal<T>::ZERO)
            {
                rRot.mTuples[0] = kRow1[1];
                rRot.mTuples[1] = kRow1[0];
                rRot.mTuples[2] = -kRow1[0];
                rRot.mTuples[3] = kRow1[1];
            }
            else
            {
                rRot.makeIdentity();
            }
        }
    }

    template <typename T>
    inline TMatrix2<T> operator *(T scalar, const TMatrix2<T> &rkM)
    {
        return rkM * scalar;
    }

    template <typename T>
    inline TVector2<T> operator *(const TVector2<T> &rkV, const TMatrix2<T> &rkM)
    {
        return TVector2<T>(rkV[0] * rkM[0][0] + rkV[1] * rkM[1][0], 
            rkV[0] * rkM[0][1] + rkV[1] * rkM[1][1]);
    }

    template <typename T>
    const TMatrix2<T> TMatrix2<T>::ZERO(0.0, 0.0, 0.0, 0.0);

    template <typename T>
    const TMatrix2<T> TMatrix2<T>::IDENTITY(1.0, 0.0, 0.0, 1.0);
}
