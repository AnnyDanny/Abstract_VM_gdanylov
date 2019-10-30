#ifndef AVM_IOPERAND_HPP
#define AVM_IOPERAND_HPP

#include "Common.hpp"

class IOperand {
  public:
    virtual ~IOperand() {}

    virtual int getPrecision() const = 0;                           
    virtual eOperandType getType() const = 0;                       
    virtual IOperand const *operator+(IOperand const &) const = 0;  
    virtual IOperand const *operator-(IOperand const &) const = 0;  
    virtual IOperand const *operator*(IOperand const &)const = 0;   
    virtual IOperand const *operator/(IOperand const &) const = 0;  
    virtual IOperand const *operator%(IOperand const &) const = 0;  
    virtual std::string const &toString() const = 0;                
};

#endif  // AVM_IOPERAND_HPP
