#pragma once
#include <stdio.h>
#include <iostream>
#include <string>
#include <ctime>


class party
{
private:

	//array of first 100 primes - randomly chooses values from this table for e
	int primeArr[100] = {7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97,101,103,107,109,
		113,127,131,137,139,149,151,157,163,167,173,179,181,191,193,197,199,211,223,227,229,233,239,241,251,
		257,263,269,271,277,281,283,293,307,311,313,317,331,337,347,349,353,359,367,373,379,383,389,397,401,
		409,419,421,431,433,439,443,449,457,461,463,467,479,487,491,499,503,509,521,523,541,547,557,563};

	//private key
	struct sKey
	{
		int p;
		int q;
		int phi;
		int d;
		//Diffie-Hellman Secret Key
		int secretKeyDH;
	}secretKey;

public:
	//Public key
	struct pKey
	{
		int n;
		int e;
		//Diffie-Hellman Shared Value
		int shareValueDH;
	}pubKey;

	//Holds plaintext/ciphertext
	std::string strMessage;

	party();
	party(int inputP, int inputQ);
	//Sender only has a private key. Uses pub key of receiver
	party(int inputX);
	~party();
	

	//Calc e and d based on criteria of RSA
	void calcEandD();

	//Using shared/public DH and RSA keys from RECEIVER --> calculate shared and the common private DH keys for SENDER
	void genPrivateKeySender(int shareVal, int recE, int recN);
	//Using shared DH key from SENDER --> calculate the common private DH key for RECEIVER
	void genPrivateKeyRec(int valueRec);

	//Apply RSA + DH encryption
	std::string encryption(int recN, int recE, int recShared);
	//Apply RSA + DH decryption
	std::string decryption();
	

	//----------------------Helper Functions----------------------
	int modulo(int a, int b, int n);
	int gcd(int a, int b);
	bool isPrime(int a);
};


