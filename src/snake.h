#ifndef SNAKE_H
#define SNAKE_H

#include <vector>
#include "SDL.h"

class Snake {
 public:
  enum class Direction { kUp, kDown, kLeft, kRight };

  Snake(int grid_width, int grid_height, float x_pos, float y_pos) // CHANGE - added x_pos and y_pos arguments to constructor
      : grid_width(grid_width),                                    // to control the starting position of snake
        grid_height(grid_height),
        head_x(grid_width * x_pos),
        head_y(grid_height * y_pos) {}

  void Update();

  void GrowBody();
  bool SnakeCell(int x, int y);
  int GetScore() const; // NEW - Getter function for score
  void IncrementScore(); // NEW - Helper function to increase score

  Direction direction = Direction::kUp;

  float speed{0.1f};
  int size{1};
  bool alive{true};
  float head_x;
  float head_y;
  std::vector<SDL_Point> body;

 private:
  void UpdateHead();
  void UpdateBody(SDL_Point &current_cell, SDL_Point &prev_cell);

  bool growing{false};
  int grid_width;
  int grid_height;
  int score{0}; // New - Score now a member of Class Snake
};

#endif