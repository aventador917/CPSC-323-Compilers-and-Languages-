/*
Paul Tang

CPSC 323
December 15, 2019

Assignment#3
*/

#include "Parser.h"
#include <string> // std::string, std::to_string

using namespace std;
int main() {
    
    Lexer lex;
    Parser parse;
    vector<Token> tokens;
    string current = "";
    string infilepath;
    string outfilepath;
    
    int lineNumber = 0;
		
	char str[256];
	
	cout << "TestCase1.txt" << endl;
	cout << "TestCase2.txt" << endl;
	cout << "TestCase3.txt" << endl << endl;

	cout << "Please input the file you want to test: ";
	cin.get(str, 256);
	cout << endl;
    
		fin.open(str);
		fout.open("output.txt");

        if (!fin) 
		{
            cout << "Error. Unable to read file." << endl;
            return -1;
        }
        
        while (getline(fin, current)) 
		{
            
            lineNumber++;
            tokens = lex.lexical(current, lineNumber);
            for (int i = 0; i < tokens.size(); i++) {
                tokens[i].linenum = lineNumber;
            }
            
            tokenList.insert(tokenList.end(), tokens.begin(), tokens.end());
            tokens.clear();
        }
        
        fin.close();
        parse.Rat18S();
        printST();
        fout << "\n\n";
        printIT();
        fout.close();
        SymbolTable.clear();
        InstructionTable.clear();
        memory_address = 5000; // Global starting address variable
        stdinflag = false;
        cout << "Completed "<<str<<"\n";
		cout << "You can now open output.txt" << endl;
    
    
	system("Pause");
    return 0;
}
