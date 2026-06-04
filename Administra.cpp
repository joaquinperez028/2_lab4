#include "Administra.h"
#include "ICollection/collections/List.h"
#include "Publicacion.h"
#include "ICollection/interfaces/IIterator.h"
#include "datatypes/DTInfoInmueble.h"
#include "Inmueble.h"

using namespace std;

Administra ::Administra(Inmobiliaria *inmo, Inmueble *inm)
{

    this->inmobiliaria = inmo;
    this->inmueble = inm;

    this->publicaciones = new List();
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

Administra ::~Administra() {

    delete this->publicaciones;

};

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
    return false;
}

Publicacion *Administra ::crearPublicacion(int codigo, tipoPublicacion tipo, std::string texto, float precio,
                                           fecha fechaHoy)
{
    Publicacion *pub = new Publicacion(codigo, texto, precio, fechaHoy, tipo, this);
    agregarPublicacion(pub);
    return pub;
}

// Corresponde al mensaje 2.1: getAdministra():DTEspecifica
// Delega a Inmueble para que construya su propio DTEspecifica
DTEspecifica *Administra::getAdministra()
{
    return this->inmueble->getInmueble(); // mensaje 2.1.1
}

DTAdministrados *Administra ::getDTAdministrados()
{

    DTInfoInmueble *dtInm = this->inmueble->getDTInfoInmueble();

    DTAdministrados *res = new DTAdministrados(

        this->fechaInicio,
        dtInm->getIdentificador(),
        dtInm->getDir()

    );
    delete dtInm;
    return res;
}

ICollection* Administra::getPublicaciones() {
    return this->publicaciones;
}

string Administra::getInmo() {
    return this->inmobiliaria->getNickName();
}