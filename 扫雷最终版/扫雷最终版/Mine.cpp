#include "Mine.h"
//private
int Mine::NumberOfBoom(int row, int col)
{
	int direction_X[8] = { 1,-1,1,-1,1,-1,0,0, };
	int direction_Y[8] = { 1,-1,-1,1,0,0,-1,1, };

	int count_boom = 0;
	for (int i = 0;i < 8;i++) {
		int temp_row = row + direction_Y[i];
		int temp_col = col + direction_X[i];
		if (matrix[temp_row][temp_col] == -1) {
			count_boom++;
		}
	}

	return count_boom;
}

void Mine::Code()
{
	for (int i = 1;i <= this->row;i++) {//初始加密
		for (int j = 1;j <= this->col;j++) {
			matrix[i][j] += 20;
		}
	}
}

void Mine::Decode()
{
	for (int i = 1;i <= this->row;i++) {//初始加密
		for (int j = 1;j <= this->col;j++) {
			matrix[i][j] -= 20;
		}
	}
}

void Mine::Code(int row, int col)
{
	matrix[row][col] += 20;
}

void Mine::Decode(int row, int col)
{
	matrix[row][col] -= 20;
}

void Mine::sign(int row,int col)
{
	matrix[row][col] += 10;
}

void Mine::unsign(int row, int col)
{
	matrix[row][col] -= 10;
}

void Mine::InitImage()
{
	initgraph(row * size, col * size, SHOWCONSOLE);//页面上输出图像并且同时打开控制台
	for (int i = 0; i < 12; i++) {//初始化图片
		char filename[20];
		sprintf_s(filename, "%d.PNG", i);
		loadimage(&img[i], filename, 50, 50);
	}
}

void Mine::LayMines()
{
	srand(time(nullptr));
	for (int i = 0;i < this->boom;) {
		int rand_row = rand() % this->row + 1;//[1,row]
		int rand_col = rand() % this->col + 1;//[1,col]
		if (matrix[rand_row][rand_col] == 0) {
			matrix[rand_row][rand_col] = -1;
			i++;
		}
	}
}

void Mine::CountBoom()
{
	for (int i = 1;i <= row;i++) {
		for (int j = 1;j <= col;j++) {
			if (matrix[i][j] != -1) {
				matrix[i][j] = NumberOfBoom(i, j);
			}
		}
	}
}

int Mine::Click()
{
	MOUSEMSG msg;
	while (1) {
		msg = GetMouseMsg();
		int r = msg.y / size + 1;
		int c = msg.x / size + 1;//映射

		switch (msg.uMsg) {
		case WM_LBUTTONDOWN://左键
			if (count == 0 && matrix[r][c] == 19) {//如果第一个是雷
				if (boom <= sqrt(this->row * this->col) ) {//如果雷比较少
					Random_Prevent(r, c);
					if (matrix[r][c] == 20) {
						openZero(r, c);
					}
					else {
						Decode(r, c);
						count++;
					}
				}
				else {//如果雷比较多
					Inorder_Prevent(r, c);
					if (matrix[r][c] == 20) {
						openZero(r, c);
					}
					else {
						Decode(r, c);
						count++;
					}
				}
			}
			else if (matrix[r][c] >= 19 && matrix[r][c] <= 28) {//第一个不是雷以及后序的左键点击

				if (matrix[r][c] == 20) {
					openZero(r, c);
				}
				else {
					Decode(r, c);
					count++;
				}

			}
			return matrix[r][c];
			break;
		case WM_RBUTTONDOWN://右键
			if (matrix[r][c] >= 19 && matrix[r][c] <= 28) {//标记
				sign(r, c);
			}
			else if (matrix[r][c] >= 29 && matrix[r][c] <= 38) {//取消标记
				unsign(r, c);
			}
			return matrix[r][c];
			break;
		}
	}
	return 0;
}

bool Mine::isValid(int row, int col)
{
	if (row <= this->row && col <= this->col && row >= 1 && col >= 1) {
		return true;
	}
	else {
		return false;
	}
}

void Mine::DrawMatrix()//在窗体中输出图片
{
	for (int i = 1;i <= this->row;i++) {
		for (int j = 1;j <= this->col;j++) {
			if (matrix[i][j] == -1) {//雷
				putimage((j - 1) * size, (i - 1) * size, &img[10]);
			}
			else if (matrix[i][j] >= 0 && matrix[i][j] <= 8) {//数字
				putimage((j - 1) * size, (i - 1) * size, &img[matrix[i][j]]);
			}
			else if (matrix[i][j] >= 19 && matrix[i][j] <= 28) {//加密的显示
				putimage((j - 1) * size, (i - 1) * size, &img[11]);
			}
			else if (matrix[i][j] >= 29 && matrix[i][j] <= 38) {//标记后的显示
				putimage((j - 1) * size, (i - 1) * size, &img[9]);
			}

		}
	}
}

void Mine::Random_Prevent(int row, int col)
{
	matrix[row][col] = 20;//删掉掉雷

	Decode();//解密

	srand(time(nullptr));
	while (1) {
		int r = rand() % this->row + 1;
		int c = rand() % this->col + 1;
		if (matrix[r][c] == 0 && (r != row || c != col)) {
			matrix[r][c] = -1;//埋雷
			break;
		}
	}

	CountBoom();//算雷

	Code();
}

void Mine::Inorder_Prevent(int row, int col)
{
	matrix[row][col] = 20;//删掉掉雷

	Decode();//解密

	for (int i = 1;i <= this->row;i++) {
		for (int j = 1;j <= this->col;j++) {
			if (matrix[i][j] != -1 && (i != row || j != col)) {//不是雷且和之前不同

				matrix[i][j] = -1;//埋雷

				CountBoom();//算雷

				Code();

				return;
			}
		}
	}

}

bool Mine::IsWin()
{
	return count == row * col - boom;
}

void Mine::openZero(int row, int col)
{
	Decode(row, col);
	count++;

	for (int i = 0; i < 8; i++) {
		int x = col + direction_X[i];
		int y = row + direction_Y[i];
		if (isValid(y, x) && (matrix[y][x] >= 19 && matrix[y][x] <= 28)) { //有效范围且处于加密状态
			if (matrix[y][x] == 20) {
				openZero(y, x);
			}
			else {
				Decode(y, x);
				count++;
			}
		}
	}
}

//public

Mine::Mine(int row, int col, int boom)
{
	this->row = row;
	this->col = col;
	this->boom = boom;
	matrix.resize(row + 2, vector<int>(col + 2, 0));//这里多申请两行两列的空间是为了方便后面判断
}

void Mine::Inital()
{
	LayMines();

	CountBoom();

	Code();

	InitImage();

}

void Mine::Test()
{
	for (int i = 1;i <= this->row;i++) {
		for (int j = 1;j <= this->col;j++) {
			cout << setw(4) << left << matrix[i][j];
		}
		cout << endl;
	}
}

void Mine::Play()
{
	DrawMatrix();
	while (1) {

		int click = Click();
		DrawMatrix();
		if (click == -1) {
			DrawMatrix();//注意此时仍然要更新图片
			MessageBox(NULL, "You are failed!", "Exit", MB_OK);
			exit(0);
		}
		else if (IsWin()) {
			DrawMatrix();//更新图片
			MessageBox(NULL, "You are Win!", "Exit", MB_OK);
			exit(0);
		}
	}
}









