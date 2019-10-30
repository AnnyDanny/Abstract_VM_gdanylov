#include "Exceptions.hpp"

BaseException::BaseException(const char *str) : runtime_error(str)
{
}

const char *BaseException::what() const throw()
{
    return std::runtime_error::what();
}

BadFile::BadFile() : BaseException("Bad file")
{
}

Overflow::Overflow() : BaseException("Overflow")
{
}

Underflow::Underflow() : BaseException("Underflow")
{
}

UnknownInstruction::UnknownInstruction() : BaseException("Unknown instruction")
{
}

BadValue::BadValue() : BaseException("Bad value")
{
}

ToFewOperands::ToFewOperands() : BaseException("To few operands to perform operation")
{
}

DivModByZero::DivModByZero() : BaseException("Division/Modulo by zero")
{
}

AssertionError::AssertionError() : BaseException("Assertion error")
{
}

ExitMissing::ExitMissing() : BaseException("Exit missing")
{
}

PopOnEmpty::PopOnEmpty() : BaseException("Pop on empty stack")
{
}

SyntaxError::SyntaxError() : BaseException("Syntax error")
{
}
