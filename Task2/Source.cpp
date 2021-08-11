# include <iostream>

using namespace std;

long long factorial(int n) {
	long long res = 1;
	if (n < 0)
	{
		return NULL;
	}
	if (n == 0 || n == 1)
	{
		return res;
	}
	for (int i = 2; i < n; i++)
	{
		res *= i;
	}
	return res;
}
void input(int& n) {
	do {
		cout << "Please enter a positive integer: ";
		cin >> n;
	} while (n <= 0);
}
int main() {
	int n;
	input(n);
	cout << factorial(n)<< endl;

	system("PAUSE");
	return 0;
}