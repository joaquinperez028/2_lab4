#include <iostream>
#include "Factory.h"
#include "Datatypes/Status.h"

using namespace std;

int main()
{
    ISistema *sistema = Factory::getSistema();

    Status st = sistema->altaCliente("juan123", "Juan", "pass123", "juan@mail.com", "Perez", "12345678");
    if (st == Status::OK)
    {
        cout << "Alta cliente: OK" << endl;
    }
    else
    {
        cout << "Alta cliente: ERROR" << endl;
    }

    st = sistema->altaCliente("juan123", "Otro", "pass456", "otro@mail.com", "Garcia", "87654321");
    if (st == Status::ERROR)
    {
        cout << "Nickname duplicado detectado: OK" << endl;
    }
    else
    {
        cout << "Nickname duplicado: fallo la validacion" << endl;
    }

    st = sistema->altaPropietario("ana_prop", "Ana", "pass789", "ana@mail.com", "00112233", "Santander");
    if (st == Status::OK)
    {
        cout << "Alta propietario: OK" << endl;
    }
    else
    {
        cout << "Alta propietario: ERROR" << endl;
    }

    st = sistema->altaPropietario("juan123", "Otro", "pass", "otro@mail.com", "999", "Itau");
    if (st == Status::ERROR)
    {
        cout << "Nickname duplicado (propietario vs cliente): OK" << endl;
    }
    else
    {
        cout << "Nickname duplicado propietario: fallo la validacion" << endl;
    }

    st = sistema->altaPropietario("ana_prop", "Ana2", "pass2", "ana2@mail.com", "444", "BBVA");
    if (st == Status::ERROR)
    {
        cout << "Nickname duplicado (propietario): OK" << endl;
    }
    else
    {
        cout << "Nickname duplicado propietario: fallo la validacion" << endl;
    }

    return 0;
}
