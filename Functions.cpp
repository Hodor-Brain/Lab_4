#include "Header.h"

void Stack::push(char* fu)
{
	Stack* temp = new Stack;

	temp->funct[0] = fu[0];
	temp->funct[1] = fu[1];
	temp->funct[2] = fu[2];
	temp->funct[3] = '\0';

	temp->next = head;
	head = temp;

	size++;
}

char* Stack::pop(char* fun)
{
	char* temp = head->funct;
	fun = head->funct;

	Stack* t = head;
	head = head->next;

	size--;

	return temp;
}

void StackOfTrees::push(Tree* my)
{
	StackOfTrees* temp = new StackOfTrees;

	temp->data = my;

	temp->next = head;
	head = temp;
}

Tree* StackOfTrees::pop()
{
	Tree* temp = head->data;

	StackOfTrees* t = head;
	head = head->next;

	return temp;
}

void show(Tree* my)
{
	if (my == nullptr)
	{
		return;
	}
	else
	{
		show(my->left);
		if (my->func != nullptr)
		{
			cout << my->func[0];
			cout << my->func[1];
			cout << my->func[2];

			cout << ' ';
		}
		else if (my->oper != '\0')
		{
			cout << my->oper;
			cout << ' ';
		}
		else if (my->varia != '\0')
		{
			cout << my->varia;
			cout << ' ';
		}
		else
		{
			cout << my->data;
			cout << ' ';
		}
	}
	show(my->right);
}

/*void ConvertToPolska(char* string, char* b)
{
	Stack* stack = new Stack;

	int i = 0;
	int j = 0;

	char str[100] = {};
	char* a = str;

	while (string[i] != '\0')
	{
		char temp = string[i];

		if (isalnum(temp) != 0)
		{
			a[j] = temp;
			j++;
		}
		else if (temp == '(')
		{
			stack->push(temp);
		}
		else if (temp == ')')
		{
			while (stack->head->data != '(')
			{
				a[j] = stack->pop();
				j++;
			}
			stack->pop();
		}
		else if (temp == '+' || temp == '-' || temp == '*' || temp == '/' || temp == '^')
		{
			if (temp == '+' || temp == '-')
			{
				while (stack->size != 0 && stack->head->data != '(')
				{
					a[j] = stack->pop();
					j++;
				}
				stack->push(temp);
			}
			else if (temp != '^')
			{
				while (stack->size != 0 && stack->head->data != '(' && stack->head->data != '+' && stack->head->data != '-')
				{
					a[j] = stack->pop();
					j++;
				}
				stack->push(temp);
			}
			else
			{
				while (stack->size != 0 && stack->head->data == '^')
				{
					a[j] = stack->pop();
					j++;
				}
				stack->push(temp);
			}

		}

		i++;
	}

	while (stack->size != 0)
	{
		a[j] = stack->pop();
		j++;
	}

	strcpy_s(b, sizeof(char) * 100, str);

	delete stack;

	return ;
}*/



Tree** MakeExpr(char* str, Tree** b)
{
	Stack* stack = new Stack;

	int i = 0, j = 0;

	char* temp = str;
	char** ttemp = new char*;

	char funn[3] = {'\0','\0','\0'};
	char* fun = funn;
	fun[0] = '\0';

	if (str[0] == '-')
	{
		fun[0] = '~';
		fun[1] = '\0';
		fun[2] = '\0';
		stack->push(fun);

		i++;
	}

	while (temp[i] != '\0')
	{
		if (isdigit(temp[i]) != 0)
		{
			char* k = new char[strlen(temp) - i + 1];

			for (int l = 0; l < (strlen(temp) - i); l++)
			{
				k[l] = temp[i + l];
			}
			k[strlen(temp) - i] = '\0';

			b[j] = new Tree;
			b[j]->data = strtod(k, ttemp);
			temp = *ttemp;
			j++;
			i = -1;
		}
		else if (isalpha(temp[i]) != 0)
		{
			if (temp[i] == 'e' && temp[i + 1] == 'x' && temp[i + 2] == 'p')
			{
				fun[0] = 'e';
				fun[1] = 'x';
				fun[2] = 'p';

				stack->push(fun);
				i = i + 2;
			}
			else if (temp[i] == 'l' && temp[i + 1] == 'o' && temp[i + 2] == 'g')
			{
				fun[0] = 'l';
				fun[1] = 'o';
				fun[2] = 'g';

				stack->push(fun);
				i = i + 2;
			}
			else
			{
				b[j] = new Tree;
				b[j]->varia = temp[i];
				j++;
			}
		}
		else if (temp[i] == '(')
		{
			fun[0] = '(';
			fun[1] = '\0';
			fun[2] = '\0';
			stack->push(fun);
		}
		else if (temp[i] == ')')
		{
			while (stack->head->funct[0] != '(')
			{
				fun = stack->pop(fun);

				if (fun[1] == '\0')
				{
					b[j] = new Tree;
					b[j]->oper = fun[0];
				}
				else
				{
					b[j] = new Tree;

					b[j]->function[0] = fun[0];
					b[j]->function[1] = fun[1];
					b[j]->function[2] = fun[2];
					b[j]->func = b[j]->function;
				}
				j++;
			}
			stack->pop(fun);
		}
		else if (temp[i] == '+' || temp[i] == '-' || temp[i] == '*' || temp[i] == '/' || temp[i] == '^')
		{
			if (temp[i] == '+' || temp[i] == '-')
			{
				if (temp[i] == '-' && i != 0 && (temp[i - 1] == '(' || temp[i-1] == ','))
				{
					fun[0] = '~';
					fun[1] = '\0';
					fun[2] = '\0';
					stack->push(fun);
				}
				else
				{
					while (stack->size != 0 && stack->head->funct[0] != '(')
					{
						fun = stack->pop(fun);

						if (fun[1] == '\0')
						{
							b[j] = new Tree;
							b[j]->oper = fun[0];
						}
						else
						{
							b[j] = new Tree;

							b[j]->function[0] = fun[0];
							b[j]->function[1] = fun[1];
							b[j]->function[2] = fun[2];
							b[j]->func = b[j]->function;
						}
						j++;
					}

					fun[0] = temp[i];
					fun[1] = '\0';
					fun[2] = '\0';
					stack->push(fun);
				}
			}
			else if (temp[i] == '*' || temp[i] == '/')
			{
				while (stack->size != 0 && stack->head->funct[0] != '(' && stack->head->funct[0] != '+' && stack->head->funct[0] != '-')
				{
					fun = stack->pop(fun);

					if (fun[1] == '\0')
					{
						b[j] = new Tree;
						b[j]->oper = fun[0];
					}
					else
					{
						b[j] = new Tree;

						b[j]->function[0] = fun[0];
						b[j]->function[1] = fun[1];
						b[j]->function[2] = fun[2];
						b[j]->func = b[j]->function;
					}
					j++;
				}

				fun[0] = temp[i];
				fun[1] = '\0';
				fun[2] = '\0';
				stack->push(fun);
			}
			else if (temp[i] == '^')
			{
				while (stack->size != 0 && (stack->head->funct[0] == '^' || stack->head->funct[0] == 'l' || stack->head->funct[0] == 'e'))
				{
					fun = stack->pop(fun);

					if (fun[1] == '\0')
					{
						b[j] = new Tree;
						b[j]->oper = fun[0];
					}
					else
					{
						b[j] = new Tree;

						b[j]->function[0] = fun[0];
						b[j]->function[1] = fun[1];
						b[j]->function[2] = fun[2];
						b[j]->func = b[j]->function;
					}
					j++;
				}

				fun[0] = temp[i];
				fun[1] = '\0';
				fun[2] = '\0';
				stack->push(fun);
			}
		}
		else if (temp[i] == ',')
		{
			while (stack->head->funct[0] != '(')
			{
				fun = stack->pop(fun);
	
				if (fun[1] == '\0')
				{
					b[j] = new Tree;
					b[j]->oper = fun[0];
				}
				else
				{
					b[j] = new Tree;

					b[j]->function[0] = fun[0];
					b[j]->function[1] = fun[1];
					b[j]->function[2] = fun[2];
					b[j]->func = b[j]->function;
				}

				j++;
			}
		}

		i++;
	}

	while (stack->size != 0)
	{
		fun = stack->pop(fun);

		if (fun[1] == '\0')
		{
			b[j] = new Tree;
			b[j]->oper = fun[0];
		}
		else
		{
			b[j] = new Tree;

			b[j]->function[0] = fun[0];
			b[j]->function[1] = fun[1];
			b[j]->function[2] = fun[2];
			b[j]->func = b[j]->function;
		}
		j++;
	}

	return b;
}

Tree* MakeTree(Tree** our, Tree* root)
{
	StackOfTrees* stack = new StackOfTrees;

	int i = 0;

	while (our[i] != nullptr)
	{
		if (our[i]->func != nullptr)
		{
			Tree* temp = stack->pop();

			if (our[i]->func[0] == 'e')
			{
				our[i]->left = temp;
			}
			else
			{
				Tree* tempp = stack->pop();

				our[i]->left = tempp;
				our[i]->right = temp;
			}

			stack->push(our[i]);
		}
		else if (our[i]->oper != '\0')
		{
			Tree* temp = stack->pop();
			
			if (our[i]->oper == '~')
			{
				our[i]->left = temp;
			}
			else
			{
				our[i]->right = temp;

				Tree* tempp = stack->pop();

				our[i]->left = tempp;
			}
			stack->push(our[i]);
		}
		else if (our[i]->varia != '\0')
		{
			stack->push(our[i]);
		}
		else
		{
			stack->push(our[i]);
		}

		i++;
	}

	root = stack->pop();
	return root;
}

double eval(Tree* root, Variables* a)
{
	if (!root)
		return 0;

	if (!root->left && !root->right)
	{
		if (root->varia != '\0')
		{
			int i = 0;
			for (int j = 0; a[j].name != '\0'; j++)
			{
				if (root->varia == a[j].name)
				{
					return a[j].value;
				}
				i++;
			}

			a[i].name = root->varia;

			cout << endl << "Initialize the variable : " << root->varia << " = ";
			cin >> a[i].value;

			return a[i].value;
		}
		else
		{
			return (root->data);
		}
	}

	double leftval = eval(root->left, a);

	double rightval = eval(root->right, a);

	if (root->oper == '~')
		return -leftval;

	if (root->oper == '+')
		return leftval + rightval;

	if (root->oper == '-')
		return leftval - rightval;

	if (root->oper == '*')
		return leftval * rightval;

	if (root->oper == '/')
		return leftval / rightval;

	if (root->oper == '^')
		return pow(leftval , rightval);

	if (root->func[0] == 'l')
		return log(rightval) / log(leftval);

	if (root->func[0] == 'e')
		return exp(leftval);
}