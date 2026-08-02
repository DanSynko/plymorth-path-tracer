#ifdef __INTELLISENSE__
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <print>
#include <numbers>
#else
import std;
#endif

import linear_algebra;
import path_tracing_objects;

constexpr float screen_width = 300.0f;
constexpr float screen_height = 200.0f;
constexpr float aspect_ratio = screen_width / screen_height;
constexpr int FOV = 75;

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

int main() {
	std::println("Hello, world!");

    std::vector<plymorth::Color> frame_buffer(screen_width * screen_height);

	plymorth::Vec3 camera{};
	plymorth::Sphere sphere{};

	for (int x = 0; x < screen_width; ++x) {
        for (int y = 0; y < screen_height; ++y) {
            auto [x_cam, y_cam] = raster_to_camera(x, y);

            plymorth::Ray primary_ray = {
				camera, 
				{x_cam, y_cam, -1.0f}
			};

            primary_ray.direction = plymorth::normalize(primary_ray.direction);
            plymorth::Color current_pixel_color = plymorth::hit_sphere(sphere, primary_ray);

            frame_buffer[y * screen_width + x] = current_pixel_color;
		}
	}

    std::ofstream out("image.ppm");

    out << "P3\n" << screen_width << ' ' << screen_height << "\n255\n";
    for (const auto& current_pixel_color : frame_buffer) {
        out << current_pixel_color.r << " " 
			<< current_pixel_color.g << " " 
			<< current_pixel_color.b << "\n";
    }

	out.close();

	std::println("Image created successfully!");

	return 0;
}