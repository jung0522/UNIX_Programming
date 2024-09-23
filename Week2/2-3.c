#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
    char *str;  // Declare a pointer to string

    str = malloc(sizeof(char) * 20);  // allocate memory (20 bytes)

    strcpy(str, "Hello");  // Copy the string "Hello" into the allocated memory
    printf("%s\n", str);  // Print "Hello"

    strcpy(str, "Good morning");  // Copy the string "Good morning" into the same memory
    printf("%s\n", str);  // Print "Good morning"

    free(str);  // Free the allocated memory
    return 0;  
}

