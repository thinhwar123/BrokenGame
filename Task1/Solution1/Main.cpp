#include <iostream>
using namespace std;
#pragma region SwapFunction
void Swap1(int& a, int& b) {
	int temp = a;
	a = b;
	b = temp;
}
void Swap2(int *a, int *b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}
#pragma endregion

#pragma region IOFunction
void Input(int &a, int &b) {
	cin >> a >> b;
}
void Output(int a, int b) {
	cout << "a: " << a << endl;
	cout << "b: " << b << endl;
}
#pragma endregion


int main() {
	int a, b;

	Input(a, b);
	Swap1(a, b);
	Output(a, b);

	Input(a, b);
	Swap2(&a, &b);
	Output(a, b);

	system("PAUSE");
	return 0;
}