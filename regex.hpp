#pragma once 

#include <iostream>
#include <stdexcept>
#include <string>
#include <regex>
#include <fstream>

class RegEx
{
public:
    virtual ~RegEx(){}; // Updated to specify noexcept
    virtual void display(std::ostream &os) const = 0;

    friend std::ostream &operator<<(std::ostream &os, const RegEx &regex)
    {
        regex.display(os);
        return os;
    }
};

class Choice : public RegEx
{
private:
    RegEx *thisOne;
    RegEx *thatOne;

public:
    Choice(RegEx *thisOne, RegEx *thatOne) : thisOne(thisOne), thatOne(thatOne) {}

    ~Choice()
    {
        delete thisOne;
        delete thatOne;
    }

    void display(std::ostream &os) const override
    {
        os << "choice-regex {";
        os << *thisOne << " or ";
        os << *thatOne << "}";
    }
};

class Sequence : public RegEx
{
private:
    RegEx *first;
    RegEx *second;

public:
    Sequence(RegEx *first, RegEx *second) : first(first), second(second) {}

    ~Sequence()
    {
        delete first;
        delete second;
    }

    void display(std::ostream &os) const override
    {
        os << "Sequence {";
        os << *first << ", ";
        os << *second << "}";
    }
};

class Repetition : public RegEx
{
private:
    RegEx *internal;

public:
    Repetition(RegEx *internal) : internal(internal) {}

    ~Repetition()
    {
        delete internal;
    }

    void display(std::ostream &os) const override
    {
        os << "Repetition {";
        os << *internal << "}";
    }
};

class Primitive : public RegEx
{
private:
    char c;

public:
    Primitive(char c) : c(c) {}

    void display(std::ostream &os) const override
    {
        os << c;
    }

    char getChar()
    {
        return this->c;
    }
};

class RegExParser
{
private:
    std::string input;

public:
    RegExParser(const std::string &input) : input(input) {}

    RegEx *parse()
    {
        return regex();
    }

private:
    char peek()
    {
        return (input.empty()) ? '\0' : input[0];
    }

    void eat(char c)
    {
        if (peek() == c)
            input = input.substr(1);
        else
            throw std::runtime_error("Expected: " + std::string(1, c) + "; got: " + peek());
    }

    char next()
    {
        char c = peek();
        eat(c);
        return c;
    }

    bool more()
    {
        return !input.empty();
    }

    RegEx *regex();
    RegEx *term();
    RegEx *factor();
    RegEx *base();
};

RegEx *RegExParser::regex()
{
    RegEx *term = this->term(); // Renamed to term_() to avoid conflict with variable name

    if (more() && peek() == '|')
    {
        eat('|');
        RegEx *nextRegex = regex();
        return new Choice(term, nextRegex);
    }
    else
    {
        return term;
    }
}

RegEx *RegExParser::term()
{
    RegEx *factor = new Primitive('$'); // 2

    while (more() && peek() != ')' && peek() != '|')
    {
        RegEx *nextFactor = this->factor();
        factor = new Sequence(factor, nextFactor);
    }

    return factor;
}

RegEx *RegExParser::factor()
{
    RegEx *baseRegex = base();

    while (more() && peek() == '*')
    {
        eat('*');
        baseRegex = new Repetition(baseRegex);
    }

    return baseRegex;
}

RegEx *RegExParser::base()
{
    char esc;
    RegEx *r = nullptr;

    switch (peek())
    {
    case '(':
        eat('(');
        r = regex();
        eat(')');
        return r;

    case '\\':
        eat('\\');
        esc = next();
        return new Primitive(esc);

    default:
        return new Primitive(next());
    }
}

std::string expandExpression(const std::string &input)
{
    std::regex pattern("([a-zA-Z0-9])\\+");
    std::string result = std::regex_replace(input, pattern, "$1$1*");
    return result;
}