#include <iostream>
#include <cstdlib>
#include <ctime>
#include  <windows.h>
#include <conio.h>

using namespace std;

class park {

private:
	int map[10][10][10] = { 0 };  // ��
	int map2[10][10][10] = { 0 }; // �� �ʱ�ȭ ���� ������ ������ �迭
	int x1[7], y1[7], x2[7], y2[7], x3[7], y3[7], y_1[3]; // ����ġ �Լ�
public:
	void tree_map(); // ������ �����ǰ� ȭ�� ������ �Լ�
	void turn(int turn_number);    //ȭ�� ������ �Լ�
	void print_up();               //���� ����ϴ� �Լ�
	void print_side(int number);   //��, ��, �� ����ϴ� �Լ�
	void print_mini(int t_num1, int t_num2, int t_num3); // ��� ����ϴ� �Լ�
	void mini_reset();  //--------------���� Ʈ���� ����� �ʱ�ȭ
	void reset(int count); // ���̰� �� �鿡 Ʈ���� �� ���̰� �ϴ� �Լ�
	void make_tree(int m1, int m2, int m3, int m4, int m5); // Ʈ���� ��������� ������ ���ڳִ� �Լ�
	void snow_map(int s_time); //�� ������, �� �� ȭ�� ������ �Լ�
	void snow_up(); // ���� �� ��ġ �����ϴ� �Լ�
	void snow_rand(int s1_arr[7], int s2_arr[7], int num);//������ ����� �� ���� ����
};

void park::tree_map() {

	int key, a;
	int x = 3, y = 3, again = 0; // ���� ���� ��ġ ���� ���� ,x y

	srand((unsigned int)time(NULL));
	a = rand() % 3 + 2;  //���� ���� 2~4������ ��������
	map[9][y][x] = 80;   //���� ��ġ �����ϱ� ���� ǥ��

	print_up();  //���� ���
	while (again == 0) {

		map[9][y][x] = 0;
		key = _getch();

		if (key == 75 && x > 3)x--;
		if (key == 77 && x < 6)x++;
		if (key == 72 && y > 3)y--;
		if (key == 80 && y < 6)y++;
		if (key == 32)again = 1;

		map[9][y][x] = 80;
		print_up();
		cout << "��ǥ������ �Ϸ�Ǿ����� [Space Bar]�� �����ּ���" << endl;
	}
	map[9][y][x] = 0;
	a = a - 1; // ���� ��

	make_tree(y - a, y + a + 1, x - a, x + a + 1, 0); //���� ���� �� �� ����
	make_tree(y - a + 1, y + a, x - a + 1, x + a, 1); //���� �ι�° �� ����
	if (a >= 2) { // ���� ������ 3�� �̻��̶��
		make_tree(y - a + 2, y + a - 1, x - a + 2, x + a - 1, 2); //���� ����° �� ����
		if (a == 3) //���� ������ 4���̶��
			make_tree(y - a + 3, y + a - 2, x - a + 3, x + a - 2, 3); //���� ���� �� �� ����
	}

	reset(5);
	print_up();
	print_side(1);
	turn(1);
}

void park::turn(int turn_number) {  //ȭ�� ������ �Լ�
	int key, i;
	int bb = 0, again = 0;

	while (again == 0) {

		key = _getch();
		if (key == 77)bb++; // ���������� ����
		if (key == 75)bb--; // �������� ����
		if (key == 32)again = 1; //�����̽��ٸ� �׸�
		if (bb == -4 || bb == 4)bb = 0;  //�ѹ��� ���� �ٽ� ����

		mini_reset();  //���� ������ ��� �Ȱ�ġ�� ���� �ʱ�ȭ
		reset(5);
		if (turn_number > 10)snow_up(); //11�϶�, ���� �� ��ġ ����
		print_up();
		if (turn_number > 10)mini_reset();//11 �̻��϶�(�� ������ �� ��)���� ���� ���� ���� �� �����(�ʱ�ȭ)

		if (turn_number > 10) {   //11 �϶� ����ġ�� 1�־���
			for (i = 0; i < 7; i++) {  //���� �� ��ġ�� ������ ������ ������ ����
				if (map[y_1[0]][y1[i]][x1[i]] < 90)map[y_1[0]][y1[i]][x1[i]] = 1;
				if (map[y_1[1]][y2[i]][x2[i]] < 90) map[y_1[1]][y2[i]][x2[i]] = 1;
				if (map[y_1[2]][y3[i]][x3[i]] < 90) map[y_1[2]][y3[i]][x3[i]] = 1;
			}
		}

		if (bb == 0)print_side(turn_number); //����
		if (bb == 1 || bb == -3)print_side(turn_number + 1);//������
		if (bb == 2 || bb == -2)print_side(turn_number + 2);//�޸�
		if (bb == -1 || bb == 3)print_side(turn_number + 3);//�޸�
		cout << endl << "�׸� ������ �ʹٸ� [Space Bar]�� �����ּ���" << endl;
	}
}

void park::make_tree(int m1, int m2, int m3, int m4, int m5) {
	int j, k;
	for (j = m1; j < m2; j++) {   //���� ������ 90���� 93���� �������� �� ����
		for (k = m3; k < m4; k++) { //�������� ����� ����
			map[m5][j][k] = rand() % 4 + 90;
			map2[m5][j][k] = map[m5][j][k];
		}
	}
}

void park::print_up() { //���� ���

	int i, j;
	system("cls");
	cout << " [����] �Դϴ�" << endl;
	for (i = 0; i < 10; i++) {
		for (j = 0; j < 10; j++) {
			print_mini(9, i, j);
		}
		cout << endl;
	}
	cout << endl;
}

void park::print_side(int number) {
	int i, j;

	if (number < 10)mini_reset();
	if (number > 10)number -= 10;
	reset(number);

	if (number == 1)cout << endl << "[ ���� ] �Դϴ�" << endl;
	if (number == 2)cout << endl << "[ ������ ] �Դϴ�" << endl;
	if (number == 3)cout << endl << "[ �޸� ] �Դϴ�" << endl;
	if (number == 4)cout << endl << "[ ���ʸ� ] �Դϴ�" << endl;

	for (i = 9; i >= 0; i--) {
		if (number == 1 || number == 4) {
			for (j = 0; j < 10; j++) {
				if (number == 1)print_mini(i, 9, j);//����
				if (number == 4)print_mini(i, j, 0);//���ʸ�
			}
		}
		else {
			for (j = 9; j >= 0; j--) {
				if (number == 2)print_mini(i, j, 9);//������
				if (number == 3)print_mini(i, 0, j);//�޸�
			}
		}
		cout << endl;
	}
}

void park::mini_reset() { //�ʱ�ȭ �Լ�
	int i, j, k;
	for (i = 0; i < 10; i++) {
		for (j = 0; j < 10; j++) {
			for (k = 0; k < 10; k++)
				map[i][j][k] = map2[i][j][k];
		}
	}
}

void park::reset(int count) {// ���� �鿡�� ���̴� ����, �� ���� ���̰� �� �־��ִ� �Լ�
	int i, j, k;            //reset(����) => ���ڴ� 1~5���� 1:����, 2:������, 3:�޸�, 4:���ʸ�, 5:����

	if (count == 5) {
		for (i = 9; i >= 0; i--) {
			for (j = 0; j < 10; j++) {
				for (k = 0; k < 10; k++)
				{
					if (map[i][j][k] > 0 && map[9][j][k] == 0) { //�� ���� ��������� ��
						if (map[i][j][k] == 1)map[9][j][k] = 1;  // 1�� ��
						else map[9][j][k] = map[i][j][k] - 10;
					}
				}
			}
		}
	}
	for (i = 0; i < 10; i++)
	{
		if (count == 4) {
			for (k = 0; k < 10; k++) {
				for (j = 0; j < 10; j++) {
					if (map[i][j][k] > 0 && map[i][j][0] == 0)
					{
						if (map[i][j][k] == 1)map[i][j][0] = map[i][j][k];
						else map[i][j][0] = map[i][j][k] - 10;  // 1�� �ƴҰ�� -10�ؼ� ��
					}                                           // ������ ���߿� �� ������
				}                                               // ������ �ƴ� �κп� ���̰� �ϱ�����
			}
		}
		if (count == 2) {
			for (k = 9; k >= 0; k--) {
				for (j = 0; j < 10; j++) {
					if (map[i][j][k] > 0 && map[i][j][9] == 0)
					{
						if (map[i][j][k] == 1)map[i][j][9] = 1;
						else map[i][j][9] = map[i][j][k] - 10;
					}
				}
			}
		}
		if (count == 3) {
			for (j = 0; j < 10; j++) {
				for (k = 0; k < 10; k++) {
					if (map[i][j][k] > 0 && map[i][0][k] == 0)
					{
						if (map[i][j][k] == 1)map[i][0][k] = 1;
						else map[i][0][k] = map[i][j][k] - 10;
					}
				}
			}
		}
		if (count == 1) {
			for (j = 9; j >= 0; j--) {
				for (k = 0; k < 10; k++) {
					if (map[i][j][k] > 0 && map[i][9][k] == 0)
					{
						if (map[i][j][k] == 1)map[i][9][k] = 1;
						else map[i][9][k] = map[i][j][k] - 10;
					}
				}
			}
		}
	}
}

void park::print_mini(int t_num1, int t_num2, int t_num3) {

	if (map[t_num1][t_num2][t_num3] == 0)cout << "��"; //��
	if (map[t_num1][t_num2][t_num3] == 1)cout << "��"; //��
	if (map[t_num1][t_num2][t_num3] == 80 || map[t_num1][t_num2][t_num3] == 90)cout << "��"; //����
	if (map[t_num1][t_num2][t_num3] == 81 || map[t_num1][t_num2][t_num3] == 91)cout << "��"; //����
	if (map[t_num1][t_num2][t_num3] == 82 || map[t_num1][t_num2][t_num3] == 92)cout << "��"; //����
	if (map[t_num1][t_num2][t_num3] == 83 || map[t_num1][t_num2][t_num3] == 93)cout << "��"; //����
}

void park::snow_map(int s_time) { //�� ������ �Լ�

	int i, s_count = 0;
	for (i = 0; i < 7; i++) { //����ǥ �������� �����
		x1[i] = rand() % 10;
		y1[i] = rand() % 5 + 0;
		x2[i] = rand() % 10;
		y2[i] = rand() % 5 + 5;
		x3[i] = rand() % 10;
		y3[i] = rand() % 10;
		if (i < 3)y_1[i] = 10;
		if (x1[i] % 2 == 0 || x2[i] % 2 == 1)i--;
	}

	while (s_time > 0) {

		if (s_count < 9)s_count++;
		y_1[0]--;
		if (s_count >= 4)y_1[1]--;
		if (s_count >= 7)y_1[2]--;

		if (y_1[0] == -1)snow_rand(x1, y1, 0);
		if (y_1[1] == -1)snow_rand(x2, y2, 1);
		if (y_1[2] == -1)snow_rand(x3, y3, 2);

		mini_reset(); // ���ȴ� �� ����� �ʱ�ȭ
		reset(5);
		snow_up(); //���� �� ��ġ ǥ�� �Լ�
		print_up();
		mini_reset(); //����� ��ĥ �� �����Ƿ� �ʱ�ȭ

		for (i = 0; i < 7; i++)
		{
			if (map[y_1[0]][y1[i]][x1[i]] < 90)map[y_1[0]][y1[i]][x1[i]] = 1;  //�� ���� ���� ������ �ƴϿ��߸� ����
			if (s_count >= 4 && map[y_1[1]][y2[i]][x2[i]] < 90) map[y_1[1]][y2[i]][x2[i]] = 1;
			if (s_count >= 7 && map[y_1[2]][y3[i]][x3[i]] < 90) map[y_1[2]][y3[i]][x3[i]] = 1;
		}
		print_side(11); //�������
		s_time--;
		Sleep(500);
	}
	turn(11);
}

void park::snow_rand(int s1_arr[7], int s2_arr[7], int num) {
	int i;     //�� ���� �� �ٽ� �������� ��ġ����
	if (y_1[num] == -1) {
		for (i = 0; i < 7; i++) {
			s1_arr[i] = rand() % 10;
			s2_arr[i] = rand() % 10;
			y_1[num] = 9;
			if (s1_arr[i] % 2 == num)i--;
		}
	}
}

void park::snow_up() { //���� ����ġ ����
	int i;
	for (i = 0; i < 7; i++) {
		map[9][y1[i]][x1[i]] = 1;
		map[9][y2[i]][x2[i]] = 1;
		map[9][y3[i]][x3[i]] = 1;
	}
}

int main() {

	int snow_time;
	park game;
	cout << "���� ���� �ð��� �Է��� �ּ���  :";
	cin >> snow_time;
	snow_time *= 2;

	game.tree_map();
	game.snow_map(snow_time);

	return 0;
}