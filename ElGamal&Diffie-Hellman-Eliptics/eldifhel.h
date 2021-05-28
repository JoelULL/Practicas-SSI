#include <iostream>
#include <vector>
#include <string>
#include <math.h>
#include <bitset>
#include <ctime>

#define eucmax 100

struct G {
    long x;
    long y;
};

class ElDiffieHel {
    private:
    long p_;
    long a_;
    long b_;
    G G_;
    long da_;
    long db_;
    long s_;
    long x3_;
    long y3_;
    long m_;
    long M_;
    long h_;
    std::vector<G> curvepoints_;
    std::vector<G> msgpoints_;
    G dbG_;
    G daG_;
    G mPoint_;

    public:
    ElDiffieHel(long p, long a, long b, long gx, long gy, long db, long da, long m);
    ~ElDiffieHel();
    void pointGenerator();
    G equalPoints(G p);
    G difPoints(G p, G q);
    G doubleAndAdd(G p, long k);
    void showResult();
    void keyGen();
    void gamalCodeMessage();
    bool validPoint();
    bool lehmanPeralta(long prime);
    bool checkAandB();

    private:
    long gcdExtended(long a, long b, long* x, long* y);
    long modInverse(long a, long m);
    long quickExp(long long a, unsigned long b, long m);
    long mod(long a, long b);
    long modulo (long n, long p);
    long negativeModInverse(long n, long p);
};

std::ostream& operator << (std::ostream &o,const G &p);
bool operator==(const G& lhs, const G& rhs);
