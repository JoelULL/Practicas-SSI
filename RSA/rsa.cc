#include "rsa.h"

Rsa::Rsa(std::string message, int p, int q, int d) {
    message_ = message;
    p_ = p;
    q_ = q;
    d_ = d;
    euclidean_ = (p - 1) * (q - 1);
    n_ = p * q;
    initializeAlphabet();
    try {
        if (!lehmanPeralta(p) || !lehmanPeralta(q)) {
            throw ("Error");
        }
    } catch(...){
        std::cout << "error p y q deben ser primos" << std::endl;
    }
    std::cout << "Se comprueba que p y q son primos"<<std::endl;
    try {
        if (!isDprime(d, euclidean_) ) {
            throw ("Error");
        }
    } catch(...){
        std::cout << "error "<< d <<" debe ser primo con: " << euclidean_ << std::endl;
    }
    std::cout << "Se comprueba que d es primo con Φ(n) = "<< euclidean_ <<std::endl;
    std::cout << "Se calcula e = "<< e_ << std::endl;
}

Rsa::~Rsa(){}

bool Rsa::lehmanPeralta(int prime) {
    std::vector<int> lprimes = {2, 5, 7, 11};
    std::vector<int> randomNumbers;
    unsigned int counter1 = 0;
    unsigned int counterM1 = 0;

    for (size_t i = 0; i < lprimes.size(); i++) {
        if (prime == lprimes[i])
            return true;
        if(prime % lprimes[i] == 0)
            return false;
    }
    std::srand(std::time(NULL));

    for (int i = 0; i < eucmax; i++) {
        randomNumbers.push_back(std::rand() % (prime - 2) + 2);
    }

    for (size_t i = 0; i < randomNumbers.size(); i++) {
        if (quickExp(randomNumbers[i], ((prime - 1)/ 2), prime) == 1) {
            counter1++;
        }
        if(quickExp(randomNumbers[i], ((prime - 1)/ 2), prime) == -1) {
            counterM1++;
        }
    }
    if (counter1 == randomNumbers.size() || counterM1 == randomNumbers.size())
        return false;
    
    return true;
}

int Rsa::quickExp(long long a, unsigned int b, int m) {
    int res = 1;     

    a = a % m; 
                
    if (a == 0) return 0; 

    while (b > 0)
    {
        if (b & 1)
            res = (res*a) % m;

        b = b >> 1; 
        a = (a * a) % m;
    }
    return res;
}

int Rsa::gcdExtended(int a, int b, int* x, int* y)
{
    if (a == 0)
    {
        *x = 0, *y = 1;
        return b;
    }
    int x1, y1;
    int gcd = gcdExtended(b % a, a, &x1, &y1);

    *x = y1 - (b / a) * x1;
    *y = x1;

    return gcd;
}

bool Rsa::isDprime(int d, int m)
{
    int x, y;
    int g = gcdExtended(d, m, &x, &y);
    if (g != 1) {
        return false;
    }
    else
    {
        e_ = (x % m + m) % m;
        return true;        
    }
}

void Rsa::encrypt() {
    int i = 0;
    std::string mcopy = message_;
    removeSpaces(mcopy);
    std::vector<std::string> divided;
    
    do {
        i++;
    } while(n_ > std::pow(base, i));

    blocksize_ = i - 1;
    std::cout << "Como n = "<< n_<< ", se divide el texto en bloques de " << blocksize_ << " caracteres." << std::endl;
    int counter = 0;
    std::string tov;

    for (size_t i = 0; i < mcopy.size(); i++) {
        tov+= mcopy[i];
        counter++;
        if(counter == blocksize_) {
            divided.push_back(tov);
            counter = 0;
            tov = "";
        }
    }
    if (divided[divided.size() - 1].size() != blocksize_) {
        int dif = blocksize_ - divided[divided.size() - 1].size();
        for (int i = 0; i < dif; i++) {
            divided[divided.size() - 1] += 'X';
        }
    }
    
    for (size_t i = 0; i < divided.size(); i++) {
        decimals_.push_back(convertToDecimal(divided[i]));
    }

    for (size_t i = 0; i < decimals_.size(); i++) {
        cipher_.push_back(quickExp(decimals_[i], e_, n_));
        
    }
}

void Rsa::showResult() {
    std::cout << "Se pasa cada bloque a decimal para poder cifrar obteniendo: ";
    for (size_t i = 0; i < decimals_.size(); i++) {
        std::cout << decimals_[i] << " ";
    }
    std::cout << "\nSe calcula en decimal el texto cifrado: ";
        for (size_t i = 0; i < cipher_.size(); i++) {
        std::cout << cipher_[i] << " ";
    }
    std::cout << "\n";
}

void Rsa::initializeAlphabet() {
    for (char letter = 'A'; letter <= 'Z'; letter++) {
        upalphabet_.push_back(letter);
    }
}

std::string Rsa::removeSpaces(std::string &str) {
    using namespace std;
    str.erase(std::remove(str.begin(), str.end(), ' '), str.end());
    return str;
}

int Rsa::convertToDecimal(std::string str) {
    int result = 0;
    int powd = blocksize_ - 1;
    for(int i = 0; i < blocksize_; i++) {
        for (size_t j = 0; j < upalphabet_.size(); j++) {
            if (str[i] == upalphabet_[j]) {
                result += j * pow(base, powd);
                powd = powd - 1;
                break;
            }
        }
    }
    return result;
}