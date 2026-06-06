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

Status Sistema::altaCasa(Direccion direccion, float superficie, Fecha anoConstruc,
                         TipoTecho techo, bool propHorizontal)
{
    if (this->propRecordado == nullptr)
        return Status::ERROR;

    this->ultimoCodigoInmueble++;
    int codigo = this->ultimoCodigoInmueble;

    Casa *casa = propRecordado->crearCasa(direccion, superficie, anoConstruc,
                                          codigo, techo, propHorizontal);

    this->inmuebles->add(new Integer(codigo), casa);

    this->propRecordado = NULL;

    return Status::OK;
}

Status Sistema::altaApto(Direccion direccion, float superficie, Fecha anoConstruc,
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

    this->propRecordado = NULL;

    return Status::OK;
}

Status Sistema::altaInmobiliaria(string nickname, string nombre, string contrasenia,
                                 Direccion dir, string telefono, string url)
{
    Status st = this->revisarNickname(nickname);
    if (st != Status::OK)
    {
        return st;
    }

    Inmobiliaria *inmobiliaria = new Inmobiliaria(nickname, nombre, contrasenia, "",
                                                  dir, telefono, url);
    this->usuarios->add(new String(nickname.c_str()), inmobiliaria);

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

    Propietario *propietario = dynamic_cast<Propietario *>(this->buscarPorNickname(nickname));
    if (propietario == nullptr)
    {
        return;
    }

    this->inmoRecordada->asociarPropietario(propietario);
    propietario->asociarInmobiliaria(this->inmoRecordada);

    this->inmoRecordada = NULL;
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

ICollection *Sistema::listarPublicaciones(string, float, float, Opciones)
{
    return new List();
}

DTEspecifica *Sistema::listarEspecifica(int codigoPubli)
{

    Integer *key = new Integer(codigoPubli);
    Publicacion *pub = dynamic_cast<Publicacion *>(this->publicaciones->find(key));
    delete key;

    if (pub == nullptr)
        return nullptr;

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

    Integer *key = new Integer(identificador);
    Inmueble *inmu = dynamic_cast<Inmueble *>(this->inmuebles->find(key));
    delete key;

    if (inmu == nullptr)
        return nullptr;

    Direccion dir = inmu->getDireccion();
    Fecha anio = inmu->getAnoConstruc();
    int codigo = inmu->getIdentificador();
    TipoInmueble tipo = inmu->getTipo();

    return new DTInmueble(codigo, dir, anio, tipo);
}

Status Sistema::eliminarInmueble(int id)
{
    Integer *keyInmueble = new Integer(id);

    Inmueble *inmu = dynamic_cast<Inmueble *>(this->inmuebles->find(keyInmueble));

    if (inmu == nullptr)
    {
        delete keyInmueble;
        return Status::ERROR;
    }

    ICollection *colPublicaciones = inmu->prepararEliminacion();

    if (colPublicaciones != nullptr)
    {
        IIterator *it = colPublicaciones->getIterator();

        while (it->hasCurrent())
        {
            Publicacion *pub = dynamic_cast<Publicacion *>(it->getCurrent());

            it->next();

            if (pub != nullptr)
            {
                pub->eliminarAgendas();

                Integer *keyPub = new Integer(pub->getCodigo());
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

    Inmobiliaria *inmo = dynamic_cast<Inmobiliaria *>(
        this->buscarPorNickname(nickname));

    if (inmo == nullptr)
        return nullptr;

    this->inmoRecordada = inmo;

    return inmo->getInmueblesRepresentados();
}

Fecha Sistema ::obtenerFechaActual()
{
    time_t t = time(nullptr);
    tm *now = localtime(&t);

    return Fecha(
        now->tm_mday,
        now->tm_mon + 1,
        now->tm_year + 1900);
}

Status Sistema ::altaPublicacion(int identificador, TipoPublicacion tipo, string texto,
                                 float precio)
{
    if (inmoRecordada == NULL)
        return Status ::ERROR;

    Administra *adm = inmoRecordada->findAdministra(identificador);
    if (adm == NULL)
        this->inmoRecordada = NULL;
    return Status ::ERROR;

    Fecha fechaHoy = obtenerFechaActual();

    if (adm->existePubAciva(tipo, fechaHoy))
        this->inmoRecordada = NULL;
    return Status ::ERROR;

    this->ultimoCodigoPub++;
    int codigo = this->ultimoCodigoPub;

    Publicacion *pub = adm->crearPublicacion(codigo, tipo, texto, precio, fechaHoy);

    Integer *key = new Integer(pub->getCodigo());
    publicaciones->add(key, pub);

    this->inmoRecordada = NULL;
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

    this->inmoRecordada = inmo;

    ICollection *resultado = inmo->getAdministras();

    return resultado;
}

Status Sistema ::altaAdministracion(int identificador)
{
    Integer *key = new Integer(identificador);

    Inmueble *inmu = dynamic_cast<Inmueble *>(this->inmuebles->find(key));
    if (inmu == NULL)
        inmoRecordada = NULL;
    return Status ::ERROR;

    Fecha fechaActual = obtenerFechaActual();

    inmoRecordada->crearAdministra(inmu, fechaActual);

    inmoRecordada = NULL;
    inmu = NULL;

    return Status ::OK;
}