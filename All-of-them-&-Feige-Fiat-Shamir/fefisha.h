#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <math.h>
#include <algorithm>

#define max 100

class Fefisha {
    private:
        long p_;
        long q_;
        long i_;
        long x_;
        long n_;
        long r_;
        long witness_;
        long y_;
        long powy_;
        long verified_;
        unsigned int sign_;
        std::vector<long> s_;
        std::vector<long> v_;
        std::vector<int> a_;
        bool checked_;
    public:
    Fefisha(long p, long q, long i, long r, std::string sign);
    ~Fefisha();

    bool lehmanPeralta(long prime);
    long quickExp(long long a, unsigned long b, long m);
    long gcdExtended(long a, long b, long* x, long* y);
    bool isXPrime(long x, long m);
    void protocol();
    void showResult();
};