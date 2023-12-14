
#pragma once

#include <cmath>
#include <raylib.h>

#define dbg_vec(A) printf(#A ": %f, %f, %f\n", A.x, A.y, A.z);

namespace nbody {

struct vec3 {
    double x = 0;
    double y = 0;
    double z = 0;

    inline vec3 &operator+=(const vec3 &rhs) {
        x += rhs.x;
        y += rhs.y;
        z += rhs.z;
        return *this;
    }

    inline vec3 &operator-=(const vec3 &rhs) {
        x -= rhs.x;
        y -= rhs.y;
        z -= rhs.z;
        return *this;
    }

    inline vec3 &operator*=(const vec3 &rhs) {
        x *= rhs.x;
        y *= rhs.y;
        z *= rhs.z;
        return *this;
    }

    inline vec3 &operator*=(double rhs) {
        x *= rhs;
        y *= rhs;
        z *= rhs;
        return *this;
    }

    inline vec3 &operator/=(const vec3 &rhs) {
        x /= rhs.x;
        y /= rhs.y;
        z /= rhs.z;
        return *this;
    }

    inline vec3 &operator/=(double rhs) {
        x /= rhs;
        y /= rhs;
        z /= rhs;
        return *this;
    }

    inline Vector3 convert() {
        return (Vector3) {
            (float) x,
            (float) y,
            (float) z,
        };
    }

    inline double dot(const vec3 &rhs) const {
        return x * rhs.x + y * rhs.y + z * rhs.z;
    }

    inline double length() const {
        return std::sqrt(dot(*this));
    }

    inline vec3 normalized() const {
        return *this / length();
    }
    
    friend vec3 operator+(vec3 lhs, const vec3 &rhs) {
        lhs += rhs;
        return lhs;
    }

    friend vec3 operator-(vec3 lhs, const vec3 &rhs) {
        lhs -= rhs;
        return lhs;
    }

    friend vec3 operator*(vec3 lhs, const vec3 &rhs) {
        lhs *= rhs;
        return lhs;
    }

    friend vec3 operator*(vec3 lhs, double rhs) {
        lhs *= rhs;
        return lhs;
    }

    friend vec3 operator/(vec3 lhs, const vec3 &rhs) {
        lhs /= rhs;
        return lhs;
    }

    friend vec3 operator/(vec3 lhs, double rhs) {
        lhs /= rhs;
        return lhs;
    }
};

}

