#include <iostream>

int main() {
  const int image_width = 256;
  const int image_height = 256;

  std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";

  for (int j = 0; j < image_height; j++) {
    std::clog << "\nScaning lines remaining: " << image_height - j << "\n";
    for (int i = 0; i < image_width; i++) {
      auto r = double(i) / (image_width - 1);
      auto g = double(j) / (image_height - 1);
      auto b = 0.0;

      int ir = int(255.999 * r);
      int ig = int(255.999 * g);
      int ib = int(255.999 * b);

      std::cout << ir << " " << ig << " " << ib << "\n";
    }
  }

  std::clog << "\nDone          \n";

  return 0;
}