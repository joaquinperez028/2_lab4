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
#include "Datatypes/TipoPublicacion.h"
#include "Publicacion.h"
#include "AgendaVisita.h"
#include <ctime>
#include "Datatypes/DTPublicacion.h"

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
    limpiarInmuebles();
    limpiarPublicaciones();
    limpiarUsuarios();

    delete this->usuarios;
    delete this->inmuebles;
    delete this->publicaciones;
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
                                string email, string numCuenta, string banco,
                                string telefono)
{
    Status st = this->revisarNickname(nickname);
    if (st != Status::OK)
    {
        return st;
    }

    Propietario *propietario = new Propietario(nickname, nombre, contrasenia, email,
                                               numCuenta, banco, telefono);
    this->usuarios->add(new String(nickname.c_str()), propietario);

    this->propRecordado = propietario;

    return Status::OK;
}

Status Sistema::altaCasa(Direccion dir, float superficie, Fecha anoConstruc,
                         TipoTecho techo, bool propHorizontal)
{
    if (this->propRecordado == nullptr)
        return Status::ERROR;

    this->ultimoCodigoInmueble++;
    int codigo = this->ultimoCodigoInmueble;

    Casa *casa = propRecordado->crearCasa(dir, superficie, anoConstruc,
                                          codigo, techo, propHorizontal);

    this->inmuebles->add(new Integer(codigo), casa);

    return Status::OK;
}

Status Sistema::altaApto(Direccion dir, float superficie, Fecha anoConstruc,
                         int numPiso, bool ascensor, float gastosComunes)
{
    if (this->propRecordado == nullptr)
        return Status::ERROR;

    this->ultimoCodigoInmueble++;
    int codigo = this->ultimoCodigoInmueble;

    Apartamento *apartamento = propRecordado->crearApto(dir, superficie,
                                                        anoConstruc, codigo,
                                                        numPiso, ascensor,
                                                        gastosComunes);

    this->inmuebles->add(new Integer(codigo), apartamento);

    return Status::OK;
}

Status Sistema::altaInmobiliaria(string nickname, string nombre, string contrasenia,
                                 string email, Direccion dir, string telefono,
                                 string url)
{
    Status st = this->revisarNickname(nickname);
    if (st != Status::OK)
    {
        return st;
    }

    Inmobiliaria *inmobiliaria = new Inmobiliaria(nickname, nombre, contrasenia, email,
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

Status Sistema::seleccionarPropietario(string nickname)
{
    Propietario *propietario = dynamic_cast<Propietario *>(this->buscarPorNickname(nickname));
    if (propietario == nullptr)
        return Status::ERROR;

    this->propRecordado = propietario;
    return Status::OK;
}

int Sistema::obtenerUltimoCodigoInmueble()
{
    return this->ultimoCodigoInmueble;
}

void Sistema::asociarPropietario(string nickname)
{
    Inmobiliaria *inmo = this->inmoRecordada;
    if (inmo == nullptr)
        inmo = this->inmoSeleccionada;
    if (inmo == nullptr)
        return;

    Propietario *propietario = dynamic_cast<Propietario *>(this->buscarPorNickname(nickname));
    if (propietario == nullptr)
        return;

    inmo->asociarPropietario(propietario);
    propietario->asociarInmobiliaria(inmo);
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
            DTInmobiliaria *dt = inmo->getDTInmobiliaria();
            resultado->add(dt);
        }

        it->next();
    }

    delete it;
    return resultado;
}

ICollection *Sistema::listarPublicaciones(string tipo, float precioMin, float precioMax, Opciones interes)
{
    ICollection *resultado = new List();

    IIterator *it = this->publicaciones->getIterator();

    while (it->hasCurrent())
    {

        Publicacion *pub = dynamic_cast<Publicacion *>(it->getCurrent());

        if (pub == nullptr)
        {
            it->next();
            continue;
        }

        if (pub->esActiva())
        {

            if (tipo == "Venta" && !pub->coincideTipo(TipoPublicacion::Venta))
            {
                it->next();
                continue;
            }
            if (tipo == "Alquiler" && !pub->coincideTipo(TipoPublicacion::Alquiler))
            {
                it->next();
                continue;
            }

            if (pub->precioFranja(precioMin, precioMax))
            {

                if (pub->compararInteres(interes))
                {

                    DTPublicacion *dt = pub->getPublicacion();
                    resultado->add(dt);
                }
            }
        }

        it->next();
    }

    delete it;
    return resultado;
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
            lista->add(inm->getDTPropiedad());
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
    string nombrePropietario = "";
    if (inmu->getPropietario() != nullptr)
    {
        nombrePropietario = inmu->getPropietario()->getNombre();
    }

    return new DTInmueble(codigo, dir, anio, tipo, nombrePropietario);
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

    this->inmoSeleccionada = inmo;

    return inmo->getInmueblesRepresentados();
}

ICollection *Sistema::listarPropietariosRepresentados(string nickname)
{
    Inmobiliaria *inmo = dynamic_cast<Inmobiliaria *>(
        this->buscarPorNickname(nickname));

    if (inmo == nullptr)
        return nullptr;

    this->inmoSeleccionada = inmo;

    return inmo->getPropietariosRepresentados();
}

Status Sistema::altaAdministracion(int identificador)
{
    if (inmoSeleccionada == nullptr)
        return Status::ERROR;

    Integer *key = new Integer(identificador);
    Inmueble *inm = dynamic_cast<Inmueble *>(inmuebles->find(key));
    delete key;

    if (inm == nullptr)
        return Status::ERROR;

    Propietario *prop = inm->getPropietario();
    if (prop == NULL)
        return Status ::ERROR;

    Inmobiliaria *inmo = prop->getInmobiliaria();
    if (inmo != inmoSeleccionada)
        return Status ::ERROR;

    Fecha fechaActual = obtenerFechaActual();

    return inmoSeleccionada->crearAdministra(inm, fechaActual);
}

Status Sistema::altaAgendaVisita(string nicknameCliente, int codigoPublicacion, Fecha fecha, string formaContacto)
{
    Cliente *cliente = dynamic_cast<Cliente *>(buscarPorNickname(nicknameCliente));
    if (cliente == nullptr)
        return Status::ERROR;

    Integer *key = new Integer(codigoPublicacion);
    Publicacion *pub = dynamic_cast<Publicacion *>(publicaciones->find(key));
    delete key;

    if (pub == nullptr || !pub->esActiva())
        return Status::ERROR;

    AgendaVisita *agenda = new AgendaVisita(fecha, formaContacto, cliente, pub);
    pub->agregarAgenda(agenda);

    return Status::OK;
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
    if (inmoSeleccionada == NULL)
        return Status ::ERROR;

    Administra *adm = inmoSeleccionada->findAdministra(identificador);
    if (adm == NULL)
        return Status ::ERROR;

    Fecha fechaHoy = obtenerFechaActual();

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

void Sistema::limpiarInmuebles()
{
    IIterator *it = this->usuarios->getIterator();

    while (it->hasCurrent())
    {
        Propietario *p = dynamic_cast<Propietario *>(it->getCurrent());
        if (p != nullptr)
            p->limpiarInmuebles(this);
        it->next();
    }
    delete it;

    ICollection *pendientes = new List();
    IIterator *itInm = this->inmuebles->getIterator();

    while (itInm->hasCurrent())
    {
        pendientes->add(itInm->getCurrent());
        itInm->next();
    }
    delete itInm;

    IIterator *itRest = pendientes->getIterator();
    while (itRest->hasCurrent())
    {
        Inmueble *inm = dynamic_cast<Inmueble *>(itRest->getCurrent());
        if (inm != nullptr)
            eliminarInmueble(inm->getIdentificador());
        itRest->next();
    }
    delete itRest;
    delete pendientes;
}

void Sistema::limpiarPublicaciones()
{
    ICollection *pendientes = new List();
    IIterator *it = this->publicaciones->getIterator();

    while (it->hasCurrent())
    {
        pendientes->add(it->getCurrent());
        it->next();
    }
    delete it;

    IIterator *itPub = pendientes->getIterator();
    while (itPub->hasCurrent())
    {
        Publicacion *pub = dynamic_cast<Publicacion *>(itPub->getCurrent());
        itPub->next();

        if (pub != nullptr)
        {
            pub->eliminarAgendas();
            Integer *key = new Integer(pub->getCodigo());
            this->publicaciones->remove(key);
            delete key;
            delete pub;
        }
    }
    delete itPub;
    delete pendientes;
}

void Sistema::limpiarUsuarios()
{
    IIterator *it = this->usuarios->getIterator();
    while (it->hasCurrent())
    {
        Propietario *p = dynamic_cast<Propietario *>(it->getCurrent());
        if (p != nullptr)
            p->desasociarInmobiliaria();
        it->next();
    }
    delete it;

    Propietario *propietario = nullptr;
    do
    {
        propietario = nullptr;
        it = this->usuarios->getIterator();
        while (it->hasCurrent())
        {
            propietario = dynamic_cast<Propietario *>(it->getCurrent());
            if (propietario != nullptr)
                break;
            it->next();
        }
        delete it;

        if (propietario != nullptr)
        {
            String *key = new String(propietario->getNickName().c_str());
            this->usuarios->remove(key);
            delete key;
            delete propietario;
        }
    } while (propietario != nullptr);

    Cliente *cliente = nullptr;
    do
    {
        cliente = nullptr;
        it = this->usuarios->getIterator();
        while (it->hasCurrent())
        {
            cliente = dynamic_cast<Cliente *>(it->getCurrent());
            if (cliente != nullptr)
                break;
            it->next();
        }
        delete it;

        if (cliente != nullptr)
        {
            String *key = new String(cliente->getNickName().c_str());
            this->usuarios->remove(key);
            delete key;
            delete cliente;
        }
    } while (cliente != nullptr);

    Inmobiliaria *inmobiliaria = nullptr;
    do
    {
        inmobiliaria = nullptr;
        it = this->usuarios->getIterator();
        while (it->hasCurrent())
        {
            inmobiliaria = dynamic_cast<Inmobiliaria *>(it->getCurrent());
            if (inmobiliaria != nullptr)
                break;
            it->next();
        }
        delete it;

        if (inmobiliaria != nullptr)
        {
            String *key = new String(inmobiliaria->getNickName().c_str());
            this->usuarios->remove(key);
            delete key;
            delete inmobiliaria;
        }
    } while (inmobiliaria != nullptr);

    this->propRecordado = nullptr;
    this->inmoRecordada = nullptr;
    this->inmoSeleccionada = nullptr;
    this->ultimoCodigoInmueble = 0;
    this->ultimoCodigoPub = 0;
}
