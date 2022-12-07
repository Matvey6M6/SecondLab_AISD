#include "Mnogochlen.hpp"

int Mnogochlen::GetEpsilon() const {return this->Epsilon;}

Mnogochlen Mnogochlen::Normalize() const
{
    Mnogochlen *Newbie = new Mnogochlen(GetOrderOfMnogochlen(), GetEpsilon());
    double Delitel = (*this)[GetOrderOfMnogochlen()];
    for (int i = OrderOfMnogochlen; i >= 0; i--)
    {
        Newbie->Set(i, ((*this)[i] / Delitel));
    }
    return *Newbie;
}

Node *Mnogochlen::GetHead() const
{
    return Head;
}

long long Mnogochlen::GetOrderOfMnogochlen() const
{
    return OrderOfMnogochlen;
}

Mnogochlen::Mnogochlen(long long Order, int Epsilon)
{
    if (Order >= 0 || Epsilon > 0)
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

Mnogochlen::Mnogochlen(const Mnogochlen& Other)
{
    OrderOfMnogochlen = Other.GetOrderOfMnogochlen();
    Head = nullptr;
    this->Epsilon = Other.GetEpsilon();

    Node* P = Other.GetHead();

    while(P != nullptr)
    {
        Set(P->MyOrder,P->Value);
        P=P->Next;
    }
}

Mnogochlen::~Mnogochlen()
{
    while (Head->Next != nullptr)
    {
        Node *tmp = Head;
        Head = Head->Next;
        delete tmp;
    }
}

void Mnogochlen::Set(long long Order, double Coef)
{
    if (Coef == 0)
    {
        cout << "\n!!!Only non-zero coefs will be saved!!!" << endl;
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
        Node *newbie = new Node;
        newbie->MyOrder = Order;
        newbie->Value = Coef;
        newbie->Next = nullptr;
        Head = newbie;
        return;
    }

    Node *PointerA = GetHead();
    Node *PointerB = PointerA;
    for (long long i = 0; i < GetOrderOfMnogochlen() + 1 && PointerA; i++)
    {
        if (PointerA->Next == nullptr && Order < PointerA->MyOrder) //последний эдемент
        {
            Node *newbie = new Node;
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
            Node *newbie = new Node;
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

double Mnogochlen::operator[](long long Order) const
{
    Node *Pointer = GetHead();

    while (Pointer)
    {
        if (Pointer->MyOrder == Order)
            return Pointer->Value;
        Pointer = Pointer->Next;
    }
    return 0;
}

Mnogochlen Mnogochlen::operator+(const Mnogochlen &Other) const
{
    long long Maximum = 0;

    this->GetOrderOfMnogochlen() < Other.GetOrderOfMnogochlen() ? Maximum = Other.GetOrderOfMnogochlen() : Maximum = this->GetOrderOfMnogochlen();

    Mnogochlen Result(Maximum, this->GetEpsilon());

    long long CurrentOrder = Maximum;

    while (CurrentOrder > -1)
    {
        Result.Set(CurrentOrder, ((*this)[CurrentOrder]) + (Other[CurrentOrder]));
        CurrentOrder--;
    }

    return Result;

}

Mnogochlen Mnogochlen::operator-(const Mnogochlen &Other) const
{
    long long Maximum = 0;

    this->GetOrderOfMnogochlen() < Other.GetOrderOfMnogochlen() ? Maximum = Other.GetOrderOfMnogochlen() : Maximum = this->GetOrderOfMnogochlen();

    Mnogochlen Result(Maximum, this->GetEpsilon());

    long long CurrentOrder = Maximum;

    while (CurrentOrder > -1)
    {
        Result.Set(CurrentOrder, ((*this)[CurrentOrder]) - (Other[CurrentOrder]));
        CurrentOrder--;
    }

    return Result;
}

Mnogochlen Mnogochlen::operator*(double Val) const
{
    Node *Pointer = GetHead();
    Mnogochlen Result(Pointer->MyOrder, this->GetEpsilon());

    while(Pointer != NULL)
    {
        Result.Set(Pointer->MyOrder, Pointer->Value * Val);
        Pointer = Pointer->Next;
    }
    return Result;
}

Mnogochlen operator*(const int val, const Mnogochlen& M) // обеспечивает коммутативность
{
    return M * val;
}

bool Mnogochlen::operator==(const Mnogochlen &Other) const
{
    cout<<"Epsilon = "<<Epsilon<<endl;
    Node* P1 = this->GetHead();
    Node* P2 = Other.GetHead();

    if(P1 != nullptr && P2!= nullptr)
    {
        if(P1->MyOrder == P2->MyOrder)
        {
            while(P1 != nullptr && P2!= nullptr)
            {
                if((abs(P1->Value - P2->Value) < Epsilon))
                {
                    if(P1->MyOrder == P2->MyOrder && P1->MyOrder == 0) return true;
                }
                else return false;
                P1 = P1->Next;
                P2 = P2->Next;
            }
        }
        else return false;
    }
    if(this->GetHead() || Other.GetHead()) return false;
    return true;
}

bool Mnogochlen::operator!=(const Mnogochlen &Other) const
{
    cout<<"Epsilon = "<<Epsilon<<endl;
    Node* P1 = this->GetHead();
    Node* P2 = Other.GetHead();

    if(P1 != nullptr && P2!= nullptr)
    {
        if(P1->MyOrder != P2->MyOrder)
        {
            return true;
        }
        else 
        {
            while(P1 != nullptr && P2!= nullptr)
            {
                if((abs(P1->Value - P2->Value) > Epsilon))
                {
                    return true;
                }
                else 
                {
                    if(P1->MyOrder - P2->MyOrder && P1->MyOrder == 0) return false;
                }
                P1 = P1->Next;
                P2 = P2->Next;
            }
        }
    }
    if(this->GetHead() || Other.GetHead()) return true;
    return false;
}

void Mnogochlen::GetRoots() const
{
    if (GetOrderOfMnogochlen() != 3)
    {
        throw RangeError("Order is not 3");
    }
    Node *Pointer = GetHead();
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

/*Mnogochlen::Mnogochlen(const Mnogochlen& src)
{
    this->OrderOfMnogochlen = src.GetOrderOfMnogochlen();
    
    Node* Pointer = src.GetHead();

    int i = OrderOfMnogochlen;

    while(Pointer)
    {
        this->Set(i, Pointer->Value);
        Pointer = Pointer->Next;
        i--;
    }
}*/

double Mnogochlen::CountValue(double x) const
{
    Node *Pointer = GetHead();
    double Ans = 0;
    for (long long i = 0; i < GetOrderOfMnogochlen() + 1 && Pointer; i++)
    {
        Ans += Pointer->Value * pow(x, Pointer->MyOrder);
        Pointer = Pointer->Next;
    }
    return Ans;
}
