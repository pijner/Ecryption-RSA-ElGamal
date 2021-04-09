# Ecryption-RSA-ElGamal

## Requirements
GCC or any other C++ compiler with standard libraries

## How to run
* RSA
  - Navigate to the RSA subfoler using a terminal and run the following command (switch ./ tp .\ for Windows)

        $ g++ *.cpp -o RSA-Cipher; ./RSA-Cipher
      
  - The program will prompt you to enter a string to encrypt. This is done to verify the encoding and encryption functions are working as defined in the project requirements. Type `DOG CAT ZZZ` to see the expected output from the requirements.
  - The program will proceed to read and decrypt the `message.txt` file in the RSA directory.

* ElGamal
  - Navigate to the ElGamal subfoler using a terminal and run the following command (switch ./ tp .\ for Windows)
        
        $ g++ *.cpp -o ElGamal-Cipher; ./ElGamal-Cipher
  - The program will autonomously read the file and compute the decryption key to decrypt the file based on the parameters given inn the project requirement
