#ifndef SYMBOL_HPP
#define SYMBOL_HPP

#include <string>
#include <vector>

union SymbolValue
{
    int intValue;
    double doubleValue;
};

enum VarType
{
    INT_TYPE,
    REAL_TYPE,
    NONE_TYPE
};

enum SymbolType
{
    FUNCTION_SYMBOL,
    PROCEDURE_SYMBOL,
    LABEL_SYMBOL,
    VAR_SYMBOL,
    CONSTANT_SYMBOL,
    NONE_SYMBOL
};

class Symbol
{
public:
    Symbol();
    Symbol(int value);
    Symbol(double value);
    Symbol(std::string symbolName) : symbolName(symbolName)
    {
        this->address = 0;
        this->type = NONE_TYPE;
        this->symbolType = NONE_SYMBOL;
    };
    Symbol(std::string symbolName, VarType varType) :symbolName(symbolName), type(varType)
    {
        this->address = 0;
        this->type = NONE_TYPE;
        this->symbolType = NONE_SYMBOL;
    };

    ~Symbol();
    std::string getSymbolName();
    VarType getVarType();
    void setVarType(VarType varType)
    {
        this->type = varType;
    }
    SymbolValue getSymbolValue()
    {
        return this->value;
    }
    SymbolType getSymbolType()
    {
        return this->symbolType;
    }
    void setSymbolType(SymbolType symbolType);
    void setAddress(int address)
    {
        this->address = address;
    }

    int getAddress()
    {
        return this->address;
    }

private:
    std::string symbolName;
    SymbolValue value;
    VarType type;
    SymbolType symbolType;
    bool isReference;
    int address;
};

#endif