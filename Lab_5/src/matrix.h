
#include <iostream>
using namespace std;
class TwoDimensionMatrix {
    int matrix[2][2];
    constexpr static int size = 2;
public:
    TwoDimensionMatrix();
    TwoDimensionMatrix(const TwoDimensionMatrix& original_matrix);
    TwoDimensionMatrix(const int original_matrix[2][2]);
    int get(int i, int j)const { return matrix[i][j]; }
    void set(int i, int j, int value) { this->matrix[i][j] = value; }
    static constexpr int getSize() { return size; }
    TwoDimensionMatrix& operator=(const TwoDimensionMatrix& wzor);
    friend ostream& operator <<(ostream& strumien, const TwoDimensionMatrix& matrix) {
        for (int i = 0; i < matrix.size; i++)
            for (int j = 0; j < matrix.size; j++)
                strumien << matrix.matrix[i][j] << " ";
        strumien << endl;
        return strumien;
    }
    friend const TwoDimensionMatrix operator+(const TwoDimensionMatrix& matrix1, const TwoDimensionMatrix& matrix2)
    {
        TwoDimensionMatrix matrix3;
        for (int i = 0; i < matrix3.size; i++)
            for (int j = 0; j < 2; j++)matrix3.matrix[i][j] = matrix1.matrix[i][j] + matrix2.matrix[i][j];
        return matrix3;
    }
    friend const TwoDimensionMatrix operator*(const TwoDimensionMatrix& matrix1, const TwoDimensionMatrix& matrix2) {
        TwoDimensionMatrix matrix3;
        int s = 0;
        for (int i = 0; i < matrix3.size; i++)
            for (int j = 0; j < 2; j++) {
                s = 0;
                for (int k = 0; k < 2; k++) s += matrix1.matrix[i][k] * matrix2.matrix[k][j];
                matrix3.matrix[i][j] = s;
            }
        return matrix3;
    }
    TwoDimensionMatrix& operator*=(int liczba);
    TwoDimensionMatrix& operator&&(const TwoDimensionMatrix& matrix1) ;
    const int* operator[](size_t index) { return matrix[index]; }
    explicit operator size_t()const { return size; }
};

