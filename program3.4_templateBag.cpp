
//3.1.2 using templates to represent container class
// program 3.4:definition of the class bag

#include <iostream>
#include <memory>
using namespace std;

template <class T>
class Bag {
public:
	Bag(int bagCapacity = 10);
	~Bag();

	int Size() const;
	bool IsEmpty() const;
	T& Element() const;

	void Push(const T&);
	void Pop();

private:
	T* array;
	int capacity;
	int top;
};


template <class T>
Bag<T>::Bag(int bagCapacity) : capacity(bagCapacity)
{
	if (capacity < 1) throw "Capacity must be > 0";
	array = new T[capacity];
	top = -1;
}

template <class T>
Bag<T>::~Bag() { delete[] array; }

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

template <class T>
int Bag<T>::Size() const {
	return top + 1;
}

template <class T>
bool Bag<T>::IsEmpty() const {
	return top < 0;
}

template <class T>
T& Bag<T>::Element() const {
	if (top == -1)throw "index out of bound";
	return this->array[top];
}


template <class T>
void Bag<T>::Push(const T& x)
{
	if (top == capacity - 1)
		// 현재 버젼은 ordering 상태에서 push한다. non-ordering되게 push가 가능하게 수정
	{
		ChangeSizeID(array, capacity, 2 * capacity);
		capacity *= 2;
	}
	array[++top] = x;
}

template <class T>
void Bag<T>::Pop()
{
	if (IsEmpty()) throw "Bag is empty, cannot delete";
	int deletePos = top / 2;
	// 실습 사항: no ordering상태로 pop되게 수정
	//copy(array + deletePos + 1, array + top + 1, array + deletePos);
	memcpy(array + deletePos, array + deletePos, top + 1);
	top--;
}


int main() {
	Bag<int> b(4);
	//Bag<float> fo(10);에 대하여도 구현할 것
	//화면에서 임의 숫자를 입력받아 Push() 호출하도록 수정
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

	system("pause");
	return 0;
}


