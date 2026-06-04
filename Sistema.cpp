#include "Sistema.h"
#include "Cliente.h"
#include "Propietario.h"
#include "Inmobiliaria.h"
#include "Administra.h"
#include "ICollection/collections/List.h"
#include "ICollection/interfaces/IIterator.h"
#include "ICollection/collections/OrderedDictionary.h"
#include "ICollection/Integer.h"
#include "ICollection/String.h"
#include "Casa.h"
#include "Apartamento.h"
#include "Datatypes/TipoTecho.h"
#include "Publicacion.h"
#include <ctime>

Sistema *Sistema::instance = nullptr;

Sistema::Sistema()
{
    this->usuarios = new OrderedDictionary();
    this->inmuebles = new OrderedDictionary();
    this->publicaciones = new OrderedDictionary();
    this->propRecordado = nullptr;
    this->inmoRecordada = nullptr;
    this->inmoSeleccionada = nullptr;
    this->ultimoCodigoPub = 0;
    this->ultimoCodigoInmueble = 0;
}

Sistema::~Sistema()
{
    delete this->usuarios;
    delete this->inmuebles;
}

Sistema *Sistema::getInstance()
{
    if (instance == nullptr)
    {
        instance = new Sistema();
    }
    return instance;
}

Status Sistema::revisarNickname(string nickname)
{
    String *key = new String(nickname.c_str());
    bool existe = this->usuarios->member(key);
    delete key;
    if (existe)
    {
        return Status::ERROR;
    }
    return Status::OK;
}

Usuario *Sistema::buscarPorNickname(string nickname)
{
    String *key = new String(nickname.c_str());
    ICollectible *val = this->usuarios->find(key);
    delete key;
    return dynamic_cast<Usuario *>(val);
}

Status Sistema::altaCliente(string nickname, string nombre, string contrasenia,
                            string email, string apellido, string documento)
{
    Status st = this->revisarNickname(nickname);
    if (st != Status::OK)
    {
        return st;
    }

    Cliente *cliente = new Cliente(nickname, nombre, contrasenia, email, apellido, documento);
    this->usuarios->add(new String(nickname.c_str()), cliente);

    return Status::OK;
}

Status Sistema::altaPropietario(string nickname, string nombre, string contrasenia,
                                string email, string numCuenta, string banco)
{
    Status st = this->revisarNickname(nickname);
    if (st != Status::OK)
    {
        return st;
    }

    Propietario *propietario = new Propietario(nickname, nombre, contrasenia, email,
                                               numCuenta, banco, "");
    this->usuarios->add(new String(nickname.c_str()), propietario);

    this->propRecordado = propietario;

    return Status::OK;
}

Status Sistema::altaCasa(direccion direccion, float superficie, fecha anoConstruc,
                         tipoTecho techo, bool propHorizontal)
{
    if (this->propRecordado == nullptr)
        return Status::ERROR;

    this->ultimoCodigoInmueble++;
    int codigo = this->ultimoCodigoInmueble;

    Casa *casa = propRecordado->crearCasa(direccion, superficie, anoConstruc,
                                          codigo, techo, propHorizontal);

    this->inmuebles->add(new Integer(codigo), casa);

    return Status::OK;
}

Status Sistema::altaApto(direccion direccion, float superficie, fecha anoConstruc,
                         int numPiso, bool ascensor, float gastosComunes)
{
    if (this->propRecordado == nullptr)
        return Status::ERROR;

    this->ultimoCodigoInmueble++;
    int codigo = this->ultimoCodigoInmueble;

    Apartamento *apartamento = propRecordado->crearApto(direccion, superficie,
                                                        anoConstruc, codigo,
                                                        numPiso, ascensor,
                                                        gastosComunes);

    this->inmuebles->add(new Integer(codigo), apartamento);

    return Status::OK;
}

Status Sistema::altaInmobiliaria(string nickname, string nombre, string contrasenia,
                                 direccion dir, string telefono, string url)
{
    Status st = this->revisarNickname(nickname);
    if (st != Status::OK)
    {
        return st;
    }

    Inmobiliaria *inmobiliaria = new Inmobiliaria(nickname, nombre, contrasenia, "",
                                                  dir, telefono, url);
    this->usuarios->add(new String(nickname.c_str()), inmobiliaria);

    // El sistema recuerda inmo (diagrama altaInmobiliaria)
    this->inmoRecordada = inmobiliaria;

    return Status::OK;
}

ICollection *Sistema::listarPropietarios()
{
    ICollection *lista = new List();
    IIterator *it = this->usuarios->getIterator();
    while (it->hasCurrent())
    {
        Usuario *u = dynamic_cast<Usuario *>(it->getCurrent());
        Propietario *p = dynamic_cast<Propietario *>(u);
        if (p != nullptr)
        {
            lista->add(p->getDTPropietario());
        }
        it->next();
    }
    delete it;
    return lista;
}

void Sistema::asociarPropietario(string nickname)
{
    if (this->inmoRecordada == nullptr)
    {
        return;
    }

    // mensaje 1: p := find(nickname) — visibilidad <<association>>
    Propietario *propietario = dynamic_cast<Propietario *>(this->buscarPorNickname(nickname));
    if (propietario == nullptr)
    {
        return;
    }

    // mensaje 2: inmo.asociarPropietario(p) — inmo es la recordada en altaInmobiliaria
    this->inmoRecordada->asociarPropietario(propietario);
    propietario->asociarInmobiliaria(this->inmoRecordada);
}

ICollection *Sistema::listarInmobiliarias()
{
    ICollection *resultado = new List();

    IIterator *it = this->usuarios->getIterator();

    while (it->hasCurrent())
    {
        Usuario *u = dynamic_cast<Usuario *>(it->getCurrent());
        Inmobiliaria *inmo = dynamic_cast<Inmobiliaria *>(u);

        if (inmo != nullptr)
        {
            resultado->add(inmo);
        }

        it->next();
    }

    delete it;
    return resultado;
}

ICollection *Sistema::listarPublicaciones(string, float, float, opciones)
{
    return new List();
}

DTEspecifica *Sistema::listarEspecifica(int codigoPubli)
{

    // mensaje 1: pub := find(codigoPubli) — visibilidad <<association>>
    // Sistema tiene IDictionary* publicaciones como atributo
    Integer *key = new Integer(codigoPubli);
    Publicacion *pub = dynamic_cast<Publicacion *>(this->publicaciones->find(key));
    delete key;

    if (pub == nullptr)
        return nullptr;

    // mensaje 2: dt := getDTEspecifica() — visibilidad <<local>>
    // pub se obtuvo del find, por eso es local
    return pub->getDTEspecifica();
}

ICollection *Sistema::listarPropiedades()
{
    ICollection *lista = new List();
    IIterator *it = this->inmuebles->getIterator();
    while (it->hasCurrent())
    {
        Inmueble *inm = dynamic_cast<Inmueble *>(it->getCurrent());
        if (inm != nullptr)
        {
            lista->add(inm->getDetalles());
        }
        it->next();
    }
    delete it;
    return lista;
}

DTInmueble *Sistema::mostrarDetalle(int identificador)
{

    // mensaje 1: inmu := find(Identificador) — visibilidad <<association>>
    // Sistema tiene IDictionary* inmuebles como atributo
    Integer *key = new Integer(identificador);
    Inmueble *inmu = dynamic_cast<Inmueble *>(this->inmuebles->find(key));
    delete key;

    if (inmu == nullptr)
        return nullptr;

    // mensajes 2 al 6 — visibilidad <<local>>
    // inmu se obtuvo del find, por eso es local
    // cada getter le pide al inmueble sus propios datos
    direccion dir = inmu->getDireccion();
    fecha anio = inmu->getAnoConstruc();
    int codigo = inmu->getIdentificador();
    tipoInmueble tipo = inmu->getTipo();

    return new DTInmueble(codigo, dir, anio, tipo);
}

Status Sistema::eliminarInmueble(int id)
{
    Integer* keyInmueble = new Integer(id);

    Inmueble* inmu = dynamic_cast<Inmueble*>(this->inmuebles->find(keyInmueble));

    if (inmu == nullptr)
    {
        delete keyInmueble;
        return Status::ERROR;
    }

    ICollection* colPublicaciones = inmu->prepararEliminacion();

    if (colPublicaciones != nullptr)
    {
        IIterator* it = colPublicaciones->getIterator();

        while (it->hasCurrent())
        {
            Publicacion* pub = dynamic_cast<Publicacion*>(it->getCurrent());

            it->next();

            if (pub != nullptr)
            {
                pub->eliminarAgendas();

                Integer* keyPub = new Integer(pub->getCodigo());
                this->publicaciones->remove(keyPub);
                delete keyPub;

                delete pub;
            }
        }

        delete it;
        delete colPublicaciones;
    }

    this->inmuebles->remove(keyInmueble);

    delete keyInmueble;
    delete inmu;

    return Status::OK;
}

ICollection *Sistema::listarInmueblesRepresentados(string nickname)
{

    // mensaje 1: inmo := find(nickname) — visibilidad <<association>>
    // usa buscarPorNickname que ya tienen implementado en Sistema
    Inmobiliaria *inmo = dynamic_cast<Inmobiliaria *>(
        this->buscarPorNickname(nickname));

    if (inmo == nullptr)
        return nullptr;

    // sistema recuerda inmo segun la nota del diagrama
    this->inmoSeleccionada = inmo;

    // mensaje 2: getInmueblesRepresentados() — visibilidad <<local>>
    // inmo se obtuvo del find, por eso es local
    return inmo->getInmueblesRepresentados();
}

Status Sistema::altaAdministracion(int)
{

    return Status::OK;
}

fecha Sistema ::obtenerFechaActual()
{
    time_t t = time(nullptr);
    tm *now = localtime(&t);

    return fecha(
        now->tm_mday,
        now->tm_mon + 1,
        now->tm_year + 1900);
}

Status Sistema ::altaPublicacion(int identificador, tipoPublicacion tipo, string texto,
                                 float precio)
{
    if (inmoSeleccionada == NULL)
        return Status ::ERROR;

    Administra *adm = inmoSeleccionada->findAdministra(identificador);
    if (adm == NULL)
        return Status ::ERROR;

    fecha fechaHoy = obtenerFechaActual();

    if (adm->existePubAciva(tipo, fechaHoy))
        return Status ::ERROR;

    this->ultimoCodigoPub++;
    int codigo = this->ultimoCodigoPub;

    Publicacion *pub = adm->crearPublicacion(codigo, tipo, texto, precio, fechaHoy);

    Integer *key = new Integer(pub->getCodigo());
    publicaciones->add(key, pub);

    return Status ::OK;
}

ICollection *Sistema ::seleccionarInmobiliaria(string nickname)
{

    String *key = new String(nickname.c_str());
    ICollectible *val = this->usuarios->find(key);
    delete key;

    Inmobiliaria *inmo = dynamic_cast<Inmobiliaria *>(val);
    if (inmo == NULL)
        return NULL;

    this->inmoSeleccionada = inmo;

    ICollection *resultado = inmo->getAdministras();

    return resultado;
}
