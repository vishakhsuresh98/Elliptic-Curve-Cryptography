#include <math.h>
#include "elliptic_curve.h"

long long elliptic_curve(long long x, long a, long b, long long p)
{
    long long y = (long long)pow(x,1.5);
    while(((long long)pow(y, 2) % p) != ((long long)pow(x, 3) + a * x + b) % p) {
        y++;
    }
    return y;
}