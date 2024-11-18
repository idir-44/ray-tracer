#include "color.h"
#include "ray.h"
#include "vec3.h"
#include <cmath>
#include <iostream>

double hit_sphere(const point3 &center, double radious, point3 &o,
                  const ray &r) {
  vec3 oc = r.origin() - center;
  auto a = dot(r.direction(), r.direction());
  auto b = 2.0 * dot(oc, r.direction());
  auto c = dot(oc, oc) - radious * radious;
  auto discriminant = b * b - 4 * a * c;

  if (discriminant < 0) {
    return -1;
  } else {
    return (-b - sqrt(discriminant)) / (2.0 * a);
  }
}

color ray_color(const ray &r) {
  vec3 unit_direction = unit_vector(r.direction());
  auto a = 0.5 * (unit_direction.y() + 1.0);
  return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);
}

int main() {
  auto aspect_ratio = 16.0 / 9.0;
  int image_width = 500;

  int image_height = int(image_width / aspect_ratio);
  image_height = image_height < 1 ? 1 : image_height;

  auto focal_length = 1.0;
  auto viewport_height = 2.0;
  auto viewport_width = viewport_height * (double(image_width) / image_height);
  auto camera_center = point3(0, 0, 0);

  // Vectors across x and y axis
  auto viewport_u = vec3(viewport_width, 0, 0);
  auto viewport_v = vec3(0, viewport_height, 0);

  auto lower_left_corner = camera_center - viewport_v / 2 - viewport_u / 2 -
                           vec3(0, 0, focal_length);

  vec3 lightDir = unit_vector(vec3(-1, -1, -1));

  std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";

  for (int j = image_height - 1; j >= 0; --j) {
    std::clog << "\nScaning lines remaining: " << j << "\n";
    for (int i = 0; i < image_width; i++) {
      auto u = double(i) / (image_width - 1);
      auto v = double(j) / (image_height - 1);
      ray r(camera_center, lower_left_corner + u * viewport_u + v * viewport_v -
                               camera_center);
      auto t = hit_sphere(point3(0, 0, -1), 0.5, camera_center, r);
      color pixel_color;
      if (t > 0.0) {
        pixel_color = color(1, 0, 1);
        // the normal is p - c
        auto n_hit_point = unit_vector(r.at(t) - point3(0, 0, -1));

        auto d = std::max(dot(n_hit_point, -lightDir), 0.0);

        pixel_color *= d;

      } else {
        pixel_color = ray_color(r);
      }

      write_color(std::cout, pixel_color);
    }
  }

  std::clog << "\nDone          \n";

  return 0;
}
