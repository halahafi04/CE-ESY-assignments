#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


#define SIZE 2  //size of the circular buffer
// case one  size bigger than the input name size =50
// case two  size smaller than the input name size =2

// Define the circular buffer structure //
typedef struct {
    char buffer[SIZE]; // data array
    int head;    // read pointer
    int tail;   // write pointer
    int count;  // current number of elements
} CircularBuffer;

// Initialize the circular buffer
void init(CircularBuffer *cb) {
    cb->head = 0;
    cb->tail = 0;
    cb->count = 0;
}

//  Check if the buffer is full
bool isFull(CircularBuffer *cb) {
    return cb->count == SIZE;
}

//  Check if the buffer is empty
bool isEmpty(CircularBuffer *cb) {
    return cb->count == 0;
}

// Write data to the buffer
void write_char(CircularBuffer *cb, char data) {
    // Handle buffer overflow
    if (isFull(cb)) {
        printf("Buffer Overflow\n");
        return;
    }
    cb->buffer[cb->tail] = data;
   
    cb->tail = (cb->tail + 1) % SIZE;
    cb->count++;
}

//  Read data from the buffer
char read_char(CircularBuffer *cb) {
    // Handle buffer underflow
    if (isEmpty(cb)) {
        printf("Buffer Underflow\n");
        return '\0';
    }
    char data = cb->buffer[cb->head];
   
    cb->head = (cb->head + 1) % SIZE;
    cb->count--;
    return data;
}

//  Main function 
int main() {
    CircularBuffer cb;
    init(&cb);
    char input_name[50];
    printf("Please enter your name:");
    
    // Read input using standard input
    if (fgets(input_name, sizeof(input_name), stdin) != NULL) {
        // Remove newline character
        input_name[strcspn(input_name, "\r\n")] = 0;
    }

    // Append the required string "CE-ESY"
    strcat(input_name, "CE-ESY");
    printf("Full text after appending: %s\n", input_name);
    // Write each character to the buffer
    int length = strlen(input_name);
    for (int i = 0; i < length; i++) {
        write_char(&cb, input_name[i]);
    }
    
    // Read and print back the characters without newlines
    printf("Read data: ");
    while (!isEmpty(&cb)) {
        char c = read_char(&cb);
        printf("%c", c);
    }
    printf("\n");
    // Ensure the buffer is empty
    if (isEmpty(&cb)) {
        printf("The buffer is now empty.\n");
    } else {
        printf("The buffer is not empty.\n");
    }
    return 0;
}
