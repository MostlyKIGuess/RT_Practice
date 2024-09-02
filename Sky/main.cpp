#include <iostream>
#include <cmath>
#include "sdltemplate.h"

int main() {
    int width = 800;
    int height = 400;

    std::cout << "P3\n" << width << " " << height << "\n255\n";
    sdltemplate::sdl("Ray Tracer", width, height);
    sdltemplate::loop();

    for(int y = 0; y < height; y++) {
        for(int x = 0; x < width; x++) {
            float t = static_cast<float>(y) / height;
            int r = static_cast<int>((1.0 - t) * 70 + t * 135); 
            int g = static_cast<int>((1.0 - t) * 130 + t * 206); 
            int b = static_cast<int>((1.0 - t) * 180 + t * 235); 
            std::cout << r << " " << g << " " << b << "\n";
            sdltemplate::setDrawColor(sdltemplate::createColor(r, g, b, 255));
            sdltemplate::drawPoint(x, y);
        }
    }

    while(sdltemplate::running) {
        sdltemplate::loop();
    }
}