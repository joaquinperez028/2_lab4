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
#include <ctime>

Sistema *Sistema::instance = nullptr;

Sistema::Sistema()
{
    this->usuarios = new OrderedDictionary();
    this->inmuebles = new OrderedDictionary();
    this->propRecordado = nullptr;
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

    return Status::OK;
}

Status Sistema::altaCasa(direccion direccion, float superficie, int anoConstruc, tipoTecho techo, bool propHorizontal)
{
    if (this->propRecordado == nullptr)
    {
        return Status::ERROR;
    }

    this->ultimoCodigoInmueble++;
    int codigo = this->ultimoCodigoInmueble;

    Casa *casa = propRecordado->crearCasa(direccion, superficie, codigo, techo, propHorizontal);

    this->inmuebles->add(new Integer(codigo), casa);

    return Status::OK;
}

Status Sistema::altaApto(direccion direccion, float superficie, int anoConstruc, int numPiso, bool ascensor, float gastosComunes)
{
    if (this->propRecordado == nullptr)
    {
        return Status::ERROR;
    }

    this->ultimoCodigoInmueble++;
    int codigo = this->ultimoCodigoInmueble;

    Apartamento *apartamento = propRecordado->crearApto(direccion, superficie, codigo, numPiso, ascensor, gastosComunes);

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

    return Status::OK;
}

ICollection *Sistema::listarPropietarios()
{
    return new List();
}

void Sistema::asociarPropietario(string)
{
    string nicknameProp = "ana_prop";
    string nicknameInmo = "inmo_central";

    Usuario *uProp = this->buscarPorNickname(nicknameProp);
    Usuario *uInmo = this->buscarPorNickname(nicknameInmo);

    Propietario *propietario = dynamic_cast<Propietario *>(uProp);
    Inmobiliaria *inmobiliaria = dynamic_cast<Inmobiliaria *>(uInmo);

    if (propietario == nullptr || inmobiliaria == nullptr)
    {
        return;
    }

    inmobiliaria->asociarPropietario(propietario);
    propietario->asociarInmobiliaria(inmobiliaria);
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

ICollection *Sistema::seleccionarInmobiliaria(string)
{
    return new List();
}

Status Sistema::altaPublicacion(int, tipoPublicacion, string, float)
{
    return Status::OK;
}

ICollection *Sistema::listarPublicaciones(string, float, float, opciones)
{
    return new List();
}

DTEspecifica Sistema::listarEspecifica(int)
{
    return DTEspecifica();
}

ICollection *Sistema::listarPropiedades()
{
    return new List();
}

DTInmueble Sistema::mostrarDetalle(int)
{
    return DTInmueble();
}

Status Sistema::eliminarInmueble(int)
{
    return Status::OK;
}

ICollection *Sistema::listarInmueblesRepresentados(string)
{
    return new List();
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
    Administra *adm = inmoSeleccionada->findAdministra(identificador);
    if (adm == NULL)
        return Status ::ERROR;

    fecha fechaHoy = obtenerFechaActual();

    if (adm->existePubAciva(tipo, fechaHoy))
        return Status ::ERROR;

    this->ultimoCodigoPub++;
    int codigo = this->ultimoCodigoPub;

    Publicacion *pub = adm->crearPublicacion(codigo, tipo, texto, precio, fechaHoy);

    int codigo = pub->getCodigo();
    Integer *key = new Integer(codigo);
    publicaciones->add(key, pub);

    return Status ::OK;
}
