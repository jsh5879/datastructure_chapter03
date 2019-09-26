//3.4 subtyping and inheritance in c++
//program 3.13~14
#include <iostream>
#include <memory>
using namespace std;

class Bag {
public:
	Bag(int bagCapacity = 10);
	~Bag();

	int Size() const;
	bool IsEmpty() const;
	int& Element() const;

	void Push(const int&);
	void Pop();

	//private:
	int* array = nullptr;
	int capacity;
	int top;
};


Bag::Bag(int bagCapacity) : capacity(bagCapacity)
{
	if (capacity < 1) throw "Capacity must be > 0";
	array = new int[capacity];
	top = -1;
}


Bag::~Bag() { delete[] array; }


void ChangeSizeID(int*& a, const int oldSize, const int newSize)
{
	if (newSize < 0) throw "New length must be >= 0";

	int* temp = new int[newSize];
	int number = oldSize;
	if (oldSize > newSize) number = newSize;
	//copy(a, a + number, temp);
	memcpy(temp, a, number);
	delete[] a;
	a = temp;
}

int Bag::Size() const {
	return top + 1;
}


bool Bag::IsEmpty() const {
	return top < 0;
}


int& Bag::Element() const {
	if (top == -1)throw "index out of bound";
	return this->array[top];
}



void Bag::Push(const int& x)
{
	if (top == capacity - 1)
	{
		ChangeSizeID(array, capacity, 2 * capacity);
		capacity *= 2;
	}
	array[++top] = x;
}


void Bag::Pop()
{
	if (IsEmpty()) throw "Bag is empty, cannot delete";
	int deletePos = top / 2;
	//copy(array + deletePos + 1, array + top + 1, array + deletePos);
	memcpy(array + deletePos, array + deletePos, top + 1);
	top--;
}

class Stack : public Bag
{
public:
	Stack(int stackCapacity = 10);
	~Stack();
	int Top() const;
	void Pop();
	//stack에 Push()는 no duplicate를 구현, 단 Bag::Push()를 재사용한 코딩 구현
};

Stack::Stack(int stackCapacity) : Bag(stackCapacity) {}

Stack::~Stack() {}

int Stack::Top() const
{
	if (IsEmpty()) throw "Stacak is empty";
	return array[top];
}

void Stack::Pop()
{
	if (IsEmpty()) throw "Stack is empty. Cannot delete";
	top--;
}


int main() {

	Stack b(4);
	b.Push(3);
	b.Push(5);
	b.Push(1);
	b.Push(6);

	if (b.IsEmpty()) {
		cout << "empty" << endl;
	}
	else {
		cout << "not empty" << endl;
	}

	while (!b.IsEmpty()) {
		cout << b.Element() << endl;
		b.Pop();
	}
	//b.Pop();//실행시 오류 발생 - 소스코드 수정 필요
	system("pause");
	return 0;

}
