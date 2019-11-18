#include <iostream>
#include <algorithm>
#include <memory>
#include <vector>
using namespace std;

class Point{
    int x;
    int y;
    int posX;
    int posY;
public:
    Point(int x, int y): x{x}, y{y}, posX{-1}, posY{-1} {}
    void setX(int x){ posX = x;}
    void setY(int y){ posY = y;}
    int getX() { return posX; }
    int getY() { return posY; }
    friend bool compareX(shared_ptr<Point> a, shared_ptr<Point> b);
    friend bool compareY(shared_ptr<Point> a, shared_ptr<Point> b);
    friend ostream& operator<<(ostream& out, const Point& pt);
};

bool compareX(shared_ptr<Point> a, shared_ptr<Point> b) {
    return a->x < b->x;
}

bool compareY(shared_ptr<Point> a, shared_ptr<Point> b) {
    return a->y < b->y;
}

ostream& operator<<(ostream& out, const Point& pt){
    out << pt.x << " " << pt.y;
    return out;
}

void kdtree(vector<shared_ptr<Point>> vx, vector<shared_ptr<Point>> vy, string index){
    int median, pivot;
    if (vx.size()==1){
        cout << *vx[0] << endl;
        return;
    }
    if (vx.empty())
        return;
    
    if (index == "x"){
        median = vx.size()/2;
        pivot = vx[median]->getX();
        vector<shared_ptr<Point>> newvx1, newvx2;
        for (int i = 0; i < median; ++i)
            newvx1.emplace_back(vx[i]);
        for (int i = median+1; i < vx.size(); ++i)
            newvx2.emplace_back(vx[i]);
        
        vector<shared_ptr<Point>> newvy1, newvy2;
        for (int i = 0; i < vy.size(); ++i){
            if (vy[i]->getX() < pivot){
                newvy1.emplace_back(vy[i]);
            }
            if (vy[i]->getX() > pivot){
                newvy2.emplace_back(vy[i]);
            }
        }
        
        cout << *vx[median] << endl;
        kdtree(newvx1, newvy1, "y");
        kdtree(newvx2, newvy2, "y");
    }
    else{
        median = vy.size()/2;
        pivot = vy[median]->getY();
        vector<shared_ptr<Point>> newvy1, newvy2;
        for (int i = 0; i < median; ++i)
            newvy1.emplace_back(vy[i]);
        for (int i = median+1; i < vy.size(); ++i)
            newvy2.emplace_back(vy[i]);
        vector<shared_ptr<Point>> newvx1, newvx2;
        for (int i = 0; i < vx.size(); ++i){
            if (vx[i]->getY() < pivot){
                newvx1.emplace_back(vx[i]);
            }
            if (vx[i]->getY() > pivot){
                newvx2.emplace_back(vx[i]);
            }
        }
        cout << *vy[median] << endl;
        kdtree(newvx1, newvy1, "x");
        kdtree(newvx2, newvy2, "x");
    }
}

int main(int argc, const char * argv[]) {
    int numpoint;
    cin >> numpoint;
    vector<shared_ptr<Point>> vx;
    vector<shared_ptr<Point>> vy;
    int x, y;
    for (int i=0; i<numpoint; ++i){
        cin>>x;
        cin>>y;
        shared_ptr<Point> p = make_shared<Point>(x, y);
        vx.emplace_back(p);
        vy.emplace_back(p);
    }
    sort(vx.begin(), vx.end(), compareX);
    for (int i = 0; i < vx.size(); ++i) { vx[i]->setX(i); }
    sort(vy.begin(), vy.end(), compareY);
    for (int i = 0; i < vy.size(); ++i) { vy[i]->setY(i); }
    kdtree(vx, vy, "x");
    return 0;
}
