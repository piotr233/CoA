//
// Created by piotr on 05/10/2021.
//

#include "window_plane.h"
WindowPlane::WindowPlane(const Plane &plane) : width_(plane.GetWidth()), height_(plane.GetHeight()) {
  grid_.reserve(width_ * height_);

  for (int x = 0; x < width_; x++)
    for (int y = 0; y < height_; y++) {
      switch (plane.GetCell({x, y})) {
        case CellType::EMPTY:
          grid_.emplace_back(58, 58, 58);
          break;
        case CellType::WALL:
          grid_.emplace_back(21, 5, 78);
          break;
        case CellType::START:
          grid_.emplace_back(0, 0, 0);
          break;
        case CellType::FINISH:
          grid_.emplace_back(255, 178, 71);
          break;
      }
    }
}
void WindowPlane::DrawToWindow(sf::RenderWindow &window) {
  unsigned window_height = window.getSize().y;
  unsigned window_width = window.getSize().x;

  float cell_width = window_width / width_;
  float cell_height = window_height / height_;

  float cell_size = cell_height < cell_width ? cell_height : cell_width;

  std::vector<sf::RectangleShape> display;
  display.reserve(width_ * height_);

  sf::RectangleShape square;
  square.setSize(sf::Vector2f(cell_size, cell_size));
  square.setOutlineThickness(0);

  int x_pixel_shift = (window_width - (width_ * cell_size)) / 2;
  int y_pixel_shift = (window_height - (height_ * cell_size)) / 2;

  for (int x = 0; x < width_; x++)
    for (int y = 0; y < height_; y++) {
      square.setFillColor(grid_[Coord(x, y).ToInt(width_)]);
      square.setPosition(x_pixel_shift + x * cell_size, y_pixel_shift + y * cell_size);
      window.draw(square);
    }
}
WindowPlane::WindowPlane(const std::vector<Cell> &plane, int width, int height) : width_(width), height_(height) {
  for (int x = 0; x < width_; x++)
    for (int y = 0; y < height_; y++) {
      switch (plane[x * width + y].cell_type) {
        case CellType::EMPTY:

          if (plane[x * width + y].distance == CELL_MAX)
            grid_.emplace_back(colorscheme_.background);
          else
            grid_.emplace_back(colorscheme_.discovered);
          break;
        case CellType::WALL:

          grid_.emplace_back(colorscheme_.wall);
          break;
        case CellType::START:
          grid_.emplace_back(colorscheme_.start);
          break;
        case CellType::FINISH:
          grid_.emplace_back(colorscheme_.finish);
          break;
      }
    }
}
void WindowPlane::HighlightCells(const std::vector<Coord> &plane, sf::Color highlight_color) {
  if (highlight_color == sf::Color(0, 0, 0))

    highlight_color = colorscheme_.point_of_interest;

  for (auto &c : plane) {
    grid_[c.ToInt(width_)] = highlight_color;
  }
}
WindowPlane::WindowPlane(const std::vector<Cell> &plane, int width, int height, const ColorScheme& color_scheme) : width_(width), height_(height),colorscheme_(color_scheme) {

  for (int x = 0; x < width_; x++)
    for (int y = 0; y < height_; y++) {
      switch (plane[x * width + y].cell_type) {
        case CellType::EMPTY:

          if (plane[x * width + y].distance == CELL_MAX)
            grid_.emplace_back(colorscheme_.background);
          else
            grid_.emplace_back(colorscheme_.discovered);
          break;
        case CellType::WALL:

          grid_.emplace_back(colorscheme_.wall);
          break;
        case CellType::START:
          grid_.emplace_back(colorscheme_.start);
          break;
        case CellType::FINISH:
          grid_.emplace_back(colorscheme_.finish);
          break;
      }
    }
}
