//#include <iostream>
#include <windows.h>
#include <ctime>
#include <stack>
 
#define SCREEN_HEIGHT 50
#define SCREEN_WIDTH  211
#define START_POINT_X 1
#define START_POINT_Y 1

class Way {
public:
	int m_a;
	int m_b;
	Way(const int& a, const int& b) : m_a(a), m_b(b) {}
	/*friend std::ostream& operator<<(std::ostream& out, const Way& sh) {
		out << sh.m_a << " " << sh.m_b << std::endl;
		return out;//hei bei
	}*/
	const int& A() { return m_a; }
	const int& B() { return m_b; }
};
struct Point {
	int m_a;
	int m_b;
};
int main() {
	using namespace std;

	HANDLE hOutput = (HANDLE)GetStdHandle(STD_OUTPUT_HANDLE);

	COORD dwBufferSize = { SCREEN_WIDTH,SCREEN_HEIGHT };
	COORD dwBufferCoord = { 0, 0 };
	SMALL_RECT rcRegion = { 0, 0, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1 };

	CHAR_INFO maze[SCREEN_HEIGHT][SCREEN_WIDTH] = { 0 };

	ReadConsoleOutput(hOutput, (CHAR_INFO*)maze, dwBufferSize,
		dwBufferCoord, &rcRegion);

	srand(time(NULL));

	stack<Way> m_maze;
	m_maze.emplace(START_POINT_Y, START_POINT_X);
	maze[START_POINT_Y][START_POINT_X].Attributes = 255;
	bool check = false;
	int i = 0, count = 0;
	int ax = 1, bx = 1;
	Point point[4];
	system("pause");
	while (1) {
		if (ax == 1 && bx == 1) {
			if (check) {
				system("pause");
				exit(0);
			}
			check = true;
		}
		if (ax - 2 >= 1 && maze[ax - 2][bx].Attributes < 16) {
			point[i].m_a = ax - 2;
			point[i].m_b = bx;
			++i;
		}
		if (ax + 2 <= SCREEN_HEIGHT - 2 && maze[ax + 2][bx].Attributes < 16) {
			point[i].m_a = ax + 2;
			point[i].m_b = bx;
			++i;
		}
		if (bx - 2 >= 1 && maze[ax][bx - 2].Attributes < 16) {
			point[i].m_a = ax;
			point[i].m_b = bx - 2;
			++i;
		}
		if (bx + 2 <= SCREEN_WIDTH - 2 && maze[ax][bx + 2].Attributes < 16) {
			point[i].m_a = ax;
			point[i].m_b = bx + 2;
			++i;
		}
		if (!i) {
			m_maze.pop();
		}
		else {
			//Sleep(10);
			int turn = rand() % i;
			m_maze.emplace(point[turn].m_a, point[turn].m_b);
			maze[point[turn].m_a][point[turn].m_b].Attributes = 255;
			maze[ax + (point[turn].m_a - ax) / 2][bx + (point[turn].m_b - bx) / 2].Attributes = 255;
			count++; i = 0;
			WriteConsoleOutput(hOutput, (CHAR_INFO*)maze, dwBufferSize,
				dwBufferCoord, &rcRegion);
		}
		ax = m_maze.top().A();
		bx = m_maze.top().B();
	}
}