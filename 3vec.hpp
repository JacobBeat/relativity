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

  vec3(double x_, double y_, double z_);
};

double dot(vec3 v1, vec3 v2);
