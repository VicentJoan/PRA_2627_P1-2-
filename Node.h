#ifndef NODE_H
#define NODE_H

#include <ostream> // Necesario para la sobrecarga del operador <<

template <typename T> //Convierte a Node en una clase genérica capaz de almacenar cualquier tipo de dato T
class Node {
    public:
        // Atributos de la clase Node (típicamente públicos en nodos de listas)
        T data;
        Node<T>* next;

        // Método constructor
        Node(T data, Node<T>* next = nullptr) {  //un nodo necesita almacenar un dato (T data) y un puntero al siguiente nodo de su mismo tipo (Node<T>* next)
            this->data = data;
            this->next = next;
        }

        // Sobrecarga global del operador <<   //Permite imprimir el nodo directamente con std::cout. Tal como indica la instrucción, se limita a enviar al flujo de salida (out) únicamente el atributo data del nodo. La inclusión de <ostream> al principio del archivo es obligatoria para que esto funcione.

        friend std::ostream& operator<<(std::ostream &out, const Node<T> &node) {
            out << node.data;
            return out;
        }
};

#endif
