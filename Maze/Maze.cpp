#include <iostream>
#include <windows.h>
#include <vector>
#include <ctime>
 
#define SCREEN_HEIGHT 50
#define SCREEN_WIDTH  100

class Way {
public:
	int m_a;
	int m_b;
	Way(const int& a, const int& b) : m_a(a), m_b(b) {}
	friend std::ostream& operator<<(std::ostream& out, const Way& sh) {
		out << sh.m_a << " " << sh.m_b << std::endl;
		return out;
	}
	const int& A() { return m_a; }
	const int& B() { return m_b; }
};
struct Point {
	int m_a;
	int m_b;
};
int main() {
	using namespace std;

	int posy = 3, posx = 1;

	HANDLE hOutput = (HANDLE)GetStdHandle(STD_OUTPUT_HANDLE);

	COORD dwBufferSize = { SCREEN_WIDTH,SCREEN_HEIGHT };
	COORD dwBufferCoord = { 0, 0 };
	SMALL_RECT rcRegion = { 0, 0, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1 };

	CHAR_INFO maze[SCREEN_HEIGHT][SCREEN_WIDTH];

	ReadConsoleOutput(hOutput, (CHAR_INFO*)maze, dwBufferSize,
		dwBufferCoord, &rcRegion);

	srand(time(NULL));

	vector<Way> m_maze;
	m_maze.emplace_back(1, 1);
	maze[1][1].Attributes = 255;
	bool check = false;
	int i = 0, count = 0;
	int ax = 1, bx = 1;
	Point point[4];
	while (1) {
		ax = m_maze.back().A();
		bx = m_maze.back().B();
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
			m_maze.pop_back();
		}
		else {
			Sleep(10);
			int fuq = rand() % i;
			m_maze.emplace_back(point[fuq].m_a, point[fuq].m_b);
			maze[point[fuq].m_a][point[fuq].m_b].Attributes = 255;
			maze[ax + (point[fuq].m_a - ax) / 2][bx + (point[fuq].m_b - bx) / 2].Attributes = 255;
			count++; i = 0;
		}
		WriteConsoleOutput(hOutput, (CHAR_INFO*)maze, dwBufferSize,
			dwBufferCoord, &rcRegion);
	}
}