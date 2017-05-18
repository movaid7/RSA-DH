# RSA-DH
Implementation of hybrid RSA-DH encryption &amp; decryption 
 
Procedure: 
 
1.  Read in line of text as string (message in plaintext) 
 
2.  Diffie-Hellman key exchange was setup -> sender and receipient therefore have a common secret key 
 
3.  Sender: 
      Characters were converted to ASCII decimal values 
      RSA encryption was then performed on each character 
      For each encrypted character, the DH secret key was added to the value 
      Characters were packaged into 4 digit number 
      Concatenated these values -> Ciphertext  
      This was sent to the receiver 
 
4.  Receiver: 
      Receives ciphertext 
      Extracts 4 digit numbers one at a time 
      Subtracts DH secret key from value 
      Perform RSA decryption on the result 
      Convert from ASCII decimal back to character 
      Output this string -> Original plaintext message 
