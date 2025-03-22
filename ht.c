// Nour Helmy
// 202202012

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100
#define DEFAULT_BYTES 10
#define DEFAULT_LINES 10 

void help(){
    printf("$ ./ht --help\n"
    "usage: ./ht [--help] [-h|-t] [-b|-l number] [filename]\n"
    "help: [--help] prints this help message\n"
    "mode: [-h|-t] -h: head, -t: tail, default -h\n"
    "unit: [-b|-l] -b: bytes, -l: lines, default -b\n"
    "[number]: number of bytes or lines, default is 10\n"
    "If you use -b or -l you need to specify the number\n"
    "stream: [filename] the full path of a file. It is optional and the default id the standard input\n"
    "Description: ht prints the head or the tail of a stream\n"
    "In case of head it prints the first number of bytes or lines to the standard output\n"
    "In case of tail it prints the last number of bytes or lines to the standard output\n");
}

void head_lines(char *filename,  int lines_num){
    // open file - read
    FILE *file = fopen(filename, "r");
    // checking if file opened
    if (file == NULL){
        printf("Unable to open file\n");
        return;
    }
    // buffer holds up to 256 characters
    char line[256];
    int count = 0;
    // loop over file until count is equal to the number of lines entered
    while (fgets(line, sizeof(line), file)){
        printf("%s", line);
        count++;
        if (count == lines_num){
            break;
        }
    }
    fclose(file);
}

void head_bytes(char *filename,  int bytes){
    // open file - read
    FILE *file = fopen(filename, "r");
    // checking if file opened
    if (file == NULL){
        printf("Unable to open file\n");
        return;
    }
    // buffer to store bytes
    char byt[256]; 
    // for reading the characters in the file
    char c; 
    int j = 0;
    // Set 'from' to 0, meaning start from the beginning of the file
    int from = 0;
    // Loop to read the required bytes from the file 
    for (int i = 0; i < bytes && c != EOF; i++) { 
        // Read the next character
        c = fgetc(file); 
        // Store the byte in the buffer once we reach 'from' (which is 0)
        if (i >= from) { 
            byt[j] = c; 
            j++; 
        } 
    } 
    byt[j] = '\0'; // Null-terminate the string
    // Print the bytes as a string 
    printf("%s\n", byt); 
    // Close the file 
    fclose(file); 
}

void tail_lines(char *filename,  int lines_num){
    // open file - read
    FILE *file = fopen(filename, "r");
    // checking if file opened
    if (file == NULL){
        printf("Unable to open file\n");
        return;
    }
    // buffer to store each line
    char line[256];
    // counter to track number of lines read
    int count = 0;
    char *lines[MAX]; // Array to store pointers to each line
    // Read the file line by line and store them in the lines array
    // looping and storing the duplicated line in the array
    while (fgets(line, sizeof(line), file) != NULL ) {
        lines[count] = strdup(line); 
        count++;
    }
    // Print the lines in reverse order
    for (int i = count - 1; i >= count-lines_num; i--) {
        printf("%s", lines[i]);
        free(lines[i]); // Free the memory allocated by strdup
    }
    fclose(file);
}

void tail_bytes(char *filename,  int bytes){
    // open file - read
    FILE *file = fopen(filename, "r");
    // checking if file opened
    if (file == NULL){
        printf("Unable to open file\n");
        return;
    }
    // buffer to store bytes
    char byt[256]; 
    // for reading the characters in the file
    char c; 
    int j = 0;
    // Move to the end of the file to determine the total size
    fseek(file, 0, SEEK_END);
    int from = ftell(file); // size fo file
    printf("bytes:  %d \n", bytes);
    int start = from - bytes;
    fseek(file, start, SEEK_SET); // Move back to the beginning of the file
    // Loop to read the required bytes from the file 
    for (int i = start; i < from && c != EOF; i++) { 
        // Read the next character
        c = fgetc(file); 
      byt[j] = c; 
      j++;
    } 
    byt[j] = '\0'; // Null-terminate the string
    // Print the bytes as a string 
    printf("%s\n", byt); 
    // Close the file 
    fclose(file); 
    }

int main(int argc, char *argv[]){
   int mode = 'h';  // Default mode is 'head'
    int unit = 'b';  // Default unit is bytes
    int num = DEFAULT_BYTES;  // Default to 10 bytes if not specified
    FILE *fp = stdin;
    char filename[256] = "";  // To store filename if provided

    // Parse command line arguments
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--help") == 0) {
            help();
            return 0;
        } else if (strcmp(argv[i], "-h") == 0) {
            mode = 'h';  // Head mode
        } else if (strcmp(argv[i], "-t") == 0) {
            mode = 't';  // Tail mode
        } else if (strcmp(argv[i], "-b") == 0) {
            unit = 'b';  // Byte unit
            if (i + 1 < argc) {
                num = atoi(argv[++i]);  // Get the number of bytes
            }
        } else if (strcmp(argv[i], "-l") == 0) {
            unit = 'l';  // Line unit
            if (i + 1 < argc) {
                num = atoi(argv[++i]);  // Get the number of lines
            }
        } else {
            // Assume it's the filename
            strcpy(filename, argv[i]);
        }
    }

    // Check if the file is provided or use stdin
    if (strlen(filename) > 0) {
        fp = fopen(filename, "r");
        if (!fp) {
            fprintf(stderr, "Error: Could not open file %s\n", filename);
            return 1;
        }
    }

    // Decide whether to print head or tail and whether to count by lines or bytes
    if (mode == 'h') {
        if (unit == 'l') {
            head_lines(filename, num);  // Print the first 'num' bytes
        } else {
            head_bytes(filename, num);  // Print the first 'num' lines
        }
    } else if (mode == 't') {
        if (unit == 'l') {
            tail_lines(filename, num);  // Print the last 'num' bytes
        } else {
            tail_bytes(filename, num);  // Print the last 'num' lines
        }
    }

    // Close the file if not reading from stdin
    if (fp != stdin) fclose(fp);

    return 0;
}

