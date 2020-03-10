#include <iostream>
#include <map>
#include <vector>
#include <fstream>
#include "global.h"
using namespace std;

void Line_intersection() {
    for (int i = 0; i < (int)LineList.size() - 1; i++) {
        pair<int, int> k0 = LineList.at(i).getK();
        pair<int, int> b0 = LineList.at(i).getB();
        for (int j = i + 1; j < (int)LineList.size(); j++) {
            pair<int, int> k1 = LineList.at(j).getK();
            pair<int, int> b1 = LineList.at(j).getB();
            if ((k0.first == k1.first) && (k0.second == k1.second)) {
                continue;
            }
            else { 
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
                        second = k0.second * b0.first * X.second + b0.second * k0.first * X.first;
                        first = b0.first * k0.first * X.first;
                        Y = getPair(first, second);
                    }
                }
                addPointList(X, Y);
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
            float y2 = -sqrtf(r0 * r0 - (x1 - x0) * (x1 - x0)) + y0;
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
    for (int i = 0; i < (int)CircleList.size() - 1; i++) {
        for (int j = i + 1; j < (int)CircleList.size(); j++) {
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
    for (int i = 0; i < (int)LineList.size(); i++) {
        Line line = LineList.at(i);
        for (int j = 0; j < (int)CircleList.size(); j++) {
            Circle circle = CircleList.at(j);
            x0 = (float)circle.getX();
            y0 = (float)circle.getY();
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



int main(int argc, char* argv[])
{
    string out = "";
    string in = "";
    for (int i = 0; i < argc; i++) {
        if (argv[i][0] == '-' && argv[i][1] == 'i') {
            in = argv[i+1];
        }else if (argv[i][0] == '-' && argv[i][1] == 'o') {
            out = argv[i+1];
        }
    }
    ifstream fin(in);
    ofstream fout(out);
    
    int n;
    fin >> n;
    for (int i = 0; i < n; i++) {
        char type;
        fin >> type;
        if (type == 'L') {
            int x1, y1, x2, y2;
            fin >> x1 >> y1 >> x2 >> y2;
            initLineList(x1, y1, x2, y2);
        }
        else if (type == 'C') {
            int x, y, r;
            fin >> x >> y >> r;
            initCircleList(x, y, r);
        }
    }
    if (LineList.size() != 0) {
        Line_intersection();
    }
    if (CircleList.size() != 0) {
        PointList2float();
        Circle_intersection();
        CirLine_intersection();
        fout << floatPointList.size() << endl;
    }
    else {
        fout << PointList.size() << endl;
    }

    return 0;
}
