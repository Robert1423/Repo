#include "bib.h"

using namespace std;

czytelnik::czytelnik() 
{
    name="brak";
    id=0;
    ksiazka.push_back("brak");
    kara=0;
    oplacono=0;
}

czytelnik::czytelnik(string n, int i, string b, int k, int o, time_t t)
{
    name=n;
    id=i;
    ksiazka.push_back(b);
    kara=k;
    oplacono=o;
    data_wyp.push_back(localtime(&t));
}

void czytelnik::fill()
{
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout<<"Wprowadź imię i nazwisko: ";
    getline(cin,name);
}

void czytelnik::set_id(int n)
{
    id=n;
}

void czytelnik::kara_oblicz(int x)
{
    cout<<"Zliczanie!\n";
    kara=0;
    time_t t;
    time(&t);
    for (auto i : data_wyp)
    {
        tm * d=localtime(&t);
        d->tm_mday=i->tm_mday;
        d->tm_mon=i->tm_mon;
        d->tm_year=i->tm_year;
        int n=ile_dni(t,mktime(d));
        if (n > zwrot)
            kara+=x*(n-zwrot);
    }
    kara-=oplacono;
}

void czytelnik::oplac(int x)
{
    if (x>kara)
    {
        cout<<"Kara wynosi: "<<kara<<".\nWpłacona kwota przekracza karę\nReszta wynosi: ";
        cout<<x-kara<<endl;
        oplacono+=x-(x-kara);
        kara-=x-(x-kara);
    }
    else
    {
        kara-=x;
        oplacono+=x;
    }
}

bool czytelnik::sprawdz_kare()
{
    if (kara==0)
    {
        oplacono=0;
        return true;
    }
    else
    {
        cout<<"Kara wynosi "<<kara<<" zl\n";
        char ch;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout<<"Czy chcesz oplacic kare?: <t, n>";
        while (cin.get(ch))
        {
            if (ch=='t'||ch=='T'||ch=='n'||ch=='N')
                break;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout<<"Bład! Jeszcze raz: \nCzy chcesz oplacic kare?: <t, n>";
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (ch=='t'||ch=='T')
        {
            cout<<"Ile chcesz wpłacić? :";
            int a;
            while (!(cin>>a))
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout<<"Błąd!\nIle chcesz wpłacić? :";
            }
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            oplac(a);
            if (kara==0)
            {
                oplacono=0;
                return true;
            }
            else
                return false;
        }
        if (ch=='n'||ch=='N')
            return false;
    }
    return false;
}
        
bool czytelnik::wypozycz(string b)
{
    time_t t;
    time(&t);
    if (sprawdz_kare())
    {
        if (ksiazka[0]=="brak")
            ksiazka.pop_back();
        transform(b.begin(), b.end(), b.begin(), [](unsigned char c){ return toupper(c); });
        ksiazka.push_back(b);
        if (ksiazka.size()==1)
            data_wyp.erase(data_wyp.begin(),data_wyp.end());
        data_wyp.push_back(localtime(&t));
        return true;
    }
    else
        cout<<"Nie mozna wypozyczyc! Zbyt wysoka kara!\n";
    return false;
}

void czytelnik::zwroc(string b)
{
    transform(b.begin(), b.end(), b.begin(), [](unsigned char c){ return toupper(c); });
    for (int i=0; i<ksiazka.size(); i++)
    {
        if (b==ksiazka[i])
        {
            if (sprawdz_kare())
            {
                ksiazka.erase(ksiazka.begin()+i);
                data_wyp.erase(data_wyp.begin()+i);
                cout<<"Książka \""<<b<<"\" została zwrócona\n";
                break;
            }
            else
                cout<<"Błąd!\nOpłać karę!\n";
        }
    }
}

void czytelnik::lista()
{
    if (ksiazka.size()==0)
        cout<<"BRAK!\n";
    else
        for (auto i : ksiazka)
            cout<<i<<endl;
}
ostream& operator<<(ostream & os, const czytelnik & c)
{
    os.width(5);
    os<<left<<c.id<<"\t";
    os.width(20);
    os<<right<<c.name<<"\t";
    os.width(30);
    if (c.ksiazka.size()>0)
    {
        if (c.ksiazka[0]=="brak")
        {
            os<<right<<"\nKARA:\t";
            os<<left<<c.kara<<"\tOPŁACONO="<<c.oplacono<<endl; 
        }
        else
        {
        os<<left<<c.ksiazka[0]<<"\t";
        os.width(5);
        os<<right<<c.data_wyp[0]->tm_mday<<"-"<<c.data_wyp[0]->tm_mon+1<<"-"<<c.data_wyp[0]->tm_year+1900<<"\n";
        if (c.ksiazka.size()>1)
            for (int i=1; i<c.ksiazka.size(); i++)
            {
                os.width(5);
                os<<left<<"-";
                os.width(20);
                os<<right<<"\t";
                os.width(30);
                os<<left<<c.ksiazka[i]<<"\t";
                os.width(5);
                os<<right<<c.data_wyp[i]->tm_mday<<"-"<<c.data_wyp[i]->tm_mon+1<<"-"<<c.data_wyp[i]->tm_year+1900<<"\n";
            }
        os<<"KARA:\t";
        os<<left<<c.kara<<"\tOPŁACONO="<<c.oplacono<<endl;
        }
    }
    else
    {
        os<<right<<"\nKARA:\t";
        os<<left<<c.kara<<"\tOPŁACONO="<<c.oplacono<<endl;
    }
    return os;
}

istream & operator>>(istream & fs, czytelnik & c)
{
    string l;
    int i=0;
    int d[3];
    char ch;
    while (ch=fs.peek())
    {
        if (isdigit(ch))
        {
            fs>>c.id;
            getline(fs,l,'\t');
            getline(fs,c.name,'\t');
            ch=fs.peek();
            if (!isspace(ch))
            {
                getline(fs,l,'\t');
                for (int i=0; i<l.size(); i++)
                {
                    if (l[i]==' '&&l[i+1]==' ')
                        l.erase(l.begin()+i,l.end());
                }
                c.ksiazka[0]=l;
                while (ch!='\n')
                {
                    ch=fs.peek();
                    if (isdigit(ch))
                    {
                        fs>>d[i];
                        i++;
                    }
                    else
                        fs.get(ch);
                }
                tm * temp = new tm;
                temp->tm_mday=d[0];
                temp->tm_mon=d[1]-1;
                temp->tm_year=d[2]-1900;
                c.data_wyp.erase(c.data_wyp.begin(),c.data_wyp.end());
                c.data_wyp.push_back(temp);
                fs.get(ch);
            }
            else 
            {
                getline(fs,l);
                break;
            }
        }
        if (ch=='-')
        {
            while (ch!='K')
            {
                getline(fs,l,'\t');
                getline(fs,l,'\t');
                for (int i=0; i<l.size(); i++)
                {
                    if (l[i]==' '&&l[i+1]==' ')
                        l.erase(l.begin()+i,l.end());
                }
                c.ksiazka.push_back(l);
                i=0;
                while (ch!='\n')
                {
                    ch=fs.peek();
                    if (isdigit(ch))
                    {
                        fs>>d[i];
                        i++;
                    }
                    else
                        fs.get(ch);
                }
                tm * temp = new tm;
                temp->tm_mday=d[0];
                temp->tm_mon=d[1]-1;
                temp->tm_year=d[2]-1900;
                c.data_wyp.push_back(temp);
                fs.get(ch);
            }
        }
        else break;
    }
    getline(fs,l,'=');
    fs>>c.oplacono;
    fs.get();
    c.kara_oblicz(mn);
    if (c.kara==0)
        c.oplacono=0;
    return fs;
}

ksiazka::ksiazka()
{}

ksiazka::ksiazka(string a,string t, int n, int i)
{
    autor=a;
    tytul=t;
    ilosc=n;
    id=i;
}

void ksiazka::fill()
{
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout<<"Podaj autora: ";
    getline(cin,autor);
    cout<<"Podaj tytul: ";
    getline(cin,tytul);
    cout<<"Podaj ilosc: ";
    while (!(cin>>ilosc))
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout<<"Blad!\nPodaj ilosc: ";
    }
}

void ksiazka::set_id(int n)
{
    id=1000+n;
}

void ksiazka::wypozycz()
{
    if (dostepnosc())
        ilosc--;
    else
        cout<<"Brak ksiazki na stanie!\n";
}

void ksiazka::zwroc()
{
    ilosc++;
}

bool ksiazka::dostepnosc()
{
    if (ilosc>0)
        return true;
    else
        return false;
}

ostream & operator<<(ostream & os, const ksiazka & c)
{
    os.width(5);
    os<<left<<c.id<<"\t";
    os.width(20);
    os<<right<<c.autor<<"\t";
    os.width(30);
    os<<c.tytul<<"\t";
    os.width(5);
    os<<c.ilosc<<"\n";
    return os;
}

istream & operator>>(istream & fs, ksiazka & c)
{
    string l;
    fs>>c.id;
    getline(fs,l,'\t');
    getline(fs,c.autor,'\t');
    getline(fs,c.tytul,'\t');
    int i=0;
    while (isspace(c.tytul[i]))
        i++;
    c.tytul.erase(c.tytul.begin(),c.tytul.begin()+i);
    fs>>c.ilosc;
    getline(fs,l);
    return fs;
}

int ile_dni(time_t t1, time_t t2) {return (t1-t2)/86400;}
