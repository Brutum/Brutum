#ifndef GAME_HPP
#define GAME_HPP

#include <stack>

#include <SFML/Graphics.hpp>

class GameState;

/**
 * Manages the SFML window and switching between game states.
 */
class Game {

private:
  sf::RenderWindow window;

  std::stack<GameState*> states;

public:

  Game();
  ~Game();

  // game state related
  void push_state(GameState* state);
  void pop_state();
  void change_state(GameState* state);
  void draw(const float dt);

  void game_loop();
};

#endif // GAME_HPP
