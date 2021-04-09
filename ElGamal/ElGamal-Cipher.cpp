/**
 * ElGamal-Cipher.cpp : This file contains the 'main' function. 
 * @author Prahar Ijner
 */

#include <iostream>
#include "vector"
#include "fstream"
#include "ElGamal.h"
#include <cmath>
#include <string>

std::vector<std::pair<int, int>> readCipherFromFile(std::string);

int main() {
    std::vector<std::pair<int, int>> cipher = readCipherFromFile("cipherText.txt");

    ElGamal elg(31847, 5, 18074);

    std::vector<int> decrypted = elg.decrypt(cipher);
    std::string plainText = elg.decode(decrypted);
    std::cout << plainText << std::endl;

    return 0;
}

/**
 * function to read cipher text from given text file. The cipher is in the format (c1, c2) and there are multiple in the file
 *
 * @param filename string representing the name or path to the file
 * @return a vector of integer pairs consisting c1 and c2 from the file
 */
std::vector<std::pair<int, int>> readCipherFromFile(std::string filename) {
    char buffer;
    int c1, c2;
    std::vector<std::pair<int, int>> cipherText;

    std::ifstream fileReader(filename);
    if (fileReader) {
        while (fileReader.eof() == 0) {
            fileReader >> buffer >> c1 >> buffer >> c2 >> buffer;
            cipherText.emplace_back(c1, c2);
        }
    }
    return cipherText;
}