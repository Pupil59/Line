#pragma once
#ifndef GLOBAL
#define GLOBAL
#include <iostream>
#include <map>
#include <vector>

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

extern vector<Line> LineList;
extern vector<Circle> CircleList;
extern vector<pair<float, float>> floatPointList;
extern vector<pair<pair<int, int>, pair<int, int>>> PointList;

pair<int, int> getPair(int deltaX, int deltaY);
void initLineList(int x1, int y1, int x2, int y2);
void initCircleList(int x, int y, int r);
float Pair2float(pair<int, int> Pair);
void PointList2float();
void addFloatPointList(float x0, float y0);
void addPointList(pair<int, int> X, pair<int, int> Y);

#endif // !GLOBAL
