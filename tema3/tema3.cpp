#include "agentie.h"

using namespace std;

int main() {
    AgentieImobiliara agentie;
    while(true)
    {
    cout<<"Alegeti o optiune:"<<endl;
    cout<<"0.Exit"<<endl;
    cout<<"1.Citeste locuinte"<<endl;
    cout<<"2.Afisare locuinte"<<endl;
    cout<<"3.Adaugare locuinta"<<endl;
    cout<<"4.Inchiriere locuinta"<<endl;
    cout<<"5.Vanzare locuinta"<<endl;

    int optiune;
    cin>>optiune;
    if(optiune==0)
        break;
    else if(optiune==1)
        cin>>agentie;
    else if(optiune==2)
        cout<<agentie;
    else if(optiune==3)
        agentie.adaugaLocuinta();
    else if(optiune==4)
        agentie.inchirieazaLocuinta();
    else if(optiune==5)
        agentie.cumparaLocuinta();
    else
        cout<<"Optiune invalida"<<endl;
    }
return 0;
}
