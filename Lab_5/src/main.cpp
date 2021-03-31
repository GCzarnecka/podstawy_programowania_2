#include <iostream>
#include "matrix.h"
using namespace std;


TwoDimensionMatrix::TwoDimensionMatrix() {
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++)
            matrix[i][j] = 0;
    }
}

 TwoDimensionMatrix::TwoDimensionMatrix(const TwoDimensionMatrix &original_matrix)
    {
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++) 
                matrix[i][j] = original_matrix.get(i, j);
        }
    }
 TwoDimensionMatrix::TwoDimensionMatrix(const int original_matrix[2][2])
    {
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++) 
                matrix[i][j] = original_matrix[i][j];
                
        }
    }
    TwoDimensionMatrix & TwoDimensionMatrix::operator=(const TwoDimensionMatrix& wzor)
    {
        if (&wzor == this) return *this;//sprawdzenie czy nie kopiuje sam siebie
        int *size = new int(wzor.size);
        for (int i = 0; i < *size; i++)
            for (int j = 0; j < 2; j++)matrix[i][j]= wzor.matrix[i][j];
        return *this;
    }
    
    TwoDimensionMatrix & TwoDimensionMatrix::operator *=(int liczba) {
        for (int i = 0; i < size; i++)
            for (int j = 0; j < 2; j++)this->matrix[i][j] *= liczba;
         return *this;

    }
    TwoDimensionMatrix& TwoDimensionMatrix::operator&&(const TwoDimensionMatrix& matrix1)  {
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < 2; j++) {
                if (this->matrix[i][j] == matrix1.get(i,j))matrix[i][j]=1;
                else matrix[i][j]=0;
            }
        }
        return *this;
    }
    


int main(int argc, char* argv[])
{
    int matrix[2][2] = { { 1,2 }, { 3,4 } };

    TwoDimensionMatrix matrix1;
    TwoDimensionMatrix matrix2(matrix);
    matrix1 = matrix2;
    cout << "matrix1:\n"<<matrix1;
    cout << "matrix2:\n" << matrix2;
    cout << "matrix1 + matrix2:\n" << matrix1 + matrix2;
    cout<<"matrix1 * matrix2:\n" << matrix1 * matrix2;//mnozenie macierzy przez siebie, dodatkowo
    cout << "Przed mnozeniem\n" << matrix1;
    matrix1 *= 2;
    cout <<"Po mnozeniu *2\n"<< matrix1;
    cout << "Czy macierze maja takie same odpowiednie wartosci:\n"<< matrix1.operator&&(matrix2);
    cout<<"getSize()  "<<matrix1.getSize()<<endl;
    cout <<"operator konwersji  "<< matrix1.operator size_t();
    return 0;
}