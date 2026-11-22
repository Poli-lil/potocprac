#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

using namespace std;

class Matrix {
private:
    int rows;
    int cols;
    int** data;

public:
    Matrix(int r, int c) {
        rows = r;
        cols = c;

        data = new int* [rows];

        for (int i = 0; i < rows; i++) {
            data[i] = new int[cols];

            for (int j = 0; j < cols; j++) {
                data[i][j] = rand() % 100;
            }
        }
    }
    ~Matrix() {
        for (int i = 0; i < rows; i++) {
            delete[] data[i];
        }

        delete[] data;
    }
    Matrix(const Matrix&) = delete;
    Matrix& operator=(const Matrix&) = delete;

    friend ostream& operator<<(ostream& out, const Matrix& m) {
        for (int i = 0; i < m.rows; i++) {
            for (int j = 0; j < m.cols; j++) {
                out << m.data[i][j] << "\t";
            }
            out << "\n";
        }

        return out;
    }
    friend istream& operator>>(istream& in, Matrix& m) {
        for (int i = 0; i < m.rows; i++) {
            for (int j = 0; j < m.cols; j++) {
                in >> m.data[i][j];
            }
        }
    }
};

int main() {
    setlocale(LC_ALL, "Russian");
    srand(time(0));
    int rows, cols;
    cout << "Введите количество строк: ";
    cin >> rows;
    cout << "Введите количество столбцов: ";
    cin >> cols;
    if (!cin || rows <= 0 || cols <= 0) {
        cout << "Неверный размер матрицы!\n";
        return 1;
    }
    Matrix matrix(rows, cols);
    cout << "\nСлучайная матрица:\n";
    cout << matrix;
    cout << "\nВведите элементы матрицы:\n";
    cin >> matrix;
    cout << "\nВаша матрица:\n";
    cout << matrix;
    ofstream outFile("matrix.txt");

    if (outFile.is_open()) {
        outFile << matrix;
        outFile.close();

        cout << "\nМатрица записана в файл!\n";
    }
    else {
        cout << "Ошибка открытия файла!\n";
    }
    ifstream inFile("matrix.txt");

    if (inFile.is_open()) {
        inFile >> matrix;
        inFile.close();

        cout << "\nМатрица прочитана из файла:\n";
        cout << matrix;
    }
    else {
        cout << "Ошибка чтения файла!\n";
    }
}