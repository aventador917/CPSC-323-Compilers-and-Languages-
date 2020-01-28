/*
Paul Tang

CPSC 323
December 15, 2019

Assignment#3
*/

#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <iomanip>

#include "Lexer.h"
#include "Assembly.h"

#define ERROR_FOUND << currentToken.lexeme << "' on line " << currentToken.linenum; exit(1);
#define ADVANCE if (tokenCounter < tokenList.size()) { currentToken = tokenList[tokenCounter]; tokenCounter++; }

class Parser {
	void OptFuncDef();
	void FuncDef();
	void Func();
	void OptParamList();
	void ParamList();
	void Parameter();
	void Qualifier();
	void Body();
	void OptDecList();
	void DecList();
	void Declaration();
	void IDs();
	void StatementList();
	void Statement();
	void Compound();
	void Assign();
	void If();
	void Return();
	void Print();
	void Scan();
	void While();
	void Condition();
	void Relop();
	void Expression();
	void ExpressionPrime();
	void Term();
	void TermPrime();
	void Factor();
	void Primary();
	void Empty();
public:
	void Rat18S();

};

int tokenCounter = 0;
vector<Token> tokenList;
Token currentToken;
bool printSwitch = true;

int addr = 0;
string symboltype; 


void Parser::Rat18S() {
	ADVANCE
		OptFuncDef();

	if (currentToken.lexeme == "%%") {
		ADVANCE
			OptDecList();
		StatementList();
	}
	else {
		cout << "\nSyntax Error, expecting this %% before '" ERROR_FOUND
	}
}

void Parser::OptFuncDef() {

	if (currentToken.lexeme == "%%") {
		Empty();
	}
	else {
		cout << "\nSyntax Error, expecting 'function' or '%%' before '" ERROR_FOUND
	}

}

void Parser::FuncDef() {

	while (currentToken.lexeme == "function") {
		Func();
	}
}

void Parser::Func() {

	ADVANCE

		if (currentToken.token == "Identifier") {
			ADVANCE
				if (currentToken.lexeme == "[") {
					ADVANCE
						OptParamList();
					if (currentToken.lexeme == "]") {
						ADVANCE
							OptDecList();
						Body();
					}
					else {
						cout << "\nSyntax Error, expecting ']' before '" ERROR_FOUND
					}
				}
				else {
					cout << "\nSyntax Error, expecting '[' before '" ERROR_FOUND
				}
		}
		else {
			cout << "\nSyntax Error, expecting <Identifier> before '" ERROR_FOUND
		}
}

void Parser::OptParamList() {

	if (currentToken.token == "Identifier") {
		ParamList();
	}
	else if (currentToken.lexeme == "]") {
		Empty();
	}
	else {
		cout << "\nSyntax Error, expecting <Identifier> before '" ERROR_FOUND
	}
}

void Parser::ParamList() {

	if (currentToken.token == "Identifier") {
		Parameter();
		if (currentToken.lexeme == ",") {
			ADVANCE
				ParamList();
		}
	}
}

void Parser::Parameter() {

	IDs();
	if (currentToken.lexeme == ":") {
		ADVANCE
			Qualifier();
	}
	else {
		cout << "\nSyntax Error, expecting ':' before '" ERROR_FOUND
	}
}

void Parser::Qualifier() {

	if (currentToken.lexeme == "int" || currentToken.lexeme == "true"
		|| currentToken.lexeme == "false" || currentToken.lexeme == "boolean") {
		symboltype = currentToken.lexeme;
		ADVANCE
	}
	else {
		cout << "\nSyntax Error, expecting 'int' or 'boolean' before '" ERROR_FOUND
	}
}

void Parser::Body() {

	if (currentToken.lexeme == "{") {
		ADVANCE
			StatementList();
		if (currentToken.lexeme == "}") {
			ADVANCE
		}
		else {
			cout << "\nSyntax Error, expecting '}' before '" ERROR_FOUND
		}
	}
	else {
		cout << "\nSyntax Error, expecting '{' before '" ERROR_FOUND
	}
}

void Parser::OptDecList() {

	if (currentToken.lexeme == "{") {
		Empty();
	}
	else if (currentToken.lexeme == "int" || currentToken.lexeme == "boolean") {
		DecList();
	}
	else {
		cout << "\nSyntax Error, expecting 'int' or 'boolean' before '" ERROR_FOUND
	}
}

void Parser::DecList() {

	Declaration();
	if (currentToken.lexeme == ";") {
		ADVANCE
			if (currentToken.lexeme == "int" || currentToken.lexeme == "boolean") {
				DecList();
			}
	}
	else {
		cout << "\nSyntax Error, expecting ';' on line " ERROR_FOUND
	}
}

void Parser::Declaration() {
	Qualifier();
	IDs();
}

void Parser::IDs() {

	if (currentToken.token == "Identifier") {
		add_symbol(currentToken.lexeme, memory_address, symboltype);
		ADVANCE
			if (currentToken.lexeme == ",") {
				ADVANCE
					IDs();
			}
			else if (currentToken.token == "Identifier") {
				cout << "\nSyntax Error, expecting ',' between multiple identifiers on line " << currentToken.linenum;
				exit(1);
			}
	}
	else {
		cout << "\nSyntax Error, expecting <Identifier> before '" ERROR_FOUND
	}
}

void Parser::StatementList() {

	while (currentToken.lexeme == "if" || currentToken.lexeme == "return" || currentToken.lexeme == "put"
		|| currentToken.lexeme == "get" || currentToken.lexeme == "while" || currentToken.token == "Identifier"
		|| currentToken.lexeme == "function") {
		Statement();
	}
}

void Parser::Statement() {

	if (currentToken.lexeme == "{")
		Compound();
	else if (currentToken.token == "Identifier")
		Assign();
	else if (currentToken.lexeme == "if")
		If();
	else if (currentToken.lexeme == "return")
		Return();
	else if (currentToken.lexeme == "put")
		Print();
	else if (currentToken.lexeme == "get")
		Scan();
	else if (currentToken.lexeme == "function")
		Func();
	else if (currentToken.lexeme == "while")
		While();
	else {
		cout << "\nSyntax Error, expecting proper '<Statement>' before '" ERROR_FOUND
	}
}

void Parser::Compound() {

	if (currentToken.lexeme == "{") {
		ADVANCE
			StatementList();
		if (currentToken.lexeme == "}") {
			ADVANCE
		}
	}
}

void Parser::Assign() {

	if (currentToken.token == "Identifier") {
		save = currentToken;
		ADVANCE
			if (currentToken.lexeme == "=") {
				ADVANCE
					Expression();
				add_instr("POPM", get_address(save));
				if (currentToken.lexeme == ";") {
					ADVANCE
				}
				else {
					cout << "\n<Assign> Syntax Error";
					exit(1);
				}
			}
			else {
				cout << "\nSyntax Error, expecting '=' before '" ERROR_FOUND
			}
	}
}

void Parser::If() {

	if (currentToken.lexeme == "if") {
		ADVANCE
			if (currentToken.lexeme == "(") {
				ADVANCE
					Condition();
				if (currentToken.lexeme == ")") {
					ADVANCE
						Statement();
					if (currentToken.lexeme == "endif") {
						ADVANCE
					}
					else if (currentToken.lexeme == "else") {
						ADVANCE
							Statement();
						if (currentToken.lexeme == "endif") {
							ADVANCE
						}
						else {
							cout << "\nSyntax Error, expecting 'endif' on line " << currentToken.linenum;
							exit(1);
						}
					}
					else {
						cout << "\nSyntax Error, expecting 'endif' or 'else' on line " << currentToken.linenum;
						exit(1);
					}
				}
				else {
					cout << "\nSyntax Error, expecting ) after <Condition> on line " << currentToken.linenum;
					exit(1);
				}
			}
			else {
				cout << "\nSyntax Error, expecting ( on line " << currentToken.linenum;
				exit(1);
			}
	}
}

void Parser::Return() {

	ADVANCE
		if (currentToken.lexeme == ";") {
			ADVANCE
		}
		else {
			Expression();
			if (currentToken.lexeme == ";") {
				ADVANCE
			}
			else {
				cout << "\nSyntax Error, expecting ';' before '" ERROR_FOUND
			}
		}
}

void Parser::Print() {

	ADVANCE
		if (currentToken.lexeme == "(") {
			ADVANCE
				Expression();
			add_instr("STDOUT", -1); // INSTR;
			if (currentToken.lexeme == ")") {
				ADVANCE
					if (currentToken.lexeme == ";") {
						ADVANCE
					}
					else {
						cout << "\nSyntax Error, expecting ';' before '" ERROR_FOUND
					}
			}
			else {
				cout << "\nSyntax Error, expecting ')' before '" ERROR_FOUND
			}
		}
		else {
			cout << "\nSyntax Error, expecting '(' before '" ERROR_FOUND
		}
}

void Parser::Scan() {

	ADVANCE
		if (currentToken.lexeme == "(") {
			add_instr("STDIN", -1); stdinflag = true; // INSTR
			ADVANCE
				IDs();
			if (currentToken.lexeme == ")") {
				ADVANCE
					if (currentToken.lexeme == ";") {
						ADVANCE
					}
					else {
						cout << "\nSyntax Error. Expecting ';' before '" ERROR_FOUND
					}
			}
			else {
				cout << "\nSyntax Error, expecting ')' before '" ERROR_FOUND
			}
		}
		else {
			cout << "\nSyntax Error, expecting '(' before '" ERROR_FOUND
		}
}

void Parser::While() {

	addr = InstructionTable.size() + 1;
	add_instr("LABEL", -1);

	ADVANCE
		if (currentToken.lexeme == "(") {
			ADVANCE
				Condition();
			if (currentToken.lexeme == ")") {
				ADVANCE
					Statement();
				add_instr("JUMP", addr); 
				back_patch(); 
			}
			else {
				cout << "\nSyntax Error, expecting ')' before '" ERROR_FOUND
			}
		}
		else {
			cout << "\nSyntax Error, expecting '(' before '" ERROR_FOUND
		}
}

void Parser::Condition() {

	Expression();
	Relop();
	Expression();

	// CASE op
	if (symboltype == "=") { add_instr("EQU", -1); jumpstack.push(InstructionTable.size()); add_instr("JUMPZ", -1); }
	else if (symboltype == "^=") { add_instr("NEQ", -1); jumpstack.push(InstructionTable.size()); add_instr("JUMPZ", -1); }
	else if (symboltype == "<") { add_instr("LES", -1); jumpstack.push(InstructionTable.size()); add_instr("JUMPZ", -1); }
	else if (symboltype == ">") { add_instr("GRT", -1); jumpstack.push(InstructionTable.size()); add_instr("JUMPZ", -1); }
	else if (symboltype == "=>") { add_instr("GEQ", -1); jumpstack.push(InstructionTable.size()); add_instr("JUMPZ", -1); }
	else if (symboltype == "<=") { add_instr("LEQ", -1); jumpstack.push(InstructionTable.size()); add_instr("JUMPZ", -1); }

}

void Parser::Relop() {

	if (currentToken.lexeme == "==" || currentToken.lexeme == "^=" || currentToken.lexeme == ">"
		|| currentToken.lexeme == "<" || currentToken.lexeme == "=>" || currentToken.lexeme == "=<") {
		symboltype = currentToken.lexeme;
		ADVANCE
	}
	else
	{
		cout << "\nSyntax error, expecting valid comparison operator before " ERROR_FOUND
	}
}

void Parser::Expression() {
	Term();
	ExpressionPrime();
}

void Parser::ExpressionPrime() {

	if (currentToken.lexeme == "+") {
		ADVANCE
			Term();
		add_instr("ADD", -1);
		ExpressionPrime();
	}
	else if (currentToken.lexeme == "-") {
		ADVANCE
			Term();
		add_instr("SUB", -1);
		ExpressionPrime();
	}
	else if (currentToken.token == "Unknown") {
		cout << "\nSyntax error, expecting '+', '-', or nothing before '" ERROR_FOUND
	}
	else {
		Empty();
	}
}

void Parser::Term() {
	Factor();
	TermPrime();
}

void Parser::TermPrime() {
	if (currentToken.lexeme == "*") {
		ADVANCE
			Factor();
		add_instr("MUL", -1);
		TermPrime();
	}
	else if (currentToken.lexeme == "/") {
		ADVANCE
			Factor();
		add_instr("DIV", -1);
		TermPrime();
	}
	else if (currentToken.token == "Unknown") {
		cout << "\nSyntax Error, expecting '*', '/', or 'Empty' before '" ERROR_FOUND
	}
	else {
		Empty();
	}
}

void Parser::Factor() {
	if (currentToken.lexeme == "-") {
		ADVANCE
			Primary();
	}
	else if (currentToken.token != "Unknown") {
		Primary();
	}
	else {
		cout << "\nSyntax Error, expecting something different before '" ERROR_FOUND
	}
}

void Parser::Primary() {

	if (currentToken.token == "Identifier") {
		add_instr("PUSHM", get_address(currentToken));
		ADVANCE
			if (currentToken.lexeme == "[") {
				ADVANCE
					IDs();
				if (currentToken.lexeme == "]") {
					ADVANCE
				}
				else {
					cout << "\nSyntax Error, expecting ']' before '" ERROR_FOUND
				}
			}
			else {

			}

	}
	else if (currentToken.token == "Integer") {
		ADVANCE
	}
	else if (currentToken.lexeme == "(") {
		ADVANCE
			Expression();
		if (currentToken.lexeme == ")") {
			ADVANCE
		}
		else {
			cout << "\nSyntax Error, expecting ')' before '" ERROR_FOUND
		}
	}
	else if (currentToken.lexeme == "true") {
		add_instr("PUSHI", 1);
		ADVANCE
	}
	else if (currentToken.lexeme == "false") {
		add_instr("PUSHI", 0);
		ADVANCE
	}
	else {
		cout << "\nSyntax Error, expecting '<Identifer>', '<Qualifier>' or '<Expression>' before '" ERROR_FOUND
	}
}

void Parser::Empty() {
}



#endif