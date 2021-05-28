#include "fefisha.h"

Fefisha::Fefisha(long p, long q, long i, long r, std::string sign) {
    p_ = p;
    q_ = q;
        try {
        if (!lehmanPeralta(p) || !lehmanPeralta(q)) {
            throw ("Error");
        }
    } catch(...){
        std::cout << "error p y q deben ser primos" << std::endl;
    }
    r_ = r;
    n_ = p_ * q_;
    i_ = i;
    if (sign == "negativo") {
        sign_ = -1;
    } else {
        sign_ = 1;
    }
}

bool Fefisha::lehmanPeralta(long prime) {
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

    for (long i = 0; i < max; i++) {
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

long Fefisha::quickExp(long long a, unsigned long b, long m) {
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

long Fefisha::gcdExtended(long a, long b, long* x, long* y)
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

bool Fefisha::isXPrime(long x, long m)
{
    long t, y;
    long g = gcdExtended(x, m, &t, &y);
    if (g != 1) {
        return false;
    }
    else
    {
        return true;        
    }
}

Fefisha::~Fefisha(){}

void Fefisha::protocol() {
    long secret;
    bool error = false;
    
    
    std::cout << "Ingresa identificación secreta de A: \n";
    for (int i = 0; i < i_; i++) {
        std::cout << "Numero: "; std::cin >> secret;
        if (isXPrime(secret, n_)) {
            s_.push_back(secret);
            if (i % 2 == 0) {
                a_.push_back(1);
            }else {
                a_.push_back(1);
            }
        } else {
            error = true;
            break;
        }
    }
    long tov;
    if (!error) {
        for (size_t i = 0; i < s_.size(); i++) {
            tov = (s_[i] * s_[i]) % n_;
            v_.push_back(tov);
        }
        witness_ = sign_ * (r_ * r_);
        witness_ %= n_;
        y_ = r_;
        for (size_t i = 0; i < s_.size(); i++) {
            y_ *= pow(s_[i], a_[i]);
        }
    }
    powy_ = witness_;

    for (size_t i = 0; i < v_.size(); i++) {
        powy_*= pow(v_[i],a_[i]);
    }

    if (powy_ == (pow(y_,2) ) ) {
        verified_ = powy_ % n_;
        checked_ = true;
    }else {
        checked_ = false;
    }
}

void Fefisha::showResult() {
    std::cout << "Testigo: " << witness_ << " mod (" << n_<< ")\n";
    std::cout << "Reto: ";
    for (size_t i = 0; i < a_.size(); i++) {
        std::cout << "\na"<< i + 1 << ": "<< a_[i]; 
    }
    std::cout << "\nRespuesta: "<< y_ << "\n";
    std::cout << "Verificación: ";
    if (checked_) {
        std::cout << "Se verifica que y2 = ±x * v1^a1 * v2^a2* ...* vkak(mod n) = " << verified_<<"\n";
    }
    else {
        std::cout << "No se ha podido verificar\n";
    }
}