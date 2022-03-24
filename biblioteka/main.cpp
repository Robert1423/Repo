#include "bib.h"

using namespace std;

string czyt="baza_cz.txt";
string ksia="baza_k.txt";

template<typename V, typename C, typename S>
void z_pliku(V & v, C & c, S & s)
{
    v.erase(v.begin(),v.end());
    char ch;
    ifstream plik;
    plik.open(s.c_str());
    if (plik.good())
    {
        while (!plik.eof())
        {
            C t;
            ch=plik.peek();
            if (ch=plik.eof()||ch=='\n')
                break;
            plik>>t;
            v.push_back(t);
        }
    }
    else
        cout<<"Blad!\nNie udalo sie otworzyc pliku: "<<s.c_str()<<"!\n";
    plik.close();
}
template<typename V>
void wyswietl(const V & v)
{
    for (auto i : v)
        cout<<i;
}
template<typename V, typename S>
void zapis_do_pliku(V & v, S & s)
{
    ofstream plik;
    plik.open(s.c_str());
    if (plik.good())
    {
        for (auto i : v)
            plik<<i;
    }
    else
        cout<<"Blad!\nNie udalo sie otworzyc pliku: "<<s.c_str()<<"!\n";
    plik.close();
}
template<typename V, typename C>
void nowy(V & v, C & c)
{
    c.fill();
    int i=1;
    for (auto x : v)
        ++i;
    c.set_id(i);
    v.push_back(c);
}
 
void menu();
void pauza();
void wczytaj_pliki(vector<czytelnik>& c, vector<ksiazka> & k);
void wprowadz(int & x, string & n);
void baza(vector<czytelnik> & v);
void baza(vector<ksiazka> & v);
void dodaj(vector<czytelnik> & v);
void dodaj(vector<ksiazka> & v);
void wypozycz(vector<czytelnik>& c, vector<ksiazka> & k);
void zwroc(vector<czytelnik>& c, vector<ksiazka> & k);
void sp_dos(vector<ksiazka> & k);
void zapisz(vector<czytelnik>& c, vector<ksiazka> & k);
void termin(vector<czytelnik>& c);
void kara(vector<czytelnik> & c);
time_t dodaty(time_t czas, int x) { return czas+x*86400;};

int main()
{
    int x;
    vector<ksiazka> k;
    vector<czytelnik> u;
    wczytaj_pliki(u,k);
    menu();
    while (!(cin>>x))
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout<<"Blad!\nSpruboj ponownie\n<ENTER, aby kontynuowac>\n";
        getchar();
        menu();
    }
    while (x!=0)
    {
        switch (x)
        {
            case 1: baza(u);
                    break;
            case 2: baza(k);
                    break;
            case 3: dodaj(u);
                    break;
            case 4: dodaj(k);
                    break;
            case 5: wypozycz(u,k);
                    break;
            case 6: zwroc(u,k);
                    break;
            case 7: sp_dos(k);
                    break;
            case 8: termin(u);
                    break;
            case 9: kara(u);
                    break;
            default: cout<<"Błąd!\nSpruboj ponownie\n";
                    pauza();
                    break;
        }
        menu();
        while (!(cin>>x))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout<<"Blad!\nSpruboj ponownie\n<ENTER, aby kontynuowac>\n";
            getchar();
            menu();
        }
    }
    zapisz(u,k);
    return 0;
}

void menu()
{
    system("clear");
    cout<<"Co chcesz zrobic?\n";
    cout.width(10);
    cout<<left<<"1 - wyswietl baze czytelnikow\t";
    cout.width(10);
    cout<<left<<"2 - wyswietl baze ksiazek\n";
    cout.width(10);
    cout<<left<<"3 - dodaj nowego czytelnika\t";
    cout.width(10);
    cout<<left<<"4 - dodaj ksiazki do bazy\n";
    cout.width(20);
    cout<<left<<"5 - wypozycz ksiazke\t\t";
    cout.width(10);
    cout<<left<<"6 - zwroc ksiazke\n";
    cout.width(20);
    cout<<left<<"7 - sprawdz dostepnosc\t\t";
    cout.width(10);
    cout<<left<<"8 - pokaz termin zwrotu\n";
    cout.width(20);
    cout<<left<<"9 -  pokaz naleznosc\n";
    cout<<left<<"0 - koniec\n";
    cout<<"Wybierz: ";
}

void pauza()
{
    cout<<"<ENTER, aby kontynuowac>";
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getchar();
}

void wczytaj_pliki(vector<czytelnik>& c, vector<ksiazka> & k)
{
    czytelnik tempc;
    z_pliku(c,tempc,czyt);
    ksiazka tempk;
    z_pliku(k,tempk,ksia);
    
}
void wprowadz(int & x, string & n)
{
    cout<<"Podaj ID czytelnika: ";
    while (!(cin>>x))
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout<<"Blad!\nSpruboj ponownie\nPodaj ID czytelnika: ";
    }
    cout<<"Wpisz tytul ksiazki:\n";
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin,n);
}

void baza(vector<czytelnik> & v)
{
    system("clear");
    if (v.size()!=0)
    {
        cout.width(5);
        cout<<"ID"<<'\t';
        cout.width(20);
        cout<<"Nazwisko"<<'\t';
        cout.width(30);
        cout<<"Wypozyczone"<<'\t';
        cout.width(5);
        cout<<"Data wyp.\n";
        wyswietl(v);
    }
    pauza();
}

void baza(vector<ksiazka> & v)
{
    system("clear");
    if (v.size()!=0)
    {
        cout.width(5);
        cout<<"ID";
        cout.width(20);
        cout<<"Autor\t";
        cout.width(30);
        cout<<"Tytul\t";
        cout.width(5);
        cout<<"Ilosc\n";
        wyswietl(v);
    }
    pauza();
}

void dodaj(vector<czytelnik> & v)
{
    system("clear");
    czytelnik c;
    nowy(v,c);
    zapis_do_pliku(v,czyt);
    pauza();
}

void dodaj(vector<ksiazka> & v)
{
    system("clear");
    ksiazka c;
    nowy(v,c);
    zapis_do_pliku(v,ksia);
    pauza();
}

void wypozycz(vector<czytelnik>& c, vector<ksiazka> & k)
{
    system("clear");
    int x;
    string n;
    wprowadz(x,n);
    int a=0;
    for (int j=0; j<c.size(); j++)
    {
        if (x==c[j].show_id())
        {
            a=1;
            for (int i=0; i<k.size(); i++)
            {
                if (n==k[i].tyt())
                {
                    a=2;
                    if (k[i].dostepnosc())
                    {
                        if (!c[j].wypozycz(n))
                            cout<<"Nie można wypozyczyc!\n";
                        else
                        {
                            k[i].wypozycz();
                            zapisz(c,k);
                        }
                        break;
                    }
                    else
                    {
                        cout<<"Brak ksiazki na stanie!\n";
                        break;
                    }
                }
            }
            break;
        }
    }
    if (a==0)
        cout<<"Blad!\nBrak uzytkownika w bazie!\n";
    if (a==1)
        cout<<"Brak ksiazki w bazie!\n";
    pauza();
}

void zwroc(vector<czytelnik>& c, vector<ksiazka> & k)
{
    system("clear");
    int x;
    string n;
    wprowadz(x,n);
    int f=0;
    for (int j=0; j<c.size(); j++)
    {
        if (x==c[j].show_id())
        {
            for (int i=0; i<k.size(); i++)
            {
                if (n!=k[i].tyt())
                    f=1;
                else
                {
                    c[j].zwroc(n);
                    k[i].zwroc();
                    zapisz(c,k);
                    f=2;
                    break;
                }
            }
            break;
        }
    }
    if (f==0)
        cout<<"Blad!\nBrak uzytkownika w bazie!\n";
    if (f==1)
        cout<<"Błąd!\nBrak ksiazki w bazie!\n";
    pauza();
}

void sp_dos(vector<ksiazka> & k)
{
    system("clear");
    string b;
    cout<<"Wpisz tytul ksiazki:\n";
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin,b);
    int i=0;
    int a=0;
    for (i; i<k.size(); i++)
        if (b==k[i].tyt())
        {
            if (k[i].dostepnosc())
                cout<<"Obecnie na stanie: "<<k[i].ile()<<endl;
            else
                cout<<"Brak!\n";
            a++;
            break;
        }
    if (a==0)
        cout<<"Brak ksiazki w bazie!\n";
    pauza();
}

void zapisz(vector<czytelnik>& c, vector<ksiazka> & k)
{
    zapis_do_pliku(c,czyt);
    zapis_do_pliku(k,ksia);
}

void termin(vector<czytelnik> & c)
{
    system("clear");
    string b;
    int x;
    wprowadz(x,b);
    transform(b.begin(), b.end(), b.begin(), [](unsigned char c){ return toupper(c); });
    int f=0;
    for (int j=0; j<c.size(); j++)
    {
        if (x==c[j].show_id())
        {
            vector<string> temp=c[j].wypo();
            int n=0;
            for (auto s : temp)
            {
                if (b==s)
                {
                    f++;
                    time_t t1;
                    time(&t1);
                    tm * d2=localtime(&t1);
                    d2->tm_mday=c[j].daty()[n]->tm_mday;
                    d2->tm_mon=c[j].daty()[n]->tm_mon;
                    d2->tm_year=c[j].daty()[n]->tm_year;
                    t1=mktime(d2);
                    time_t t2=dodaty(mktime(d2),14);
                    d2=localtime(&t2);
                    cout<<"Termin zwrotu to: ";
                    cout<<d2->tm_mday<<"-"<<d2->tm_mon+1<<"-"<<d2->tm_year+1900<<endl;
                    d2=localtime(&t1);
                    break;
                }
                n++;
            }
            break;
        }
    }
    if (f==0)
        cout<<"Blad!\n";
    pauza();
}

void kara(vector<czytelnik> & c)
{
    system("clear");
    int x;
    cout<<"Podaj ID czytelnika: ";
    while (!(cin>>x))
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout<<"Blad!\nSpruboj ponownie\nPodaj ID czytelnika: ";
    }
    int f=0;
    for (int j=0; j<c.size(); j++)
    {
        if (x==c[j].show_id())
        {
            if (c[j].sprawdz_kare())
                cout<<"Kara oplacona\n";
            f=1;
            break;
        }
    }
    if (f==0)
        cout<<"Blad!\nNie znaloziono ID\n";
    pauza();
}
