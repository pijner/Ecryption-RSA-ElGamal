#pragma once

#include "vector"
#include <string>
#include <bitset>
#include <cmath>

/**
 * Class to implement ElGamal encryption and decryption
 */
class ElGamal {
private:
    int _p;     // prime number to use for mod calculations
    int _e1;    // first primitive root
    int _e2;    // second primitive root
    int _d;     // decryption key (calculated in constructor)

public:
    ElGamal(int p, int e1, int e2);                     // class constructor
    std::vector<int> encode(std::string s);             // encoder function
    std::string decode(std::vector<int> encodedText);   // decoder function

    std::vector<std::pair<int, int>> encrypt(std::vector<int> encodedText);     // encryption function
    std::vector<int> decrypt(std::vector<std::pair<int, int>> encryptedText);   // decryption function

    // Utility functions
    int fast_exponentiation(int a, int x);
    int mod_inverse(int a);
};
