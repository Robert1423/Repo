//równania metoda Cramera
#include <iostream>
#include <limits>
#include <vector>
#include <cctype>
#include <algorithm>
#include <math.h>

using namespace std;

void wyswietl_macierz(vector<vector<double>> & v);
void sczytaj_rownanie(string r, vector<vector<double>> & wsp, vector<double> & w); //funkcja skladajaca macierz z rownania
vector<vector<double>> zastap(vector<vector<double>> & wsp, vector<double> & w, int n); //funkcja podmieniajac kolumne w macierzy wspolczynikow na macierz wynikow
double det ( int n, int w, int * WK, vector<vector<double>> & A ); //wyznacznik
bool czy_zero(vector<double> v);

int main()
{
    vector<vector<double>> macierz_wspolczynnikow;
    vector<double> macierz_wolnych;
    vector<double> wyz;
    cout<<"Ile rownan: ";
    int x;
    while (!(cin>>x))
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout<<"Blad!\nIle rownan: ";
    }
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    for (int i=0; i<x; i++)
    {
        cout<<"Wprowadz rownanie: ";
        string rownanie;
        getline(cin,rownanie);
        sczytaj_rownanie(rownanie,macierz_wspolczynnikow,macierz_wolnych);
    }
    cout<<"Macierz wspolczynnikow:\n";
    wyswietl_macierz(macierz_wspolczynnikow);
    int * WK = new int [x];
    for( int i = 0; i < x; i++ )
        WK [ i ] = i;
    double wyzG=det(x,0,WK,macierz_wspolczynnikow);
    delete [] WK;
    cout<<"Wyznacznik: ";
    cout<<" = "<<wyzG<<endl;
    cout<<"\nMacierz wyrazow wolnych:\n";
    for (int i=0; i<macierz_wolnych.size(); i++)
    {
        cout.width(3);
        cout<<macierz_wolnych[i]<<endl;
    }
    for (int i=0; i<macierz_wolnych.size(); i++)
    {
        vector<vector<double>> m=zastap(macierz_wspolczynnikow,macierz_wolnych,i);
        cout<<"\nMacierz z zastapionym wierszem "<<i+1<<":\n";
        wyswietl_macierz(m);
        int * WK = new int [x];
        for( int i = 0; i < x; i++ )
            WK [ i ] = i;
        double d=det(m.size(),0,WK,m);
        delete [] WK;
        cout<<"Wyznacznik: ";
        cout<<" = "<<d<<endl;
        wyz.push_back(d);
    }
    cout<<endl;
    if (wyzG==0)
        if (czy_zero(wyz))
            cout<<"Rownanie nieoznaczone\n";
        else
            cout<<"Rownanie sprzeczne\n";
    else
        for (int i=0; i<x; i++)
            cout<<"x"<<i+1<<" = "<<wyz[i]/wyzG<<endl;
    getchar();
}

void wyswietl_macierz(vector<vector<double>> & v)
{
    for (int i=0; i<v.size(); i++)
    {
        for (int j=0; j<v[i].size(); j++)
        {
            cout.width(3);
            cout<<v[i][j]<<" ";
        }
        cout<<endl;
    }
}

void sczytaj_rownanie(string r, vector<vector<double>> & wsp, vector<double> & w)
{
	//funkcja szczytuje wpisane rownanie i tworzy z nich macierze wspolczynikow i wynikow rownan, ktore posluza do znalezienia rozwiazań
    int i=0;
    string temp; //do zlozenia liczby ze znakow rownania
    double x;
    char z; //znak liczby
    vector<double> row;
    for (char ch : r)
    {
        if (ch=='-')//sprawdzenie jaki liczba ma znak i zapisanie go
            z='-';
        if (ch=='+')
            z='+';
        if (isdigit(ch))
            temp.push_back(ch);//skadanie liczby
        if (!isdigit(ch)&&temp.size()>0) //jezeli nastepny znak nie jest liczba i liczba istnieje wrzuca liczbe do wiersza macierzy
        {
            x=stod(temp); //konwersja liczby z rownania na double
            if (z=='-')
                x=-x; //zmiana znaku jezeli trzeba
            if (temp.size()>0)
                row.push_back(x); //skladanie wiersza
            temp.erase(temp.begin(),temp.end()); //czysczenie temp
        }
        if (ch=='=')
        {
            wsp.push_back(row); //skladanie macierzy wspolczynikow
            break;
        }
        i++;
    }
    z='+';
    temp.erase(temp.begin(),temp.end());
    for (i; i<r.size(); i++) //skladanie macierzy wynikow rownan
    {
        if (r[i]=='-')//zmiana znaku jezeli potrzeba
            z='-';
        if (isdigit(r[i]))
            temp.push_back(r[i]);//skladanie liczby
    }
    x=stod(temp);//konwersja
    if (z=='-')//zmiana znaku jezeli potrzeba
        x=-x;
    w.push_back(x);//skladanie macierzy wynikow
}

vector<vector<double>> zastap(vector<vector<double>> & wsp, vector<double> & w, int n)
{
   vector<vector<double>> m;
   for (int i=0; i<wsp.size(); i++)
   {
       vector<double> row;
       for (int j=0; j<wsp[i].size(); j++)
               row.push_back(wsp[i][j]);
       row[n]=w[i]; //zmiana podanego wyrazu w wierszu na wyraz z macierzy wynikow
       m.push_back(row);
    }
    return m;
}

bool czy_zero(vector<double> v)
{
    for (int i=0; i<v.size(); i++)
        if (v[i]!=0)
            return false;
    return true;
}

double det ( int n, int w, int * WK, vector<vector<double>> & A )
{
  int    i, j, k, m, * KK;
  double s;
  if( n == 1 )                     
    return A [ w ][ WK [ 0 ] ];    
  else
  {
    KK = new int [ n - 1 ];        
    s = 0;                         
    m = 1;                         
    for( i = 0; i < n; i++ )       
    {
      k = 0;                       
      for( j = 0; j < n - 1; j++ ) 
      {
        if( k == i ) k++;          
        KK [ j ] = WK [ k++ ];     
      }
      s += m * A [ w ][ WK [ i ] ] * det ( n - 1, w  + 1, KK, A );
      m = -m;                      
    }
    delete [ ] KK;                 
    return s;                      
  }
}
