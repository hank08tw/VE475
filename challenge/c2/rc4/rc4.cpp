#include "rc4.h"
#include <fstream>

void swap_rc4(uchar_t &a, uchar_t &b) {
	uchar_t temp = a;
	a = b;
	b = temp;
}

void rc4::initialize() {
	int l = key.length();
	for (int i = 0; i < 256; ++i) {
		S[i] = i;
		T[i] = key[i % l];
	}
	int j = 0;
	for (int i = 0; i < 256; ++i) {
		j = (j + S[i] + T[i]) % 256;
		swap_rc4(S[i], S[j]);
	}
}

rc4::rc4(const std::string& key, const std::string& content) {
	get_information(key, content);
}

void rc4::spawn_stream() {
	int i = 0;
	int j = 0;
	int l = content.length();
	keystream = "";
	while (l--) {
		i = (i+1) % 256;
		j = (j+S[i]) % 256;
		swap_rc4(S[i], S[j]);
		keystream.push_back(S[(S[i]+S[j])%256]);
		//keystream.push_back(65);
	}
	//std::cout << "keystream: " << keystream << std::endl;
}

void rc4::get_information(const std::string &key__r, const std::string &content_t) {
	content = content_t;
	std::ifstream iFile(key__r);
	std::getline(iFile, key);
	//std::cout << key << std::endl;
	initialize();
}

void rc4::get_information_default (const std::string &content_t) {
	content = content_t;
	initialize();
}

std::string rc4::rc4_encrypt(){
	std::string temp;
	spawn_stream();
	for (auto i = keystream.begin(), j=content.begin(); i!=keystream.end(); ++i, ++j) {
		//std::cout << "*i: " << *i << " *j: " << *j << " result: " << (char)(*i^*j) << std::endl;
		temp.push_back(*i^*j);
	}
	return temp;
}

std::string rc4::rc4_decrypt(){
	int d = content.length()/2;
	unsigned char c[content.length()/2];
	for (int i = 0; i < content.length(); i+=2) {
		int x, y;
		switch (content[i]) {
			case '0': x = 0;break;
			case '1': x = 1;break;
			case '2': x = 2;break;
			case '3': x = 3;break;
			case '4': x = 4;break;
			case '5': x = 5;break;
			case '6': x = 6;break;
			case '7': x = 7;break;
			case '8': x = 8;break;
			case '9': x = 9;break;
			case 'a': x = 10;break;
			case 'b': x = 11;break;
			case 'c': x = 12;break;
			case 'd': x = 13;break;
			case 'e': x = 14;break;
			case 'f': x = 15;break;
		}
		switch (content[i+1]) {
			case '0': y = 0;break;
			case '1': y = 1;break;
			case '2': y = 2;break;
			case '3': y = 3;break;
			case '4': y = 4;break;
			case '5': y = 5;break;
			case '6': y = 6;break;
			case '7': y = 7;break;
			case '8': y = 8;break;
			case '9': y = 9;break;
			case 'a': y = 10;break;
			case 'b': y = 11;break;
			case 'c': y = 12;break;
			case 'd': y = 13;break;
			case 'e': y = 14;break;
			case 'f': y = 15;break;
		}
		if (16*x+y<128) {
			c[i/2] = (unsigned char)(16*x+y);
		}
		else {
			c[i/2] = (unsigned char)(16*x+y-256);
		}
		//std::cout << c[i/2];
		//std::cout << "c[i]: " << c << std::endl;
		
	}
	//std::cout << std::endl;
	content = "";
	for (int j = 0; j < d; j++) {
		content.push_back(c[j]);
	}
	//std::cout << "ciphertext: " << content << std::endl;
	std::string temp;
	spawn_stream();
	for (auto i = keystream.begin(), j = content.begin(); i != keystream.end(); ++i, ++j) {
		//std::cout << "*i: " << *i << " *j: " << *j << " result: " << (char)(*i^*j) << std::endl;
		temp.push_back(*i^*j);
	}
	return temp;
	//cout << text << endl;
	//cout << endl;
	//return std::string() = rc4_encrypt();
}

