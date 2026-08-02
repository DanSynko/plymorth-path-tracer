export module linear_algebra;

#ifdef __INTELLISENSE__
#include <vector>
#include <cmath>
#include <numbers>
#else
import std;
#endif

import constants;

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

    float x, y, z = 0.0f;
};
Vec3 operator+(Vec3 lhs, Vec3 rhs) {
    lhs += rhs;
    return lhs;
}
Vec3 operator-(Vec3 lhs, Vec3 rhs) {
    lhs -= rhs;
    return lhs;
}

[[nodiscard]] std::pair<float, float> raster_to_camera(int x, int y) noexcept {
    float x_normalized_device_coordinates = (x + 0.5) / screen_width;
    float y_normalized_device_coordinates = (y + 0.5) / screen_height;

    float x_screen_space = 2 * x_normalized_device_coordinates - 1;
    float y_screen_space = 1 - 2 * y_normalized_device_coordinates;

    float grad_to_rad = FOV * (std::numbers::pi / 180);
    float FOV_scale_factor = std::tan(grad_to_rad / 2);

    float x_cam = x_screen_space * aspect_ratio * FOV_scale_factor;
    float y_cam = y_screen_space * FOV_scale_factor;

    return {x_cam, y_cam};
}

[[nodiscard]] float dot_product(Vec3 first, Vec3 second) noexcept {
    return (first.x * second.x) + (first.y * second.y) + (first.z * second.z);
}

[[nodiscard]] Vec3 cross_product(Vec3 first, Vec3 second) noexcept {
    return Vec3(
        first.y * second.z - first.z * second.y, 
        first.z * second.x - first.x * second.z,
        first.x * second.y - first.y * second.x
    );
}

[[nodiscard]] float get_vec_length(Vec3 vec) noexcept {
    float x_square = vec.x * vec.x;
    float y_square = vec.y * vec.y;
    float z_square = vec.z * vec.z;

    return std::sqrt(x_square + y_square + z_square);
}

[[nodiscard]] Vec3 normalize(Vec3 direction) noexcept { 
    float length = get_vec_length(direction);

    Vec3 normalized = direction;

    normalized.x /= length;
    normalized.y /= length;
    normalized.z /= length;

    return normalized;
}
} // namespace plymorth