#ifndef __ERRORS__
#define __ERRORS__

#include "manual.hpp"

class Error : public runtime_error
{
public:
    Error() : runtime_error("Error") {}
    virtual string what_happened() const = 0;
};

class RepetitiveModule : public Error
{
public:
    string what_happened() const { return  EXIST_MODULE_ERROR;}
};

class DuplicatedLogic : public Error
{
public:
    string what_happened() const { return  DUPLICATE_ID_ERROR;}
};

class IncompatibleInputs : public Error
{
public:
    string what_happened() const { return INCOMPATIBLE_ERROR;}
};

class IDNotFound : public Error
{
public:
    string what_happened() const { return ID_NOT_FOUND_ERROR;}
};

class LogicNotFound : public Error
{
public:
    string what_happened() const { return GATE_NOT_FOUND_ERROR; }
};

class InvalidConnection : public Error
{
public:
    string what_happened() const { return INVALID_CONNECTION_ERROR;}
};

class InvalidValue : public Error
{
public:
    string what_happened() const { return INVALID_VALUE_ERROR;}
};

#endif