
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>

// Estructura para representar un Pokémon
    struct Pokemon {
    std::string name;
    std::string japanese_name;
    std::vector<std::string> abilities;
    bool is_legendary;
    std::string type1;
    std::string type2;
    
    //float height;
    //float weight;
    //int hp;
    //int attack;
    //int defense;
    //int sp_attack;
    //int sp_defense;
    //int speed;
    //int base_happiness;
    //int base_total;
    //int pokedex_number;
};

// Función para cargar Pokémon desde un archivo CSV
void cargarDesdeArchivo(const std::string& filename, std::vector<Pokemon>& pokedex) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "No se pudo abrir el archivo " << filename << std::endl;
        return;
    }

    std::string line;
    // Leer la primera línea (encabezados) y omitirla
    std::getline(file, line);

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string abilities_str, name, japanese_name, type1, type2, is_legendary_str;

        // Leer las columnas relevantes, separando por el delimitador ';'
        std::getline(ss, name, ';');
        std::getline(ss, japanese_name, ';');
        std::getline(ss, abilities_str, ';');
        std::getline(ss, type1, ';');
        std::getline(ss, type2, ';');
        std::getline(ss, is_legendary_str, ';');

        // Crear el objeto Pokémon y agregarlo al pokedex
        // Convertir 'is_legendary_str' a bool: si es "0" (no legendario), es 'false'; si es "1", es 'true'
        Pokemon pokemon = {name, japanese_name, {abilities_str}, is_legendary_str == "0", type1, type2};
        pokedex.push_back(pokemon);
    }

    file.close();
}

// Función para mostrar un Pokémon
void mostrarPokemon(const Pokemon& pokemon) {
    std::cout << "Nombre: " << pokemon.name << std::endl;
    std::cout << "Nombre Japonés: " << pokemon.japanese_name << std::endl;
    std::cout << "Habilidades: ";
    for (const auto& ability : pokemon.abilities) {
        std::cout << ability << " ";
    }
    std::cout << std::endl;
    std::cout << "Tipo 1: " << pokemon.type1 << ", Tipo 2: " << (pokemon.type2.empty() ? "None" : pokemon.type2) << std::endl;
    std::cout << "Legendario: " << (pokemon.is_legendary ? "Sí" : "No") << std::endl;
    std::cout << "-------------------------------------" << std::endl;
}

// Función para cargar Pokémon desde un archivo CSV
