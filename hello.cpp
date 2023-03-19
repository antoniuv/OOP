#include <iostream>
#include <cstring>
using namespace std;

class Ingredient
{
    string nume;
    float pret;
    int cantitate;
    public:
        Ingredient(const string& numeIngredient)
        {
            nume=numeIngredient;
            pret=0.0;
            cantitate=0;
        }
        Ingredient(const string& numeIngredient="nimic", const float& pretIngredient=0.0, const int& cantitateIngredient=0)
        {
            nume=numeIngredient;
            pret=pretIngredient;
            cantitate=cantitateIngredient;
        }
        Ingredient(const Ingredient& altIngredient)
	    {
		    nume = altIngredient.nume;
            pret = altIngredient.pret;
            cantitate = altIngredient.cantitate;
        }
        Ingredient& operator=(const Ingredient& altIngredient)
	    {
		    nume = altIngredient.nume;
            pret = altIngredient.pret;
            cantitate = altIngredient.cantitate;
		    return *this;
	    }
        Ingredient& operator+=(int y)
	    {
            this->cantitate += y;
		    return *this;
	    }
        string getNume()
        {
	        return nume;
        }
        void setter(string numeIngredient, float pretnou , int cantitatenou)
        {
	        nume = numeIngredient;
            pret = pretnou;
            cantitate = cantitatenou;
        }
        void setter(const Ingredient& altIngredient)
        {
	        nume = altIngredient.nume;
            pret = altIngredient.pret;
            cantitate = altIngredient.cantitate;
        }
        ~Ingredient(){};
        friend ostream& operator<<(ostream& os, const Ingredient& altIngredient);
        friend istream& operator>>(istream& in, Ingredient& altIngredient);
};

ostream& operator<<(ostream& os, const Ingredient& altIngredient)
{
    os << altIngredient.nume << ' ' << altIngredient.pret << ' ' << altIngredient.cantitate << endl;
    return os;
}
istream& operator>>(istream& in, Ingredient& altIngredient)
{
    in >> altIngredient.nume >> altIngredient.pret >> altIngredient.cantitate;
    return in;
}

class Pizza
{
    char denumire[50];
    int nrIngrediente;
    Ingredient Ingr[10];
    public:
        Pizza(){}
        Pizza(const char* altdenumire)
        {
            strcpy(denumire, altdenumire);
            nrIngrediente = 0;
        }
        Pizza(const char* altdenumire, const int& altnr)
        {
            strcpy(denumire, altdenumire);
            nrIngrediente=altnr;
        }
        Pizza& operator+=(const Ingredient& y)
	    {
            Ingr[nrIngrediente] = y;
            nrIngrediente++;
		    return *this;
	    }
        bool operator>(const Pizza& altaPizza)
        {
            if (nrIngrediente > altaPizza.nrIngrediente) return false;
            else return false;
        }
        ~Pizza(){}
        friend ostream& operator<<(ostream& os, const Pizza& altaPizza);
        friend istream& operator>>(istream& in, Pizza& altaPizza);


};

istream& operator>>(istream& in, Pizza& altaPizza)
{
    in >> altaPizza.denumire >> altaPizza.nrIngrediente;
    for(int i=0;i<altaPizza.nrIngrediente;i++)cin>>altaPizza.Ingr[i];
    return in;
}

ostream& operator<<(ostream& os, const Pizza& altaPizza)
{
    os << altaPizza.denumire << ' ' << altaPizza.nrIngrediente << endl;
    for(int i=0;i<altaPizza.nrIngrediente;i++)cout<<altaPizza.Ingr[i];
    return os;
}

int main()
{
    Ingredient i1("Piper",0.5, 10), i2("Nimic", 0.0, 0);
    cout<<i1;
    cin>>i2;
    i1 += 500; // aduna o valoare la cantitatea disponibila
    Ingredient i3 = i1, i4, i5(i1);
    i4 = i1;
    Pizza pizza1("Clasic"), pizza2;
    pizza1 += i1;
    cin>>pizza2; 
    cout<<pizza1<<pizza2;
    if (pizza1 > pizza2) cout<<"pizza1 are mai multe ingrediente decat pizza2";
    else cout<<"pizza2 are mai multe ingrediente decat pizza1";
    return 0;
}