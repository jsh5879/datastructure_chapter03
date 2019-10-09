//3.6.2 postfix notation
//3.18~19
//stack¿« ∫Ø»≠ cout operator overiding
#include <iostream>
#include <memory>
#include "stackTemplate.h"
#include <stdio.h>

typedef char* Expression;
typedef char Token;
using namespace std;

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
		return 21;
	else if (a == ')')
		return 19;
	else if (a == '+' || a == '-')
		return 12;
	else if (a == '*' || a == '%' || a == '/')
		return 13;
	else
		return 22;
}

int icp(char a)
{
	if (a == '(')
		return 1;
	else if (a == ')')
		return 19;
	else if (a == '+' || a == '-')
		return 12;
	else if (a == '*' || a == '%' || a == '/')
		return 13;
	else
		return 0;
}

void Postfix(Expression e)
{
	Stack<char> stack;
	stack.Push('#');
	for (char x = NextToken(e); x != '#'; x = NextToken(e))
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
		{/*
			for (; isp(stack.Top()) >= icp(x); stack.Pop())
				cout << stack.Top();
			stack.Push(x);*/
			while (isp(stack.Top()) <= icp(x)) {
				cout << stack.Top();
				stack.Pop();
			}
			stack.Push(x);
		}
	}
	index = 0;
	while (stack.Top() != '#') {
		cout << stack.Top();
		stack.Pop();
	}
	stack.Pop();
	cout << endl;
}

double check(char x);

//e = postfix
void Eval(Expression e){
	Stack<Token> stack;
	stack.Push('#');
	for (Token x = NextToken(e); x != NULL; x = NextToken(e)) {
		if (isOperand(x)) stack.Push(x);
		else {
			//remove the correct number of operands for operator x from stack;
			//perform the operation x and store the result onto the stack;
			char operand1, operand2, result;
			operand1 = check(stack.Top());
			stack.Pop();
			operand2 = check(stack.Top());
			stack.Pop();
			if (x == '+') result = operand1 + operand2;
			else if (x == '-') result = operand1 - operand2;
			else if (x == '*') result = operand1 * operand2;
			else if (x == '/') result = operand1 / operand2;
			else result = 0;
			stack.Push(result);
			printf("%d/n", stack.Top());
		}
	}
}

double check(char x) {
	if (x == 'A') return 2;
	else if (x == 'B') return 3;
	else if (x == 'C') return 4;
	else if (x == 'D') return 5;
	else return 1;
}

int main()
{
	try{
	//infix > postfix > eval
	index = 0;
	Expression infix, postfix;
	infix = new char[10];
	postfix = new char[10];
	scanf("%s", infix); //   ex)  "A*(B+C)*D#"
	cout << "infix: " << infix << endl;
	cout << "Postfix: ";
	Postfix(infix);
	scanf("%s", postfix);
	Eval(postfix);
	}
	catch (string m) {
		cout << m << endl;
	}
	return 0;
}
