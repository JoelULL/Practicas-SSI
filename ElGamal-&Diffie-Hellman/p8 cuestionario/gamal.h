#include "diffie.h"

class Gamal {
    private:
    int p_;
    int a_;
    int k_;
    int x_;
    int m_;
    int C_;
    int K_;
    int Ki_;
    int M_;

    public:
    Gamal(int p, int a, int k, int x, int m);
    ~Gamal();
    void gamalEncrypt();
    void gamalDecrypt();

    void showresults();
    int modInverse(int a, int m);

    private:
    int gcdExtended(int a, int b, int* x, int* y);
    
};