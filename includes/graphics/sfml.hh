//
// sfml.hh for gomoku in /home/terran_j/rendu/ia_gomoku
//
// Made by terran_j
// Login   <terran_j@epitech.net>
//
// Started on  Tue Oct 27 11:21:22 2015 terran_j
// Last update Thu Nov 26 20:40:44 2015 terran_j
//

#ifndef SFML_HH__
# define SFML_HH__

#include <map>
#include <list>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <X11/Xlib.h>
#include <iostream>

#include "referee/Piece.hh"

#define WIDTH 1500
#define HEIGHT 1000

class SFML;

namespace referee { class Board; }

class SFML
{
public:
  SFML();
  ~SFML();

  SFML &operator=(SFML const &) = default;
  SFML(const SFML &) = default;
  SFML(SFML &&) = default;

  void startMenu();
  void endMenu();
  int initLib(unsigned int x, unsigned int y);
  void refreshImg(referee::Board&, referee::Piece::identity, int white_points, int black_points, referee::Piece::identity);
  void affScores(const std::string &toAff, unsigned int x, unsigned int y);
  void affScoreWhite(const std::string &toAff, unsigned int x, unsigned int y);
  void affScoreBlack(const std::string &toAff, unsigned int x, unsigned int y);
  void affVictory(const std::string &toAff, unsigned int x, unsigned int y);
  void affPlayerTurn(const std::string &toAff, unsigned int x, unsigned int y);
  void closeLib();
  sf::Vector2i getPosition();
  sf::Vector2i pixelToBoardPos(sf::Vector2i position);
  sf::Vector2i XYToPixels(int x, int y);
  void putWhite(sf::Vector2i pos);
  void putBlack(sf::Vector2i pos);

  inline sf::RenderWindow& window() { return *_window; };
  sf::Music *_music;

private:
  sf::RenderWindow *_window;
  int _x;
  int _y;
  sf::Sprite _background;
  sf::Sprite _background2;
  sf::Sprite _white;
  sf::Sprite _black;
  sf::Text _scores;
  sf::Text _scoreWhite;
  sf::Text _scoreBlack;
  sf::Text _victory;
  sf::Text _playerTurn;

public:
  bool IsSound;
  bool SoundIsHere;
  bool IsAI;
  bool AreExtraRules;
};

#endif
