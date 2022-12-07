#pragma once
#include <iostream>

using namespace std;

class MnogochlenExceptions : public exception
{
protected:
    const char *Message;

    MnogochlenExceptions();

    void SetMessage(const char *Message);

    void PrintInfo() const;
};

class MemoryError : MnogochlenExceptions
{
public:
    MemoryError(const char *Message);
};

class RangeError : MnogochlenExceptions
{
public:
    RangeError(const char *Message);
};
