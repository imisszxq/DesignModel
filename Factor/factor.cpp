#include <iostream>
#include <memory>
#include <string>
using namespace std;

class Product
{
public:
    virtual ~Product() {}
    virtual string Opertion() const = 0;
};
class concreteProductA : public Product
{
public:
    string Opertion() const override
    {
        return "concreteProductA";
    }
};
class concreteProductB : public Product
{
public:
    string Opertion() const override
    {
        return "concreteProductB";
    }
};

class Creator
{
public:
    virtual ~Creator() {}
    virtual Product *FactoryMethod() const = 0;
    string SomeOpertion() const
    {
        Product *product = this->FactoryMethod();
        string result = product->Opertion();
        delete product;
        return result;
    }
};

class ConcreteCreatorA : public Creator
{
public:
    Product *FactoryMethod() const override
    {
        return new concreteProductA();
    }
};

class ConcreteCreatorB : public Creator
{
public:
    Product *FactoryMethod() const override
    {
        return new concreteProductB();
    }
};
void ClientCode(const Creator& creator){
    cout<<creator.SomeOpertion()<<endl;
}
int main(){
    Creator* creator =new ConcreteCreatorA();
    ClientCode(*creator);
    cout<<endl;
    creator=new ConcreteCreatorB();
    ClientCode(*creator);
    cout<<endl;
    delete creator;

    return 0;
}