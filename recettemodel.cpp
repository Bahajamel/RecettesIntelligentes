#include "recettemodel.h"

#include <utility>

class recetteModelData : public QSharedData
{
public:
};

recetteModel::recetteModel()
    : data(new recetteModelData)
{}

recetteModel::recetteModel(const recetteModel &rhs)
    : data{rhs.data}
{}

recetteModel::recetteModel(recetteModel &&rhs)
    : data{std::move(rhs.data)}
{}

recetteModel &recetteModel::operator=(const recetteModel &rhs)
{
    if (this != &rhs)
        data = rhs.data;
    return *this;
}

recetteModel &recetteModel::operator=(recetteModel &&rhs)
{
    if (this != &rhs)
        data = std::move(rhs.data);
    return *this;
}

recetteModel::~recetteModel() {}
