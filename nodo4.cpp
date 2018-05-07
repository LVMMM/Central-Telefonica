#ifndef NODO4_H_
#define NODO4_H_

#ifndef NULL
#define NULL 0
#endif

class Nodo4 {

    private:

        unsigned int peso;

        unsigned int estado;

        Central* adyacente;

        Nodo4* siguiente;

    public:

        /*
         * post: el Nodo resulta inicializado con el dato dado
         *       y sin un Nodo siguiente.
         */
        Nodo4(unsigned int nuevoPeso, unsigned int nuevoEstado, Central* nuevoAdyacente) {

            this->peso = nuevoPeso;
            this->siguiente = NULL;
            this->adyacente = nuevoAdyacente;
            this->estado = nuevoEstado;
        }

        /*
         * post: devuelve el valor del dato.
         */
        unsigned int obtenerPeso() {

            return this->peso;
        }

        unsigned int obtenerEstado() {
            return this->estado;
        }
        Central* obtenerAdyacente(){
            return this->adyacente;
        }

        Nodo4* obtenerSiguiente(){
            return this->siguiente;
        }

        /*
         * post: cambia el valor del dato.
         */
        void cambiarPeso(unsigned int nuevoPeso) {
            this->peso = nuevoPeso;
        }
        /*
         * post: cambia el siguiente Nodo por nuevoSiguiente.
         */
        void cambiarSiguiente(Nodo4* nuevoSiguiente) {

            this->siguiente = nuevoSiguiente;
        }
        void cambiarEstado(unsigned int nuevoEstado){
            this->estado = nuevoEstado;
        }
        void cambiarAdyacente(Central* nuevoAdyacente){
            this->adyacente = nuevoAdyacente;
        }
};


#endif /* NODO_H4_ */
