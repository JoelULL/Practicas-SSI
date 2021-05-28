#include "menu.h"

unsigned int interpretateHex(std::string s) {
    unsigned int x = std::stoul(s, nullptr, 16);
    return x;
}

uint32_t swap_endian(uint32_t u)
{
    static_assert (CHAR_BIT == 8, "CHAR_BIT != 8");

    union
    {
        uint32_t u;
        unsigned char u8[sizeof(uint32_t)];
    } source, dest;

    source.u = u;

    for (size_t k = 0; k < sizeof(uint32_t); k++)
        dest.u8[k] = source.u8[sizeof(uint32_t) - k - 1];

    return dest.u;
}

void vigenereError(int code) {
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

void analyzeBytes(std::string str, std::vector<std::bitset<8> > &vc) {
    int counter = 0;
    std::string aux;
    for (size_t i = 0; i < str.size(); i++) {
        if (counter == 2) {
            vc.push_back(interpretateHex(aux));
            aux = "";
            counter = 0;
        }
        aux+=str[i];
        counter++;
        if (i == str.size() - 1) {
            vc.push_back(interpretateHex(aux));
        }
    }
}

bool isPrime(int n)
{
    if (n <= 1)
        return false;
 
    for (int i = 2; i < n; i++)
        if (n % i == 0)
            return false;
 
    return true;
}

bool checkMessage(std::string str) {
    for (size_t i = 0; i < str.size(); i++) {
        if (!isupper(str[i]) && str[i] != ' ')
            return false;
    }
    return true;
}

Menu::Menu(std::string pname) {
    pname_ = pname;
    initializePractices(); 
    menuSwitch();
}

Menu::~Menu(){}

void Menu::menuSwitch() {
    int practice = 999;
    for (size_t i = 0; i < pnames_.size(); i++) {
        if (pname_ == pnames_[i].name) {
            practice = pnames_[i].number;
            break;
        }
    }
    switch(practice) {
        case 0: {
            vigenere();
            break;
        }
        case 1: {
            rc4();
            break;
        }
        case 2: {
            chaCha20();
            break;
        }
        case 3: {
            c_a();
            break;
        }
        case 4: {
            snowAes();
            break;
        }
        case 5: {
            aesF();
            break;
        }
        case 6: {
            aesCbc();
            break;
        }
        case 7: {
            elGamal();
            break;
        }
        case 8: {
            rsa();
            break;
        }
        case 9: {
            eldifhel();
            break;
        }
        case 10: {
            fefishaF();
            break;
        }
        default: {
            std::cout << "práctica no conocida! prueba con:";
            std::cout << " vigenere, rc4, chacha20, C/A, Snow 3G/AES, AES, CBC, ";
            std::cout << "ElGamal, RSA, eldifhel ó fefisha\n";
            break;
        }
    }
}

void Menu::initializePractices() {
    for(int i = 0; i < prsize; i++) {
        pnames_.push_back(prtc());
        pnames_[i].number = i;
    }
    pnames_[0].name = "vigenere";
    pnames_[1].name = "rc4";
    pnames_[2].name = "chacha20";
    pnames_[3].name = "C/A";
    pnames_[4].name = "Snow/AES";
    pnames_[5].name = "AES";
    pnames_[6].name = "CBC";
    pnames_[7].name = "ElGamal";
    pnames_[8].name = "RSA";
    pnames_[9].name = "eldifhel";
    pnames_[10].name = "fefisha";   
}

void Menu::vigenere() {
  std::string key;
  std::string original_message; 
  
  std::cout << "\t====Cifrado de vigenere====\n";
  
  std::cout << "\nIngrese una clave: ";
  std::cin >> key;

   if (!isalpha(key) ) {
     vigenereError(1);
   }
  
  std::cout << "\nIngrese el mensaje: ";
  std::cin.ignore();
  std::getline(std::cin, original_message);

   if (!isalpha(space_killer(original_message) )) {
     vigenereError(2);
   }

  std::cout << "\n";
  Vigenere program(key, original_message);
  
  program.VigenereCipher();
  program.VigenereDecipher();

  program.WriteCipher();
  program.WriteDecipher();
}
void Menu::rc4() {
    std::vector<int> seed;
    std::vector<int> message;
    bool stop = false;
    bool checked = false;
    char response;
    int number;
    std::cout << "Ingrese los numeros de la semilla: \n";
    do {
        std::cout << "Numero: "; std::cin >> number;
        seed.push_back(number);
        do {
            std::cout << "¿Ha terminado? (y/n): "; std::cin >> response;
            if (response == 'y' || response == 'n')
                checked = true;
        }while(!checked);

        if (response == 'y') {
            stop = true;
        }
    }while(!stop);

    stop = false;
    checked = false;
    std::cout << "Ingrese los numeros del mensaje: \n";
        do {
        std::cout << "Numero: "; std::cin >> number;
        message.push_back(number);
        do {
            std::cout << "¿Ha terminado? (y/n): "; std::cin >> response;
            if (response == 'y' || response == 'n')
                checked = true;
        }while(!checked);

        if (response == 'y') {
            stop = true;
        }
    }while(!stop);

    Rc4 test(seed, message);
    test.CipherMessage();
    test.Showresults();
}

void Menu::chaCha20() {
    uint32_t tochacha [12];
    std::string strhex;
    bool error = false;

    std::cout << "Introduce los numeros de la clave: ";
    for (int i = 0; i < chsk; i++) {
        std::cout << "\nNumero: "; std::cin >> strhex;
        if (strhex.size() != 8) {
            std::cout << "Error, debe tener 8 digitos";
            error = true;
            break;
        }
        tochacha[i] = interpretateHex(strhex);
        strhex = "";
    }
    std::cout << "Introduce el contador: "; std::cin >> strhex;
    if (strhex.size() != 8) {
        std::cout << "Error, debe tener 8 digitos";
        error = true;
    }
    if(!error)
        tochacha[8] = interpretateHex(strhex);
    
    std::cout << "Introduce el nounce: ";
    for (int i = 9; i < chmx; i++) {
        std::cout << "\nNumero: "; std::cin >> strhex;
        if (strhex.size() != 8) {
            std::cout << "Error, debe tener 8 digitos";
            error = true;
            break;
        }
        tochacha[i] = interpretateHex(strhex);
        strhex = "";
    }
    if (!error) {
        for (int i = 0; i < 12; i++)
        tochacha[i] = swap_endian(tochacha[i]);

    ChaCha20 test (tochacha);
    test.ChaChaBlock();
    test.ShowResult();
    }
}

void Menu::c_a() {
    int id, its;
    bool error = false;
    std::cout << "ID: ";
    std::cin >> id;
    
    std::cout << "\nLongitud sec salida: ";
    std::cin >> its;

    if (id <= 0 || id > 32) {
        std::cout << "Error id incorrecto";
        error = true;
    }

    if (!error) {
        CaGps test(id, its);
        test.lsfrsWork();
        test.showResults();
    }

}

void Menu::snowAes() {
    std::string byte1;
    std::string byte2;
    std::string algorithm;
    int b1, b2;
    bool error = false;
    
    std::cout << "Primer byte: ";
    std::cin >> byte1;

    std::cout << "\nSegundo byte: ";
    std::cin >> byte2;

    std::cout << "\nAlgoritmo: ";
    std::cin >> algorithm;

    if (algorithm != "aes" && algorithm != "snow") {
        std::cout << "error, introduce un algoritmo valido: snow o aes\n";
        error = true;
    }
    if (!error) {
        b1 = interpretateHex(byte1);
        b2 = interpretateHex(byte2);

        BinaryMul test(b1,b2,algorithm);
        test.multiplyThem();
        test.showResults();
    }
}

void Menu::aesF() {
    std::string key;
    std::string text;
    std::vector<std::bitset<8> > keyg;
    std::vector<std::bitset<8> > textg;

    std::cout << "Clave(16 bytes en hexadecimal): ";
    std::cin >> key;

    std::cout << "Bloque de texto original (16 bytes en hexadecimal): ";
    std::cin >> text;

    if (key.size() < 32 || text.size() < 32) {
        std::cout<< "Error no hay 16 bytes";
    } else {
    analyzeBytes(key,keyg);
    analyzeBytes(text,textg);
    
    Aes test(keyg, textg);
    test.encrypt();
    }
}

void Menu::aesCbc() {
    std::string skey, siv, splain1, splain2;
    std::vector<std::bitset<8> > key;
    std::vector<std::bitset<8> > iv;
    std::vector<std::bitset<8> > plaintext1;
    std::vector<std::bitset<8> > plaintext2;
    std::vector<std::vector<std::bitset<8> > > allTheData;

    std::cout << "Clave: ";
    std::cin >> skey;
    analyzeBytes(skey, key);
    allTheData.push_back(key);

    std::cout << "\nIV: ";
    std::cin >> siv;
    analyzeBytes(siv, iv);
    allTheData.push_back(iv);

    std::cout << "\nBloque 1 de texto Original: ";
    std::cin >> splain1;
    analyzeBytes(splain1, plaintext1);
    allTheData.push_back(plaintext1);

    std::cout << "\nBloque 2 de texto Original: ";
    std::cin >> splain2;
    analyzeBytes(splain2, plaintext2);
    allTheData.push_back(plaintext2);

    if (skey.size() != sz || siv.size() != sz || splain1.size() != sz)
        std::cout<< "Error deben haber 16 bytes por entrada";

    Cbc test(allTheData);
    test.cipherCbc();
    test.showResults();
}

void Menu::elGamal() {
    int p, a, k, x ,m;

    std::cout << "p = "; std::cin >> p; std::cout << "a = "; std::cin >> a;
    std::cout << "k = "; std::cin >> k; std::cout << "x = "; std::cin >> x;
    std::cout << "m = "; std::cin >> m;
    if (!isPrime(p)) {
        std::cout << "p debe ser primo\n";
    } else {
        Gamal prgm(p, a, k, x, m);
        
        prgm.gamalEncrypt();
        prgm.gamalDecrypt();
        prgm.showresults();
    }
}

void Menu::rsa() {
    long p, q, d;
    std::string message;

    std::cout << "\nmessage = "; 
    std::getline(std::cin, message);

    std::cout << "p = "; 
    std::cin >> p;
    std::cout << "\nq = "; 
    std::cin >> q;
    std::cout << "\nd = "; 
    std::cin >> d;


    if (!checkMessage(message)) {
        std::cout << "Error se piden caracteres del abecedario de A-Z sin Ñ"<<std::endl;
        
    } else {
        Rsa prgm(message, p, q, d);
        prgm.encrypt();
        prgm.showResult();
    }
}
void Menu::eldifhel() {
        long p, a, b, gx, gy, db , da, m;
        bool error = false;

    std::cout << "p= "; std::cin >> p;
    std::cout << "\na= "; std::cin >> a;
    std::cout << "\nb= "; std::cin >> b;
    std::cout << "\ncoordenada x de G= "; std::cin >> gx;
    std::cout << "\ncoordenada y de G= "; std::cin >> gy;
    std::cout << "\ndB= "; std::cin >> db;
    std::cout << "\ndB= "; std::cin >> da;
    std::cout << "\nm= "; std::cin >> m;

    ElDiffieHel test(p, a, b, gx, gy, db, da, m);

    if (!test.lehmanPeralta(p)) {
        std::cout << "\n" << p << "p no es primo segun el test de lehmanPeralta\n";
        error = true;
    }
    if (!test.validPoint()) {
        std::cout << "\n(" << gx << ", "<< gy << ")  no es un punto de la curva\n";
        error = true;
    }
    if(!test.checkAandB()) {
        std::cout << " a y b deben satisfacer que: 4a³ + 27b² ≠ 0 (mod p)\n";
        error = true;
    }
    if (!error) {
        test.gamalCodeMessage();
        test.showResult();
    }
}

void Menu::fefishaF() {
    long p,q,i,r;
    std::string sign;

    std::cout << "p= "; std::cin >> p;
    std::cout << "\nq= "; std::cin >> q;
    std::cout << "\niteraciones= ";std::cin >> i;
    std::cout << "\nr= "; std::cin >> r;
    std::cout << "Signo(positivo o negativo): "; std::cin >> sign;
    if (sign != "positivo" && sign != "negativo") {
        std::cout << "Error, introduzca positivo o negativo\n";
    }else {
        Fefisha test(p, q, i, r, sign);
        test.protocol();
        test.showResult();
    }
}