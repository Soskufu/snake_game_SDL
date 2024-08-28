#pragma once
class Config {
public:
    static constexpr int CELL_SIZE = 30; // Or compute based on window width
    static constexpr float SNAKE_BASE_SPEED = 0.2f;
    static constexpr float SNAKE_MAX_SPEED = 0.02f;
    static constexpr float SPEED_BUMP = 0.005f;

    enum Directions { Up = 1, Down, Left, Right };
};