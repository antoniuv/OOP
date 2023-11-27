#include <iostream>
#include <vector>
#include <string>
#include <typeinfo>

class RON{
    const float to_euro;
public:
    RON(float to_euro = 0.21) : to_euro(to_euro) {}
    float getToEuro(){
        return to_euro;
    }
};

class EUR{
    const float to_euro;
    public:
    EUR(float to_euro = 1) : to_euro(to_euro) {}
    float getToEuro(){
        return to_euro;
    }
};

class USD{
    const float to_euro;
    public:
    USD(float to_euro = 0.84) : to_euro(to_euro) {}
    float getToEuro(){
        return to_euro;
    }
};

class plataBase {
    public:
    virtual float getValoare() = 0;
    virtual ~plataBase() {}
};


template <class T>
class plata: public plataBase{
    float valoare;
    T moneda;
public:
    plata(float valoare) : valoare(valoare) {}
    float getValoare(){
        return valoare * moneda.getToEuro();
    }
};


class Locuinta {
protected:
    std::string numeClient;
    int suprafataUtila;
    float discount;
    float pret;
public:
    Locuinta(std::string numeClient, int suprafataUtila, float discount, float pret) : numeClient(numeClient), suprafataUtila(suprafataUtila), discount(discount), pret(pret) {}
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
    float getPret(){
        return pret;
    }
    void setNumeClient(std::string numeClient){
        this->numeClient = numeClient;
    }
    virtual ~Locuinta() {}
    virtual float CalculChirie(int X, int Y) = 0;
};

class Apartament : public Locuinta {
    int etaj;
public:
    Apartament(std::string numeClient, int suprafataUtila, float discount, int etaj, float pret) : Locuinta(numeClient, suprafataUtila, discount, pret), etaj(etaj) {}
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
    Casa(std::string numeClient, int suprafataUtila, float discount, int suprafataCurte, float pret) : Locuinta(numeClient, suprafataUtila, discount, pret), suprafataCurte(suprafataCurte) {}
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

class Locuinta_factory{
    public:
    static Apartament* Garsoniera () {return new Apartament("gol", 30, 0, 1, 30000);}
    static Apartament* Apartament_2cam () {return new Apartament("gol", 50, 0, 1, 50000);}
    static Apartament* Apartament_3cam () {return new Apartament("gol", 70, 0, 1, 70000);}
    static Casa* Casa_mica () {return new Casa("gol", 100, 0, 50, 100000);}
    static Casa* Casa_mare () {return new Casa("gol", 200, 0, 100, 200000);}
};

class Apartament_builder{
    std::string numeClient;
    int suprafataUtila;
    float discount;
    int etaj;
    float pret;
    public:
    Apartament_builder& setNumeClient(std::string numeClient){
        this->numeClient = numeClient;
        return *this;
    }
    Apartament_builder& setSuprafataUtila(int suprafataUtila){
        this->suprafataUtila = suprafataUtila;
        return *this;
    }
    Apartament_builder& setDiscount(float discount){
        this->discount = discount;
        return *this;
    }
    Apartament_builder& setEtaj(int etaj){
        this->etaj = etaj;
        return *this;
    }
    Apartament_builder& setPret(float pret){
        this->pret = pret;
        return *this;
    }
    Apartament* build(){
        return new Apartament(numeClient, suprafataUtila, discount, etaj, pret);
    }
};

class Casa_builder{
    std::string numeClient;
    int suprafataUtila;
    float discount;
    int suprafataCurte;
    float pret;
    public:
    Casa_builder& setNumeClient(std::string numeClient){
        this->numeClient = numeClient;
        return *this;
    }
    Casa_builder& setSuprafataUtila(int suprafataUtila){
        this->suprafataUtila = suprafataUtila;
        return *this;
    }
    Casa_builder& setDiscount(float discount){
        this->discount = discount;
        return *this;
    }
    Casa_builder& setSuprafataCurte(int suprafataCurte){
        this->suprafataCurte = suprafataCurte;
        return *this;
    }
    Casa_builder& setPret(float pret){
        this->pret = pret;
        return *this;
    }
    Casa* build(){
        return new Casa(numeClient, suprafataUtila, discount, suprafataCurte, pret);
    }
};

class AgentieImobiliara {
    std::vector<Locuinta*> locuinte;
public:
    AgentieImobiliara() {}
    void adaugaLocuinta() {
            std::cout<<"Alege tipul locuintei:"<<std::endl;
            std::cout<<"1. Template Prestabilit"<<std::endl;
            std::cout<<"2. Template Personalizat"<<std::endl;
            int optiune;
            std::cin>>optiune;
            if(optiune == 1){
                std::cout<<"Alegeti din optiunile disponibile:"<<std::endl;
                std::cout<<"1. Garsoniera"<<std::endl;
                std::cout<<"2. Apartament 2 Camere"<<std::endl;
                std::cout<<"3. Apartament 3 Camere"<<std::endl;
                std::cout<<"4. Casa Mica"<<std::endl;
                std::cout<<"5. Casa Mare"<<std::endl;
                int optiune2;
                std::cin>>optiune2;
                if(optiune2 == 1){
                    Locuinta* garsoniera = Locuinta_factory::Garsoniera();
                    locuinte.push_back(dynamic_cast<Locuinta*>(garsoniera));
                }
                else if(optiune2 == 2){
                    Locuinta* apartament2 = Locuinta_factory::Apartament_2cam();
                    locuinte.push_back(dynamic_cast<Locuinta*>(apartament2));
                }
                else if(optiune2 == 3){
                    Locuinta* apartament3 = Locuinta_factory::Apartament_3cam();
                    locuinte.push_back(dynamic_cast<Locuinta*>(apartament3));
                }
                else if(optiune2 == 4){
                    Locuinta* casaMica = Locuinta_factory::Casa_mica();
                    locuinte.push_back(dynamic_cast<Locuinta*>(casaMica));
                }
                else if(optiune2 == 5){
                    Locuinta* casaMare = Locuinta_factory::Casa_mare();
                    locuinte.push_back(dynamic_cast<Locuinta*>(casaMare));
                }
                else{
                    std::cout<<"Optiune invalida!"<<std::endl;
                }
            }
            else if(optiune == 2){
            std::string numeClient;
            int suprafataUtila;
            float discount;
            float pret;
            std::cout<<"Introduceti numele, suprafata, discount-ul si pretul:"<<std::endl;
            std::cin >> numeClient >> suprafataUtila >> discount >> pret;

            std::string tipLocuinta;
            std::cout<<"Introduceti tipul locuintei(Apartament|Casa):"<<std::endl;
            std::cin >> tipLocuinta;
            try{
            if (tipLocuinta == "Apartament") {
                int etaj;
                std::cout<<"Introduceti etajul:"<<std::endl;
                std::cin >> etaj;
                Apartament_builder builder;
                locuinte.push_back(dynamic_cast<Locuinta*>(builder.setNumeClient(numeClient).setSuprafataUtila(suprafataUtila).setDiscount(discount).setEtaj(etaj).setPret(pret).build()));
                ///Locuinta* apartament = new Apartament(numeClient, suprafataUtila, discount, etaj);
                ///locuinte.push_back(dynamic_cast<Locuinta*>(new Apartament(numeClient, suprafataUtila, discount, etaj, pret)));
            }
            else if (tipLocuinta == "Casa") {
                int suprafataCurte;
                std::cout<<"Introduceti suprafata curtii:"<<std::endl;
                std::cin >> suprafataCurte;
                Casa_builder builder;
                locuinte.push_back(dynamic_cast<Locuinta*>(builder.setNumeClient(numeClient).setSuprafataUtila(suprafataUtila).setDiscount(discount).setSuprafataCurte(suprafataCurte).setPret(pret).build()));
                ///Locuinta* casa = new Casa(numeClient, suprafataUtila, discount, suprafataCurte);
                ///locuinte.push_back(dynamic_cast<Locuinta*>(new Casa(numeClient, suprafataUtila, discount, suprafataCurte, pret)));
            }
            else 
            {throw std::invalid_argument("Tip precizat incorect!");}
        }
        catch (const std::invalid_argument& ex) {
            std::cout << std::endl;
            std::cout << "Error: " << ex.what() << std::endl<<std::endl;}
            }
            else{
                std::cout<<"Optiune invalida!"<<std::endl;
            }
    }
    void inchirieazaLocuinta() {
        std::string numeClient;
        std::cout<<"Introduceti numele clientului:"<<std::endl;
        std::cin >> numeClient;
        for(auto& locuinta : locuinte){
            std::cout<<"Client: "<<locuinta->getNumeClient()<<std::endl<<"Suprafata: "<<locuinta->getSuprafataUtila()<<std::endl<<"Discount: "<<locuinta->getDiscount()<<std::endl<< "pret: " <<std::endl<<locuinta->getPret() <<" Euro"<<std::endl;
            if(typeid(*locuinta)==typeid(Apartament))
                std::cout<<"Etaj: "<<((Apartament*)locuinta)->getEtaj()<<std::endl;
            else
                std::cout<<"Suprafata curte: "<<((Casa*)locuinta)->getSuprafataCurte()<<std::endl;
            if(locuinta->getNumeClient() == "gol"){
                std::string raspuns;
                std::cout<<"Doriti sa inchiriati aceasta locuinta? (DA/NU)"<<std::endl;
                std::cin >> raspuns;
                if(raspuns == "DA"){
                std::cout<<"Locuinta a fost inchiriata de "<<numeClient<<std::endl;
                locuinta->setNumeClient(numeClient);
                break;
                }
            }
        }
        std::cout << std::endl;
    }
    void cumparaLocuinta() {
        std::string numeClient;
        std::cout<<"Introduceti numele clientului:"<<std::endl;
        std::cin >> numeClient;
        std::cout <<"Introduceti suma platii:" << std::endl;
        float suma;
        std::cin >> suma;
        std::string moneda;
        std::cout <<"Introduceti moneda platii(RON|EUR|USD):" << std::endl;
        std::cin >> moneda;
        plataBase* achizitie = nullptr;
        if (moneda == "RON") {
            achizitie = new plata<RON>(suma);
        }
        else if (moneda == "EUR") {
            achizitie = new plata<EUR>(suma);
        }
        else if (moneda == "USD") {
            achizitie = new plata<USD>(suma);
        }
        else {
            std::cout << "Trecere in EUR...";
            achizitie = new plata<EUR>(suma);
        }
        std::cout << "Suma in EUR: " << achizitie->getValoare() << std::endl << std::endl;
        for(auto& locuinta : locuinte){
            std::cout<<"Client: "<<locuinta->getNumeClient()<<std::endl<<"Suprafata: "<<locuinta->getSuprafataUtila()<<std::endl<<"Discount: "<<locuinta->getDiscount()<<std::endl<<locuinta->getPret() <<" Euro"<<std::endl;
            if(typeid(*locuinta)==typeid(Apartament))
                std::cout<<"Etaj: "<<((Apartament*)locuinta)->getEtaj()<<std::endl;
            else
                std::cout<<"Suprafata curte: "<<((Casa*)locuinta)->getSuprafataCurte()<<std::endl;
            if(locuinta->getNumeClient() == "gol"){
                std::string raspuns;
                std::cout<<"Doriti sa cumparati aceasta locuinta? (DA/NU)"<<std::endl;
                std::cin >> raspuns;
                if(raspuns == "DA" && achizitie->getValoare() >= locuinta->getPret()){
                std::cout<<"Locuinta a fost cumparata de "<<numeClient<<std::endl;
                locuinta->setNumeClient(numeClient);
                }
                else if(raspuns == "DA" && achizitie->getValoare() < locuinta->getPret()){
                    std::cout<<"Suma insuficienta!"<<std::endl;
                }
            }
        }
        std::cout << std::endl;
    }
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
            float pret;
            std::cout<<"Introduceti numele, suprafata, discount-ul si pretul:"<<std::endl;
            in >> numeClient >> suprafataUtila >> discount >> pret;

            std::string tipLocuinta;
            std::cout<<"Introduceti tipul locuintei(Apartament|Casa):"<<std::endl;
            in >> tipLocuinta;
            try{
            if (tipLocuinta == "Apartament") {
                int etaj;
                std::cout<<"Introduceti etajul:"<<std::endl;
                in >> etaj;

                ///Locuinta* apartament = new Apartament(numeClient, suprafataUtila, discount, etaj);
                agentie.locuinte.push_back(dynamic_cast<Locuinta*>(new Apartament(numeClient, suprafataUtila, discount, etaj, pret)));
            }
            else if (tipLocuinta == "Casa") {
                int suprafataCurte;
                std::cout<<"Introduceti suprafata curtii:"<<std::endl;
                in >> suprafataCurte;

                ///Locuinta* casa = new Casa(numeClient, suprafataUtila, discount, suprafataCurte);
                agentie.locuinte.push_back(dynamic_cast<Locuinta*>(new Casa(numeClient, suprafataUtila, discount, suprafataCurte, pret)));
            }
            else 
            {throw std::invalid_argument("Tip precizat incorect!");}
        }
        catch (const std::invalid_argument& ex) {
            std::cout << std::endl;
            std::cout << "Error: " << ex.what() << std::endl; i--;}
        }
        std::cout << std::endl;
        return in;
    }

    friend std::ostream& operator<<(std::ostream& out, const AgentieImobiliara& agentie) {
        for (const auto& locuinta : agentie.locuinte) {
            int X,Y;
            out<<"Client: "<<locuinta->getNumeClient()<<std::endl<<"Suprafata: "<<locuinta->getSuprafataUtila()<<std::endl<<"Discount: "<<locuinta->getDiscount()<< std::endl <<"Pret: "<<std::endl<<locuinta->getPret() <<" Euro"<<std::endl;
            if(typeid(*locuinta)==typeid(Apartament))
                out<<"Etaj: "<<((Apartament*)locuinta)->getEtaj()<<std::endl;
            else
                out<<"Suprafata curte: "<<((Casa*)locuinta)->getSuprafataCurte()<<std::endl;
            std::string optiune;
            std::cout<<"Calculati chiria(DA/NU)? "<<std::endl;
            std::cin >> optiune;
            if(optiune=="DA")
            {
            std::cout<<"Introduceti pret/metru patrat: "<<std::endl;
            std::cin >> X;
            std::cout<<"Se aplica discount-ul(1|0): "<<std::endl; 
            std::cin >> Y;
            out <<"Chirie: "<< locuinta->CalculChirie(X, Y) << std::endl << std::endl;
            }
            std::cout << std::endl;
        }

        return out;
    }
};

