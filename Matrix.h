#pragma once
#include <vector>
#include <iostream>

using namespace std;

class matrix {
private:
	vector<vector<double>>_data; // вектор векторов-хранит данные матрицы 
	int _rows;  // число строк
	int _cols; // число столбцов
public:
	matrix(int rows, int cols) : //конструстор создающий пустую матрицу с нужным количеством строк и столбцов;
		_rows(rows),
		_cols(cols)
	{
		_data.resize(_rows); // создали длину массива, которая будет совпадать с кол-вом его строк
		for (int i = 0; i < _data.size(); i++)
			_data[i].resize(_cols); // увеличиваем до размера количество столбцов
	};
	//конструктор для удобного занесения элементов в матрицу
	matrix(int rows, int cols, vector<vector<double>> data) :
		_cols(cols),
		_rows(rows),
		_data(data)
	{};

	//доступ к элементу матрицы через стандартный метод at
	double& at(int row, int col) {
		if (row >= _rows || col >= _cols)
			throw logic_error("Out of range at ()");
		return _data[row][col];        //чтобы могли в матрицу вводить значения
	}

	//перегрузка оператора вывода
	friend ostream& operator <<(ostream& out, const matrix& mtx) { // стандартная штука, friend- с помощью него мы получаем доступ к полям класса
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
	//скопировал сложение и заменил знак (вычитание матриц) 
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
	friend matrix operator*(matrix& mtx, double s) {
		matrix res(mtx._rows, mtx._cols);
		for (int i = 0; i < res._rows; i++)
			for (int j = 0; j < res._cols; j++)
				res._data[i][j] = mtx._data[i][j] * s;
		return res;
	} // дублировал тоже самое, только поменял местами число, чтобы работало 3*А
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
	// умножение матрицу на матрицу 
	friend matrix operator*(const matrix& left, const matrix& right) {
		if (left._cols != right._rows)
			throw logic_error("Matrix A and B cannot be multiply because not correct size");
		matrix res(left._rows, right._cols);
		for (int i = 0; i < res._rows; i++)
			for (int j = 0; j < res._cols; j++)
				for (int k = 0; k < left._cols; k++)
					res._data[i][j] += left._data[i][k] * right._data[k][j];
		return res;
	}

	//умножение поэлементное 
	matrix mulByEl(const matrix& right) {     // создаем правую матрицу, а левую будем вызывать
		if (_rows != right._rows || _cols != right._cols)
			throw logic_error("Matrix must be same size");
		matrix res(_rows, _cols);
		for (int i = 0; i < res._rows; i++)
			for (int j = 0; j < res._cols; j++)
				res._data[i][j] = _data[i][j] * right._data[i][j];
		return res;
	} // деление поэлементное матрица на матрицу.(аддитивное деление)
	matrix divByEl(const matrix& right) {
		if (_rows != right._rows || _cols != right._cols)
			throw logic_error("Matrix must be same size");
		matrix res(_rows, _cols);
		for (int i = 0; i < res._rows; i++)
			for (int j = 0; j < res._cols; j++)
				res._data[i][j] = _data[i][j] / right._data[i][j];
		return res;
	}

	//оператор сравнения матриц
	friend bool operator==(const matrix& left, const matrix& right) {
		if (left._rows != right._rows || left._cols != right._cols)
			throw logic_error("Matrix must be same size");

		for (int i = 0; i < left._rows; i++)
			for (int j = 0; j < left._cols; j++)
				if (left._data[i][j] != right._data[i][j])
					return false;

		return true;
	} // оператор неравенства матриц
	friend bool operator!=(const matrix& left, const matrix& right) {
		return !(left == right);
	}
	// в степень можно возводить только квадратные матрицы. Оператор возведения в степень.
	//оператор возведения в степень матрицы
	friend matrix operator^(const matrix& mtx, int s) {
		if (!mtx.isSquare())
			throw logic_error("Matrix must be a square");

		matrix res = mtx;//копируем исходную матрицу во временную
		for (int i = 0; i < s - 1; i++)
			res = res * mtx;
		return res;
	}
	//поэлементное возведение в степень
	matrix powByEl(int s) {
		if (!isSquare())
			throw logic_error("Matrix must be a square");

		matrix res = *this;//копируем исходную матрицу во временную
		for (int i = 0; i < s - 1; i++)
			res = res.mulByEl(*this);

		return res;
	}
	//транспонирование матрицы
	matrix transpose() {
		matrix res(_cols, _rows);
		for (int i = 0; i < _rows; i++)
			for (int j = 0; j < _cols; j++)
				res._data[j][i] = _data[i][j];
		return res;
	}
	//метод проверки матрицы на ее тип (в данном случае на квадратную)
	bool isSquare()  const {
		return _cols == _rows;
	}

	//вспомогательная функция для получения обратной матрицы
	static matrix E(int size) {        //метод отвязан от объекта, возвращает матрицу размера size*size
		matrix e(size, size);
		for (int i = 0; i < size; i++)
			e._data[i][i] = 1;
		return e;
	}
	//обратная матрица
	matrix inv() const {
		if (!isSquare())
			throw logic_error("Matrix must be a square");

		//выходная обратная матрица 
		matrix inv = matrix::E(_cols);

		//будущая единичная матрица
		matrix res = *this;
		//цикл по главной диагонале (ее столбцы)
		for (int k = 0; k < _cols - 1; k++) {
			//цикл по строкам
			for (int i = k + 1; i < _cols; i++) {
				double coeff = -res._data[i][k] / res._data[k][k];
				//цикл для сложения двух строк
				for (int j = 0; j < _cols; j++) {

					res._data[i][j] = res._data[i][j] + coeff * res._data[k][j];
					inv._data[i][j] = inv._data[i][j] + coeff * inv._data[k][j];

				}
			}
		}
		//проверка на вырожденную матрицу
		for (int i = 0; i < _cols; i++)
			if (res._data[i][i] == 0)
				throw logic_error("Singular matrix");

		for (int k = _cols - 1; k > 0; k--) {
			//цикл по строкам
			for (int i = k - 1; i >= 0; i--) {
				double coeff = -res._data[i][k] / res._data[k][k];
				//цикл для сложения двух строк
				for (int j = 0; j < _cols; j++) {

					res._data[i][j] = res._data[i][j] + coeff * res._data[k][j];
					inv._data[i][j] = inv._data[i][j] + coeff * inv._data[k][j];

				}
			}
		}
		// res диагональная матрица

		for (int i = 0; i < _cols; i++) {
			for (int j = 0; j < _cols; j++) {
				inv._data[i][j] = inv._data[i][j] / res._data[i][i];
			}
		}
		return inv;
	}
	double det() const {
		if (!isSquare())
			throw logic_error("Matrix must be a square");
		//будущая единичная матрица
		matrix res = *this;
		//цикл по главной диагонале (ее столбцы)
		for (int k = 0; k < _cols - 1; k++) {
			//цикл по строкам
			for (int i = k + 1; i < _cols; i++) {
				double coeff = -res._data[i][k] / res._data[k][k];
				//цикл для сложения двух строк
				for (int j = 0; j < _cols; j++) {

					res._data[i][j] = res._data[i][j] + coeff * res._data[k][j];

				}
			}
		}
		//проверка на вырожденную матрицу
		for (int i = 0; i < _cols; i++)
			if (res._data[i][i] == 0)
				return 0;

		for (int k = _cols - 1; k > 0; k--) {
			//цикл по строкам
			for (int i = k - 1; i >= 0; i--) {
				double coeff = -res._data[i][k] / res._data[k][k];
				//цикл для сложения двух строк
				for (int j = 0; j < _cols; j++) {

					res._data[i][j] = res._data[i][j] + coeff * res._data[k][j];
				}
			}
		}
		// res диагональная матрица
		double acc = 1;
		for (int i = 0; i < _cols; i++) {
			acc *= res._data[i][i];
		}
		return acc;
	}
	friend matrix operator/(const matrix& left, const matrix& right)
	{
		return left * right.inv();
	}
	//норма матрицы 
	//i -номер нормы 
	//1-столбцовая норма 
	//2- бесконечная норма 
	//3- сферическая норма 
	double norm(int i) const {
		if (i == 1)
		{
			double max = -1;
			for (int j = 0; j < _cols; j++)// складываем столбцы и выводим наибольшую сумму
			{
				double sum = 0;
				for (int i = 0; i < _rows; i++)
				{
					sum += abs(_data[i][j]);
				}
				if (sum > max)
					max = sum;
			}
			return max;
		}
		if (i == 2)
		{
			double max = -1;
			for (int i = 0; i < _rows; i++)    //складываем стоку и выводим с макс числом 
			{
				double sum = 0;
				for (int j = 0; j < _cols; j++)
				{
					sum += abs(_data[i][j]);
				}
				if (sum > max)
					max = sum;
			}
			return max;
		}

		if (i == 3)
		{
			double sum = 0;
			for (int i = 0; i < _rows; i++)                       //возводит в степень каждый элемент матрицы и потом извлекает корень из суммы
				for (int j = 0; j < _cols; j++)
					sum += _data[i][j] * _data[i][j];
			return sqrt(sum);
		}
	}
	double& operator ()(int i, int j) //работает с неконстантными объектами 
	{
		if (i >= _rows || j >= _cols)
			throw logic_error("Out of range index operator()");
		return _data[i][j];
	}
	double operator ()(int i, int j) const     //работает с константными объектами 
	{
		if (i >= _rows || j >= _cols)
			throw logic_error("Out of range index operator()");
		return _data[i][j];
	}
	int rows()const { //возращает размер сколько строк 
		return _rows;
	}
	int cols()const { //возвращает сколько столбцов
		return _cols;
	}
	vector<double>get_row(int i) const {                      //возвращает i строку 
		if (i >= _rows)
			throw logic_error("Out of range index get_row");
		return _data[i];
	}

	vector<double>get_col(int j) const {                       //возвращает j столбец
		if (j >= _cols)
			throw logic_error("Out of range index get_col()");

		vector<double> column;                       //массив, который хранит столбец
		for (int i = 0; i < _rows; i++)
			column.push_back(_data[i][j]);
		return column;
	}
	//проверка является  матрица диагональной или нет 
	bool isDiagonal() const {
		if (!isSquare())
			return false;
		for (int i = 0; i < _rows; i++)
			for (int j = 0; j < _cols; j++)
				if (i != j && _data[i][j] != 0)

					return false;
		return true;
	}
	//проверка является матрица единичной или нет
	bool isIdentity()const {
		if (!isDiagonal())
			return false;
		for (int i = 0; i < _rows; i++)
			if (_data[i][i] != 1)
				return false;
		return true;
	}
	//проверка на нулевую матрицу
	bool isZero() const {
		for (int i = 0; i < _rows; i++)
			for (int j = 0; j < _cols; j++)
				if (_data[i][j] != 0)
					return false;
		return true;
	}//проверка на верхне треугольную
	bool isUpper() const {
		if (!isSquare())
			return false;
		for (int i = 0; i < _rows; i++)
			for (int j = 0; j < _cols; j++)
				if (i > j && _data[i][j] != 0)
					return false;
		return true;
	}
	//проверка на нижне треугольную
	bool isLow() const {
		if (!isSquare())
			return false;
		for (int i = 0; i < _rows; i++)
			for (int j = 0; j < _cols; j++)
				if (i < j && _data[i][j] != 0)
					return false;
		return true;
	}// проверка на треугольность матрицы
	bool isTriangular() const {
		if (isUpper())
			return true;
		if (isLow())
			return true;
		return false;
	}//проверка на симметричность матрицы
	bool isSymmetric() const {
		if (!isSquare())
			return false;
		for (int i = 0; i < _rows; i++)
			for (int j = 0; j < i + 1; j++)
				if (_data[i][j] != _data[j][i])
					return false;
		return true;

	} //проверка на кососимметричную матрицу
	bool isSkewSymmetric() const {
		if (!isSquare())
			return false;
		for (int i = 0; i < _rows; i++)
			for (int j = 0; j < i + 1; j++)
				if (_data[i][j] != (-_data[j][i]))
					return false;
		return true;
	}
};

