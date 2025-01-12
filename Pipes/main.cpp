#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "sdltemplate.h"

struct Vec2 {
    int x, y;
    Vec2(int x, int y) : x(x), y(y) {}
    Vec2 operator+(const Vec2& v) const { return Vec2(x + v.x, y + v.y); }
};

enum Direction { UP, DOWN, LEFT, RIGHT };

struct Pipe {
    Vec2 position;
    Direction direction;
    SDL_Color color;
    Pipe(Vec2 pos, Direction dir, SDL_Color col) : position(pos), direction(dir), color(col) {}
};

SDL_Color randomColor() {
    return SDL_Color{static_cast<Uint8>(std::rand() % 256), static_cast<Uint8>(std::rand() % 256), static_cast<Uint8>(std::rand() % 256), 255};
}

int main() {
    int width = 1280;
    int height = 720;
    int pipe_length = 120;
    int pipe_thickness = 30;
    std::vector<Pipe> pipes;

    for (int i = 0; i < 10; ++i) {
        pipes.push_back(Pipe(Vec2(std::rand() % width, std::rand() % height), static_cast<Direction>(std::rand() % 4), randomColor()));
    }

    std::srand(std::time(0));

    sdltemplate::sdl("Pipes Screensaver", width, height);
    sdltemplate::loop();

    while (sdltemplate::running) {
        sdltemplate::begin_render();
        sdltemplate::setDrawColor(sdltemplate::createColor(0, 0, 0, 255));
        SDL_RenderClear(sdltemplate::renderer);

        for (auto& pipe : pipes) {
            sdltemplate::setDrawColor(pipe.color);
            SDL_Rect rect;
            rect.w = pipe_thickness;
            rect.h = pipe_thickness;

            switch (pipe.direction) {
                case UP:
                    rect.x = pipe.position.x - pipe_thickness / 2;
                    rect.y = pipe.position.y - pipe_length;
                    rect.h = pipe_length;
                    pipe.position.y -= pipe_length;
                    break;
                case DOWN:
                    rect.x = pipe.position.x - pipe_thickness / 2;
                    rect.y = pipe.position.y;
                    rect.h = pipe_length;
                    pipe.position.y += pipe_length;
                    break;
                case LEFT:
                    rect.x = pipe.position.x - pipe_length;
                    rect.y = pipe.position.y - pipe_thickness / 2;
                    rect.w = pipe_length;
                    pipe.position.x -= pipe_length;
                    break;
                case RIGHT:
                    rect.x = pipe.position.x;
                    rect.y = pipe.position.y - pipe_thickness / 2;
                    rect.w = pipe_length;
                    pipe.position.x += pipe_length;
                    break;
            }

            SDL_RenderFillRect(sdltemplate::renderer, &rect);

            SDL_Color shade = {static_cast<Uint8>(pipe.color.r / 2), static_cast<Uint8>(pipe.color.g / 2), static_cast<Uint8>(pipe.color.b / 2), 255};
            sdltemplate::setDrawColor(shade);
            SDL_Rect shade_rect = rect;
            shade_rect.x += 2;
            shade_rect.y += 2;
            SDL_RenderFillRect(sdltemplate::renderer, &shade_rect);

            if (std::rand() % 4 == 0) {
                pipe.direction = static_cast<Direction>(std::rand() % 4);
            }
        }

        sdltemplate::end_render();
        SDL_Delay(100); 
        sdltemplate::loop();
    }

    sdltemplate::quit();
    return 0;
}