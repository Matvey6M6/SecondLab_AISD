#include <iostream>
//#include <conio.h>
#include <unistd.h>
#include <termios.h>
#include "Mnogochlen.hpp"
using namespace std;

char _getch(void)
{
    char buf = 0;
    struct termios old = {0};
    fflush(stdout);
    if (tcgetattr(0, &old) < 0)
        perror("tcsetattr()");
    old.c_lflag &= ~ICANON;
    old.c_lflag &= ~ECHO;
    old.c_cc[VMIN] = 1;
    old.c_cc[VTIME] = 0;
    if (tcsetattr(0, TCSANOW, &old) < 0)
        perror("tcsetattr ICANON");
    if (read(0, &buf, 1) < 0)
        perror("read()");
    old.c_lflag |= ICANON;
    old.c_lflag |= ECHO;
    if (tcsetattr(0, TCSADRAIN, &old) < 0)
        perror("tcsetattr ~ICANON");
    return buf;
}

double check()
{
	double number = 0;
	
    while (!(cin >> number) || (cin.peek() != '\n'))
    {
        cin.clear();
        while (cin.get() != '\n');
        cout << "Incorrect value\n";
    }

    return number;
}

Mnogochlen *MenuInput()
{
    cout << "Create poilynominal menu\n\n"
         << endl;

    cout << "Order of Mnogochlen: " << endl;
    long long OrderOfMnogochlen = 0;
    cin >> OrderOfMnogochlen;

    cout << "Epsilon: " << endl;
    int Epsilon = int(check());
    Mnogochlen *Newbie = NULL;
    try
    {
        Newbie = new Mnogochlen(OrderOfMnogochlen, Epsilon);
    }
    catch (exception e)
    {
        clog << "An exception occured" << endl;
    }

    for (long long i = OrderOfMnogochlen; i >= 0; i--)
    {
        cout << "Coef by " << i << ":\n";
        double Coefficient =  check();
        Newbie->Set(i, Coefficient);
        cout << endl;
    }

    cout << "Created Mnogochlen: " << *Newbie << endl;
    cout << "Press any key" << endl;
    _getch();

    return Newbie;
}

ostream &operator<<(ostream &os, const Mnogochlen &Obj)
{
    if (Obj.GetOrderOfMnogochlen() == -1)
    {
        cout << "Mnogochlen has no coefs" << endl;
    }
    Node *Pointer = Obj.GetHead();
    for (int i = 0; i < Obj.GetOrderOfMnogochlen() + 1 && Pointer; i++)
    {
        os << Pointer->Value << "*x^" << Pointer->MyOrder;
        if (Pointer->Next)
            os << " + ";
        Pointer = Pointer->Next;
    }
    return os;
}

double InputValue()
{
    cout << "Give a value: " << endl;
    double X = check();
    return X;
}

void GiveAnX(const Mnogochlen *Object)
{
    double Y = 0;
    double X = InputValue();

    for (int i = Object->GetOrderOfMnogochlen(); i >= 0; i--)
    {
        Y += (*Object)[i] * pow(X, i);
    }

    cout << "Value for polynom (x = " << X << "): " << Y << endl;
}

void Sum(const Mnogochlen *Object)
{
    system("clear");

    cout << "Firstly input another polynom" << endl;
    cout << "Any key to input another polynom" << endl;

    _getch();

    system("clear");

    const Mnogochlen *Another = MenuInput();

    system("clear");

    cout << "Sum of two Mnogochlens:" << endl;
    cout << "\n\nFirst: " << (*Object) << endl;
    cout << "\nSecond: " << (*Another) << endl;
    cout << "\nTheir sum: " << ((*Object) + (*Another)) << endl;

    delete Another;
}

void Substract(const Mnogochlen *Object)
{
    system("clear");

    cout << "Substract menu\n"
         << endl;

    cout << "Firstly input another polynom" << endl;
    cout << "Any key to input another polynom" << endl;

    _getch();

    system("clear");

    const Mnogochlen *Another = MenuInput();

    system("clear");

    cout << "Substract menu\n"
         << endl;

    cout << "Sum of two Mnogochlens:" << endl;
    cout << "First: " << (*Object) << endl;
    cout << "Second: " << (*Another) << endl;
    cout << "Their substruction result: " << ((*Object) - (*Another)) << endl;

    delete Another;
}

void MultiplyByArg(const Mnogochlen *Object)
{
    cout << "Multiply by arg menu\n"
         << endl;
    double Arg = InputValue();

    system("clear");

    cout << "Multiply by arg menu\n"
         << endl;

    cout << "(" << (*Object) << ")"
         << " * " << Arg << " :" << endl;
    cout << (*Object) * Arg << endl;
}

void ChangeCoefByIndex(Mnogochlen *Object)
{
    system("clear");

    cout << "Change coefficient by index menu\n"
         << endl;
    cout << (*Object) << endl;
    cout << "Input index: ";
    int Index = check();
    cout<<"Input new value: ";
    double value = check();
    (*Object).Set(Index, value);
    cout << "Value: " << (*Object)[Index] << endl;
}

void CompareTwoPolynoms(const Mnogochlen *Object)
{
    system("clear");

    cout << "Compare two polynoms menu\n"
         << endl;

    cout << "Firstly input another polynom" << endl;
    cout << "Any key to input another polynom" << endl;

    _getch();

    system("clear");

    const Mnogochlen *Another = MenuInput();

    system("clear");

    cout << "Compare two polynoms menu\n"
         << endl;

    cout<<"First "<<(*Object)<<endl;
    cout<<"Second "<<(*Another)<<endl;    

    if((*Object) == (*Another))
    {
        cout << "The first is equal to second." << endl;
    }
    else
    {
        cout << "The first is NOT equal to second." << endl;
    }

    cout<<"Press any button to continue"<<endl;
    _getch();
}

void GetRoots(const Mnogochlen *Object)
{
    if (Object->GetOrderOfMnogochlen() != 3)
    {
        throw RangeError("Incorrect order");
    }

    system("clear");

    cout << "Get roots menu\n"
         << endl;

    cout<<(*Object)<<endl;

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
    cout << "\n\t[7] - Compare two polynoms"<<endl;
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

int main()
{

    while (true)
    {

        cout << "Hellow, world!" << endl;
        system("clear");

        Mnogochlen *Object = nullptr;

        Object = MenuInput();

        while (Object)
        {
            system("clear");

            cout << "Your polymon: " << *Object << endl;
            int Choice = MenuChoice();

            switch (Choice)
            {
            case 49: // Give an X
                GiveAnX(Object);
                break;
            case 50: // Sum

                Sum(Object);
                break;
            case 51: // Substract
                Substract(Object);
                break;
            case 52: // Multiply by arg
                MultiplyByArg(Object);
                break;
            case 53: // Get doef by index
                ChangeCoefByIndex(Object);
                break;
            case 54: // Get premitive fucntion
                GetRoots(Object);
                break;
            case 55: // Compare two polynoms
                CompareTwoPolynoms(Object);
                break;
            case 127: // Set new polynoms
                delete Object;
                Object = nullptr;
                break;
            case 27: // Exit
                system("clear");
                cout << "Word is done" << endl;
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
