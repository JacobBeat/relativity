// Relativistic 3-vectors, all components assumed contravariant
class vec3 {
public:
  static constexpr double c = 1.0;
  double x;
  double y;
  double t;

  vec3 operator+(const vec3 &v) { return {x + v.x, y + v.y, t + v.t}; }
  vec3 operator-(const vec3 &v) { return {x - v.x, y - v.y, t - v.t}; }
  vec3 operator*(const vec3 &v) { return {x * v.x, y * v.y, t * v.t}; }
  vec3 operator/(const vec3 &v) { return {x / v.x, y / v.y, t / v.t}; }
  vec3 &operator+=(const vec3 &v) {
    x += v.x;
    y += v.y;
    t += v.t;
    return *this;
  }

  double lensq();
};

double dot(vec3 v1, vec3 v2);
