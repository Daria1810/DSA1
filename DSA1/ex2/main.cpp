#include <iostream>
#include <fstream>
#include <queue>
#include <cmath>

using namespace std;

int T, N;

int main()
{

    ///minutele se citesc mereu cu 2 zecimale iar durata se citeste in minute
    /// a)
    struct Order
    {
        float t;
        int d;
        int hour;
        float minutes;
        int time;

    } a[50];

    queue <Order> r;
    queue <int> aux;

    ///citirea din fisier

    ifstream fin ("order.txt");

    fin>>N>>T;

    ///separare ore si minute + conversie in minute

    for(int i =1; i<=N; i++)
    {
        fin>>a[i].t>>a[i].d;
        a[i].hour = floor(a[i].t);
        a[i].minutes = fmod(a[i].t, 1.0)*100 + 0.5;
        a[i].time=a[i].hour*60 + a[i].minutes;
    }


    ///sortarea crescatoare dupa timpul de sosire

    for (int i = 1; i < N; i++)
        for (int j = i; j <= N; j++)
            if(a[i].t>a[j].t)
                swap(a[i],a[j]);

    ///initial, in lista avem timpurile in care s-ar fi terminat comenzile, daca nu erau decalaje
    cout<<"d)"<<endl;
    cout<<"The expected completion times are ";
    for (int i = 1; i <= N; i++)
    {
        cout<<(a[i].time+a[i].d)/60<<":";
        if((a[i].time+a[i].d)%60!=0)
            cout<<(a[i].time+a[i].d)%60<<" ";
        else cout<<"00 ";

    }
    cout<<endl;
    ///update pt timpul de INCEPERE
    for(int i=1; i<=N; i++)
        if(a[i].time+a[i].d>=a[i+1].time)
            a[i+1].time=a[i].time + a[i].d;


    ///afisarea timpului de finalizare

    cout<<"The actual completion times are ";
    for (int i = 1; a[i].time<T*60; i++)
    {
        cout<<(a[i].time+a[i].d)/60<<":";
        if((a[i].time+a[i].d)%60!=0)
            cout<<(a[i].time+a[i].d)%60<<" ";
        else cout<<"00 ";

    }

    cout<<endl;
    cout<<endl;

    ///b), este folosita coada r care se comporta ca o coada normala de la un restaurant
    ///(lumea vine, comanda si pleaca atunci cand comanda este gata) si se compara timpul
    ///in care e se termina comanda curenta si incepe comanda urmatoare si perioada respectiva e
    /// perioada in care bucatarul ia pauza
    cout<<"b)"<<endl;
    Order *crt;
    Order *nxt;
    r.push(a[1]);
    int dmax=0;
    for (int i = 2; i <=N; i++)
    {
         r.push(a[i]);
        crt = &r.front();
        nxt = &r.front()+1;

        if(nxt->time > crt->time + crt->d)
        {
            cout<<"The chef is free from "<<(crt->time+crt->d)/60<<":";
            if((crt->time+crt->d)%60!=0)
                cout<<(crt->time+crt->d)%60;
            else cout<<"00";

            cout<<" to "<<nxt->time/60<<":";
            if((nxt->time)%60!=0)
                cout<<(nxt->time)%60;
            else cout<<"00";
            cout<<endl;
            r.pop();
        }

        if(crt->time + crt->d == nxt->time)
        {
            r.pop();
            r.pop();
            r.push(*nxt);
        }

        if(nxt->d>dmax)
            dmax=nxt->d;
    }

    ///test care verifica faptul ca in coada ramane mereu ULTIMA COMANDA
    /*while(!r.empty())
    {
        cout << r.front().time + r.front().d << " ";
        r.pop();
    }*/
    cout<<endl<<"e)"<<endl;
    cout<<"The maximum duration for completing an order is "<<dmax<<endl;

    ///e)
    queue <Order> c;
    int k=0;
    int p=0;
    Order* crtt;
    for (int i = 1; i <=N; i++)
        c.push(a[i]);

    for (int i = 1; i <=N && k==0; i++)
    {
        crtt = &c.front();
        c.pop();
        if(crtt->time<=T*60 && (crtt->time+crtt->d)>T*60){
            k++;
        }
        if(crtt->time>=T*60){
            p++;
        }
    }

    cout<<"e)"<<endl;
    if(k==1)
        cout<<"There is one order finished after the program ends and there are "<<p<<" orders unfinished.";
    else
        cout<<"There are no orders finished after closing time and "<<p<<" unfinished orders.";
    return 0;
}
