#include <iostream>
#include <string>
#include <vector>
#include <stdint.h>
#include <iomanip>
#include <climits>
#define ROTL(a,b) (((a) << (b)) | ((a) >> (32 - (b))))
#define QR(a, b, c, d) (			\
	a += b,  d ^= a,  d = ROTL(d,16),	\
	c += d,  b ^= c,  b = ROTL(b,12),	\
	a += b,  d ^= a,  d = ROTL(d, 8),	\
	c += d,  b ^= c,  b = ROTL(b, 7))
#define ROUNDS 20
 
class ChaCha20 {
    private:
    uint32_t out_[16];
    uint32_t in_[16];
    uint32_t x_[16];
    uint32_t af20_[16];
    public:
    ChaCha20(uint32_t keycntnonce[12]);
    ~ChaCha20();

   void ChaChaBlock();
   void ShowResult();
};

