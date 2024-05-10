#pragma once
#include <vector>
#include <iostream>

using namespace std;

class matrix {
private:
	vector<vector<double>>_data; // ������ ��������-������ ������ ������� 
	int _rows;  // ����� �����
	int _cols; // ����� ��������
public:
	matrix(int rows, int cols) : //����������� ��������� ������ ������� � ������ ����������� ����� � ��������;
		_rows(rows),
		_cols(cols)
	{
		_data.resize(_rows); // ������� ����� �������, ������� ����� ��������� � ���-��� ��� �����
		for (int i = 0; i < _data.size(); i++)
			_data[i].resize(_cols); // ����������� �� ������� ���������� ��������
	};
	//����������� ��� �������� ��������� ��������� � �������
	matrix(int rows, int cols, vector<vector<double>> data) :
		_cols(cols),
		_rows(rows),
		_data(data)
	{};

	//������ � �������� ������� ����� ����������� ����� at
	double& at(int row, int col) {
		if (row >= _rows || col >= _cols)
			throw logic_error("Out of range at ()");
		return _data[row][col];        //����� ����� � ������� ������� ��������
	}

	//���������� ��������� ������
	friend ostream& operator <<(ostream& out, const matrix& mtx) { // ����������� �����, friend- � ������� ���� �� �������� ������ � ����� ������
		for (int i = 0; i < mtx._rows; i++) {
			for (int j = 0; j < mtx._cols; j++)
				out << mtx._data[i][j] << " ";
			out << endl;
		}
		return out;
	}

	friend istream& operator >>(istream& in, matrix& mtx) { // ���� � ������� �������;
		for (int i = 0; i < mtx._rows; i++) {
			for (int j = 0; j < mtx._cols; j++)
				in >> mtx._data[i][j];
		}
		return in;
	}
	//�������� ������ 
	friend matrix operator+(matrix& leftop, matrix rightop) { // �������� 
		if (leftop._rows != rightop._rows || leftop._cols != rightop._cols)
			throw logic_error("Matrix must be same size");

		matrix res(leftop._rows, leftop._cols);
		for (int i = 0; i < res._rows; i++)
			for (int j = 0; j < res._cols; j++)
				res._data[i][j] = leftop._data[i][j] + rightop._data[i][j];
		return res;
	}
	//���������� �������� � ������� ���� (��������� ������) 
	friend matrix operator-(matrix& leftop, matrix rightop) { // �������� 
		if (leftop._rows != rightop._rows || leftop._cols != rightop._cols)
			throw logic_error("Matrix must be same size");

		matrix res(leftop._rows, leftop._cols);
		for (int i = 0; i < res._rows; i++)
			for (int j = 0; j < res._cols; j++)
				res._data[i][j] = leftop._data[i][j] - rightop._data[i][j];
		return res;
	}
	//�������� += ������� ������ 
	matrix& operator+=(matrix mtx) { // �������� 
		if (_rows != mtx._rows || _cols != mtx._cols)
			throw logic_error("Matrix must be same size");

		for (int i = 0; i < _rows; i++)
			for (int j = 0; j < _cols; j++)
				_data[i][j] = _data[i][j] + mtx._data[i][j];
		return *this;          //�������������� ������� ��������� this
	}
	//�������� -= ������� ������
	matrix& operator-=(matrix mtx) { // �������� 
		if (_rows != mtx._rows || _cols != mtx._cols)
			throw logic_error("Matrix must be same size");

		for (int i = 0; i < _rows; i++)
			for (int j = 0; j < _cols; j++)
				_data[i][j] = _data[i][j] - mtx._data[i][j];
		return *this;          //�������������� ������� ��������� this
	}
	//��������� ������� �� ����� 
	friend matrix operator*(matrix& mtx, double s) {
		matrix res(mtx._rows, mtx._cols);
		for (int i = 0; i < res._rows; i++)
			for (int j = 0; j < res._cols; j++)
				res._data[i][j] = mtx._data[i][j] * s;
		return res;
	} // ���������� ���� �����, ������ ������� ������� �����, ����� �������� 3*�
	friend matrix operator*(double s, matrix& mtx) {
		matrix res(mtx._rows, mtx._cols);
		for (int i = 0; i < res._rows; i++)
			for (int j = 0; j < res._cols; j++)
				res._data[i][j] = mtx._data[i][j] * s;
		return res;
	}
	// ������� �� ������ �������� ���������, �� ������ �� ������
	friend matrix operator/(matrix& mtx, double s) {

		return mtx * (1.0 / s);
	}
	// ��������� ������� �� ������� 
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

	//��������� ������������ 
	matrix mulByEl(const matrix& right) {     // ������� ������ �������, � ����� ����� ��������
		if (_rows != right._rows || _cols != right._cols)
			throw logic_error("Matrix must be same size");
		matrix res(_rows, _cols);
		for (int i = 0; i < res._rows; i++)
			for (int j = 0; j < res._cols; j++)
				res._data[i][j] = _data[i][j] * right._data[i][j];
		return res;
	} // ������� ������������ ������� �� �������.(���������� �������)
	matrix divByEl(const matrix& right) {
		if (_rows != right._rows || _cols != right._cols)
			throw logic_error("Matrix must be same size");
		matrix res(_rows, _cols);
		for (int i = 0; i < res._rows; i++)
			for (int j = 0; j < res._cols; j++)
				res._data[i][j] = _data[i][j] / right._data[i][j];
		return res;
	}

	//�������� ��������� ������
	friend bool operator==(const matrix& left, const matrix& right) {
		if (left._rows != right._rows || left._cols != right._cols)
			throw logic_error("Matrix must be same size");

		for (int i = 0; i < left._rows; i++)
			for (int j = 0; j < left._cols; j++)
				if (left._data[i][j] != right._data[i][j])
					return false;

		return true;
	} // �������� ����������� ������
	friend bool operator!=(const matrix& left, const matrix& right) {
		return !(left == right);
	}
	// � ������� ����� ��������� ������ ���������� �������. �������� ���������� � �������.
	//�������� ���������� � ������� �������
	friend matrix operator^(const matrix& mtx, int s) {
		if (!mtx.isSquare())
			throw logic_error("Matrix must be a square");

		matrix res = mtx;//�������� �������� ������� �� ���������
		for (int i = 0; i < s - 1; i++)
			res = res * mtx;
		return res;
	}
	//������������ ���������� � �������
	matrix powByEl(int s) {
		if (!isSquare())
			throw logic_error("Matrix must be a square");

		matrix res = *this;//�������� �������� ������� �� ���������
		for (int i = 0; i < s - 1; i++)
			res = res.mulByEl(*this);

		return res;
	}
	//���������������� �������
	matrix transpose() {
		matrix res(_cols, _rows);
		for (int i = 0; i < _rows; i++)
			for (int j = 0; j < _cols; j++)
				res._data[j][i] = _data[i][j];
		return res;
	}
	//����� �������� ������� �� �� ��� (� ������ ������ �� ����������)
	bool isSquare()  const {
		return _cols == _rows;
	}

	//��������������� ������� ��� ��������� �������� �������
	static matrix E(int size) {        //����� ������� �� �������, ���������� ������� ������� size*size
		matrix e(size, size);
		for (int i = 0; i < size; i++)
			e._data[i][i] = 1;
		return e;
	}
	//�������� �������
	matrix inv() const {
		if (!isSquare())
			throw logic_error("Matrix must be a square");

		//�������� �������� ������� 
		matrix inv = matrix::E(_cols);

		//������� ��������� �������
		matrix res = *this;
		//���� �� ������� ��������� (�� �������)
		for (int k = 0; k < _cols - 1; k++) {
			//���� �� �������
			for (int i = k + 1; i < _cols; i++) {
				double coeff = -res._data[i][k] / res._data[k][k];
				//���� ��� �������� ���� �����
				for (int j = 0; j < _cols; j++) {

					res._data[i][j] = res._data[i][j] + coeff * res._data[k][j];
					inv._data[i][j] = inv._data[i][j] + coeff * inv._data[k][j];

				}
			}
		}
		//�������� �� ����������� �������
		for (int i = 0; i < _cols; i++)
			if (res._data[i][i] == 0)
				throw logic_error("Singular matrix");

		for (int k = _cols - 1; k > 0; k--) {
			//���� �� �������
			for (int i = k - 1; i >= 0; i--) {
				double coeff = -res._data[i][k] / res._data[k][k];
				//���� ��� �������� ���� �����
				for (int j = 0; j < _cols; j++) {

					res._data[i][j] = res._data[i][j] + coeff * res._data[k][j];
					inv._data[i][j] = inv._data[i][j] + coeff * inv._data[k][j];

				}
			}
		}
		// res ������������ �������

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
		//������� ��������� �������
		matrix res = *this;
		//���� �� ������� ��������� (�� �������)
		for (int k = 0; k < _cols - 1; k++) {
			//���� �� �������
			for (int i = k + 1; i < _cols; i++) {
				double coeff = -res._data[i][k] / res._data[k][k];
				//���� ��� �������� ���� �����
				for (int j = 0; j < _cols; j++) {

					res._data[i][j] = res._data[i][j] + coeff * res._data[k][j];

				}
			}
		}
		//�������� �� ����������� �������
		for (int i = 0; i < _cols; i++)
			if (res._data[i][i] == 0)
				return 0;

		for (int k = _cols - 1; k > 0; k--) {
			//���� �� �������
			for (int i = k - 1; i >= 0; i--) {
				double coeff = -res._data[i][k] / res._data[k][k];
				//���� ��� �������� ���� �����
				for (int j = 0; j < _cols; j++) {

					res._data[i][j] = res._data[i][j] + coeff * res._data[k][j];
				}
			}
		}
		// res ������������ �������
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
	//����� ������� 
	//i -����� ����� 
	//1-���������� ����� 
	//2- ����������� ����� 
	//3- ����������� ����� 
	double norm(int i) const {
		if (i == 1)
		{
			double max = -1;
			for (int j = 0; j < _cols; j++)// ���������� ������� � ������� ���������� �����
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
			for (int i = 0; i < _rows; i++)    //���������� ����� � ������� � ���� ������ 
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
			for (int i = 0; i < _rows; i++)                       //�������� � ������� ������ ������� ������� � ����� ��������� ������ �� �����
				for (int j = 0; j < _cols; j++)
					sum += _data[i][j] * _data[i][j];
			return sqrt(sum);
		}
	}
	double& operator ()(int i, int j) //�������� � �������������� ��������� 
	{
		if (i >= _rows || j >= _cols)
			throw logic_error("Out of range index operator()");
		return _data[i][j];
	}
	double operator ()(int i, int j) const     //�������� � ������������ ��������� 
	{
		if (i >= _rows || j >= _cols)
			throw logic_error("Out of range index operator()");
		return _data[i][j];
	}
	int rows()const { //��������� ������ ������� ����� 
		return _rows;
	}
	int cols()const { //���������� ������� ��������
		return _cols;
	}
	vector<double>get_row(int i) const {                      //���������� i ������ 
		if (i >= _rows)
			throw logic_error("Out of range index get_row");
		return _data[i];
	}

	vector<double>get_col(int j) const {                       //���������� j �������
		if (j >= _cols)
			throw logic_error("Out of range index get_col()");

		vector<double> column;                       //������, ������� ������ �������
		for (int i = 0; i < _rows; i++)
			column.push_back(_data[i][j]);
		return column;
	}
	//�������� ��������  ������� ������������ ��� ��� 
	bool isDiagonal() const {
		if (!isSquare())
			return false;
		for (int i = 0; i < _rows; i++)
			for (int j = 0; j < _cols; j++)
				if (i != j && _data[i][j] != 0)

					return false;
		return true;
	}
	//�������� �������� ������� ��������� ��� ���
	bool isIdentity()const {
		if (!isDiagonal())
			return false;
		for (int i = 0; i < _rows; i++)
			if (_data[i][i] != 1)
				return false;
		return true;
	}
	//�������� �� ������� �������
	bool isZero() const {
		for (int i = 0; i < _rows; i++)
			for (int j = 0; j < _cols; j++)
				if (_data[i][j] != 0)
					return false;
		return true;
	}//�������� �� ������ �����������
	bool isUpper() const {
		if (!isSquare())
			return false;
		for (int i = 0; i < _rows; i++)
			for (int j = 0; j < _cols; j++)
				if (i > j && _data[i][j] != 0)
					return false;
		return true;
	}
	//�������� �� ����� �����������
	bool isLow() const {
		if (!isSquare())
			return false;
		for (int i = 0; i < _rows; i++)
			for (int j = 0; j < _cols; j++)
				if (i < j && _data[i][j] != 0)
					return false;
		return true;
	}// �������� �� ������������� �������
	bool isTriangular() const {
		if (isUpper())
			return true;
		if (isLow())
			return true;
		return false;
	}//�������� �� �������������� �������
	bool isSymmetric() const {
		if (!isSquare())
			return false;
		for (int i = 0; i < _rows; i++)
			for (int j = 0; j < i + 1; j++)
				if (_data[i][j] != _data[j][i])
					return false;
		return true;

	} //�������� �� ���������������� �������
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

