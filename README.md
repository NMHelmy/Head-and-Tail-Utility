# Head-and-Tail-Utility
This is a command-line utility that mimics the functionality of the head and tail commands. It allows users to display the beginning (head) or end (tail) of a file, either by lines or bytes. The program supports both file input and standard input (stdin).

## Features
* Head Mode: Display the first n lines or bytes of a file or input.
* Tail Mode: Display the last n lines or bytes of a file or input.
* Flexible Input: Supports both file input and standard input (stdin).
* Help Menu: Provides a detailed help message for usage instructions.

## Usage
Basic Usage
```
./ht [--help] [-h|-t] [-b|-l number] [filename]
```
### Options
* --help: Display the help message and exit.
* -h: Use head mode (default).
* -t: Use tail mode.
* -b: Count by bytes (default).
* -l: Count by lines.
* number: The number of bytes or lines to display (default is 10).
* filename: The file to read from. If not provided, the program reads from standard input (stdin).

## Examples
Display the first 10 lines of a file:
```
./ht -l 10 filename.txt
```
Display the last 20 bytes of a file:
```
./ht -t -b 20 filename.txt
```
Display the first 15 bytes from standard input:
```
cat filename.txt | ./ht -b 15
```
Display the help message:
```
./ht --help
```

## Code Overview
### Key Functions
* help(): Displays the help message with usage instructions.
* head_lines(): Displays the first n lines of a file.
* head_bytes(): Displays the first n bytes of a file.
* tail_lines(): Displays the last n lines of a file.
* tail_bytes(): Displays the last n bytes of a file.

### Main Function
* main(): Parses command-line arguments, determines the mode (head/tail), unit (bytes/lines), and number of units to display. It then calls the appropriate function based on the input.

### Defaults
* Mode: head (display the beginning of the file).
* Unit: bytes (count by bytes).
* Number: 10 (display 10 bytes or lines by default).

## Example Output
### Help Message
```
$ ./ht --help
usage: ./ht [--help] [-h|-t] [-b|-l number] [filename]
help: [--help] prints this help message
mode: [-h|-t] -h: head, -t: tail, default -h
unit: [-b|-l] -b: bytes, -l: lines, default -b
[number]: number of bytes or lines, default is 10
If you use -b or -l you need to specify the number
stream: [filename] the full path of a file. It is optional and the default id the standard input
Description: ht prints the head or the tail of a stream
In case of head it prints the first number of bytes or lines to the standard output
In case of tail it prints the last number of bytes or lines to the standard output
```
### Head Mode (Lines)
```
$ ./ht -l 5 filename.txt
Line 1
Line 2
Line 3
Line 4
Line 5
```
### Tail Mode (Bytes)
```
$ ./ht -t -b 20 filename.txt
Last 20 bytes of the file.
```
