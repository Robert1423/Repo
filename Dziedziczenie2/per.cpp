#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include "per.h"
using std::cout;
using std::cin;
using std::endl;
using std::string;
Person::~Person() {}
void Person::Get()
{
    cout<<"Podaj imię i nazwisko: ";
    getline(cin,fullname);
}
void Person::Set()
{
    Get();
}
void Person::Show() const
{
    cout<<"Imię i nazwisko: "<<fullname<<endl;
}
void Gunslinger::Data() const
{
    cout<<"Czas wyciąganie rewolwera: "<<wyc<<endl;
    cout<<"Ilość nacięć na rewolwerze: "<<nac<<endl;
}
void Gunslinger::Show() const
{
    cout<<"Rewolwerowiec:\n";
    Person::Show();
    Data();
}
void Gunslinger::Get()
{
    cout<<"Podaj czas wyciągania rewolwera (w formacie X.XX): ";
    while (!(cin>>wyc))
    {
        cin.clear();
        while (cin.get()!='\n')
            continue;
        cout<<"Podaj czas wyciągania rewolwera (w formacie X.XX): ";
    }
    cout<<"Podaj liczbę nacięć na rewolwerze: ";
    while (!(cin>>nac))
    {
        cin.clear();
        while (cin.get()!='\n')
            continue;
        cout<<"Podaj liczbę nacięć na rewolwerze: ";
    }
}
void Gunslinger::Set()
{
    Person::Get();
    Get();
}
Card::Card()
{
    std::srand(std::time(0));
    numerk=(std::rand()&52)+1;
    if (numerk%2==0)
        kolor="czerwony";
    else
        kolor="czarny";
}
void Card::NrC()
{
    numerk=(std::rand()%52)+1;
    if (numerk%2==0)
        kolor="czerwony";
    else
        kolor="czarny";
}
void Card::Show() const
{
    cout<<"Karta nr: "<<numerk<<endl;
    cout<<"Kolor karty: "<<kolor<<endl;
}
Card & PokerPlayer::Draw()
{
    Card temp;
    karta=temp;
    return karta;
}
void PokerPlayer::Get()
{
    karta.NrC();
}
void PokerPlayer::Set()
{
    Person::Get();
    Get();
}
void PokerPlayer::Data() const
{
    karta.Show();
}
void PokerPlayer::Show() const
{
    cout<<"Pokerzysta:\n";
    Person::Show();
    Data();
}
void BadDude::Gdraw()
{
    Gunslinger::Draw();
}
void BadDude::Cdraw()
{
    PokerPlayer::Draw();
}
void BadDude::Set()
{
    Person::Get();
    Gunslinger::Get();
    PokerPlayer::Get();
}
void BadDude::Show() const
{
    cout<<"BadDude:\n";
    Person::Show();
    Gunslinger::Data();
    PokerPlayer::Data();
}
