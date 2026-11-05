#ifndef LISTARRAY_H
#define LISTARRAY_H

#include <ostream>
#include <stdexcept>
#include "List.h"

template <typename T>
class ListArray : public List<T> {
    private:
        // Atributos privados
        T* arr;  //T* arr: Es un puntero que señala al inicio del bloque de memoria contigua donde se guardarán los elementos de tu lista. Al usar T, puede guardar cualquier tipo de dato.
        int max;  //int max: Controla la capacidad total que tiene el array en un momento dado.
        int n; //int n: Lleva la cuenta exacta de cuántos elementos reales has insertado en la lista.
        static const int MINSIZE = 2;  //static const int MINSIZE = 2: Define el tamaño mínimo inicial que tendrá el array de forma constante.

        // Método privado para redimensionar
        void resize(int new_size) {  //resize(int new_size): Este método privado ejecuta paso a paso la estrategia exigida: crea un array nuevo con el tamaño new_size usando new, transfiere los datos del array viejo al nuevo mediante un bucle, elimina el array viejo con delete[] para evitar fugas de memoria, y finalmente reasigna el puntero arr y el valor max.

            T* new_arr = new T[new_size]; // 1. Crear nuevo array dinámico
            for (int i = 0; i < n; ++i) { // 2. Copiar el contenido
                new_arr[i] = arr[i];
            }
            delete[] arr;                 // 3. Liberar memoria del array actual
            arr = new_arr;                // 4. Actualizar puntero
            max = new_size;               // 5. Actualizar max
        }

    public:
        // Constructor
        ListArray() {  //ListArray() (Constructor): Inicializa la clase reservando la memoria dinámica inicial (un array del tamaño MINSIZE), y establece el contador de elementos n a 0
            arr = new T[MINSIZE];
            max = MINSIZE;
            n = 0;
        }

        // Destructor
        ~ListArray() override {   //~ListArray() (Destructor): Cuando la lista se destruye o el programa termina, se ejecuta automáticamente la instrucción delete[] arr para devolver la memoria reservada al sistema operativo.
            delete[] arr;
        }

        // Sobrecarga del operador []
        T operator[](int pos) {    //T operator[](int pos): Permite acceder a los elementos de tu lista usando corchetes, igual que en un array normal (ej. miLista[2]). Incluye una comprobación de seguridad que lanza un error std::out_of_range si intentas acceder a una posición fuera de los límites de 0 a n-1.
            if (pos < 0 || pos >= n) { 
                throw std::out_of_range("Posición no válida");
            }
            return arr[pos];
        }

        // Sobrecarga del operador << (friend)
        friend std::ostream& operator<<(std::ostream &out, ListArray<T> &list) {  //friend std::ostream& operator<<: Permite imprimir toda la lista directamente con cout << miLista. Al ser friend, es una función externa que tiene permiso para acceder a los atributos privados (arr y n) de la clase.
            out << "[";
            for (int i = 0; i < list.n; ++i) {
                out << list.arr[i] << " ";
            }
            out << "]";
            return out;
        }
	// Busca un elemento y devuelve su posición (o -1 si no existe)
        int search(T val) const override {
            for (int i = 0; i < n; i++) {
                if (arr[i] == val) {
                    return i; // Elemento encontrado
                }
            }
            return -1; // Elemento no encontrado
        }

       // Devuelve el número de elementos actuales en la lista
        int size() const override {
            return n;
        }
	bool empty() const override {
		return n == 0;
	}

        // Obtiene el elemento de una posición concreta
        T get(int pos) const override {
            if (pos < 0 || pos >= n) {
                throw std::out_of_range("Posición fuera de rango");
            }
            return arr[pos];
        }

        // Inserta un elemento en una posición específica
        void insert(int pos, T val) override {
            if (pos < 0 || pos > n) {
                throw std::out_of_range("Posición de inserción no válida");
            }
            
            // Si el array está lleno, duplicamos su capacidad
            if (n == max) {
                resize(max * 2); 
            }
            
            // Tarea de mantenimiento: Desplazar elementos a la derecha para hacer hueco
            // y garantizar la contigüidad
            for (int i = n; i > pos; i--) {
                arr[i] = arr[i - 1];
            }
            
            arr[pos] = val;
            n++;
        }

        // Añade un elemento al final de la lista
        void append(T val) override {
            insert(n, val); // Reutilizamos la lógica de insert
        }

        // Añade un elemento al principio de la lista
        void prepend(T val) override {
            insert(0, val); // Reutilizamos la lógica de insert[cite: 6]
        }

        // Elimina y devuelve el elemento de una posición
        T remove(int pos) override {
            if (pos < 0 || pos >= n) {
                throw std::out_of_range("Posición de borrado no válida");
            }
            
            T removed_val = arr[pos];
            
            // Tarea de mantenimiento: Desplazar elementos a la izquierda para tapar
            // el hueco y garantizar la contigüidad[cite: 9]
            for (int i = pos; i < n - 1; i++) {
                arr[i] = arr[i + 1];
            }
            n--;
            
            // Si el array está demasiado vacío (ej. menos del 25% de ocupación)
            // reducimos su tamaño a la mitad, respetando el MINSIZE[cite: 6]
            if (n > 0 && n <= max / 4 && max / 2 >= MINSIZE) {
                resize(max / 2);
            }
            
            return removed_val;
        }
};

#endif

