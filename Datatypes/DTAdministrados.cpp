#include "DTAdministrados.h"

DTAdministrados ::DTAdministrados(Fecha fechaComienzo, int identificador, Direccion dir)
{
    this->fechaComienzo = fechaComienzo;
    this->identificador = identificador;
    this->dir = dir;
}

Fecha DTAdministrados ::getFechaComienzo()
{
    return this->fechaComienzo;
}

int DTAdministrados ::getIdentificador()
{
    return this->identificador;
}

Direccion DTAdministrados ::getDir()
{
    return this->dir;
}

std::ostream &operator<<(std::ostream &os, const DTAdministrados &dt)
{
    os << "Id: " << dt.identificador
       << " | Inicio administracion: " << dt.fechaComienzo
       << " | Direccion: " << dt.dir;
    return os;
}
