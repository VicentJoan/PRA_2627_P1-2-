#ifndef LISTLINKED_H
#define LISTLINKED_H

#include <ostream>
#include <stdexcept>
#include "List.h"
#include "Node.h"

template <typename T>
class ListLinked : public List<T> {
    private:
        Node<T>* first; // Puntero al primer nodo de la lista
        int n;          // Número de elementos en la lista

    public:
        // Constructor: inicializa una lista vacía
        ListLinked() {
            first = nullptr;
            n = 0;
        }

        // Destructor: libera la memoria de todos los nodos
        ~ListLinked() override {
            while (first != nullptr) {            //guarda dirección al siguiente nodo.Elimina el actual.Y avanza first al siguiente nodo.Hasta liberar
                Node<T>* aux = first->next;
                delete first;
                first = aux;
            }
        }

        // Sobrecarga del operador [] para acceder a elementos por posición
        T operator[](int pos) {
            if (pos < 0 || pos >= n) {
                throw std::out_of_range("Posición fuera de rango");	//Comprueba posición.Si es valida avanza hasta el nodo y devuelve el valor
            }
            Node<T>* aux = first;
            for (int i = 0; i < pos; i++) {
                aux = aux->next;
            }
            return aux->data;
        }

        // Imprime la lista por pantalla
        friend std::ostream& operator<<(std::ostream &out, const ListLinked<T> &list) {
            out << "[";
            Node<T>* aux = list.first;
            while (aux != nullptr) {
                out << aux->data;
                if (aux->next != nullptr) {
                    out << ", ";
                }
                aux = aux->next;
            }
            out << "]";
            return out;
        }

        // --- MÉTODOS HEREDADOS DE LA INTERFAZ LIST<T> ---

        void insert(int pos, T e) override {
            if (pos < 0 || pos > n) {
                throw std::out_of_range("Posición inválida");
            }
            if (pos == 0) {
                prepend(e);
            } else {
                Node<T>* prev = first;
                for (int i = 0; i < pos - 1; i++) {
                    prev = prev->next;
                }
                prev->next = new Node<T>(e, prev->next);
                n++;
            }
        }

        void append(T e) override {
            insert(n, e);
        }

        void prepend(T e) override {
            first = new Node<T>(e, first);
            n++;
        }

        T remove(int pos) override {
            if (pos < 0 || pos >= n) {
                throw std::out_of_range("Posición fuera de rango");
            }
            Node<T>* aux;
            T data;

            if (pos == 0) {
                aux = first;
                first = first->next;
            } else {
                Node<T>* prev = first;
                for (int i = 0; i < pos - 1; i++) {
                    prev = prev->next;
                }
                aux = prev->next;
                prev->next = aux->next;
            }

            data = aux->data;
            delete aux;
            n--;
            return data;
        }

        T get(int pos) const override {
            if (pos < 0 || pos >= n) {
                throw std::out_of_range("Posición fuera de rango");
            }
            Node<T>* aux = first;
            for (int i = 0; i < pos; i++) {
                aux = aux->next;
            }
            return aux->data;
        }

        int search(T e) const override {
            Node<T>* aux = first;
            int i = 0;
            while (aux != nullptr) {
                if (aux->data == e) {
                    return i;
                }
                aux = aux->next;
                i++;
            }
            return -1;
        }

        bool empty() const override {
            return n == 0;
        }

        int size() const override {
            return n;
        }
};

#endif
