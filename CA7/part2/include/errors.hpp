#ifndef __ERRORS__
#define __ERRORS__

#include "manual.hpp"

class Error
{
public:
    virtual void print_err() const = 0;
};
class Bad_Request : public Error
{
public:
    void print_err() const { print(BAD_REQUEST); }
};
class Permission_Denied : public Error
{
public:
    void print_err() const { print(PERMISSION_DENIED); }
};
class Not_Found : public Error
{
public:
    void print_err() const { print(NOT_FOUND); }
};
class Empty : public Error
{
public:
    void print_err() const { print(EMPTY); }
};
class Is_Not_Available : public Error
{
public:
    void print_err() const { print(IS_NOT_AVAILABLE); }
};
#endif
