#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "snake.h"

class Controller {
 public:
  //void HandleInput(bool &running, Snake &snake) const;
  //void HandleInput2(bool &running, Snake &snake) const;
  void HandleInput(bool &running, std::vector<Snake>& players) const;

 private:
  void ChangeDirection(Snake &snake, Snake::Direction input,
                       Snake::Direction opposite) const ;
};

#endif