#include <iostream>
#include <vector>
#include <limits>
#include <cstdlib>
#include <math.h>

using namespace std;

void menu();
void pauza();
void stworz_macierz(vector<vector<double>> & v);
void wyswietl_macierz(vector<vector<double>> & v);
void dodaj(vector<vector<double>> v1, vector<vector<double>> v2);
void odejmij(vector<vector<double>> v1, vector<vector<double>> v2);
void skalar(vector<vector<double>> & v);
void mnozenie(vector<vector<double>> v1, vector<vector<double>> v2);
vector<vector<double>> transponuj(vector<vector<double>> v);
vector<vector<double>> tnij(vector<vector<double>> & v,int n, int m);
vector<vector<double>> tnijw(vector<vector<double>> & v,int n);
vector<vector<double>> tnijk(vector<vector<double>> & v,int n);
double det ( int n, int w, int * WK, vector<vector<double>> & A );
double det2(vector<vector<double>> & v);
double det3(vector<vector<double>> & v);
void wyz(vector<vector<double>> & v);
vector<vector<double>> dopelnienie(vector<vector<double>> v);
double reku(vector<vector<double>> v, vector<double> pw);
void odwrotna(vector<vector<double>> v);

int main()
{
    vector<vector<double>> a;
    vector<vector<double>> b;
    menu();
    int x;
    while (!(cin>>x))
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout<<"Blad!\nSpruboj ponownie\n";
        getchar();
        menu();
    }
    while (x!=0)
    {
        switch (x)
        {
            case 1: stworz_macierz(a);
                    stworz_macierz(b);
                    dodaj(a,b);
                    pauza();
                    break;
            case 2: stworz_macierz(a);
                    stworz_macierz(b);
                    odejmij(a,b);
                    pauza();
                    break;
            case 3: stworz_macierz(a);
                    skalar(a);
                    pauza();
                    break;
            case 4: stworz_macierz(a);
                    stworz_macierz(b);
                    mnozenie(a,b);
                    pauza();
                    break;
            case 5: stworz_macierz(a);
                    system("clear");
                    cout<<"Macierz A:\n";
                    wyswietl_macierz(a);
                    b=transponuj(a);
                    cout<<"Macierz transponowana\n";
                    wyswietl_macierz(b);
                    pauza();
                    break;
            case 6: wyz(a);
                    break;
            case 7: stworz_macierz(a);
                    system("clear");
                    if (a.size()==a[0].size())
                    {
                        b=dopelnienie(a);
                        cout<<"Macierz dopelnien\n";
                        wyswietl_macierz(b);
                    }
                    else
                        cout<<"Nie zdefiniowano!\n";
                    pauza();
                    break;
            case 8: stworz_macierz(a);
                    system("clear");
                    if (a.size()==a[0].size())
                        odwrotna(a);
                    else
                        cout<<"Nie zdefiniowano!\n";
                    pauza();
                    break;
            default:
                cout<<"Bledny wybor\n";
        }
        menu();
        while (!(cin>>x))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout<<"Blad!\nSpruboj ponownie\n";
            getchar();
            menu();
        }
    }
    return 0;
}
void menu()
{
    system("clear");
    cout<<"Wybierz:\n";
    cout<<"1 - dodawanie\n2 - odejmowanie\n3 - mnozenie przez liczbe\n";
    cout<<"4 - mnozenie\n5 - transponuj\n6 - wyznacznik\n";
    cout<<"7 - dopelnienie\n8 - odwrotna\n0 - koniec\n";
    cout<<"Wybierz: ";
}

void pauza()
{
    cout<<"<ENTER>\n";
    getchar();
    getchar();
}
void stworz_macierz(vector<vector<double>> & v)
{
    v.erase(v.begin(),v.end());
    int x, y;
    cout<<"Podaj ilość wierszy: ";
    while (!(cin>>x))
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout<<"Blad!\nSpruboj ponownie\nPodaj ilość wierszy: ";
    }
    cout<<"Podaj ilość kolumn: ";
    while (!(cin>>y))
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout<<"Blad!\nSpruboj ponownie\nPodaj ilość kolumn: ";
    }
    for (int i=0; i<x; i++)
    {
        vector<double> temp;
        for (int j=0; j<y; j++)
        {
            cout<<"Wprowadz el "<<i+1<<"x"<<j+1<<": ";
            double t;
            cin>>t;
            temp.push_back(t);
        }
        v.push_back(temp);
    }   
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

void dodaj(vector<vector<double>> v1, vector<vector<double>> v2)
{
    system("clear");
    cout<<"Macierz A\n";
    wyswietl_macierz(v1);
    cout<<"Macierz B\n";
    wyswietl_macierz(v2);
    if (v1.size()==v2.size()&&v1[0].size()==v2[0].size())
    {
        vector<vector<double>> v;
        for (int i=0; i<v1.size(); i++)
        {
            vector<double> temp;
            for (int j=0; j<v1[i].size(); j++)
                temp.push_back(v1[i][j]+v2[i][j]);
            v.push_back(temp);
        }
        cout<<"A+B\n";
        wyswietl_macierz(v);
    }
    else
        cout<<"Nie zdefiniowano!\n";
}

void odejmij(vector<vector<double>> v1, vector<vector<double>> v2)
{
    system("clear");
    cout<<"Macierz A\n";
    wyswietl_macierz(v1);
    cout<<"Macierz B\n";
    wyswietl_macierz(v2);
    if (v1.size()==v2.size()&&v1[0].size()==v2[0].size())
    {
        vector<vector<double>> v;
        for (int i=0; i<v1.size(); i++)
        {
            vector<double> temp;
            for (int j=0; j<v1[i].size(); j++)
                temp.push_back(v1[i][j]-v2[i][j]);
            v.push_back(temp);
        }
        cout<<"A-B\n";
        wyswietl_macierz(v);
    }
    else
        cout<<"Nie zdefiniowano!\n";
}

void skalar(vector<vector<double>> & v)
{
    int x;
    cout<<"Podaj liczbe: ";
    while (!(cin>>x))
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout<<"Blad!\nSpruboj ponownie\nPodaj liczbe: ";
    }
    system("clear");
    cout<<"Macierz A\n";
    wyswietl_macierz(v);
    cout<<"Liczba: "<<x<<endl;
    vector<vector<double>> v1;
    for (int i=0; i<v.size(); i++)
    {
        vector<double> temp;
        for (int j=0; j<v[i].size(); j++)
            temp.push_back(v[i][j]*x);
        v1.push_back(temp);
    }
    cout<<x<<"*A\n";
    wyswietl_macierz(v1);
}

void mnozenie(vector<vector<double>> v1, vector<vector<double>> v2)
{
    system("clear");
    cout<<"Macierz A\n";
    wyswietl_macierz(v1);
    cout<<"Macierz B\n";
    wyswietl_macierz(v2);
    cout<<endl;
    if (v1[0].size()==v2.size())
    {
        vector<vector<double>> v;
        cout<<"Obliczenia:\n";
        for (int i=0; i<v1.size(); i++)
        {
            vector<double> temp;
            for (int k=0; k<v2[0].size(); k++)
            {
                double t=0;
                for (int j=0; j<v2.size(); j++)
                {
                    t+=v1[i][j]*v2[j][k];
                    cout<<v1[i][j]<<"*"<<v2[j][k];
                    if (j==(v2.size()-1))
                        cout<<"=";
                    else
                        cout<<"+";
                }
                cout<<t<<endl<<endl;
                temp.push_back(t);
            }
            v.push_back(temp);
        }
        cout<<"\nAB\n";
        wyswietl_macierz(v);
    }
    else
        cout<<"Nie zdefiniowano\n";
}

vector<vector<double>> transponuj(vector<vector<double>> v)
{
    vector<vector<double>> t;
    for (int i=0; i<v[0].size(); i++)
    {
        vector<double> temp;
        for (int j=0; j<v.size(); j++)
            temp.push_back(v[j][i]);
        t.push_back(temp);
    }
    return t;
}

vector<vector<double>> tnij(vector<vector<double>> & v,int n, int m)
{
    vector<vector<double>> mac;
    for (int i=0; i<v.size(); i++)
    {
        vector<double> row;
        if (n==i)
            continue;
        for (int j=0; j<v[i].size(); j++)
        {
            if (m==j)
                continue;
            row.push_back(v[i][j]);
        }
        mac.push_back(row);
    }
    return mac;
}

vector<vector<double>> tnijw(vector<vector<double>> & v,int n)
{
    vector<vector<double>> mac;
    for (int i=0; i<v.size(); i++)
    {
        vector<double> row;
        if (n==i)
            continue;
        for (int j=0; j<v[i].size(); j++)
        {
            row.push_back(v[i][j]);
        }
        mac.push_back(row);
    }
    return mac;
}

vector<vector<double>> tnijk(vector<vector<double>> & v,int n)
{
    vector<vector<double>> mac;
    for (int i=0; i<v.size(); i++)
    {
        vector<double> row;
        for (int j=0; j<v[0].size(); j++)
        {
            if (n!=j)
                row.push_back(v[i][j]);
        }
        mac.push_back(row);
    }
    return mac;
}

double det ( int n, int w, int * WK, vector<vector<double>> & M )
{
  int    i, j, k, mn, * KK;
  double s;

  if( n == 1 )                     

    return M [ w ][ WK [ 0 ] ];    

  else
  {

    KK = new int [ n - 1 ];        

    s = 0;                         
    mn = 1;                         

    for( i = 0; i < n; i++ )       
    {

      k = 0;                       

      for( j = 0; j < n - 1; j++ ) 
      {
        if( k == i ) k++;          
        KK [ j ] = WK [ k++ ];     
      }
      s += mn * M [ w ][ WK [ i ] ] * det ( n - 1, w  + 1, KK, M );
      mn = -mn;                      

    }

    delete [ ] KK;                 

    return s;                      

  }
}

double det2(vector<vector<double>> & v)
{
    double t;
    t=v[0][0]*v[1][1]-v[0][1]*v[1][0];
    cout<<"("<<v[0][0]<<" * "<<v[1][1]<<") - ("<<v[0][1]<<" * "<<v[1][0]<< ")";
    return t;
}

double det3(vector<vector<double>> & v)
{
    double d=0;
    for (int j=0; j<v[0].size();j++)
    {
        vector<vector<double>> temp;
        double t;
        temp=tnij(v,0,j);
        t=det2(temp);
        cout<<"\n("<<-1<<") ^ ("<<1<<"+"<<j+1<<") * "<<v[0][j]<<" * "<<t;
        d+=(pow(-1,(1+j+1))*v[0][j]*t);
        if (j+1<v[0].size())
            cout<<" + ";
        else
            cout<<" = "<<d<<endl;
    }
    return d;
}

void wyz(vector<vector<double>> & v)
{
    stworz_macierz(v);
    system("clear");
    cout<<"Macierz A:\n";
    wyswietl_macierz(v);
    if (v.size()==v[0].size())
    {
        if (v.size()<=4)
        {
            double d=reku(v,v[0]);
            if (v.size()==2)
                cout<<" = "<<d<<endl;
            cout<<"\nDet(A) = "<<d<<endl;
        }
        else
        {
            int * WK = new int [v.size()];
            for( int i = 0; i < v.size(); i++ )
                WK [ i ] = i;
            cout<<"Det(A) = "<<det(v.size(),0,WK,v)<<endl;
        }
    }
    else
        cout<<"\nNie zdefiniowano!\n";
    pauza();
}

vector<vector<double>> dopelnienie(vector<vector<double>> v)
{
    int * WK = new int [v.size()];
    for( int i = 0; i < v.size(); i++ )
        WK [ i ] = i;
    vector<vector<double>> dop;
    for (int i=0; i<v.size(); i++)
    {
        vector<double> row;
        for (int j=0; j<v[0].size(); j++)
        {
            int m=pow(-1,(i+j+2));
            vector<vector<double>> temp=tnij(v,i,j);
            double d=det(temp.size(),0,WK,temp);
            cout<<"El. "<<i+1<<"x"<<j+1<<" = "<<m<<" * ("<<d;
            row.push_back(m*d);
            cout<<") = "<<row[j]<<endl;
        }
        dop.push_back(row);
    }
    delete [] WK;
    return dop;
}

double reku(vector<vector<double>> v,vector<double> pw)
{
    int mn=1;
    double d=0;
    vector<double> tpw=v[0];
    vector<vector<double>> m=(tnijw(v,0));
    if (v.size()==1&&v[0].size()==1)
    {
        d=v[0][0];
        return d;
    }
    if (v.size()==2&&v[0].size()==2)
    {
        d=det2(v);
        return d;
    }
    if (v.size()==3&&v[0].size()==3)
    {
        d=det3(v);
        return d;
    }
    if (v.size()==3)
    {
        for (int i=0; i<m[0].size(); i++)
        {
            vector<vector<double>> temp=tnijk(v,i);
            cout<<"\nTemp po odcieciu "<<i+1<<" kolumny\n";
            wyswietl_macierz(temp);
            double d3=det3(temp);
            cout<<"\n("<<-1<<") ^ ("<<1<<"+"<<i+1<<") * "<<pw[i]<<" * "<<d3;
            double t;
            t=mn*pw[i]*d3;
            mn=-mn;
            cout<<"="<<t<<endl;
            d+=t;
        }
    }
    else
        //for (int i=0; i<pw.size(); i++)
        //{
            d+=/*mn*pw[i]**/reku(m,tpw);
          //  mn=-mn;
        //}
    return d;
}

void odwrotna(vector<vector<double>> v)
{
    cout<<"Macierz A\n";
    wyswietl_macierz(v);
    int * WK = new int [v.size()];
    for( int i = 0; i < v.size(); i++ )
        WK [ i ] = i;
    double x=(1/det(v.size(),0,WK,v));
    cout<<"Wyznacznik: "<<det(v.size(),0,WK,v)<<endl;
    cout<<"\nDopelnienia\n";
    vector<vector<double>> tv=transponuj(dopelnienie(v));
    cout<<"\nADT\n";
    wyswietl_macierz(tv);
    vector<vector<double>> odw;
    for (int i=0; i<tv.size(); i++)
    {
        vector<double> temp;
        for (int j=0; j<tv[i].size(); j++)
            temp.push_back(tv[i][j]*x);
        odw.push_back(temp);
    }
    cout<<"Macierz odwrotna do A:\n";
    wyswietl_macierz(odw);
    delete [] WK;
}
