#define _CRTDBG_MAP_ALLOC
#include <algorithm>
#include <cmath>
#include <iostream>
#include <iterator>
#include <list>
#include <memory>
#include <typeinfo>
#include <crtdbg.h>

double M_PI = 3.14159265358979323846;
using namespace std;

class Figure {
    string type;
    class Point2D {
    public:
        int x_ob;
        int y_ob;
        Point2D() {
            x_ob = 0;
            y_ob = 0;
        }
        double getPtX() { return x_ob; };
        double getPtY() { return y_ob; };
        Point2D(int _x, int _y) {
            x_ob = _x;
            y_ob = _y;
        }
        void setPtXY(int x, int y) {
            x_ob = x;
            y_ob = y;
        }
        ~Point2D() { cout << "Point2D" << endl; }
    };
    Point2D coord;

public:
    Figure() {
        coord.x_ob = 0;
        coord.y_ob = 0;
    }
    virtual ~Figure()= default;
    void setXY(int _x, int _y) { coord.setPtXY(_x, _y); }
    void setType(const char* n) { type = n; }
    void getType() { cout << type; }
    void getCo() { cout << "(" << coord.x_ob << " , " << coord.y_ob << ")"; }
    virtual double getArea() { return 0; };
    virtual double getCircumference() { return 0; };
    Figure(const Figure& f) {
        this->setXY(f.getX(), f.getY());
        this->type = f.type;
    }
    virtual Figure* clone() const { return new Figure(*this); }
    double getX() const { return this->coord.x_ob; }
    double getY() const { return this->coord.y_ob; }
};

class Square : public Figure {
private:
    string type = "Square";
    double side = 5;

public:
    static double count;

    Square(const Square& sq) : Figure(sq) {
        this->side = sq.side;
        count++;
    }

    Square(double _side_, int x, int y) {
        count++;
        side = _side_;
        std::cout << "Object Square created" << std::endl;
        this->setType("Square");
        this->setXY(x, y);
    }
    Square() {
        count++;
        this->setType("Square");
    };
    ~Square() {
        count--;
        std::cout << "Object Square destroyed" << std::endl;
    }
    double getCircumference() override { return 4 * side; }
    double getArea() override { return side * side; }
    double getSide() { return side; }
    void set(double n) { side = n; }

    void changePosS(int a, int b) { this->setXY(a, b); }
};

double Square::count = 0;
class Circle : public Figure {
private:
    double radius = 10;

public:
    Circle(const Circle& cir) : Figure(cir) { this->radius = cir.radius; }
    Circle(double _radius_, int x, int y) {
        radius = _radius_;
        std::cout << "Object Circle created" << std::endl;
        this->setXY(x, y);
        this->setType("Circle");
    }
    Circle() {
        this->setType("Circle");
        this->setXY(0, 0);
    };
    ~Circle() { std::cout << "Object Circle destroyed" << std::endl; }
    double getCircumference() override { return 2 * M_PI * radius; }
    double getArea() override { return M_PI * radius * radius; }
    static void print_pi() { std::cout << "Pi is " << M_PI << std::endl; }
    void set(double n) { radius = n; }
    double getRadius() { return radius; }
    void changePosC(int a, int b) { this->setXY(a, b); }
};

class Drawing {
private:
    int r_x, r_y;
    list<Figure*> figureList;

public:
    Drawing() {
        r_x = 20;
        r_y = 20;
    };
    Drawing(int _rx, int _ry) {
        r_x = _rx;
        r_y = _ry;
        cout << "Drawing has been created." << endl;
    }
    Drawing(const Drawing& f) {};
    ~Drawing() {
        figureList.clear();
        cout << endl << "Clear the lsit." << endl;
    }
    Drawing* deepcopy(const Drawing* copy) { return new Drawing(*copy); }
    void setSize(int rx, int ry) {
        r_x = rx;
        r_y = ry;
    }
    void addFigure(Figure* ab) {
        figureList.push_back(ab);
    };
    void printList() {
        cout << endl << "List of elements: " << endl;
        for (auto const& v : figureList) {
            cout << "Figure type: ";
            v->getType();
            cout << " ";
            cout << endl << "Co-ordinates: ";
            v->getCo();
            cout << endl;
            cout << "Area: " << v->getArea()
                << " Circumference: " << v->getCircumference() << endl
                << endl;
        }
        cout << endl;
    }
    void eraser(int idx) {
        list<Figure*>::iterator itr = figureList.begin();
        advance(itr, idx);
        figureList.erase(itr);
    }
    list<Figure*> & getList( ) {
        return figureList;
    }
    Figure * operator []( int i) { 
        auto itr = figureList.begin();
        if (i > figureList.size()) return *itr;
        advance(itr, i);
        return *itr;
    }
    Figure* operator ()(int i) {
        auto itr = figureList.begin();
        if (i > figureList.size()) return *itr;
        advance(itr, i);
        return *itr;
    }

    bool operator ==(Drawing& drawing) {
        if (figureList.size() != drawing.figureList.size()) return false;
        if(figureList == drawing.figureList) return true;
        return false;
    }
    
    void operator+=(Drawing& d) {
        auto a = d.figureList.begin();
        for (a; a != d.figureList.end(); a++) addFigure(*a);
    }
    void operator = (Drawing& d) {
        auto a = d.figureList.begin();
        int i = 0;
        while(figureList.size()){
            eraser(i);
            cout << i;
        }
        for (a; a != d.figureList.end(); a++) addFigure(*a);

    }
    friend ostream& operator<<(ostream& os, const Drawing& obj);
    friend istream& operator>>(istream& os, Drawing& obj);
};

bool operator <(  Figure& f1,   Figure& f2 ) {//idk czy nie const
    if (f1.getArea()< f2.getArea()) return true;
    return false;
}

Drawing& operator+(Drawing& draw1, Drawing& draw2) {
    Drawing* new_drawing = new Drawing();
    *new_drawing = draw1;
    *new_drawing += draw2;
    return *new_drawing;
}

ostream& operator<<(ostream& os, const Drawing& obj)
{
    os <<obj.r_x<<endl;
    os << obj.r_y<<endl;
    for (auto const& v : obj.figureList) {
            cout << "Figure type: ";
            v->getType();
            cout << " ";
            cout << endl << "Co-ordinates: ";
            v->getCo();
            cout << endl;
            cout << "Area: " << v->getArea()
                << " Circumference: " << v->getCircumference() << endl
                << endl;
        }
    return os;
}

istream& operator>>(istream& os,  Drawing& obj)
{
    cout << "SIZE" << endl;
    os >> obj.r_x;
    os >> obj.r_y;
    return os;
}


 bool PComp( Figure *const &a,  Figure *const &b) { return *a < *b; }//const?



int main(int argc, char* argv[]) {
    Drawing* drawing = new Drawing(100, 100);
    Drawing* drawing2 = new Drawing(200, 200);

    Circle* c1 = new Circle(5, 10, 15);
    Square* s1 = new Square(5, 10, 15);
    drawing->addFigure(c1);
    drawing->addFigure(s1);

    drawing2->addFigure(c1);
    drawing2->addFigure(s1);

    Square* sq1 = new Square(*s1);
    Circle* cir2 = new Circle(*c1);
    drawing->addFigure(cir2);
    drawing->addFigure(sq1);

    // 1 // print all available info
    std::cout << *drawing << std::endl;
    std::cout << *drawing2 << std::endl;
    // 2 // change the drawing dimensions
     std::cin >> *drawing;
    // std::cout << *drawing << std::endl;

    // 3 // comparison
     if (*drawing == *drawing2) {
    cout << "Drawing are equal" << std::endl;
    }
     else cout << "Drawing are not equal" << std::endl;
     
    // 4 // sort the figures based on area (compare pointer by the dereference)
    // uncoment also PComp function
     cout << *drawing << endl;
     drawing->getList().sort(PComp);
     cout << *drawing << endl;

    // 5 // return the n'th element in the figure list
     std::cout << (*drawing)[0]<< std::endl;

    // 6 // return the n'th element in the figure list
    std::cout << (*drawing)(0);
    // 7 // add figures from drawing2 to drawing
     *drawing += *drawing2; 
     *drawing = *drawing + *drawing2;
    // 8 //add copy assigment operator
     *drawing = *drawing2;
     std::cout << *drawing << std::endl;

    // 9 // fix the memory leak

    // 10 // clean the code

    delete drawing;
    delete drawing2;
    delete c1;
    delete s1;
    delete sq1;
    delete cir2;
    
    _CrtDumpMemoryLeaks();

    return 0;
}
