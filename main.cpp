#include "color.h"
#include <iostream>

int main() {
  const int image_width = 256;
  const int image_height = 256;

  std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";

  for (int j = 0; j < image_height; j++) {
    std::clog << "\nScaning lines remaining: " << image_height - j << "\n";
    for (int i = 0; i < image_width; i++) {
      auto pixel_color = color(double(i) / (image_width - 1),
                               double(j) / (image_height - 1), 0);
      write_color(std::cout, pixel_color);
    }
  }

  std::clog << "\nDone          \n";

  return 0;
}
