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
	while (true) {
		cout << "Please enter a positive integer: ";
		cin >> n;
		if (cin.good())
		{
			break;
		}
		else
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Invalid input; please re-enter." << endl;
		}
	}
}
int main() {
	int n;
	input(n);
	cout << factorial(n)<< endl;

	system("PAUSE");
	return 0;
}