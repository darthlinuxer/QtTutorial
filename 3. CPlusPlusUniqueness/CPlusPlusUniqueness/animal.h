#ifndef ANIMAL_H
#define ANIMAL_H

#include "animalstatus.h"
#include <QObject>
#include <iostream>
#include <QTimer>

using namespace std;

//Pay attenting to this automatically created class... it has a funny constructor where it added
//a pointer to another QObject .. on the implementation side-> Animal::Animal(string name, QObject *parent): QObject(parent)
//It calls the constructor of QObject with a parent argument
//Note:
//Automatically created classes can be created if you click on Project with right button and select Add New -> Class
//A popup window will appear where you can select the base class..

//Why to call QObject with parent ?
//If you delete the parent class, everything that is linked to it will be deleted automatically
class Animal : public QObject
{
    Q_OBJECT

    std::string _name;
    int _metersWalked = 0;
    int _hungryLevel = 0;
    int _happyLevel=100;
    int _thirst=0;

    int hungryLevel() const;
    void increaseHungryLevel(int increaseBy);

    int happyLevel() const;
    void decreaseHappyLevel(int decreaseBy);

    int thirst() const;
    void increaseThirst(int increaseBy);

    QTimer _timer;

    //properties can be created by putting _ in front of the name.
    //If you do this and refactor the code Qt will automatically create the QPROPERTY along with
    //Getters, Setters and Notification signals for the property
    AnimalStatus m_animalStatus = AnimalStatus::alive; //this is an enum
    Q_PROPERTY(AnimalStatus animalStatus READ animalStatus WRITE setAnimalStatus NOTIFY animalStatusChanged FINAL)

public:
    explicit Animal(std::string name, QObject *parent = nullptr);
    ~Animal();

    void Walk();
    void Walk(int meters);
    std::string GetName();

    void Sleep();
    void Eat();
    void Play();
    void DrinkWater();

    // the method below is a pure virtual method which will
    //transform this to an Abstract class that cannot be instantiated.
    virtual void MakeSound()=0;

    AnimalStatus animalStatus() const; //this is like C# GET
    void setAnimalStatus(AnimalStatus newAnimalStatus); //this is like C# Set

    /*
     * The inline keyword in C++ is used as a hint to the compiler that it should attempt to generate code
     * (inline code) for a function directly in place, rather than generating code to call the function
     * where it is defined.
     * However, it’s important to note that inline is just a hint to the compiler. The compiler is not obligated
     * to inline the function and may choose not to do so for various reasons (for example, if the function
     * is too complex).
     * */
    inline std::string AnimalStatusToString(AnimalStatus status)
    {
        switch (status)
        {
        case alive: return "alive";
        case hungry: return "hungry";
        case sleeping: return "sleeping";
        case tired: return "tired";
        case happy: return "happy";
        case sad: return "sad";
        case thirsty: return "thirsty";
        case dead: return "dead";
        default: return "unknown";
        }
    }

signals:
    void animalStatusChanged(Animal* animal);
    void animalDied();

public slots:
    void DecreaseHappinessOnIdleTime();

};

#endif // ANIMAL_H
