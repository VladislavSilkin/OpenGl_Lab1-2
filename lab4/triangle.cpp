#include "triangle.h"

triangle::triangle(){

}

triangle::triangle(std::pair<double,double> dot1, std::pair<double,double> dot2)
{
    this->dots[0] = dot1;
    this->dots[1] = dot2;

    dots[2].first = (dot2.first-dot1.first)*cos(60.0 * M_PI / 180)-(dot2.second-dot1.second)*sin(60.0 * M_PI / 180)+dot1.first;
    dots[2].second = (dot2.first-dot1.first)*sin(60.0 * M_PI / 180)-(dot2.second-dot1.second)*cos(60.0 * M_PI / 180)+dot1.second;

    dots[3].first = (dot1.first + dot2.first + dots[2].first) / 3;
    dots[3].second = (dot1.second + dot2.second + dots[2].second) / 3;
}

void triangle::rotate(double alpha)
{
    initCoords();

    std::vector<double> rotation (4);
    rotation[0] = cos(alpha);
    rotation[1] = -sin(alpha);
    rotation[2] = sin(alpha);
    rotation[3] = cos(alpha);

    for(int i = 0; i < 3; i++)
    {
        float temp = dots[i].first;
        dots[i].first = dots[i].first * rotation[0] + dots[i].second * rotation[1];
        dots[i].second = temp * rotation[2] + dots[i].second * rotation[3];
    }

    backCoords();
}

void triangle::resize(double size)
{
    initCoords();

    for(int i = 0; i < 3; i++) {
        dots[i].first *= size;
        dots[i].second *= size;
    }

    backCoords();
}

void triangle::initCoords()
{
    for(int i = 0; i < 3; i++)
    {
        dots[i].first -= dots[3].first;
        dots[i].second -= dots[3].second;
    }
}

void triangle::backCoords()
{
    for(int i = 0; i < 3; i++)
    {
        dots[i].first += dots[3].first;
        dots[i].second += dots[3].second;
    }
}
