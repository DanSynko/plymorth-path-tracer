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

import constants;
import linear_algebra;
import path_tracing_objects;

int main() {
	std::println("Hello, world!");

    std::vector<plymorth::Color> frame_buffer(screen_width * screen_height);

	plymorth::Vec3 camera{};
	plymorth::Sphere sphere{};
    plymorth::Plane plane{};
    plymorth::LightSource light_source{};

	for (int x = 0; x < screen_width; ++x) {
        for (int y = 0; y < screen_height; ++y) {
            auto [x_cam, y_cam] = plymorth::raster_to_camera(x, y);

            plymorth::Ray primary_ray = {
				camera, 
				{x_cam, y_cam, -1.0f}
			};
            primary_ray.direction = plymorth::normalize(primary_ray.direction);

            bool hit = plymorth::hit_sphere(sphere, primary_ray);
			if (hit) {
	            frame_buffer[y * screen_width + x] = sphere.color;
                continue;
			}

            hit = plymorth::hit_plane(plane, primary_ray);
            if (hit) {
                frame_buffer[y * screen_width + x] = plane.color;
                continue;
            }

            hit = plymorth::hit_light_source(light_source, primary_ray);
            if (hit) {
                frame_buffer[y * screen_width + x] = light_source.emission_color;
            }
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