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
	matrix(int rows, int cols); //конструстор создающий пустую матрицу с нужным количеством строк и столбцов;
		
	//конструктор для удобного занесения элементов в матрицу
	matrix(int rows, int cols, vector<vector<double>> data);
		

	//доступ к элементу матрицы через стандартный метод at
	double& at(int row, int col);

	//перегрузка оператора вывода
	friend ostream& operator <<(ostream& out, const matrix& mtx);  // стандартная штука, friend- с помощью него мы получаем доступ к полям класса
	
	

	friend istream& operator >>(istream& in, matrix& mtx);  // ввод в консоль матрицы;
	//сложение матриц 
	friend matrix operator+(matrix& leftop, matrix rightop);  
	//скопировал сложение и заменил знак (вычитание матриц) 
	friend matrix operator-(matrix& leftop, matrix rightop);  
	//оператор += функция класса 
	matrix& operator+=(matrix mtx);   
	//оператор -= функция класса
	matrix& operator-=(matrix mtx);
	//умножение матрицы на число 
	friend matrix operator*(matrix& mtx, double s); 
	friend matrix operator*(double s, matrix& mtx); 
	// деление на скаляр вызывает умножение, но скаляр на оборот
	friend matrix operator/(matrix& mtx, double s); 
	// умножение матрицу на матрицу 
	friend matrix operator*(const matrix& left, const matrix& right); 
	//умножение поэлементное 
	matrix mulByEl(const matrix& right);   
	matrix divByEl(const matrix& right); 
	//оператор сравнения матриц
	friend bool operator==(const matrix& left, const matrix& right); 
	// оператор неравенства матриц
	friend bool operator!=(const matrix& left, const matrix& right); 
	// в степень можно возводить только квадратные матрицы. Оператор возведения в степень.
	//оператор возведения в степень матрицы
	friend matrix operator^(const matrix& mtx, int s); 
	//поэлементное возведение в степень
	matrix powByEl(int s); 
	//транспонирование матрицы
	matrix transpose(); 
	//метод проверки матрицы на ее тип (в данном случае на квадратную)
	bool isSquare()  const; 
	//вспомогательная функция для получения обратной матрицы
	static matrix E(int size);       //метод отвязан от объекта, возвращает матрицу размера size*size(единичную)
	//обратная матрица
	matrix inv() const; 
	double det() const; 	
	friend matrix operator/(const matrix& left, const matrix& right);
	//норма матрицы 
	//i -номер нормы 
	//1-столбцовая норма 
	//2- бесконечная норма 
	//3- сферическая норма 
	double norm(int i) const; 
	double& operator ()(int i, int j); //работает с неконстантными объектами 
	double operator ()(int i, int j) const;     //работает с константными объектами 
	int rows()const; //возращает размер сколько строк 
	int cols()const; //возвращает сколько столбцов
	vector<double>get_row(int i) const;                     //возвращает i строку 
	vector<double>get_col(int j) const;                     //возвращает j столбец
	//проверка является  матрица диагональной или нет 
	bool isDiagonal() const;
	//проверка является матрица единичной или нет
	bool isIdentity()const; 
	//проверка на нулевую матрицу
	bool isZero() const; 
	//проверка на верхне треугольную
	bool isUpper() const; 
	//проверка на нижне треугольную
	bool isLow() const; 
	// проверка на треугольность матрицы
	bool isTriangular() const; 
	//проверка на симметричность матрицы
	bool isSymmetric() const;
	//проверка на кососимметричную матрицу
	bool isSkewSymmetric() const; 
};

