#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

int main()
{
  sf::RenderWindow window(sf::VideoMode(800,600), "window");

  sf::Event event;
  while(window.pollEvent(event))
  {
    if(event.type == sf::Event::Closed)
      window.close();
  }


  window.display();
}

// #include "GameManager.h"

// int main() {
//   sf::RenderWindow window(sf::VideoMode({800, 600}), "My window");
//     // GameManager game;
//     // game.run();
//     // return 0;
// }
