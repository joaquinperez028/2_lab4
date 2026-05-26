#include "Cliente.h"

Cliente::Cliente(string nickname, string nombre, string contrasenia, string email, string apellido, string documento)
    : Usuario(nickname, nombre, contrasenia, email) {
    this->apellido = apellido;
    this->documento = documento;
}

Cliente::~Cliente() {}

string Cliente::getApellido() {
    return apellido;
}

string Cliente::getDocumento() {
    return documento;
}
