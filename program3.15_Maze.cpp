//3.5 a mazing problem
//program 3.15: finding a path through a maze
// 3.16~17
#include <iostream>
#include <fstream>
#include "stackTemplate.h"
using namespace std;

const int DefaultSize = 10000;
enum Boolean { FALSE, TRUE };

struct items {
	int x, y, dir;
};

ostream& operator<<(ostream& os, items& item)
{
	return os << item.x << "," << item.y << "," << item.dir;
}

struct offsets {
	int a, b;
};

enum directions { N, NE, E, SE, S, SW, W, NW };
offsets moves[8];
int maze[100][100];
int mark[100][100];

void path(int m, int p)
// Output a path (if any) in the maze; rows is m, cols is p;
{
	//start at (1,1)
	mark[1][1] = 1;
	Stack<items> stack(m * p);
	items temp;
	temp.x = 1; temp.y = 1; temp.dir = E;
	stack.Add(temp);

	while (!stack.IsEmpty()) // stack not empty
	{
		temp = *stack.Delete(temp); // unstack
		int i = temp.x; int j = temp.y; int d = temp.dir;
		while (d < 8) // moves forward
		{
			//outFile << i << " " << j << " " << d << endl;
			int g = i + moves[d].a;
			int h = j + moves[d].b;
			if ((g == m) && (h == p)) { // reached exit
										// output path
				cout << stack;

				cout << "the term near the exit: " << i << " " << j << endl;
				cout << "exit: " << m << " " << p << endl;
				return;
			}
			if ((!maze[g][h]) && (!mark[g][h])) { // new position
				mark[g][h] = 1;
				//push the old temp to the stack, but the direction changes.
				//Because the neighbor in the direction of d has been checked.
				temp.x = i;  temp.y = j; temp.dir = d + 1;
				stack.Add(temp); // stack it
				i = g; j = h; d = N; // moves to (g,h)
			}
			else d++; // try next direction
		}
	}
	cout << "no path in maze " << endl;
}
/*
maze[][], mark[][]를 class의 private data member로 선언
main()에서는 class의 public function의 호출로 미로 찾기
*/
void main() {
	int input[12][15] = {
	{ 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1 },
	{ 1, 0, 0, 0, 1, 1, 0, 1, 1, 1, 0, 0, 1, 1, 1 },
	{ 0, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1 },
	{ 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 0 },
	{ 1, 1, 0, 1, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1 },
	{ 0, 0, 1, 1, 0, 1, 1, 1, 0, 1, 0, 0, 1, 0, 1 },
	{ 0, 0, 1, 1, 0, 1, 1, 1, 0, 1, 0, 0, 1, 0, 1 },
	{ 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 0, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1 },
	{ 1, 1, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0 },
	{ 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0 },
	{ 0, 1, 0, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0 },
	};

	moves[N].a = -1; moves[N].b = 0;
	moves[NE].a = -1; moves[NE].b = 1;
	moves[E].a = 0; moves[E].b = 1;
	moves[SE].a = 1; moves[SE].b = 1;
	moves[S].a = 1; moves[S].b = 0;
	moves[SW].a = 1; moves[SW].b = -1;
	moves[W].a = 0; moves[W].b = -1;
	moves[NW].a = -1; moves[NW].b = -1;


	for (int i = 0; i < 14; i++) {
		for (int j = 0; j < 17; j++)
		{
			if ((!i) || (!j) || (i == 13) || (j == 16))
				maze[i][j] = 1;
			else {
				maze[i][j] = input[i - 1][j - 1];
			};
			mark[i][j] = 0;

		}
	}
	for (int i = 0; i <= 13; i++)
	{
		for (int j = 0; j <= 16; j++)
			cout << maze[i][j] << " ";
		cout << endl;
	}
	path(12, 15);

	int end;
	cin >> end;
}
