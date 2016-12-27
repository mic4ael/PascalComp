#include "symbol.hpp"

Symbol::Symbol()
{
    this->address = 0;
    this->type = NONE_TYPE;
    this->symbolType = NONE;
}

Symbol::Symbol(int value)
{
    this->address = 0;
    this->value.intValue = value;
    this->type = INT_TYPE;
    this->symbolType = CONSTANT_SYMBOL;
}

Symbol::Symbol(double value)
{
    this->address = 0;
    this->value.doubleValue = value;
    this->type = REAL_TYPE;
    this->symbolType = CONSTANT_SYMBOL;
}

std::string Symbol::getSymbolName()
{
    return this->symbolName;
}

VarType Symbol::getVarType()
{
    return this->type;
}

void Symbol::setSymbolType(SymbolType symbolType)
{
    this->symbolType = symbolType;
}

Symbol::~Symbol()
{

}