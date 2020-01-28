/*
Paul Tang

CPSC 323
November 18, 2019

Assignment#2
*/
#pragma once
#include<string>
#include<vector>
#include<stack>

using namespace std;

class Syntaxer
{
  private:
    string stack, output;
    string checkTable(string n_buff, string t_buff);
    int nonterminal(string inbuff);
    int terminal(string inbuff);
  public:
    bool start(string token, string lexeme);
    void addTokenLex_toPrint(string inbuff);
    string printout();
};

bool Syntaxer::start(string token, string lexeme)
{
  string top_stack;

  if(stack.empty()) 
  {
	  stack.push_back('S');
    return false;
  }
  else{
    top_stack = stack.back();

    if(top_stack == " ") 
	{
      stack.pop_back();
      return true;
    }
    else if(token == "IDENTIFIER") 
	{
      if(top_stack != "i") 
	  {
        stack.pop_back();
        stack.append(checkTable(top_stack, "i"));
        top_stack = stack.back();
        if(top_stack == "e") 
		{
          stack.pop_back();
        }
        return false;
      }
      else if(top_stack == "i") 
	  {
        stack.pop_back();
      }
    }
    else if(token == "OPERATOR" && terminal(lexeme) >= 0) {
      if(top_stack != lexeme) 
	  {
        stack.pop_back();
        stack.append(checkTable(top_stack, lexeme));
        top_stack = stack.back();
        if(top_stack == "e") 
		{
          stack.pop_back();
        }
        return false;
      }
      else if(top_stack == lexeme) 
	  {
        stack.pop_back();
      }
    }
    else if(token == "SEPARATOR" && terminal(lexeme) >= 0) 
	{
      if(top_stack != lexeme) 
	  {
        stack.pop_back();
        stack.append(checkTable(top_stack, lexeme));
        top_stack = stack.back();
        if(top_stack == "e") 
		{
          stack.pop_back();
         }
        return false;
      }
      else if(top_stack == lexeme) 
	  {
        stack.pop_back();
      }
    }
  }
  return true;
}

int Syntaxer::nonterminal(string inbuff)
{
  int result = -1;

  //if(inbuff == "<Assign>")
  if(inbuff == "S")
    result = 0;
  //else if(inbuff == "<Expression>")
  else if(inbuff == "E")
    result = 1;
  //else if(inbuff == "<Expression Prime>")
  else if(inbuff == "Q")
    result = 2;
 //else if(inbuff == "<Term>")
  else if(inbuff == "T")
    result = 3;
  //else if(inbuff =="<Term Prime>")
  else if(inbuff == "R")
    result = 4;
  //else if(inbuff == "<Factor>")
  else if(inbuff == "F")
    result = 5;

  return result;
}

int Syntaxer::terminal(string inbuff) 
{
  int result = -1;

  if(inbuff == "i")
    result = 0;
  else if(inbuff == "+")
    result = 1;
  else if(inbuff == "-")
    result = 2;
  else if(inbuff == "*")
    result = 3;
  else if(inbuff == "/")
    result = 4;
  else if(inbuff == "(")
    result = 5;
  else if(inbuff == ")")
    result = 6;
  else if(inbuff == "=")
    result = 7;
  else if(inbuff == ";")
    result = 8;
  else if(inbuff == "$")
    result = 9;

  return result;
}

string Syntaxer::checkTable(string n_buff, string t_buff)
{
  vector<vector<string>> table 
  {

	  //{"<Identifier>=<Expression>","", "", "", "", "", "", "", "", ""},
	  //{"<Term><Expression Prime>", "", "", "", "", "<Term><Experssion Prime>", "", "", "", ""},
	 //{"", "+<Term><Expression Prime>", "-<Term><Expression Prime>", "", "", "", "<Empty>", "", "<Empty>", ""},
	  //{"<Factor><Term Prime>", "", "", "", "", "<Factor><Term Prime>", "", "", "", ""},
	// {"", "<Empty>", "<Empty>", "*<Factor> <Term Prime>", "/<Factor><Term Prime>", "", "<Empty>", "", "<Empty>", ""},
	 //{"<Identifier>", "", "", "", "", "(<Experssion>)", "", "", "", ""}

    //            i  +   -   *   /   (   )   =   ;   $
    /* S */  {"i=E;", "", "", "", "", "", "", "", "", ""},
    /* E */  {"TQ", "", "", "", "", "TQ", "", "", "", ""},
    /* Q */  {"", "+TQ", "-TQ", "", "", "", "e", "", "e", ""},
    /* T */  {"FR", "", "", "", "", "FR", "", "", "", ""},
    /* R */  {"", "e", "e", "*FR", "/FR", "", "e", "", "e", ""},
    /* F */  {"i", "", "", "", "", "(E)", "", "", "", ""}
  };
  string production, reverse_production;

  if(nonterminal(n_buff) >= 0) 
  {
    production = table[nonterminal(n_buff)][terminal(t_buff)];
    if(!production.empty()) 
	{
      output.append("<"+ n_buff + "> -> " + production + "\n  ");
    }
    while(!production.empty()) 
	{
        reverse_production.push_back(production.back());
        production.pop_back();
    }
  }
  else
  {
    return " ";
  }
  return reverse_production;
  return reverse_production;
}

void Syntaxer::addTokenLex_toPrint(string inbuff)
{
  output.append(inbuff);
}

string Syntaxer::printout()
{
  return output;
}
