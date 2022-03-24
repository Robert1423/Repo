#include <iostream>
#include "winec.h"
int main()
{
    using std::cin;
    using std::cout;
    using std::endl;
    cout<<"Podaj nazwę wina: ";
    char lab[50];
    cin.getline(lab,50);
    cout<<"Podaj liczbę roczników: ";
    int yrs;
    cin>>yrs;
    Wine holding(lab,yrs); //pobiera nazwę i liczbę roczników
    holding.GetBottles(); //pobiera dane o roczniku i liczbie butelek
    holding.Show(); //wyświetla zawartość
    const int YRS=3;
    int y[YRS]={1993,1995,1998};
    int b[YRS]={48,60,72};
    Wine more("Gushing Grape Red",YRS,y,b);
    more.Show();
    cout<<"Łączna liczba butelek wina "<<more.Label()
        <<": "<<more.sum()<<endl;
    cout<<"Koniec.\n";
    return 0;
}
