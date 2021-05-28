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
        int p_;
        int q_;
        int d_;
        int e_;
        int euclidean_;
        int n_;
        std::vector<char> upalphabet_;
        std::vector<int> decimals_;
        std::vector<int> cipher_;
        int blocksize_;
    public:
        Rsa(std::string message, int p, int q, int d);
        ~Rsa();

        bool lehmanPeralta(int prime);
        int quickExp(long long a, unsigned int b, int m);
        int gcdExtended(int a, int b, int* x, int* y);
        bool isDprime(int d, int m);
        void encrypt();
        void showResult();
    private:
        void initializeAlphabet();
        std::string removeSpaces(std::string &str);
        int convertToDecimal(std::string str);
};