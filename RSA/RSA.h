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

public:
    RSA(int, int);                              // class constructor
    std::vector<int> encode(std::string);       // encoder function
    std::string decode(std::vector<int>);       // decoder function
    
    std::vector<int> encrypt(std::vector<int>);         // encryption function
    std::vector<int> decrypt(std::vector<int>, int);    // decryption function (requires key)

    // Utility functions
    int fast_exponentiation(int, int);
};