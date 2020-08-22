#include "is_prime.h"

/**
 * Check if an input is prime or not
 *
 * @param input the input, as an int 
 * @returns true/false (true, if prime)
 */
bool is_prime(int input)
{
    if(input < 2) {
        return false;
    }
    if(input <= 3) {
        return true;
    }
    if(input % 2 == 0 || input % 3 == 0) {
        return false;
    }
    for(int i = 5; i*i <= input; i += 6) {
        if (input % i == 0 || input % (i + 2) == 0)  
           return false;
    }    
    return true;
}