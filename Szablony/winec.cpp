#include "winec.h"
using std::cout;
using std::cin;
using std::endl;
void Wine::GetBottles()
{
    if (n<0)
        cout<<"Błąd, tablica nie ma miejsca!";
    else
    {
        for (int i=0; i<n; i++)
        {
            cout<<"Podaj rocznik: ";
            int r;
            cin>>r;
            cout<<"Podaj liczbę butelek: ";
            int lb;
            cin>>lb;
            PairArray::first()[i]=r;
            PairArray::second()[i]=lb;
        }
    }
}
int Wine::sum() const
{
    int suma=0;
    for (int i=0; i<n; i++)
        suma+=PairArray::second()[i];
    return suma;
}
void Wine::Show() const
{
    cout<<"Wino: "<<(std::string)*this<<endl;
    cout<<"\tRocznik\tButelki\n";
    for (int i=0; i<n; i++)
        cout<<"\t"<<PairArray::first()[i]<<"\t"<<PairArray::second()[i]<<endl;
}
