//
// main.cpp for gomoku in /home/terran_j/rendu/ia_gomoku
//
// Made by terran_j
// Login   <terran_j@epitech.net>
//
// Started on  Tue Oct 27 11:16:54 2015 terran_j
// Last update Thu Nov 26 20:03:54 2015 terran_j
//

#include <thread>
#include "graphics/sfml.hh"
#include "referee/Referee.hh"
#include "IAminmax/IAminmax.hh"

int	main()
{
  SFML *lib = new SFML();
  sf::Vector2i position;
  sf::Vector2i gridPos;

  XInitThreads();
  if (lib->initLib(WIDTH, HEIGHT) == -1)
    return (-1);

  lib->startMenu();
  lib->endMenu();

  referee::Referee* _referee;
  if (lib->IsAI) {
    IAminmax* iAminmax;
    _referee = new referee::Referee(new game::Player(referee::Piece::identity::black), iAminmax = new IAminmax(referee::Piece::identity::white));
    iAminmax->setReferee(_referee);
  }
  else
    _referee = new referee::Referee();

  // boucle de jeu:
  while (lib->window().isOpen()) {
    sf::Event e;
    while ( (_referee->win() == referee::Piece::identity::none && !_referee->human_turn()) || lib->window().pollEvent(e)) {
      if (_referee->win() == referee::Piece::identity::none && !_referee->human_turn()) {
        _referee->ia_place();
        lib->refreshImg(_referee->board(),
                        _referee->getMTurn(),
                        _referee->white_player().taken(), _referee->black_player().taken(),
                        _referee->win());
      }
      else if (e.type == sf::Event::MouseButtonPressed) {
        position = lib->getPosition();
        gridPos = lib->pixelToBoardPos(position);
        if (gridPos.x!=-1 and gridPos.y!=-1) {
          // envoyer gridPos a lyoko ici:
          _referee->place_at(referee::Piece::Position({gridPos.x, gridPos.y}));
          // puis si il confirme que c'est good il me renvoie la map completée

          // puis j'affiche la map dans refresh image:
          lib->refreshImg(_referee->board(),
                          _referee->getMTurn(),
                          _referee->white_player().taken(), _referee->black_player().taken(),
                          _referee->win());
        }
      } else
      if (e.type == sf::Event::Closed)
        lib->closeLib();
      else
      if (e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::Key::Escape)
        lib->closeLib();
    }
  }
  return (0);
}
