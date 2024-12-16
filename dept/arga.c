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

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <message>\n", argv[0]);
        exit(1);
    }

    // Concatenate all arguments into a single message
    char message_text[MAX_TEXT] = "";
    for (int i = 1; i < argc; i++) {
        strncat(message_text, argv[i], MAX_TEXT - strlen(message_text) - 1);
        if (i < argc - 1) {
            strncat(message_text, " ", MAX_TEXT - strlen(message_text) - 1); // Add space between words
        }
    }

    // Generate a unique key using ftok() (use my student ID for the path)
    key_t key = ftok("202011024", 65);  
    if (key == -1) {
        perror("ftok failed");
        exit(1);
    }

    // Create or access the message queue
    int msgid = msgget(key, 0666 | IPC_CREAT);
    if (msgid == -1) {
        perror("msgget failed");
        exit(1);
    }

    struct msg_buffer message;
    message.msg_type = 1;  // Set message type
    strncpy(message.msg_text, message_text, MAX_TEXT); // Copy the concatenated message to the message queue

    // Send the message to the queue
    if (msgsnd(msgid, &message, sizeof(message), 0) == -1) {
        perror("msgsnd failed");
        exit(1);
    }

    printf("Message sent to the queue: %s\n", message.msg_text);
    return 0;
}

