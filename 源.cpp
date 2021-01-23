#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#define MX 70
#define MY 30//�߽�ֵ
#define enemy_members 13//��������
#define fire_members 26//ǹ������
#define enemy_speed 1//�����ٶ�
#define fire_speed 2//ǹ���ٶ�
#pragma warning(disable : 4996)
void printall(int a[][MX]);//��ӡȫ��
void gotoxy(int x, int y);//����ƶ�
void HideCursor();//���ع��
void change_position(int x, int y, int a[][MX]);//�ı�ɻ�λ��
int dead(int x, int y, int a[][MX]);//�����ж�
void fire(int x, int y, int f[][3]);//�жϿ���λ��
void fire_print(int f[][3], int a[][MX]);//��ӡ����
void produce_enemy(int e[][3], int m);//��������
void enemy_print(int e[][3], int a[][MX]);//��ӡ����
void hit(int a[][MX], int e[][3], int f[][3]);//�жϻ���
static int scores = 0;
int main()
{
	int  i, j, m, a[MY][MX];
	register char input;
	while (1) {
		int f[fire_members][3], e[enemy_members][3];
		int x = MX/2, y = MY/3*2;
		int flag = 0;
		scores = 0;
		
		
		//��ʼ������,����
		for (i = 0; i <fire_members; i++) { f[i][0] = 0; }
		for (i = 0; i < enemy_members; i++) { e[i][0] = 0; }
		for (i = 1; i < MY - 1; i++) {
			for (j = 2; j < MX - 2; j++) {
				a[i][j] = 0;
			}
		}
		
		while (dead(x, y, a)) {
			gotoxy(0, 0);
			m = rand() % 100 + 2;
			HideCursor();
			if (kbhit()) {
				input = getch();
				switch (input) {
				case 75: {x = x - 2; break; }
				case 77: {x = x + 2; break; }
				case 72: {y = y - 2; break; }
				case 80: {y = y + 2; break; } 
				default: break;
				}
			}
			fire(x, y, f);
			produce_enemy(e, m);
			enemy_print(e, a);
			fire_print(f, a);
			hit(a, e, f);
			change_position(x, y, a);
			//��ʼ���߽�
			for (i = 1; i <= MY - 1; i++) {
				a[i][0] = 2;
				a[i][1] = 2;
				a[i][MX - 1] = 2;
				a[i][MX - 2] = 2;
			}
			for (i = 1; i < MX - 1; i++) {
				a[0][i] = 3;
				a[MY - 1][i] = 3;
			}
			printall(a);

		}
		if (!dead(x, y, a)) {
			system("cls");
			for (i = 0; i <= 13; i++) printf("\n");
			for (i = 0; i <= 40; i++) printf(" ");
			printf("Game Over!  ��ĵ÷�Ϊ��%d\n                                         ��ENTER����һ��  ��ESC�˳���", scores);
			while (1) {
				if (getch() == 27) { flag = 1; break; }
				else if (getch() == 13) { system("cls"); break; }
				else continue;
			}
		}
		if (flag) break;
	}

}

void printall(int a[][MX]) {
	int i, j;
	for (i = 0; i <= MY - 1; i++) {
		for (j = 0; j <= MX - 1; j++) {
			if (a[i][j] == 0) printf(" ");
			if (a[i][j] == 1 || a[i][j] == 5) printf("*");
			if (a[i][j] == 2 || a[i][j] == 4) printf("|");
			if (a[i][j] == 3) printf("-");
		}
		if (i == 0) printf(" ��ĵ÷�Ϊ��%d", scores);
		printf("\n");
	}
}

void change_position(int x, int y, int a[][MX]) {
	int i, j;
	for (i = 1; i < MY-1; i++) {
		for (j = 2; j <MX-2 ; j++) {
			if (a[i][j] != 4 && a[i][j] != 5)  a[i][j] = 0;
		}
	}
	for (i = y; i < y + 4; i++) {
		for (j = x - (i - y); j <= x + (i - y); j++) {
			a[i][j] = 1;
		}
	}
	a[y + 4][x - 2] = 1;
	a[y + 4][x + 2] = 1;
}

int dead(int x, int y, int a[][MX]) {
	if (x >= 6 && x <= MX - 6 && y >= 1 && y <= MY - 6 && a[y - 1][x] != 5 && a[y][x + 1] != 5 && a[y][x - 1] != 5 && a[y + 1][x - 2] != 5 && a[y + 1][x + 2] != 5 && a[y + 2][x - 3] != 5 && a[y + 2][x + 3] != 5) {
		return 1;
	}
	else {
		return 0;
	}
}

void fire(int x, int y, int f[][3]) {
	int i, j;
	for (i = 0; i < fire_members; i++) {
		if (f[i][0] == 0) {
			f[i][0] = 1;
			f[i][1] = x + 1;
			f[i][2] = y;
			for (j = i; j <= fire_members; j++) {
				if (f[j][0] == 0) {
					f[j][0] = 1;
					f[j][1] = x - 1;
					f[j][2] = y;
					break;
				}
			}
			break;
		}
	}
}

void fire_print(int f[][3], int a[][MX]) {
	int i;
	for (i = 0; i < fire_members; i++) {
		if (f[i][0]) {
			if (f[i][2] > 0) {
				a[f[i][2]][f[i][1]] = 4;
				a[f[i][2] + fire_speed][f[i][1]] = 0;
			}
			else {
				f[i][0] = 0;
				a[f[i][2] + fire_speed][f[i][1]] = 0;
			}
		}
	}
	for (i = 0; i < fire_members; i++) {
		f[i][2]-= fire_speed;
	}

}

void produce_enemy(int e[][3], int m) {
	int i;
	if (3 < m&&m < MX - 3) {
		for (i = 0; i < enemy_members; i++) {
			if (e[i][0] == 0) {
				e[i][0] = 1;
				e[i][1] = m;
				e[i][2] = 2;
				break;
			}
		}
	}
}

void enemy_print(int e[][3], int a[][MX]) {
	int i;
	for (i = 0; i < enemy_members; i++) {
		if (e[i][0]) {
			if (e[i][2] < MY - 1) {
				a[e[i][2]][e[i][1]] = 5;
				a[e[i][2] - 1][e[i][1] + 1] = 5;
				a[e[i][2] - 1][e[i][1] - 1] = 5;
				a[e[i][2] - enemy_speed][e[i][1]] = 0;
				a[e[i][2] - 1- enemy_speed][e[i][1] + 1] = 0;
				a[e[i][2] - 1- enemy_speed][e[i][1] - 1] = 0;
			}
			else if (e[i][2] == MY - 1) {
				e[i][0] = 0;
				a[e[i][2] - 1- enemy_speed][e[i][1] + 1] = 0;
				a[e[i][2] - 1- enemy_speed][e[i][1] - 1] = 0;
				a[e[i][2] - enemy_speed][e[i][1]] = 0;
			}
		}
	}
	for (i = 0; i < enemy_members; i++) {
		if (e[i][0]) { e[i][2] += enemy_speed; }
	}
}

void hit(int a[][MX], int e[][3], int f[][3]) {
	int i, j;
	for (i = 0; i < fire_members; i++) {
		for (j = 0; j < enemy_members; j++) {
			if (f[i][0] == 1 && e[j][0] == 1) {
				if ((f[i][1] == e[j][1]|| f[i][1] == e[j][1]+1|| f[i][1] == e[j][1]-1) && (e[j][2]==f[i][2]|| e[j][2] -1== f[i][2] || e[j][2] - 2 == f[i][2])) {
					f[i][0] = 0;
					a[f[i][2] + fire_speed][f[i][1]] = 0;
					e[j][0] = 0;
						a[e[j][2] - 1 - enemy_speed][e[j][1] + 1] = 0;
						a[e[j][2] - 1 - enemy_speed][e[j][1] - 1] = 0;
						a[e[j][2] - enemy_speed][e[j][1]] = 0;
					scores++;
					break;
				}
		
			}

		}

	}
}

void HideCursor()
{
	CONSOLE_CURSOR_INFO cursor;
	cursor.bVisible = FALSE;
	cursor.dwSize = sizeof(cursor);
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorInfo(handle, &cursor);
}

void gotoxy(int x, int y)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(handle, pos);
}