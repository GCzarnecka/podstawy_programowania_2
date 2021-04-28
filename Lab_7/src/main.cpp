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

class Object {
    double length;
public:
    Object() { length = 0; }
    Object(double d) { this->length = d; };
    virtual ~Object() = default;
    virtual double getArea() { return 0; };
    virtual double getCircumference() { return 0; };
    virtual double getLength() { return 0; };
    virtual void info() = 0;
};

class Square : public Object {
private:
    double side = 5;

public:
    Square(double _side_) {
        side = _side_;
        cout << "Object Square created" << endl;
    }
    ~Square() {
        cout << "Object Square destroyed" << endl;
    }
    double getCircumference() override { return 4 * side; }
    double getArea() override { return side * side; }
    double getSide() { return side; }
    void info() override {
        cout << " Square " << this->side << endl;
    }
};

class CurvedLine : public Object {
private:
    double length;

public:
    CurvedLine(double _length) {
        length = _length;
        cout << "Object CurvedtLine created" << endl;
    }
    ~CurvedLine() {
        cout << "Object CurvedtLine destroyed" << endl;
    }
    double getLength() { return length; }
    void info() override {
        cout << " Curved Line " << length << endl;
    }
};

class StraightLine : public Object {
private:
    double length = 5;

public:
    StraightLine(double _side_) {
        length = _side_;
        cout << "Object StraightLine created" << endl;
    }
    ~StraightLine() {
        cout << "Object StraightLine destroyed" <<endl;
    }
    double getLength() { return length; }
    void info() override {
        cout << " StraightLine " << length << endl;
    }
};


class Circle : public Object {
private:
    double radius ;

public:
    Circle(double _radius_) {
        radius = _radius_;
        cout << "Object Circle created" << endl;
    }

    ~Circle() { cout << "Object Circle destroyed" << endl; }
    double getCircumference() override { return 2 * M_PI * radius; }
    double getArea() override { return M_PI * radius * radius; }
    double getRadius() { return radius; }
    void info() override {
        cout << " Circle " << radius << endl;
    }
};

class Drawing {
private:
    int r_x, r_y;
    list<Object*> figureList;
public:
    Drawing() {};
    Drawing(int _rx, int _ry) {
        r_x = _rx;
        r_y = _ry;
        cout << "Drawing has been created." << endl;
    }
    ~Drawing() {
        for (auto&& a : figureList) delete a;
        figureList.clear();
        cout << endl << "Clear the lsit." << endl;
    }
    void addObject(Object* ab) { figureList.push_back(ab);};
    void printList() {
        
        cout << endl << "List of elements: " << endl;
        for (auto const& v : figureList) { v->info(); }
        }
    
    void eraser(int idx) {
        list<Object*>::iterator itr = figureList.begin();
        advance(itr, idx);
        figureList.erase(itr);
    }
    list<Object*>& getList() {
        return figureList;
    }
};

class Painter {
    Drawing& drawing;
public:
    Painter(Drawing& _drawing) :drawing(_drawing) {};
    ~Painter(){cout << "Painter destroyed" << endl; }
    virtual Object* createObject(double size)=0;
    void drawObject(double size) {
        Object* f = createObject(size);
        drawing.addObject(f);
    }
    void printMyWork() {
        drawing.printList();
    }

};
class StraightLinePainter: public Painter {
public:
    StraightLinePainter(Drawing& drawing) : Painter(drawing) {};
    ~StraightLinePainter() {};
    Object* createObject(double size)override {return new StraightLine(size);}
};
class CirclePainter : public Painter {
public:
    CirclePainter(Drawing& drawing) : Painter(drawing) {};
    ~CirclePainter() {};
    Object* createObject(double size)override { return new Circle(size); }
};
class SquarePainter : public Painter {
public:
    SquarePainter(Drawing& drawing) : Painter(drawing) {};
    ~SquarePainter() {};
    Object* createObject(double size)override { return new Square(size); }
};
class CurvedLinePainter : public Painter {
public:
    CurvedLinePainter(Drawing& drawing) : Painter(drawing) {};
    ~CurvedLinePainter() {};
    Object* createObject(double size)override { return new CurvedLine(size); }
};


int main(int argc, char* argv[]) {
    Drawing* draw = new Drawing;
    Painter* obj1 = new StraightLinePainter(*draw);
    obj1->drawObject(1);
    obj1->drawObject(2);
    obj1->printMyWork();

    Painter* obj2 = new CirclePainter(*draw);
    obj2->drawObject(3);
    obj2->printMyWork();

    Painter* obj3 = new CurvedLinePainter(*draw);
    obj3->drawObject(4);
    obj3->printMyWork();

    Painter* obj4 = new SquarePainter(*draw);
    obj4->drawObject(5);
    obj4->printMyWork();
    delete obj1;
    delete obj2;
    delete obj3;
    delete obj4;
    delete draw;

    _CrtDumpMemoryLeaks();

    return 0;
}
