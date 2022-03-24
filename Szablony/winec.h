#ifndef WINEC_H_
#define WINEC_H_
#include <iostream>
#include <string>
#include <valarray>
template <class T1, class T2>
class Pair
{
    private:
        T1 a;
        T2 b;
    public:
        T1 & first();
        T2 & second();
        T1 first() const { return a; }
        T2 second() const { return b; }
        Pair(const T1 & aval, const T2 & bval) : a(aval), b(bval) {}
        Pair() {}
};

    template<class T1, class T2>
T1 & Pair<T1, T2>::first()
{
    return a;
}
    template<class T1, class T2>
T2 & Pair<T1,T2>::second()
{
    return b;
}
typedef std::valarray<int> ArrayInt;
typedef Pair<ArrayInt,ArrayInt> PairArray;
class Wine : private PairArray, private std::string
{
private:
    int n;
public:
    Wine() : std::string("brak"), PairArray(), n(0) {}
    Wine(const char * l, int y, const int yr[], const int bot[]) : std::string(l), n(y), PairArray(ArrayInt(yr,y),ArrayInt(bot,y)) {} //na liście inicjalizacyjnej obiekt p musi być podany wraz ze specjalizacją, inaczej nie zadziała
    explicit Wine(const char * l, int y) : std::string(l), n(y), PairArray(ArrayInt(y),ArrayInt(y)) {}
    void GetBottles();
    std::string & Label() {return (std::string &)*this;}
    int sum() const; //łączna liczba butelek;
    void Show() const;
};
#endif
