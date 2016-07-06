#include <stack>

#include <SFML/Graphics.hpp>

#include "game.hpp"
#include "game_state.hpp"

/**
 * Constructor.
 */
Game::Game() {
  // TODO: add parameters to change settings
  window.create(sf::VideoMode::getDesktopMode(), "Brutum", sf::Style::Fullscreen);
  window.setFramerateLimit(60);
}

/**
 * Destructor.
 */
Game::~Game() {
  while (!states.empty()) {
    pop_state();
  }
}

/**
 * Pushes another state in the stack.
 */
void Game::push_state(GameState* state) {
  states.push(state);
}

/**
 * Pops a game state.
 */
void Game::pop_state() {
  delete states.top();
  states.pop();
}

/**
 * Changes the current state to the given state.
 */
void Game::change_state(GameState* state) {
  if (!states.empty()) {
    pop_state();
  }
  push_state(state);
}

/**
 * The main game loop.
 */
void Game::game_loop() {
  sf::Clock clock;

  while (window.isOpen()) {
    float dt = clock.restart().asSeconds();

    sf::Event event;

    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
      else {
        if (!states.empty()) {
          states.top()->handle_event();
        }
      }
    }

    if (!states.empty()) {
      states.top()->update(dt);
    }
    window.clear(sf::Color::Black);
    if (!states.empty()) {
      states.top()->draw(dt);
    }
    window.display();
  }
}
