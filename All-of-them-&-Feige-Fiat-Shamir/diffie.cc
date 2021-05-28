 #include "diffie.h"
int quickexp(int a, int b, int m) {
    int x = 1;
    int y = a % m;

    do {
        if (b % 2 != 0) {
            x = (x * y) % m;
            b = b - 1;
        }
        else {
            y = (y * y) % m;
            b = b / 2;
        }
    }while ((b > 0) && (y > 1) );

    return x;
}
 Diffie::Diffie(int p, int a, int A, int B) {
     p_ = p;
     a_ = a;
     A_ = A;
     B_ = B;
     error = false;
 }
 Diffie::~Diffie(){}

void Diffie::diffiesKeys() {
    int ka, kb;
    Ya_ = quickexp(a_, A_,p_);
    Yb_ = quickexp(a_, B_, p_);

    ka = quickexp(Yb_,A_,p_);
    kb = quickexp(Ya_,B_,p_);
    
    if (ka == kb)
        K_ = ka;
    else 
        error = true;
}

void Diffie::showResults() {
    std::cout << "ya = "<<Ya_<<std::endl;
    std::cout << "yb = "<< Yb_<<std::endl;
    std::cout << "K = "<< K_ <<std::endl;
}

int Diffie::getK() {
    if (!error)
        return K_;
    else {
        std::cout << "ERROR";
        return -1;
    }
}
int Diffie::getYa() {
    return Ya_;
}
int Diffie::getYb() {
    return Yb_;
}