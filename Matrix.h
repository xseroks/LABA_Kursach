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
	matrix(int rows, int cols); //����������� ��������� ������ ������� � ������ ����������� ����� � ��������;
		
	//����������� ��� �������� ��������� ��������� � �������
	matrix(int rows, int cols, vector<vector<double>> data);
		

	//������ � �������� ������� ����� ����������� ����� at
	double& at(int row, int col);

	//���������� ��������� ������
	friend ostream& operator <<(ostream& out, const matrix& mtx);  // ����������� �����, friend- � ������� ���� �� �������� ������ � ����� ������
	
	

	friend istream& operator >>(istream& in, matrix& mtx);  // ���� � ������� �������;
	//�������� ������ 
	friend matrix operator+(matrix& leftop, matrix rightop);  
	//���������� �������� � ������� ���� (��������� ������) 
	friend matrix operator-(matrix& leftop, matrix rightop);  
	//�������� += ������� ������ 
	matrix& operator+=(matrix mtx);   
	//�������� -= ������� ������
	matrix& operator-=(matrix mtx);
	//��������� ������� �� ����� 
	friend matrix operator*(matrix& mtx, double s); 
	friend matrix operator*(double s, matrix& mtx); 
	// ������� �� ������ �������� ���������, �� ������ �� ������
	friend matrix operator/(matrix& mtx, double s); 
	// ��������� ������� �� ������� 
	friend matrix operator*(const matrix& left, const matrix& right); 
	//��������� ������������ 
	matrix mulByEl(const matrix& right);   
	matrix divByEl(const matrix& right); 
	//�������� ��������� ������
	friend bool operator==(const matrix& left, const matrix& right); 
	// �������� ����������� ������
	friend bool operator!=(const matrix& left, const matrix& right); 
	// � ������� ����� ��������� ������ ���������� �������. �������� ���������� � �������.
	//�������� ���������� � ������� �������
	friend matrix operator^(const matrix& mtx, int s); 
	//������������ ���������� � �������
	matrix powByEl(int s); 
	//���������������� �������
	matrix transpose(); 
	//����� �������� ������� �� �� ��� (� ������ ������ �� ����������)
	bool isSquare()  const; 
	//��������������� ������� ��� ��������� �������� �������
	static matrix E(int size);       //����� ������� �� �������, ���������� ������� ������� size*size(���������)
	//�������� �������
	matrix inv() const; 
	double det() const; 	
	friend matrix operator/(const matrix& left, const matrix& right);
	//����� ������� 
	//i -����� ����� 
	//1-���������� ����� 
	//2- ����������� ����� 
	//3- ����������� ����� 
	double norm(int i) const; 
	double& operator ()(int i, int j); //�������� � �������������� ��������� 
	double operator ()(int i, int j) const;     //�������� � ������������ ��������� 
	int rows()const; //��������� ������ ������� ����� 
	int cols()const; //���������� ������� ��������
	vector<double>get_row(int i) const;                     //���������� i ������ 
	vector<double>get_col(int j) const;                     //���������� j �������
	//�������� ��������  ������� ������������ ��� ��� 
	bool isDiagonal() const;
	//�������� �������� ������� ��������� ��� ���
	bool isIdentity()const; 
	//�������� �� ������� �������
	bool isZero() const; 
	//�������� �� ������ �����������
	bool isUpper() const; 
	//�������� �� ����� �����������
	bool isLow() const; 
	// �������� �� ������������� �������
	bool isTriangular() const; 
	//�������� �� �������������� �������
	bool isSymmetric() const;
	//�������� �� ���������������� �������
	bool isSkewSymmetric() const; 
};

