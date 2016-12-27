#ifndef SYMBOL_TABLE_HPP
#define SYMBOL_TABLE_HPP

#include <vector>
#include "symbol.hpp"

class SymbolTable
{
private:
    int address;
    SymbolTable *parent;
    std::vector<Symbol> symbols;
    int temporaryVariableCount;

public:
    SymbolTable();
    int lookupSymbol(const char *symbol);
    int lookupSymbol(int intValue);
    int lookupSymbol(double doubleValue);
    int createTemporaryVariable(VarType varType);
    Symbol &getSymbolByIndex(int tokenIndex);
    int insertSymbol(const char *symbol);
    int insertSymbol(const char *symbol, VarType varType);
    int insertConstant(int intValue);
    int insertConstant(double doubleValue);
    std::string tableStr();
    void increaseAddress(int increaseBy);
    int getAddress();
};

#endif