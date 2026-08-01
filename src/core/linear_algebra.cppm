export module linear_algebra;

#ifdef __INTELLISENSE__
#include <vector>
#include <cmath>
#else
import std;
#endif

export namespace plymorth {
struct Vec3 {
    Vec3& operator+=(Vec3 other) {
        x += other.x;
        y += other.y;
        z += other.z;
        return *this;
    }
    Vec3& operator-=(Vec3 other) {
        x -= other.x;
        y -= other.y;
        z -= other.z;
        return *this;
    }

    Vec3 operator*=(float scalar) {
        x *= scalar;
        y *= scalar;
        z *= scalar;
        return *this;
    }

    float x = 0.0f;
    float y = 0.0f; 
    float z = 0.0f;
};
Vec3 operator+(Vec3 lhs, Vec3 rhs) {
    lhs += rhs;
    return lhs;
}
Vec3 operator-(Vec3 lhs, Vec3 rhs) {
    lhs -= rhs;
    return lhs;
}

float dot_product(Vec3 first, Vec3 second) noexcept {
    return (first.x * second.x) + (first.y * second.y) + (first.z * second.z);
}

Vec3 cross_product(Vec3 first, Vec3 second) noexcept {
    return Vec3(
        first.y * second.z - first.z * second.y, 
        first.z * second.x - first.x * second.z,
        first.x * second.y - first.y * second.x
    );
}

float get_vec_length(Vec3 vec) noexcept {
    float x_square = vec.x * vec.x;
    float y_square = vec.y * vec.y;
    float z_square = vec.z * vec.z;

    return std::sqrt(x_square + y_square + z_square);
}

Vec3 normalize(Vec3 direction) noexcept { 
    float length = get_vec_length(direction);

    Vec3 normalized = direction;

    normalized.x /= length;
    normalized.y /= length;
    normalized.z /= length;

    return normalized;
}
} // namespace plymorth