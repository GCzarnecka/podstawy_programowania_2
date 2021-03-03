#include <iostream>
using namespace std;

void a1(int a, int b, int *p)//przez wartoœæ
{
    *p = a + b;
}

void a2(int *a, int *b, int* p)//przez wskaŸnik
{
    *p = *a + *b;
}

void a3(int &a, int &b, int* p)//przez referencjê
{
    *p = a + b;
}
void a4(int* (&a), int* (&b), int* p)//przez wskaŸnik do referencji
{
    *p = *a + *b;
}


void b1( int a[],  int b[], int* p)
{
    for (int i=0; i < 10; i++) {
        p[i]= a[i] + b[i];
    }
}

void b2(int *a, int *b, int *p)
{
    for (int i=0; i < 10; i++) {
        p[i] = a[i] +b[i];
    }
}


void b3(int (&a)[10], int (&b)[10], int* p)
{
    for (int i=0; i < 10; i++) {
        p[i] = a[i] + b[i];
    }
}

void b4(int *(&a), int *(&b), int *p)
{
    for (int i=0; i < 10; i++) {
        p[i] = a[i] + b[i];
    }
}

void wypisz(int tab[])
{
    cout << "tab3 = {";
    for (int i = 0; i<10; i++)
    {
        cout<< tab[i] << " ";
    }
    cout <<'}'<< endl;
}

int main(int argc, char *argv[])
{
    int a = 1, b = 2,c=0,i=0;
    int tab1[10] = { 1,2,3,4,5,6,7,8,9,10 }, tab2[10] = { 1,2,3,4,5,6,7,8,9,10 }, tab3[10] = { 0 };
    a1(a, b, &c);
    cout<<"a = "<<a<<" b = "<<b<<" c =" << c<<endl;
    a2(&a, &b, &c);
    cout << "a = " << a << " b = " << b << " c =" << c << endl;
    a3(a, b, &c);
    cout << "a = " << a << " b = " << b << " c =" << c << endl;
    cout << endl;

    b1(tab1, tab2, tab3);
    wypisz(tab3);
    b2(&tab1[0], &tab2[0], tab3);
    wypisz(tab3);
    b3(tab1, tab2, tab3);
    wypisz(tab3);
    int *p1 = &tab1[0], *p2 = &tab2[0];
    b4(p1, p2, tab3);
    wypisz(tab3);

    return 0;
}