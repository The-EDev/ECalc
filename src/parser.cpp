#include "parser.h"
#include <math.h>

namespace E {

enum calc_operator
{
    Pwr,
    Mul,
    Div,
    Mod,
    Add,
    Sub
};

const std::vector<char> calc_operator_char
    ({
        '^',
        'x',
        '/',
        '%',
        '+',
        '-'
    });

double calc (double x, double y, calc_operator op)
{
    switch (op)
    {
    case Add: return x+y;
    case Mod: return int(x)%int(y);
    case Div: return x/y;
    case Mul: return x*y;
    case Sub: return x-y;
    case Pwr: return pow(x,y);
    }
    return 0.0;
}

class expression
{
public:
    virtual ~expression() {}
    virtual double evaluate() = 0;
    virtual std::string print() = 0;
};

class value : public expression
{
public:
    value(double _val) : val(_val){}
    ~value() {}
    double evaluate() override
    {
        return val;
    }
    std::string print() override
    {
        return std::to_string(val);
    }
private:
    double val;
};

class operation : public expression
{
public:
    operation(expression *_A, expression *_B, calc_operator _op) : A(_A), B(_B), op(_op) {}
    double evaluate() override
    {
        return calc(A->evaluate(), B->evaluate(), op);
    }
    std::string print() override
    {
        return std::string('(' + A->print() + calc_operator_char[op] + B->print() + ')');
    }
private:
    std::unique_ptr<expression> A, B;
    calc_operator op;
};

const std::unordered_map<char, uint8_t> precedence
    ({
        {'(',0},
        {'^',1},
        {'*',2},
        {'/',2},
        {'%',2},
        {'+',3},
        {'-',3},
        {')',(uint8_t)-1}
    });

enum operation_state {
    DEF,
    VAL,
    OP,
    PAR
};

inline double val(std::string& acc)
{
    double ret(0.0);
    if (!acc.empty())
    {
        ret = std::stod(acc);
        acc.clear();
    }
    return ret;
}

// Whether or not to use the variable after
size_t lookahead(size_t index, std::string& str)
{
    uint8_t current_precedence = precedence.at(str[index-1]);
    for (; index < str.size(); index++)
    {
        char c(str[index]);
        switch (c)
        {
        case '+':
        case '-':
        case '*':
        case '/':
        case '%':
        case '^':
        case '(':
        case ')':
        {
            uint8_t pres (precedence.at(c));
            return current_precedence <= pres ? index : 0;
        }

        default: break; // Assume a number
        }
    }
    return str.size(); // if the for loop ran and finished, return the last index + 1
}

expression* parse(std::string& str, size_t index = 0, expression* prev = 0);

inline expression* parse_operator(size_t index, std::string& str, expression* acc, calc_operator c_op)
{
    if (size_t end = lookahead(++index, str))
    {
        std::string b(str.substr(index, end-index));
        if (end != str.size())
            return parse(str, end, new operation(acc, new value(val(b)), c_op));
        return new operation(acc, new value(val(b)), c_op);
    }

    return new operation(acc, parse(str, index), c_op);
}

expression* parse(std::string& str, size_t index, expression* prev)
{
    std::string acc("");
    for (; index < str.size(); index++)
    {
        char c(str[index]);
        switch (c)
        {
        case '+': return parse_operator(index, str, prev ? prev : new value(val(acc)), calc_operator::Add);
        case '-': return parse_operator(index, str, prev ? prev : new value(val(acc)), calc_operator::Sub);
        case '*': return parse_operator(index, str, prev ? prev : new value(val(acc)), calc_operator::Mul);
        case '/': return parse_operator(index, str, prev ? prev : new value(val(acc)), calc_operator::Div);
        case '%': return parse_operator(index, str, prev ? prev : new value(val(acc)), calc_operator::Mod);
        case '^': return parse_operator(index, str, prev ? prev : new value(val(acc)), calc_operator::Pwr);

        case '(':
        case ')':
        case ' ': break;
        default: acc+=c; // Assume a number
        }
    }
    return new value(acc.empty() ? 0 : val(acc));
} //TODO fails when paranthesis are in middle or at end

}

BackEnd::BackEnd(QObject *parent) :
    QObject(parent)
{
}

double BackEnd::calculate(QString expression)
{
    std::string xstr (expression.toStdString());
    std::unique_ptr<E::expression>ex (E::parse(xstr));
    return ex->evaluate();
}
