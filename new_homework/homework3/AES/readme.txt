Written by ShiHan Chan on 2019/6/8
This readme file is for VE475 homework3 problem4. I use c to completely implement both encryption and decrption of AES in one file main.c
Use the command below to see the plaintext, key, corresponding ciphertext, and the plaintext decrypted from ciphertext.
$ g++ -o main main.c
$./main

You can change the plaintext, key and see different result by yourself. (Noted 0x is hex number and we seperate 128 bits to 16 bytes)
uint8_t myplaintext[16]={0x74, 0x56, 0xfe, 0x28,0xdd, 0xae, 0xdc, 0x43,0x27, 0x59, 0x21, 0xee,0xca, 0xcd, 0xdc, 0x88};
uint8_t myprivate_key[16] = {0xff, 0x04, 0xd0, 0xff,0x42, 0x39, 0x21, 0xce,0x64, 0x73, 0xee, 0xbb,0xbf, 0xfb, 0x5b, 0xb3};

encrypt is encryption function and decrypt is decryption function.

The invsbox is derived directly from sbox. For each element in invsbox, search element in sbox that element value from sbox is same as row/column value from invsbox. Then the corresponding row/column value from sbox is the value of invsbox.