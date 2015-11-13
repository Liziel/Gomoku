//
// Created by collio_v on 11/10/15.
//

#include <bits/stl_pair.h>
#include <iostream>
#include "referee/Referee.hh"

static const std::array< referee::Piece::Position, 8> directions({
    referee::Piece::Position{ 0, -1},
    referee::Piece::Position{ 0,  1},

    referee::Piece::Position{ 1, -1},
    referee::Piece::Position{-1,  1},

    referee::Piece::Position{-1,  0},
    referee::Piece::Position{ 1,  0},

    referee::Piece::Position{-1, -1},
    referee::Piece::Position{ 1,  1}
});

bool referee::Referee::double_three_rule(const Piece::Position& position)
{
  int     direction_identifier(0);

  for (const auto& oth : directions) {
    if (this->m_board[oth+position].is_empty()) {
      if (not this->m_board[oth*2 + position].is_empty()) {
        if (this->m_board[oth*2+ position].is_same_color(m_turn)) {
          if (this->m_board[oth*3 + position].is_empty()) {
            this->m_board[oth*3 + position].mark_for(m_turn, direction_identifier / 2);
            this->m_board[oth + position].mark_for(m_turn, direction_identifier / 2);
            this->m_board[-oth + position].mark_for(m_turn, direction_identifier / 2);
          } else
          if (this->m_board[oth*3 + position].is_same_color(m_turn)) {
            this->m_board[oth*3 + position].unmark_for(m_turn, direction_identifier / 2);
            this->m_board[oth + position].unmark_for(m_turn, direction_identifier / 2);
            this->m_board[-oth + position].unmark_for(m_turn, direction_identifier / 2);

            this->m_board[position].mark_for(m_turn, direction_identifier / 2);
            this->m_board[oth*2 + position].mark_for(m_turn, direction_identifier / 2);
            this->m_board[oth*3 + position].mark_for(m_turn, direction_identifier / 2);
          }
        }
        continue;
      }
    } else
    if (this->m_board[oth+position].is_same_color(m_turn)) {
      if (this->m_board[oth * 2 + position].is_same_color(m_turn)) {
        this->m_board[-oth + position].unmark_for(m_turn, direction_identifier / 2);
        this->m_board[oth*3 + position].unmark_for(m_turn, direction_identifier / 2);
        this->m_board[oth*4 + position].unmark_for(m_turn, direction_identifier / 2);

        this->m_board[oth + position].mark_for(m_turn, direction_identifier / 2);
        this->m_board[oth*2 + position].mark_for(m_turn, direction_identifier / 2);
      } else
      if (this->m_board[oth*2+position].is_empty()) {
        this->m_board[-oth + position].mark_for(m_turn, direction_identifier / 2);
        this->m_board[-oth*2 + position].mark_for(m_turn, direction_identifier / 2);
        this->m_board[oth*2 + position].mark_for(m_turn, direction_identifier / 2);
        this->m_board[oth*3 + position].mark_for(m_turn, direction_identifier / 2);
      }
    }
    ++direction_identifier;
  }
  return false;
}

bool referee::Referee::place_at(const Piece::Position& position)
{
  if (!m_board[position].can_pose(m_turn))
    return false;
  if (double_three_rule(position))
    return false;

  board()[position].set_identity(m_turn);

  if (m_turn == Piece::identity::black)
    m_turn = Piece::identity::white;
  else
    m_turn = Piece::identity::black;

  return true;
}

referee::Referee::Referee(referee::game::Ia* white, referee::game::Ia* black)
    : m_turn(referee::Piece::identity::white), m_win(referee::Piece::identity::none), m_white(white), m_black(black) {}

bool referee::Referee::can_pose(const referee::Piece::Position& position)
{
  referee::Piece& piece(m_board[position]);

  if (m_turn == Piece::identity::white) {
    std::array<int, Piece::alignements_count>::iterator it;
    it = std::find_if(piece.m_white_three_alignement.begin(), piece.m_white_three_alignement.end(), [](int p){return p > 0;});
    if (it != std::end(piece.m_white_three_alignement)
        && std::find_if(it + 1, piece.m_white_three_alignement.end(), [](int p){return p > 0;}) != std::end(piece.m_white_three_alignement))
      return false;

    if (piece.is_three_white_aligned()) {

    }

  } else {
    std::array<int, Piece::alignements_count>::iterator it;
    it = std::find_if(piece.m_black_three_alignement.begin(), piece.m_black_three_alignement.end(), [](int p){return p > 0;});
    if (it != std::end(piece.m_black_three_alignement)
        && std::find_if(it + 1, piece.m_black_three_alignement.end(), [](int p){return p > 0;}) != std::end(piece.m_black_three_alignement))
      return false;



  }
  return true;
}
