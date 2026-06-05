#ifndef TIPOINMUEBLE_H
#define TIPOINMUEBLE_H

#include <iostream>

enum class TipoInmueble
{
    Casa,
    Apartamento
};

inline std::ostream &operator<<(std::ostream &os, TipoInmueble t)
{
    switch (t)
    {
    case TipoInmueble::Casa:
        os << "Casa";
        break;
    case TipoInmueble::Apartamento:
        os << "Apartamento";
        break;
    }
    return os;
}

#endif
