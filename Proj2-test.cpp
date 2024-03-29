/**
	CEG 4424/6424
	Security Attacks and Defenses
    
**/

#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<chrono>
using namespace std;
using namespace std::chrono;
#include"cryptopp/cryptlib.h"
#include"cryptopp/hex.h"
#include"cryptopp/filters.h"
#include"cryptopp/des.h"
#include"cryptopp/aes.h"
#include"cryptopp/modes.h"

using namespace CryptoPP;
string aes_decode(string & cipher,byte key[])
{
	string plain;
	try{
		ECB_Mode< AES >::Decryption dec;
		dec.SetKey(key, AES::DEFAULT_KEYLENGTH);
		StringSource s(cipher, true, new StreamTransformationFilter(dec, new StringSink(plain)));
	}
	catch(const CryptoPP::Exception& e){
	}
	return plain;
}
int main(int argc,char * argv[])
{
	fstream file1;
	fstream file2;
	byte key[AES::DEFAULT_KEYLENGTH + 1] = "aaaax7qfkp3mbv9w";
	cout << "Starting Key: " <<  key << endl;
	if(argc!=3)
	{
		cout<<"usage:aes_decode infile outfile"<<endl;
		return 0;
	}

	file1.open(argv[1],ios::in);
	file2.open(argv[2], ios::out);
	//reading
	stringstream buffer;
	buffer << file1.rdbuf();
	string cipher(buffer.str());


	//checks to see if loop is done with alphabet
	int check = 0;
	int check1 = 0;
	int check2 = 0;
	int check3 = 0;
	int count = 0;  //count for checking ascii values in decoded text
	string plain;
	int flag = 0;
	double ratio;


	for(int i = 0; i < 36; i++) {
		for(int j = 0; j < 36; j++) {
			for(int k = 0; k < 36; k++) {
				for(int l = 0; l < 36; l++) {
						plain = aes_decode(cipher, key);
						for(int q = 0; q < plain.size(); q++) {
							if(isascii((char)plain[q])) {
								count++;
								ratio = count / plain.size();
							}
						}
						if(ratio > .8) {
							cout << "possible candidate: " << key << endl;
							cout << "Ratio: " << ratio << endl;
						}
						if(count == plain.size()){
							cout << "key found: " << key << endl;
							cout << "Plain text: " << plain << endl;
							flag = 1;
							break;
						}
						else {
							if(l > 25 && !check) {
								check = 1;
								key[3] = '/';
							}
							if(l == 0) {
								key[3] = 'a';
								check = 0;
							}
							key[3] += 1;
							count = 0;
							//cout << key << endl;
						}

					}
					if(flag) {
						break;
					}
					if(k > 25 && !check1) {
						check1 = 1;
						key[2] = '/';
					}
					if(k == 0) {
						key[2] = 'a';
						check1 = 0;
					}
					key[2] += 1;
			}
			if(flag) {
				break;
			}
			if(j > 25 && !check2) {
				check2 = 1;
				key[1] = '/';
			}
			if(j == 0) {
				key[1] = 'a';
				check2 = 0;
			}
			key[1] += 1;
		}
		if(flag) {
			break;
		}
		if(i > 25 && !check3) {
			check3 = 1;
			key[0] = '/';
		}
		if(i == 0) {
			key[0] = 'a';
			check3 = 0;
		}
		key[0] += 1;
	}

	

	file2 << plain;
	cout << "Decrypted plain text saved to: " << argv[2] << endl;
	return 0;
}
