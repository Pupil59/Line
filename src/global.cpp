#include <iostream>
#include <map>
#include <vector>
#include "global.h"

using namespace std;


vector<Line> LineList;
vector<Circle> CircleList;
vector<pair<float, float>> floatPointList;
vector<pair<pair<int, int>, pair<int, int>>> PointList;


int getDivisor(int x, int y) {
    if (x < y) {
        getDivisor(y, x);
    }
    else {
        if (y == 0) {
            return x;
        }
        else {
            getDivisor(y, x % y);
        }
    }
}

pair<int, int> getPair(int deltaX, int deltaY) {
    int divisor;
    if (deltaX < 0) {
        deltaX = -deltaX;
        deltaY = -deltaY;
    }
    if (deltaY < 0) {
        divisor = getDivisor(deltaX, -deltaY);
    }
    else {
        divisor = getDivisor(deltaX, deltaY);
    }
    if (divisor != 0) {
        deltaX /= divisor;
        deltaY /= divisor;
    }
    return pair<int, int>(deltaX, deltaY);
}

void initLineList(int x1, int y1, int x2, int y2) {
    int deltaX = x2 - x1;
    int deltaY = y2 - y1;
    pair<int, int> K = getPair(deltaX, deltaY);
    pair<int, int> B;
    if (K.first == 0 && K.second != 0) {
        deltaY = x1;
        deltaX = 1;
        B = pair<int, int>(deltaX, deltaY);
    }
    else {
        deltaX = K.first;
        deltaY = K.first * y1 - K.second * x1;
        B = getPair(deltaX, deltaY);
    }
    Line newline;
    newline.init(K, B);
    LineList.push_back(newline);
}

void initCircleList(int x, int y, int r) {
    Circle newcircle;
    newcircle.init(x, y, r);
    CircleList.push_back(newcircle);
}

float Pair2float(pair<int, int> Pair) {
    return (float)Pair.second / (float)Pair.first;
}

void PointList2float() {
    for (int i = 0; i < (int)PointList.size(); i++) {
        float x = Pair2float(PointList.at(i).first);
        float y = Pair2float(PointList.at(i).second);
        floatPointList.push_back(pair<float, float>(x, y));
    }
}

void addFloatPointList(float x0, float y0) {
    int flag = 0;
    for (int i = 0; i < (int)floatPointList.size(); i++) {
        float x = floatPointList.at(i).first;
        float y = floatPointList.at(i).second;
        if (x0 == x && y0 == y) {
            flag = 1;
            break;
        }
    }
    if (flag == 0) {
        floatPointList.push_back(pair<float, float>(x0, y0));
    }
    else {
        flag = 0;
    }
}

void addPointList(pair<int, int> X, pair<int, int> Y) {
    int flag = 0;
    for (int k = 0; k < (int)PointList.size(); k++) {
        if (PointList.at(k).first.first == X.first && PointList.at(k).first.second == X.second &&
            PointList.at(k).second.first == Y.first && PointList.at(k).second.second == Y.second) {
            flag = 1;
            break;
        }
    }
    if (flag == 0) {
        PointList.push_back(pair<pair<int, int>, pair<int, int>>(X, Y));
    }
    else {
        flag = 0;
    }
}

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