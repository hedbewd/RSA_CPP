// My program has different keys with HW2 PDF file.
// Thanks to allow question, professor!
// My variables and functions names are all about PPT, so maybe easier to read my RSA code than DES........ maybe......
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <stdlib.h>
#include <string>

using namespace std;

bool check_prime_num(long long p, long long q);
void key_generation(long long p, long long q);
bool check_rprime_num(long long phi, long long e);
void text_to_ascii(string text, int *ascii);
void ascii_to_text(int* ascii);
void encryption(int* plain_ascii, int* cipher_ascii);
void decryption(int* cipher_ascii, int* plain_ascii);
long long pow_with_mod(long long x, long long y, long long mod);

long long n;
long long public_key;
long long private_key;

int main()
{
	long long p = 0, q = 0;
	while (true) {
		cout << "Enter p: ";
		cin >> p;
		cout << "Enter q: ";
		cin >> q;
		if (check_prime_num(p, q) == true) break;
		else cout << "p and q must be prime number!!" << endl;
	}
	
	key_generation(p, q);
	cout << "public key: <" << public_key << ", " << n << ">" << endl;
	cout << "private key: " << private_key << endl << endl;
	string plain_text;
	cout << "Enter a plain text: ";
	cin >> plain_text;	// If care about 'spaces' then should use getline() but don't care about in this problem.
	cout << endl << "You entered \"" << plain_text << "\"" << endl << endl;

	int plain_ascii[21] = { 0 };
	int cipher_ascii[21] = { 0 };
	text_to_ascii(plain_text, plain_ascii);
	
	encryption(plain_ascii, cipher_ascii);
	int ret_plain_ascii[21] = { 0 };
	decryption(cipher_ascii, ret_plain_ascii);

	ascii_to_text(ret_plain_ascii);

	return 0;
}

bool check_prime_num(long long p, long long q)
{
	int flag = 0;
	for (int i = 2; i < p; i++) {
		if (p % i == 0)
			flag++;
	}
	for (int i = 2; i < q; i++) {
		if (q % i == 0)
			flag++;
	}
	if (flag == 0) return true;
	else return false;
}

void key_generation(long long p, long long q)
{
	n = p * q;
	cout << "n: " << n << endl;
	long long phi = (p - 1) * (q - 1);
	cout << "phi: " << phi << endl;
	srand(123);
	long long e = 0;
	while (true) {
		e = rand() % phi;
		if (e != 0) {
			if (check_rprime_num(phi, e) == true) break;
		}
	}
	cout << "e: " << e << endl;
	long long d;
	for (d = 2; d < phi; d++) {
		if ((e * d) % phi == 1) break;
	}
	cout << "d: " << d << endl;
	public_key = e;
	private_key = d;
}

bool check_rprime_num(long long phi, long long e) {
	for (int i = 2; i < e; i++) {
		if (phi % i == 0 && e % i == 0)
			return false;
	}
	return true;
}

void text_to_ascii(string text, int *ascii)
{
	for (int i = 0; i < text.size(); i++) {
		if (text[i] >= 'a' && text[i] <= 'z') {
			ascii[i] = int(text.at(i));
		}
		else if (text[i] >= 'A' && text[i] <= 'Z') {
			ascii[i] = int(text.at(i));
		}
	}
}

void ascii_to_text(int* ascii)
{
	cout << "Deciphered plaintext is \"";
	for (int i = 0; i < sizeof(ascii); i++) {
		if (ascii[i] == 0) break;
		else {
			if (ascii[i] >= 97 && ascii[i] <= 122) {
				cout << char(ascii[i]);
			}
			else if (ascii[i] >= 65 && ascii[i] <= 90) {
				cout << char(ascii[i]);
			}
		}
	}
	cout << "\"" << endl;
}

void encryption(int *plain_ascii, int *cipher_ascii)
{
	long long cipher_ascii1[21] = { 0 };
	cout << "ASCII value of ciphertext is ";
	for (int i = 0; i < sizeof(plain_ascii); i++) {
		if (plain_ascii[i] == 0) break;
		else {
			cipher_ascii1[i] = pow_with_mod(plain_ascii[i], public_key, n);
			cout << cipher_ascii1[i] << " ";
			cipher_ascii[i] = (int)cipher_ascii1[i];
		}
	}
	cout << endl << endl;
}

long long pow_with_mod(long long x, long long y, long long mod)
{
	long long ret = 1;
	for (int i = 0; i < y; i++)
	{
		ret = ret * (x % mod);
		ret %= mod;
	}
	return ret % mod;
}

void decryption(int* cipher_ascii, int* plain_ascii)
{
	long long plain_ascii1[21] = { 0 };
	cout << "ASCII value of plaintext is ";
	for (int i = 0; i < sizeof(cipher_ascii); i++) {
		if (cipher_ascii[i] == 0) break;
		else {
			plain_ascii1[i] = pow_with_mod(cipher_ascii[i], private_key, n);
			cout << plain_ascii1[i] << " ";
			plain_ascii[i] = (int)plain_ascii1[i];
		}
	}
	cout << endl << endl;
}