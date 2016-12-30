#include "symbol.hpp"

Symbol::Symbol()
{
    this->references = -1;
    this->isReference = false;
    this->address = 0;
    this->type = NONE_TYPE;
    this->symbolType = NONE_SYMBOL;
}

Symbol::Symbol(int value)
{
    this->references = -1;
    this->isReference = false;
    this->address = 0;
    this->value.intValue = value;
    this->type = INT_TYPE;
    this->symbolType = CONSTANT_SYMBOL;
}

Symbol::Symbol(double value)
{
    this->references = -1;
    this->isReference = false;
    this->address = 0;
    this->value.doubleValue = value;
    this->type = REAL_TYPE;
    this->symbolType = CONSTANT_SYMBOL;
}

std::string Symbol::getSymbolName()
{
    if (this->symbolType == CONSTANT_SYMBOL)
    {
        if (this->type == INT_TYPE)
        {
            return std::to_string(this->value.intValue);
        }
        else
        {
            std::string doubleStr = std::to_string(this->value.doubleValue);
            return doubleStr.erase(doubleStr.find_last_not_of('0') + 3, std::string::npos);
        }
    }

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