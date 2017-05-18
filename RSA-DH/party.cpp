#include "stdafx.h"
#include "party.h"

party::party()
{
}

party::party(int inputP, int inputQ)
{
	secretKey.p = inputP;
	secretKey.q = inputQ;
	pubKey.n = inputP * inputQ;
	secretKey.phi = (inputP - 1) * (inputQ - 1);
	calcEandD();
}

party::party(int inputD)
{
	secretKey.d = inputD;
}

party::~party()
{
}

//----------------------Calculate e and d----------------------

void party::calcEandD()
{
	pubKey.e = 2;
	int temp;

	//Calc e that satisfies gcd(e,phi) = 1
	while (1)
	{
		temp = gcd(pubKey.e, secretKey.phi);

		//Random 0-99  pos
		int n = (rand() % 99)+1;

		if (temp == 1)
		{
			for (int i = 1; i < secretKey.phi; i++)
			{
				if (((pubKey.e*i) % secretKey.phi) == 1)
				{
					secretKey.d = i;
					break;
				}		
			}
			break;
		}
				
		else
		{
			while(primeArr[n] > secretKey.phi)
				n = (rand() % 99) + 1;

			pubKey.e = primeArr[n];
		}		
	}

	//Calc value to share
	pubKey.shareValueDH = modulo(pubKey.e, secretKey.d, pubKey.n);

	std::cout << "Public Key is: (" << pubKey.n << "," << pubKey.e << "," << pubKey.shareValueDH << ")" << std::endl;
	std::cout << "Private Key is: (" << secretKey.p << "," << secretKey.q << "," << secretKey.phi << "," << secretKey.d << ")" << std::endl;
}

//----------------------Calculate shared and the common private DH keys for SENDER----------------------

void party::genPrivateKeySender(int valueRec, int recE, int recN)
{
	std::cout << "AA: " << recE << std::endl;
	pubKey.shareValueDH = modulo(recE, secretKey.d, recN);
	secretKey.secretKeyDH = modulo(valueRec, secretKey.d, recN);
	std::cout << "Secret Shared key: " << secretKey.secretKeyDH << std::endl;
}

//----------------------Calculate the common private DH key for RECEIVER----------------------

void party::genPrivateKeyRec(int valueRec)
{
	secretKey.secretKeyDH = modulo(valueRec, secretKey.d, pubKey.n);
	std::cout << "Secret Shared key: " << secretKey.secretKeyDH << std::endl;
}

//----------------------Sender will encrypt data by performing RSA encryption (char-by-char) and adding secret key to each letters encrypted value----------------------

std::string party::encryption(int recN,int recE, int recShared)
{
	std::string retString= "";

	for each (char c in strMessage)
	{
		std::cout << "VAL: " << (int)c << std::endl;
		int tempNum = modulo((int)c, recE, recN);
		//std::cout << tempNum + secretKey.secretKeyDH;
		
		//Add DH key to number and convert to string
		std::string tempStr = std::to_string(tempNum+secretKey.secretKeyDH);

		//Packet as 4 characters
		switch (tempStr.length())
		{
		case 1:
			tempStr = "000" + tempStr;
			break;		
		case 2:
				tempStr = "00" + tempStr;
				break;
		case 3:
			tempStr = "0" + tempStr;
			break;
		case 4:
			break;
		default:
			tempStr = "0000";
			break;
		}
		retString += tempStr;
	}

	return retString;
}

//----------------------Sender will decrypt data by first subtracting secret key from each letters encrypted value and then performing RSA decrypting----------------------

std::string party::decryption()
{
	std::string retString = "";

	for (int i = 0; i < strMessage.length(); i += 4)
	{
		int temp = 0;
		//Extract 4 characters at a time
		temp = stoi(strMessage.substr(i, 4));
		//std::cout << "Before Decryption: " << temp << std::endl;
		
		//Subtract DH key from number after converting from string
		temp -= secretKey.secretKeyDH;

		//Decrypt the four characters
		int tempNum = modulo(temp, secretKey.d, pubKey.n);
		//std::cout << "After Decryption: " << tempNum << std::endl;
	
		//Add to string
		retString += (char)tempNum;
	}

	return retString;
}



//----------------------Helper Functions----------------------

int party::gcd(int a, int b)
{
	if (b == 0)
		return a;
	else
		return gcd(b, a%b);
}

bool party::isPrime(int a)
{
	for (int i = 2; i < a / 2; i++)
	{
		if (a % i == 0) return false;
	}
	return true;
}

int party::modulo(int a, int b, int n) {
	long long x = 1, y = a;
	while (b > 0) {
		if (b % 2 == 1) {
			x = (x*y) % n;
		}
		y = (y*y) % n; // squaring the base
		b /= 2;
	}
	return x%n;
}