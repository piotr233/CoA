//
// Created by piotr on 04/10/2021.
//

#include "plane.h"
Plane::Plane(const Plane &other) {
  width_ = other.width_;
  height_ = other.width_;

  for (auto &c : other.plane_)
    plane_.emplace_back(c);
}
Plane &Plane::operator=(const Plane &other) {
  if (&other == this) return *this;
  width_ = other.width_;
  height_ = other.width_;

  for (auto &c : other.plane_)
    plane_.emplace_back(c);

  return *this;
}
CellState Plane::GetCell(const Coord &position) const {
  return plane_[position.ToInt(width_)];
}
void Plane::SetCell(const Coord &position, const CellState value) {
  plane_[position.ToInt(width_)] = value;
}
unsigned int Plane::GetWidth() const {
  return width_;
}
unsigned int Plane::GetHeight() const {
  return height_;
}
Plane::Plane(unsigned int width, unsigned int height) : width_(width), height_(height) {
  int threshold = 10;
  plane_.reserve(width * height);

  for (int i = 0; i < width * height; i++)
    if (rand() % 100 < threshold)
      plane_.emplace_back(CellState::WALL);
    else
      plane_.emplace_back(CellState::EMPTY);
}
void Plane::AddBorder() {
  //vertical top
  for (int x = 0; x < GetWidth(); x++)
    SetCell({x, 0}, CellState::WALL);

  //vertical bottom
  for (int x = 0; x < GetWidth(); x++)
    SetCell({x, (int) GetHeight() - 1}, CellState::WALL);

  // left edge
  for (int y = 0; y < GetHeight(); y++)
    SetCell({0, y}, CellState::WALL);

  // right ege
  for (int y = 0; y < GetHeight(); y++)
    SetCell({(int)GetWidth()-1, y}, CellState::WALL);
}
