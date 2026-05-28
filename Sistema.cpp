#include "Sistema.h"
#include "Cliente.h"
#include "Propietario.h"

Sistema *Sistema::instance = nullptr;

Sistema::Sistema()
{
    this->colUsuarios = new ColUsuario();
}

Sistema::~Sistema()
{
    delete this->colUsuarios;
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
    UsuarioIterator *it = this->colUsuarios->getIterator();
    while (it->hasCurrent())
    {
        Usuario *u = it->getCurrent();
        if (u->getNickName() == nickname)
        {
            delete it;
            return Status::ERROR;
        }
        it->next();
    }
    delete it;
    return Status::OK;
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
    this->colUsuarios->add(cliente);

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
    this->colUsuarios->add(propietario);

    return Status::OK;
}

Status Sistema::altaCasa(direccion, float, int, tipoTecho, bool)
{
    return Status::OK;
}

Status Sistema::altaApto(direccion, float, int, int, bool, float)
{
    return Status::OK;
}

Status Sistema::altaInmobiliaria(string, string, string, direccion, string, string)
{
    return Status::OK;
}

DTprop Sistema::listarPropietarios()
{
    return DTprop();
}

void Sistema::asociarPropietario(string)
{
}

DTInmobiliaria Sistema::listarInmobiliarias()
{
    return DTInmobiliaria();
}

DTInmuebles Sistema::seleccionarInmobiliaria(string)
{
    return DTInmuebles();
}

Status Sistema::altaPublicacion(int, tipoPublicacion, string, float)
{
    return Status::OK;
}

DTPublicacion Sistema::listarPublicaciones(string, float, float, opciones)
{
    return DTPublicacion();
}

DTEspecifica Sistema::listarEspecifica(int)
{
    return DTEspecifica();
}

DTprop Sistema::listarPropiedades()
{
    return DTprop();
}

DTInmueble Sistema::mostrarDetalle(int)
{
    return DTInmueble();
}

Status Sistema::eliminarInmueble(int)
{
    return Status::OK;
}

DTInmueblesRep Sistema::listarInmueblesRepresentados(string)
{
    return DTInmueblesRep();
}

Status Sistema::altaAdministracion(int)
{
    return Status::OK;
}
