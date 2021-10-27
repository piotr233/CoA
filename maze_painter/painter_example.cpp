//
// Created by piotr on 09/10/2021.
//
#include "../path_search/path_search.h"

#include "maze_painter.h"
#include <conio.h>
#include <iostream>
#define WINDOW_SIZE 500

void MessageMe(Algorythm algorythm, size_t time, int path_length) {

  std::string maze_type;
  std::string algorithm;

  switch (algorythm) {
    case Algorythm::DIJKSTRA: algorithm = "Dijkstra"; break;
    case Algorythm::A_STAR: algorithm = "A*\t"; break;
    case Algorythm::RANDOM_WALK: algorithm = "Random Walk"; break;
    case Algorythm::RIGHT_HAND_RULE: algorithm = "Right Hand Rule"; break;
  }
  std::cout << "\talgorithm: " << algorithm << "\ttime:" << time << "us\t"
            << "path length: " << path_length << "\n";
}

#define T_START std::chrono::high_resolution_clock::now()
#define T_RECORD(t_1) std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - (t_1)).count()

class Generator {
 public:
  Generator(std::pair<Plane, Algorythm> &settings, Window &window, const ColorScheme &color_scheme) {

    generator_thread_ = new std::thread(&Generator::MainLoop, this, std::ref(settings), std::ref(window), color_scheme);
  };

  void MainLoop(std::pair<Plane, Algorythm> &settings, Window &window, ColorScheme color_scheme) {
    std::chrono::steady_clock::time_point t_1;
    double time;

    std::unique_ptr<GraphBase> engine;

    switch (settings.second) {
      case Algorythm::DIJKSTRA: engine = std::move(std::unique_ptr<GraphBase>(new Dijkstra(settings.first))); break;
      case Algorythm::A_STAR: engine = std::move(std::unique_ptr<GraphBase>(new AStar(settings.first))); break;
      case Algorythm::RANDOM_WALK: engine = std::move(std::unique_ptr<GraphBase>(new RandomWalk(settings.first))); break;
      case Algorythm::RIGHT_HAND_RULE: engine = std::move(std::unique_ptr<GraphBase>(new RHR(settings.first))); break;
    }

    auto path = engine->FindPath(window, color_scheme);
    t_1 = T_START;
    engine->FindPath();
    time = T_RECORD(t_1);
    MessageMe(settings.second, time, path.size());
  };

  ~Generator() {
    generator_thread_->join();
    delete generator_thread_;
  }

  std::thread *generator_thread_;
};

void GlobalVisuals(std::vector<std::pair<Plane, Algorythm>> &settings) {

  std::vector<Window *> windows;
  windows.reserve(settings.size());
  std::vector<Generator> generators;
  generators.reserve(settings.size());

  ColorScheme color_scheme;
  color_scheme.LoadGreenSet();

  for (int i = 0; i < settings.size(); ++i) {

    windows.push_back(new Window({{i * WINDOW_SIZE, 0}, WINDOW_SIZE, WINDOW_SIZE}));

    generators.emplace_back(settings[i], *windows[i], color_scheme);
  }
}
int main() {

  MazePainter maze(800, 800, 20, 20);
  maze.MainLoop();
  maze.GetPlane().SaveToFile("../saved_mazes/test.txt");

  std::vector<std::pair<Plane, Algorythm>> settings = {{maze.GetPlane(), Algorythm::A_STAR}};

  GlobalVisuals(settings);
  getch();

  return 0;
}