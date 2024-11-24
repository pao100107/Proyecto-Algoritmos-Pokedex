#ifndef _BST_H
#define _BST_H

#include <iostream>
#include <utility> // Para std::pair
#include <string>
#include "pokemonhashtable.h" // Incluye las definiciones de HashTable

class BinarySearchTree {
public:
    using PokemonEntry = std::pair<std::string, Hashtablepokemon*>; // Tupla con string y puntero a HashTable

    BinarySearchTree() : root(nullptr) {}

    ~BinarySearchTree() {
        makeEmpty();
    }

    bool isEmpty() const {
        return root == nullptr;
    }

    // Inserta un nodo en el árbol
    void insert( std::string& name, Hashtablepokemon* table) {
        PokemonEntry entry = std::make_pair(name, table);
        insert(entry, root);
    }

    // Busca un nodo por nombre
    const PokemonEntry* find(const std::string& name) const {
        return find(name, root);
    }

    // Limpia el árbol
    void makeEmpty() {
        makeEmpty(root);
    }

    // Imprime el árbol en orden
    void printTree(std::ostream& out = std::cout) const {
        printTree(root, out);
    }

private:
    struct BinaryNode {
        PokemonEntry element;
        BinaryNode* left;
        BinaryNode* right;

        BinaryNode(const PokemonEntry& elem, BinaryNode* lt, BinaryNode* rt)
            : element(elem), left(lt), right(rt) {}
    };

    BinaryNode* root;

    void insert(const PokemonEntry& x, BinaryNode*& t) {
        if (!t) {
            t = new BinaryNode(x, nullptr, nullptr); // Crea un nuevo nodo
        } else if (x.first < t->element.first) {
            insert(x, t->left); // Inserta en el subárbol izquierdo
        } else if (x.first > t->element.first) {
            insert(x, t->right); // Inserta en el subárbol derecho
        } else {
            // Si ya existe un nodo con el mismo nombre, se puede actualizar la tabla hash:
            *t->element.second = *x.second; // Actualiza el contenido del HashTable
        }
    }

    const PokemonEntry* find(const std::string& name, BinaryNode* t) const {
        if (!t) {
            return nullptr;
        } else if (name < t->element.first) {
            return find(name, t->left);
        } else if (name > t->element.first) {
            return find(name, t->right);
        } else {
            return &t->element;
        }
    }

    void makeEmpty(BinaryNode*& t) {
        if (t) {
            makeEmpty(t->left);
            makeEmpty(t->right);
            delete t->element.second; // Libera la tabla hash asociada
            delete t; // Libera el nodo
        }
        t = nullptr;
    }

    void printTree(BinaryNode* t, std::ostream& out) const {
        if (t) {
            printTree(t->left, out);
            out << "Pokemon Name: " << t->element.first << std::endl;
            // Asegúrate de tener un método en HashTable para obtener su información:
            out << "HashTable Info: (custom output here)" << std::endl;
            printTree(t->right, out);
        }
    }
};

#endif // _BST_H