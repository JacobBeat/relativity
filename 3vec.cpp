#include "3vec.hpp"
#include <cmath>

vec2::vec2(double x_, double y_) : x(x_), y(y_) {}
vec3::vec3(double x_, double y_, double t_) : x(x_), y(y_), t(t_) {}

double dot(vec2 v1, vec2 v2) { return (v1.x * v2.x) + (v1.y * v2.y); }
double dot(vec3 v1, vec3 v2) {
  return (std::pow(vec3::c, 2.0) * v1.t * v2.t) - (v1.x * v2.x) - (v1.y * v2.y);
}

double vec2::lensq() { return dot(*this, *this); }
double vec3::lensq() { return dot(*this, *this); }
