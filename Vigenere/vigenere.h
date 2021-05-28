/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Seguridad en sistemas informáticos
 *
 * @author Joel Aday Dorta Hernadez
 * @date 25.02.2021
 * @brief Archivo en el que se definen la clase Vigenere con sus metodos y atributos.
 *        
 *               
 * @see https://es.wikipedia.org/wiki/Cifrado_de_Vigen%C3%A8re
 *
 */

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

#define module 26

struct Alphabet {
    char symbol;
    int number;
};

class Vigenere {
  private:
    std::vector<Alphabet> symboltable_;
    std::string key_;
    std::string originalmessage_;
    std::string ciphermessage_; 
    std::string deciphermessage_;
    std::vector<std::string> dividedmessage_;
    std::vector<std::string> dividedcipher_;
    std::vector<int> keynumbers_;
    std::vector<int> partnumbers_;
  public:

  Vigenere(std::string key, std::string message);
  ~Vigenere();

  void ToNumbers();
  void ToNumbers(std::string part);

  void DivideMessage(std::string &message);
  int MathCipherOp(int op1, int op2);
  int MathDeCipherOp(int op1, int op2);
  void VigenereCipher();
  void VigenereDecipher();

  void WriteCipher();
  void WriteDecipher();
  
};

std::string space_killer(std::string message);