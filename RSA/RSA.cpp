#include "RSA.h"
#include <bitset>
#include <iostream>

/**
 * class constructor that takes in the base and encryption key for RSA
 *
 * @param n integer representing modulus base to be used
 * @param e integer representing the encryption key for RSA
 */
RSA::RSA(int n, int e) {
    this->_n = n;
    this->_e = e;

    // calculate prime numbers that were used to select n
    int p, q;
    for (int i = 2; i < sqrt(_n); i++) {
        if ((_n % i) == 0 && is_prime(i)) {
            int factor2 = _n / i;
            if (is_prime(factor2)) {
                p = i, q = factor2;
                break;
            }
        }
    }

    // calculate phi(n)
    int phi = (p - 1) * (q - 1);
    this->_d = mod_inverse(this->_e, phi);
}

/**
 * function to perform RSA encryption on a vector of integers
 * 
 * @param encodedText a vector of integers representing text encoded using the encode() function (below)
 * @return vector of integers encrypted using RSA 
 */
std::vector<int> RSA::encrypt(std::vector<int> encodedText) {
    std::vector<int> encrypted;
    for (int p : encodedText) {
        encrypted.push_back(this->fast_exponentiation(p, this->_e));
    }
    return encrypted;
}

/**
 * function to perform RSA decryption on a vector of integers
 *
 * @param encodedText a vector of integers representing text encoded using the encode() function (below)
 * @param d decryption key for RSA
 * @return vector of integers encrypted using RSA
 */
std::vector<int> RSA::decrypt(std::vector<int> encryptedText) {
    std::vector<int> decrypted;
    for (int c : encryptedText) {
        decrypted.push_back(this->fast_exponentiation(c, this->_d));
    }
    return decrypted;
}

/**
 * function to encode a given string of 3 (upper-case) letter words seperated by spaces
 * Consider alphabets from A-Z as integers from 0-25
 * Encoding is done by char1 * 26^2 + char2 * 26^1 + char3 * 26^0
 *
 * @param s string to be encoded
 * @return vector of integers representing encoded words from string
 */
std::vector<int> RSA::encode(std::string s) {
    std::vector<int> encoded;
    if (s.length() < 3)
        return encoded;

    for (int i = 0; i < s.length(); i += 4) {
        int c = 0;
        for (int k = 0; k < 3; k++) {
            c += (pow(26, 2-k) * (((int)s[i + k]) - 65));
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
std::string RSA::decode(std::vector<int> encodedText) {
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

/**
 * function to perform fast exponentiation in mod _p (class parameter)
 * a^x mod _p
 *
 * @param a integer representing the base
 * @param x integer representing the exponenet
 * @return value of a^x mod _p
 */
int RSA::fast_exponentiation(int a, int x) {
    int y = 1;

    // get binary representations for a and x
    std::string aBinary = std::bitset<16>(a).to_string();
    std::string xBinary = std::bitset<16>(x).to_string();

    // convert string to binary for aBinary
    int aBin = std::stoi(aBinary, nullptr, 2);

    for (int i = xBinary.size() - 1; i >= 0; i--) {
        char thisDigit = xBinary[i];
        if (thisDigit == '1')
            y = (aBin * y + this->_n) % this->_n;
        aBin = (aBin * aBin + this->_n) % this->_n;
    }

    return y;
}

/**
 * function to check if a number is prime or not
 * 
 * @param a number to check
 * @return boolean value representing if the input if prime or not
 */
bool RSA::is_prime(int a) {
    if (a < 1)
        return false;
    else if (a < 3) 
        return true;
    
    for (int i = 5; i < sqrt(a); i += 6) {
        if (a % i == 0 || a % (i + 6) == 0)
            return false;
    }

    return true;
}

/**
 * function to calculate inverse of a number in mod _p using euclidean algorithm
 *
 * @param a integer representing number whose inverse is to be calculated
 * @return inverse of number
 */
int RSA::mod_inverse(int a, int mod) {
    int x = 1, y = 0, s = 0, t = 1, m, n, q, r;
    int p_temp = mod;

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

    return (s + mod) % mod;
}