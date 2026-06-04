#include "Administra.h"
#include "ICollection/collections/List.h"
#include "Publicacion.h"
#include "ICollection/interfaces/IIterator.h"
#include "Datatypes/DTInfoInmueble.h"
#include "Inmueble.h"
#include "Inmobiliaria.h"  

using namespace std;

Administra ::Administra(Inmobiliaria *inmo, Inmueble *inm)
{
    this->inmobiliaria = inmo;
    this->inmueble = inm;
    this->publicaciones = new List();
    this->fechaInicio = fecha();
}

Inmobiliaria *Administra ::getInmobiliaria()
{
    return this->inmobiliaria;
}

Inmueble *Administra ::getInmueble()
{
    return this->inmueble;
}

void Administra ::agregarPublicacion(Publicacion *pub)
{
    publicaciones->add(pub);
}

Administra ::~Administra()
{
    delete this->publicaciones;
}

bool Administra ::existePubAciva(tipoPublicacion tipo, fecha fechaHoy)
{
    IIterator *it = publicaciones->getIterator();

    while (it->hasCurrent())
    {
        Publicacion *pub = (Publicacion *)it->getCurrent();
        if (pub->coincideTipo(tipo) && pub->getFecha() == fechaHoy && pub->esActiva())
            return true;
        it->next();
    }
    delete it;
    return false;
}

Publicacion *Administra ::crearPublicacion(int codigo, tipoPublicacion tipo, std::string texto, float precio,
                                           fecha fechaHoy)
{
    Publicacion *pub = new Publicacion(codigo, texto, precio, fechaHoy, tipo, this);
    agregarPublicacion(pub);
    return pub;
}

DTEspecifica *Administra::getAdministra()
{
    return this->inmueble->getInmueble();
}

DTAdministrados *Administra ::getDTAdministrados()
{
    DTInfoInmueble *dtInm = this->inmueble->getDTInfoInmueble();

    DTAdministrados *res = new DTAdministrados(
        this->fechaInicio,
        dtInm->getIdentificador(),
        dtInm->getDir());

    delete dtInm;
    return res;
}

ICollection* Administra::getPublicaciones()
{
    ICollection* copia = new List();

    IIterator* it = publicaciones->getIterator();

    while(it->hasCurrent())
    {
        copia->add(it->getCurrent());
        it->next();
    }

    delete it;

    return copia;
}

string Administra::getInmo() {
    return this->inmobiliaria->getNickName();
}