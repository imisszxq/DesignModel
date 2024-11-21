#include <iostream>
#include <memory>
#include <string>
#include <list>
using namespace std;

class IObserver
{   
public:
    virtual ~IObserver() {}
    virtual void update(const string &messageFromSubject) = 0;
    virtual void removeMeFromList() = 0;
};


class ISubject
{
public:
    virtual ~ISubject() {}
    virtual void attach(shared_ptr<IObserver> observe) = 0;
    virtual void detach(shared_ptr<IObserver> observe) = 0;
    virtual void createMessage(const string &message) = 0;
    virtual void notify() = 0;
};

class subject : public ISubject
{
private:
    list<shared_ptr<IObserver>> mListObservers;
    string mMessage;

public:
    virtual ~subject() {}
    void attach(shared_ptr<IObserver> observe) override
    {
        mListObservers.push_back(observe);
    }
    void detach(shared_ptr<IObserver> observe) override
    {
        mListObservers.remove(observe);
    }
    void notify() override
    {
        for (auto &observe : mListObservers)
        {
            observe->update(mMessage);
        }
    }
    void createMessage(const string &message) override
    {
        mMessage = message;
        notify();
    }
};

class observer : public IObserver
{
private:
    string mMessageFromSubject;
    shared_ptr<ISubject> mSubject;
    static int mStaticNumber;
    

public:
    observer(shared_ptr<ISubject> subject) : mSubject(subject)
    {
        mSubject->attach(make_shared<observer>(*this));
    }
    virtual ~observer() {}
    void update(const string &messageFromSubject) override
    {
        mMessageFromSubject = messageFromSubject;
        cout << "observer"<< "get message: " << mMessageFromSubject << endl;
    }
    void removeMeFromList() override
    {
        mSubject.get()->detach(make_shared<observer>(*this));
    }
};
int observer::mStaticNumber = 2;

void clientCode()
{
    shared_ptr<ISubject> rSubject = shared_ptr<ISubject>(new subject());
    shared_ptr<IObserver> rObserver1 = shared_ptr<IObserver>(new observer(rSubject));
    shared_ptr<IObserver> rObserver2 = shared_ptr<IObserver>(new observer(rSubject));
    rSubject.get()->createMessage("hello");
    rObserver1.get()->removeMeFromList();
}
int main()
{
    clientCode();
    return 0;
}