//
// Created by piotr on 05/10/2021.
//
#include "cell.h"
bool Cell::operator<(const Cell &rhs) const {

  return distance < rhs.distance;
}
bool Cell::operator>(const Cell &rhs) const {
  return rhs < *this;
}
bool Cell::operator<=(const Cell &rhs) const {
  return !(rhs < *this);
}
bool Cell::operator>=(const Cell &rhs) const {
  return !(*this < rhs);
}
std::ostream &operator<<(std::ostream &os, const Cell &cell) {
  switch (cell.cell_type) {

    case CellState::EMPTY: {
      if (cell.distance == CELL_MAX) {
        os << "  ";
      } else if (cell.distance < 10) {
        os << " " << cell.distance;
      } else if (cell.distance < 99) {
        os << cell.distance;
      } else {
        os << "--";
      }
    } break;
    case CellState::WALL: os << " #"; break;
    case CellState::START: os << " S"; break;
    case CellState::FINISH:
      os << " F";
      break;
  }

  return os;
}