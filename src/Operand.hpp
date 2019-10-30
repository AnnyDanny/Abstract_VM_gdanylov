#ifndef Operand_HPP_
#define Operand_HPP_

#include <cfenv>
#include <cmath>
#include <functional>
#include <iomanip>
#include <sstream>

#include "Exceptions.hpp"
#include "Factory.hpp"

template <typename Type>
class Operand : public IOperand {
    struct MyPlus {
        template <typename T, std::enable_if_t<std::is_integral<T>::value, int> = 0>
        T operator()(const T &x, const T &y) const
        {
            T res = x + y;
            if (x > 0 && y > 0 && res < 0)
                throw Overflow();
            if (x < 0 && y < 0 && res > 0)
                throw Overflow();
            return res;
        }

        template <typename T, std::enable_if_t<std::is_floating_point<T>::value, int> = 0>
        T operator()(const T &x, const T &y) const
        {
            std::feclearexcept(FE_OVERFLOW);
            std::feclearexcept(FE_UNDERFLOW);
            T res = x + y;
            if ((bool)std::fetestexcept(FE_OVERFLOW))
                throw Overflow();
            if ((bool)std::fetestexcept(FE_UNDERFLOW))
                throw Underflow();
            return res;
        }
    };

    struct MyMinus {
        template <typename T, std::enable_if_t<std::is_integral<T>::value, int> = 0>
        T operator()(const T &x, const T &y) const
        {
            T res = x - y;
            if (res + y != x)
                throw Underflow();
            return res;
        }

        template <typename T, std::enable_if_t<std::is_floating_point<T>::value, int> = 0>
        T operator()(const T &x, const T &y) const
        {
            std::feclearexcept(FE_OVERFLOW);
            std::feclearexcept(FE_UNDERFLOW);
            T res = x - y;
            if ((bool)std::fetestexcept(FE_OVERFLOW))
                throw Overflow();
            if ((bool)std::fetestexcept(FE_UNDERFLOW))
                throw Underflow();
            return res;
        }
    };

    struct MyMul {
        template <typename T, std::enable_if_t<std::is_integral<T>::value, int> = 0>
        T operator()(const T &x, const T &y) const
        {
            T res = x * y;
            if (res / x != y)
                throw Overflow();
            return res;
        }

        template <typename T, std::enable_if_t<std::is_floating_point<T>::value, int> = 0>
        T operator()(const T &x, const T &y) const
        {
            std::feclearexcept(FE_UNDERFLOW);
            std::feclearexcept(FE_OVERFLOW);
            T res = x * y;
            if ((bool)std::fetestexcept(FE_OVERFLOW))
                throw Overflow();
            if ((bool)std::fetestexcept(FE_UNDERFLOW))
                throw Underflow();
            return res;
        }
    };

    struct MyDiv {
        template <typename T>
        T operator()(const T &x, const T &y) const
        {
            if (y == 0) {
                throw DivModByZero();
            }
            return x / y;
        }
    };

    struct MyMod {
        template <typename T>
        T operator()(const T &x, const T &y) const
        {
            if (y == 0) {
                throw DivModByZero();
            }
            if (is_floating_point<T>::value) {
                return mod(x, y);
            } else {
                return mod(x, y);
            }
        }

      private:
        double mod(const double &x, const double &y) const
        {
            return fmod(x, y);
        }

        int32_t mod(const int32_t &x, const int32_t &y) const
        {
            return x % y;
        }
    };

  public:

    Operand(Type val, int precision, eOperandType type) : _val(val), _precision(precision), _type(type)
    {
        std::ostringstream stream;
        stream << std::fixed;
        if (_type == Int8) {
            stream << static_cast<int32_t>(_val);
        } else {
            stream << _val;
        }
        _str = stream.str();
    }

    int getPrecision() const
    {
        return _precision;
    }

    eOperandType getType() const
    {
        return _type;
    }

    IOperand const *operator+(IOperand const &rhs) const
    {
        return eval(MyPlus(), rhs);
    }

    IOperand const *operator-(IOperand const &rhs) const
    {
        return eval(MyMinus(), rhs);
    }

    IOperand const *operator*(IOperand const &rhs) const
    {
        return eval(MyMul(), rhs);
    }

    IOperand const *operator/(IOperand const &rhs) const
    {
        return eval(MyDiv(), rhs);
    }

    IOperand const *operator%(IOperand const &rhs) const
    {
        return eval(MyMod(), rhs);
    }

    std::string const &toString() const
    {
        return _str;
    }

  private:
    Operand();
    Operand(const Operand &);
    Operand &operator=(const Operand &);
    
    template <class T>
    const IOperand* create_op(T res, eOperandType type) const{
        return _factory.createOperand(type, std::to_string(res));
    }

    template <class F>
    const IOperand* ev(eOperandType type, const IOperand &rhs, F f) const{
                    switch (type) {
                case Int16:
                    return create_op(f.template operator()<int16_t>(static_cast<int16_t>(_val), static_cast<int16_t>(std::stoi(rhs.toString()))),
                                     type);
                case Int32:
                    return create_op(f(static_cast<int32_t>(_val), static_cast<int32_t>(std::stoi(rhs.toString()))),
                                     type);
                case Float:
                    return create_op(f(static_cast<float>(_val), static_cast<float>(std::stof(rhs.toString()))), type);
                case Double:
                    return create_op(f(static_cast<double>(_val), static_cast<double>(std::stod(rhs.toString()))),
                                     type);
                default:
                    return create_op(f(static_cast<int8_t>(_val), static_cast<int8_t>(std::stoi(rhs.toString()))),
                                     type);
            }
    }

    template <class F>
    const IOperand *eval(F f, IOperand const &rhs) const
    {
        if (_precision < rhs.getPrecision()) {
            return ev(rhs.getType(), rhs, f);
        }
        return ev(_type, rhs, f);
    }

    Type _val;
    int _precision;
    eOperandType _type;
    Factory _factory;
    std::string _str;
};

#endif  // Operand_HPP_
