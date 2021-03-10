#include <iostream>
#include<cmath>
#define M_PI 3.14159265358979323846
using namespace std;

class Square {
    double a;

public:
    static int ilosc;
    explicit Square(double a) {
        this->a = a;
        ilosc++;
        cout << "Tworzenie Kwadratu" << endl;
    }
    Square(const Square& a1) { a = a1.a; ilosc++;
    }
    double pole();
    double obwod();
    ~Square() {
        ilosc--;
        cout << "Niszczenie Kwadratu" << endl;
    }
};


class Circle{
    double r;
public:
    static int ilosc;
    explicit Circle(double r) {
        this->r = r;
        ilosc++;
        cout << "Tworzenie Kola" << endl;
    }
    Circle(const Circle& r1) { 
        ilosc++;
        r = r1.r;
    }
    double pole();
    double obwod();
    static double pi() { return M_PI; }
    ~Circle() {
        ilosc--;
        cout << "Niszczenie Kola" << endl;
    }
};
int Circle::ilosc = 0;
int Square::ilosc = 0;


double Circle::pole() {
    return M_PI * this->r * this->r;
}
double Circle::obwod()
{
    return 2 * M_PI * this->r;
}

double Square::pole() {
    return this->a*this->a;
}
double Square::obwod()
{
    return 4* this->a;
}


int main(int argc, char *argv[])
{
    Circle *c1= new Circle(3.0);//na stercie
    cout << "Ilosc kol:" << c1->ilosc << endl;
    cout << c1->pole() << endl;
    cout << c1->obwod()<<endl;
    Circle c2(5);//na stosie
    cout << "Ilosc kol:" << c1->ilosc << endl;
    cout << c2.pole() << endl;
    cout << c2.obwod() << endl;
    Circle c3 = c2;
    cout << "Ilosc kol:" << c1->ilosc << endl;
    cout << c3.pole() << endl;
    cout << c3.obwod() << endl;
    cout<<"Pi wynosi = "<<c1->pi()<<endl;
    cout << endl;

    Square* s1 = new Square(4.0);
    cout << "Ilosc kwadratow:" << s1->ilosc << endl;
    cout << s1->pole() << endl;
    cout << s1->obwod()<<endl;
    Square s2(6.0);
    cout << "Ilosc kwadratow:" << s1->ilosc << endl;
    cout << s2.pole() << endl;
    cout << s2.obwod() << endl;
    c1->~Circle();
    cout << "Ilosc kol:" << c1->ilosc << endl;
    s1->~Square();
    cout << "Ilosc kwadratow:" << s1->ilosc << endl;
    return 0;
}