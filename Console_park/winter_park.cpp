#include <iostream>
#include <cstdlib>
#include <ctime>
#include  <windows.h>
#include <conio.h>

using namespace std;

class park {

private:
	int map[10][10][10] = { 0 };  // 맵
	int map2[10][10][10] = { 0 }; // 맵 초기화 위해 원래맵 복사한 배열
	int x1[7], y1[7], x2[7], y2[7], x3[7], y3[7], y_1[3]; // 눈위치 함수
public:
	void tree_map(); // 나무가 생성되고 화면 돌리는 함수
	void turn(int turn_number);    //화면 돌리는 함수
	void print_up();               //윗면 출력하는 함수
	void print_side(int number);   //앞, 옆, 뒤 출력하는 함수
	void print_mini(int t_num1, int t_num2, int t_num3); // 모양 출력하는 함수
	void mini_reset();  //--------------맵을 트리만 남기고 초기화
	void reset(int count); // 보이게 될 면에 트리나 눈 보이게 하는 함수
	void make_tree(int m1, int m2, int m3, int m4, int m5); // 트리가 만들어질때 한층씩 숫자넣는 함수
	void snow_map(int s_time); //눈 내리고, 그 후 화면 돌리기 함수
	void snow_up(); // 윗면 눈 위치 지정하는 함수
	void snow_rand(int s1_arr[7], int s2_arr[7], int num);//내리고 사라진 눈 랜덤 생성
};

void park::tree_map() {

	int key, a;
	int x = 3, y = 3, again = 0; // 나무 만들 위치 지정 변수 ,x y

	srand((unsigned int)time(NULL));
	a = rand() % 3 + 2;  //나무 높이 2~4층까지 랜덤지정
	map[9][y][x] = 80;   //나무 위치 지정하기 위한 표시

	print_up();  //윗면 출력
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
		cout << "좌표지정이 완료되었으면 [Space Bar]를 눌러주세요" << endl;
	}
	map[9][y][x] = 0;
	a = a - 1; // 나무 층

	make_tree(y - a, y + a + 1, x - a, x + a + 1, 0); //나무 제일 밑 층 생성
	make_tree(y - a + 1, y + a, x - a + 1, x + a, 1); //나무 두번째 층 생성
	if (a >= 2) { // 만약 나무가 3층 이상이라면
		make_tree(y - a + 2, y + a - 1, x - a + 2, x + a - 1, 2); //나무 세번째 층 생성
		if (a == 3) //만약 나무가 4층이라면
			make_tree(y - a + 3, y + a - 2, x - a + 3, x + a - 2, 3); //나무 제일 위 층 생성
	}

	reset(5);
	print_up();
	print_side(1);
	turn(1);
}

void park::turn(int turn_number) {  //화면 돌리기 함수
	int key, i;
	int bb = 0, again = 0;

	while (again == 0) {

		key = _getch();
		if (key == 77)bb++; // 오른쪽으로 돌림
		if (key == 75)bb--; // 왼쪽으로 돌림
		if (key == 32)again = 1; //스페이스바면 그만
		if (bb == -4 || bb == 4)bb = 0;  //한바퀴 돌면 다시 정면

		mini_reset();  //전에 보였던 면과 안겹치기 위해 초기화
		reset(5);
		if (turn_number > 10)snow_up(); //11일때, 윗면 눈 위치 지정
		print_up();
		if (turn_number > 10)mini_reset();//11 이상일때(눈 내리고 난 후)전에 보인 면의 내린 눈 지우기(초기화)

		if (turn_number > 10) {   //11 일때 눈위치에 1넣어줌
			for (i = 0; i < 7; i++) {  //눈이 들어갈 위치에 나무가 있으면 생기지 않음
				if (map[y_1[0]][y1[i]][x1[i]] < 90)map[y_1[0]][y1[i]][x1[i]] = 1;
				if (map[y_1[1]][y2[i]][x2[i]] < 90) map[y_1[1]][y2[i]][x2[i]] = 1;
				if (map[y_1[2]][y3[i]][x3[i]] < 90) map[y_1[2]][y3[i]][x3[i]] = 1;
			}
		}

		if (bb == 0)print_side(turn_number); //정면
		if (bb == 1 || bb == -3)print_side(turn_number + 1);//오른면
		if (bb == 2 || bb == -2)print_side(turn_number + 2);//뒷면
		if (bb == -1 || bb == 3)print_side(turn_number + 3);//왼면
		cout << endl << "그만 돌리고 싶다면 [Space Bar]를 눌러주세요" << endl;
	}
}

void park::make_tree(int m1, int m2, int m3, int m4, int m5) {
	int j, k;
	for (j = m1; j < m2; j++) {   //나무 생성시 90부터 93까지 랜덤으로 수 넣음
		for (k = m3; k < m4; k++) { //여러가지 모양을 위함
			map[m5][j][k] = rand() % 4 + 90;
			map2[m5][j][k] = map[m5][j][k];
		}
	}
}

void park::print_up() { //윗면 출력

	int i, j;
	system("cls");
	cout << " [윗면] 입니다" << endl;
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

	if (number == 1)cout << endl << "[ 정면 ] 입니다" << endl;
	if (number == 2)cout << endl << "[ 오른면 ] 입니다" << endl;
	if (number == 3)cout << endl << "[ 뒷면 ] 입니다" << endl;
	if (number == 4)cout << endl << "[ 왼쪽면 ] 입니다" << endl;

	for (i = 9; i >= 0; i--) {
		if (number == 1 || number == 4) {
			for (j = 0; j < 10; j++) {
				if (number == 1)print_mini(i, 9, j);//정면
				if (number == 4)print_mini(i, j, 0);//왼쪽면
			}
		}
		else {
			for (j = 9; j >= 0; j--) {
				if (number == 2)print_mini(i, j, 9);//오른면
				if (number == 3)print_mini(i, 0, j);//뒷면
			}
		}
		cout << endl;
	}
}

void park::mini_reset() { //초기화 함수
	int i, j, k;
	for (i = 0; i < 10; i++) {
		for (j = 0; j < 10; j++) {
			for (k = 0; k < 10; k++)
				map[i][j][k] = map2[i][j][k];
		}
	}
}

void park::reset(int count) {// 각각 면에서 보이는 나무, 눈 등이 보이게 값 넣어주는 함수
	int i, j, k;            //reset(숫자) => 숫자는 1~5까지 1:정면, 2:오른면, 3:뒷면, 4:왼쪽면, 5:윗면

	if (count == 5) {
		for (i = 9; i >= 0; i--) {
			for (j = 0; j < 10; j++) {
				for (k = 0; k < 10; k++)
				{
					if (map[i][j][k] > 0 && map[9][j][k] == 0) { //들어갈 곳이 비었을때만 들어감
						if (map[i][j][k] == 1)map[9][j][k] = 1;  // 1은 눈
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
						else map[i][j][0] = map[i][j][k] - 10;  // 1이 아닐경우 -10해서 들어감
					}                                           // 이유는 나중에 눈 내릴때
				}                                               // 나무가 아닌 부분에 보이게 하기위함
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

	if (map[t_num1][t_num2][t_num3] == 0)cout << "□"; //벽
	if (map[t_num1][t_num2][t_num3] == 1)cout << "ω"; //눈
	if (map[t_num1][t_num2][t_num3] == 80 || map[t_num1][t_num2][t_num3] == 90)cout << "★"; //나무
	if (map[t_num1][t_num2][t_num3] == 81 || map[t_num1][t_num2][t_num3] == 91)cout << "●"; //나무
	if (map[t_num1][t_num2][t_num3] == 82 || map[t_num1][t_num2][t_num3] == 92)cout << "▲"; //나무
	if (map[t_num1][t_num2][t_num3] == 83 || map[t_num1][t_num2][t_num3] == 93)cout << "♥"; //나무
}

void park::snow_map(int s_time) { //눈 내리는 함수

	int i, s_count = 0;
	for (i = 0; i < 7; i++) { //눈좌표 랜덤으로 찍어줌
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

		mini_reset(); // 내렸던 눈 지우는 초기화
		reset(5);
		snow_up(); //윗면 눈 위치 표시 함수
		print_up();
		mini_reset(); //윗면과 겹칠 수 있으므로 초기화

		for (i = 0; i < 7; i++)
		{
			if (map[y_1[0]][y1[i]][x1[i]] < 90)map[y_1[0]][y1[i]][x1[i]] = 1;  //눈 내릴 곳이 나무가 아니여야만 내림
			if (s_count >= 4 && map[y_1[1]][y2[i]][x2[i]] < 90) map[y_1[1]][y2[i]][x2[i]] = 1;
			if (s_count >= 7 && map[y_1[2]][y3[i]][x3[i]] < 90) map[y_1[2]][y3[i]][x3[i]] = 1;
		}
		print_side(11); //정면출력
		s_time--;
		Sleep(500);
	}
	turn(11);
}

void park::snow_rand(int s1_arr[7], int s2_arr[7], int num) {
	int i;     //다 내린 눈 다시 랜덤으로 위치지정
	if (y_1[num] == -1) {
		for (i = 0; i < 7; i++) {
			s1_arr[i] = rand() % 10;
			s2_arr[i] = rand() % 10;
			y_1[num] = 9;
			if (s1_arr[i] % 2 == num)i--;
		}
	}
}

void park::snow_up() { //윗면 눈위치 지정
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
	cout << "눈이 내릴 시간을 입력해 주세요  :";
	cin >> snow_time;
	snow_time *= 2;

	game.tree_map();
	game.snow_map(snow_time);

	return 0;
}