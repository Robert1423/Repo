#include <iostream>
#include <cstring>
#include "per.h"
const int SIZE = 5;
using std::cin;
using std::cout;
using std::endl;
using std::strchr;
int main()
{
    Person * lolas[SIZE];
    int ct=0;
    for (ct = 0; ct < SIZE; ct++)
    {
        char choice;
        cout<<"Podaj kategorię:\n";
        cout<<"r: rewolwerowiec; p: pokerzysta; "
            <<"z: BadDude; w: wyjście\n";
        cin>>choice;
        while (strchr("rpzw", choice) == NULL)
        {
            cout << "Wpisz r, p, z lub w: ";
            cin >> choice;
        }
        if (choice == 'w')
            break;
        switch(choice)
        {
            case 'r' :  lolas[ct]=new Gunslinger;
                        break;
            case 'p' :  lolas[ct]=new PokerPlayer;
                        break;
            case 'z' :  lolas[ct]=new BadDude;
                        break;
        }
        cin.get();
        lolas[ct]->Set();
    }
    cout<<"Lista:\n";
    for (int i = 0; i < ct; i++)
    {
        cout << endl;
        cout<<i+1<<"#:\n";
        lolas[i]->Show();
    }
    for (int i = 0; i < ct; i++)
        delete lolas[i];
    cout << "Koniec.\n";
    return 0;
}

