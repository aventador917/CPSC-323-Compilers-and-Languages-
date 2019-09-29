/*
Paul Tang

CPSC 323
September 28, 2019

Assignment#1
*/

#include<string>
#include<stdlib.h>
#include<stdio.h>
#include<iostream>
#include <fstream>

using namespace std;

bool isLetter(char ch) 
{//identifier
	if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z') || ch =='$' )
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool isDigit(char ch) 
{//isDigit 
	if (ch >= '0' && ch <= '9')
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool isOperators(char ch) 
{// isOperators 
	if (ch == '+' || ch == '*' || ch == '-' || ch == '/' || ch == '=' || ch == ':' || ch == '<' || ch == '>' || ch =='!')
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool isDelimiter(char ch) 
{// is separator
	if (ch == ',' || ch == ';' || ch == '.' || ch == '(' || ch == ')' || ch == '[' || ch == ']' || ch == '{' || ch == '}' || ch == '#' || ch == '\\'||ch == '"' || ch == '\'' )
	{
	
		return true;
	}
	else
	{
		return false;
	}
}
bool isBlank(char ch) 
{
	if (ch == ' ' || ch == '\t' || ch == '\n')
	{
		return true;
	}
	else
	{
		return false;
	}
}
char  key[34][10] = { "main",
"auto", "short", "int", "long", "float", "double", "char", "struct"
, "union", "enum", "typedef", "const", "unsigned", "signed", "extern", "register"
, "static", "volatile", "void", "if", "else", "switch", "case", "for"
, "do", "while", "goto", "continue", "break", "default", "sizeof", "return","then" };

void fsm(char sourceCode[256])
{
	ofstream out("out.txt");
	int number = 0;
	int h = 0;
	char hh[100][10] = { '\0' };
	out << "token            lexeme" << endl;
	out << "-----------------------" << endl;
	for (int i = 0; i < 256; i) {
		//char delimiter[2] = "";
		int j = 0;  //letter  
		int l = 0;   //digit 
		int k = 0;   //operators  

		int b = 0;  // The typerNumber; the identifier is 1,real number is 2, keyword is 3, operator is 4 and separator is 5.
		char num[100] = "";
		char word[100] = "";
		if (isBlank(sourceCode[i]) == 1) 
		{
			i += 1;
		}//remove whitespace
		else {
			if (isLetter(sourceCode[i]) == 1)         //identifier
			{                                             //yes
				do
				{
					if (j < 10) 
					{
						word[j] = sourceCode[i];
						j++;
					}
				} while (isDigit(sourceCode[++i]) == 1 || isLetter(sourceCode[i]) == 1);

				int a = 0;
				while (a < 34) 
				{
					if (strcmp(key[a], word) == 0) 
					{
						b = 3;
						a++;
						break;
					}
					else 
					{
						b = 1;
						a++;
						
					}
				}
				if (b == 3)
				{
					out << "keyword          " << word << endl;
				}
				if (b == 1) 
				{
					int q = 0, qq = 0;
					for (int qq = 0; strcmp(hh[qq], "") != 0; qq++) 
					{
						if (strcmp(word, hh[qq]) == 0) 
						{
							q = 1; break;
						}
					}
					if (q == 1) 
					{
					out << "identifier          " <<word<< endl;
						q = 0;
					}
					else 
					{
						for (qq = 0; qq < j; qq++) 
						{
							hh[h][qq] = word[qq];
						}
					out << "identifier          " << word<< endl;
						h++;
					}
				}
				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			}
			else if (isDigit(sourceCode[i]) == 1)//realnumber
			{
				int c = 0;
				while (isDigit(sourceCode[i]) || sourceCode[i] == '.' ) 
				{

					num[c] = sourceCode[i];
					i += 1;
					c++;
				}
				out << "real               " << num << endl;
			}
			else if (isDelimiter(sourceCode[i]) == 1) //separator
			{

				out << "separator          " << sourceCode[i] << endl;
				i++;
			}
			else if (isOperators(sourceCode[i]) == 1) //operator
			{

				if (sourceCode[i] == ':' || sourceCode[i] == '>' || sourceCode[i] == '<'&&sourceCode[i + 1] == '=') 
				{
					out << "operator          " << sourceCode[i]<<sourceCode[i+1] << endl;
					i += 2;
				}
				else 
				{
					out << "operator          " << sourceCode[i] << endl;
					i += 1;
				}
			}
			else 
			{
				if (sourceCode[i] != '\0')
				{
					out << "error         " << sourceCode[i] << endl;
					
				}
				if (sourceCode[i + 1] != '\0') 
				{

					i += 1;
				}
				else
				{
					i = 256;
				}
			}
		}
	}
}


int main()
{
	char str[256];
	char originCode[256] = "";
	char *buffer = originCode;

	cout << "TestCase1.txt" << endl;
	cout << "TestCase2.txt" << endl;
	cout << "TestCase3.txt" << endl << endl;

	cout << "Please input the file you want to test: ";
	cin.get(str, 256);
	cout << endl;
	
	ifstream is(str);
	int i = 0;
	while (is.get(originCode[i]))
	{
		cout << originCode[i];
		++i;
	}

	cout << endl << endl;
	
	fsm(originCode);
	
	cout << "See the lexical result in output.txt" << endl;
	system("pause");
	return 0;
}