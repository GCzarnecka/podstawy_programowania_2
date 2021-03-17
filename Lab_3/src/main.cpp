#include <iostream>
#include <cmath>

const double M_PI = 3.14159265358979323846;
using namespace std;

class Square {
private:
    double side;
    double x;
    double y;
public:
    static double count;
    Square(double _side_,double x1, double y1) {
        count++;
        side = _side_;
        x = x1;
        y  = y1;
        std::cout << "Object Square created" << std::endl;
    }
    ~Square() {
        count--;
        std::cout << "Object Square destroyed" << std::endl;
    }
    Square(const Square& sqr1) { 
        side = sqr1.side; 
        x = sqr1.x;
        y = sqr1.y;
    }
    double getCircumference() const { return 4 * side; }
    double getArea() const { return side * side; }
    double getSide() const { return  side; }
    double getX() const { return  x; }
    double getY() const { return  y; }
};

double Square::count = 0;

class Circle {
private:
    double radius;
    double x;
    double y;
public:
    Circle(double _radius_, double x1, double y1) {
        radius = _radius_;
        x = x1;
        y = y1;
        std::cout << "Object Circle created" << std::endl;
    }
    ~Circle() { std::cout << "Object Circle destroyed" << std::endl; }
    Circle(const Circle& cir1) { 
        radius = cir1.radius; 
        x = cir1.x;
        y = cir1.y;
    }
    double getCircumference() const { return 2 * M_PI * radius; }
    double getArea() const { return M_PI * radius * radius; }
    double getRadius() const { return  radius; }
    static void print_pi() { std::cout << "Pi is " << M_PI << std::endl; }
    double getX() const { return  x; }
    double getY() const { return  y; }
};

class Drawing {
private:
    Square *square;
    Circle *circle;
    const int rozmiar[2] = { 20,20 };

public:
    Drawing() {
        cout << "Object Drawing created!" << endl;
        square = new Square(5,5,5);
        circle = new Circle(5,10,10);
    }
    Drawing(Drawing *d) {
       square = new Square(*(d->square));
       circle = new Circle(*(d->circle));
    }

    ~Drawing() {
        delete square;
        delete circle;
        cout << "Object Drawing destroyed!" << endl;
    }

    void wypisz();
};

void Drawing::wypisz(){
    cout << " Rozmiar " << rozmiar[0] << "x" << rozmiar[1] << endl;
    cout << "Kwadrat" << endl;
    cout << "Obwod = " << square->getCircumference() << endl;
    cout << "Pole = " << square->getArea() << endl;
    cout << "Wspolrzedne :  x = " << square->getX() <<" y= "<< square->getX() << endl;
    cout << "Bok " << square->getSide() << endl;
    cout << endl;
    cout << "Kolo" << endl;
    cout << "Pole = " << circle->getArea() << endl;
    cout << "Obwod = " << circle->getCircumference() << endl;
    cout << "Promien = " << circle->getRadius() << endl;
    cout << "Wspolrzedne :  x = " << circle->getX() << " y= " << circle->getX() << endl;
    circle->print_pi();
}



int main(int argc, char* argv[]) 
{ 
    Drawing *d1 = new Drawing();
    d1->wypisz();
    cout << endl;
    Drawing* d2 = new Drawing(d1);//kopia
    d2->wypisz();
    cout << endl;
    delete d1;
    delete d2;
    return 0;
}