#include <iostream>
#include <cstdlib>
double M_PI = 3.14;
using namespace std;

class Position
{
private:
    double x;
    double y;
public:
    Position(double x1, double y1) {
        x = x1;
        y = y1;
    }
    ~Position() {}
    double getX() { return x; }
    double getY() { return y; }
    void setX(double x1) { x = x1; }
    void setY(double y1) { y = y1; }
};

class Figure {
protected:
    Position p;
    double side;
    string type;
public:
    Figure(double side, double x, double y) :side(side) , p(x, y){};

    void changeXY(double x1, double y1) {
        p.setX(x1);
        p.setY(y1);
    }
    virtual double getCircumference() { return side; };
    virtual double getArea() { return side; };
    double getSide() { return side; };
    string printType() { return type; }
    void printPosition()  {
        cout <<"x= "<<p.getX()<< " y=  " <<p.getY()<<endl;
    }
    virtual ~Figure() {};
};

class Square:public Figure {
public:
    Square(double side, double x, double y):Figure(side,x,y)
    {
        type = "square";
    }
    ~Square() {
        cout << "Object Square destroyed" <<endl;
    }
    Square(const Figure& d):Figure(d) {
        type = "square";
    }
    double getCircumference() { return 4 * side; }
    double getArea()  { return side * side; }
    string printType() { return type; }
};


class Circle :public Figure {
public:
    Circle(double side, double x, double y) :Figure(side, x, y) {
        type = "circle";
    }
    ~Circle() { cout << "Object Circle destroyed" << endl; }
    Circle(const Circle& d) :Figure(d) {
        type = "circle";
    }
    double getCircumference() {  return 2 * M_PI * side; }
    double getArea() { return M_PI * side * side; }
    string printType() { return type; }
};

class Drawing {
private:
    double rozmiar[2];
    Figure* tablica[20];
    int count;

public:
    Drawing(double x, double y) {
        cout << "Object Drawing created!" << endl;
        rozmiar[0] = x;
        rozmiar[1] = y;
        count = 0;
    }
    Drawing(const Drawing &d) {
        rozmiar[0] = d.rozmiar[0];
        rozmiar[1] = d.rozmiar[1];
    }

    ~Drawing() {
        //nie dziala
       // delete [] tablica;
       // for (int i = 0; i < 20;i++) delete tablica[i] ;
    }
    void addCircle(double size1,double x1, double y1) {
        tablica[count] = new Circle(size1, x1, y1);
        count++;
    }
    void addSquare(double size1, double x1, double y1) {
        tablica[count] = new Square(size1, x1, y1);
        count++;
    }
    void deleteFigure(int i) {
        for (int j = i; i < count - 1; i++) {
            tablica[i] = tablica[i + 1];
        }
        delete tablica[count - 1];
        count--;
    }
 
    void wypisz(int i) {
        cout << "indeks  " << i << endl;
        cout << "Typ : " << tablica[i]->printType() << endl;
        cout << "Bok / Promien: " << tablica[i]->getSide() << endl;
        cout << "Pole : " << tablica[i]->getArea() << endl;
        cout << "Obwod: " << tablica[i]->getCircumference() << endl;
        cout << "wspolrzedne: ";
        tablica[i]->printPosition();
        cout << endl;
    }
    void move(int i, double x, double y) {
        tablica[i]->changeXY(x, y);
    }
};




int main(int argc, char* argv[])
{
    Drawing  d(20, 20);
    d.addCircle(2, 1, 1);
    d.addCircle(3, 2, 1);
    d.addSquare(1, 1, 2);
    d.wypisz(2);
    d.wypisz(1);
   
    d.move(1, 2, 3);


    return 0;
};