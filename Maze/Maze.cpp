#include <iostream>
#include <vector>
#include <ctime>
class Way {
public:
	int m_a;
	int m_b;
	Way(const int& a, const int& b): m_a(a), m_b(b){}
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
int main(){
	using namespace std;
	srand(time(NULL));
	int n = 10, m = 20;
	cin >> n >> m;
	bool** maze = new bool* [n]; 
	for (int i = 0; i < n; ++i)
		maze[i] = new bool[m] {0};
	vector<Way> m_maze;
	m_maze.emplace_back(0, 0);
	maze[0][0] = 1;
	int i = 0, count = 0;
	int ax, bx;
	Point point[4];
	while (count < (n / 2) * (m / 2) - 1) {
		ax = m_maze.back().A();
		bx = m_maze.back().B();
		if (ax - 2 >= 0 && maze[ax - 2][bx] == 0) {
			point[i].m_a = ax - 2;
			point[i].m_b = bx;
			++i;
		}
		if (ax + 2 <= n - 1 && maze[ax + 2][bx] == 0) {
			point[i].m_a = ax + 2;
			point[i].m_b = bx;
			++i;
		}
		if (bx - 2 >= 0 && maze[ax][bx - 2] == 0) {
			point[i].m_a = ax;
			point[i].m_b = bx - 2;
			++i;
		}
		if (bx + 2 <= m - 1 && maze[ax][bx + 2] == 0) {
			point[i].m_a = ax;
			point[i].m_b = bx + 2;
			++i;
		}
		if (!i) {
			m_maze.pop_back();
		}
		else {
			int fuq = rand() % i;
			m_maze.emplace_back(point[fuq].m_a, point[fuq].m_b);
			maze[point[fuq].m_a][point[fuq].m_b] = true;
			maze[ax + (point[fuq].m_a - ax) / 2][bx + (point[fuq].m_b - bx) / 2] = true;
			count++; i = 0;
		}
	}
	cout << static_cast<char>(177) << static_cast<char>(177) << "  ";
	for (i = 0; i < m - 1; i++)
		cout << static_cast<char>(177) << static_cast<char>(177);
	cout << endl;
	for (i = 0; i < n; i++) {
		cout << static_cast<char>(177) << static_cast<char>(177);
		for (int j = 0; j < m - 1; j++) {
			if (!maze[i][j]) {
				cout << static_cast<char>(177);
				cout << static_cast<char>(177);
			}
			else
				cout << "  ";
		}
		(i == n - 2) ? cout << "  " : cout << static_cast<char>(177) << static_cast<char>(177);
		cout << endl;
	}
}