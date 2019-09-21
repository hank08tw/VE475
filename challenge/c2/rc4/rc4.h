#ifndef RC4_H
#define RC4_H

#include <string>
#include <iostream>

using uchar_t = unsigned char;
class rc4;

class rc4 {
	friend void swap_rc4(uchar_t&, uchar_t&);
public:
	rc4()=default;
	rc4(const std::string&, const std::string&);
	void get_information(const std::string&, const std::string&);
	void get_information_default(const std::string&);
	std::string rc4_encrypt();
	std::string rc4_decrypt();
private:
	uchar_t S[256];
	uchar_t T[256];
	std::string keystream;
	// this is the default key. 
	std::string key = "EAV7xejGE9V7Vs98";
	std::string content;
	std::string ciphertext;
	void initialize();
	void spawn_stream();
};

void swap_rc4(uchar_t&, uchar_t&);

#endif