#include <iostream>
#include <conio.h>
#include <complex>
#include "Mnogochlen.hpp"
using namespace std;

template <typename T>
T check()
{
    T Value = T(0);

    while (!(cin >> Value) || (cin.peek() != '\n'))
    {
        cin.clear();
        while (cin.get() != '\n')
            ;
        cout << "Incorrect value\n";
    }
    return Value;
}

template <typename T>
Mnogochlen<T> *MenuInput()
{
    cout << "Create poilynominal menu\n\n"
         << endl;

    cout << "Order of Mnogochlen: " << endl;
    long long OrderOfMnogochlen = check<long long>();

    cout << "Epsilon: " << endl;
    T Epsilon = check<T>();

    Mnogochlen<T> *Newbie = NULL;
    try
    {
        Newbie = new Mnogochlen<T>(OrderOfMnogochlen, Epsilon);
    }
    catch (exception e)
    {
        clog << "An exception occured" << endl;
    }

    for (long long i = OrderOfMnogochlen; i >= 0; i--)
    {
        cout << "Coef by " << i << ":\n";
        T Coefficient = check<T>();
        Newbie->Set(i, Coefficient);
        cout << endl;
    }

    cout << "Created Mnogochlen: " << *Newbie << endl;
    cout << "Press any key" << endl;
    _getch();

    return Newbie;
}

template <typename T>
ostream &operator<<(ostream &os, const Mnogochlen<T> &Obj)
{
    if (Obj.GetOrderOfMnogochlen() == -1)
    {
        cout << "Mnogochlen has no coefs" << endl;
    }
    Node<T> *Pointer = Obj.GetHead();
    for (int i = 0; i < Obj.GetOrderOfMnogochlen() + 1 && Pointer; i++)
    {
        os << Pointer->Value << "*x^" << Pointer->MyOrder;
        if (Pointer->Next)
            os << " + ";
        Pointer = Pointer->Next;
    }
    return os;
}

template <typename T>
T InputValue()
{
    cout << "Give a value: " << endl;
    T X = check<T>();
    return X;
}

template <typename T>
void GiveAnX(const Mnogochlen<T> *Object)
{
    T Y = T(0);
    T X = InputValue<T>();

    for (long long i = Object->GetOrderOfMnogochlen(); i >= 0; i--)
    {
        Y += (*Object)[i] * T(pow(X, i));
    }

    cout << "Value for polynom (x = " << X << "): " << Y << endl;
}

template <typename T>
void Sum(const Mnogochlen<T> *Object)
{
    system("cls");

    cout << "Firstly input another polynom" << endl;
    cout << "Any key to input another polynom" << endl;

    _getch();

    system("cls");

    const Mnogochlen<T> *Another = MenuInput<T>();

    system("cls");

    cout << "Sum of two Mnogochlens:" << endl;
    cout << "\n\nFirst: " << (*Object) << endl;
    cout << "\nSecond: " << (*Another) << endl;
    cout << "\nTheir sum: " << ((*Object) + (*Another)) << endl;

    delete Another;
}

template <typename T>
void Substract(const Mnogochlen<T> *Object)
{
    system("cls");

    cout << "Substract menu\n"
         << endl;

    cout << "Firstly input another polynom" << endl;
    cout << "Any key to input another polynom" << endl;

    _getch();

    system("cls");

    const Mnogochlen<T> *Another = MenuInput<T>();

    system("cls");

    cout << "Substract menu\n"
         << endl;

    cout << "Substract of two Mnogochlens:" << endl;
    cout << "First: " << (*Object) << endl;
    cout << "Second: " << (*Another) << endl;
    cout << "Their substruction result: " << ((*Object) - (*Another)) << endl;

    delete Another;
}

template <typename T>
void MultiplyByArg(const Mnogochlen<T> *Object)
{
    cout << "Multiply by arg menu\n"
         << endl;
    T Arg = InputValue<T>();

    system("cls");

    cout << "Multiply by arg menu\n"
         << endl;

    cout << "(" << (*Object) << ")"
         << " * " << Arg << " :" << endl;
    cout << (*Object) * Arg << endl;
}

template <typename T>
void ChangeCoefByIndex(Mnogochlen<T> *Object)
{
    system("cls");

    cout << "Change coefficient by index menu\n"
         << endl;
    cout << (*Object) << endl;
    cout << "Input index: ";
    int Index = check<int>();
    cout << "Input new value: ";
    T value = check<T>();
    (*Object).Set(Index, value);
    cout << "Value: " << (*Object)[Index] << endl;
}

template <typename T>
void CompareTwoPolynoms(const Mnogochlen<T> *Object)
{
    system("cls");

    cout << "Compare two polynoms menu\n"
         << endl;

    cout << "Firstly input another polynom" << endl;
    cout << "Any key to input another polynom" << endl;

    _getch();

    system("cls");

    const Mnogochlen<T> *Another = MenuInput<T>();

    system("cls");

    cout << "Compare two polynoms menu\n"
         << endl;

    cout << "First " << (*Object) << endl;
    cout << "Second " << (*Another) << endl;

    if ((*Object) == (*Another))
    {
        cout << "The first is equal to second." << endl;
    }
    else
    {
        cout << "The first is NOT equal to second." << endl;
    }

    cout << "Press any button to continue" << endl;
    _getch();
}

template <typename T>
void GetRoots(const Mnogochlen<T> *Object)
{
    if (Object->GetOrderOfMnogochlen() != 3)
    {
        throw RangeError("Incorrect order");
    }

    system("cls");

    cout << "Get roots menu\n"
         << endl;

    cout << (*Object) << endl;

    Object->GetRoots();
}

int MenuChoice()
{
    cout << "\n\t[1] - Give an X" << endl;
    cout << "\n\t[2] - Sum" << endl;
    cout << "\n\t[3] - Substract" << endl;
    cout << "\n\t[4] - Multiply by arg" << endl;
    cout << "\n\t[5] - Change coefficinent by index" << endl;
    cout << "\n\t[6] - Get roots (3rd order)" << endl;
    cout << "\n\t[7] - Compare two polynoms" << endl;
    cout << "\n\t[BACKSPACE] - Set new polynoms" << endl;
    cout << "\n\n\tEsc - Exit" << endl;
    while (true)
    {
        int key = _getch();
        if ((key == 49) || (key == 50) || (key == 51) || (key == 52) || (key == 53) || (key == 54) || (key == 55) || (key == 127) || (key == 27))
        {
            return key;
        }
    }
}

template <typename T>
int Menu1()
{

    while (true)
    {

        cout << "Hellow, world!" << endl;
        system("cls");

        Mnogochlen<T> *Object = nullptr;

        Object = MenuInput<T>();

        while (Object)
        {
            system("cls");

            cout << "Your polymon: " << *Object << endl;
            int Choice = MenuChoice();

            switch (Choice)
            {
            case 49: // Give an X
                GiveAnX<T>(Object);
                break;
            case 50: // Sum

                Sum<T>(Object);
                break;
            case 51: // Substract
                Substract<T>(Object);
                break;
            case 52: // Multiply by arg
                MultiplyByArg<T>(Object);
                break;
            case 53: // Get doef by index
                ChangeCoefByIndex<T>(Object);
                break;
            case 54: // Get premitive fucntion
                GetRoots<T>(Object);
                break;
            case 55: // Compare two polynoms
                CompareTwoPolynoms<T>(Object);
                break;
            case 127: // Set new polynoms
                delete Object;
                Object = nullptr;
                break;
            case 27: // Exit
                system("cls");
                cout << "Work is done" << endl;
                return EXIT_SUCCESS;
                break;
            default:
                break;
            }

            cout << "Press any key" << endl;
            _getch();
        }
    }
}

int main()
{
    while (true)
    {
        system("cls");
        cout << "Choose type:" << endl;
        ;
        cout << "[1] - int" << endl;
        ;
        cout << "[2] - float" << endl;
        ;
        cout << "[3] - double" << endl;
        ;
        cout << "[4] - complex (float)" << endl;
        ;
        cout << "[5] - complex (double)" << endl;
        ;
        cout << "[ESC] - Exit" << endl;
        ;

        int Choice = _getch();

        switch (Choice)
        {
        case 49:
            Menu1<int>();
            break;
        case 50:
            Menu1<float>();
            break;
        case 51:
            Menu1<double>();
            break;
        case 52:
            Menu1<complex<float>>();
            break;
        case 53:
            Menu1<complex<double>>();
            break;
        case 27:
            return EXIT_SUCCESS;
        default:
            system("clear");
            break;
        }
    }
}