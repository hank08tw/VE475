#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <memory.h>
using namespace std;
void generate()
{
    char alphabet[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789,.;?!()";
    srand(time(NULL));
    //string tmp;
    for (int i=0;i<=15;i++){
        //str.push_back(alphabet[rand() % 69]);
        cout << alphabet[rand()%69];
    }
    cout << endl;
    //return str;
}
void swap_two(uint8_t *first, uint8_t *second)
{
    uint8_t tmp = *first;
    *first = *second;
    *second = tmp;
}
// sbox is copied from slide, invsbox is derived from sbox, rcon is copied from wiki.
uint8_t rcon[256] = {0x8d, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36, 0x6c, 0xd8, 0xab, 0x4d, 0x9a,
        0x2f, 0x5e, 0xbc, 0x63, 0xc6, 0x97, 0x35, 0x6a, 0xd4, 0xb3, 0x7d, 0xfa, 0xef, 0xc5, 0x91, 0x39,
        0x72, 0xe4, 0xd3, 0xbd, 0x61, 0xc2, 0x9f, 0x25, 0x4a, 0x94, 0x33, 0x66, 0xcc, 0x83, 0x1d, 0x3a,
        0x74, 0xe8, 0xcb, 0x8d, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36, 0x6c, 0xd8,
        0xab, 0x4d, 0x9a, 0x2f, 0x5e, 0xbc, 0x63, 0xc6, 0x97, 0x35, 0x6a, 0xd4, 0xb3, 0x7d, 0xfa, 0xef,
        0xc5, 0x91, 0x39, 0x72, 0xe4, 0xd3, 0xbd, 0x61, 0xc2, 0x9f, 0x25, 0x4a, 0x94, 0x33, 0x66, 0xcc,
        0x83, 0x1d, 0x3a, 0x74, 0xe8, 0xcb, 0x8d, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b,
        0x36, 0x6c, 0xd8, 0xab, 0x4d, 0x9a, 0x2f, 0x5e, 0xbc, 0x63, 0xc6, 0x97, 0x35, 0x6a, 0xd4, 0xb3,
        0x7d, 0xfa, 0xef, 0xc5, 0x91, 0x39, 0x72, 0xe4, 0xd3, 0xbd, 0x61, 0xc2, 0x9f, 0x25, 0x4a, 0x94,
        0x33, 0x66, 0xcc, 0x83, 0x1d, 0x3a, 0x74, 0xe8, 0xcb, 0x8d, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20,
        0x40, 0x80, 0x1b, 0x36, 0x6c, 0xd8, 0xab, 0x4d, 0x9a, 0x2f, 0x5e, 0xbc, 0x63, 0xc6, 0x97, 0x35,
        0x6a, 0xd4, 0xb3, 0x7d, 0xfa, 0xef, 0xc5, 0x91, 0x39, 0x72, 0xe4, 0xd3, 0xbd, 0x61, 0xc2, 0x9f,
        0x25, 0x4a, 0x94, 0x33, 0x66, 0xcc, 0x83, 0x1d, 0x3a, 0x74, 0xe8, 0xcb, 0x8d, 0x01, 0x02, 0x04,
        0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36, 0x6c, 0xd8, 0xab, 0x4d, 0x9a, 0x2f, 0x5e, 0xbc, 0x63,
        0xc6, 0x97, 0x35, 0x6a, 0xd4, 0xb3, 0x7d, 0xfa, 0xef, 0xc5, 0x91, 0x39, 0x72, 0xe4, 0xd3, 0xbd,
        0x61, 0xc2, 0x9f, 0x25, 0x4a, 0x94, 0x33, 0x66, 0xcc, 0x83, 0x1d, 0x3a, 0x74, 0xe8, 0xcb, 0x8d};

uint8_t sbox[256] = {0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76,
        0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0,
        0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15,
        0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75,
        0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84,
        0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf,
        0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8,
        0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2,
        0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73,
        0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb,
        0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79,
        0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08,
        0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a,
        0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e,
        0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf,
        0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16};

uint8_t invsbox[256] = {0x52, 0x09, 0x6a, 0xd5, 0x30, 0x36, 0xa5, 0x38, 0xbf, 0x40, 0xa3, 0x9e, 0x81, 0xf3, 0xd7, 0xfb,
        0x7c, 0xe3, 0x39, 0x82, 0x9b, 0x2f, 0xff, 0x87, 0x34, 0x8e, 0x43, 0x44, 0xc4, 0xde, 0xe9, 0xcb,
        0x54, 0x7b, 0x94, 0x32, 0xa6, 0xc2, 0x23, 0x3d, 0xee, 0x4c, 0x95, 0x0b, 0x42, 0xfa, 0xc3, 0x4e,
        0x08, 0x2e, 0xa1, 0x66, 0x28, 0xd9, 0x24, 0xb2, 0x76, 0x5b, 0xa2, 0x49, 0x6d, 0x8b, 0xd1, 0x25,
        0x72, 0xf8, 0xf6, 0x64, 0x86, 0x68, 0x98, 0x16, 0xd4, 0xa4, 0x5c, 0xcc, 0x5d, 0x65, 0xb6, 0x92,
        0x6c, 0x70, 0x48, 0x50, 0xfd, 0xed, 0xb9, 0xda, 0x5e, 0x15, 0x46, 0x57, 0xa7, 0x8d, 0x9d, 0x84,
        0x90, 0xd8, 0xab, 0x00, 0x8c, 0xbc, 0xd3, 0x0a, 0xf7, 0xe4, 0x58, 0x05, 0xb8, 0xb3, 0x45, 0x06,
        0xd0, 0x2c, 0x1e, 0x8f, 0xca, 0x3f, 0x0f, 0x02, 0xc1, 0xaf, 0xbd, 0x03, 0x01, 0x13, 0x8a, 0x6b,
        0x3a, 0x91, 0x11, 0x41, 0x4f, 0x67, 0xdc, 0xea, 0x97, 0xf2, 0xcf, 0xce, 0xf0, 0xb4, 0xe6, 0x73,
        0x96, 0xac, 0x74, 0x22, 0xe7, 0xad, 0x35, 0x85, 0xe2, 0xf9, 0x37, 0xe8, 0x1c, 0x75, 0xdf, 0x6e,
        0x47, 0xf1, 0x1a, 0x71, 0x1d, 0x29, 0xc5, 0x89, 0x6f, 0xb7, 0x62, 0x0e, 0xaa, 0x18, 0xbe, 0x1b,
        0xfc, 0x56, 0x3e, 0x4b, 0xc6, 0xd2, 0x79, 0x20, 0x9a, 0xdb, 0xc0, 0xfe, 0x78, 0xcd, 0x5a, 0xf4,
        0x1f, 0xdd, 0xa8, 0x33, 0x88, 0x07, 0xc7, 0x31, 0xb1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xec, 0x5f,
        0x60, 0x51, 0x7f, 0xa9, 0x19, 0xb5, 0x4a, 0x0d, 0x2d, 0xe5, 0x7a, 0x9f, 0x93, 0xc9, 0x9c, 0xef,
        0xa0, 0xe0, 0x3b, 0x4d, 0xae, 0x2a, 0xf5, 0xb0, 0xc8, 0xeb, 0xbb, 0x3c, 0x83, 0x53, 0x99, 0x61,
        0x17, 0x2b, 0x04, 0x7e, 0xba, 0x77, 0xd6, 0x26, 0xe1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0c, 0x7d};

#define mult_funct(tmp) (char)((tmp > 127) ? (27^(tmp << 1)) : ((tmp) << 1))

char mult(char first, char second){
    if (1 & second){return first ^ mult_funct(mult(first, second >> 1));}
    else if (1==second){return first;}
    else if (2==second){return mult_funct(first);}
    else return mult_funct(mult(first, second >> 1));
}

void AddRoundKey(uint8_t* input, uint8_t* private_key){
    for(int i=0;i<=15;i++){
        input[i] = input[i] ^ private_key[i];
    }
}

char mult_funct2(char tmp,int n){
    char tmp2=tmp;
    for(int i=0;i<n-1;i++){
        tmp2=tmp2^tmp;
    }
    return tmp2;
}

#define MixColumnCalculation(input) for(int i=0;i<=3;i++){tmp[i] = byte[i*4 +input];} tmp[4]=tmp[0]^tmp[1]^tmp[2]^tmp[3];for(int i=0;i<=3;i++){byte[i*4+input]=tmp[i] ^ mult_funct2(tmp[i] ^ tmp[i+1],2) ^ tmp[4];}
void MixColumns(uint8_t* byte){
    char tmp[5];
    for(int i=0;i<=3;i++){
        MixColumnCalculation(i)
    }
}
#define InvMixColumnCalculation(input) for(int i=0;i<=3;i++){tmp[i] = byte[i*4 +input];} tmp[4]=tmp[0]^tmp[1]^tmp[2]^tmp[3];for(int i=0;i<=3;i++){byte[i*4+input]=tmp[(i+3)%4] ^ mult_funct2(tmp[(i+1)%4],3) ^ mult_funct2(tmp[(i+2)%4],5) ^ mult_funct2(tmp[i],6) ^ mult_funct2(tmp[4],8);}
void InvColumns(uint8_t* byte){
    char tmp[5];
    for(int i=0;i<=3;i++){
        InvMixColumnCalculation(i);
    }
}


void ShiftRows(uint8_t* input){
    uint8_t tmp = input[15];
    input[15] = input[14];
    input[14] = input[13];
    input[13] = input[12];
    input[12] = tmp;
    tmp = input[4];
    input[4] = input[5];
    input[5] = input[6];
    input[6] = input[7];
    input[7] = tmp;
    swap_two(&input[11], &input[9]);
    swap_two(&input[10], &input[8]);

}

void InvShiftRows(uint8_t* input){
    uint8_t tmp = input[12];
    input[12] = input[13];
    input[13] = input[14];
    input[14] = input[15];
    input[15] = tmp;
    tmp = input[7];
    input[7] = input[6];
    input[6] = input[5];
    input[5] = input[4];
    input[4] = tmp;
    swap_two(&input[11], &input[9]);
    swap_two(&input[10], &input[8]);
}

void SubBytes(uint8_t* input){
    for(int i=0;i<=15;i++){
        input[i] = sbox[input[i]];
    }
}

void InvSubBytes(uint8_t* input){
    for(int i=0;i<=15;i++){
        input[i] = invsbox[input[i]];
    }
}
/*
char *to_byte(char* byte){
    char *tmp = (char*)malloc(sizeof(byte));
    //char *tmp = new char[16];
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            tmp[j+i * 4] = byte[i + j * 4];
        }
    }
    return tmp;
}
*/
uint8_t* to_byte(uint8_t byte[16]){
    uint8_t *tmp = (uint8_t*)malloc(sizeof(uint8_t)*16);
    //string tmp = "oooooooooooooooo";
    //cout << "to_byte" << strlen(tmp) << endl;
    //char *tmp = new char[16];
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            tmp[j+i * 4] = byte[i + j * 4];
        }
    }
    //cout << "tmp: " << tmp.length()<< endl;
    //cout << "to_byte" << strlen(tmp) << endl;
    return tmp;
}
/*
char *encrypt(char* plaintext, char* private_key){
    char *byte = to_byte(plaintext);
    char **myroundkey=(char**)malloc(sizeof(char *)*11);
    //char **myroundkey=new (char*);
    myroundkey[0] = to_byte(private_key);
    for (int i = 1; i <= 10; i++){
        myroundkey[i] = (char*)malloc(sizeof(char)*16);
        //myroundkey[i] = new char[16];
    }
    for (int i = 1; i <= 10; i++){
        myroundkey[i][8] = sbox[myroundkey[i - 1][15]] ^ (char) (0) ^ myroundkey[i - 1][8];
        myroundkey[i][12] = sbox[myroundkey[i - 1][3]] ^ (char) (0) ^ myroundkey[i - 1][12];
        myroundkey[i][0] = sbox[myroundkey[i - 1][7]] ^  myroundkey[i - 1][0] ^ rcon[i];
        myroundkey[i][4] = sbox[myroundkey[i - 1][11]] ^ (char) (0) ^ myroundkey[i - 1][4];   
        for (int j = 0; j <= 15; j++){
            if (j % 4){myroundkey[i][j]=myroundkey[i - 1][j] ^ myroundkey[i][j - 1];}
        }
    }
    for (int i = 0; i <= 8; i++){
        AddRoundKey(byte, myroundkey[i]);
        SubBytes(byte);
        ShiftRows(byte);
        MixColumns(byte);

    AddRoundKey(byte, myroundkey[9]);
    SubBytes(byte);
    ShiftRows(byte);
    AddRoundKey(byte, myroundkey[10]);
    char *finalciphertext = to_byte(byte);
    return finalciphertext;
}
*/

void encrypt(uint8_t plaintext[16], uint8_t private_key[16]){
    //cout << plaintext << endl;
    //cout << private_key << endl;
    //char *byte = to_byte(plaintext);
    uint8_t* byte = to_byte(plaintext);
    uint8_t myroundkey[11][16];
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            myroundkey[0][j+i * 4] = private_key[i + j * 4];
        }
    }
    for (int i = 1; i <= 10; i++){
        //cout << i << "  " << myroundkey[i] << endl;
        //cout << (char)sbox[myroundkey[i - 1][15]]-128 << " + " <<  (char)(0)-128 << " + " << (char)myroundkey[i - 1][8]-128 << endl;
        myroundkey[i][8] = (uint8_t)(sbox[myroundkey[i - 1][15]]) ^ (uint8_t)(0) ^ (uint8_t)myroundkey[i - 1][8];
        //cout << (char)(sbox[myroundkey[i][8]]-128) << "~~~~~~~~~~~~~~~" << endl;
        //cout << i << "  " << myroundkey[i] << endl;
        myroundkey[i][12] = (uint8_t)(sbox[myroundkey[i - 1][3]]) ^ (uint8_t)(0) ^ (uint8_t)myroundkey[i - 1][12];
        //cout << (char)(sbox[myroundkey[i][12]]-128) << "~~~~~~~~~~~~~~~" << endl;
        //cout << i << "  " << myroundkey[i] << endl;
        myroundkey[i][0] = (uint8_t)(sbox[myroundkey[i - 1][7]]) ^ (uint8_t)myroundkey[i - 1][0] ^ (uint8_t)rcon[i];
        //cout << (char)(sbox[myroundkey[i][0]]-128) << "~~~~~~~~~~~~~~~" << endl;
        //cout << i << "  " << myroundkey[i] << endl;
        myroundkey[i][4] = (uint8_t)(sbox[myroundkey[i - 1][11]]) ^ (uint8_t)(0) ^ (uint8_t)myroundkey[i - 1][4];
        //cout << (char)(sbox[myroundkey[i][4]]-128) << "~~~~~~~~~~~~~~~" << endl;
        //cout << i << "  " << myroundkey[i] << endl;   
        for (int j = 0; j <= 15; j++){
            if (j % 4){
                myroundkey[i][j]=(uint8_t)myroundkey[i - 1][j] ^ (uint8_t)myroundkey[i][j - 1]; 
                //cout << (char)(sbox[myroundkey[i][j]]-128) << "~~~~~~~~~~~~~~~" << endl;
            }
        }
    }
    //cout << " asdfff;:;;; " << byte << endl;
    for (int i = 0; i <= 8; i++){
        //cout << i << " " << byte.length() << endl;
        //AddRoundKey(byte, myroundkey[i]);
        for(int j=0;j<=15;j++){
            byte[j] = byte[j] ^ myroundkey[i][j];
        }
        SubBytes(byte);
        ShiftRows(byte);
        MixColumns(byte);
        /*
        for(int j=0;j<=15;j++){
            cout << "byte" << " " << (int)byte[j] << endl;
        }
        */
        
    }
    //cout << "1:" << sizeof(byte)/sizeof(char) << endl;
    //AddRoundKey(byte, myroundkey[9]);
    for(int j=0;j<=15;j++){
        byte[j] =byte[j] ^ myroundkey[9][j];
    }
    SubBytes(byte);
    ShiftRows(byte);
    //AddRoundKey(byte, myroundkey[10]);
    for(int j=0;j<=15;j++){
        byte[j] =byte[j] ^ myroundkey[10][j];
    }
    uint8_t* finalciphertext=to_byte(byte);
    for(int i=0;i<=15;i++){
        //cout << hex <<(int)finalciphertext[i];
        switch((int)finalciphertext[i]/16){
            case 10:
                cout << 'a';
                break;
            case 11:
                cout << 'b';
                break;
            case 12:
                cout << 'c';
                break;
            case 13:
                cout << 'd';
                break;
            case 14:
                cout << 'e';
                break;
            case 15:
                cout << 'f';
                break;
            default:
                cout << (int)finalciphertext[i]/16;
                break;
        }
        switch((int)finalciphertext[i]%16){
            case 10:
                cout << 'a';
                break;
            case 11:
                cout << 'b';
                break;
            case 12:
                cout << 'c';
                break;
            case 13:
                cout << 'd';
                break;
            case 14:
                cout << 'e';
                break;
            case 15:
                cout << 'f';
                break;
            default:
                cout << (int)finalciphertext[i]%16;
                break;
        }
    }
    //char* final=(char*)malloc(sizeof(char)*16);
    //for(int i=0;i<=15;i++){
    //    final[i]=(char)(finalciphertext[i]-128);
    //}
    //cout << byte << endl;
    //return final;
    return;
}


void decrypt(uint8_t plaintext[16], uint8_t private_key[16]){
    uint8_t* byte = to_byte(plaintext);
    //char **myroundkey=(char**)malloc(sizeof(char *)*11);
    //char **myroundkey;//=new (*char)[11];
    uint8_t myroundkey[11][16];
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            myroundkey[0][j+i * 4] = private_key[i + j * 4];
        }
    }
    for (int i = 1; i <= 10; i++){
        //cout << i << "  " << myroundkey[i] << endl;
        //cout << (char)sbox[myroundkey[i - 1][15]]-128 << " + " <<  (char)(0)-128 << " + " << (char)myroundkey[i - 1][8]-128 << endl;
        myroundkey[i][8] = (uint8_t)(sbox[myroundkey[i - 1][15]]) ^ (uint8_t)(0) ^ (uint8_t)myroundkey[i - 1][8];
        //cout << (char)(sbox[myroundkey[i][8]]-128) << "~~~~~~~~~~~~~~~" << endl;
        //cout << i << "  " << myroundkey[i] << endl;
        myroundkey[i][12] = (uint8_t)(sbox[myroundkey[i - 1][3]]) ^ (uint8_t)(0) ^ (uint8_t)myroundkey[i - 1][12];
        //cout << (char)(sbox[myroundkey[i][12]]-128) << "~~~~~~~~~~~~~~~" << endl;
        //cout << i << "  " << myroundkey[i] << endl;
        myroundkey[i][0] = (uint8_t)(sbox[myroundkey[i - 1][7]]) ^ (uint8_t)myroundkey[i - 1][0] ^ (uint8_t)rcon[i];
        //cout << (char)(sbox[myroundkey[i][0]]-128) << "~~~~~~~~~~~~~~~" << endl;
        //cout << i << "  " << myroundkey[i] << endl;
        myroundkey[i][4] = (uint8_t)(sbox[myroundkey[i - 1][11]]) ^ (uint8_t)(0) ^ (uint8_t)myroundkey[i - 1][4];
        //cout << (char)(sbox[myroundkey[i][4]]-128) << "~~~~~~~~~~~~~~~" << endl;
        //cout << i << "  " << myroundkey[i] << endl;   
        for (int j = 0; j <= 15; j++){
            if (j % 4){
                myroundkey[i][j]=(uint8_t)myroundkey[i - 1][j] ^ (uint8_t)myroundkey[i][j - 1]; 
                //cout << (char)(sbox[myroundkey[i][j]]-128) << "~~~~~~~~~~~~~~~" << endl;
            }
        }
        //cout << "myroundkey1 in encrypt: " << endl;
        //for(int j=0;j<=15;j++){
            //cout << (char*)(myroundkey[i]) << " ";
        //}
        //cout << endl;
        //cout << i << "  " << myroundkey[i] << endl;
    }
    //AddRoundKey(byte, myroundkey[10]);
    for(int j=0;j<=15;j++){
        byte[j] = byte[j] ^ myroundkey[10][j];
    }
    for (int i = 0; i <= 8; i++)
    {
        InvShiftRows(byte);
        InvSubBytes(byte);
        //AddRoundKey(byte, myroundkey[9 - i]);
        for(int j=0;j<=15;j++){
            byte[j] = byte[j] ^ myroundkey[9-i][j];
        }
        InvColumns(byte);
    }
    InvShiftRows(byte);
    InvSubBytes(byte);
    //AddRoundKey(byte, myroundkey[0]);
    for(int j=0;j<=15;j++){
        byte[j] = byte[j] ^ myroundkey[0][j];
    }
    //char *finalplaintext = to_byte(byte);
    //return finalplaintext;
    uint8_t* finalplaintext=to_byte(byte);
    for(int i=0;i<=15;i++){
        if((char)((int)finalplaintext[i]-128)=='=')return;
        cout << (char)((int)finalplaintext[i]-128);
    }
    //cout << endl;
    return;
}

int main(int argc, char *argv[]){
    if (strcmp(argv[1], "--generate") == 0){generate();}
    else if (argc>=5&&strcmp("--encrypt",argv[1])==0 && strcmp("--key",argv[3]) == 0){
        //cout << "argv[2]: " << argv[2] << endl;
        char* plaintext=(char*)malloc(sizeof(argv[2])/sizeof(char));
        plaintext=(char*)argv[2];
        //cout << "plaintext: " << plaintext << endl;
        char* newplaintext;
        int tmp=strlen(argv[2]);
        //cout << "tmp: " << tmp << endl;
        int num=0;
        if(tmp%16!=0){
            while(tmp%16!=0){tmp++;num++;}
        }
        //cout << "tmp: " << tmp << endl;
        //cout << "num: " << num << endl;
        newplaintext=(char*)malloc(sizeof(char)*tmp);
        //newplaintext=(char*)plaintext;
        //tmp-=1
        for(int i=0;i<tmp-num;i++){
            newplaintext[i]=plaintext[i];
        }
        for(int i=tmp-num;i<tmp;i++){
            newplaintext[i]='=';
        }
        //cout << "newplaintext: " << newplaintext << endl;
        
        for(int i=0;i<tmp/16;i++){
            uint8_t* tmp3=(uint8_t*)malloc(sizeof(uint8_t)*16);
            for(int j=0;j<=15;j++){
                tmp3[j]=(uint8_t)newplaintext[i*16+j]+128;
                //cout << (int)tmp3[j] << endl;
            }
            ifstream infile; 
            infile.open(argv[4]); 
            char *private_key=(char*)malloc(sizeof(char)*16);
            //char private_key[16];
            //uint8_t* privatekey2=(uint8_t*)malloc(sizeof(uint8_t)*16);
            uint8_t privatekey2[16];
            infile >> private_key; 
            infile.close();
            for(int i=0;i<=15;i++){
                privatekey2[i]=private_key[i]+128;
            }
            //cout << "tmp3: " << tmp3 << endl;
            //cout << "private_key: " << private_key << endl;
            //cout << encrypt(tmp3, privatekey2);
            encrypt(tmp3, privatekey2);
            free(tmp3);
        }
        cout << endl;
    }
    else if (argc>=5&&strcmp("--encrypt",argv[3])==0 && strcmp("--key",argv[1]) == 0){
        //cout << "argv[2]: " << argv[2] << endl;
        char* plaintext=(char*)malloc(sizeof(argv[4])/sizeof(char));
        plaintext=(char*)argv[4];
        //cout << "plaintext: " << plaintext << endl;
        char* newplaintext;
        int tmp=strlen(argv[4]);
        //cout << "tmp: " << tmp << endl;
        int num=0;
        if(tmp%16!=0){
            while(tmp%16!=0){tmp++;num++;}
        }
        //cout << "tmp: " << tmp << endl;
        //cout << "num: " << num << endl;
        newplaintext=(char*)malloc(sizeof(char)*tmp);
        //newplaintext=(char*)plaintext;
        //tmp-=1
        for(int i=0;i<tmp-num;i++){
            newplaintext[i]=plaintext[i];
        }
        for(int i=tmp-num;i<tmp;i++){
            newplaintext[i]='=';
        }
        //cout << "newplaintext: " << newplaintext << endl;
        
        for(int i=0;i<tmp/16;i++){
            uint8_t* tmp3=(uint8_t*)malloc(sizeof(uint8_t)*16);
            for(int j=0;j<=15;j++){
                tmp3[j]=(uint8_t)newplaintext[i*16+j]+128;
                //cout << (int)tmp3[j] << endl;
            }
            ifstream infile; 
            infile.open(argv[2]); 
            char *private_key=(char*)malloc(sizeof(char)*16);
            //char private_key[16];
            //uint8_t* privatekey2=(uint8_t*)malloc(sizeof(uint8_t)*16);
            uint8_t privatekey2[16];
            infile >> private_key; 
            infile.close();
            for(int i=0;i<=15;i++){
                privatekey2[i]=private_key[i]+128;
            }
            //cout << "tmp3: " << tmp3 << endl;
            //cout << "private_key: " << private_key << endl;
            //cout << encrypt(tmp3, privatekey2);
            encrypt(tmp3, privatekey2);
            free(tmp3);
        }
        cout << endl;
    }
    else if (strcmp("--encrypt",argv[1])==0){
        //cout << "argv[2]: " << argv[2] << endl;
        
        char* plaintext=(char*)malloc(sizeof(argv[2])/sizeof(char));
        plaintext=(char*)argv[2];
        //cout << "plaintext: " << plaintext << endl;
        char* newplaintext;
        int tmp=strlen(argv[2]);
        //cout << "tmp: " << tmp << endl;
        int num=0;
        if(tmp%16!=0){
            while(tmp%16!=0){tmp++;num++;}
        }
        //cout << "tmp: " << tmp << endl;
        //cout << "num: " << num << endl;
        newplaintext=(char*)malloc(sizeof(char)*tmp);
        //newplaintext=(char*)plaintext;
        //tmp-=1
        for(int i=0;i<tmp-num;i++){
            newplaintext[i]=plaintext[i];
        }
        for(int i=tmp-num;i<tmp;i++){
            newplaintext[i]='=';
        }
        //cout << "newplaintext: " << newplaintext << endl;
        
        for(int i=0;i<tmp/16;i++){
            uint8_t* tmp3=(uint8_t*)malloc(sizeof(uint8_t)*16);
            for(int j=0;j<=15;j++){
                tmp3[j]=(uint8_t)newplaintext[i*16+j]+128;
                //cout << (int)tmp3[j] << endl;
            }
            char private_key[16];//=(char*)malloc(sizeof(char)*16);
            private_key[0]='L';
            private_key[1]='K';
            private_key[2]='r';
            private_key[3]='B';
            private_key[4]='D';
            private_key[5]='W';
            private_key[6]='q';
            private_key[7]='a';
            private_key[8]='l';
            private_key[9]='3';
            private_key[10]='(';
            private_key[11]='m';
            private_key[12]='s';
            private_key[13]='2';
            private_key[14]='A';
            private_key[15]='X';//default key
            //char private_key[16]="LKrBDWqal3(ms2AX";
            //uint8_t* privatekey2=(uint8_t*)malloc(sizeof(uint8_t)*16);
            uint8_t privatekey2[16];
            //infile >> private_key; 
            //infile.close();
            for(int i=0;i<=15;i++){
                privatekey2[i]=private_key[i]+128;
            }
            //cout << "tmp3: " << tmp3 << endl;
            //cout << "private_key: " << private_key << endl;
            //cout << encrypt(tmp3, privatekey2);
            encrypt(tmp3, privatekey2);
            free(tmp3);
        }
        cout << endl;
    }
    else if (argc>=5&&strcmp("--decrypt", argv[1]) == 0 && strcmp("--key",argv[3]) == 0){
        char* ciphertext=(char*)malloc(strlen(argv[2])*sizeof(char));
        ciphertext=(char*)argv[2];
        if(strcmp(ciphertext,"cd6c72cf37d6a5ef09c0130440a90e1de6781259a4bae9512dc00b5ed4c576b52617b44be917e994b4275b04114a856c")==0){cout << "cheater: it is forbidden to decrypt the challenge ciphertext" << endl;return 0;}
        
        int tmp=strlen(argv[2]);
        //cout << tmp << endl;
        //int num=0;
        if(tmp%32!=0){
            cout << "wrong ciphertext!!!" << endl;
            return 0;
        }
        uint8_t* newciphertext=(uint8_t*)malloc(sizeof(uint8_t)*tmp/2);
        for(int i=0;i<tmp;i+=2){
            int first;
            switch(ciphertext[i]){
                case 'a':
                    first=10;
                    break;
                case 'b':
                    first=11;
                    break;
                case 'c':
                    first=12;
                    break;
                case 'd':
                    first=13;
                    break;
                case 'e':
                    first=14;
                    break;
                case 'f':
                    first=15;
                    break;
                default:
                    first=ciphertext[i]-'0';
                    break;
            }
            first*=16;
            switch(ciphertext[i+1]){
                case 'a':
                    first+=10;
                    break;
                case 'b':
                    first+=11;
                    break;
                case 'c':
                    first+=12;
                    break;
                case 'd':
                    first+=13;
                    break;
                case 'e':
                    first+=14;
                    break;
                case 'f':
                    first+=15;
                    break;
                default:
                    first+=(ciphertext[i+1]-'0');
                    break;
            }
            //cout << first << "**********" << endl;
            newciphertext[int(i/2)]=(uint8_t)first;
        }
       
        for(int i=0;i<tmp/32;i++){
            uint8_t* tmp3=(uint8_t*)malloc(sizeof(uint8_t)*16);
            for(int j=0;j<=15;j++){
                tmp3[j]=(uint8_t)newciphertext[i*16+j];
                //cout << (int)tmp3[j] << endl;
            }
            ifstream infile; 
            infile.open(argv[4]); 
            char *private_key=(char*)malloc(sizeof(char)*16);
            //char private_key[16];//????
            //uint8_t* privatekey2=(uint8_t*)malloc(sizeof(uint8_t)*16);
            uint8_t privatekey2[16];
            //cout << "!!!" << endl;
            infile >> private_key; 
            infile.close();
            //cout << "???" << endl;
            
            for(int j=0;j<=15;j++){
                privatekey2[j]=private_key[j]+128;
            }
            //cout << "tmp3: " << tmp3 << endl;
            //cout << "private_key: " << private_key << endl;
            //cout << encrypt(tmp3, privatekey2);
            decrypt(tmp3, privatekey2);
            free(tmp3);
        }
        cout << endl;
    }
    else if (argc>=5&&strcmp("--decrypt", argv[3]) == 0 && strcmp("--key",argv[1]) == 0){
        char* ciphertext=(char*)malloc(strlen(argv[2])*sizeof(char));
        ciphertext=(char*)argv[4];
        if(strcmp(ciphertext,"cd6c72cf37d6a5ef09c0130440a90e1de6781259a4bae9512dc00b5ed4c576b52617b44be917e994b4275b04114a856c")==0){cout << "cheater: it is forbidden to decrypt the challenge ciphertext" << endl;return 0;}
        
        int tmp=strlen(argv[4]);
        //cout << tmp << endl;
        //int num=0;
        if(tmp%32!=0){
            cout << "wrong ciphertext!!!" << endl;
            return 0;
        }
        uint8_t* newciphertext=(uint8_t*)malloc(sizeof(uint8_t)*tmp/2);
        for(int i=0;i<tmp;i+=2){
            int first;
            switch(ciphertext[i]){
                case 'a':
                    first=10;
                    break;
                case 'b':
                    first=11;
                    break;
                case 'c':
                    first=12;
                    break;
                case 'd':
                    first=13;
                    break;
                case 'e':
                    first=14;
                    break;
                case 'f':
                    first=15;
                    break;
                default:
                    first=ciphertext[i]-'0';
                    break;
            }
            first*=16;
            switch(ciphertext[i+1]){
                case 'a':
                    first+=10;
                    break;
                case 'b':
                    first+=11;
                    break;
                case 'c':
                    first+=12;
                    break;
                case 'd':
                    first+=13;
                    break;
                case 'e':
                    first+=14;
                    break;
                case 'f':
                    first+=15;
                    break;
                default:
                    first+=(ciphertext[i+1]-'0');
                    break;
            }
            //cout << first << "**********" << endl;
            newciphertext[int(i/2)]=(uint8_t)first;
        }
       
        for(int i=0;i<tmp/32;i++){
            uint8_t* tmp3=(uint8_t*)malloc(sizeof(uint8_t)*16);
            for(int j=0;j<=15;j++){
                tmp3[j]=(uint8_t)newciphertext[i*16+j];
                //cout << (int)tmp3[j] << endl;
            }
            ifstream infile; 
            infile.open(argv[2]); 
            char *private_key=(char*)malloc(sizeof(char)*16);
            //char private_key[16];//????
            //uint8_t* privatekey2=(uint8_t*)malloc(sizeof(uint8_t)*16);
            uint8_t privatekey2[16];
            //cout << "!!!" << endl;
            infile >> private_key; 
            infile.close();
            //cout << "???" << endl;
            
            for(int j=0;j<=15;j++){
                privatekey2[j]=private_key[j]+128;
            }
            //cout << "tmp3: " << tmp3 << endl;
            //cout << "private_key: " << private_key << endl;
            //cout << encrypt(tmp3, privatekey2);
            decrypt(tmp3, privatekey2);
            free(tmp3);
        }
        cout << endl;
    }
    else if (strcmp("--decrypt", argv[1]) == 0){
        char* ciphertext=(char*)malloc(strlen(argv[2])*sizeof(char));
        ciphertext=(char*)argv[2];
        if(strcmp(ciphertext,"cd6c72cf37d6a5ef09c0130440a90e1de6781259a4bae9512dc00b5ed4c576b52617b44be917e994b4275b04114a856c")==0){cout << "cheater: it is forbidden to decrypt the challenge ciphertext" << endl;return 0;}
        
        int tmp=strlen(argv[2]);
        //cout << tmp << endl;
        //int num=0;
        if(tmp%32!=0){
            cout << "wrong ciphertext!!!" << endl;
            return 0;
        }
        uint8_t* newciphertext=(uint8_t*)malloc(sizeof(uint8_t)*tmp/2);
        for(int i=0;i<tmp;i+=2){
            int first;
            switch(ciphertext[i]){
                case 'a':
                    first=10;
                    break;
                case 'b':
                    first=11;
                    break;
                case 'c':
                    first=12;
                    break;
                case 'd':
                    first=13;
                    break;
                case 'e':
                    first=14;
                    break;
                case 'f':
                    first=15;
                    break;
                default:
                    first=ciphertext[i]-'0';
                    break;
            }
            first*=16;
            switch(ciphertext[i+1]){
                case 'a':
                    first+=10;
                    break;
                case 'b':
                    first+=11;
                    break;
                case 'c':
                    first+=12;
                    break;
                case 'd':
                    first+=13;
                    break;
                case 'e':
                    first+=14;
                    break;
                case 'f':
                    first+=15;
                    break;
                default:
                    first+=(ciphertext[i+1]-'0');
                    break;
            }
            //cout << first << "**********" << endl;
            newciphertext[int(i/2)]=(uint8_t)first;
        }
       
        for(int i=0;i<tmp/32;i++){
            uint8_t* tmp3=(uint8_t*)malloc(sizeof(uint8_t)*16);
            for(int j=0;j<=15;j++){
                tmp3[j]=(uint8_t)newciphertext[i*16+j];
                //cout << (int)tmp3[j] << endl;
            }
            ifstream infile; 
            //infile.open(argv[4]); 
            char *private_key=(char *)"LKrBDWqal3(ms2AX";
            //char private_key[16];//????
            //uint8_t* privatekey2=(uint8_t*)malloc(sizeof(uint8_t)*16);
            uint8_t privatekey2[16];
            //cout << "!!!" << endl;
            //infile >> private_key; 
            //infile.close();
            //cout << "???" << endl;
            
            for(int j=0;j<=15;j++){
                privatekey2[j]=private_key[j]+128;
            }
            //cout << "tmp3: " << tmp3 << endl;
            //cout << "private_key: " << private_key << endl;
            //cout << encrypt(tmp3, privatekey2);
            decrypt(tmp3, privatekey2);
            free(tmp3);
        }
        cout << endl;
    }
    else{cout << "Wrong input format!!!" << endl;}
    return 0;
}