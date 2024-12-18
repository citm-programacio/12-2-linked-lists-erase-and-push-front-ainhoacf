// linkedlist2.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>

class List { 

private:
    struct Node {
        int value;
        Node* next;
        Node* prev;
        Node(int val) : value(val), next(nullptr), prev(nullptr) {}
    };

    Node* first = nullptr;
    Node* last = nullptr;
    unsigned int num_elems = 0;

public:
    List() {
        first = nullptr;
        last = nullptr;
        num_elems = 0;
    }

    ~List() {
        while (first != nullptr) {
            Node* temp = first;
            first = first->next;
            delete temp;
        }
    }

    void push_back(const int& value) {
        Node* newNode = new Node(value);
        if (last == nullptr) {
            first = last = newNode;
        }
        else {
            last->next = newNode;
            newNode->prev = last;
            last = newNode;
        }
        num_elems++;
    }

    void push_front(const int& value) {
        Node* newNode = new Node(value);
        if (first == nullptr) {
            first = last = newNode;
        }
        else {
            newNode->next = first;
            first->prev = newNode;
            first = newNode;
        }
        num_elems++;
    }

    void insert(unsigned int position, const int& value) {
        if (position == 0) {
            push_front(value);
        }
        else if (position >= num_elems) {
            push_back(value);
        }
        else {
            Node* current = first;
            unsigned int index = 0;
            while (index < position) {
                current = current->next;
                index++;
            }
            Node* newNode = new Node(value);
            newNode->next = current;
            newNode->prev = current->prev;
            if (current->prev != nullptr) {
                current->prev->next = newNode;
            }
            current->prev = newNode;
            num_elems++;
        }
    }

    void erase(unsigned int position) {
        if (position >= num_elems) {
            std::cout << "Posición fuera de rango. No se eliminó nada." << std::endl;
            return;
        }

        Node* current = first;
        if (position == 0) {
            // Eliminar el primer nodo
            first = first->next;
            if (first != nullptr) {
                first->prev = nullptr;
            }
            else {
                last = nullptr; // Lista vacía
            }
        }
        else {
            unsigned int index = 0;
            while (index < position) {
                current = current->next;
                index++;
            }

            // Actualizar los punteros del nodo anterior y el siguiente
            if (current->prev != nullptr) {
                current->prev->next = current->next;
            }
            if (current->next != nullptr) {
                current->next->prev = current->prev;
            }

            // Si eliminamos el último nodo, actualizar `last`
            if (current == last) {
                last = current->prev;
            }
        }

        delete current;
        num_elems--;
    }

    void print() const {
        Node* current = first;
        while (current != nullptr) {
            std::cout << current->value << " ";
            current = current->next;
        }
        std::cout << std::endl;
    }
};

int main() {
    List myList;

    // Pruebas de `push_back` y `print`
    myList.push_back(10);
    myList.push_back(20);
    myList.push_back(30);
    myList.print(); // Salida: 10 20 30

    // Pruebas de `push_front`
    myList.push_front(5);
    myList.print(); // Salida: 5 10 20 30

    // Pruebas de `insert`
    myList.insert(2, 15); // Inserta en la posición 2
    myList.print(); // Salida: 5 10 15 20 30

    // Pruebas de `erase`
    myList.erase(0); // Elimina el primer elemento
    myList.print(); // Salida: 10 15 20 30

    myList.erase(2); // Elimina el elemento en la posición 2
    myList.print(); // Salida: 10 15 30

    myList.erase(10); // Intento de eliminar una posición inválida
    myList.print(); // Salida: 10 15 30

    return 0;
}


// Ejecutar programa: Ctrl + F5 o menú Depurar > Iniciar sin depurar
// Depurar programa: F5 o menú Depurar > Iniciar depuración

// Sugerencias para primeros pasos: 1. Use la ventana del Explorador de soluciones para agregar y administrar archivos
//   2. Use la ventana de Team Explorer para conectar con el control de código fuente
//   3. Use la ventana de salida para ver la salida de compilación y otros mensajes
//   4. Use la ventana Lista de errores para ver los errores
//   5. Vaya a Proyecto > Agregar nuevo elemento para crear nuevos archivos de código, o a Proyecto > Agregar elemento existente para agregar archivos de código existentes al proyecto
//   6. En el futuro, para volver a abrir este proyecto, vaya a Archivo > Abrir > Proyecto y seleccione el archivo .sln
