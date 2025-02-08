#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include "msgq.h"
#define N 132
#define key 1234


// Function to reverse a string
void strrev(char *str) {
    int len = strlen(str);
    for (int i = 0; i < len / 2; i++) {
        char temp = str[i];
        str[i] = str[len - i - 1];
        str[len - i - 1] = temp;
    }
}

// Function to convert decimal to binary using bitwise operations

   

void decToBinary(int n, char *bin) {
    int c = 1;  // Start with 1
    int i = 0;

    while (c <= n)  // Find the highest power of 2 within n
        c <<= 1;
    
    c >>= 1;  // Get back to the correct starting position

    while (c > 0) {
        if (n & c)  // Check if the bit is 1
            bin[i++] = '1';
        else
            bin[i++] = '0';

        c >>= 1;  // Shift right to the next bit
    }

    bin[i] = '\0';  // Null-terminate the string
}






// Function to convert decimal to octal using bitwise operations
void decToOctal(int n, char *oct) {
    int i = 0;
    while (n > 0) {
        oct[i++] = (n & 7) + '0'; // Extract last 3 bits (n % 8)
        n >>= 3;  // Right shift by 3
    }
    oct[i] = '\0';
    strrev(oct);
}

// Function to convert decimal to hexadecimal using bitwise operations
void decToHex(int n, char *hex) {
    int i = 0;
    while (n > 0) {
        int rem = n & 15; // Extract last 4 bits (n % 16)
        hex[i++] = (rem < 10) ? (rem + '0') : (rem - 10 + 'A');
        n >>= 4;  // Right shift by 4
    }
    hex[i] = '\0';
    strrev(hex);
}

int main() {
     int msgid = msgget(key, IPC_CREAT | 0666);
    MQ msg;
    int num;

    printf("Enter a decimal number: ");
    scanf("%d", &num);

    char bin[N], oct[N], hex[N];
    decToBinary(num, bin);
    decToOctal(num, oct);
    decToHex(num, hex);

    // Sending Binary
    msg.mt = 1;
    strcpy(msg.md, bin);
    msgsnd(msgid, &msg, sizeof(msg.md), 0);

    // Sending Octal
    msg.mt = 2;
    strcpy(msg.md, oct);
    msgsnd(msgid, &msg, sizeof(msg.md), 0);

    // Sending Hexadecimal
    msg.mt = 3;
    strcpy(msg.md, hex);
    msgsnd(msgid, &msg, sizeof(msg.md), 0);

    return 0;
}

