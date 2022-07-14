/* This header file contains the algorithms and classes we use for our main cpp file */
#include<iostream>
#include<vector>
#include<numeric>

/* To reduce the number of arguments passed to the functions, info is stored in a data structure I'll call the payload */
struct Payload {
    std::vector<int> keys {};                               /* Contains one or more keys for the ciphers */
    std::vector<std::string> output {};                     /* Contains all of our output for either stdout or a file */
    
    std::string alphabet {"abcdefghijklmnopqrstuvwxyz"};    /* The payload will always have this handy when needed */
    std::string modifiedAlphabet   {};                      /* The alphabet after the respective ciphers and keys are applied. Used for quick access. */
    std::string filename;                                   /* Our input file */

    char mode;                                              /* e/E for encrypt, d/D for decrypt, user MUST be explicit, otherwise the program will not run */
    char cipher;                                            /* Used by main to determine which cipher to use */

    inline int getChIndex(char c) {                         /* A helper function to convert the characters to their */
        return (static_cast<int>(c) % 32)- 1;               /* numerical equivalents in the range [0 - 25] */
    }

    void displayContents() {
        std::cerr<<"Mode: "     << mode    << '\n'
                 <<"Cipher: "   << cipher  << '\n'
                 <<"Filename: " << filename<<'\n' 
                 <<"Keys: "     << '\n';
        for(auto x : keys) {
            std::cerr<<x << ' ';
        }
        std::cerr<<'\n';
    }

    void displayOutput() {
        for(auto line : output) {
            std::cout<<line<<std::endl;                     /* The endl is necessary to flush output and add a newline */
        }
    }
};

/* PROTOTYPES */
void ceasar(Payload*);
void rot13(Payload*);
void affine(Payload*);

void createAffineEncryptedAlphabet(Payload*);

bool affineValidateKeys(Payload*);


void ceasar(Payload* payload) {
    std::ifstream inputFile(payload->filename); /* Open up the file stream for input */
    int decryptIndex = 0;

     /* Here, we start encrypting our input file, line by line, storing them into the output vector */
    if(payload->mode == 'e') {
        /* Before anything, create the encrypted alphabet according to the key provided */
        for(auto c : payload->alphabet) {
            payload->modifiedAlphabet.push_back(
                payload->alphabet[(payload->getChIndex(c) + payload->keys.at(0)) % 26]);
        }
        
        for(std::string line; std::getline(inputFile, line);) {                                 /* Grab one whole line including the newline */
            for(int i = 0; i < line.size(); i++) {                                              /* We change out line token char by char */
                if(isalpha(line.at(i))) {                                                       /* Encountered letter */
                    line.at(i) = payload->modifiedAlphabet[payload->getChIndex(line.at(i))];    /* Modify the individual letter in the line */
                }
                                                                                                /* We ignore anything that isn't a letter */
            }
            payload->output.push_back(line);                        /* We throw the modified input line into our string vector for future output */
        }
    }
    else if(payload->mode == 'd') {
        for(std::string line; std::getline(inputFile, line);) {
            for(int i = 0; i < line.size(); i++) {
                if(isalpha(line.at(i))) {
                    decryptIndex = payload->getChIndex(line.at(i)) - payload->keys.at(0) % 26;
                    if(decryptIndex < 0) { /* We need to wrap the number around since negatives are invalid */
                        decryptIndex += 26;
                    }
                    line.at(i) = payload->alphabet.at(decryptIndex);
                }
                /* TODO: FIX NEGATIVE MODULO!! */
            }
            payload->output.push_back(line);
        }
    }

    return; /* I like to be explicit with my returns regardless of the function type */
}

/* Returns 0 if the keys provided are valid for encryption/decryption. */
bool affineValidateKeys(Payload* payload) {
    int a = payload->keys.at(0);
    int b = payload->keys.at(1);

    return ( (std::gcd(a, 26) == 1) && (b >= 0 && b <= 25) ); /* a must be coprime with 26 and b must be within 0 - 25 inclusive. */
}

/* An affine cipher function. Inverse modulus needs to be calculated for decryption. */
/* A brute force method of calculating it is used since its a smaller modulo of only 26*/
void affine(Payload* payload) {
    int a = payload->keys.at(0);
    int b = payload->keys.at(1);
    std::ifstream inputFile(payload->filename);

    switch(payload->mode) {
        case 'e':
            /* create our encrypted alphabet first */
            break;
        case 'd':
            /* find the modular inverse */
            break;
    }
    return;
}

void createAffineEncryptedAlphabet(Payload* payload) {
    for(int i = 0; i < payload->alphabet.size(); i++) {
        payload->modifiedAlphabet += payload->alphabet[i * a + b % 26];
    }
}