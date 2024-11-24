#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <algorithm>

//La estructura que representa a un pokemon
struct Pokemon {
    std::string name;
    std::string japanese_name;
    std::vector<std::string> abilities;
    bool is_legendary;
    std::string type1;
    std::string type2;

};

//función que divide una cadena y devuelve un vector por partes2
std::vector<std::string> split(const std::string& str, char delimiter) {
    std::vector<std::string> parts;
    std::stringstream ss(str);
    std::string part;
    while (std::getline(ss, part, delimiter)) {
        //Eliminar espacios al principio y final de cada parte
        part.erase(remove(part.begin(), part.end(), ' '), part.end());
        parts.push_back(part);
    }
    return parts;
}

//función que carga los pokemones desde el archivo pokemonns que es la base de datos
void cargarDesdeArchivo(const std::string& filename, std::vector<Pokemon>& pokedex) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "No se pudo abrir el archivo " << filename << std::endl;
        return;
    }

    std::string line;
    std::getline(file, line);

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string abilities_str, name, japanese_name, type1, type2, is_legendary_str;

        //se leen las respectivas columnas de la base de datos
        std::getline(ss, name, ';');
        std::getline(ss, japanese_name, ';');
        std::getline(ss, abilities_str, ';');
        std::getline(ss, type1, ';');
        std::getline(ss, type2, ';');
        std::getline(ss, is_legendary_str, ';');

        //convierte habilidades_str en un vector de habilidades
        std::vector<std::string> abilities = split(abilities_str, ',');

        //crea el objeto pokemon 
        Pokemon pokemon = {
            name,
            japanese_name,
            abilities,
            is_legendary_str == "1",  //devuelve true si es 1 (legendario) false si es 0(no es legendario)
            type1,
            type2
        };

        //se añade el pokemon a la pokedex
        pokedex.push_back(pokemon);
    }

    file.close();
}

//función que muestra un pokemon que haya pedido el usuario
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

//funcion para que se busque el pokemon por nombre (primera opcion)
void buscarPorNombre(const std::vector<Pokemon>& pokedex, const std::string& nombre) {
    bool encontrado = false;
    for (const auto& pokemon : pokedex) {
        if (pokemon.name == nombre) {
            mostrarPokemon(pokemon);
            encontrado = true;
            break;
        }
    }

    if (!encontrado) {
        std::cout << "No se encontró el Pokémon con el nombre: " << nombre << std::endl;
    }
}

//función que busca el pokemon por tipo (segunda opcion)
void buscarPorTipo(const std::vector<Pokemon>& pokedex, const std::string& tipo) {
    bool encontrado = false;
    for (const auto& pokemon : pokedex) {
        if (pokemon.type1 == tipo || pokemon.type2 == tipo) {
            mostrarPokemon(pokemon);
            encontrado = true;
        }
    }

    if (!encontrado) {
        std::cout << "No se encontraron Pokémon del tipo: " << tipo << std::endl;
    }
}

//funcion de la interfaz del usuario
void interfazUsuario(const std::vector<Pokemon>& pokedex) {
    int opcion;
    std::cout << "Bienvenido a la Pokédex ¿Qué te gustaría hacer?" << std::endl;
    std::cout << "1. Buscar por nombre" << std::endl;
    std::cout << "2. Buscar por tipo" << std::endl;
    std::cout << "3. Salir" << std::endl;
    std::cout << "Selecciona una opción: ";
    std::cin >> opcion;

    std::cin.ignore();  //se limpia el contenedor

    switch (opcion) {
        case 1: {
            std::string nombre;
            std::cout << "Ingresa el nombre del Pokémon: ";
            std::getline(std::cin, nombre);
            buscarPorNombre(pokedex, nombre);
            break;
        }
        case 2: {
            std::string tipo;
            std::cout << "Ingresa el tipo del Pokémon: ";
            std::getline(std::cin, tipo);
            buscarPorTipo(pokedex, tipo);
            break;
        }
        case 3:
            std::cout << "¡Hasta luego!" << std::endl;
            break;
        default:
            std::cout << "Opción no válida." << std::endl;
            break;
    }
}

int main() {
    std::vector<Pokemon> pokedex;

    //se cargan los pokemones desde el archivo CSV "pokemonns"
    cargarDesdeArchivo("pokemonns.csv", pokedex);

    //se llama a la interfaz del usuario
    while (true) {
        interfazUsuario(pokedex);
    }

    return 0;
}
