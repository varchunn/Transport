#include <iostream>
#include <memory>

using namespace std;

class Transport 
{
public:
    virtual void deliver() const = 0;
    virtual ~Transport() {}
};


class Truck : public Transport 
{
public:
    void deliver() const override 
    {
        cout << "Доставка вантажу вантажівкою по дорозі." << endl;
    }
};

class Ship : public Transport 
{
public:
    void deliver() const override 
    {
        cout << "Доставка вантажу судном по морю." << endl;
    }
};

class Plane : public Transport 
{
public:
    void deliver() const override 
    {
        cout << "Доставка вантажу літаком по повітрю." << endl;
    }
};

class Logistics 
{
public:
    virtual unique_ptr<Transport> createTransport() const = 0;
    virtual ~Logistics() {}
};

class RoadLogistics : public Logistics 
{
public:
    unique_ptr<Transport> createTransport() const override {
        return make_unique<Truck>();
    }
};

class SeaLogistics : public Logistics 
{
public:
    unique_ptr<Transport> createTransport() const override {
        return make_unique<Ship>();
    }
};

class AirLogistics : public Logistics 
{
public:
    unique_ptr<Transport> createTransport() const override {
        return make_unique<Plane>();
    }
};

void clientCode(const Logistics &logistics)
{
    unique_ptr<Transport> transport = logistics.createTransport();
    transport->deliver();
}

int main() {
    RoadLogistics roadLogistics;
    SeaLogistics seaLogistics;
    AirLogistics airLogistics;

    cout << "=== Тест фабрики дорожніх перевезень ===" << endl;
    clientCode(roadLogistics);

    cout << "\n=== Тест фабрики морських перевезень ===" << endl;
    clientCode(seaLogistics);

    cout << "\n=== Тест фабрики повітряних перевезень ===" << endl;
    clientCode(airLogistics);

    return 0;
}
