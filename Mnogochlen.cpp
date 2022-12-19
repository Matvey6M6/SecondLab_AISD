#include "Mnogochlen.hpp"
#include <complex>

template <typename T>
inline bool operator>(const complex<T> a, const complex<T> b)
{
    return ((a.real() > b.real()) && (a.imag() > b.imag()));
}

template <typename T>
inline bool operator<(const complex<T> a, const complex<T> b)
{
    return ((a.real() < b.real()) && (a.imag() < b.imag()));
}

template <typename T>
inline bool operator<=(const complex<T> a, const complex<T> b)
{
    return ((a.real() <= b.real()) && (a.imag() <= b.imag()));
}

template <typename T>
inline bool operator>=(const complex<T> a, const complex<T> b)
{
    return ((a.real() >= b.real()) && (a.imag() >= b.imag()));
}

template <typename T>
Mnogochlen<T> Mnogochlen<T>::Normalize() const
{
    Mnogochlen *Newbie = new Mnogochlen(GetOrderOfMnogochlen());
    T Delitel = T((*this)[GetOrderOfMnogochlen()]);
    for (int i = OrderOfMnogochlen; i >= 0; i--)
    {
        Newbie->Set(i, ((*this)[i] / Delitel));
    }
    return *Newbie;
}

template <typename T>
Node<T> *Mnogochlen<T>::GetHead() const
{
    return Head;
}

template <typename T>
long long Mnogochlen<T>::GetOrderOfMnogochlen() const
{
    return OrderOfMnogochlen;
}

template <typename T>
Mnogochlen<T>::Mnogochlen(long long Order)
{
    if (Order >= 0 || Epsilon > T(0))
    {
        OrderOfMnogochlen = Order;
        Head = nullptr;
        this->Epsilon = Epsilon;
    }
    else
    {
        delete this;
        throw RangeError("Incorrect \"Order\" for polynomianl");
    }
}

template <typename T>
Mnogochlen<T>::Mnogochlen(const Mnogochlen &Other)
{
    OrderOfMnogochlen = Other.GetOrderOfMnogochlen();
    Head = nullptr;

    Node<T> *P = Other.GetHead();

    while (P != nullptr)
    {
        Set(P->MyOrder, P->Value);
        P = P->Next;
    }
}

template <typename T>
Mnogochlen<T>::~Mnogochlen()
{
    while (Head->Next != nullptr)
    {
        Node<T> *tmp = Head;
        Head = Head->Next;
        delete tmp;
    }
}

template <typename T>
void Mnogochlen<T>::Set(long long Order, T Coef)
{
    if (Coef == T(0))
    {
        if (Order == GetOrderOfMnogochlen())
        {
            OrderOfMnogochlen -= 1;
            cout << "Order -= 1" << endl;
        }
        return;
    }
    if (Order < 0 || Order > GetOrderOfMnogochlen())
    {
        throw RangeError("Incorrect \"Order\", value can't be initialized\n");
    }
    if (Head == nullptr)
    {
        Node<T> *newbie = new Node<T>;
        newbie->MyOrder = Order;
        newbie->Value = Coef;
        newbie->Next = nullptr;
        Head = newbie;
        return;
    }

    Node<T> *PointerA = GetHead();
    Node<T> *PointerB = PointerA;
    for (long long i = 0; i < GetOrderOfMnogochlen() + 1 && PointerA; i++)
    {
        if (PointerA->Next == nullptr && Order < PointerA->MyOrder) // последний эдемент
        {
            Node<T> *newbie = new Node<T>;
            newbie->MyOrder = Order;
            newbie->Value = Coef;
            newbie->Next = nullptr;

            PointerA->Next = newbie;
            return;
        }
        else if (PointerA->MyOrder == Order) // просто изменить значение
        {
            PointerA->Value = Coef;
            return;
        }
        else if (PointerA->MyOrder < Order) // добавить между
        {
            Node<T> *newbie = new Node<T>;
            newbie->MyOrder = Order;
            newbie->Value = Coef;

            newbie->Next = PointerA;
            PointerB->Next = newbie;
            return;
        }
        PointerB = PointerA;
        PointerA = PointerA->Next;
    }
}

template <typename T>
T Mnogochlen<T>::operator[](long long Order) const
{
    Node<T> *Pointer = GetHead();

    while (Pointer)
    {
        if (Pointer->MyOrder == Order)
            return Pointer->Value;
        Pointer = Pointer->Next;
    }
    return 0;
}

template <typename T>
Mnogochlen<T> Mnogochlen<T>::operator+(const Mnogochlen &Other) const
{
    long long Maximum = 0;

    this->GetOrderOfMnogochlen() < Other.GetOrderOfMnogochlen() ? Maximum = Other.GetOrderOfMnogochlen() : Maximum = this->GetOrderOfMnogochlen();

    Mnogochlen Result(Maximum);

    long long CurrentOrder = Maximum;

    while (CurrentOrder > -1)
    {
        Result.Set(CurrentOrder, ((*this)[CurrentOrder]) + (Other[CurrentOrder]));
        CurrentOrder--;
    }

    return Result;
}

template <typename T>
Mnogochlen<T> Mnogochlen<T>::operator-(const Mnogochlen &Other) const
{
    long long Maximum = 0;

    this->GetOrderOfMnogochlen() < Other.GetOrderOfMnogochlen() ? Maximum = Other.GetOrderOfMnogochlen() : Maximum = this->GetOrderOfMnogochlen();

    Mnogochlen Result(Maximum);

    long long CurrentOrder = Maximum;

    while (CurrentOrder > -1)
    {
        Result.Set(CurrentOrder, ((*this)[CurrentOrder]) - (Other[CurrentOrder]));
        CurrentOrder--;
    }

    return Result;
}

template <typename T>
Mnogochlen<T> Mnogochlen<T>::operator*(T Val) const
{
    Node<T> *Pointer = GetHead();
    Mnogochlen Result(Pointer->MyOrder);

    while (Pointer != NULL)
    {
        Result.Set(Pointer->MyOrder, Pointer->Value * Val);
        Pointer = Pointer->Next;
    }
    return Result;
}

template <typename T>
Mnogochlen<T> operator*(const T val, const Mnogochlen<T> &M) // обеспечивает коммутативность
{
    return M * val;
}

template <typename T>
bool Mnogochlen<T>::operator==(const Mnogochlen &Other) const
{
    cout << "Epsilon = " << Epsilon << endl;
    Node<T> *P1 = this->GetHead();
    Node<T> *P2 = Other.GetHead();

    if (P1 != nullptr && P2 != nullptr)
    {
        if (P1->MyOrder == P2->MyOrder)
        {
            while (P1 != nullptr && P2 != nullptr)
            {
                if (T(abs(P1->Value - P2->Value)) < Epsilon)
                {
                    if (P1->MyOrder == P2->MyOrder && P1->Next == nullptr && P2->Next == nullptr)
                        return true;
                }
                else
                    return false;
                P1 = P1->Next;
                P2 = P2->Next;
            }
        }
        else
            return false;
    }
    if (this->GetHead() || Other.GetHead()) { return false; }
    return true;
}

template <typename T>
bool Mnogochlen<T>::operator!=(const Mnogochlen &Other) const
{
    cout << "Epsilon = " << Epsilon << endl;
    Node<T> *P1 = this->GetHead();
    Node<T> *P2 = Other.GetHead();

    if (P1 != nullptr && P2 != nullptr)
    {
        if (P1->MyOrder != P2->MyOrder)
        {
            return true;
        }
        else
        {
            while (P1 != nullptr && P2 != nullptr)
            {
                if (T(abs(P1->Value - P2->Value)) > Epsilon)
                {
                    return true;
                }
                else
                {
                    if (P1->MyOrder - P2->MyOrder && P1->MyOrder == 0)
                        return false;
                }
                P1 = P1->Next;
                P2 = P2->Next;
            }
        }
    }
    if (this->GetHead() || Other.GetHead())
        return true;
    return false;
}

void Mnogochlen<int>::GetRoots() const
{
    if (GetOrderOfMnogochlen() != 3)
    {
        throw RangeError("Order is not 3");
    }
    //Node* Pointer = GetHead();
    Mnogochlen Normalized = Normalize();
    // cout << Normalized << endl;
    double a = Normalized[2];
    double b = Normalized[1];
    double c = Normalized[0];
    double x1;
    double x2;
    double x3;
    double q, r, r2, q3;
    q = (a * a - 3. * b) / 9.;
    r = (a * (2. * a * a - 9. * b) + 27. * c) / 54.;
    r2 = r * r;
    q3 = q * q * q;
    if (r2 < q3)
    {
        double t = acos(r / sqrt(q3));
        a /= 3.;
        q = -2. * sqrt(q);
        x1 = q * cos(t / 3.) - a;
        x2 = q * cos((t + M_2PI) / 3.) - a;
        x3 = q * cos((t - M_2PI) / 3.) - a;
        cout << "Root 1 = " << x1 << endl;
        cout << "Root 2 = " << x2 << endl;
        cout << "Root 3 = " << x3 << endl;
    }
    else
    {
        double aa, bb;
        if (r <= 0.)
            r = -r;
        aa = -pow(r + sqrt(r2 - q3), 1. / 3.);
        if (aa != 0.)
            bb = q / aa;
        else
            bb = 0.;
        a /= 3.;
        q = aa + bb;
        r = aa - bb;
        x1 = q - a;
        x2 = (-0.5) * q - a;
        x3 = (sqrt(3.) * 0.5) * fabs(r);
        if (x3 == 0.)
        {
            cout << "Root 1 = " << x1 << endl;
            cout << "Root 2 = " << x2 << endl;
        }
        cout << "Root 1 = " << x1 << endl;
    }
}

template <typename T>
void Mnogochlen<T>::GetRoots() const
{
    if (GetOrderOfMnogochlen() != 3)
    {
        throw RangeError("Order is not 3");
    }
    Node<T> *Pointer = GetHead();
    Mnogochlen Normalized = Normalize();
    T a = Normalized[2];
    T b = Normalized[1];
    T c = Normalized[0];
    T x1;
    T x2;
    T x3;
    T q, r, r2, q3;
    q = (a * a - T(3) * b) / T(9);
    r = (a * (T(2) * a * a - T(9) * b) + T(27) * c) / T(54);
    r2 = r * r;
    q3 = q * q * q;
    if (r2 < q3)
    {
        T t = acos(r / sqrt(q3));
        a /= T(3.);
        q = T(-2.) * sqrt(q);
        x1 = q * cos(t / T(3.)) - a;
        x2 = q * cos((t + T(M_2PI)) / T(3.)) - a;
        x3 = q * cos((t - T(M_2PI)) / T(3.)) - a;
        cout << "Root 1 = " << x1 << endl;
        cout << "Root 2 = " << x2 << endl;
        cout << "Root 3 = " << x3 << endl;
    }
    else
    {
        T aa, bb;
        if (r <= T(0))
            r = -r;
        aa = -pow(r + sqrt(r2 - q3), T(1) / T(3));
        if (aa != T(0))
            bb = q / aa;
        else
            bb = T(0);
        a /= T(3);
        q = aa + bb;
        r = aa - bb;
        x1 = q - a;
        x2 = T(-0.5) * q - a;
        x3 = (sqrt(T(3)) * T(0.5)) * abs(r);
        if (x3 == T(0.))
        {
            cout << "Root 1 = " << x1 << endl;
            cout << "Root 2 = " << x2 << endl;
        }
        else
        {
            cout << "Root 1 = " << x1 << endl;
        }
    }
}

template <typename T>
T Mnogochlen<T>::CountValue(T x) const
{
    Node<T> *Pointer = GetHead();
    T Ans = T(0);
    for (long long i = 0; i < GetOrderOfMnogochlen() + 1 && Pointer; i++)
    {
        Ans += Pointer->Value * pow(x, T(Pointer->MyOrder));
        Pointer = Pointer->Next;
    }
    return Ans;
}

/*template struct Node<int>;
template struct Node<float>;
template struct Node<double>;
template struct Node<complex<float>>;
template struct Node<complex<double>>;*/

template class Mnogochlen<int>;
template class Mnogochlen<float>;
template class Mnogochlen<double>;
template class Mnogochlen<complex<float>>;
template class Mnogochlen<complex<double>>;