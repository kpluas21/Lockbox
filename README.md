# Lockbox
A fast cipher multi-tool that can encrypt and decrypt text files using several
different ciphers.
Program is fully controlled and configured via command line arguments.

## How it works
Simply run the command from your terminal and provide a valid text file. You can then either pipe the output to another text file,
or simply have it output to the terminal.
```
-m: The mode for the cipher
    encrypt | decrypt
-c: The cipher you want to use for the file
    affine | caesar | rot13
-k: The key or keys used for their respective cipher. The values are comma-separated and are checked for validity.
    Example: -a affine -k 2,8
    Invalid keys entered for an affine cipher
```

The following command runs an affine cipher encryption with the keys 5 & 8. The input is grabbed from input.txt, and the output is 
piped to output.txt

```
./lockbox -m encrypt -c affine -k 5,8 -f input.txt > output.txt
```

The following command runs a caesar shift on the same file with a key of 3 and outputs it to the terminal
```
./lockbox -m encrypt -c caesar -k 3 -f input.txt
```

## Currently Implemented Ciphers
Caesar
ROT13
Affine

## To be implemented
More ciphers!


