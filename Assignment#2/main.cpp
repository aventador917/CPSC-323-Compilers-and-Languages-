/*
Paul Tang

CPSC 323
November 18, 2019

Assignment#2
*/
#include<iostream>
#include<fstream>
#include"lexana.h"
#include"synalyzer.h"



int main(int argc, char **argv)
{
	char str[256];
	bool next_lexeme;
	ofstream outputFile("out.txt");
	ifstream inputFile;
	Syntaxer syntactic;
	Lexer lex;
	char inChar;

	cout << "sample1.txt" << endl;
	cout << "sample2.txt" << endl;
	cout << endl;
	cout << "Please input the file you want to test: ";
	cin.get(str, 256);
	cout << endl;
	
	inputFile.open(str);
	if(!inputFile.is_open()) 
	{
		cout << "Input file could not be opened!!" << endl;
	}
	do{
		inputFile.get(inChar);
		lex.char_input(inChar);
		if (lex.checkLexeme()) 
		{
		  syntactic.addTokenLex_toPrint("\nToken:\t" + lex.get_token() + "\t\t" + "Lexeme:\t  " + lex.get_lexeme() + "\n  ");
			next_lexeme = false;
			while(!next_lexeme) 
			{
				next_lexeme = syntactic.start(lex.get_token(), lex.get_lexeme());
			}
		}
	} while(!inputFile.eof());

	cout << syntactic.printout();
	outputFile << syntactic.printout();
	inputFile.close();
	outputFile.close();
	cout << endl;
	cout << "You can also see the result in out.txt" << endl;
	system("pause");
	return 0;
	
}
