#include <iostream>
#include <vector>
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
	double& at(int row, int col) {
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
	friend matrix operator*(matrix& mtx, double s) {
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
	// завтра обратную матрицу и деление уже матрицу на матрицу.
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
	//проверка на тип матриц(квадратная,единичная, нулевая,...)
	// в степень можно возводить только квадратные матрицы. Оператор возведения в степень.
	//---------------------------//-----------------------------------------------------------------------------------------
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
	matrix transpos() {
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

	//обратная матрица
	//вспомогательная функция для получения обратной матрицы
	static matrix E(int size) {        //метод отвязан от объекта, возвращает матрицу размера size*size
		matrix e(size, size);
		for (int i = 0; i < size; i++)
			e._data[i][i] = 1;
		return e;
	}

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
		//сейчас res диагональная матрица до циклов ниже

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

	 };

int main()
{
	matrix A(3, 3);
	/*matrix B(2, 2);
	matrix C(2, 3);*/
	A.at(0, 0) = 3;
	A.at(0, 1) = 2;
	A.at(0, 2) = -5;

	A.at(1, 0) = 2;
	A.at(1, 1) = -1;
	A.at(1, 2) = 3;
	A.at(2, 0) = 1;
	A.at(2, 1) = 2;
	A.at(2, 2) = -1;
	cout << A / A << endl;
	cout << A.det() << endl;
	try {
		cout << A << endl;

		cout << A.inv() << endl;
	}
	catch (exception& e) {
		cout << e.what() << endl;
	}

	/*B.at(0, 0) = 2;
	B.at(0, 1) = 3;
	B.at(1, 0) = -4;
	B.at(1, 1) = 2;
	 
	C.at(0, 0) = 2;
	C.at(0, 1) = 3;
	C.at(0, 2) = 3;
	C.at(1, 0) = -4;
	C.at(1, 1) = 2;
	C.at(1, 2) = 3;*/
    /*cout << A << " " << B << endl;
	cout <<  (A-B)<< endl;
	cout << C << endl;*/
	
	/*cout << A.powByEl(5) << endl;
	cout << A << endl;*/
	//cout << A << endl;

	//A += B;
	//matrix C = A / 0.5;
	//cout << A << endl;
	//cout << B<<endl;
	//cout << C << endl;

	
	return 0;
}

