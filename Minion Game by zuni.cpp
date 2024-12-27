#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <windows.h>
#include <iomanip>
#include "myfile.h"
using namespace std;
//Task 1:
/*void createAndPrintTriangle(int size) {
	int i, j;
	int** m = new int*[size];
	for (i=0; i < size; i++)
		m[i] = new int[size];
	for (i = 0; i < size; i++) {
		for (j = 0; j <=i; j++) {
			m[i][j] = 0;
		}
	}
	for (i =size-1; i>=0; i--) {
		for (j = 0; j <= i; j++) {
			if (j == 0 || i == size - 1) {
				m[i][j] = 1;
			}
			else {
				m[i][j] = m[i + 1][j] + m[i][j - 1];
			}
		}
	}
	for (i = 0; i < size; i++) {
		for (j = 0; j <=i; j++) {
			cout << setw(5)<< m[i][j];
		}
		cout << endl;
	}
	int r = size - 1;
	for (int i = 0; i < size; i++) {
		int c = i;
		int l = (size - i) * 5;
		for (; l >= 0; l++); {
			cout << " ";
		}
		l = -5;
		for (int k = 0; k < i + 1; k++) {
			int spaces = 0;
			if(spaces<k){
				cout << "     ";
				cout << "  ";
			}
			cout << setw(3) << m[r][c];
			cout << "  ";
			r--;
			c--;
		}
		r = size - 1;
		cout << endl;
		cout << endl;
		cout << endl;
	}
	for (i=0; i < size; i++)
		delete[]m[i];
	delete[]m;
}
int main() {
	int s;
	cout << "Enter size of teiangle:" << endl;
	cin >> s;
	createAndPrintTriangle(s);
	return 0;
}*/
//Task 2:
const int gridsize = 20;
class Minion {
	int speed;
	bool life;
	int power;
	int color;
	int x;
	int y;
public:
	Minion() {
		speed = 1;
		life = true;
		power = rand() % 4 + 1;
		color = ConsoleColor(rand() % 15);
		x = rand() % 20;
		y = rand() % 20;
	}
	//-----------------Setter Funs-------------------
	void setcol(int col) {
		x = col;
	}
	void setrow(int row) {
		y = row;
	}
	void setspeed(int newspeed) {
		speed = newspeed;
	}
	void setpower(int newpower) {
		power = newpower;
	}
	void setlife(bool newlife) {
		life = newlife;
	}
	void setcolor(ConsoleColor newcolor) {
		color = newcolor;
	}
	//----------------------Getter Funs-------------------
	int getcol()const {
		return x;
	}
	int getrow()const {
		return y;
	}
	int getspeed()const {
		return speed;
	}
	int getpower()const {
		return power;
	}
	int getcolor()const {
		return color;
	}
	bool getlife()const {
		return life;
	}
	//---------------Make Minion-------------------
	void makeminion() {
		SetColor(color, black);
		setCursorAt(x, y);
		char c = 2;
		cout << c;
	}
	//---------Update Speed and Life-------------
	void updatespeedandlife()const {
		Minion M[100];
		for (int i = 0; i < 100; i++) {
			for (int j = i + 1; j < 100; j++) {
				if (M[i].getlife() && M[j].getlife() && M[i].getcol() == M[j].getcol() && M[i].getrow() == M[j].getrow()) {
					if (M[i].getpower() == M[j].getpower()) {
						M[i].setlife(false);
						M[j].setlife(false);
					}
					else if (M[i].getpower() == 1 && M[j].getpower() == 5) {
						M[j].setlife(false);
						M[i].setspeed(speed + 1);
					}
					else if (M[i].getpower() == 5 && M[j].getpower() == 1) {
						M[i].setlife(false);
						M[j].setspeed(speed + 1);
					}
					else if (M[i].getpower() > M[j].getpower()) {
						M[j].setlife(false);
						M[i].setspeed(speed + 1);
					}
					else if (M[i].getpower() < M[j].getpower() == 1) {
						M[i].setlife(false);
						M[j].setspeed(speed + 1);
					}
				}
			}
		}
	}
	//----------------Move minnions-----------------------
	void moveMinions() {
		Minion M[100];
		for (int i = 0; i < 100; i++)
		{
			if (M[i].getlife())
			{
				int col = M[i].getcol();
				int row = M[i].getrow();
				if (col >= 0 && col < 20 && row >= 0 && row < 20)			// Ensure the minion's coordinates are within the grid boundaries
				{
					//trackGrid[col][row] = nullptr; // Set the previous position to nullptr
				}
				int direction = rand() % 3 + 1;        //1 for up , 2 for down , 3 forleft ,4 for right;   
				switch (direction) {
				case 1: {			//up
						y = y - speed;
						if (y < 0)    y = (y + 20) - speed;
						break;
					}
				case 2: {			//down
						y = y + speed;
						if (y > 20)			y = (y - 20) + speed;
						break;
					}
				case 3: {			//left
						x = x - speed;
						if (x < 0)    x = (x + 20) - speed;
						break;
					}
				case 4: {			//right
						x = x + speed;
						if (x > 20)			y = (x - 20) + speed;
						break;
					}
				}
			}
			M[i].setcol(x);
			M[i].setrow(y);
			int col = M[i].getcol();
			int row = M[i].getrow();
			//if (col >= 0 && col < 20 && row >= 0 && row < 20)
				//trackGrid[col][row] = &M[i];
		}
	}
	void updateTrackGrid(Minion M[], Minion* trackGrid[20][20]) {
		for (int i = 0; i < 20; i++) {
			for (int j = 0; j < 20; j++) {
				trackGrid[i][j] = nullptr; // Reset track grid
			}
		}

		for (int i = 0; i < 100; i++) {
			if (M[i].getlife()) {
				int col = M[i].getcol();
				int row = M[i].getrow();
				// Ensure the minion's coordinates are within the grid boundaries
				if (col >= 0 && col < gridsize && row >= 0 && row < gridsize) {
					trackGrid[col][row] = &M[i];
				}
			}
		}
	}
	bool continueGame(Minion M[]) {
		int Count = 0;
		for (int i = 0; i < 100; i++) {
			if (M[i].getlife()) {
				Count++;
			}
		}
		if (Count > 1) {
			return true;
		}
		return false;
	}
};
Minion* trackGrid[gridsize][gridsize];
/*int main() {
	Minion m;
	Minion();
	int i, j, x, y, pow, col;
	Minion M[100];
	for (i = 0; i < 100; i++) {
		pow = rand() % 4 + 1;
		col = rand() % 15;
		x = rand() % 19 + 1;
		y = rand() % 19 + 1;
		m.setcol(x);
		m.setrow(y);
		m.setpower(pow);
		m.setcolor(col);
		m.setspeed(1);
		m.setlife(true);
		m.getcol();
		m.getrow();
		m.getpower();
		m.getcolor();
		m.getspeed();
		m.getlife();
		m.makeminion();
		m.updatespeedandlife();
	}
	m.moveMinions(M, &trackGrid[20][20]);
	m.updateTrackGrid( M, &trackGrid[20][20]);
	m.updatespeedandlife();
	m.continueGame(M);
	return 0;
}*/
int main() {
	srand(time(NULL));
	Minion M[100];
	while (true) {
		system("cls");
		for (int i = 0; i < 100; ++i) {
			if (M[i].getlife()) {
				M[i].moveMinions();
				M[i].makeminion();

				for (int j = 0; j < 100; j++) {
					if (i != j && M[i].getlife()) {
						M[i].updatespeedandlife();
					}
				}
			}
		}
		Sleep(500);
	}
	return 0;
}