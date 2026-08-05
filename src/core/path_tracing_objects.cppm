export module path_tracing_objects;

#ifdef __INTELLISENSE__
#include <vector>
#include <cmath>
#else
import std;
#endif

import linear_algebra;

export namespace plymorth {
struct Ray {
    Vec3 origin;
    Vec3 direction;
};

struct Color {
    float r, g, b = 255.0f;
};

struct Sphere {
    Color color = {255.0f, 0.0f, 0.0f};
    Vec3 center = {0.0f, 0.0f, -5.0f};
    float radius = 1.0f;
};

struct Plane {
    Color color = {0.0f, 255.0f, 0.0f};
    Vec3 normal = {0.0f, 1.0f, 0.0f};
    float d = 25.0f;
};

struct Emission {
    float r_intensity = 1.0f;
    float g_intensity = 1.0f;
    float b_intensity = 1.0f;
};

struct LightSource {
    Sphere shape{
        {255.0f, 255.0f, 255.0f},
        {-2.7f, 1.5f, -4.0f},
        1.0f
    };
    Emission emission{};
    Color emission_color{
        shape.color.r * emission.r_intensity, 
        shape.color.g * emission.g_intensity, 
        shape.color.b * emission.b_intensity
    };
};

[[nodiscard]] bool hit_sphere(Sphere sphere, Ray current_ray) noexcept {
    float a = dot_product(current_ray.direction, current_ray.direction);

    Vec3 V = current_ray.origin - sphere.center; 
    float b = 2 * dot_product(current_ray.direction, V);

    float c = dot_product(V, V) - std::powf(sphere.radius, 2);


    float discriminant = (std::powf(b, 2)) - 4 * a * c;

    if (discriminant < 0) {
        return false;
    }

    float first_root = (-b - std::sqrt(discriminant)) / 2;
    float second_root = (-b + std::sqrt(discriminant)) / 2;

    float& nearest_root = first_root;

    constexpr float t_min = 0.001f;
    constexpr float t_max = std::numeric_limits<float>::infinity();

    if (nearest_root < t_min || nearest_root > t_max) {
        nearest_root = second_root;
        if (nearest_root < t_min || nearest_root > t_max) {
            return false;
        }
    }

    return true;
}

[[nodiscard]] bool hit_plane(Plane plane, Ray current_ray) noexcept {
    float origin_to_point_distance = -(dot_product(plane.normal, current_ray.origin) + plane.d);
    float ray_incidence_angle = dot_product(current_ray.direction, plane.normal);

    if (ray_incidence_angle == 0) {
        return false;
    }

    float t = origin_to_point_distance / ray_incidence_angle;

    if (t < 0) {
        return false;
    }

    return true;
}

[[nodiscard]] bool hit_light_source(LightSource light_source, Ray current_ray) noexcept {
    return hit_sphere(light_source.shape, current_ray);
}
} // namespace plymorth