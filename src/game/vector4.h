/************************************************************************
 *
 * vector4.h
 * Vector class and implementation
 *
 * 2006-08-30  Migael Strydom    Created
 * 2006-09-02  Timothy Stranex   Added << operator
 * 2006-09-10  Timothy Stranex   Added post divide by scalar
 * 2006-09-14  Migael Strydom    Added SquaredLength
 *
 ************************************************************************/

#ifndef VECTOR4_H
#define VECTOR4_H

#include <cmath>
#include <ostream>

typedef double vectype;

class vector4
{
public:
    vectype x, y, z, w;

    //constructor
    vector4(vectype px = 0, vectype py = 0, vectype pz = 0, vectype pw = 1)
        : x(px), y(py), z(pz), w(pw)
    {
    }

    // vector index
    vectype &operator[](const long idx)
    {
        return *((&x)+idx);
    }

    // vector assignment
    const vector4 &operator=(const vector4 &vec)
    {
        x = vec.x;
        y = vec.y;
        z = vec.z;
        w = vec.w;

        return *this;
    }

    // vector equality
    const bool operator==(const vector4 &vec) const
    {
        return ((x == vec.x) && (y == vec.y) && (z == vec.z));
    }

    // vector inequality
    const bool operator!=(const vector4 &vec) const
    {
        return !(*this == vec);
    }

    // vector add
    const vector4 operator+(const vector4 &vec) const
    {
        return vector4(x + vec.x, y + vec.y, z + vec.z);
    }

    // vector increment
    const vector4& operator+=(const vector4& vec)
    {
        x += vec.x;
        y += vec.y;
        z += vec.z;
        return *this;
    }

    // vector subtraction
    const vector4 operator-(const vector4& vec) const
    {
        return vector4(x - vec.x, y - vec.y, z - vec.z);
    }

    // vector negation
    const vector4 operator-() const
    {
        return vector4(-x, -y, -z);
    }

    // vector decrement
    const vector4 &operator-=(const vector4& vec)
    {
        x -= vec.x;
        y -= vec.y;
        z -= vec.z;

        return *this;
    }

    // scalar self-multiply
    const vector4 &operator*=(const vectype &s)
    {
        x *= s;
        y *= s;
        z *= s;

        return *this;
    }

    // scalar self-divide
    const vector4 &operator/=(const vectype &s)
    {
        const vectype recip = 1/s; // faster to divide only once

        x *= recip;
        y *= recip;
        z *= recip;

        return *this;
    }

    // post multiply by scalar
    const vector4 operator*(const vectype &s) const
    {
        return vector4(x*s, y*s, z*s);
    }

    // pre multiply by scalar
    friend inline const vector4 operator*(const vectype &s, const vector4 &vec)
    {
        return vec*s;
    }

    // post divide by a scalar
    const vector4 operator/(const vectype &s) const
    {
        return vector4(x/s, y/s, z/s);
    }

    //dot vectors
    const vectype operator*(const vector4& vec) const
    {
        return x*vec.x + y*vec.y + z*vec.z;
    }

    //cross vectors
    const vector4 operator%(const vector4& vec) const
    {
        return vector4(y*vec.z - z*vec.y, z*vec.x - x*vec.z, x*vec.y - y*vec.x);
    }

    //returns the length of the vector
    const vectype length() const
    {
        return std::sqrt((*this)*(*this));
    }
    
    //returns the length of the vector squared
    //this is useful for comparisons because expensive square root
    //needn't be calculated
    const vectype squaredLength() const
    {
        return (*this)*(*this);
    }

    /**
     * Print the vector to the stream in the form <x,y,z,w>.
     */
    friend std::ostream& operator<<(std::ostream &os, const vector4 &v)
    {
        os << "<" << v.x << "," << v.y << "," << v.z << "," << v.w << ">";
        return os;
    }
};

#endif
