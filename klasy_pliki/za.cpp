//trzeba dokończyć, wczytywanie z pliku do tablicy
#include "emp.h"
#include <cstdlib>
#include <limits>
#include <cctype>
using namespace std;
const int MAX=10;
void Menu();
bool SprawdzPlik(const char * filename, int & pos, int & z);
int main(int argc, char * argv[])
{
    if (argc==1)
    {
        cerr<<"Błąd krytyczny! Blędne uruchomienie programu!\n";
        cerr<<"Składnia: "<<argv[9]<<" plik[i]\n";
        cerr<<"Nastąpi zakończenie programu!\n";
        exit(EXIT_FAILURE);
    }
    abstr_emp * pc[MAX];
    for (int file=1; file<argc; file++)
    {
    char ch;
    int p=0;
    int iz=0;
    int m=MAX;
    if (!SprawdzPlik(argv[file],p,iz))
    {
        cout<<"Utworzono plik "<<argv[file]<<", wprowadź dane:\n";
        cout<<"Można wprowadzić "<<m<<" pozycji\n";
        ofstream fout(argv[file]);
        for (int i=0; i<MAX; i++)
            fout<<"  ";
        fout<<endl;
    }
    else
    {
        m=m-iz;
        if (m>0)
            cout<<"\nZostało miejsca na "<<m<<" pozycji:\n";
        cout<<"\nCzy chcesz wprowadzić nowe dane? <y/n> ";
        cin>>ch;
        while (ch!='y'&&ch!='Y'&&ch!='n'&&ch!='N')
        {
            cout<<"Błędny wybór! Spróbuj jeszcze raz: <y/n> ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin>>ch;
        }
        cin.get();
    }
    if (ch=='n'||ch=='N')
    {
        cout<<"Koniec\n";
        exit(EXIT_FAILURE);
    }
    int count=0;
    fstream fio(argv[file],ios_base::in|ios_base::out);
    if (!fio.is_open())
    {
        cerr<<"Nie udało się otworzyć pliku\n";
        exit(EXIT_FAILURE);
    }
    int x;
    fio.seekp(p);
    if (m==0)
        cout<<"\nBrak miejsca na nowe dane:\n";
    else
    {
        for (int i=0; i<m; i++)
        {
            Menu();
            (cin>>x).get();
            if (x<1||x>4)
            {
                break;
            }
            else
            {
                switch (x)
                {
                    case Employee : pc[i] = new employee;
                                    pc[i]->SetAll();
                                    fio<<Employee<<" ";
                                    break;
                    case Manager  : pc[i] = new manager;
                                    pc[i]->SetAll();
                                    fio<<Manager<<" ";
                                    break;
                    case Fink     : pc[i] = new fink;
                                    pc[i]->SetAll();
                                    fio<<Fink<<" ";
                                    break;
                    case Highfink : pc[i] = new highfink;
                                    pc[i]->SetAll();
                                    fio<<Highfink<<" ";
                                    break;
                }
            }
            count++;
        }
    }
    fio.close();
    ofstream fout(argv[file],ios_base::out|ios_base::app);
    if (!fout.is_open())
    {
        cerr<<"Nie udało się otworzyć pliku\n";
        exit(EXIT_FAILURE);
    }
    for (int i=0; i<count; i++)
    {
        pc[i]->writeall(fout);
        delete pc[i];
    }
    fout.close();
    ifstream fin(argv[file]);
    if (!fin.is_open())
    {
        cerr<<"Nie udało się otworzyć pliku\n";
        exit(EXIT_FAILURE);
    }
    int classtype;
    count=0;
    x=0;
    while ((fin>>classtype).get(ch))
    {
        switch (classtype)
        {
            case Employee : pc[x] = new employee;
                            break;
            case Manager  : pc[x] = new manager;
                            break;
            case Fink     : pc[x] = new fink;
                            break;
            case Highfink : pc[x] = new highfink;
                            break;
        }
        x++;
        count++;
        if (ch=='\n')
            break;
    }
    fin.close();
    fin.open(argv[file]);
    string temp;
    getline(fin,temp);
    for (int i=0; i<count; i++)
        pc[i]->getall(fin);
    cout<<"\n<ENTER> by kontynować\n";
    cin.get();
    cout<<"Dame wczytane z pliku do tablicy:\n";
    for (int i=0; i<count; i++)
    {
        pc[i]->ShowAll();
        cout<<endl;
    }    
    }
    cout<<"Koniec\n";
    return 0;
}
void Menu()
{
    cout<<"Wybierz stanowisko:\n";
    cout<<"\t1 - Pracownik\n";
    cout<<"\t2 - Manager\n";
    cout<<"\t3 - Donosiciel\n";
    cout<<"\t4 - Główny Donosiciel\n";
    cout<<"Błedny wybór, spowoduje zakończenie wprowadzania\n";
}
bool SprawdzPlik(const char * filename, int & pos, int & z)
{
    ifstream fin(filename);
    char ch;
    if (fin.is_open())
    {
        cout<<"Aktualna zawartość pliku:\n";
        while (fin.get(ch))
        {
            cout<<ch;
            if (ch=='\n')
            {
                break;
            }
            if (isdigit(ch))
            {
                pos=fin.tellg();
                z++;
            }
        }
        while (fin.get(ch))
            cout<<ch;
        fin.close();
        pos++;
        return true;
    }
    else
        return false;
}
