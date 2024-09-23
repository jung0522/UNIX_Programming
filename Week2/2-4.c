#include <stdio.h> 
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int n; 
    extern char *optarg; 
    extern int optind;

    long r; 

    while ((n = getopt(argc, argv, "a:m:")) != -1) {
        switch (n) {
            case 'a': // If option '-a' 
                r = 0; // Initialize result to 0 
                // Loop through all arguments after the '-a' option
                for (--optind; optind < argc; optind++) 
                    r = r + atol(argv[optind]); // Add each argument to the result

                break; 
                
            case 'm': // If option '-m' 
                r = 1; // Initialize result to 1 
                // Loop through all arguments after the '-m' option
                for (--optind; optind < argc; optind++) 
                    r = r * atol(argv[optind]); // Multiply each argument with the result

                break;
                
        // Print the result of the operation
        printf("res = %ld\n", r);
    }
    return 0;
}

