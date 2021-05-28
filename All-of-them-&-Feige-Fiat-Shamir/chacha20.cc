#include "chacha20.h"

std::string toHex( uint32_t i )
{
  std::stringstream stream;
         stream << std::setfill ('0') << std::setw(sizeof(uint32_t)*2)
         << std::hex << i;
  return stream.str();
}


ChaCha20::ChaCha20(uint32_t keycntnonce[12]) {
    const uint32_t const1 = 0x61707865;
    const uint32_t const2 = 0x3320646e;
    const uint32_t const3 = 0x79622d32;
    const uint32_t const4 = 0x6b206574;

    in_[0] = const1;
    in_[1] = const2;
    in_[2] = const3;
    in_[3] = const4;
    int j = 4;

    for (int i = 0; i < 12; i++) {
        in_[j] = keycntnonce[i];
        j++;
    }

}
ChaCha20::~ChaCha20(){}

void ChaCha20::ChaChaBlock() {
    int i;
	for (i = 0; i < 16; ++i)	
		x_[i] = in_[i];
	// 10 loops × 2 rounds/loop = 20 rounds
	for (i = 0; i < ROUNDS; i += 2) {
		// Odd round
		QR(x_[0], x_[4], x_[ 8], x_[12]); // column 0
		QR(x_[1], x_[5], x_[ 9], x_[13]); // column 1
		QR(x_[2], x_[6], x_[10], x_[14]); // column 2
		QR(x_[3], x_[7], x_[11], x_[15]); // column 3
		// Even round
		QR(x_[0], x_[5], x_[10], x_[15]); // diagonal 1 (main diagonal)
		QR(x_[1], x_[6], x_[11], x_[12]); // diagonal 2
		QR(x_[2], x_[7], x_[ 8], x_[13]); // diagonal 3
		QR(x_[3], x_[4], x_[ 9], x_[14]); // diagonal 4
	}

    for (i = 0; i < 16; ++i) {
        af20_[i] = x_[i];
    }

	for (i = 0; i < 16; ++i)
		out_[i] = x_[i] + in_[i];
}

void ChaCha20::ShowResult() {
    int i;
    int counter = 0;

    std::cout << "Estado inicial=\n";
    for (i = 0; i < 16; i++) {
        std::cout << toHex(in_[i]) << " ";
        counter++;
        if (counter == 4) {
            std::cout << "\n";
            counter = 0;
        }
}
    counter = 0;
    std::cout << "\nEstado final tras 20 iteraciones=\n";
    for (i = 0; i < 16; i++) {
        std::cout << toHex(af20_[i]) << " ";
        counter++;
        if (counter == 4) {
            std::cout << "\n";
            counter = 0;
        }
    }
    counter = 0;
    std::cout << "\nEstado de salida del generador=\n";
    for (i = 0; i < 16; i++) {
        std::cout << toHex(out_[i]) << " ";
        counter++;
        if (counter == 4) {
            std::cout << "\n";
            counter = 0;
        }
    }
    std::cout << "\n";
}