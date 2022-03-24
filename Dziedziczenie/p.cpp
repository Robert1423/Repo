#include <iostream>
#include "dma.h"
int main()
{
    using namespace std;
    DMA * p[4];
    char et[20];
    char k[20];
    char s[20];
    int a;
    for (int i=0; i<4; i++)
    {
        cout<<"Wprowadź etykietę: ";
        cin.getline(et,20);
        cout<<"Wprowadź numer klasy: ";
        while (!(cin>>a))
        {
            cin.clear();
            while (cin.get()!='\n')
                continue;
            cout<<"Błędne dane;\nWprowadź numer klasy: ";
        }
        cout<<"Wybierz rodzaj obiektu:\n1 - obiekt baseDMA,\n"
            <<"2 - obiekt lacksDMA,\n3 - obiekt hasDMA\n";
        int x;
        while (!(cin>>x)&&(x<1||x>4))
        {
            cin.clear();
            while (cin.get()!='\n')
                continue;
            cout<<"Błędny wybór!";
        }
        while (cin.get()!='\n')
            continue;
        if (x==1)
            p[i]=new baseDMA(et,a);
        else if (x==2)
        {
            cout<<"Wprowadź kolor: ";
            cin.getline(k,20);
            p[i]=new lacksDMA(k,et,a);
        }
        else
        {
            cout<<"Wprowadź styl: ";
            cin.getline(s,20);
            p[i]=new hasDMA(s,et,a);
        }
    }
    cout<<"\nWprowadzone dane:\n\n";
    for (int i=0; i<4; i++)
    {
        p[i]->View();
        cout<<endl;
    }
    for (int i=0; i<4; i++)
    {
        delete p[i];
    }
    cout<<"Gotowe!\n";
    return 0;
}
