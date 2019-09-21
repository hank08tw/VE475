#include <string>
#include <stdint.h>
#include <cstring>
#include <iostream>
#include "rc4.h"
#include <ctime>

using namespace std;

const char alphabet[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789,.;?!()";



void invalid_input()
{
    std::cout << "Invalid input!" << std::endl;
}

string generate()
{
    srand(time(0));
    string str;
    for (int i = 0; i < 16; i++)
    {
        str.push_back(alphabet[rand() % 69]);
    }
    return str;
}

int main(int argc, char *argv[])
{
    rc4 RC4;
    uint8_t alphabet_in[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1,
                                 1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                                 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1,
                                 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                                 1, 1, 0, 0, 0, 0, 0};
    if (argc <= 1) {
        invalid_input();
    }
    else if (strcmp(argv[1], "--generate") == 0) {
        std::cout << generate() << endl;
    }
    else if (strcmp(argv[1], "--encrypt") == 0 && argc == 3) {
        int flag = 1;
        for (int k = 0; k < strlen(argv[2]); k++) {
            if (alphabet_in[argv[2][k]] <= 0) {
                flag = 0;
                std::cout << "Invalid input! The plaintet must only contain characters in the given alphabet" << std::endl;
                break;
            }
        }
        if (flag == 1) {
            RC4.get_information_default(argv[2]);
            std::string ciphertext = RC4.rc4_encrypt();
            for (int i=0; i<ciphertext.length(); i++) {
                int temp = (int)ciphertext[i];
                if (temp < 0) {
                    temp += 256;
                }
                //cout << temp << endl;
                int x = temp / 16;
                int y = temp - x * 16;
                char z, w;
                switch (x) {
                    case 0: z='0'; break;
                    case 1: z='1'; break;
                    case 2: z='2'; break;
                    case 3: z='3'; break;
                    case 4: z='4'; break;
                    case 5: z='5'; break;
                    case 6: z='6'; break;
                    case 7: z='7'; break;
                    case 8: z='8'; break;
                    case 9: z='9'; break;
                    case 10: z='a'; break;
                    case 11: z='b'; break;
                    case 12: z='c'; break;
                    case 13: z='d'; break;
                    case 14: z='e'; break;
                    case 15: z='f'; break;
                }
                switch (y) {
                    case 0: w='0'; break;
                    case 1: w='1'; break;
                    case 2: w='2'; break;
                    case 3: w='3'; break;
                    case 4: w='4'; break;
                    case 5: w='5'; break;
                    case 6: w='6'; break;
                    case 7: w='7'; break;
                    case 8: w='8'; break;
                    case 9: w='9'; break;
                    case 10: w='a'; break;
                    case 11: w='b'; break;
                    case 12: w='c'; break;
                    case 13: w='d'; break;
                    case 14: w='e'; break;
                    case 15: w='f'; break;
                }
                std::cout<<z<<w;
            }
            //std::cout << ciphertext[0] << " " << ciphertext[1] << " " << ciphertext[15] << std::endl;
            //std::cout << ciphertext << std::endl;
            std::cout << endl;

        }
        
    }


    else if (argc==5 && (strcmp(argv[1], "--encrypt") == 0 && strcmp(argv[3], "--key") == 0)) {
        int flag = 1;
        for (int k = 0; k < strlen(argv[2]); k++) {
            if (alphabet_in[argv[2][k]] <= 0) {
                flag = 0;
                std::cout << "Invalid input! The plaintet must only contain characters in the given alphabet" << std::endl;
                break;
            }
        }


        if (flag == 1) {
            RC4.get_information(argv[4], argv[2]);
            std::string ciphertext = RC4.rc4_encrypt();
            for (int i=0; i<ciphertext.length(); i++) {
                int temp = (int)ciphertext[i];
                if (temp < 0) {
                    temp += 256;
                }
                //cout << temp << endl;
                int x = temp / 16;
                int y = temp - x * 16;
                char z, w;
                switch (x) {
                    case 0: z='0'; break;
                    case 1: z='1'; break;
                    case 2: z='2'; break;
                    case 3: z='3'; break;
                    case 4: z='4'; break;
                    case 5: z='5'; break;
                    case 6: z='6'; break;
                    case 7: z='7'; break;
                    case 8: z='8'; break;
                    case 9: z='9'; break;
                    case 10: z='a'; break;
                    case 11: z='b'; break;
                    case 12: z='c'; break;
                    case 13: z='d'; break;
                    case 14: z='e'; break;
                    case 15: z='f'; break;
                }
                switch (y) {
                    case 0: w='0'; break;
                    case 1: w='1'; break;
                    case 2: w='2'; break;
                    case 3: w='3'; break;
                    case 4: w='4'; break;
                    case 5: w='5'; break;
                    case 6: w='6'; break;
                    case 7: w='7'; break;
                    case 8: w='8'; break;
                    case 9: w='9'; break;
                    case 10: w='a'; break;
                    case 11: w='b'; break;
                    case 12: w='c'; break;
                    case 13: w='d'; break;
                    case 14: w='e'; break;
                    case 15: w='f'; break;
                }
                std::cout<<z<<w;
            }
            //std::cout << ciphertext[0] << " " << ciphertext[1] << " " << ciphertext[15] << std::endl;
            //std::cout << ciphertext << std::endl;
            std::cout << endl;
        }
        
    }
    ////////////////////////////////////////////////////////////////////////////////////////////
    else if (argc==5 && (strcmp(argv[3], "--encrypt") == 0 && strcmp(argv[1], "--key") == 0)) {
        int flag = 1;
        for (int k = 0; k < strlen(argv[4]); k++) {
            if (alphabet_in[argv[4][k]] <= 0) {
                flag = 0;
                std::cout << "Invalid input! The plaintet must only contain characters in the given alphabet" << std::endl;
                break;
            }
        }


        if (flag == 1) {
            RC4.get_information(argv[2], argv[4]);
            std::string ciphertext = RC4.rc4_encrypt();
            for (int i=0; i<ciphertext.length(); i++) {
                int temp = (int)ciphertext[i];
                if (temp < 0) {
                    temp += 256;
                }
                //cout << temp << endl;
                int x = temp / 16;
                int y = temp - x * 16;
                char z, w;
                switch (x) {
                    case 0: z='0'; break;
                    case 1: z='1'; break;
                    case 2: z='2'; break;
                    case 3: z='3'; break;
                    case 4: z='4'; break;
                    case 5: z='5'; break;
                    case 6: z='6'; break;
                    case 7: z='7'; break;
                    case 8: z='8'; break;
                    case 9: z='9'; break;
                    case 10: z='a'; break;
                    case 11: z='b'; break;
                    case 12: z='c'; break;
                    case 13: z='d'; break;
                    case 14: z='e'; break;
                    case 15: z='f'; break;
                }
                switch (y) {
                    case 0: w='0'; break;
                    case 1: w='1'; break;
                    case 2: w='2'; break;
                    case 3: w='3'; break;
                    case 4: w='4'; break;
                    case 5: w='5'; break;
                    case 6: w='6'; break;
                    case 7: w='7'; break;
                    case 8: w='8'; break;
                    case 9: w='9'; break;
                    case 10: w='a'; break;
                    case 11: w='b'; break;
                    case 12: w='c'; break;
                    case 13: w='d'; break;
                    case 14: w='e'; break;
                    case 15: w='f'; break;
                }
                std::cout<<z<<w;
            }
            //std::cout << ciphertext[0] << " " << ciphertext[1] << " " << ciphertext[15] << std::endl;
            //std::cout << ciphertext << std::endl;
            std::cout << endl;
        }
        
    }

    ////////////////////////////////////////////////////////////////////


    /////here appears the challengeciphertext!!!! Need to modify it

    else if (strcmp(argv[1], "--decrypt") == 0 && argc == 3) {
        //std::cout << "yes" << std::endl;
        if (strcmp(argv[2], "71284117da0c6e8aa12652ea95c4df5a8a5559e0d805c0fadb8495c5e41147badd25c0169b70844696fe427833e587d40c82f1bc37906dfea9898bb1af83d54e8f2a64de7e9b28c1fa40e14f5cd978e86168f0cb46726a604113ea7d015086527f27eba41be963f99f15334b324848303759bfbfa247df64ada01eeeda5535c96acc72d86c21a256151ebd57f5c843aef26b6335b1beef9f78d0b0e5e521251f16e19329ffcc8f9bd0c748191c493dbc6fe1") == 0) {
            std::cout << "cheater: it is forbidden to decrypt the challenge ciphertext" << std::endl;
        }
        else {
            int flag = 1;
            for (int k = 0; k < strlen(argv[2]); k++) {
                if ((strlen(argv[2]) % 2 == 1) || !(((argv[2][k] >= 48) && (argv[2][k] <= 57)) || ((argv[2][k] >= 97) && (argv[2][k] <= 102)))) {
                    flag = 0;
                    std::cout << "The ciphertext must be of an even number of characters and can only have 0~9 and a~f" << std::endl;
                    break;
                }
            }
            if (flag == 1) {
                rc4 RC4_2;
                RC4_2.get_information_default(argv[2]);
                std::cout << RC4_2.rc4_decrypt() << std::endl;
            }
        }
    }

    else if (strcmp(argv[1], "--decrypt") == 0 && strcmp(argv[3], "--key") == 0) {
        if (strcmp(argv[2], "71284117da0c6e8aa12652ea95c4df5a8a5559e0d805c0fadb8495c5e41147badd25c0169b70844696fe427833e587d40c82f1bc37906dfea9898bb1af83d54e8f2a64de7e9b28c1fa40e14f5cd978e86168f0cb46726a604113ea7d015086527f27eba41be963f99f15334b324848303759bfbfa247df64ada01eeeda5535c96acc72d86c21a256151ebd57f5c843aef26b6335b1beef9f78d0b0e5e521251f16e19329ffcc8f9bd0c748191c493dbc6fe1") == 0) {
            std::cout << "cheater: it is forbidden to decrypt the challenge ciphertext" << std::endl;
        }
        else {
            int flag = 1;
            for (int k = 0; k < strlen(argv[2]); k++) {
                if ((strlen(argv[2]) % 2 == 1) || !(((argv[2][k] >= 48) && (argv[2][k] <= 57)) || ((argv[2][k] >= 97) && (argv[2][k] <= 102)))) {
                    flag = 0;
                    std::cout << "The ciphertext must be of an even number of characters and can only have 0~9 and a~f" << std::endl;
                    break;
                }
            }
        //std::cout << "flag: " << flag << std::endl;
            if (flag == 1) {
                RC4.get_information(argv[4], argv[2]);
                std::cout << RC4.rc4_decrypt() << std::endl;
            }
        }
    }

    else if (strcmp(argv[3], "--decrypt") == 0 && strcmp(argv[1], "--key") == 0) {
        if (strcmp(argv[4], "71284117da0c6e8aa12652ea95c4df5a8a5559e0d805c0fadb8495c5e41147badd25c0169b70844696fe427833e587d40c82f1bc37906dfea9898bb1af83d54e8f2a64de7e9b28c1fa40e14f5cd978e86168f0cb46726a604113ea7d015086527f27eba41be963f99f15334b324848303759bfbfa247df64ada01eeeda5535c96acc72d86c21a256151ebd57f5c843aef26b6335b1beef9f78d0b0e5e521251f16e19329ffcc8f9bd0c748191c493dbc6fe1") == 0) {
            std::cout << "cheater: it is forbidden to decrypt the challenge ciphertext" << std::endl;
        }
        else {
            int flag = 1;
            for (int k = 0; k < strlen(argv[4]); k++) {
                if ((strlen(argv[4]) % 2 == 1) || !(((argv[4][k] >= 48) && (argv[4][k] <= 57)) || ((argv[4][k] >= 97) && (argv[4][k] <= 102)))) {
                    flag = 0;
                    std::cout << "The ciphertext must be of an even number of characters and can only have 0~9 and a~f" << std::endl;
                    break;
                }
            }
        //std::cout << "flag: " << flag << std::endl;
            if (flag == 1) {
                RC4.get_information(argv[2], argv[4]);
                std::cout << RC4.rc4_decrypt() << std::endl;
            }
        }
    }

    else {
        invalid_input();
    }
    return 0;
}