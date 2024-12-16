#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <ctype.h>

#define MAX_TEXT 100

// Message structure definition
struct msg_buffer {
    long msg_type;           // Message type
    char msg_text[MAX_TEXT]; // Message content
};

void toggle_case(char *str) {
    // Function to toggle the case of the string
    for (int i = 0; str[i]; i++) {
        if (isupper(str[i])) {
            str[i] = tolower(str[i]);
        } else if (islower(str[i])) {
            str[i] = toupper(str[i]);
        }
    }
}

int main() {
    // Generate a unique key using ftok() (use my student ID for the path)
    key_t key = ftok("202011024", 65);  
    if (key == -1) {
        perror("ftok failed");
        exit(1);
    }

    // Access the message queue
    int msgid = msgget(key, 0666 | IPC_CREAT);
    if (msgid == -1) {
        perror("msgget failed");
        exit(1);
    }

    struct msg_buffer message;

    // Receive the message from the queue
    if (msgrcv(msgid, &message, sizeof(message), 1, 0) == -1) {
        perror("msgrcv failed");
        exit(1);
    }

    toggle_case(message.msg_text);  // Toggle the case of the message
    printf("Reversed msg = %s\n", message.msg_text);

    // Delete the message queue
    if (msgctl(msgid, IPC_RMID, NULL) == -1) {
        perror("msgctl failed");
        exit(1);
    }

    return 0;
}

