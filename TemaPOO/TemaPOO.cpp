#include <iostream>
#include <random>
#include <time.h>

/// Simulator de magazin
/// Functionalitatea Magazinului este urmatoarea:
/// La magazin vin clienti cu un nr random de bani, si nr random de produse distincte pe care doresc sa le cumpere
/// Lista clientului este citita la tastatura
/// Apoi este procesata de Program
/// Daca Clientul nu are destui bani sa achite, i se spune sa returneze un obiect, iar el il returneaza pe cel mai scump
/// Daca in Stoc nu mai sunt Produse, Clientul nu va achita banii pe produsele respective
/// Daca in Stoc sunt produse, iar clientul cere mai mult decat sunt, el va achita bani doar pentru produsele care sunt in stoc
/// Ziua se termina cand au trecut pe la magazin 10 clienti
/// lista de produse este putin mai jos
/// Programul nu este case Sensitive, de aceea recomand sa tastati produsele cu litere mici
/// Atat, daca mai apare ceva, va anunt
/// In final, clientul va cumpara Produsele doar daca are destui bani ca sa achite
/// La final se afiseaza earnedMoney

///Ar putea fi erori de scriere, sau niste bugguri care sunt de fapt feature-uri
///La momentul de fata am monitorizat toti pasii programului, iar acesta nu ar trebui sa dea erori
///daca exista erori, ma anuntati

using namespace std;

string ProductList[11] = { "varza","paine","faina","vin","cartofi","jucarii","lapte","mere","snickers",/*bere*/"blonda",/*bere*/"bruna" };

class Produs
{
    string nume;
    int pret;
    int cant;
public:
    Produs() { }
    Produs(string nume, int pret, int cant)
    {
        this->nume = nume;
        this->pret = pret;
        this->cant = cant;
    }

    Produs(const Produs& p)
    {
        this->nume = p.nume;
        this->pret = p.pret;
        this->cant = p.cant;
    }
    ~Produs()
    {
        //cout<<"destructor";
    }
#pragma region set&get
    void setNume(string nume)
    {
        this->nume = nume;
    }
    void setPret(int pret)
    {
        this->pret = pret;
    }
    void setCant(int cant)
    {
        this->cant = cant;
    }

    string getNume()
    {
        return nume;
    }
    int getPret()
    {
        return pret;
    }
    int getCant()
    {
        return cant;
    }

    void setPret()
    {
        if (nume == "varza" or nume == "Varza")
            pret = 5 * cant;
        else if (nume == "paine" or nume == "Paine")
            pret = 7 * cant;
        else if (nume == "faina" or nume == "Faina")
            pret = 7 * cant;
        else if (nume == "blonda" or nume == "Blonda")
            pret = 17 * cant;
        else if (nume == "bruna" or nume == "Bruna")
            pret = 20 * cant;
        else if (nume == "vin" or nume == "Vin")
            pret = 50 * cant;
        else if (nume == "cartofi" or nume == "Cartofi")
            pret = 3 * cant;
        else if (nume == "jucarii" or nume == "Jucarii")
            pret = 15 * cant;
        else if (nume == "lapte" or nume == "Lapte")
            pret = 8 * cant;
        else if (nume == "mere" or nume == "Mere")
            pret = 4 * cant;
        else if (nume == "snickers" or nume == "Snickers")
            pret = 10 * cant;
    }
#pragma endregion

    friend istream& operator>>(istream&, Produs&);
    friend ostream& operator<<(ostream&, Produs&);
};


class Client
{
    int money;
    int cateProduse;
    Produs listaProduse[11];
    int totalPrice;
public:
    Client()
    {
        this->money = rand() % (100 + 1) + 100;
        this->cateProduse = 2 + rand() % 5;
    }

#pragma region Set&Get
    void setMoney(int money)
    {
        this->money = money;
    }
    void setCateProduse(int cateProduse)
    {
        this->cateProduse = cateProduse;
    }

    void setList()
    {
        cout << "Lista Clientului: (produs cantitate)\n";
        for (int i = 0; i < cateProduse; i++)
        {
            cin >> listaProduse[i];
            if (listaProduse[i].getNume() == "bere" or listaProduse[i].getNume() == "Bere")
            {
                string s;
                cout << "Blonda/Bruna?\n";
                cin >> s;
                listaProduse[i].setNume(s);
                listaProduse[i].setPret();

            }
            else
                listaProduse[i].setPret();
        }
    }

    void generateList()
    {
        int a[11] = { 0 };
        int i = 0;
        cout << "Lista Clientului: (produs cantitate)\n";
        do {
            int x = rand() % 11;
            if (!a[x])
            {
                int cant = rand() % 10 + 1;
                a[x] = 1;
                listaProduse[i].setNume(ProductList[x]);
                listaProduse[i].setCant(cant);
                listaProduse[i].setPret();
                i++;
            }
        } while (i < cateProduse);
    }

    void idxSetCant(int i, int x)
    {
        listaProduse[i].setCant(x);
    }

    void idxSetPret(int i, int x)
    {
        listaProduse[i].setPret(x);
    }

    int getidxMaxPret()
    {
        int j = 0;
        int max = listaProduse[0].getPret();
        for (int i = 0; i < cateProduse; i++)
        {
            if (listaProduse[i].getPret() > max)
            {
                max = listaProduse[i].getPret();
                j = i;
            }
        }
        return j;
    }

    Produs* getListaProduse()
    {
        return listaProduse;
    }

    int getMoney()
    {
        return money;
    }
    int getCateProduse()
    {
        return cateProduse;
    }
    int getTotalPrice()
    {
        return totalPrice;
    }
#pragma endregion

    void calculateTotalPrice()
    {
        int sum = 0;
        for (int i = 0; i < cateProduse; i++)
        {
            sum += listaProduse[i].getPret();
        }

        this->totalPrice = sum;
    }
    void cumpara()
    {
        calculateTotalPrice();
        cout << "trebuie sa achite " << getTotalPrice() << " lei\n";
        cout << endl;
    }
    void returnOb()
    {
        int i = getidxMaxPret();
        listaProduse[i].setCant(listaProduse[i].getCant() - 1);
        listaProduse[i].setPret();
    }

    void getNormalPrice(int idx)
    {
        while (money < totalPrice)
        {
            returnOb();
            if (listaProduse[idx].getCant() == 0)
                idxSetPret(idx, 0);
            calculateTotalPrice();
        }
    }
};

#pragma region Supraincarcare Cin Cout
istream& operator>>(istream& in, Produs& produs)
{
    in >> produs.nume >> produs.cant;
    return in;
}

ostream& operator<<(ostream& out, Produs& produs)
{
    out << produs.nume << ' ';
    if (produs.cant != 0)
    {
        out << produs.cant << ' ' << "in stoc si costa ";
        out << (produs.pret) / produs.cant << " Lei per unitate" << ' ';
    }
    else
        out << "Nu mai avem acest produs";
    return out;
}

#pragma endregion

class Magazin
{
    Produs stocProduse[11];
    Client listaClienti[5];
    int earnedMoney;
    int soldProducts;

public:
    Magazin()
    {
        for (int i = 0; i < 11; i++)
        {
            int x = rand() % (10 + 1) + 15;
            stocProduse[i].setNume(ProductList[i]);
            stocProduse[i].setCant(x);
            stocProduse[i].setPret();
        }
        earnedMoney = 0;
        soldProducts = 0;
    }
    void primireaClientilor()
    {
        for (int i = 0; i < 5; i++)
        {
            cout << "Clientul nr " << i + 1 << endl;
            Client c;

            Produs* listaClient = new Produs[c.getCateProduse()];

            cout << "Clientul cumpara " << c.getCateProduse() << " tipuri de produse" << endl;  //client prezentarea
            cout << "Clientul are " << c.getMoney() << " lei" << endl;
            cout << endl;

            cout << "Introduceti lista:\n";
            c.setList();
            cout << endl;
            c.calculateTotalPrice();

            if (c.getMoney() < c.getTotalPrice())
            {
                cout << "Nu are destui bani, trebuie sa returneze ceva..\n";
                c.getNormalPrice(i);
                cout << endl;
            }


            for (int i = 0; i < c.getCateProduse(); i++)
            {
                listaClient[i] = c.getListaProduse()[i];
            }
            actualizareStoc_Client(c);

            for (int i = 0; i < c.getCateProduse(); i++)
            {
                c.idxSetCant(i, listaClient[i].getCant());
                if (listaClient[i].getCant() == 0)
                    c.idxSetPret(i, 0);
            }

            //Monitorizarea functionaliatii
            cout << "\Lista finala a Clientului:\n";
            for (int i = 0; i < c.getCateProduse(); i++)
                cout << c.getListaProduse()[i] << endl;

            c.cumpara();



            cout << endl;
            earnedMoney += c.getTotalPrice();

            delete[] listaClient;


        }
    }

    void randPerspective()
    {
        for (int i = 0; i < 5; i++)
        {
            cout << "Clientul nr " << i + 1 << endl;
            Client c;

            Produs* listaClient = new Produs[c.getCateProduse()];

            cout << "Clientul cumpara " << c.getCateProduse() << " tipuri de produse" << endl;  //client prezentarea
            cout << "Clientul are " << c.getMoney() << " lei" << endl;
            cout << endl;

            c.generateList();
            for (int i = 0; i < c.getCateProduse(); i++)
                cout << c.getListaProduse()[i] << endl;

            cout << endl;
            c.calculateTotalPrice();

            if (c.getMoney() < c.getTotalPrice())
            {
                cout << "Nu are destui bani, trebuie sa returneze ceva..\n";
                c.getNormalPrice(i);
                cout << endl;
            }

            for (int i = 0; i < c.getCateProduse(); i++)
                listaClient[i] = c.getListaProduse()[i];


            actualizareStoc_Client(c);

            for (int i = 0; i < c.getCateProduse(); i++)
            {
                c.idxSetCant(i, listaClient[i].getCant());
                if (listaClient[i].getCant() == 0)
                    c.idxSetPret(i, 0);
            }


            cout << "\Lista finala a Clientului:\n";
            for (int i = 0; i < c.getCateProduse(); i++)
                cout << c.getListaProduse()[i] << endl;

            c.cumpara();



            cout << endl;
            earnedMoney += c.getTotalPrice();

            delete[] listaClient;

            string s;
            cout << "\nApasa 'c' pentru a continua\n";
            cin >> s;
        }
    }
    void getStoc()
    {
        cout << "Produse in stoc:\n";
        for (int i = 0; i < 11; i++)
        {
            string x = stocProduse[i].getNume();
            if (x == "varza" or x == "paine" or x == "jucarii" or x == "blonda" or x == "vin" or x == "bruna" or x == "snickers" or x == "lapte")
                if (stocProduse[i].getCant() != 0)
                    cout << stocProduse[i] << "buc\n";
                else
                    cout << stocProduse[i] << endl;
            else if (x == "faina" or x == "cartofi" or x == "mere")
                if (stocProduse[i].getCant() != 0)
                    cout << stocProduse[i] << " Kg\n";
                else
                    cout << stocProduse[i] << endl;
        }
    }

    void actualizareClient(Client& c)
    {
        for (int i = 0; i < 11; i++)
            for (int j = 0; j < 11; j++)
                if (stocProduse[i].getNume() == c.getListaProduse()[j].getNume())
                {
                    if (stocProduse[i].getCant() < c.getListaProduse()[j].getCant())
                    {
                        while (stocProduse[i].getCant() < c.getListaProduse()[j].getCant())
                        {
                            c.idxSetCant(j, c.getListaProduse()[j].getCant() - 1);
                        }
                        stocProduse[i].setCant(0);
                    }
                }
    }

    void actualizareStoc_Client(Client& c)
    {

        for (int i = 0; i < 11; i++)
            for (int j = 0; j < 11; j++)
                if (stocProduse[i].getNume() == c.getListaProduse()[j].getNume())
                {

                    if (stocProduse[i].getCant() == 0)
                    {
                        cout << stocProduse[i].getNume() << ' ';
                        cout << " nu mai avem acest produs in stoc\n";
                        c.idxSetCant(j, 0);
                        break;
                    }
                    if (stocProduse[i].getCant() >= c.getListaProduse()[j].getCant())
                    {
                        int x = stocProduse[i].getCant() - c.getListaProduse()[j].getCant();
                        stocProduse[i].setCant(x);
                    }
                    else
                    {
                        while (stocProduse[i].getCant() < c.getListaProduse()[j].getCant())
                        {
                            c.idxSetCant(j, c.getListaProduse()[j].getCant() - 1);
                        }
                        stocProduse[i].setCant(0);
                    }

                    if (c.getListaProduse()[j].getCant() == 0)
                    {
                        c.idxSetPret(j, 0);
                    }
                }
    }

    void setEarnedMoney(int x)
    {
        earnedMoney = x;
    }
    int getEarnedMoney()
    {
        return earnedMoney;
    }

};


void MENIU()
{
    cout << "Bine ati venit in Magazinul Moldova:\n";
    cout << "Proprietar: Hadirca Dionisie\n";


    Magazin m;
    string x;
    do {
        cout << "Alegeti din ce perspectiva doriti sa simulati magazinul\n";
        cout << "1 - Perspectiva 1\n";
        cout << "2 - Perspectiva 2\n\n";

        int n;
        cin >> n;

        switch (n)
        {
        case 1:

            cout << "Veti simula Clientii care vin cu listele de cumparaturi.\n";
            cout << "Aveti un nr random de bani si de produse in lista d-voastra.\n";
            cout << "Cumparati ce doriti si ce se afla in stoc.\n";

            m.getStoc();
            cout << endl;
            m.primireaClientilor();
            cout << "Astazi am facut " << m.getEarnedMoney() << " Lei\n\n";

            m.getStoc();
            cout << endl;
            m.setEarnedMoney(0);

        case 2:

            cout << "Veti privi clientii de la persoana 3 observand cine si ce cumpara.\n";
            m.getStoc();
            cout << endl;
            m.randPerspective();
            cout << "Astazi am facut " << m.getEarnedMoney() << " Lei\n\n";

            m.getStoc();
            cout << endl;
            m.setEarnedMoney(0);

        }

        cout << "Pentru a termina programul tastati 'exit'\n";
        cout << "Pentru a continua tastati orice tasta\n";
        cin >> x;
    } while (x != "exit");
}


int main()
{
    srand(time(NULL));
    MENIU();
    return 0;
}