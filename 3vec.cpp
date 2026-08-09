#include "3vec.hpp"
#include <cmath>

vec3::vec3(double x_, double y_, double t_) : x(x_), y(y_), t(t_) {}

double vec3::lensq() {
  return ((std::pow(c, 2.0) * std::pow(t, 2.0)) - std::pow(x, 2.0) -
          std::pow(y, 2.0));
}

double dot(vec3 v1, vec3 v2) {
  return (std::pow(vec3::c, 2.0) * v1.t * v2.t) - (v1.x * v2.x) - (v1.y * v2.y);
}
