#include <iostream>
#include <vector>
#include <string>

class Diffie {
    private:
        int p_;
        int a_;
        int A_;
        int B_;
        int Ya_;
        int Yb_;
        int K_;
    public:
        Diffie(int p, int a, int A, int B);
        ~Diffie();
        void diffiesKeys();
        void showResults();

        int getK();
        int getYa();
        int getYb();
    private:
        bool error;
};