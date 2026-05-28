// WRAPPER DE LA COLECCION DE USUARIOS
#ifndef COLUSUARIO_H
#define COLUSUARIO_H

#include "ICollection.h"
#include "UsuarioIterator.h"
#include "Usuario.h"

class ColUsuario {
    private:
        ICollection* col;
    public:
        ColUsuario();
        void add(Usuario* i);
        void remove(Usuario* i);
        bool member(Usuario* i);
        bool isEmpty();
        
        UsuarioIterator* getIterator(); 
    
};

#endif