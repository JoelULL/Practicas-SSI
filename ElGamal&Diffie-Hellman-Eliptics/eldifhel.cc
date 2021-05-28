#include "eldifhel.h"

ElDiffieHel::ElDiffieHel(long p, long a, long b, long gx, long gy, long db, long da, long m) {
    p_ = p;
    a_ = a;
    b_ = b;
    pointGenerator();
    G_.x = gx;
    G_.y = gy;
    db_ = db;
    da_ = da;
    m_ = m;
    
}

ElDiffieHel::~ElDiffieHel() {}

void ElDiffieHel::pointGenerator() {
    std::vector<long> xcalc;
    std::vector<long> ycalc;
    G aux;
    for (long i = 0; i < p_; i++) {
        long x = (pow(i, 3) + (a_ * i) + b_);
        long y = (pow(i, 2));
        xcalc.push_back( x % p_);
        ycalc.push_back( y % p_);
    }
    for (size_t i = 0; i < xcalc.size(); i++) {
        for (size_t j = 0; j < ycalc.size(); j++) {
            if (xcalc[i] == ycalc[j]) {
                aux.x = i;
                aux.y = j;
                curvepoints_.push_back(aux);
            }
        }
    }
}

G ElDiffieHel::equalPoints(G p) {
    long num;
    long dem;
    G result;

    num = 3 * pow(p.x, 2) + a_;
    dem = 2 * p.y;
    num = mod(num, p_);
    if(dem < 0)
        dem = negativeModInverse(dem, p_);
    else
        dem = modInverse(dem, p_);
    s_ = mod((num * dem), p_);

    x3_ = pow(s_,2) - p.x - p.x;
    y3_ = (s_ * (p.x - x3_)) - p.y;

    result.x = mod(x3_, p_);
    result.y = mod(y3_, p_);

    return result;
}

G ElDiffieHel::difPoints(G p, G q) {
    long num, dem;
    G result;
    num = q.y - p.y;
    dem = q.x - p.x;
    if( dem < 0)
        dem = negativeModInverse(dem, p_);
    else
        dem = modInverse(dem , p_);

    s_ = mod((num * dem) , p_);
    x3_ = pow(s_,2) - p.x - q.x;
    y3_ = (s_ * (p.x - x3_)) - p.y;

    result.x = mod(x3_, p_);
    result.y = mod(y3_, p_);
    
    return result;
}


void ElDiffieHel::gamalCodeMessage() {
    long x = -1;
    bool founded = false;
    G encoding;


    if (mod(m_, 2) == 0)
        M_ = m_ + 2;
    else 
        M_ = m_ + 1;

    h_ = p_ / M_;

    for (int j = 0; j < h_; j++) {
        if (!founded)
            x = (m_ * h_) + j;
        else
            break;
        for (size_t i = 0; i < curvepoints_.size(); i++) {
            if (curvepoints_[i].x == x) {
                founded = true;
                mPoint_ = curvepoints_[i];
                break;
            } 
        }
    }
    dbG_ = doubleAndAdd(G_,db_);
    daG_ = doubleAndAdd(G_,da_);

    encoding = doubleAndAdd(dbG_,da_);
    encoding = difPoints(mPoint_, encoding);

    msgpoints_.push_back(encoding);
    msgpoints_.push_back(daG_);
}

long ElDiffieHel::gcdExtended(long a, long b, long* x, long* y)
{
    if (a == 0)
    {
        *x = 0, *y = 1;
        return b;
    }
    long x1, y1;
    long gcd = gcdExtended(mod(b,a), a, &x1, &y1);

    *x = y1 - (b / a) * x1;
    *y = x1;

    return gcd;
}

long ElDiffieHel::modInverse(long a, long m)
{
    long x, y, res;
    long g = gcdExtended(a, m, &x, &y);
    if (g != 1) {
        return 0;
    }
    else
    {
        res = mod((mod(x,m)+ m),m);
        return res;
    }
}

void ElDiffieHel::showResult() {
    std::cout << "Puntos de la curva: ";
    for (size_t  i = 0; i < curvepoints_.size(); i++) {
        std::cout << "(" << curvepoints_[i].x << ", " << curvepoints_[i].y << ")";
        if (i != curvepoints_.size() - 1)
            std::cout << ", ";
    }
    std::cout << "\nClave pública de B: punto dBG = "<< dbG_ << "\n";
    std::cout << "Clave pública de B: punto dAG = "<< daG_ << "\n";
    std::cout << "Clave secreta compartida calculada por A: "<< da_ << "*" 
        << dbG_ << " = "<< doubleAndAdd(dbG_, da_) << "\n";
    std::cout << "Clave secreta compartida calculada por b: "<< db_ << "*" 
        << daG_ << " = "<< doubleAndAdd(daG_, db_) << "\n";
    std::cout << "M = "<< M_ << "\n";
    std::cout << "h = " << h_ << " < " << p_ << " / " << M_ << "\n";
    std::cout << "Mensaje original codificado comopunto Qm ="<< mPoint_ << "\n";
    std::cout << "Mensaje cifrado y clave pública enviados de A a B: {Qm+dA*(dBG), dAG} = {";
    for (size_t i = 0; i < msgpoints_.size(); i++) {
        std::cout << msgpoints_[i];
        if (i != msgpoints_.size() - 1)
            std::cout << " ,";
    }
    std::cout << "}\n";
}

G ElDiffieHel::doubleAndAdd(G p, long k) {
    G result;
    result.x = 0;
    result.y = 0;
    
    if (k == 0)
        return result;

    if (k == 1)
        return p;

    if (mod(k, 2) == 1)
        return difPoints(p,doubleAndAdd(p, k - 1));
    else
        return doubleAndAdd(equalPoints(p), k / 2);

}

bool ElDiffieHel::validPoint() {
    for (size_t i = 0; i < curvepoints_.size(); i++) {
        if (G_ == curvepoints_[i])
            return true;
    }
    return false;
}

long ElDiffieHel::quickExp(long long a, unsigned long b, long m) {
    long res = 1;     

    a = mod(a, m); 
                
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

long ElDiffieHel::mod(long  a, long b) {
    long long int ret = a % b;
    if (ret < 0)
        ret += b;
    return ret;
}

long ElDiffieHel::modulo (long n, long p) {
    long r = n%p;
    if(((p > 0) && (r < 0)) || ((p < 0) && (r > 0)))
        r += p;
    return r;
}
long ElDiffieHel::negativeModInverse(long n, long p) {
    n = modulo(n, p);
    for(int x = 1; x < p; x++) {
        if(modulo(n*x, p) == 1) return x;
    }
    return 0;
}

std::ostream& operator << (std::ostream &o,const G &p)
{
    o << "(" << p.x << ", " << p.y << ")";
    return o;
}

bool operator==(const G& lhs, const G& rhs) {
    return lhs.x == rhs.x && lhs.y == rhs.y;
}

bool ElDiffieHel::lehmanPeralta(long prime) {
    std::vector<long> lprimes = {2, 5, 7, 11};
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

bool ElDiffieHel::checkAandB() {
    long op = (4 * pow(a_, 3) ) + (27 * pow(b_, 2) );
    if (op % p_ == 0)
        return false; 
    return true;
}