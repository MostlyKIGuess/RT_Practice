#include <iostream>
#include <cmath>
#include "sdltemplate.h"

struct Vec3 {
    float x, y, z;
    Vec3(float x, float y, float z) : x(x), y(y), z(z) {}
    Vec3 operator-(const Vec3& v) const { return Vec3(x - v.x, y - v.y, z - v.z); }
    Vec3 operator+(const Vec3& v) const { return Vec3(x + v.x, y + v.y, z + v.z); }
    Vec3 operator*(float t) const { return Vec3(x * t, y * t, z * t); }
    float dot(const Vec3& v) const { return x * v.x + y * v.y + z * v.z; }
    Vec3 normalize() const {
        float mag = std::sqrt(x * x + y * y + z * z);
        return Vec3(x / mag, y / mag, z / mag);
    }
};

int main() {
    int width = 1280;
    int height = 720;
    Vec3 sphere_center(width / 2, height / 2, 50);
    float sphere_radius = std::min(width, height) / 4;
    Vec3 light_dir = Vec3(1, -1, -1).normalize();

    std::cout << "P3\n" << width << " " << height << "\n255\n";
    sdltemplate::sdl("Ray Tracer", width, height);
    sdltemplate::loop();

    for(int y = 0; y < height; y++) {
        for(int x = 0; x < width; x++) {
            float t = static_cast<float>(y) / height;
            int bg_r = static_cast<int>((1.0 - t) * 70 + t * 135);
            int bg_g = static_cast<int>((1.0 - t) * 130 + t * 206);
            int bg_b = static_cast<int>((1.0 - t) * 180 + t * 235);

             


            Vec3 pixel_pos(x, y, 0);
            Vec3 sphere_to_pixel = pixel_pos - sphere_center;
            float dist = sphere_to_pixel.dot(sphere_to_pixel);

            if (dist < sphere_radius * sphere_radius) {
                float z = std::sqrt(sphere_radius * sphere_radius - sphere_to_pixel.x * sphere_to_pixel.x - sphere_to_pixel.y * sphere_to_pixel.y);
                Vec3 normal = Vec3(sphere_to_pixel.x, sphere_to_pixel.y, z).normalize();
                float light_intensity = std::max(0.1f, normal.dot(light_dir));

                int sphere_r = static_cast<int>(208 * light_intensity);
                int sphere_g = static_cast<int>(50 * light_intensity);
                int sphere_b = static_cast<int>(128 * light_intensity);

                // int r = (sphere_r - bg_r) / 2;
                // int g = (sphere_g - bg_g) / 2;
                // int b = (sphere_b - bg_b) / 2;

                // int r = (sphere_r + bg_r) / 2;
                // int g = (sphere_g + bg_g) / 2;
                // int b = (sphere_b + bg_b) / 2;


                int r = sphere_r ;
                int g = sphere_g;
                int b = sphere_b;

                std::cout << r << " " << g << " " << b << "\n";
                sdltemplate::setDrawColor(sdltemplate::createColor(r, g, b, 255));
            } else {
                std::cout << bg_r << " " << bg_g << " " << bg_b << "\n";
                sdltemplate::setDrawColor(sdltemplate::createColor(bg_r, bg_g, bg_b, 255));
            }
            sdltemplate::drawPoint(x, y);
        }
    }

    while(sdltemplate::running) {
        sdltemplate::loop();
    }
}