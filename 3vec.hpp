// 2-d vector for purely spatial components
struct vec2 {
  double x;
  double y;

  vec2 operator+(const vec2 &v) { return {x + v.x, y + v.y}; }
  vec2 operator-(const vec2 &v) { return {x - v.x, y - v.y}; }
  vec2 operator*(double s) { return {x * s, y * s}; }
  vec2 operator/(double s) { return {x / s, y / s}; }
  vec2 &operator+=(const vec2 &v) {
    x += v.x;
    y += v.y;
    return *this;
  }

  double lensq();

  vec2(double x_, double y_);
};

// Relativistic 3-vectors, all components assumed contravariant
struct vec3 {
  static constexpr double c = 1.0;
  double x;
  double y;
  double t;

  vec3 operator+(const vec3 &v) { return {x + v.x, y + v.y, t + v.t}; }
  vec3 operator-(const vec3 &v) { return {x - v.x, y - v.y, t - v.t}; }
  vec3 operator*(double s) { return {x * s, y * s, t * s}; }
  vec3 operator/(double s) { return {x / s, y / s, t / s}; }
  vec3 &operator+=(const vec3 &v) {
    x += v.x;
    y += v.y;
    t += v.t;
    return *this;
  }

  double lensq();

  vec3(double x_, double y_, double t_);
};

double dot(vec2 v1, vec2 v2);
double dot(vec3 v1, vec3 v2);
