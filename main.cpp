#include <iostream>
#include <fstream>
#include <time.h>
#include <string>
#include <math.h>

#include "key_struct.h"
// #include "generate_key.h"
// #include "encrypt.h"
// #include "decrypt.h"
#include "is_prime.h"
#include "elliptic_curve.h"
// #include "large_pow_modulo.h"

// Driver program to test the above functions 
int main() 
{  
    srand(time(NULL));
    ifstream in_ptr;
    ofstream out_ptr;

    cout << "ECC" << endl;
    cout << "---\n\n" << endl;

    // encryption process
    cout << "Encryption process :\n" << endl;
    string input;
    in_ptr.open("plaintext.txt"); 
    getline(in_ptr, input);
    int plaintext = stoi(input);
    cout << "Plaintext - " << plaintext << endl;

    struct key_struct key;

    // bob generates private key
    long lower_lim = (long)pow(10, 3);
    long upper_lim = (long)pow(10, 4);
    do {
        key.n = rand() % (upper_lim - lower_lim) + lower_lim;
    } while(!is_prime(key.n));

    cout<<"n = "<<key.n<<endl;

    key.d = rand() % (key.n - 2) + 1;
    
    cout<<"d = "<<key.d<<endl;

    // condition for a and b : 4a^3 + 27b^2 mod n != 0 
    long temp1 = 0;
    long temp2 = 0;
    long temp3 = 0;
    long temp4 = 0; 
    do {
        key.a = rand();
        key.b = rand();
        temp1 = key.a % key.n;
        temp2 = key.b % key.n;
        temp3 = ((4%key.n) * temp1 * temp1 * temp1)%key.n;
        temp4 = ((27%key.n) * temp2 * temp2)%key.n;
    } while((temp3 + temp4) != 0);

    cout<<"a = "<<key.a<<endl;
    cout<<"b = "<<key.b<<endl;

    key.M_x = plaintext;
    key.M_y = elliptic_curve(key.M_x, key.a, key.b, key.n);

    cout<<"M = ("<<key.M_x<<","<<key.M_y<<")"<<endl;

    key.P_x = rand();
    key.P_y = elliptic_curve(key.P_x, key.a, key.b, key.n);

    cout<<"P = ("<<key.P_x<<","<<key.P_y<<")"<<endl;

    key.Q_x = key.P_x * key.d;
    key.Q_y = key.P_y * key.d;

    cout<<"Q = ("<<key.Q_x<<","<<key.Q_y<<")"<<endl;

    key.k = rand() % (key.n - 2) + 1;

    cout<<"k = "<<key.k<<endl;

    key.C1_x = key.P_x * key.k;
    key.C1_y = key.P_y * key.k;

    cout<<"C1 = ("<<key.C1_x<<","<<key.C1_y<<")"<<endl;

    key.C2_x = key.Q_x * key.k + key.M_x;
    key.C2_y = key.Q_y * key.k + key.M_y;

    cout<<"C2 = ("<<key.C2_x<<","<<key.C2_y<<")"<<endl;

    long long retrieved = key.C2_x - key.d * key.C1_x;

    // long long ciphertext = encrypt(plaintext, key); 
    // cout << "Ciphertext C1- " << key.C1_x << endl; 
    // cout << "Ciphertext C2- " << key.C2_x << endl; 
    cout << "\n\n";
    in_ptr.close();

    // decryption process
    // cout << "Decryption process :\n" << endl; 
    // plaintext = decrypt(ciphertext, key); 
    cout << "Retrieved Plaintext - " << retrieved << endl; 
    cout << "\n";
    in_ptr.close();

    return 0; 
} 
