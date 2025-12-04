#include "databasemanager.h"

#include <utility>

class databasemanagerData : public QSharedData
{
public:
};

databasemanager::databasemanager()
    : data(new databasemanagerData)
{}

databasemanager::databasemanager(const databasemanager &rhs)
    : data{rhs.data}
{}

databasemanager::databasemanager(databasemanager &&rhs)
    : data{std::move(rhs.data)}
{}

databasemanager &databasemanager::operator=(const databasemanager &rhs)
{
    if (this != &rhs)
        data = rhs.data;
    return *this;
}

databasemanager &databasemanager::operator=(databasemanager &&rhs)
{
    if (this != &rhs)
        data = std::move(rhs.data);
    return *this;
}

databasemanager::~databasemanager() {}
