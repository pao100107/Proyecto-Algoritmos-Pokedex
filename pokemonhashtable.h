

#include <iostream>
#include "structurepokemon.h"
#include <cmath>

#pragma once

class Hashtablepokemon {
private:
  int bias1;
  int bias2;
  std::vector<int> hashes1;
  std::vector<int> hashes2;
  std::vector<Pokemon *> firstcucko;
  std::vector<Pokemon *> secondcucko;
  int size = 13;
  int hashFunc1(const std::string &key) {
    int hashValue = 0; // variable para almacenar el valor hash
    // itera sobre cada carácter en el nombre del Pokémon
    for (char ch : key) {
      // formula hash utilizando el valor ASCII de cada carácter
      hashValue = abs(((37* hashValue + int(ch))))%size;
      //std::cout<<"hashvalue"<<hashValue<<std::endl;
    }
    //std::cout<<hashValue<<std::endl;
    return hashValue; // devuelve el valor hash calculado
  }
  void rehash() {
    //int firstsize = size;
    // find prime
    int newsize = getfirstprimenumber();
    //std::cout<<newsize<<std::endl;
    //std::cout<<"hash value"<<hashFunc1("Pikachu");
    
    std::vector<Pokemon *> getfirsth;
    std::vector<Pokemon *> getsecondh;
    for (int i = 0; i < hashes1.size(); i++) {
      int index = hashes1[i];
      Pokemon* pokemon = new Pokemon(*firstcucko[index]);
      getfirsth.push_back(pokemon);
      //std::cout<<"pokemons"<<pokemon->name<<std::endl;
      
      //cout hash1 value
    
      //std::cout<<index<<std::endl;
      firstcucko[index] = nullptr;
    }
    
    for (int i = 0; i < hashes2.size(); i++) {
      int index2 = hashes2[i];
      //std::cout<<"pokemon name"<<secondcucko[index2]->name<<std::endl;
      getsecondh.push_back(new Pokemon(*secondcucko[index2]));
      secondcucko[index2] = nullptr;
      //std::cout<<"test null ptr"<<(secondcucko[index2] == nullptr)<<std::endl;
    }
   

    while (firstcucko.size() != newsize) {
      firstcucko.push_back(nullptr);
      secondcucko.push_back(nullptr);
    }
    //std::cout<<"nuevo tamaño: "<<firstcucko.size()<<std::endl;
    //std::cout<<"hash value"<<hashFunc1("Pikachu")<<std::endl;
     

    size = newsize;
    //empty hashes
    hashes1.clear();
    hashes2.clear();

    while (getfirsth.size() != 0) {
      //std::cout<<"intento"<<std::endl;

      insertpokemon(getfirsth[0], 0, 0);
      getfirsth.erase(getfirsth.begin());
    }

    while (getsecondh.size() != 0) {
      insertpokemon(getsecondh[0], 0, 0);
      getsecondh.erase(getsecondh.begin());
    }
   

    // create new table
  }

  void insertpokemon(Pokemon *pokemonnn, int mode, int n_iter) {
    //std::cout<<"wtf";
    if (n_iter > 5) {
      //std::cout<<"rehash"<<std::endl;
      //std::cout<<n_iter<<std::endl;
      rehash();
      //insertpokemon(pokemonnn, 0,0);
      //std::cout<<"tamaño"<<std::endl;
      
    
      //std::cout<<size<<std::endl;
    
      insertpokemon(pokemonnn, 0, 0);
      return;
    }
    int firsthash = hashFunc1(pokemonnn->name);
    int secondhash = hashFunc2(pokemonnn->name);
    //std::cout<<"vever"<<firstcucko[firsthash]->name<<std::endl;
    //std::cout<<"size"<<size<<std::endl;
    //std::cout<<firsthash<<std::endl;
    //std::cout<<pokemonnn->name<<std::endl;
    if (mode == 0) {
      
      

      if (firstcucko[firsthash] == nullptr) {
        Pokemon* temp= new Pokemon(*pokemonnn);
        //new pointer
        firstcucko[firsthash] = temp;
        
       
        //firstcucko.at(firsthash)= temp;
        hashes1.push_back(firsthash);
        //std::cout<<"inserted"<<firstcucko[firsthash]->name;

        return;
      }
      else{
      //std::cout<<mode<<"mode"<<std::endl;
      Pokemon* current = new Pokemon(*firstcucko[firsthash]);
      Pokemon* replace= new Pokemon(*pokemonnn);
      //std::cout <<"test"<<firstcucko[firsthash]->name<<std::endl;
      //Pokemon current = *firstcucko[firsthash];
        //std::cout<<(current->name)<<std::endl;
      //std::cout<<"name current"<<current.name<<std::endl;
      firstcucko[firsthash] = replace;
      //std::cout<<"test name"<<std::endl;
      //std::cout<<current.name<<std::endl;
      //std::cout<<pokemonnn->name<<std::endl;
      insertpokemon(current, (mode + 1) % 2, n_iter + 1);
      return;
      }
    } else {
      //std::cout<<mode<<"modo"<<std::endl;
      
      if (secondcucko[secondhash] == nullptr) {
        Pokemon* pointernew= new Pokemon(*pokemonnn);
        
        secondcucko[secondhash] = pointernew;
        hashes2.push_back(secondhash);
        return;
      }
      Pokemon *current = new Pokemon(*secondcucko[secondhash]);
      Pokemon* newpointer= new Pokemon(*pokemonnn);
      secondcucko[secondhash] = newpointer;
      insertpokemon(current, (mode + 1) % 2, n_iter + 1);
      return;
    }
  }
  int hashFunc2(const std::string &key) {
    int hashValue = 0; // variable para almacenar el valor hash
    // itera sobre cada carácter en el nombre del Pokémon
    for (char ch : key) {
      // formula hash utilizando el valor ASCII de cada carácter
      hashValue = abs(((37* hashValue + int(ch)) + bias2))%size;
      //std::cout<<"hashval"<<hashValue<<std::endl;
    }
    return hashValue; // devuelve el valor hash calculado
  }

  bool testprime(int &prime) {
    int range = prime / 2;
  
    for (int i = 2; i < range; i++) {
      if (prime % i == 0) {
        return false;
      }
    }
    return true;
  }
  int getfirstprimenumber() {
    int base = size+1;
    while (!testprime(base)) {
      base++;
     
      
    }
    return base;
  }
  void initializehashtable() {
    int newsize = getfirstprimenumber();
    size = newsize;
    for (int i = 0; i < size; i++) {
      firstcucko.push_back(nullptr);
      secondcucko.push_back(nullptr);
    }
  }

public:
  Hashtablepokemon() {
    initializehashtable();
    bias1 = 0;
    bias2 = 3;
    
  };
  ~Hashtablepokemon(){};
  void insertpokemon(Pokemon &pokemon) { insertpokemon(&pokemon, 0, 0); return;}
  Pokemon *searchpokemon(const std::string &name) {
    int firsthash = hashFunc1(name);
    int secondhash = hashFunc2(name);
    
    //std::cout<<firsthash<<std::endl;
    if (firstcucko[firsthash] != nullptr) {
      if (firstcucko[firsthash]->name == name) {
        return firstcucko[firsthash];
      }
      if (secondcucko[secondhash] != nullptr) {
        if (secondcucko[secondhash]->name == name) {
          return secondcucko[secondhash];
        }
        return nullptr;
      }
    }
    return nullptr;
  }
void forcerehash(){
  rehash();
}
};