#ifndef UNITE_H
#define UNITE_H

#include <QString>

enum class UNITE {
    GRAMME,
    KILOGRAMME,
    LITRE,
    MILLILITRE,
    PIECE
};

QString uniteToString(UNITE u);
UNITE stringToUnite(const QString& s);

#endif // UNITE_H
