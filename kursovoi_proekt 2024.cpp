
#include <iostream>
#include <vector>
using namespace std;

class matrix {
private :
	vector<vector<double>>_data; // вектор векторов-хранит данные матрицы 
	int _rows;  // число строк
	int _cols; // число столбцов
public:
	matrix(int rows, int cols) : //конструстор создающий пустую матрицу с нужным количеством строк и столбцов;
		_rows(rows),
		_cols(cols)
	{
		_data.resize(_rows); // создали длину массива, которая будет совпадать с кол-вом его строк
		for (int i=0; i<_data.size();i++)
			_data[i].resize(_cols); // увеличиваем до размера количество столбцов
	};
	double& at(int row, int col) {
		return _data[row][col];        //чтобы могли в матрицу вводить значения
	}
	//перегрузка оператора вывода
	friend ostream& operator <<(ostream& out,  matrix& mtx) { // стандартная штука, friend- с помощью него мы получаем доступ к полям класса
		for (int i = 0; i < mtx._rows; i++) {
			for (int j = 0; j < mtx._cols; j++)
				out << mtx._data[i][j] << " ";
					out << endl;
		}
		return out;
	}
	
	friend istream& operator >>(istream& in, matrix& mtx) { // ввод в консоль матрицы;
		for (int i = 0; i < mtx._rows; i++) {
			for (int j = 0; j < mtx._cols; j++)
				in >> mtx._data[i][j];
		}
		return in;
	}
	//сложение матриц 
	friend matrix operator+(matrix& leftop, matrix rightop) { // проверка 
		if (leftop._rows != rightop._rows || leftop._cols != rightop._cols)
			throw logic_error("Matrix must be same size");

		matrix res(leftop._rows, leftop._cols);
		for (int i = 0; i < res._rows; i++)
			for (int j = 0; j < res._cols; j++)
				res._data[i][j] = leftop._data[i][j] + rightop._data[i][j];
		return res;
	}
	//скопировал сложение и заменил знак (вычитание матрич)
	friend matrix operator-(matrix& leftop, matrix rightop) { // проверка 
		if (leftop._rows != rightop._rows || leftop._cols != rightop._cols)
			throw logic_error("Matrix must be same size");

		matrix res(leftop._rows, leftop._cols);
		for (int i = 0; i < res._rows; i++)
			for (int j = 0; j < res._cols; j++)
				res._data[i][j] = leftop._data[i][j] - rightop._data[i][j];
		return res;
	}
	//оператор += функция класса 
	matrix& operator+=(matrix mtx) { // проверка 
		if (_rows != mtx._rows || _cols != mtx._cols)
			throw logic_error("Matrix must be same size");

		for (int i = 0; i < _rows; i++)
			for (int j = 0; j < _cols; j++)
				_data[i][j] = _data[i][j] + mtx._data[i][j];
		return *this;          //разименовываем скрытый указатель this
	}
	//оператор -= функция класса
	matrix& operator-=(matrix mtx) { // проверка 
		if (_rows != mtx._rows || _cols != mtx._cols)
			throw logic_error("Matrix must be same size");

		for (int i = 0; i < _rows; i++)
			for (int j = 0; j < _cols; j++)
				_data[i][j] = _data[i][j] - mtx._data[i][j];
		return *this;          //разименовываем скрытый указатель this
	}
	//умножение матрицы на число 
	friend matrix operator*(matrix& mtx, double s ){
		matrix res(mtx._rows, mtx._cols);
		for (int i = 0; i < res._rows; i++)
			for (int j = 0; j < res._cols; j++)
				res._data[i][j] = mtx._data[i][j] * s;
		return res;
	} // дублировали тоже самое, только поменяли местами число, чтобы работало 3*А
	friend matrix operator*(double s, matrix& mtx) {
		matrix res(mtx._rows, mtx._cols);
		for (int i = 0; i < res._rows; i++)
			for (int j = 0; j < res._cols; j++)
				res._data[i][j] = mtx._data[i][j] * s;
		return res;
	}
	// деление на скаляр вызывает умножение, но скаляр на оборот
	friend matrix operator/(matrix& mtx, double s) {

		return mtx * (1.0 / s);
	}
};

int main()
{
	matrix A(2, 2);
	matrix B(2, 2);
	A.at(0, 0) = 5;
	B.at(1, 1) = 2;
	A += B;
	matrix C = A / 0.5;
	cout << A << endl;
	cout << B<<endl;
	cout << C << endl;

	/*try {
		matrix C = A - B;
		cout << C << endl;
	}
	catch (exception& e) {
		cout << e.what() << endl;
	}*/
	return 0;
}

