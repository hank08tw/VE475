Written by ShiHan Chan on 2019/7/7
This readme file is for VE475 challenge2 cipher1. I use c++ to completely implement generate, encrypt, decrypt function of AES. AES uses 128-bits block, this implementation uses array of uint8_t (unsigned char: 0~255) to represent the block. 


##usage
1. encrypt the plaintext by key and get the ciphertext
./c2 --encrypt <plaintext> --key <key>
2. decrypt the ciphertext by key and get the plaintext
./c2 --decrypt <ciphertext> --key <key>
3. randomly generate the key in key file.
./c2 --generate > <keyfile>
4. encrypt the plaintext by default key (LKrBDWqal3(ms2AX) and get the ciphertext
./c2 --encrypt <plaintext>
5. cannot decrypt without key!!!
./c2 --decrypt <ciphertext>

Any other format of usage is forbidden.

Note that I use “=“ padding when the input plaintext is not multiple of 16 bytes in encryption. And the length of ciphertext will only be multiple of 32. For generate function, srand(time(NULL)) provides random selection of key.

The invsbox is derived directly from sbox. For each element in invsbox, search element in sbox that element value from sbox is same as row/column value from invsbox. Then the corresponding row/column value from sbox is the value of invsbox.