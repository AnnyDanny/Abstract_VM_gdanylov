#ifndef AVM_EXCEPTIONS_HPP
#define AVM_EXCEPTIONS_HPP

#include <exception>
#include <stdexcept>

class BaseException : public std::runtime_error {
  public:
    explicit BaseException(const char *str);
    virtual const char *what() const noexcept;
};

class BadFile : public BaseException {
  public:
    BadFile();
};

class Overflow : public BaseException {
  public:
    Overflow();
};

class Underflow : public BaseException {
  public:
    Underflow();
};

class UnknownInstruction : public BaseException {
  public:
    UnknownInstruction();
};

class BadValue : public BaseException {
  public:
    BadValue();
};

class ToFewOperands : public BaseException {
  public:
    ToFewOperands();
};

class DivModByZero : public BaseException {
  public:
    DivModByZero();
};

class AssertionError : public BaseException {
  public:
    AssertionError();
};

class ExitMissing : public BaseException {
  public:
    ExitMissing();
};

class PopOnEmpty : public BaseException {
   public:
    PopOnEmpty();
};

class SyntaxError : public BaseException {
   public:
    SyntaxError();
};

#endif  // AVM_EXCEPTIONS_HPP
