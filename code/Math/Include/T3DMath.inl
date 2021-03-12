

namespace Tiny3D
{
    ////////////////////////////////////////////////////////////////////////////
    template <typename T>
    inline T TMath<T>::degreesToRadians(T degrees)
    {
        return degrees * DEGREES_TO_RADIANS;
    }

    template <typename T>
    inline T TMath<T>::radiansToDegrees(T radians)
    {
        return radians * RADIANS_TO_DEGREES;
    }

    ////////////////////////////////////////////////////////////////////////////
    template <typename T>
    inline T TRadian<T>::valueDegrees() const
    {
        return TMath<T>::radiansToDegrees(mRadian);
    }

    template <typename T>
    inline T TDegree<T>::valueRadians() const
    {
        return TMath<T>::degreesToRadians(mDegree);
    }

    ////////////////////////////////////////////////////////////////////////////

    template <typename T>
    inline TRadian<T>::TRadian(const TDegree<T> &degree)
        : mRadian(degree.valueRadians())
    {

    }

    template <typename T>
    inline TRadian<T> &TRadian<T>::operator =(const TDegree<T> &degree)
    {
        mRadian = degree.valueRadians();
        return *this;
    }

    template <typename T>
    inline TRadian<T> TRadian<T>::operator +(const TDegree<T> &degree) const
    {
        return TRadian(mRadian + degree.valueRadians());
    }

    template <typename T>
    inline TRadian<T> TRadian<T>::operator -(const TDegree<T> &degree) const
    {
        return TRadian(mRadian - degree.valueRadians());
    }

    template <typename T>
    inline TRadian<T> &TRadian<T>::operator +=(const TDegree<T> &degree)
    {
        mRadian += degree.valueRadians();
        return *this;
    }

    template <typename T>
    inline TRadian<T> &TRadian<T>::operator -=(const TDegree<T> &degree)
    {
        mRadian -= degree.valueRadians();
        return *this;
    }

    ////////////////////////////////////////////////////////////////////////////
    template <typename T>
    inline TDegree<T>::TDegree(const TRadian<T> &radian)
        : mDegree(radian.valueDegrees())
    {

    }

    template <typename T>
    inline TDegree<T> &TDegree<T>::operator =(const TRadian<T> &radian)
    {
        mDegree = radian.valueDegrees();
        return *this;
    }

    template <typename T>
    inline TDegree<T> TDegree<T>::operator +(const TRadian<T> &radian) const
    {
        return TDegree(mDegree + radian.valueDegrees());
    }

    template <typename T>
    inline TDegree<T> TDegree<T>::operator -(const TRadian<T> &radian) const
    {
        return TDegree(mDegree - radian.valueDegrees());
    }

    template <typename T>
    inline TDegree<T> &TDegree<T>::operator +=(const TRadian<T> &radian)
    {
        mDegree += radian.valueDegrees();
        return *this;
    }

    template <typename T>
    inline TDegree<T> &TDegree<T>::operator -=(const TRadian<T> &radian)
    {
        mDegree -= radian.valueDegrees();
        return *this;
    }

    ////////////////////////////////////////////////////////////////////////////

    template <typename T>
    inline T TMath<T>::sqr(T value)
    {
        return value * value;
    }

    template <typename T>
    inline T TMath<T>::sqrt(T value)
    {
        return ::sqrt(value);
    }

    template <typename T>
    inline T TMath<T>::invSqrt(T value)
    {
        return TReal<T>::ONE / ::sqrt(value);
    }

    template <typename T>
    inline T TMath<T>::abs(T value)
    { 
        return T(fabs(value));
    }

    template <typename T>
    inline TDegree<T> TMath<T>::abs(const TDegree<T> &value)
    { 
        return TDegree<T>(fabs(value.valueDegrees())); 
    }

    template <typename T>
    inline TRadian<T> TMath<T>::abs(const TRadian<T>& value)
    { 
        return TRadian<T>(fabs(value.valueRadians()));
    }

    template <typename T>
    inline bool TMath<T>::realEqual(T a, T b, 
        T tolerance /* = std::numeric_limits<TReal>::epsilon() */)
    {
        if (fabs(b-a) <= tolerance)
            return true;
        else
            return false;
    }

    template <typename T>
    inline T TMath<T>::sin(const TDegree<T> &degrees)
    {
        return T(::sin(degrees.valueRadians()));
    }

    template <typename T>
    inline T TMath<T>::sin(const TRadian<T> &radians)
    {
        return T(::sin(radians.valueRadians()));
    }

    template <typename T>
    inline T TMath<T>::cos(const TDegree<T> &degrees)
    {
        return T(::cos(degrees.valueRadians()));
    }

    template <typename T>
    inline T TMath<T>::cos(const TRadian<T> &radians)
    {
        return T(::cos(radians.valueRadians()));
    }

    template <typename T>
    inline T TMath<T>::tan(const TDegree<T> &degrees)
    {
        return T(::tan(degrees.valueRadians()));
    }

    template <typename T>
    inline T TMath<T>::tan(const TRadian<T> &radians)
    {
        return T(::tan(radians.valueRadians()));
    }

    template <typename T>
    inline TRadian<T> TMath<T>::asin(T value)
    {
        return TRadian<T>(::asin(value));
    }

    template <typename T>
    inline TRadian<T> TMath<T>::acos(T value)
    {
        return TRadian<T>(::acos(value));
    }

    template <typename T>
    inline TRadian<T> TMath<T>::atan(T value)
    {
        return TRadian<T>(::atan(value));
    }

    template <typename T>
    inline TRadian<T> TMath<T>::atan2(T y, T x)
    {
        return TRadian<T>(::atan2(y, x));
    }

    template <typename T>
    inline T TMath<T>::min(T a, T b)
    {
        return (a < b ? a : b);
    }

    template <typename T>
    inline T TMath<T>::max(T a, T b)
    {
        return (a > b ? a : b);
    }

    template <typename T>
    const T TMath<T>::POS_INFINITY = TReal<T>::INF;

    template <typename T>
    const T TMath<T>::NEG_INFINITY = TReal<T>::MINUSINF;

    template <typename T>
    const T TMath<T>::PI = T(4.0f * ::atan(TReal<T>::ONE));

    template <typename T>
    const T TMath<T>::TWO_PI = T(2.0f * PI);

    template <typename T>
    const T TMath<T>::HALF_PI = T(TReal<T>::HALF * PI);

    template <typename T>
    const T TMath<T>::DEGREES_TO_RADIANS = PI / T(180.0f);

    template <typename T>
    const T TMath<T>::RADIANS_TO_DEGREES = T(180.0f) / PI;

}

