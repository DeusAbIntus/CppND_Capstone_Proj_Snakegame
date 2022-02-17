#include "game.h"
#include <iostream>
#include "SDL.h"

Game::Game(std::size_t grid_width, std::size_t grid_height)
    : //snakeA(grid_width, grid_height, 0.75, 0.5),
      //snakeB(grid_width, grid_height, 0.25, 0.5),
      engine(dev()),
      random_w(0, static_cast<int>(grid_width - 1)),
      random_h(0, static_cast<int>(grid_height - 1)) {
  PlaceFood();
  //players.clear();
  for (int i = 1; i < 3; i++)
  {
    if (i == 2) { 
        //Snake snake(grid_width, grid_height, 0.75, 0.5);
        this->players.emplace_back(new Snake(grid_width, grid_height, 0.75, 0.5));
      }
    else 
      { 
        //Snake snake(grid_width, grid_height, 0.25, 0.5);
        this->players.emplace_back(new Snake(grid_width, grid_height, 0.25, 0.5)); 
      }
  }
  
}

void Game::Run(Controller const &controller, Renderer &renderer,
               std::size_t target_frame_duration) {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true;

  while (running) {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    controller.HandleInput(running, players);
    Update();
    renderer.Render(players[0], players[1], food);

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      renderer.UpdateWindowTitle(players[0].GetScore(), frame_count);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }
}

void Game::PlaceFood() {
  int x, y;
  while (true) {
    x = random_w(engine);
    y = random_h(engine);
    // Check that the location is not occupied by a snake item before placing
    // food.
    if (!players[0].SnakeCell(x,y) && !players[1].SnakeCell(x, y)) {
      food.x = x;
      food.y = y;
      return;
    }
  }
}

void Game::Update() {
  for (auto p : players)
  {
  if (!p.alive) return;
  p.Update();
  }

  for (auto p : players){

    int new_x = static_cast<int>(p.head_x);
    int new_y = static_cast<int>(p.head_y);

    // Check if there's food over here
    if (food.x == new_x && food.y == new_y) {
      p.IncrementScore();
      PlaceFood();
      // Grow snake and increase speed.
      p.GrowBody();
      //snake.speed += 0.02;
    }
  }
}
 /* // NEW - Update cycle for Snake B ////////////////////////
  if (snakeB.alive){
    snakeA.Update();

    int new2_x = static_cast<int>(snakeB.head_x);
    int new2_y = static_cast<int>(snakeB.head_y);

    // Check if there's food over here
    if (food.x == new2_x && food.y == new2_y) {
      snakeB.IncrementScore();
      PlaceFood();
      // Grow snake and increase speed.
      snakeB.GrowBody();
      //snake.speed += 0.02;
    }
  }
*/


int Game::GetScore() const { return players[0].GetScore(); } // CHANGE - Score attribute tranfered to Snake Class 
int Game::GetSize() const { return players[1].size; }