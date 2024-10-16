#!/bin/sh
echo "Encryption..."
echo "Please enter password"
read passwd
if ./MyEncryptor input.tar.gz encrypted.bin $passwd
then
	echo "Encryption done"
else 
	echo "Encryption failed"
	exit 1
fi
echo "Decryption..."
if ./MyEncryptor -d encrypted.bin output.tar.gz $passwd
then
	echo "Decryption done"
else
	echo "Decryption failed"
	exit 2
fi
rm encrypted.bin
echo "Please check output.tar.gz and remove it manually"
