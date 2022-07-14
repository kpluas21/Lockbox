/* A cipher multitool. Accepts input from a file and outputs either encrypted or decrypted text to a file or stdout */
/* Which ciphers are used and which keys are needed depend on the command line arguments provided by the user. */
/* All ciphers assume you're using the English alphabet and only encrypt/decrypt the 26 alphabetic characters.  */
/* AUTHOR : Kevin Pluas */


/* lockbox.cpp : In charge of handling command line arguments and program flow */
#include<iostream>  //for stdin+stdout
#include<vector>    //what we use to store our letters
#include<unistd.h>  //for getopt and parsing command line arguments
#include<memory>
#include<cstring>
#include<sstream>
#include<fstream>

#include"lockbox.h"

/* PROTOTYPES */
void printUsageMessage(const char*);
int handleArguments(Payload*, int,  char**);

int main(int argc, char** argv) {
    Payload* payload = new Payload;          /* Always practice safe memory management!!  */
    if(payload == nullptr) { return 2; }     /* No memory available, exit */
    
    /* 1. Parse CL arguments */
    if(handleArguments(payload, argc, argv) != 0) {
        return 1;
    }

    switch(payload->cipher) {
        case 'c':
            ceasar(payload);
            break;
        case 'a':
            if(affineValidateKeys(payload) == false) { 
                std::cerr<<"Invalid keys entered for an affine cipher\n";
                return 1;
            }
            return 0;
    }
    payload->displayOutput();    

    /* 5. Validate keys */
    /* 6. Run the input through the cipher with their respective keys */
    /* 7. Output to file OR stdout depending on args */
    /* 8. End program */

    delete payload;
    return 0;
}

void printUsageMessage(const char* prog) {
    std::cerr<<"Usage: " << prog << "[MODE] [CIPHER] [KEYS (comma-separated)] file\n"
             <<"A cipher multitool used to encrypt or decrypt text files\n";
}


/* Loops through and parses the command line arguments provided to the program. */
/* Returns a non-zero value on error or invalid argument */
int handleArguments(Payload* payload, int argc, char* argv[]) {
    int opt;
    std::fstream inputFile;
    std::stringstream optss;
    while((opt = getopt(argc, argv, ":hm:c:k:f:")) != -1) {
        switch(opt) {
            case 'h':
                printUsageMessage(argv[0]);
                return 1;
            case 'm':
                /* 2. Determine if encrypting or decrypting */
                if(strcmp(optarg, "encrypt") == 0 || strcmp(optarg, "decrypt") == 0) {    /* Is the user encrypting or decrypting? */
                    payload->mode = optarg[0];                                            /* We only need the first letter to determine mode */
                }
                break;
            case 'c':
                /* 3. Determine which ciphers to use */
                if(strcmp(optarg, "caesar") == 0 
                || strcmp(optarg, "affine") == 0 
                || strcmp(optarg, "rot13") == 0) {
                    payload->cipher = optarg[0];
                }
                break;
            case 'k':
                optss.str(optarg);
                for(std::string key; std::getline(optss, key, ',');) {
                    payload->keys.push_back(std::stoi(key));
                }
                break;
            case 'f':
                payload->filename = optarg;
                inputFile.open(payload->filename);
                if(!inputFile) { 
                    std::cerr<<"File could not be opened\n";
                    return 1; 
                }
                inputFile.close();
                break;
            case '?':
                std::cerr<<"Unknown option "<< optopt << '\n';
                return 1;
            case ':':
                std::cerr<<"Missing argument for " << optopt << '\n';
                return 1;
        }
        
    }

    payload->displayContents();
    return 0; /* All good. */
}