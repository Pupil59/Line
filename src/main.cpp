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

vector<Line> LineList;
map<pair<int, int>, pair<int, int>> PointList;

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

void intersection() {
    for (int i = 0; i < LineList.size() - 1; i++) {
        pair<int, int> leftK = LineList.at(i).getK();
        for (int j = i + 1; j < LineList.size(); j++) {
            pair<int, int> rightK = LineList.at(j).getK();
            if ((leftK.first == rightK.first) && (leftK.second == rightK.second)) {
                continue;
            }
            else {
                pair<int, int> leftB = LineList.at(i).getB();
                pair<int, int> rightB = LineList.at(j).getB();
                pair <int, int> X, Y;
                if (leftK.first == 0) {
                    X = pair<int, int>(1, leftB.second);
                    int second = rightK.second * rightB.first * leftB.second + rightB.second * rightK.first;
                    int first = rightK.first * rightB.first;
                    Y = getPair(first, second);
                }
                else {
                    if (rightK.first == 0) {
                        X = pair<int, int>(1, rightB.second);
                        int second = leftK.second * leftB.first * rightB.second + leftB.second * leftK.first;
                        int first = leftK.first * leftB.first;
                        Y = getPair(first, second);
                    }
                    else {
                        int second = (rightB.second * leftB.first - leftB.second * rightB.first) * (leftK.first * rightK.first);
                        int first = (rightB.first * leftB.first) * (leftK.second * rightK.first - rightK.second * leftK.first);
                        X = getPair(first, second);
                        second = leftK.second * leftB.first * first + leftB.second * leftK.first * second;
                        first = leftB.first * leftK.first * second;
                        Y = getPair(first, second);
                    }
                }
                map<pair<int, int>, pair<int, int>>::iterator iter = PointList.find(X);
                if (iter == PointList.end()) {
                    PointList.insert(pair<pair<int, int>, pair<int, int>>(X, Y));
                }
            }
        }
    }
    cout << PointList.size() << endl;
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
            //initCircle(c, y, r);
        }
    }
    intersection();

    return 0;
}
