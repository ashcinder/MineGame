#include "Mine.h"
#include <iostream>
using namespace std;

int main() {
	int row, col, boom;
	cout << "�������С��С�ը������" << endl;
	cin >> row >> col >> boom;

	Mine mine(row, col, boom);
	mine.Inital();
	mine.Test();
	mine.Play();
}