#include "Sistema.h"
#include "Cliente.h"
#include "Propietario.h"
#include "Inmobiliaria.h"
#include "ICollection/collections/List.h"
#include "ICollection/interfaces/IIterator.h"
#include "ICollection/collections/OrderedDictionary.h"
#include "ICollection/Integer.h"
#include "ICollection/String.h"
#include "Casa.h"
#include "Apartamento.h"
#include "datatypes/tipoTecho.h"

Sistema *Sistema::instance = nullptr;

Sistema::Sistema()
{
    this->colUsuarios = new ColUsuario(); //this->usuarios = new OrderedDictionary();
    this->inmuebles = new OrderedDictionary();
    this->propRecordado = nullptr;
    this->ultimoCodigoInmueble = 0;
}

Sistema::~Sistema()
{
    delete this->colUsuarios; //cambiar por: delete this->usuarios;
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

Status Sistema::revisarNickname(string nickname) //revisar porque al usar dictionary se hace diferente
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

Usuario *Sistema::buscarPorNickname(string nickname) //revisar porque al usar dictionary se hace diferente
{
    UsuarioIterator *it = this->colUsuarios->getIterator();
    while (it->hasCurrent())
    {
        Usuario *u = it->getCurrent();
        if (u->getNickName() == nickname)
        {
            delete it;
            return u;
        }
        it->next();
    }
    delete it;
    return nullptr;
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
    this->colUsuarios->add(cliente); //this->usuarios->add(new String(nickname.c_str()), cliente);
                                        //como ahora usamo dictionary hay que hacer y añadir la clave
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
    this->colUsuarios->add(propietario); //this->usuarios->add(new String(nickname.c_str()), propietario);
                                            //como ahora usamo dictionary hay que hacer y añadir la clave
    return Status::OK;
}


Status Sistema::altaCasa(direccion direccion, float superficie, int anoConstruc, tipoTecho TipoTecho, bool propHorizontal)
{   
   if (this->propRecordado == nullptr) {
        return Status::ERROR;
    }

    this->ultimoCodigoInmueble++;
    int codigo = this->ultimoCodigoInmueble;

    Casa* casa = propRecordado->crearCasa(direccion, superficie, codigo, TipoTecho, propHorizontal);

    inmuebles->add(casa);

    return Status::OK;
}

Status Sistema::altaApto(direccion direccion, float superficie, int numPiso, bool ascensor, float gastosComunes)
{   
    if (this->propRecordado == nullptr) {
        return Status::ERROR;
    }

    this->ultimoCodigoInmueble++;
    int codigo = this->ultimoCodigoInmueble;

    Apartamento* apartamento = propRecordado->crearApto(direccion, superficie, codigo, numPiso, ascensor, gastosComunes);
    
    inmuebles->add(apartamento);

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
<<<<<<< HEAD
                                                  dir, telefono, url);
    this->colUsuarios->add(inmobiliaria);
=======
                                                    dir, telefono, url);
    this->colUsuarios->add(inmobiliaria); //cambiar lo mismo que antes, ahora ya no tenemos colUsuarios y agregar la clave
>>>>>>> 5ff080a1c280291fce3ac0e738da22b7dcad6d93

    return Status::OK;
}

DTprop Sistema::listarPropietarios()
{
    return DTprop();
}

void Sistema::asociarPropietario(string)
{
    // hardcoded hasta implementar listarPropietarios / listarInmobiliarias
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

ICollection* Sistema::listarInmobiliarias() {
    ICollection* resultado = new List();
 
    // mensaje 1* [foreach && esInmobiliaria()] — visibilidad <<association>>
    IIterator* it = this->usuarios->getIterator();
 
    while (it->hasCurrent()) {
        // recupera cada usuario de la coleccion generica
        Usuario* u = dynamic_cast<Usuario*>(it->getCurrent());
 
        // filtra solo los que son inmobiliarias — condicion del foreach
        if (u->esInmobiliaria()) {
 
            // casteo seguro porque ya verificamos con esInmobiliaria()
            Inmobiliaria* i = dynamic_cast<Inmobiliaria*>(u);
 
            // mensaje 2* getDTInmobiliaria() — visibilidad <<association>>
            DTInmobiliaria* dt = i->getDTInmobiliaria();
 
            resultado->add(dt);
        }
 
        it->next();
    }
 
    delete it;
    return resultado;
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

Status Sistema ::altaPublicacion(int identificador, tipoPublicacion tipo, string texto,
                                 float precio)
{
    Administra *adm = inmoSeleccionada->findAdministra(identificador);
    if (adm == NULL)
        return Status ::ERROR;

    fecha fechaHoy = obtenerFechaActual();

    if (adm->existePubActiva(tipo, fechaHoy))
        return Status ::ERROR;

    this->ultimoCodigo++;
    int codigo = this->ultimoCodigo;

    adm->crearPublicacion(codigo, tipo, texto, precio, fechaHoy);
    return Status ::OK;
}