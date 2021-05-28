/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Seguridad en sistemas informáticos
 *
 * @author Joel Aday Dorta Hernadez
 * @date 25.02.2021
 * @brief Archivo se desarrollan los metodos de la clase Vigenere. 
 *        
 *               
 * @see https://es.wikipedia.org/wiki/Cifrado_de_Vigen%C3%A8re
 *
 */

#include "vigenere.h"

/**
 * Funcion que se usa para eliminar los 
 * espacios de un string.
 **/
std::string space_killer(std::string message) {
  message.erase(std::remove(message.begin(), message.end(), ' '), message.end());
  return message;
}

/**
 * Funcion que se usa para traducir la clave
 * de letras a numeros segun su posicion en la tabla.
**/
void Vigenere::ToNumbers() { 
  for (size_t i = 0; i < key_.size(); i++) {
    for (size_t j = 0; j < symboltable_.size(); j++) {
      if (key_[i] == symboltable_[j].symbol)
      keynumbers_.push_back(symboltable_[j].number);
    }
  }
}

/**
 * Funcion que se usa para traducir 
 * las partes del mensaje a numeros segun 
 * su posicion en la tabla.
**/
void Vigenere::ToNumbers(std::string part) {
  for (size_t i = 0; i < part.size(); i++) {
    for (size_t j = 0; j < symboltable_.size(); j++) {
      if (part[i] == symboltable_[j].symbol)
      partnumbers_.push_back(symboltable_[j].number);
    }
  }
}

Vigenere::Vigenere(std::string key, std::string message) {
  key_ = key;
  originalmessage_ = message;
  
  for (int i = 0; i < module; i++)
    symboltable_.push_back(Alphabet() );

  int iterator = 0;

  for (char letter = 'a'; letter <= 'z'; letter++) {
    symboltable_[iterator].symbol = letter;
    symboltable_[iterator].number = iterator;
    iterator++;
  }
  iterator = 0;

  ToNumbers();
}

Vigenere::~Vigenere(){}

void Vigenere::DivideMessage(std::string &message) {
  int keysize = key_.size();

  for (size_t i = 0; i < message.size(); i = i + keysize)
    dividedmessage_.push_back(message.substr(i, keysize) );
}

int Vigenere::MathCipherOp(int op1, int op2) {
  int result = 0;

  result = (op1 + op2) % module;

  return result;
}

int Vigenere::MathDeCipherOp(int op1, int op2) {

  int result = 0;
  result = (op1 - op2) % module;

  return result;
}

void Vigenere::VigenereCipher() {
  std::string nospaces = space_killer(originalmessage_);
  DivideMessage(nospaces);

  int result_aux = 0;

  for (size_t i = 0; i < dividedmessage_.size();i++) {
    partnumbers_.clear();
    ToNumbers(dividedmessage_[i]);
    for (size_t j = 0; j < partnumbers_.size();j++) {
      result_aux = 0;
      result_aux = MathCipherOp(keynumbers_[j], partnumbers_[j]);
      for (size_t k = 0; k < symboltable_.size(); k++) {
        if (result_aux == symboltable_[k].number)
          ciphermessage_.push_back(symboltable_[k].symbol);
      }
    }
  }
}

void Vigenere::VigenereDecipher() {
  std::string nospaces = space_killer(ciphermessage_);
  int keysize = key_.size();

 for (size_t i = 0; i < ciphermessage_.size(); i = i + keysize)
    dividedcipher_.push_back(ciphermessage_.substr(i, keysize) );

  int op1 = 0;
  int result = 0;
  for (size_t i = 0; i < dividedmessage_.size(); i++){
    partnumbers_.clear();
    ToNumbers(dividedmessage_[i]);
    for (size_t j = 0; j < partnumbers_.size() ;j++) {
      op1 = 0;
      result = 0;
      op1 = keynumbers_[j] + partnumbers_[j];
      result = MathDeCipherOp(op1, keynumbers_[j]);
      for (size_t k = 0; k < symboltable_.size(); k++) {
        if (result == symboltable_[k].number)
          deciphermessage_.push_back(symboltable_[k].symbol);
      }
    }
  }
}

void Vigenere::WriteCipher() {
  std::string upper;
  std::cout << "El mensaje cifrado es: ";
  for (size_t i = 0; i < ciphermessage_.size(); i++)
    upper.push_back(std::toupper(ciphermessage_[i]) );

  std::cout << upper << "\n";
}

void Vigenere::WriteDecipher() {
  std::string upper;
  std::cout << "El mensaje descifrado es: ";
  for (size_t i = 0; i < deciphermessage_.size(); i++)
    upper.push_back(std::toupper(deciphermessage_[i]) );

  std::cout << upper << "\n";
}