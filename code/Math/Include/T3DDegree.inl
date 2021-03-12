

template <typename T>
inline TDegree<T>::TDegree(T degree /* = TReal<T>::ZERO */)
    : mDegree(degree)
{

}

template <typename T>
inline TDegree<T>::TDegree(const TDegree &other)
{
    mDegree = other.mDegree;
}

template <typename T>
inline TDegree<T> &TDegree<T>::operator =(T degree)
{
    mDegree = degree;
    return *this;
}

template <typename T>
inline TDegree<T> &TDegree<T>::operator =(const TDegree &other)
{
    mDegree = other.mDegree;
    return *this;
}

template <typename T>
inline const TDegree<T> &TDegree<T>::operator +() const
{
    return *this;
}

template <typename T>
inline TDegree<T> TDegree<T>::operator -() const
{
    return TDegree(-mDegree);
}

template <typename T>
inline bool TDegree<T>::operator ==(const TDegree &other) const
{
    return (mDegree == other.mDegree);
}

template <typename T>
inline bool TDegree<T>::operator !=(const TDegree &other) const
{
    return (mDegree != other.mDegree);
}

template <typename T>
inline bool TDegree<T>::operator <(const TDegree &other) const
{
    return (mDegree < other.mDegree);
}

template <typename T>
inline bool TDegree<T>::operator <=(const TDegree &other) const
{
    return (mDegree <= other.mDegree);
}

template <typename T>
inline bool TDegree<T>::operator >(const TDegree &other) const
{
    return (mDegree > other.mDegree);
}

template <typename T>
inline bool TDegree<T>::operator >=(const TDegree &other) const
{
    return (mDegree >= other.mDegree);
}

template <typename T>
inline TDegree<T> TDegree<T>::operator +(const TDegree &other) const
{
    return TDegree(mDegree + other.mDegree);
}

template <typename T>
inline TDegree<T> TDegree<T>::operator -(const TDegree &other) const
{
    return TDegree(mDegree - other.mDegree);
}

template <typename T>
inline TDegree<T> &TDegree<T>::operator +=(const TDegree &other)
{
    mDegree += other.mDegree;
    return *this;
}

template <typename T>
inline TDegree<T> &TDegree<T>::operator -=(const TDegree &other)
{
    mDegree -= other.mDegree;
    return *this;
}

template <typename T>
inline TDegree<T> TDegree<T>::operator *(T scalar) const
{
    return TDegree(mDegree * scalar);
}

template <typename T>
inline TDegree<T> TDegree<T>::operator /(T scalar) const
{
    if (scalar != TReal<T>::ZERO)
        return TDegree(mDegree / scalar);
    return TDegree();
}

template <typename T>
inline TDegree<T> &TDegree<T>::operator *=(T scalar)
{
    mDegree *= scalar;
    return *this;
}

template <typename T>
inline TDegree<T> &TDegree<T>::operator /=(T scalar)
{
    if (scalar != TReal<T>::ZERO)
    {
        mDegree /= scalar;
    }
    else
    {
        mDegree = TReal<T>::ZERO;
    }
    return *this;
}

template <typename T>
inline T TDegree<T>::valueDegrees() const
{
    return mDegree;
}

