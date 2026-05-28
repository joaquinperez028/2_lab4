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

    return 0;
}
