#pragma once
#include <iostream>
#include <math.h>
#include "MnogochlenExceptions.hpp"
using namespace std;
#define M_PI (3.141592653589793)
#define M_2PI (2. * M_PI)

template <typename T>
struct Node
{
    long long MyOrder;
    T Value;
    Node *Next;
    Node(long long MyOrder = 0, T Value = 0, Node *Next = nullptr)
    {
        this->MyOrder = MyOrder;
        this->Value = Value;
        this->Next = Next;
    }
};

template <typename T>
class Mnogochlen
{
    Node<T> *Head;

    long long OrderOfMnogochlen;

    Mnogochlen Normalize() const;

public:

    static T Epsilon;

    Node<T> *GetHead() const;

    long long GetOrderOfMnogochlen() const;

    Mnogochlen(long long Order);

    Mnogochlen(const Mnogochlen &Other);

    ~Mnogochlen();

    void Set(long long Order, T Coef);

    T operator[](long long Order) const;

    Mnogochlen operator+(const Mnogochlen &Other) const;

    Mnogochlen operator-(const Mnogochlen &Other) const;

    Mnogochlen operator*(T Val) const;

    bool operator==(const Mnogochlen &Other) const;

    bool operator!=(const Mnogochlen &Other) const;

    void GetRoots() const;

    T CountValue(T x) const;

    // friend ostream &operator<<(ostream &os, const Mnogochlen &Obj);

    /*
    friend bool operator>(const T& a, const T& b);
    friend bool operator<(const T& a, const T& b);
    friend bool operator>=(const T& a, const T& b);
    friend bool operator>=(const T& a, const T& b);
    */
};

template <typename T>
T Mnogochlen<T>::Epsilon = T(0);

