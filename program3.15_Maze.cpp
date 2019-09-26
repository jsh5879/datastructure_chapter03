//3.5 a mazing problem
//program 3.15: finding a path through a maze
// 3.16~17
#include <iostream>
#include <fstream>
using namespace std;

const int DefaultSize = 10000;
enum Boolean { FALSE, TRUE };

struct items {
	int x, y, dir;
};


template <class T>
class Stack {

public:
	Stack(int MaxStackSize = DefaultSize);
	Boolean IsFull();
	void Add(const T& item);
	Boolean IsEmpty();
	T* Delete(T&);

	void StackEmpty() { cout << "empty" << endl; };
	void StackFull() { cout << "full" << endl; };
	void Output();

	template <class T>
	friend ostream& operator<<(ostream& os, const Stack<T>& s);

	template <class T>
	friend ostream& operator<<(ostream& os, items& item);

private:
	int top; //current element index, begin with 0
	T* stack;
	int MaxSize;//capacity of the stack
};

template <class T>
Stack<T>::Stack(int MaxStackSize) : MaxSize(MaxStackSize)
{
	stack = new T[MaxSize];
	top = -1;
}

template <class T>
inline Boolean  Stack<T>::IsFull()
{
	if (top == MaxSize - 1) return TRUE;
	else return FALSE;
}

template <class T>
inline Boolean  Stack<T>::IsEmpty()
{
	if (top == -1) return TRUE;
	else return FALSE;
}

template <class T>
void Stack<T>::Add(const T& x)
// add x to the stack
{
	if (IsFull()) StackFull();
	else stack[++top] = x;
}

template <class T>
T* Stack<T>::Delete(T& x)
// removes and return top element from stack
{
	if (IsEmpty()) { StackEmpty(); return 0; }
	x = stack[top--];
	return &x;
}

template <class T>
ostream& operator<<(ostream& os, const Stack<T>& s)
{
	os << "top = " << s.top << endl;
	os << "stack elements: from the bottom to the top: " << endl;
	for (int i = 0; i <= s.top; i++)
		os << i << ":" << s.stack[i] << endl;
	return os;
}

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
//circular queue를 사용한 버젼으로 수정

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
