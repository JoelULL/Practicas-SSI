#include "rsa.h"

Rsa::Rsa(std::string message, long p, long q, long d) {
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

bool Rsa::lehmanPeralta(long prime) {
    std::vector<long> lprimes = {2, 3, 5, 7, 11};
    std::vector<long> randomNumbers;
    unsigned long counter1 = 0;
    unsigned long counterM1 = 0;

    for (size_t i = 0; i < lprimes.size(); i++) {
        if (prime == lprimes[i])
            return true;
        if(prime % lprimes[i] == 0)
            return false;
    }
    std::srand(std::time(NULL));

    for (long i = 0; i < eucmax; i++) {
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

long Rsa::quickExp(long long a, unsigned long b, long m) {
    long res = 1;     

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

long Rsa::gcdExtended(long a, long b, long* x, long* y)
{
    if (a == 0)
    {
        *x = 0, *y = 1;
        return b;
    }
    long x1, y1;
    long gcd = gcdExtended(b % a, a, &x1, &y1);

    *x = y1 - (b / a) * x1;
    *y = x1;

    return gcd;
}

bool Rsa::isDprime(long d, long m)
{
    long x, y;
    long g = gcdExtended(d, m, &x, &y);
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
    long i = 0;
    std::string mcopy = message_;
    removeSpaces(mcopy);
    std::vector<std::string> divided;
    
    do {
        i++;
    } while(n_ > std::pow(base, i));

    blocksize_ = i - 1;
    std::cout << "Como n = "<< n_<< ", se divide el texto en bloques de " << blocksize_ << " caracteres." << std::endl;
    size_t counter = 0;
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
    size_t size =divided[divided.size() - 1].size();
    if (size != blocksize_) {
        long dif = blocksize_ - divided[divided.size() - 1].size();
        for (long i = 0; i < dif; i++) {
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

long Rsa::convertToDecimal(std::string str) {
    long result = 0;
    long powd = blocksize_ - 1;
    for(size_t i = 0; i < blocksize_; i++) {
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