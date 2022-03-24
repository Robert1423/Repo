//równania metoda Cramera
#include <iostream>
#include <limits>
#include <vector>
#include <cctype>
#include <algorithm>
#include <math.h>

using namespace std;

void wyswietl_macierz(vector<vector<double>> & v);
void sczytaj_rownanie(string r, vector<vector<double>> & wsp, vector<double> & w);
vector<vector<double>> zastap(vector<vector<double>> & wsp, vector<double> & w, int n);
double det ( int n, int w, int * WK, vector<vector<double>> & A );
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
    int i=0;
    string temp;
    double x;
    char z;
    vector<double> row;
    for (char ch : r)
    {
        if (ch=='-')
            z='-';
        if (ch=='+')
            z='+';
        if (isdigit(ch))
            temp.push_back(ch);
        if (!isdigit(ch)&&temp.size()>0)
        {
            x=stod(temp);
            if (z=='-')
                x=-x;
            if (temp.size()>0)
                row.push_back(x);
            temp.erase(temp.begin(),temp.end());
        }
        if (ch=='=')
        {
            wsp.push_back(row);
            break;
        }
        i++;
    }
    z='+';
    temp.erase(temp.begin(),temp.end());
    for (i; i<r.size(); i++)
    {
        if (r[i]=='-')
            z='-';
        if (isdigit(r[i]))
            temp.push_back(r[i]);
    }
    x=stod(temp);
    if (z=='-')
        x=-x;
    w.push_back(x);
}

vector<vector<double>> zastap(vector<vector<double>> & wsp, vector<double> & w, int n)
{
   vector<vector<double>> m;
   for (int i=0; i<wsp.size(); i++)
   {
       vector<double> row;
       for (int j=0; j<wsp[i].size(); j++)
               row.push_back(wsp[i][j]);
       row[n]=w[i];
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
