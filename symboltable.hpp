#ifndef SYMBOL_TABLE_HPP
#define SYMBOL_TABLE_HPP

#include <string>
#include <vector>
#include "symbol.hpp"

using namespace std;

class SymbolTable
{
private:
    string name;
    int address;
    SymbolTable *parent;
    vector<Symbol> symbols;
    vector<SymbolTable*> children;
    int temporaryVariableCount;
    string printTable(SymbolTable *table);

public:
    SymbolTable();
    int lookupSymbol(const char *symbol);
    int lookupSymbol(int intValue);
    int lookupSymbol(double doubleValue);
    int createTemporaryVariable(VarType varType);
    Symbol& getSymbolByIndex(int tokenIndex);
    int insertSymbol(const char *symbol);
    int insertSymbol(const char *symbol, VarType varType);
    int insertConstant(int intValue);
    int insertConstant(double doubleValue);
    string tableStr();
    void increaseAddress(int increaseBy);
    int getAddress();
    SymbolTable *addNewSymbolTable(string name);
};

#endif