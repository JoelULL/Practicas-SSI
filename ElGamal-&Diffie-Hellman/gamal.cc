#include "gamal.h"

Gamal::Gamal(int p, int a, int k, int x, int m) {
    Diffie toGamal(p, a, k, x);
    toGamal.diffiesKeys();
    p_ = p;
    a_ = a;
    k_ = toGamal.getYa();
    x_ = toGamal.getYb();
    K_ = toGamal.getK();
    m_ = m;
}
Gamal::~Gamal(){}

void Gamal::gamalEncrypt() {
    C_ = (K_ * m_) % p_;
}

void Gamal::gamalDecrypt() {
    Ki_ = modInverse(K_, p_);
    M_ = (Ki_ * C_) % p_;
}

void Gamal::showresults() {
    std::cout << "YA = "<< k_;
    std::cout << ", YB = "<< x_;
    std::cout << ", K = "<< K_;
    std::cout << ", C = "<< C_;
    std::cout << ", K⁻¹ = "<< Ki_;
    std::cout << ", M = "<< M_ << "\n";
}

int Gamal::gcdExtended(int a, int b, int* x, int* y)
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

int Gamal::modInverse(int a, int m)
{
    int x, y, res;
    int g = gcdExtended(a, m, &x, &y);
    if (g != 1) {
    std::cout << "No existe la inversa";
        return -1;
    }
    else
    {
        res = (x % m + m) % m;
        return res;
    }
}