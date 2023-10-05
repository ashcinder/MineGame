#include "Mine.h"
#include <iostream>
using namespace std;

int main() {
	int row, col, boom;
	cout << "请输入行、列、炸弹数：" << endl;
	cin >> row >> col >> boom;

	Mine mine(row, col, boom);
	mine.Inital();
	mine.Test();
	mine.Play();
}