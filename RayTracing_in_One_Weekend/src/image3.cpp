// Generates a Blue to White Gradient Background with a Red Sphere
#pragma once
#include <iostream>
#include <fstream>
#include "color.h"
#include "ray.h"
#include "vec3.h"
bool hit_sphere(const point3& center, double radius, const ray& r) {
    vec3 oc = r.origin() - center;
    auto a = dot(r.direction(), r.direction());
    auto b = 2.0 * dot(oc, r.direction());
    auto c = dot(oc, oc) - radius*radius; 
    auto discriminant = b*b - 4*a*c;
    return (discriminant > 0);
}

color ray_color(const ray& r) {
    point3 center = point3(0,0,-1);
    double rd = 0.1;
    point3 P = (r.direction());
    // if (dot(r.origin() - center + r.direction(), r.origin() - center + r.direction())  == 9*rd^2 ){
    //     return color(1,0,0);
    // }
    // if (P.z() + rd == center.z() && P.y() - rd <= center.y() && center.y() <= P.y() + rd && P.x() - rd <= center.x() && center.x() <= P.x() + rd){
    //     std::cout << "Here!";
    //     return color(1, 0, 0);
    // }
    // if (P.e[2] - rd == center.e[2] && P.e[1] - rd <= center.e[1] && center.e[1] <= P.e[1] + rd && P.e[0] - rd <= center.e[0] && center.e[0] <= P.e[0] + rd){
    //     std::cout << "Here!";
    //     return color(1, 0, 0);
    // }
    // if (P.e[1] + rd == center.e[1] && P.e[2] - rd <= center.e[2] && center.e[2] <= P.e[2] + rd && P.e[0] - rd <= center.e[0] && center.e[0] <= P.e[0] + rd){
    //     std::cout << "XD!";
    //     return color(1, 0, 0);
    // }
    // if (P.e[1] - rd == center.e[1] && P.e[2] - rd <= center.e[2] && center.e[2] <= P.e[2] + rd && P.e[0] - rd <= center.e[0] && center.e[0] <= P.e[0] + rd){
    //     std::cout << "Xd!";
    //     return color(1, 0, 0);
    // }
    // if (P.e[0] - rd == center.e[0] && P.e[2] - rd <= center.e[2] && center.e[2] <= P.e[2] + rd && P.e[1] - rd <= center.e[1] && center.e[1] <= P.e[1] + rd){
    //     std::cout << "Here!";
    //     return color(1, 0, 0);
    // }
    // if (P.e[0] + rd == center.e[0] && P.e[2] - rd <= center.e[2] && center.e[2] <= P.e[2] + rd && P.e[1] - rd <= center.e[1] && center.e[1] <= P.e[1] + rd){
    //     std::cout << "Here!";
    //     return color(1, 0, 0);
    // }
    
    if (hit_sphere(point3(0,0,-1), 0.5, r))
        return color(1, 0, 0);
    vec3 unit_direction = unit_vector(r.direction());
    auto t = 0.5*(unit_direction.y() + 1.0);
    return (1.0-t)*color(1.0, 1.0, 1.0) + t*color(0.5, 0.7, 1.0);
}

int main() {

    // Image

    const auto aspect_ratio = 16.0 / 9.0;
    const int image_width = 400;
    const int image_height = static_cast<int>(image_width / aspect_ratio);

    // Camera

    auto viewport_height = 2.0;
    auto viewport_width = aspect_ratio * viewport_height;
    auto focal_length = 1.0;

    auto origin = point3(0, 0, 0);
    auto horizontal = vec3(viewport_width, 0, 0);
    auto vertical = vec3(0, viewport_height, 0);
    auto lower_left_corner = origin - horizontal/2 - vertical/2 - vec3(0, 0, focal_length);

    // Render
    std::ofstream myfile;
    myfile.open("../Images/Image_3.ppm");

    myfile << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int j = image_height-1; j >= 0; --j) {
        std::cout << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < image_width; ++i) {
            auto u = double(i) / (image_width-1);
            auto v = double(j) / (image_height-1);
            ray r(origin, lower_left_corner + u*horizontal + v*vertical - origin);
            color pixel_color = ray_color(r);
            write_color(myfile, pixel_color);
        }
        // std::cout << "\nDone.\n";
    }
    myfile.close();
}