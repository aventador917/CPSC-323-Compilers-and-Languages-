/*
Paul Tang

CPSC 323
December 15, 2019

Assignment#3
*/

int memory_address = 5000; // Global starting address variable
Token save; // For instruction generation
bool stdinflag = false; // flag for if ID should be pushed or popped from stack

class Symbol { // One instance of symbol, collected in vector;
    public:
    string identifier;
    int memLocation;
    string type;
    
    Symbol(string identifier, int memLocation, string type) {
        this->identifier = identifier;
        this->memLocation = memLocation;
        this->type = type;
    }
    Symbol() {
        identifier = "";
        memLocation = 0;
        type = "";
    }
};

class Instruction{ // One instance of an instruction, collected in vector
    public:
    string Op;
    int operand;
    Instruction(string Op, int operand) {
        this->Op = Op;
        this->operand = operand;
    }
    Instruction() {
        Op = "";
        operand = 0;
    }
};

vector<Symbol> SymbolTable; // Global Symbol Table
vector<Instruction> InstructionTable; // Global Instruction Table
stack<int> jumpstack; // Stack for back patching jump instructions

int get_address(Token token) { // Checks symbol table for given id and returns address
    string x = token.lexeme;
    if (SymbolTable.size() == 0) {
        fout << "Error: Symbol Table is empty" << endl;
        system("pause");
        exit(1);
    }
    for (int i = 0; i < SymbolTable.size(); i++) {
        if (SymbolTable[i].identifier == x) {
            return SymbolTable[i].memLocation;
        }
    }
    // If it reaches below code, id was not found in table
    fout << "Error: an identifier was not declared." << endl << "Functions in source can cause this problem  because they are not supported!\n" << endl;
    system("pause");
    exit(1);
}

void printST() { // Prints all stored symbols in symbol table
    if (SymbolTable.size() == 0) return;
    fout << "----------- Symbol Table -----------" << endl;
    fout << left << setw(15) << "Identifier" << left << setw(20) << "Memory Location" << left << setw(10) << "Type" << endl;
    for (int i = 0; i < SymbolTable.size(); i++) {
        fout << left << setw(20) << SymbolTable[i].identifier << left << setw(15) << SymbolTable[i].memLocation << left << setw(15) << SymbolTable[i].type << endl;
    }
}

void printIT() { // Prints all stored instructions in instr table
    if (InstructionTable.size() == 0) return;
    fout << "--------- Instruction Table ---------" << endl;
    for (int i = 0; i < InstructionTable.size(); i++) {
        string index = to_string(i + 1) + ".";
        fout << left << setw(5) << index << left << setw(10) << InstructionTable[i].Op << left << setw(15);
        if (InstructionTable[i].operand == -1)
        fout << "nil" << endl;
        else
        fout << InstructionTable[i].operand << endl;
    }
}

void add_symbol(string ins, int mem, string type) { // Adds identifier to vector
    Symbol input(ins, mem, type);
    SymbolTable.push_back(input);
    memory_address++;
}

void add_instr(string ins, int oprnd) { // Places an instruction into the vector
    Instruction input(ins, oprnd);
    InstructionTable.push_back(input);
}

void back_patch() { // Patches jump instructions after statement completes
    int patch = jumpstack.top();
    jumpstack.pop();
    InstructionTable[patch].operand = InstructionTable.size() + 1;
}
