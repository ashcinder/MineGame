#pragma once
#include <vector>
#include <iostream>
#include <iomanip>
#include <graphics.h>
#pragma comment(lib, "winmm.lib")

using namespace std;
class Mine {
private:
	vector<vector<int>> matrix;

	int row;
	int col;
	int boom;

	IMAGE img[12];

	int size = 50;
	int count = 0;

	int direction_X[8] = { 1,-1,1,-1,1,-1,0,0, };
	int direction_Y[8] = { 1,-1,-1,1,0,0,-1,1, };	
	
private:

	void Code();//����

	void Decode();//����

	void Code(int row, int col);//�ֲ�����

	void Decode(int row, int col);//�ֲ�����

	void sign(int row,int col);//���
	
	void unsign(int row,int col);//ȡ�����

	int NumberOfBoom(int row, int col);//������Χ����

	void InitImage();//��ʼ��ͼ��

	void LayMines();//����

	void CountBoom();//�������Ź�������

	int Click();//ʶ�������

	void DrawMatrix();//��ͼ

	void openZero(int row, int col);//��ʽ��0

	bool isValid(int row, int col);//�ж��Ƿ��ڷ�Χ��

	void Random_Prevent(int row, int col);//�������

	void Inorder_Prevent(int row, int col);//��������

	bool IsWin();//�ж��Ƿ�ɹ�

public:

	Mine(int row = 10, int col = 10, int boom = 10);//���캯��

	void Inital();//��ʼ������Ϊ����ӿ�

	void Test();//�������

	void Play();//ģ���������

};