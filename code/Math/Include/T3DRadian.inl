

template <typename T>
inline TRadian<T>::TRadian(T radian)
        : mRadian(radian)
{

}

template <typename T>
inline TRadian<T>::TRadian(const TRadian &other)
    : mRadian(other.mRadian)
{

}

template <typename T>
inline TRadian<T> &TRadian<T>::operator =(T radian)
{
    mRadian = radian;
    return *this;
}

template <typename T>
inline TRadian<T> &TRadian<T>::operator =(const TRadian &other)
{
    mRadian = other.mRadian;
    return *this;
}

template <typename T>
inline const TRadian<T> &TRadian<T>::operator +() const
{
    return *this;
}

template <typename T>
inline TRadian<T> TRadian<T>::operator -() const
{
    return TRadian(-mRadian);
}

template <typename T>
inline bool TRadian<T>::operator ==(const TRadian &other) const
{
    return (mRadian == other.mRadian);
}

template <typename T>
inline bool TRadian<T>::operator !=(const TRadian &other) const
{
    return (mRadian != other.mRadian);
}

template <typename T>
inline bool TRadian<T>::operator <(const TRadian &other) const
{
    return (mRadian < other.mRadian);
}

template <typename T>
inline bool TRadian<T>::operator <=(const TRadian &other) const
{
    return (mRadian <= other.mRadian);
}

template <typename T>
inline bool TRadian<T>::operator >(const TRadian &other) const
{
    return (mRadian > other.mRadian);
}

template <typename T>
inline bool TRadian<T>::operator >=(const TRadian &other) const
{
    return (mRadian >= other.mRadian);
}

template <typename T>
inline TRadian<T> TRadian<T>::operator +(const TRadian &other) const
{
    return TRadian(mRadian + other.mRadian);
}

template <typename T>
inline TRadian<T> TRadian<T>::operator -(const TRadian &other) const
{
    return TRadian(mRadian - other.mRadian);
}

template <typename T>
inline TRadian<T> &TRadian<T>::operator +=(const TRadian &other)
{
    mRadian += other.mRadian;
    return *this;
}

template <typename T>
inline TRadian<T> &TRadian<T>::operator -=(const TRadian &other)
{
    mRadian -= other.mRadian;
    return *this;
}

template <typename T>
inline TRadian<T> TRadian<T>::operator *(T scalar) const
{
    return TRadian(mRadian * scalar);
}

template <typename T>
inline TRadian<T> TRadian<T>::operator /(T scalar) const
{
    if (scalar != TReal<T>::ZERO)
        return TRadian(mRadian / scalar);
    return TRadian();
}

template <typename T>
inline TRadian<T> &TRadian<T>::operator *=(T scalar)
{
    mRadian *= scalar;
    return *this;
}

template <typename T>
inline TRadian<T> &TRadian<T>::operator /=(T scalar)
{
    if (scalar != TReal<T>::ZERO)
    {
        mRadian /= scalar;
    }
    else
    {
        mRadian = TReal<T>::ZERO;
    }

    return *this;
}

template <typename T>
inline T TRadian<T>::valueRadians() const
{
    return mRadian;
}


