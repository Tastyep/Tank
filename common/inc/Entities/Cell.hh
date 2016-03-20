#ifndef TANK_CELL_HH
#define TANK_CELL_HH

#include <vector>

template <typename T> class Cell {
public:
  Cell();

  ~Cell() = default;
  Cell(const Cell &other) = default;
  Cell(Cell &&other) = default;
  Cell &operator=(const Cell &other) = default;
  Cell &operator=(Cell &&other) = default;

private:
  std::vector<T> data;
};

#endif /* end of include guard: TANK_CELL_HH */
