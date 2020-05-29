#include "Header.h"

int main()
{
	cout << "Enter the expression" << endl;

	char string[100] = {};

	cin.getline(string, 100);
	
	cout << endl;

	Tree** mas = new Tree * [100];
	for (int l = 0; l < 100; l++)
	{
		mas[l] = nullptr;
	}

	mas = MakeExpr(string, mas);

	Tree* my = nullptr;

	my = MakeTree(mas, my);

	show(my);

	Variables varmas[100];

	double result = eval(my, varmas);

	cout << endl << endl;
	cout << "Result = " << result;

}