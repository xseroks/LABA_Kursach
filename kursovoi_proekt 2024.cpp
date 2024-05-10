#include <iostream>
#include <vector>
#include "Matrix.h"
#include<Windows.h>
#include<string>
int main()
{
	SetConsoleCP(1251);            
	setlocale(LC_ALL, "RUS");
    bool exit = false;
	string ch;
	cout << "Здравствуйте, вы попали в программу работы с матрицами!" << endl;
	cout << "Введите название матрицы и ее размер: ";
	cout << endl;
	cout << "Что вы желаете сделать?" << endl;
	cout << "1 - Сложение матриц" << endl;
	cout << "2 - Вычитание матриц" << endl;
	cout << "3 - Умножение матрицы на число" << endl;
	cout << "4 - Умножение матрицы на матрицу" << endl;
	cout << "5 - Поэлементное умножение элементов в матрице" << endl;
	cout << "6 - Деление матрицы на число" << endl;
	cout << "7 - Деление поэлементное матрицы на матрицу" << endl;
	cout << "8 - Сравнение матриц" << endl;
	cout << "9 - Возведение матрицы в степень" << endl;
	cout << "10 - Поэлементное возведение элементов в матрице" << endl;
	cout << "11 - Транспонирование матрицы" << endl;
	cout << "12 - Обратная матрица" << endl;
	cout << "13 - Норма матрицы" << endl;
	cout << "14 - Проверка типа матрицы" << endl;
	cout << "0 - завершить работу" << endl;
	
	while(!exit) //Вечный цикл для ввода пользователем выбора действия программы
	{	
		cout << "Ваш выбор--->";
		cin >> ch;

		if ((ch == "0") || (ch == "1") || (ch == "2") || (ch == "3") || (ch == "4") || (ch == "5") || (ch == "6") || (ch == "7") || (ch == "8") || (ch == "9") || (ch == "10") || (ch == "11") || (ch == "12")|| (ch == "13")|| (ch == "14")) {        //Условия для выхода из вечного цикла
		
		}
		else {
			cout << "Выбрали неверное поле меню, попробуйте еще раз!!!" << endl;
			continue;
		}

		switch (stoi(ch)) {
		case 0:
			exit = true;
			break;
		case 1: {
			cout << "Введите размер матриц:\n";
			int row;
			int col;

			cin >> row >> col;
			cout << "Введите первую матрицу\n";
			matrix A(row, col);
			cin >> A;
			cout << "Введите вторую матрицу\n";
			matrix B(row, col);
			cin >> B;

			cout << "Результат операции сложения : \n" << A + B << "\n";

			break;
		}
		case 2: {
			cout << "Введите размер матриц:\n";
			int row;
			int col;

			cin >> row >> col;
			cout << "Введите первую матрицу из которой хотите вычесть\n";
			matrix A(row, col);
			cin >> A;
			cout << "Введите вторую матрицу\n";
			matrix B(row, col);
			cin >> B;

			cout << "Результат операции вычитания: \n" << A - B << "\n";

			break;
		}
		case 3: {
			cout << "Введите размер матрицы:\n";
			int row;
			int col;

			cin >> row >> col;
			cout << "Введите матрицу\n";
			matrix A(row, col);
			std::cin >> A;
			cout << "Введите число на которое хотите умножить\n";
			int s;
			cin >> s;

			cout << "Результат операции умножения матрицы на число: \n" << A * s << "\n";

			break;
		}
		case 4:{
			cout << "Введите размер матриц:\n";
			int row;
			int col;

			cin >> row >> col;
			cout << "Введите первую матрицу\n";
			matrix A(row, col);
			cin >> A;
			cout << "Введите вторую матрицу\n";
			matrix B(row, col);
			cin >> B;

			cout << "Результат операции умножения матрицы на матрицу: \n" << A * B << "\n";
			break;
		}
		case 5: {
			cout << "Введите размер матриц:\n";
			int row;
			int col;

			cin >> row >> col;
			cout << "Введите первую матрицу\n";
			matrix A(row, col);
			cin >> A;
			cout << "Введите вторую матрицу\n";
			matrix B(row, col);
			cin >> B;
			cout << "Результат поэлементного умножения мытрицы на матрицу:\n" << A.mulByEl(B)<<endl;
			break;
		}
		case 6:
		{
			cout << "Введите размер матрицы:\n";
			int row;
			int col;

			cin >> row >> col;
			cout << "Введите матрицу\n";
			matrix A(row, col);
			std::cin >> A;
			cout << "Введите число на которое хотите разделить\n";
			int s;
			cin >> s;
			cout << "Результат операции деления матрицы на число: \n" << A*(1.0/s)<< "\n";
			break;
		}
		case 7:{
			cout << "Введите размер матриц:\n";
			int row;
			int col;

			cin >> row >> col;
			cout << "Введите первую матрицу\n";
			matrix A(row, col);
			cin >> A;
			cout << "Введите вторую матрицу\n";
			matrix B(row, col);
			cin >> B;

			cout << "Результат операции деления матрицы на матрицу: \n" << A.divByEl(B) << "\n";

			break;
		}
			break;
		case 8: {
			cout << "Введите размер матриц:\n";
			int row;
			int col;

			cin >> row >> col;
			cout << "Введите первую матрицу\n";
			matrix A(row, col);
			cin >> A;
			cout << "Введите вторую матрицу\n";
			matrix B(row, col);
			cin >> B;
			if (A!=B)
				cout << "Матрицы не равны"<<endl;
			else
			cout << "Матрицы равны"<<endl;
			
			break;
		}
		case 9:{
			cout << "Введите размер матрицы:\n";
			int row;
			int col;

			cin >> row >> col;
			cout << "Введите матрицу\n";
			matrix A(row, col);
			std::cin >> A;
			cout << "Введите число на которое хотите возвести матрицу\n";
			int s;
			cin >> s;
			cout << "Результат операции возведения матрицы в степень: \n" << (A^s)<< "\n";
			break;
		}
		case 10:{
			cout << "Введите размер матрицы:\n";
			int row;
			int col;

			cin >> row >> col;
			cout << "Введите матрицу\n";
			matrix A(row, col);
			std::cin >> A;
			cout << "Введите число на которое хотите возвести матрицу в степень поэлементно\n";
			int s;
			cin >> s;
			cout << "Результат операции поэлементного возведения матрицы в степень: \n" << A.powByEl(s) << "\n";
			break;
		}
		case 11:{
			cout << "Введите размер матрицы:\n";
			int row;
			int col;

			cin >> row >> col;
			cout << "Введите матрицу\n";
			matrix A(row, col);
			std::cin >> A;
		
			cout << "Результат операции транспонирования матрицы: \n" << A.transpose()<< "\n";
			break;
		}
		case 12:{
			cout << "Введите размер матрицы:\n";
			int row;
			int col;

			cin >> row >> col;
			cout << "Введите матрицу\n";
			matrix A(row, col);
			std::cin >> A;

			cout << "Результат обратной матрицы: \n" << A.inv() << "\n";
			break;
		}
		case 13: {
			cout << "Введите размер матрицы:\n";
			int row;
			int col;

			cin >> row >> col;
			cout << "Введите матрицу\n";
			matrix A(row, col);
			std::cin >> A;
			int i;
			cout << "Выберите норму матрицы:" << endl;
			cout << "1 - столбцовая норма" << endl;
			cout << "2 - бесконечная норма" << endl;
			cout << "3 - сферическая норма" << endl;
			cin >> i;
			if (i == 1) {
				cout << A.norm(1) << endl;
			}
			if (i == 2) {
				cout << A.norm(2) << endl;
			}
			if (i == 3) {
				cout << A.norm(3) << endl;
			}
			break; 
		}
		case 14:
		{
			cout << "Введите размер матрицы:\n";
			int row;
			int col;

			cin >> row >> col;
			cout << "Введите матрицу\n";
			matrix A(row, col);
			std::cin >> A;
			if (A.isDiagonal())
			{
				cout << "Матрица является диагональной" << endl;
			}
			if (A.isIdentity())
				cout << "Матрица является единичной" << endl;
			if (A.isSquare())
				cout << "Матрица является квадратной" << endl;
			if(A.isZero())
				cout << "Матрица является нулевой" << endl;
			if(A.isSkewSymmetric())
				cout << "Матрица является кососимметричной" << endl;
			if(A.isSymmetric())
				cout << "Матрица является симметричной" << endl;
			if (A.isTriangular())
				cout << "Матрица является треугольной" << endl;
			if(A.isUpper())
				cout << "Матрица является верхне треугольной" << endl;
			if(A.isLow())
				cout << "Матрица является нижне треугольной" << endl;
			break;
		}
		default:
			cout << "Ввод не понятен,повторите" << endl;
			break;
		}
	}

	return 0;
}

