#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <time.h>
#include <limits>
#include <algorithm>
#include <cctype>
#include <cstdlib>

const int mn=5;
const int zwrot=14;

class czytelnik
{
private:
    std::string name;
    int id;
    std::vector<std::string> ksiazka;
    int kara;
    int oplacono;
    std::vector<tm *> data_wyp;
public:
    czytelnik();
    czytelnik(std::string n, int i=0, std::string b="brak", int k=0, int o=0, time_t t=0);
    ~czytelnik() {};
    void fill();
    void set_id(int n);
    int show_id() {return id;}
    int zw() {return zwrot;}
    int show_kara() {return kara;}
    std::vector<tm *> daty() {return data_wyp;}
    std::vector<std::string> wypo() {return ksiazka;}
    void kara_oblicz(int x);
    void oplac(int x);
    bool sprawdz_kare();
    bool wypozycz(std::string b);
    void zwroc(std::string b);
    void lista();
    const tm* operator[](int i){return data_wyp[i];}
    friend std::ostream & operator<<(std::ostream & os, const czytelnik & c);
    friend std::istream & operator>>(std::istream & fs, czytelnik & c);
};

class ksiazka
{
private:
    std::string autor;
    std::string tytul;
	int ilosc;
	int id;
public:
    ksiazka();
    ksiazka(std::string a, std::string t="brak", int n=0, int i=0);
    ~ksiazka() {};
    void fill();
    void set_id(int n);
    std::string tyt() {return tytul;};
    int ile() {return ilosc;}
	void wypozycz();
    void zwroc();
    bool dostepnosc();
    friend std::ostream & operator<<(std::ostream & os, const ksiazka & c);
    friend std::istream & operator>>(std::istream & fs, ksiazka & c);
};

int ile_dni(time_t t1, time_t t2);
