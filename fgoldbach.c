#include <stdio.h>
//#include <math.h>
#include <stdlib.h>
#include <time.h>

#define LIMIT 32000

int matoi(char *s) {
    int c = 0;
    for (int i = 0; s[i] != '\0'; i++) {
        c = 10 * c + (s[i] - '0');
    }
    return c;
}

/*
int is_prime(int n) {
    if (n == 2) {
        return 1;
    }
    if (n < 2 || n % 2 == 0) {
        return 0;
    }
    int N = (int)sqrt(n);
    for (int i = 3; i <= N; i += 2) {
        if (n % i == 0) {
            return 0;
        }
    }
    return 1;
}
*/

int *sieve(int n) {
    int *ans = malloc((n + 1) * sizeof(int));
    for (int i = 0; i <= n; i++) {
        ans[i] = i;
    }
    for (int i = 2; i <= n; i++) {
        for (int j = i * i; j <= n; j += i) {
            ans[j] = '\0';
        }
    }
    ans[0] = '\0';
    ans[1] = '\0'; //override 0 and 1
    return ans;
}

void solve(int n, int *xarr) { 
    /*
    int x = 0; //array index
    int arr[n]; //worst case scenario
    for (int i = 2; i <= n ; i++) { //start from 2 because it is the smallest prime
        if (is_prime(i)) {
            arr[x] = i;
            x++;
        }
    }
    */

    int *primes = sieve(n);
    int x = 0;
    int arr[n];
    for (int i = 0; i <= n; i++) {
        if (primes[i] == '\0') {
            continue;
        }
        arr[x] = i;
        x++;
    }
    free(primes);    
    //DEBUG LOG:
    //printf("\nArray length is: %d\n", x); //x - 1 is the last element
    int l = 0;
    int r = x - 1; //x is the length of the array!
    //int x is the right pointer here
    //You cannot skip logarithmically; because there is no guarantee about the spacing of elements and the diff between them
    //For example, assume that arr[l] + arr[r] > n for the first iteration, if you skip half of the elements on the right side
    //you have incorrectly eliminated half the elements permanently with no way of knowing if arr[l] + arr[r - 1] could have
    //given you the answer; this is the simplest reason why it's different than binary search
    //proof by contradiction, QED
    int sum = 0;
    while (sum != n) {
        sum = arr[l] + arr[r];
        if (sum == n) {
            xarr[0] = arr[l];
            xarr[1] = arr[r];
            return;
        } else if (sum > n) {
            r--;
        } else {
            l++;
        }
    }
}

int main(int argc, char **args) {
    srand(time(NULL));
    int n;
    if (argc == 1) {
        n = rand() % LIMIT;        
        n += (n % 2); //if it's an odd number make sure that it's even
    } else {
        n = matoi(args[1]);
    }
    if (n % 2 != 0 || n <= 2) {
        printf("\nFaulty input.\n");
        return 1;
    }
    int arr[2];
    solve(n, arr);
    printf("\n%d + %d = %d\n", arr[0], arr[1], n);
    return 0;
}
