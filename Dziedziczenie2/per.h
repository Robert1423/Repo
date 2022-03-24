#ifndef PER_H_
#define PER_H_
#include <string>
class Person
{
private:
    std::string fullname; // imie i nazwisko
protected:
    void Get();
public:
    Person() : fullname("brak") {}
    Person(std::string & n) : fullname(n) {}
    virtual ~Person()=0; //destruktor abstrakcyjnej klasy musi być wirtualny, bo inaczej nastąpi zrzut pamięci
    virtual void Set() =0;
    virtual void Show() const=0;
};
class Gunslinger : virtual public Person
{
private:
    double wyc; // czas wyciagniecia rewolwera
    int nac; //ilosc naciec rewolwera
protected:
    void Get();
    void Data() const;
public:
    Gunslinger() : Person(), wyc(0), nac(0) {}
    Gunslinger(std::string & n, double w, int nc) : Person(n), wyc(w), nac(nc) {}
    ~Gunslinger() {}
    double Draw() {return wyc;}
    void Set();
    void Show() const;
};
class Card
{
private:
    std::string kolor; //kolor karty czarny albo czerwony
    int numerk; //nume rkarty od 1 do 52
public:
    Card();
    ~Card() {}
    void NrC(); //zmiana numeru karty
    virtual void Show() const;
};
class PokerPlayer : virtual public Person
{
private:
    Card karta;
protected:
    void Get();
    void Data() const;
public:
    PokerPlayer() : Person() {}
    PokerPlayer(std::string & n) : Person(n) {}
    ~PokerPlayer() {}
    Card & Draw(); //wyciagniecie karty
    void Show() const;
    void Set();
};
class BadDude : public Gunslinger, public PokerPlayer
{
public:
    BadDude() : Person(), Gunslinger(), PokerPlayer() {}
    BadDude(std::string & n, double w, int nc)
        : Person(n), Gunslinger(n,w,nc), PokerPlayer(n) {}
    void Gdraw(); //wyjecie rewolwera
    void Cdraw(); //wyjecie karty
    void Set();
    void Show() const;
};
#endif
