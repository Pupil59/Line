#ifndef my_class
#define my_mylass

#include <map>
using namespace std;

class Line {
private:
    pair<int, int> K;
    pair<int, int> B;

public:
    void init(pair<int, int>, pair<int, int>);
    pair<int, int> getK();
    pair<int, int> getB();
};

void Line::init(pair<int, int> a_K, pair<int, int> a_B) {
    this->K = a_K;
    this->B = a_B;
}

pair<int, int> Line::getK() {
    return this->K;
}

pair<int, int> Line::getB() {
    return this->B;
}

class Circle {
private:
    int x;
    int y;
    int r;
public:
    void init(int, int, int);
    int getX();
    int getY();
    int getR();
};

void Circle::init(int a_x, int a_y, int a_r) {
    this->x = a_x;
    this->y = a_y;
    this->r = a_r;
}

int Circle::getX() {
    return this->x;
}

int Circle::getY() {
    return this->y;
}

int Circle::getR() {
    return this->r;
}

#endif