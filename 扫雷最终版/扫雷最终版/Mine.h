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

	void Code();//加密

	void Decode();//解密

	void Code(int row, int col);//局部加密

	void Decode(int row, int col);//局部解密

	void sign(int row,int col);//标记
	
	void unsign(int row,int col);//取消标记

	int NumberOfBoom(int row, int col);//计算周围雷数

	void InitImage();//初始化图像

	void LayMines();//布雷

	void CountBoom();//计算矩阵九宫格雷数

	int Click();//识别鼠标点击

	void DrawMatrix();//画图

	void openZero(int row, int col);//链式打开0

	bool isValid(int row, int col);//判断是否在范围内

	void Random_Prevent(int row, int col);//随机生成

	void Inorder_Prevent(int row, int col);//有序生成

	bool IsWin();//判断是否成功

public:

	Mine(int row = 10, int col = 10, int boom = 10);//构造函数

	void Inital();//初始化，作为对外接口

	void Test();//测试输出

	void Play();//模拟游玩过程

};