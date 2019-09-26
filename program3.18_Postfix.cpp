//3.6.2 postfix notation
//3.18~19
#include <iostream>
#include <memory>
typedef char* Expression;
using namespace std;


template <class T>
class Stack
{
public:
	Stack(int stackCapacity = 10);
	bool IsEmpty() const;
	T& Top() const;
	void Push(const T& item);
	void Pop();

private:
	T* stack;
	int top;
	int capacity;



};

template <class T>
Stack<T>::Stack(int stackCapacity) :capacity(stackCapacity)
{
	if (capacity < 1) throw "Stack capacity must be > 0";
	stack = new T[capacity];
	top = -1;
}

template <class T>
inline bool Stack<T>::IsEmpty() const { return top == -1; }

template <class T>
inline T& Stack<T>::Top() const
{
	if (IsEmpty()) throw "Stack is empty";
	if (top >= 0)
		return stack[top];
	else
		throw "Stack is empty";
}

template <class T>
void Stack<T>::Push(const T& x)
{
	if (top == capacity - 1)
	{
		ChangeSizeID(stack, capacity, 2 * capacity);
		capacity *= 2;
	}
	stack[++top] = x;
	//cout<<"top = "<<top<<"    x = "<<x<<endl;
}

template <class T>
void Stack<T>::Pop()
{
	if (IsEmpty()) throw "Stack is empty. Cannot delete.";
	stack[top--].~T();
}

template <class T>
void ChangeSizeID(T*& a, const int oldSize, const int newSize)
{
	if (newSize < 0) throw "New length must be >= 0";

	T* temp = new T[newSize];
	int number = oldSize;
	if (oldSize > newSize) number = newSize;
	//copy(a, a + number, temp);
	memcpy(temp, a, number);
	delete[] a;
	a = temp;
}


int index = 0;

char NextToken(char* e)
{
	char token = e[index];
	index++;
	return token;
}

bool isOperand(char x)
{
	if (x == '+' || x == '-' || x == '*' || x == '/' ||
		x == '(' || x == ')' || x == '%' || x == '#')
		return false;
	else
		return true;
}

int isp(char a)
{
	if (a == '(')
		return 0;
	else if (a == ')')
		return 19;
	else if (a == '+' || a == '-')
		return 12;
	else if (a == '*' || a == '%' || a == '/')
		return 13;
	else
		return 0;
}

int icp(char a)
{
	if (a == '(')
		return 20;
	else if (a == ')')
		return 19;
	else if (a == '+' || a == '-')
		return 12;
	else if (a == '*' || a == '%' || a == '/')
		return 13;
	else
		return 0;
}

void Postfix(char* e)
{
	Stack<char> stack;
	stack.Push('#');
	for (char x = NextToken(e); x != NULL; x = NextToken(e))
	{
		//cout << "x = " << x << endl;
		if (isOperand(x))
			cout << x;
		else if (x == ')')
		{
			while (stack.Top() != '(')
			{
				cout << stack.Top();
				stack.Pop();
			}
			stack.Pop();
		}
		else
		{
			for (; isp(stack.Top()) >= icp(x); stack.Pop())
				cout << stack.Top();
			stack.Push(x);
		}
	}

	char x;
	while ((x = stack.Top()) != '#')
	{
		cout << x;
		stack.Pop();
	}
	cout << endl;
}
/*
void Eval(Expression e)
Stack<Token> stack;
stack.Push('#');
for (Token x = NextToken(e); x != '#"; x = NextToken(e))
	if (x is operand) stack.Push(x);
	else {
		//remove the correct number of operands for operator x from stack;
		//perform the operation x and store the result onto the stack;
	}
}
*/
void main()
{
	index = 0;
	Postfix("2+3*4+9");
	//165페이지, Exercises 1의 (a) ~ (f)에 대하여 동작하게 debugging
	index = 0;
	Postfix("A/B-C+D*E-A*C");//bug 발생-debugging
	//Eval("2*4 + 5*7");
	int end;
	cin >> end;
}

//코딩 과제: 
//페이지 166, 문제 3번과 4번: prefix and postfix을 만드는 문제
// 괄호() 사용시에도 처리하는 코딩으로 수정하는 것
