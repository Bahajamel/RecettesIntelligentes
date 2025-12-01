#include "unite.h"

QString uniteToString(UNITE u)
{
    switch (u) {
    case UNITE::GRAMME: return "gramme";
    case UNITE::KILOGRAMME: return "kilogramme";
    case UNITE::LITRE: return "litre";
    case UNITE::MILLILITRE: return "millilitre";
    case UNITE::PIECE: return "piece";
    }
    return "gramme";
}

UNITE stringToUnite(const QString& s)
{
    if (s == "gramme") return UNITE::GRAMME;
    if (s == "kilogramme") return UNITE::KILOGRAMME;
    if (s == "litre") return UNITE::LITRE;
    if (s == "millilitre") return UNITE::MILLILITRE;
    if (s == "piece") return UNITE::PIECE;
    return UNITE::GRAMME;
}
