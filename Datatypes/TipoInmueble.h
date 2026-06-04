#ifndef TIPOINMUEBLE_H
#define TIPOINMUEBLE_H

#include <iostream>

enum class tipoInmueble
{
    Casa,
    Apartamento
};

inline std::ostream &operator<<(std::ostream &os, tipoInmueble t)
{
    switch (t)
    {
    case tipoInmueble::Casa:
        os << "Casa";
        break;
    case tipoInmueble::Apartamento:
        os << "Apartamento";
        break;
    }
    return os;
}

#endif
