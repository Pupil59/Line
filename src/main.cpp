#include <iostream>
#include <map>
#include <vector>
#include "my_class.h"

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

void initLine(int x1, int y1, int x2, int y2) {
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

float Pair2float(pair<int, int> Pair) {
    return (float)Pair.second / (float)Pair.first;
}

void PointList2float() {
    for (int i = 0; i < PointList.size(); i++) {
        float x = Pair2float(PointList.at(i).first);
        float y = Pair2float(PointList.at(i).second);
        floatPointList.push_back(pair<float, float>(x, y)); 
    }
}

void addFloatPointList(float x0, float y0) {
    int flag = 0;
    for (int i = 0; i < floatPointList.size(); i++) {
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

void Line_intersection() {
    for (int i = 0; i < LineList.size() - 1; i++) {
        pair<int, int> k0 = LineList.at(i).getK();
        for (int j = i + 1; j < LineList.size(); j++) {
            pair<int, int> k1 = LineList.at(j).getK();
            if ((k0.first == k1.first) && (k0.second == k1.second)) {
                continue;
            }
            else {
                pair<int, int> b0 = LineList.at(i).getB();
                pair<int, int> b1 = LineList.at(j).getB();
                pair <int, int> X, Y;
                if (k0.first == 0) {
                    X = pair<int, int>(1, b0.second);
                    int second = k1.second * b1.first * b0.second + b1.second * k1.first;
                    int first = k1.first * b1.first;
                    Y = getPair(first, second);
                }
                else {
                    if (k1.first == 0) {
                        X = pair<int, int>(1, b1.second);
                        int second = k0.second * b0.first * b1.second + b0.second * k0.first;
                        int first = k0.first * b0.first;
                        Y = getPair(first, second);
                    }
                    else {
                        int second = (b1.second * b0.first - b0.second * b1.first) * (k0.first * k1.first);
                        int first = (b1.first * b0.first) * (k0.second * k1.first - k1.second * k0.first);
                        X = getPair(first, second);
                        second = k0.second * b0.first * second + b0.second * k0.first * first;
                        first = b0.first * k0.first * first;
                        Y = getPair(first, second);
                    }
                }
                int flag = 0;
                for (int k = 0; k < PointList.size(); k++) {
                    if (PointList.at(k).first.first == X.first && PointList.at(k).first.second == X.second &&
                        PointList.at(k).second.first == Y.second && PointList.at(k).second.second == Y.second) {
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
        }
    }
}

void CircleLine(Circle circle, Line line, int intersectionNum) {
    float k, b, x1, y1, delta, a, c;
    float x0 = (float)circle.getX();
    float y0 = (float)circle.getY();
    float r0 = (float)circle.getR();
    if (line.getK().first == 0) {
        x1 = Pair2float(line.getB());
        y1 = sqrtf(r0 * r0 - (x1 - x0) * (x1 - x0)) + y0;
        addFloatPointList(x1, y1);
        if (intersectionNum == 2) {
            float x2 = x1;
            float y2 = - sqrtf(r0 * r0 - (x1 - x0) * (x1 - x0)) + y0;
            addFloatPointList(x2, y2);
        }
        else {
            //error();
        }
    }
    else {
        k = Pair2float(line.getK());
        b = Pair2float(line.getB());
        delta = (k * b - k * y0 - x0) * (k * b - k * y0 - x0) - (1 + k * k) * (x0 * x0 + (b - y0) * (b - y0) - r0 * r0);
        a = (1 + k * k);
        c = k * b - k * y0 - x0;
        x1 = (-c + sqrtf(delta)) / a;
        y1 = k * x1 + b;
        addFloatPointList(x1, y1);
        if (intersectionNum == 2) {
            float x2 = (-c - sqrtf(delta)) / a;
            float y2 = k * x2 + b;
            addFloatPointList(x2, y2);
        }
        else {
            //error();
        }
    } 
}

void Circle_intersection() {
    for (int i = 0; i < CircleList.size() - 1; i++) {
        for (int j = i + 1; j < CircleList.size(); j++) {
            int x1, y1, r1, x2, y2, r2;
            x1 = CircleList.at(i).getX();
            y1 = CircleList.at(i).getY();
            r1 = CircleList.at(i).getR();
            x2 = CircleList.at(j).getX();
            y2 = CircleList.at(j).getY();
            r2 = CircleList.at(j).getR();
            int sqD = (y2 - y1) * (y2 - y1) + (x2 - x1) * (x2 - x1);
            if (sqD > (r1 + r2)* (r1 + r2) || sqD < (r1 - r2) * (r1 - r2)) {
                continue;
            } 
            else {
                pair<int, int> K = getPair((y2 - y1), (x1 - x2));
                pair<int, int> B;
                if (K.first == 0) {
                    B = getPair(2 * (x2 - x1), (r1 * r1 - r2 * r2 + x2 * x2 - x1 * x1 + y2 * y2 - y1 * y1));
                }
                else {
                    B = getPair(2 * (y2 - y1), (r1 * r1 - r2 * r2 + x2 * x2 - x1 * x1 + y2 * y2 - y1 * y1));
                }
                Line newline;
                newline.init(K, B);
                if (sqD == (r1 + r2) * (r1 + r2) || sqD == (r1 - r2)* (r1 - r2)) {
                    CircleLine(CircleList.at(i), newline, 1);
                }
                else if (sqD < (r1 + r2) * (r1 + r2) || sqD > (r1 - r2) * (r1 - r2)) {
                    CircleLine(CircleList.at(i), newline, 2);
                }
            }
        }
    }
}

void CirLine_intersection() {
    float x0, y0, r0, k, b, d;
    for (int i = 0; i < LineList.size(); i++) {
        Line line = LineList.at(i);
        for (int j = 0; j < CircleList.size(); j++) {
            Circle circle = CircleList.at(j);
            x0 = circle.getX();
            y0 = circle.getY();
            r0 = (float)circle.getR();
            if (line.getK().first == 0) {
                b = Pair2float(line.getB());
                d = abs(x0 - b);
            }
            else {
                k = Pair2float(line.getK());
                b = Pair2float(line.getB());
                d = abs((k * x0 - y0 + b) / sqrtf(k * k + 1));
            }
            if (d > r0) {
                continue;
            }
            else if (d < r0) {
                CircleLine(circle, line, 2);
            }
            else {
                CircleLine(circle, line, 1);
            }
        }

    }
}



int main()
{
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        char type;
        cin >> type;
        if (type == 'L') {
            int x1, y1, x2, y2;
            cin >> x1 >> y1 >> x2 >> y2;
            initLine(x1, y1, x2, y2);
        }
        else if (type == 'C') {
            int x, y, r;
            cin >> x >> y >> r;
            Circle newcircle;
            newcircle.init(x, y, r);
            CircleList.push_back(newcircle);
        }
    }
    if (LineList.size() != 0) {
        Line_intersection();
    }
    if (CircleList.size() != 0) {
        PointList2float();
        Circle_intersection();
        CirLine_intersection();
        cout << floatPointList.size() << endl;
    }
    else {
        cout << PointList.size() << endl;
    }

    return 0;
}
