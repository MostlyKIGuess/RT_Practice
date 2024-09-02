#include <iostream>
#include <cmath>
#include "sdltemplate.h"

int main() {
    int width = 800;
    int height = 400;
    int centerX = width / 2;
    int centerY = height / 2;
    int radius = std::min(width, height) / 4;
    std::cout << "P3\n" << width << " " << height << "\n255\n";
    sdltemplate::sdl("Ray Tracer", width, height);
    sdltemplate::loop();
    for(int y = 0; y < height; y++) {
        for(int x = 0; x < width; x++) {
            int dx = x - centerX;
            int dy = y - centerY;
            float distance = std::sqrt(dx * dx + dy * dy);

            if (distance < radius) {
                int r = 0;
                int g = 255;
                int b = 255;
                std::cout << r << " " << g << " " << b << "\n";
                sdltemplate::setDrawColor(sdltemplate::createColor(r, g, b, 255));
            } else {
                int r = 0;
                int g = 0;
                int b = 0;
                std::cout << r << " " << g << " " << b << "\n";
                sdltemplate::setDrawColor(sdltemplate::createColor(r, g, b, 255));
            }
            sdltemplate::drawPoint(x, y);
        }
    }

    while(sdltemplate::running) {
        sdltemplate::loop();
    }
}