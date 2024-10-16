#!/bin/sh
echo "Encryption..."
echo "Please enter password"
read passwd
if ./MyEncryptor input.txt encrypted.bin $passwd
then
	echo "Encryption done"
else 
	echo "Encryption failed"
	exit 1
fi
echo "Decryption..."
if ./MyEncryptor -d encrypted.bin output.txt $passwd
then
	echo "Decryption done"
else
	echo "Decryption failed"
	exit 2
fi
echo "input.txt:"
cat input.txt
echo "output.txt:"
cat output.txt
rm output.txt encrypted.bin
echo "Files removed"
