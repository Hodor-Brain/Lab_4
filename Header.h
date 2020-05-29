#pragma once

#include <iostream>
#include <cstdlib>
#include <math.h>

using namespace std;

struct Stack
{
	char funct[4] = {};

	Stack* next = nullptr;
	Stack* head = nullptr;

	int size = 0;

	void push(char* fu);
	char* pop(char* fun);
};

struct Tree
{
	char function[4] = {};

	double data = 0;
	char* func = nullptr;
	char oper = '\0';
	char varia = '\0';

	Tree* left = nullptr;
	Tree* right = nullptr;

	Tree()
	{};
	Tree(double a, char* b, char c, char d)
	{
		data = a;
		func = b;
		oper = c;
		varia = d;
	};
};

struct StackOfTrees
{
	Tree* data = nullptr;

	StackOfTrees* next = nullptr;
	StackOfTrees* head = nullptr;

	void push(Tree* my);
	Tree* pop();
};

struct Variables
{
	char name = '\0';
	int value = 0;
};

void show(Tree* our);

//void ConvertToPolska(char* string, char* b);

Tree** MakeExpr(char* str, Tree** b);

Tree* MakeTree(Tree** our, Tree* root);

double eval(Tree* root, Variables* a);