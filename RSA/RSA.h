# pragma once

#include <string>
#include <math.h>
#include <vector>

/**
 * Class to implement RSA encryption and decryption
 */
class RSA {
private:
    int _n;         // number for modulous
    int _e;         // encruption key
    int _d;         // decryption key (auto calculated)

public:
    RSA(int, int);                              // class constructor
    std::vector<int> encode(std::string);       // encoder function
    std::string decode(std::vector<int>);       // decoder function
    
    std::vector<int> encrypt(std::vector<int>);         // encryption function
    std::vector<int> decrypt(std::vector<int>);         // decryption function

    // Utility functions
    int fast_exponentiation(int, int);
    bool is_prime(int);
    int mod_inverse(int, int);
};