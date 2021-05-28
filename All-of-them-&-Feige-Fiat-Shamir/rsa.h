#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <math.h>
#include <algorithm>


#define eucmax 100
#define base 26

class Rsa {
    private:
        std::string message_;
        long p_;
        long q_;
        long d_;
        long e_;
        long euclidean_;
        long n_;
        std::vector<char> upalphabet_;
        std::vector<long> decimals_;
        std::vector<long> cipher_;
        size_t blocksize_;
    public:
        Rsa(std::string message, long p, long q, long d);
        ~Rsa();

        bool lehmanPeralta(long prime);
        long quickExp(long long a, unsigned long b, long m);
        long gcdExtended(long a, long b, long* x, long* y);
        bool isDprime(long d, long m);
        void encrypt();
        void showResult();
    private:
        void initializeAlphabet();
        std::string removeSpaces(std::string &str);
        long convertToDecimal(std::string str);
};