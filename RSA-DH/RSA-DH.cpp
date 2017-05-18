// RSA-DH.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "party.h"

//Secret primes p & q for receiver
#define p 47
#define q 59

//Secret d for sender
#define x 13

int main()
{
	std::srand(time(NULL));
	party receiver(p, q);
	party sender(x);

	std::string strMessage;
	std::cout << "\nPlease enter message to send: ";
	std::getline(std::cin, sender.strMessage);

	//Diffie-Hellman Key Exchange is implemented here
	sender.genPrivateKeySender(receiver.pubKey.shareValueDH, receiver.pubKey.e, receiver.pubKey.n);
	receiver.genPrivateKeyRec(sender.pubKey.shareValueDH);

	//Encrypt with receivers public key and pass to receiver
	receiver.strMessage = sender.encryption(receiver.pubKey.n, receiver.pubKey.e,receiver.pubKey.shareValueDH);
	std::cout << "Encrypted Message is: " << receiver.strMessage << std::endl;

	//Receiver will decrypt to obtain message
	std::string decrypt = receiver.decryption();
	std::cout << "Decrypted Message is: " << decrypt << std::endl;


	std::cin.clear();
	std::cin.ignore();
	char waitChar;
	std::cout << "\nProcess complete. Press ENTER to exit.";
	std::cin.get(waitChar);

    return 0;
}

