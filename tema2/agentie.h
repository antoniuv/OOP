#include <iostream>
#include <vector>
#include <string>
#include <typeinfo>


class Locuinta {
protected:
    std::string numeClient;
    int suprafataUtila;
    float discount;
public:
    Locuinta(std::string numeClient, int suprafataUtila, float discount) : numeClient(numeClient), suprafataUtila(suprafataUtila), discount(discount) {}
    Locuinta(const Locuinta& locuinta) : numeClient(locuinta.numeClient), suprafataUtila(locuinta.suprafataUtila), discount(locuinta.discount) {}
    Locuinta& operator=(const Locuinta& locuinta) {
        numeClient = locuinta.numeClient;
        suprafataUtila = locuinta.suprafataUtila;
        discount = locuinta.discount;
        return *this;
    }
    std::string getNumeClient(){
        return numeClient;
    }
    int getSuprafataUtila(){
        return suprafataUtila;
    }
    float getDiscount(){
        return discount;
    }
    virtual ~Locuinta() {}
    virtual float CalculChirie(int X, int Y) = 0;
};

class Apartament : public Locuinta {
    int etaj;
public:
    Apartament(std::string numeClient, int suprafataUtila, float discount, int etaj) : Locuinta(numeClient, suprafataUtila, discount), etaj(etaj) {}
    Apartament(const Apartament& apartament) : Locuinta(apartament), etaj(apartament.etaj) {}
    Apartament& operator=(const Apartament& apartament) {
        Locuinta::operator=(apartament);
        etaj = apartament.etaj;
        return *this;
    }
    int getEtaj(){
        return etaj;
    }
    float CalculChirie(int X, int Y) override {
        return X * suprafataUtila * (1 - Y * discount / 100.0);
    }
};

class Casa : public Locuinta {
    int suprafataCurte;
public:
    Casa(std::string numeClient, int suprafataUtila, float discount, int suprafataCurte) : Locuinta(numeClient, suprafataUtila, discount), suprafataCurte(suprafataCurte) {}
    Casa(const Casa& casa) : Locuinta(casa), suprafataCurte(casa.suprafataCurte) {}
    Casa& operator=(const Casa& casa) {
        Locuinta::operator=(casa);
        suprafataCurte = casa.suprafataCurte;
        return *this;
    }
    int getSuprafataCurte(){
        return suprafataCurte;
    }
    float CalculChirie(int X, int Y) override {
        return X * (suprafataUtila + 0.2 * suprafataCurte) * (1 - Y * discount / 100.0);
    }
};

class AgentieImobiliara {
    std::vector<Locuinta*> locuinte;
public:
    ~AgentieImobiliara() {
        for (auto& locuinta : locuinte) {
            delete locuinta;
        }
    }

    friend std::istream& operator>>(std::istream& in, AgentieImobiliara& agentie) {
        int numarLocuinte;
        std::cout<<"Introduceti numarul de locuinte:"<<std::endl;
        in >> numarLocuinte;

        for (int i = 0; i < numarLocuinte; i++) {
            std::string numeClient;
            int suprafataUtila;
            float discount;
            std::cout<<"Introduceti numele, suprafata si discount-ul:"<<std::endl;
            in >> numeClient >> suprafataUtila >> discount;

            std::string tipLocuinta;
            std::cout<<"Introduceti tipul locuintei(Apartament|Casa):"<<std::endl;
            in >> tipLocuinta;
            try{
            if (tipLocuinta == "Apartament") {
                int etaj;
                std::cout<<"Introduceti etajul:"<<std::endl;
                in >> etaj;

                Locuinta* apartament = new Apartament(numeClient, suprafataUtila, discount, etaj);
                agentie.locuinte.push_back(apartament);
            }
            else if (tipLocuinta == "Casa") {
                int suprafataCurte;
                std::cout<<"Introduceti suprafata curtii:"<<std::endl;
                in >> suprafataCurte;

                Locuinta* casa = new Casa(numeClient, suprafataUtila, discount, suprafataCurte);
                agentie.locuinte.push_back(casa);
            }
            else 
            {throw std::invalid_argument("Tip precizat incorect!");}
        }
        catch (const std::invalid_argument& ex) {
            std::cout << "Error: " << ex.what() << std::endl; i--;}
        }
        return in;
    }

    friend std::ostream& operator<<(std::ostream& out, const AgentieImobiliara& agentie) {
        for (const auto& locuinta : agentie.locuinte) {
            int X,Y;
            out<<"Client: "<<locuinta->getNumeClient()<<std::endl<<"Suprafata: "<<locuinta->getSuprafataUtila()<<std::endl<<"Discount: "<<locuinta->getDiscount()<<std::endl;
            if(typeid(*locuinta)==typeid(Apartament))
                out<<"Etaj: "<<((Apartament*)locuinta)->getEtaj()<<std::endl;
            else
                out<<"Suprafata curte: "<<((Casa*)locuinta)->getSuprafataCurte()<<std::endl;
            std::cout<<"Introduceti pret/metru patrat: "<<std::endl;
            std::cin >> X;
            std::cout<<"Se aplica discount-ul(1|0): "<<std::endl; 
            std::cin >> Y;
            out <<"Chirie: "<< locuinta->CalculChirie(X, Y) << std::endl << std::endl;
        }

        return out;
    }
};
