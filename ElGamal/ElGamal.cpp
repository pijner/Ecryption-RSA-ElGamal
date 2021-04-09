//
// Created by Prahar on 08-Apr.-2021.
//

#include "ElGamal.h"

/**
 * class constructor that takes in a prime number and primitive roots for ElGamal encryption. We find d using exhaustive search
 * 
 * @param p integer representing the prime number modulus for ElGamal algorithm
 * @param e1 integer representing first primitive root
 * @param e2 integer representing second primitive root
 */
ElGamal::ElGamal(int p, int e1, int e2) {
    _e1 = e1;
    _e2 = e2;
    _p = p;
    _d = 0;

    for (int i = 0; i < _p; i++) {
        if (this->_e2 == this->fast_exponentiation(this->_e1, i)) {
            _d = i;
            break;
        }
    }
}

/**
 * function to encode a given string of 3 (upper-case) letter words seperated by spaces
 * Consider alphabets from A-Z as integers from 0-25
 * Encoding is done by char1 * 26^2 + char2 * 26^1 + char3 * 26^0
 *
 * @param s string to be encoded
 * @return vector of integers representing encoded words from string
 */
std::vector<int> ElGamal::encode(std::string s) {
    std::vector<int> encoded;
    if (s.length() < 3)
        return encoded;

    for (int i = 0; i < s.length(); i += 4) {
        int c = 0;
        for (int k = 0; k < 3; k++) {
            c += (pow(26, 2 - k) * (((int)s[i + k]) - 65));
        }
        encoded.push_back(c);
    }

    return encoded;
}

/**
 * function to decode element in Zn to a 3 letter character
 * Consider alphabets from A-Z as integers from 0-25
 * Encoding is done by char1 * 26^2 + char2 * 26^1 + char3 * 26^0
 * 
 * @param encodedText integer vector consisting of endoced elements in Zn 
 * @return string consisting of decoded elements from input vector
 */
std::string ElGamal::decode(std::vector<int> encodedText) {
    std::string s = "";
    for (int i = 0; i < encodedText.size(); i++) {
        int c = encodedText[i];
        std::string thisWord = "";
        for (int j = 0; j < 3; j++) {
            int thisChar = c % 26;
            thisWord = ((char)(thisChar + 65)) + thisWord;
            c = (c - thisChar) / 26;
        }
        s = s + thisWord + " ";
    }
    return s;
}


std::vector<std::pair<int, int>> ElGamal::encrypt(std::vector<int> encodedText) {
    // not implemented
    std::vector<std::pair<int, int>> encrypted;
    return encrypted;
}

/**
 * function to decrypt given ElGamal cipher based on parameters used in the constructor
 *
 * @param encryptedText vector of pair of integers representing c1 and c2 for ElGamal decryption
 * @return vector of integers representing decrypted elements
 */
std::vector<int> ElGamal::decrypt(std::vector<std::pair<int, int>> encryptedText) {
    std::vector<int> decrypted;

    for (std::pair<int, int> encryptedPair : encryptedText) {
        int c1 = encryptedPair.first;
        int c2 = encryptedPair.second;

        int decryptedText = (c2 * this->mod_inverse(this->fast_exponentiation(c1, this->_d)) + this->_p) % this->_p;
        decrypted.push_back(decryptedText);
    }

    return decrypted;
}

/**
 * function to perform fast exponentiation in mod _p (class parameter)
 * a^x mod _p
 * 
 * @param a integer representing the base
 * @param x integer representing the exponenet
 * @return value of a^x mod _p
 */
int ElGamal::fast_exponentiation(int a, int x) {
    int y = 1;

    // get binary representations for a and x
    std::string aBinary = std::bitset<16>(a).to_string();
    std::string xBinary = std::bitset<16>(x).to_string();
    
    // convert string to binary for aBinary
    int aBin = std::stoi(aBinary, nullptr, 2);

    for (int i = xBinary.size() - 1; i >= 0; i--) {
        char thisDigit = xBinary[i];
        if (thisDigit == '1')
            y = (aBin * y + this->_p) % this->_p;
        aBin = (aBin * aBin + this->_p) % this->_p;
    }

    return y;
}

/**
 * function to calculate inverse of a number in mod _p using euclidean algorithm
 * 
 * @param a integer representing number whose inverse is to be calculated
 * @return inverse of number
 */
int ElGamal::mod_inverse(int a) {
    int x = 1, y = 0, s = 0, t = 1, m, n, q, r;
    int p_temp = _p;

    // euclidean algorithm
    while (a) {
        q = p_temp / a;
        r = p_temp % a;

        m = s - (q * x);
        n = t - (q * y);

        s = x;
        x = m;

        t = y;
        y = n;

        p_temp = a;
        a = r;
    }

    return (s + _p) % _p;
}