#include <iostream>
#include <glm/glm.hpp>
#include <bitmap/bitmap_image.hpp>

struct Sphere {
    int id;
    glm::vec3 center;
    glm::vec3 color;
    float radius;

    Sphere(const glm::vec3& center=glm::vec3(0,0,0),
            float radius=0,
            const glm::vec3& color=glm::vec3(0,0,0))
        : center(center), radius(radius), color(color) {
            static int id_seed = 0;
            id = ++id_seed;
        }
};

struct Ray {
    glm::vec3 d;
    glm::vec3 o;
};

float intersection(const Ray& ray, const Sphere& sphere) {
    glm::vec3 o = ray.o;
    glm::vec3 d = ray.d;
    glm::vec3 sc = sphere.center;
    float r = sphere.radius;

    float a = glm::dot(d, d);
    float b = 2.0 * glm::dot(o-sc, d);
    float c = glm::dot(o-sc, o-sc) - r*r;

    float discriminant = b * b - 4 * c * a;
    if (discriminant < 0) {
        return FLT_MAX;
    }

    float x = -b - sqrt(discriminant);
    if (x > 0)
        return x / (2.0 * a);

    x = -b + sqrt(discriminant);
    if (x > 0)
        return x / (2.0 * a);

    return FLT_MAX;
}

struct Viewport {
    glm::vec2 min;
    glm::vec2 max;

    Viewport(const glm::vec2& min, const glm::vec2& max)
        : min(min), max(max) {}
};



void render(int mode, bitmap_image& image, const std::vector<Sphere>& world) {
    for (int y = 0; y < 480; ++y){
        for (int x = 0; x < 640; ++x){      
            float x1 = (x + 0.5) / 64 - 5;
            float y1 = (-y - 0.5) / 48 + 5;
            Ray ray;
            if (mode == 0) {
                ray.o = glm::vec3(0, 0, -5);
                ray.d = glm::vec3(y1, x1, 0) - ray.o;
            }
            else if (mode == 1) {
                ray.o = glm::vec3(y1, x1, 0);
                ray.d = glm::vec3(0, 0, 1);
            }

            float dist = FLT_MAX;
            glm::vec3 color;
            for (Sphere s : world) {


                float curr_dist = intersection(ray, s);
                if (curr_dist < dist) {
                    dist = curr_dist;
                    color = s.color;
                }
            }

            if (dist >= FLT_MAX) {
                image.set_pixel(x, y, 122, 55, 233);
                
            } else {
                float r = color.x * 255;
                float g = color.y * 255;
                float b = color.z * 255;
                image.set_pixel(x, y, r, g, b);
            }
        }
    }
}

int main(int argc, char** argv) {
    bitmap_image image(640, 480);
    std::vector<Sphere> world = {
        Sphere(glm::vec3(0, 0, 1), 1, glm::vec3(.8229,.2944,.5)),
        Sphere(glm::vec3(1, 1, 4), 2, glm::vec3(1,1,0)),
        Sphere(glm::vec3(2, 2, 6), 3, glm::vec3(.1005, 0,.7334)),
    };

    render(0, image, world);
    image.save_image("perspective.bmp");
    render(1, image, world);
    image.save_image("orthographic.bmp");

    std::cout << "Success" << std::endl;
}


