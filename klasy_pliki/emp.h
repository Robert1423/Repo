#ifndef EMP_H_
#define EMP_H_
#include <iostream>
#include <string>
#include <fstream>
enum classkind{Employee=1,Manager,Fink,Highfink};
class abstr_emp
{
private:
    std::string fname; //imię
    std::string lname; //nazwisko
    std::string job; //zawód
public:
    abstr_emp();
    abstr_emp(const std::string & fn, const std::string & ln, const std::string & j);
    virtual void ShowAll() const; //opisuje i wyświetla dane
    virtual void SetAll(); //ustawia dane
    virtual void writeall(std::ofstream & fo); //zapisuje dane do pliku podanego jako argument
    friend std::ostream & operator<<(std::ostream & os, const abstr_emp & e);
    //wyświetla tylko imię i nazwisko
    virtual void getall(std::ifstream & fo);
    virtual ~abstr_emp()=0;//abstrakcyjna klasa bazowa
};
class employee : public abstr_emp
{
public:
    employee();
    employee(const std::string & fn, const std::string & ln, const std::string & j);
    virtual void ShowAll() const;
    virtual void SetAll();
    virtual void writeall(std::ofstream & fo);
    virtual void getall(std::ifstream & fo);
};
class manager : virtual public abstr_emp
{
private:
    int inchargeof; //liczba obiektów abstr_emp, którymi zarządza
protected:
    int InChargeOf() const {return inchargeof;} //wyjście
    int & InChargeOf() {return inchargeof;} //wejście
public:
    manager();
    manager(const std::string & fn, const std::string & ln,
            const std::string & j, int ico=0);
    manager(const abstr_emp & e, int ico);
    manager(const manager & m);
    virtual void ShowAll() const;
    virtual void SetAll();
    virtual void writeall(std::ofstream & fo);
    virtual void getall(std::ifstream & fo);
};
class fink : virtual public abstr_emp
{
private:
    std::string reportsto; //do kogo fink (donosiciel) przesyłą raport
protected:
    const std::string ReportsTo() const {return reportsto;}
    std::string & ReportsTo() {return reportsto;}
public:
    fink();
    fink(const std::string & fn, const std::string & ln,
         const std::string & j, const std::string & rpo);
    fink(const abstr_emp & e, const std::string & rpo);
    fink(const fink & e);
    virtual void ShowAll() const;
    virtual void SetAll();
    virtual void writeall(std::ofstream & fo);
    virtual void getall(std::ifstream & fo);
};
class highfink : public manager, public fink //główny donosiciel
{
public:
    highfink();
    highfink(const std::string & fn, const std::string & ln,
             const std::string & j, const std::string & rpo,
             int ico);
    highfink(const abstr_emp & e, const std::string & rpo, int ico);
    highfink(const fink & e, int ico);
    highfink(const manager & m, const std::string & rpo);
    highfink(const highfink & h);
    virtual void ShowAll() const;
    virtual void SetAll();
    virtual void writeall(std::ofstream & fo);
    virtual void getall(std::ifstream & fo);
};
#endif
