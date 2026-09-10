#include <iosstream>
#include <vector>
#include <cmath>
// #include <thread>
// #include <chrono>

struct Vec3 {
    double x{0.0}, y{0.0}, z{0.0};

    // vector addition: a + b
    Vec3 operator+(const Vec3& other) const {
        return {x + other.x, y + other.y, z + other.z};
    }

    // in-place addition: a += b
    Vec3& operator+=(const Vec3& other) {
        x += other.x;
        y += other.y;
        z += other.z;
        return *this;
    }

    // overload vector subtraction and compute directional displacement from 'other' to '*this'
    Vec3 operator-(const Vec3& other) {
        return {x - other.x, y - other.y, z - other.z};
    }

    // overload scalar multiplication 
    Vec3 operator*(double s) const {
        return {x * s, y * s, z * s};
    }




