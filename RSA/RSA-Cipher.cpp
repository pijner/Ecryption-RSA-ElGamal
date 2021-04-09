// RSA-Cipher.cpp : This file contains the 'main' function. 
// @author: Prahar Ijner
//

#include <iostream>
#include "RSA.h"
#include <fstream>

std::vector<int> readCipherFromFile(std::string);

int main()
{
    RSA r(31313, 4913);

    // testing for DOG CAT ZZZ example given
    std::string input;
    std::cout << "Enter string to encrypt ";
    std::getline(std::cin, input);

    std::vector<int> encoded = r.encode(input);
    std::cout << "Encoded string: ";
    for (int i : encoded)
        std::cout << i << " ";
    std::cout << std::endl;

    std::cout << "Encrypted string: ";
    std::vector<int> encrypted = r.encrypt(encoded);
    for (int i : encrypted)
        std::cout << i << " ";
    std::cout << std::endl;

    // Read given cipher message from file and decrypt and decode it
    encrypted = readCipherFromFile("message.txt");
    std::vector<int>  decrypted = r.decrypt(encrypted, 6497);
    std::string decoded = r.decode(decrypted);
    std::cout << "\n\nMessage in file: \n";
    std::cout << decoded << std::endl;

    return 0;
}

/**
 * function to read cipher text from given text file. The cipher is stores as integers seperated by spaces
 *
 * @param filename string representing the name or path to the file
 * @return a vector of integers consisting cipher from the file
 */
std::vector<int> readCipherFromFile(std::string filename) {
    std::vector<int> encryptedMessage;
    std::ifstream fileReader(filename);

    if (fileReader) {
        while (fileReader.eof() == 0) {
            int num = 0;
            fileReader >> num;
            encryptedMessage.push_back(num);
        }

    }

    return encryptedMessage;
}