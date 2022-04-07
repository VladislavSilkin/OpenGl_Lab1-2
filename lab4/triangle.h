#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <utility>
#include <cmath>
#include <vector>

class triangle
{
public:
    std::pair<double,double> dots[4];

    triangle(std::pair<double,double> first, std::pair<double,double> second);
    void rotate(double);
    void resize(double);
private:
    void initCoords();
    void backCoords();
};

#endif // TRIANGLE_H
