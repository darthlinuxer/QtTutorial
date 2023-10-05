#include <tuple>
#include <string>
#include <QDebug>
#include "Tuples.h"


std::tuple<int, std::string, float> getTuple()
{
    int id = 1;
    std::string name = "John";
    float score = 98.5;

    return std::make_tuple(id, name, score);
}

void useTuple()
{
    auto data = getTuple();

    int id = std::get<0>(data);
    std::string name = std::get<1>(data);
    float score = std::get<2>(data);

    qInfo() << "Id: "<< id << " , name: " << name << ", score:" << score;
}
