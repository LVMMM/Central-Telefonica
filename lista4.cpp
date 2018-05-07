
#include "lista4.h"

/*
 * Una Lista es una colección dinámica de elementos dispuestos en una secuencia.
 *
 * Define operaciones para agregar, remover, acceder y cambiar elementos
 * en cualquier posición.
 *
 * Tiene un cursor que permite recorrer todos los elementos secuencialmente.
 *
 */


Lista4::Lista4() {

    this->primero = NULL;
    this->tamanio = 0;
    this->cursor = NULL;
}

bool Lista4::estaVacia() {

    return (this->tamanio == 0);
}

unsigned int Lista4::contarElementos() {

    return this->tamanio;
}
/*void Lista4::agregar(T elemento) {

    this->agregar(elemento, this->tamanio + 1);
}*/


void Lista4::agregar(unsigned int nuevoPeso, unsigned int nuevoEstado,
                     Central* nuevaCentral, Central* nuevoAdyacente) {


        Nodo4* nuevo = new Nodo4(nuevoPeso, nuevoEstado,nuevaCentral, nuevoAdyacente);

        if (tamanio == 0) {

            nuevo->cambiarSiguiente(this->primero);
            this->primero = nuevo;

        } else {

            Nodo4* anterior = this->obtener(tamanio + 1);
            nuevo->cambiarSiguiente(anterior->obtenerSiguiente());
            anterior->cambiarSiguiente(nuevo);
        }

        this->tamanio++;

        // cualquier recorrido actual queda invalidado
        this->iniciarCursor();


}

Nodo4* Lista4::obtener(unsigned int posicion) {

    Nodo4* elemento;

    if ((posicion > 0) && (posicion <= this->tamanio)) {

        for (unsigned int i = 1; i < posicion; i++) {

        elemento = elemento->obtenerSiguiente();

        }
    }

    return elemento;
}

/*void Lista4::asignar(T elemento, unsigned int posicion) {

    if ((posicion > 0) && (posicion <= this->tamanio)) {

        this->obtenerNodo(posicion)->cambiarDato(elemento);
    }
}*/

void Lista4::remover(unsigned int posicion) {

    if ((posicion > 0) && (posicion <= this->tamanio)) {

        Nodo4* removido = obtener(posicion);

        if (posicion == 1) {

            //removido = this->primero;
            this->primero = primero->obtenerSiguiente();

        } else {

            Nodo4* anterior = this->obtener(posicion - 1);
            //removido = anterior->obtenerSiguiente();
            anterior->cambiarSiguiente(removido->obtenerSiguiente());
        }

        delete removido;
        this->tamanio--;

        /* cualquier recorrido actual queda invalidado */
        this->iniciarCursor();
    }
}

void Lista4::iniciarCursor() {

    this->cursor = NULL;
}

bool Lista4::avanzarCursor() {

    if (this->cursor == NULL) {

        this->cursor = this->primero;

    } else {

        this->cursor = this->cursor->obtenerSiguiente();
    }

    /* pudo avanzar si el cursor ahora apunta a un nodo */
    return (this->cursor != NULL);
}

Nodo4* Lista4::obtenerCursor() {

    Nodo4* elemento;

    if (this->cursor != NULL) {

        elemento = this->cursor->obtenerSiguiente();
    }

    return elemento;
}

Lista4::~Lista4() {

    while (this->primero != NULL) {

        Nodo4* aBorrar = this->primero;
        this->primero = this->primero->obtenerSiguiente();

        delete aBorrar;
    }
}

/*Nodo4* Lista4::obtenerNodo(unsigned int posicion) {

    Nodo4* actual = this->primero;
    for (unsigned int i = 1; i < posicion; i++) {

        actual = actual->obtenerSiguiente();
    }

    return actual;
}*/


