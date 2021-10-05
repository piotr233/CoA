//
// Created by piotr on 05/10/2021.
//

#ifndef COA_SFML_WINDOW_WINDOW_PLANE_H_
#define COA_SFML_WINDOW_WINDOW_PLANE_H_

#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Window/Event.hpp"

#include "../plane/plane.h"
#include "../sample_algorithm/cell.h"
#include "SFML/Graphics/RectangleShape.hpp"

/// glorified pixel array
/// those pixels can be huge basically, and multi-colored
/// but mostly rainbow coz I like rainbow

/// also this class is a simple way to communicate between window and all those different plane objects
class WindowPlane {
 public:
  WindowPlane() = delete;
  WindowPlane(const Plane &plane);
  WindowPlane(int width, int height) : width_(width), height_(height) { grid_.reserve(height_ * width_); }
  WindowPlane(const std::vector<Cell> &plane);
  WindowPlane(const WindowPlane &other) = default;
  WindowPlane &operator=(const WindowPlane &other) = default;

  void HighlightCells(const std::vector<Cell> &plane, sf::Color highlight_color = sf::Color(33, 255, 211));
  void DrawToWindow(sf::RenderWindow &window);

 protected:
  /// x axis
  unsigned width_;
  /// y axis
  unsigned height_;

  std::vector<sf::Color> grid_;
};

#endif//COA_SFML_WINDOW_WINDOW_PLANE_H_
