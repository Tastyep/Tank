#ifndef UTILS_HH_
#define UTILS_HH_

class Utils {
public:
  Utils();

  ~Utils() = default;
  Utils(const Utils &other) = default;
  Utils(Utils &&other) = default;
  Utils &operator=(const Utils &other) = default;
  Utils &operator=(Utils &&other) = default;

  static constexpr auto pi = std::acos(-1);
};

#endif /* end of include guard: UTILS_HH_ */
