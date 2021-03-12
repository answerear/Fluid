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
    inline TSphere<T>::TSphere()
        : mCenter(TReal<T>::ZERO, TReal<T>::ZERO, TReal<T>::ZERO)
        , mRadius(0)
    {
    }

    template <typename T>
    inline TSphere<T>::TSphere(const TVector3<T> &p0)
    {
        mRadius = TReal<T>::ZERO;
        mCenter = p0;
    }

    template <typename T>
    inline TSphere<T>::TSphere(const TVector3<T> &p0, const TVector3<T> &p1)
    {
        TVector3<T> a = p1 - p0;
        TVector3<T> o = TReal<T>::HALF * a;
        mRadius = o.normalize();
        mCenter = p0 + o;
    }

    template <typename T>
    inline bool TSphere<T>::build(const TVector3<T> &p0, const TVector3<T> &p1, 
        const TVector3<T> &p2)
    {
        TVector3<T> a = p1 - p0;
        TVector3<T> b = p2 - p0;

        TVector3<T> n = a.cross(b);
        T denominator = 2 * n.dot(n);

        if (denominator == TReal<T>::ZERO)
            return false;

        TVector3<T> o = (b.dot(b) * (n.cross(a))
            + (a.dot(a) * (b.cross(n)))) / denominator;

        mRadius = o.normalize();
        mCenter = p0 + o;

        return true;
    }
    
    template <typename T>
    inline bool TSphere<T>::build(const TVector3<T> &p0, const TVector3<T> &p1, 
        const TVector3<T> &p2, const TVector3<T> &p3)
    {
        TVector3<T> a = p1 - p0;
        TVector3<T> b = p2 - p0;
        TVector3<T> c = p3 - p0;

        TMatrix3<T> M(
            a.x(), a.y(), a.z(),
            b.x(), b.y(), b.z(),
            c.x(), c.y(), c.z());

        T denominator = 2 * M.determinant();

        if (denominator == TReal<T>::ZERO)
            return false;

        TVector3<T> n = a.cross(b);

        TVector3<T> o = (c.dot(c) * n + (b.dot(b) * c.cross(a))
            + a.dot(a) * b.cross(c)) / denominator;

        mRadius = o.normalize();
        mCenter = p0 + o;

        return true;
    }

    template <typename T>
    inline TSphere<T>::TSphere(const TVector3<T> &center, const T &radius)
        : mCenter(center)
        , mRadius(radius)
    {
    }

    template <typename T>
    inline TSphere<T>::TSphere(const TSphere &sphere)
        : mCenter(sphere.mCenter)
        , mRadius(sphere.mRadius)
    {
    }

    template <typename T>
    inline TSphere<T> &TSphere<T>::operator =(const TSphere &other)
    {
        mCenter = other.mCenter;
        mRadius = other.mRadius;
        return *this;
    }

    template <typename T>
    inline void TSphere<T>::build(const TVector3<T> points[], size_t count, 
        BuildOption option /* = E_BUILD_WELZL */)
    {
        switch (option)
        {
        case BuildOption::WELZL:
            buildByWelzl(points, count);
            break;
        case BuildOption::RITTER:
            buildByRitter(points, count);
            break;
        case BuildOption::AVERAGE:
            buildByAverage(points, count);
            break;
        default:
            break;
        }
    }

    template <typename T>
    inline const TVector3<T> &TSphere<T>::getCenter() const
    {
        return mCenter;
    }

    template <typename T>
    inline TVector3<T> &TSphere<T>::getCenter()
    {
        return mCenter;
    }

    template <typename T>
    inline const T &TSphere<T>::getRadius() const
    {
        return mRadius;
    }

    template <typename T>
    inline T &TSphere<T>::getRadius()
    {
        return mRadius;
    }

    template <typename T>
    inline void TSphere<T>::setCenter(const TVector3<T> &center)
    {
        mCenter = center;
    }

    template <typename T>
    inline void TSphere<T>::setRadius(const T &radius)
    {
        mRadius = radius;
    }

    template <typename T>
    inline bool TSphere<T>::contains(const TVector3<T> &point) const
    {
        return ((point - mCenter).length() <= mRadius);
    }

    template <typename T>
    void TSphere<T>::buildByWelzl(const TVector3<T> points[], size_t count)
    {
        TVector3<T> **ptr = new TVector3<T>*[count];

        size_t i = 0;
        for (i = 0; i < count; ++i)
        {
            ptr[i] = (TVector3<T>*)(&points[i]);
        }

        *this = recurseMinSphere(ptr, count);

        delete []ptr;

        for (i = 0; i < count; ++i)
        {
            TVector3<T> dist = points[i] - mCenter;
            T radius = dist.length();
            T3D_ASSERT(radius <= mRadius);
        }
    }

    template <typename T>
    TSphere<T> TSphere<T>::recurseMinSphere(
        TVector3<T> *points[], 
        size_t count,
        size_t b)
    {
        TSphere<T> sphere;

        switch (b)
        {
        case 0:
            sphere = TSphere<T>();
            break;
        case 1:
            sphere = TSphere<T>(*points[-1]);
            break;
        case 2:
            sphere = TSphere<T>(*points[-1], *points[-2]);
            break;
        case 3:
//             sphere = Sphere(*points[-1], *points[-2], *points[-3]);
            if (!sphere.build(*points[-1], *points[-2], *points[-3]))
            {
                recurseMinSphere(points + 1, 3, b);
            }
            break;
        case 4:
//             sphere = Sphere(*points[-1], *points[-2], *points[-3], *points[-4]);
            if (!sphere.build(*points[-1], *points[-2], *points[-3], *points[-4]))
            {
                recurseMinSphere(points + 1, 4, b);
            }
            return sphere;
            break;
        }

        size_t i = 0;
        for (i = 0; i < count; ++i)
        {
            T d = sphere.mCenter.distance2(*points[i]);
            if (d > TReal<T>::ZERO)
            {
                size_t j = 0;
                for (j = i; j > 0; --j)
                {
                    TVector3<T> *t = points[j];
                    points[j] = points[j - 1];
                    points[j - 1] = t;
                }

                sphere = recurseMinSphere(points + 1, i, b + 1);
            }
        }

        return sphere;
    }

    template <typename T>
    void TSphere<T>::buildByRitter(const TVector3<T> points[], size_t count)
    {
        // 先找出在x，y，z三个轴方向上距离最大的点作为半径
        size_t x0 = 0, x1 = 0;
        size_t y0 = 0, y1 = 0;
        size_t z0 = 0, z1 = 0;

        size_t i;
        for (i = 1; i < count; ++i)
        {
            if (points[i].x() < points[x0].x())
                x0 = i;
            if (points[i].x() > points[x1].x())
                x1 = i;
            if (points[i].y() < points[y0].y())
                y0 = i;
            if (points[i].y() > points[y1].y())
                y1 = i;
            if (points[i].z() < points[z0].z())
                z0 = i;
            if (points[i].z() > points[z1].z())
                z1 = i;
        }

        TVector3<T> temp = points[x1] - points[x0];
        T dx = temp.length2();

        temp = points[y1] - points[y0];
        T dy = temp.length2();

        temp = points[z1] - points[z0];
        T dz = temp.length2();

        size_t max = x1, min = x0;

        if (dz > dx && dz > dy)
        {
            max = z1;
            min = z0;
        }
        else if (dy > dx && dy > dz)
        {
            max = y1;
            min = y0;
        }

        TVector3<T> center((points[max] + points[min]) * TReal<T>::HALF);
        T d2 = (points[max] - center).length2();
        T radius = TMath<T>::sqrt(d2);

        // 遍历所有顶点来修正，以得到一个逼近的包围球
        for (i = 0; i < count; ++i)
        {
            //T d2 = points[i].distance2(center);
            TVector3<T> dist = points[i] - center;
            d2 = dist.length2();
            if (d2 > radius * radius)
            {
                T d = TMath<T>::sqrt(d2);
                T newRadius = (d + radius) * TReal<T>::HALF;
                T k = (newRadius - radius) / d;
                radius = newRadius;
                center += dist * k;
            }
        }

        mCenter = center;
        mRadius = radius;

//         for (i = 0; i < count; ++i)
//         {
//             TVector3<T> dist = points[i] - center;
//             T d2 = dist.length();
//             T3D_ASSERT(d2 <= radius);
//         }
    }

    template <typename T>
    void TSphere<T>::buildByAverage(const TVector3<T> points[], size_t count)
    {
        TVector3<T> center;
        T radius = TReal<T>::MINUS_ONE;

        if (count > 0)
        {
            center = TVector3<T>::ZERO;
            size_t i = 0;
            for (i = 0; i < count; ++i)
                center += points[i];

            center /= T(count);

            for (i = 0; i < count; ++i)
            {
                T d2 = points[i].distance2(center);

                if (d2 > radius)
                    radius = d2;
            }

            radius = TMath<T>::sqrt(radius);
        }

        mCenter = center;
        mRadius = radius;
    }
}