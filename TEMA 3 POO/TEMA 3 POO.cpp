#include <iostream>
#include <math.h>
#include <cmath>
#include <exception>
#include <string>
#include <limits>
#include <vector>
#include <algorithm>
using namespace std;

const float pi = 3.1415;

//SIMULATOR DE DESENAT FIGURI GEOMETRICE
//Hadirca Dionisie
//Proiect Laborator 2 Mosteniri
//Puteti face orice doriti, cum doriti, dar atat timp cat nu respectati limitele geometriei, figura dumnevoastra va fi INVALIDA
//Patratul si Dreptunghiul sunt cele mai simple de realizat, si aveti slabe sanse sa tastati un input INVALID
//Figura dumnevoasta nu va fi VALIDA pana cand nu veti introduce un input adecvat sau ne lasati pe noi sa va ajutam
//De la Romb in jos nu prea aveti nici o sansa sa introduceti o figura VALIDA, deci veti avea nevoie de ajutorul nostru
//Nu exista bugguri, Exista Feature-uri
//Totusi daca observati vre-o eroare in program va rugam sa ne anuntati
//Have Fun drawing

///NEW!!!!
//La trapeze programul va incerca singur sa creeze o figura valida
//la sectiunea de specializare Gestiune<Trapeze>

float rround(float var)
{
    float value = (int)(var * 100 + .5);
    return (float)value / 100;
}

class Point
{
    float x;
    float y;
public:
    Point();

    Point(float, float);

    Point(const Point& other);

    ~Point();

    void setX(float);

    void setY(float);

    float getX();

    float getY();

    Point& operator=(const Point& other);

    friend ostream& operator<<(ostream&, const Point&);

    friend istream& operator>>(istream&, Point&);
};


class Square
{
    static int numarFiguri;
protected:
    Point sp;
    float length;
    float height = 0;
    int valid = 0;
public:
    Square();

    Square(Point& sp, float, float);

    Square(const Square& other);

    ~Square();

    void setPoint(Point& sp);

    void setLength(float);

    void setHeight(float);

    virtual Point getStartingPoint();

    float getLength();

    float getHeight();

    static void increaseNumarFiguri();

    static int getNumarFiguri();

    virtual void setValidValue();

    int getValidValue();

    bool isValidFigure();

    virtual float calculateSurface();

    virtual float calculateVolume();

    Square& operator=(const Square& other);

    friend ostream& operator<<(ostream&, const Square&);

    friend istream& operator>>(istream&, Square&);

};
int Square::numarFiguri = 0;

class Rhombus :virtual public Square
{
    float alfaAngle;
protected:
    Point ep;
public:
    Rhombus();

    Rhombus(Point& sp, Point& ep, float, float);

    Rhombus(const Rhombus& other);

    ~Rhombus();

    void setEndingPoint(Point& p);

    void setAlfaAngle(float x);

    float calculateLength();

    Point getEndingPoint();

    float calculateAlfa();

    float getAlfaAngle();

    void setValidValue() override;

    float calculateSurface() override;

    float calculateVolume() override;

    Rhombus& operator=(const Rhombus& other);

    friend ostream& operator<<(ostream&, const Rhombus&);

    friend istream& operator>>(istream&, Rhombus& s);

    void setActualLength();
};

class Rectangle :virtual public Square
{
protected:
    float width;
public:
    Rectangle();

    Rectangle(Point& sp, float, float, float);

    Rectangle(const Rectangle& other);

    ~Rectangle();

    void setWidth(float);

    float getWidth();

    void setValidValue() override;

    float calculateSurface() override;

    float calculateVolume() override;

    Rectangle& operator=(const Rectangle& other);

    friend ostream& operator<<(ostream&, const Rectangle&);

    friend istream& operator>>(istream&, Rectangle& s);
};

class Parallelogram : public Rectangle, public Rhombus
{
public:
    Parallelogram();

    Parallelogram(Point& sp, Point& ep, float, float, float);

    Parallelogram(const Parallelogram& other);

    ~Parallelogram();

    float calculateNormalWidth();

    void setNormalWidth();

    void setValidValue() override;

    float calculateSurface() override;

    float calculateVolume() override;

    Parallelogram& operator=(const Parallelogram& other);

    friend ostream& operator<<(ostream& out, const Parallelogram& s);

    friend istream& operator>>(istream& in, Parallelogram& s);
};

class Trapeze :public Parallelogram
{
    float secBase = 0;
    float widthLeft = 0;
    float widthRight = 0;
public:
    Trapeze();
    Trapeze(Point& sp, Point& ep, float, float, float, float, float);
    Trapeze(const Trapeze& other);
    ~Trapeze();
    void setSecBase(float secBase);
    float getSecBase();
    float getWidthRight();
    float getWidthLeft();
    void calculateWidths();
    float calculateSurface() override;
    float calculateVolume() override;
    void setValidValue() override;
    Trapeze& operator=(const Trapeze& other);
    friend ostream& operator<<(ostream& out, const Trapeze& s);
    friend istream& operator>>(istream& in, Trapeze& s);
};

template<class tip_figura>
class Gestiune {
protected:
    vector<tip_figura> vec_figuri;
public:
    //citire/afisare
    virtual void read() {
        tip_figura x;
        int tru;
        while (true) {
            cin >> x;
            vec_figuri.push_back(x);

            cout << "\nMore? 1)yes/2)nu\n";
            cin >> tru;
            if (tru == 2) {
                break;
            }
        }
    }
    virtual void print() {
        cout << "-----------------------------------";
        for (int i = 0; i < vec_figuri.size(); i++) {
            cout << vec_figuri[i] << '\n';
        }
        cout << "-----------------------------------";

        cout << '\n';
    }

    //pur functii stl
    void append(tip_figura x) {
        vec_figuri.push_back(x);
    }
    void pop() {
        vec_figuri.pop_back();
    }

    int size() {
        return vec_figuri.size();
    }

    void clear() {
        vec_figuri.clear();
    }

    void erase(int st, int dr) {
        vec_figuri.erase(vec_figuri.begin() + st, vec_figuri.begin() + dr);
    }
    bool empty() {
        if (vec_figuri.size() != 0)
            return false;
        return true;
    }
    tip_figura front() {
        return *vec_figuri.front();
    }
    tip_figura back() {
        return *vec_figuri.back();
    }

    //algorithm, lambda expressions
    void sort_by_lenght() {
        sort(vec_figuri.begin(), vec_figuri.end(), [](tip_figura& a, tip_figura& b) -> bool {
            return a.getLength() < b.getLength();
            });
    }
    int total_surface_area() {
        int a = 0;
        for_each(vec_figuri.begin(), vec_figuri.end(), [&a](auto i) {
            a += i.calculateSurface();
            });
        return a;
    }

    tip_figura operator[](int index) {
        if (index > size()) {
            cout << "peste limita";
            exit(0);
        }
        return vec_figuri[index];
    }
};

template<>
class Gestiune<Trapeze*> {
protected:
    vector<Trapeze*> vec_figuri;
public:
    virtual void read() {
        int tru;
        while (true) {
            Trapeze* x = new Trapeze();
            cin >> *x;
            vec_figuri.push_back(x);

            cout << "\nMore? 1)yes/2)nu\n";
            cin >> tru;
            if (tru == 2) {
                break;
            }
        }
    }
    virtual void print() {
        cout << "-----------------------------------";
        for (int i = 0; i < vec_figuri.size(); i++) {
            cout << *vec_figuri[i] << '\n';
        }
        cout << "-----------------------------------";
        cout << '\n';
    }

    //operator +=
    void operator+=(Trapeze& x) {
        Trapeze* aux = new Trapeze(x);
        vec_figuri.push_back(aux);
    }

    //pur stl
    void pop() {
        vec_figuri.pop_back();
    }


    int size() {
        return vec_figuri.size();
    }

    void clear() {
        vec_figuri.clear();
    }

    void erase(int st, int dr) {
        vec_figuri.erase(vec_figuri.begin() + st, vec_figuri.begin() + dr);
    }
    bool empty() {
        if (vec_figuri.size() != 0)
            return false;
        return true;
    }
    Trapeze front() {
        return *vec_figuri.front();
    }
    Trapeze back() {
        return *vec_figuri.back();
    }
    Trapeze* operator[](int index) {
        if (index > size()) {
            cout << "peste limita\n";
            exit(0);
        }
        return vec_figuri[index];
    }
};


template<class tip_figura>
class Gestiune_redusa : public Gestiune<tip_figura> {
    static const int limit = 4;
    vector<tip_figura> new_vec;
public:
    void read(){
        tip_figura x;
        int tru;
        int a = 0;
        while (a < limit) {
            cin >> x;
            this->vec_figuri.push_back(x);
            cout << "More? 1)yes/2)no";
            cin >> tru;
            if (tru == 2) {
                break;
            }
            a++;
        }
    }

    void print() {
        cout << "---------------------------------";
        for (int i = 0; i < this->vec_figuri.size(); i++) {
            cout << this->vec_figuri[i]<<'\n';
        }
        cout << "---------------------------------";
        cout << endl;
    }

    void insert(tip_figura& x, int index) {
        if (index >= limit) {
            cout << "peste limita";
        }
        else if (index >= this->vec_figuri.size()) {
            cout << "\ntot peste marimea vectorului dar iti facem un push_back\n";
            this->vec_figuri.push_back(x);
        }
        else
        {
            this->vec_figuri[index] = x;
        }
    }
};

//Meniu exclusiv pentru a reprezenta conceptele aplicate la acest proiect
void MENIU() {
    int optiune;
    while (true) {
        cout << "\n1)Gestiune<tip_figura>\n2)Gestiune<Trapeze*>\n3)Gestiune_redusa<tip_figura>\n";
        cin >> optiune;
        switch (optiune) {
        case 1:
            while (true) {
                cout << "Vom face Gestiune<Rectangle>";
                Gestiune<Rectangle> rekt;
                rekt.read();
                rekt.print();

                cout << "read rectangle to append:\n";
                Rectangle x;
                cin >> x;

                rekt.append(x);
                rekt.sort_by_lenght();
                rekt.print();

                rekt.clear();
                break;
            }
            break;
        case 2:
            while (true) {
                Gestiune<Trapeze*> trek;
                trek.read();
                trek.print();

                Trapeze x;
                cin >> x;

                trek += x;

                //operator [] overload
                cout << *trek[1];
                break;
            }
            break;
        case 3:
            while (true)
            {
                cout << "Vom Gestiona romburi";
                Gestiune_redusa<Rhombus> roarr;
                roarr.read();
                roarr.print();

                Rhombus r;
                cin >> r;

                roarr.insert(r, 1);
                cout << roarr[1];
                break;
            }
            break;
        }
        cout << "\nmai ramai?? 1)da/2)nu\n";
        int x;
        cin >> x;
        if (x == 2) {
            break;
        }
    }
}
int main() {
    
    /*
    Gestiune<Rectangle> g;
    g.read();
    g.print();
    
    g.sort_by_lenght();
    cout << g.total_surface_area();
    g.print();
    cout << g[1];
    */
    /*
    Gestiune<Trapeze*> t;
    t.read();
    Trapeze x;
    cin >> x;
    t += x;
    cout << *t[1];
    */
    /*
    Gestiune_redusa<Rhombus> roka;
    roka.read();
    roka.print();
    */
    MENIU();
}

#pragma region Point:

Point::Point()
{
    this->x = 0;
    this->y = 0;
}

Point::Point(float x, float y)
{
    this->x = x;
    this->y = y;
}

Point::Point(const Point& other)
{
    this->x = other.x;
    this->y = other.y;
}

Point::~Point()
{
    cout << "\ndestructor point \n";
}

float Point::getX()
{
    return x;
}

float Point::getY()
{
    return y;
}

void Point::setX(float x)
{
    this->x = x;
}

void Point::setY(float y)
{
    this->y = y;
}

ostream& operator<<(ostream& out, const Point& p)
{
    out << "(" << p.x << ',';
    out << p.y << ')' << '\n';
    return out;
}

istream& operator>>(istream& in, Point& p)
{
    cout << "Reading Point: \n";
    cout << "X coordinate:";
    in >> p.x;
    cout << "Y coordinate:";
    in >> p.y;
    return in;
}

Point& Point::operator=(const Point& other)
{
    x = other.x;
    y = other.y;
    return *this;
}

#pragma endregion

#pragma region Square:

Square::Square()
{
    this->sp.setX(0);
    this->sp.setY(0);
    this->length = 0;
    this->height = 0;
    this->valid = 0;
}

Square::Square(Point& sp, float length = 0, float height = 0)
{
    this->sp.setX(sp.getX());
    this->sp.setY(sp.getY());
    this->length = length;
    this->height = height;
    setValidValue();
}

Square::Square(const Square& other)
{
    this->sp = other.sp;
    this->length = other.length;
    this->height = other.height;
    this->valid = other.valid;
}

Square::~Square()
{
    cout << "\ndestructor Square\n";
}

void Square::setPoint(Point& sp)
{
    this->sp.setX(sp.getX());
    this->sp.setY(sp.getY());
}

void Square::setLength(float length)
{
    this->length = length;
}

void Square::setHeight(float height)
{
    this->height = height;
}

void Square::setValidValue()
{
    if (length < 0 || height < 0)
    {
        valid = 0;
    }
    else
    {
        valid = 1;
    }
}

void Square::increaseNumarFiguri()
{
    numarFiguri++;
}

int Square::getNumarFiguri()
{
    return numarFiguri;
}
int Square::getValidValue()
{
    return valid;
}

bool Square::isValidFigure()
{
    if (valid) return true;
    return false;
}

Point Square::getStartingPoint()
{
    return sp;
}

float Square::getLength()
{
    return length;
}

float Square::getHeight()
{
    return height;
}

float Square::calculateSurface()
{
    setValidValue();
    try
    {
        if (valid != 1) throw (1);
        return length * length;
    }
    catch (int)
    {
        cout << "\nError Cant calculate Area and Surface of an INVALID Figure\n";
        return -1;
    }
}

float Square::calculateVolume()
{
    setValidValue();
    try
    {
        if (valid != 1) throw(1);
        return length * length * height;
    }
    catch (int)
    {
        cout << "\nError Cant calculate Area and Surface of an INVALID Figure\n";
        return -1;
    }
}

Square& Square::operator=(const Square& other)
{
    if (this != &other)
    {
        sp = other.sp;
        length = other.length;
        height = other.height;
    }
    return *this;
}

ostream& operator<<(ostream& out, const Square& s)
{
    out << "\nShow Figure info: \n";
    out << "Starting Point:" << s.sp;
    out << "length:" << s.length << '\n';
    if (s.height != 0)
    {
        out << "height:" << s.height << '\n';
    }
    return out;
}

istream& operator>>(istream& in, Square& s)
{
    cout << "(Reading Figure) \n";
    in >> s.sp;
    int n;
    cout << "\n1)2d or 2)3d:";
    cin >> n;
    cout << '\n';
    switch (n)
    {
    case 1:
        break;
    case 2:
        cout << "Height:";
        in >> s.height;
    }
    cout << "Length:";
    in >> s.length;
    s.setValidValue();
    return in;
}

#pragma endregion


#pragma region Rectangle:

Rectangle::Rectangle() : Square()
{
    this->width = 0;
}

Rectangle::Rectangle(Point& sp, float length = 0, float width = 0, float height = 0) : Square(sp, length)
{
    this->width = width;
    this->height = height;
}

Rectangle::Rectangle(const Rectangle& other) : Square(other)
{
    this->width = other.width;
}

Rectangle::~Rectangle()
{
    cout << "\ndestructor Rectangle\n";
};

void Rectangle::setWidth(float width)
{
    this->width = width;
}

float Rectangle::getWidth()
{
    return width;
}

void Rectangle::setValidValue()
{
    this->Square::setValidValue();
    if (!valid)
    {
        return;
    }
    else if (width < 0)
    {
        valid = 0;
    }
    else
    {
        valid = 1;
    }
}

float Rectangle::calculateSurface()
{
    setValidValue();
    try
    {
        if (valid != 1) throw(1);
        return length * width;
    }
    catch (int)
    {
        cout << "\nError Cant calculate Area and Surface of an INVALID Figure\n";
        return -1;
    }
}

float Rectangle::calculateVolume()
{
    setValidValue();
    try
    {
        if (valid != 1) throw(1);
        return length * width * height;
    }
    catch (int)
    {
        cout << "\nError Cant calculate Area and Surface of an INVALID Figure\n";
        return -1;
    }
}


Rectangle& Rectangle::operator=(const Rectangle& other)
{
    if (this != &other)
    {
        this->Square::operator=(other);
        this->width = other.width;
    }
    return *this;
}
ostream& operator<<(ostream& out, const Rectangle& s)
{
    out << "\nShow Figure info: \n";
    out << "Starting Point:" << s.sp;
    out << "length:" << s.length << '\n';
    out << "width:" << s.width << '\n';
    if (s.height != 0)
    {
        out << "height:" << s.height << '\n';
    }
    return out;
}

istream& operator>>(istream& in, Rectangle& s)
{
    cout << "(Reading Figure) \n";
    in >> s.sp;
    int n;
    cout << "\n1)2d or 2)3d:";
    cin >> n;
    cout << '\n';
    switch (n)
    {
    case 1:
        break;
    case 2:
        cout << "Height:";
        in >> s.height;
    }
    cout << "Length:";
    in >> s.length;
    cout << "Width:";
    in >> s.width;
    s.setValidValue();
    return in;
}


#pragma endregion

#pragma region Rhombus:

Rhombus::Rhombus() : Square()
{
    this->ep.setX(0);
    this->ep.setY(0);
    this->alfaAngle = 0;
}

Rhombus::Rhombus(Point& sp, Point& ep, float length = 0, float height = 0) : Square(sp, length, height)
{
    this->ep = ep;
}

Rhombus::Rhombus(const Rhombus& other) : Square(other)
{
    this->ep = other.ep;
    this->alfaAngle = other.alfaAngle;
}

Rhombus::~Rhombus()
{
    cout << "\ndestructor Rhombus\n";
}

void Rhombus::setEndingPoint(Point& p)
{
    this->ep = p;
}

Point Rhombus::getEndingPoint()
{
    return ep;
}


void Rhombus::setValidValue()
{
    this->Square::setValidValue();
    float x = abs(calculateLength());
    if (!valid)
    {
        return;
    }
    else if (rround(x) == rround(length))
    {
        valid = 1;
    }
    else
    {
        valid = 0;
    }
}

void Rhombus::setAlfaAngle(float x)
{
    alfaAngle = x;
}

float Rhombus::calculateAlfa()
{
    float a = (ep.getX() - sp.getX());
    float b = (ep.getY() - sp.getY());
    float x = 2 * asin((ep.getY() - sp.getY()) / sqrt(a * a + b * b));
    return x;
}

float Rhombus::calculateLength()
{
    float a = abs((ep.getX() - sp.getX()));
    float b = abs((ep.getY() - sp.getY()));
    if (abs(b) <= abs(a))
    {
        float d = sqrt(a * a + b * b);
        float alfa = asin(b / d);
        float beta = (pi / 2) - alfa;
        float gamma = beta - alfa;
        float x = (b / cos(gamma));
        this->alfaAngle = 2 * alfa;
        return x;
    }
    return -43712;
}

float Rhombus::calculateSurface()
{
    setValidValue();
    try
    {
        if (valid != 1) throw(1);
        return sin(alfaAngle) * length * length;
    }
    catch (int)
    {
        cout << "\nError Cant calculate Area and Surface of an INVALID Figure\n";
        return -1;
    }
}

float Rhombus::calculateVolume()
{
    setValidValue();
    try
    {
        if (valid != 1) throw(1);
        return calculateSurface() * height;
    }
    catch (int)
    {
        cout << "\nError Cant calculate Area and Surface of an INVALID Figure\n";
        return -1;
    }
}

Rhombus& Rhombus::operator=(const Rhombus& other)
{
    if (this != &other)
    {
        this->Square::operator=(other);
        this->ep = other.ep;
        this->alfaAngle = other.alfaAngle;
    }
    return *this;
}

ostream& operator<<(ostream& out, const Rhombus& s)
{
    out << "\nShow Figure info: \n";
    out << "Starting Point: " << s.sp;
    out << "Ending Point: " << s.ep;
    out << "length:" << s.length << '\n';
    if (s.height != 0)
    {
        out << "height:" << s.height << '\n';
    }
    return out;
    out << "Sharp Angle:" << abs((s.alfaAngle * 180) / pi) << " deg" << '\n';
    return out;
}

istream& operator>>(istream& in, Rhombus& s)
{
    cout << "(Reading Figure) \n";
    cout << "Starting Point: \n\n";
    in >> s.sp;
    cout << "\nEnding Point:" << "\n\n";
    in >> s.ep;
    int n;
    cout << "\n1)2d or 2)3d:";
    cin >> n;
    cout << '\n';
    switch (n)
    {
    case 1:
        break;
    case 2:
        cout << "Height:";
        in >> s.height;
    }
    cout << "Length:";
    in >> s.length;
    s.setAlfaAngle(s.calculateAlfa());
    s.setValidValue();
    return in;
}

void Rhombus::setActualLength()
{
    length = calculateLength();
}

float Rhombus::getAlfaAngle()
{
    return alfaAngle;
}

#pragma endregion

#pragma region Parallelogram

Parallelogram::Parallelogram() : Rhombus(), Rectangle()
{

};

Parallelogram::Parallelogram(Point& sp, Point& ep, float l, float w, float h) : Square(sp, l, h), Rhombus(sp, ep, l, h),
Rectangle(sp, l, w, h)
{

}

Parallelogram::Parallelogram(const Parallelogram& other) : Rectangle(other), Square(other), Rhombus(other)
{

}

Parallelogram::~Parallelogram()
{
    cout << "\ndestructor Paralelogram\n";
}

float Parallelogram::calculateNormalWidth()
{
    if (length + sp.getX() <= ep.getX())
    {
        float b = ep.getY() - sp.getY();
        float a = ep.getX() - (length + sp.getX());
        if (a >= 0)
        {
            float x = sqrt(a * a + b * b);
            return x;
        }
    }
    else
    {
        float b = ep.getY() - sp.getY();
        float a = (length + sp.getX() - ep.getX());
        if (a >= 0)
        {
            float x = sqrt(a * a + b * b);
            return x;
        }
        return -123456;
    }
    return -123456;
}

void Parallelogram::setNormalWidth()
{
    width = calculateNormalWidth();
}

void Parallelogram::setValidValue()
{
    this->Rhombus::setValidValue();
    if (!valid)
    {
        return;
    }
    if (width != calculateNormalWidth())
    {
        valid = 0;
    }
    else
    {
        valid = 1;
    }
}

float Parallelogram::calculateSurface()
{
    setValidValue();
    try
    {
        if (valid != 1) throw(1);
        return (ep.getY() - sp.getY()) * length;
    }
    catch (int)
    {
        cout << "\nError Cant calculate Area and Surface of an INVALID Figure\n";
        return -1;
    }
}

float Parallelogram::calculateVolume()
{
    setValidValue();
    try
    {
        if (valid != 1) throw(1);
        return calculateSurface() * height;
    }
    catch (int)
    {
        cout << "\nError Cant calculate Area and Surface of an INVALID Figure\n";
        return -1;
    }
}

Parallelogram& Parallelogram::operator=(const Parallelogram& other)
{
    if (this != &other)
    {
        this->Rectangle::operator=(other);
        this->Rhombus::operator=(other);
    }
    return *this;
}

ostream& operator<<(ostream& out, const Parallelogram& s)
{
    out << "\nShow Figure info: \n";
    out << "Starting Point: " << s.sp;
    out << "Ending Point: " << s.ep;
    out << "Length:" << s.length << '\n';
    out << "Width:" << s.width << '\n';
    if (s.height != 0)
    {
        out << "height:" << s.height << '\n';
    }
    return out;
}

istream& operator>>(istream& in, Parallelogram& s)
{
    cout << "(Reading Figure) \n";
    cout << "Starting Point: \n\n";
    in >> s.sp;
    cout << "\nEnding Point:" << "\n\n";
    in >> s.ep;
    int n;
    cout << "\n1)2d or 2)3d:";
    cin >> n;
    cout << '\n';
    switch (n)
    {
    case 1:
        break;
    case 2:
        cout << "Height:";
        in >> s.height;
    }
    cout << "Length:";
    in >> s.length;
    cout << "Width:";
    in >> s.width;
    s.setValidValue();
    return in;
}
#pragma endregion


#pragma region Trapeze

Trapeze::Trapeze() :Parallelogram()
{
    this->secBase = 0;
    this->widthLeft = 0;
    this->widthRight = 0;
}

Trapeze::Trapeze(
    Point& sp,
    Point& ep,
    float length = 0,
    float height = 0,
    float secBase = 0,
    float widthRight = 0,
    float widthLeft = 0) : Parallelogram(sp, ep, length, widthRight, height)
{
    this->secBase = secBase;
    if (widthLeft)
    {
        this->widthLeft = widthRight;
    }
    else
    {
        this->widthLeft = widthLeft;
    }

}

Trapeze::Trapeze(const Trapeze& other) :Parallelogram(other)
{
    if (this != &other)
    {
        this->secBase = other.secBase;
        this->widthRight = other.widthRight;
        this->widthLeft = other.widthRight;
    }

}

Trapeze::~Trapeze()
{
    cout << "\ndestructor Trapez\n";
}

void Trapeze::setSecBase(float secBase)
{
    this->secBase = secBase;
}

float Trapeze::getSecBase()
{
    return secBase;
}

void Trapeze::calculateWidths() {
    if (ep.getX() < sp.getX()) {
        float a = min(ep.getX(), sp.getX() - length);
        float b = min(sp.getX(), ep.getX() + secBase);
        length = sp.getX() - a;
        secBase = b - ep.getX();
        float cat1w = ep.getY() - sp.getY();
        float catlw = ep.getX() - a;
        float catrw = sp.getX() - b;
        widthRight = sqrt(catrw * catrw + cat1w * cat1w);
        widthLeft = sqrt(catlw * catlw + cat1w * cat1w);

    }
    else {
        float a = max(ep.getX(), sp.getX() + length);
        float b = max(sp.getX(), ep.getX() - secBase);
        length = a - sp.getX();
        secBase = ep.getX() - b;
        float cat1w = ep.getY() - sp.getY();
        float catlw = b - sp.getX();
        float catrw = a - ep.getX();
        widthRight = sqrt(catrw * catrw + cat1w * cat1w);
        widthLeft = sqrt(catlw * catlw + cat1w * cat1w);
    }
}

float Trapeze::getWidthRight()
{
    return widthRight;
}
float Trapeze::getWidthLeft()
{
    return widthLeft;
}

float Trapeze::calculateSurface()
{
    setValidValue();
    try
    {
        if (valid != 1) throw(1);
        return (length + secBase) * abs(sp.getY() - ep.getY()) / 2;
    }
    catch (int)
    {
        cout << "\nError Cant calculate Area and Surface of an INVALID Figure\n";
        return -1;
    }
}

float Trapeze::calculateVolume()
{
    setValidValue();
    try
    {
        if (valid != 1) throw(1);
        return calculateSurface() * height;
    }
    catch (int)
    {
        cout << "\nError Cant calculate Area and Surface of an INVALID Figure\n";
        return -1;
    }
}

void Trapeze::setValidValue()
{
    //Posibil trebuie de revazut;
    this->Square::setValidValue();
    if (!valid)
    {
        return;
    }
    ///AICI
    float l = widthLeft;
    float r = widthRight;
    calculateWidths();
    if (l != widthLeft || r != widthRight) {
        valid = 0;
        widthLeft = l;
        widthRight = r;
    }
    else valid = 1;
    return;
}

Trapeze& Trapeze::operator=(const Trapeze& other)
{
    if (this != &other)
    {
        this->Parallelogram::operator=(other);
        this->secBase = other.secBase;
        this->widthRight = other.widthRight;
        this->widthLeft = other.widthLeft;
    }
    return *this;

}
ostream& operator<<(ostream& out, const Trapeze& s)
{
    out << "\nShow Figure info: \n";
    out << "Starting Point: " << s.sp;
    out << "Ending Point: " << s.ep;
    out << "Base 1:" << s.length << '\n';
    out << "Base 2:" << s.secBase << '\n';
    out << "Width on Right:" << s.widthRight << '\n';
    out << "Width on Left:" << s.widthLeft << '\n';
    if (s.height != 0)
    {
        out << "height:" << s.height << '\n';
    }
    return out;
}

istream& operator>>(istream& in, Trapeze& s)
{
    cout << "(Reading Figure) \n";
    cout << "Starting Point: \n\n";
    in >> s.sp;
    cout << "\nEnding Point:" << "\n\n";
    in >> s.ep;
    int n;
    cout << "\n1)2d or 2)3d:";
    cin >> n;
    cout << '\n';
    switch (n)
    {
    case 1:
        break;
    case 2:
        cout << "Height:";
        in >> s.height;
    }
    cout << "Base 1:";
    in >> s.length;
    cout << "Base 2:";
    in >> s.secBase;
    cout << "Width on Right:";
    in >> s.widthRight;
    cout << "Width on Left:";
    in >> s.widthLeft;
    return in;
}

#pragma endregion