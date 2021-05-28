#include "vigenere.h"
#include "rc4.h"
#include "chacha20.h"
#include "cagps.h"
#include "binarymul.h"
#include "cbc.h"
#include "gamal.h"
#include "rsa.h"
#include "eldifhel.h"
#include "fefisha.h"

#define prsize 11
#define chsk 8
#define chmx 12
#define sz 32

struct prtc {
    std::string name;
    int number;
};

class Menu {
    private:
        std::string pname_;
        std::vector<prtc> pnames_;
    public:
    Menu(std::string pname);
    ~Menu();
    void menuSwitch();
    void vigenere();
    void rc4();
    void chaCha20();
    void c_a();
    void snowAes();
    void aesF();
    void aesCbc();
    void elGamal();
    void rsa();
    void eldifhel();
    void fefishaF();
    private:
    void initializePractices();
};