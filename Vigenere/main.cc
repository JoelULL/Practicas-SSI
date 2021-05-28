/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Seguridad en sistemas informáticos
 *
 * @author Joel Aday Dorta Hernadez
 * @date 25.02.2021
 * @brief Archivo principal del programa en él se le pide al usuario que ingrese tanto la clave
 *        como el mensaje original a cifrar.
 *               
 * @see https://es.wikipedia.org/wiki/Cifrado_de_Vigen%C3%A8re
 *
 */

#include "vigenere.h"

bool isalpha(std::string text) {
  unsigned int counter = 0;
  size_t size = text.size();

  for (size_t i = 0; i < size; i++) {
    for (char j = 'a'; j <= 'z'; j++) {
      if (text[i] == j)
        counter++;
    }
  }
  return counter == size;
}

void error_msg(int code) {
  if (code == 1) {
    std::cout << "\nError, la clave solo puede tener caracteres entre a y z!";
    std::cout << "No ingrese numeros ni caracteres que no sean letras.\n";
    std::cout << "No se permite la ñ del teclado español.\n";
  }
  if (code == 2) {
    std::cout << "\nError, el mensaje solo puede tener caracteres entre a y z!";
    std::cout << "No ingrese numeros ni caracteres que no sean letras.\n";
    std::cout << "No se permite la ñ del teclado español.\n";
  }
}

int main (void) {

  std::string key;
  std::string original_message; 
  
  std::cout << "\t====Cifrado de vigenere====\n";
  
  std::cout << "\nIngrese una clave: ";
  std::cin >> key;

   if (!isalpha(key) ) {
     error_msg(1);
     return 1;
   }
  
  std::cout << "\nIngrese el mensaje: ";
  std::cin.ignore();
  std::getline(std::cin, original_message);

   if (!isalpha(space_killer(original_message) )) {
     error_msg(2);
     return 2;
   }

  std::cout << "\n";
  Vigenere program(key, original_message);
  
  program.VigenereCipher();
  program.VigenereDecipher();

  program.WriteCipher();
  program.WriteDecipher();

  return 0;
}