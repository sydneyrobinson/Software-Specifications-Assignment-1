#include <stdio.h>
#include <string.h>

/**
Sydney Robinson, 20473812, cisc221

Goal: mimic the built-in wc command in Unix/Linux
Output: line count, word count, byte count, filename
Limitations: <stdio.h> and <string.h>
Guidelines: program only needs to work with texts encoded with ASCII

Assumptions: This program assumes that a file will be passed to the program through standard input
As such, it does not handle exception handling regarding file opening.
 */


/** 
 @brief Count number of lines in file by tracking newline characters, the same way wc does
 @param file: The file to be read
 @return int lines: The number of lines (newline characters)
 @note Alternative implementation would use getline(), which dynamically resizes buffer. However this does not mimic wc correctly
*/ 
int count_lines(FILE* file){
    int lines = 0;
    char ch;

    // Parse file and count newline characters
    while ((ch = fgetc(file)) != EOF){
    if (ch == '\n'){
        lines++;
        }
    }

    rewind(file); // Reset file pointer to beginning
    return lines;
} 

/** 
 @brief Count number of words in the file. Seperates words by delimiters tab, space, newline, and null terminator
 @param file: The file to be read
 @return int words: The number of words
 @note Accounts for consecuitve delimiters and punctuation
*/
int count_words(FILE* file){
    int words = 0; // Start at one to account for starting word
    char ch;
    long pos;
    _Bool previous_delimiter = 0; // Check for consecutive delimiters

    // Parse through characters of file until delimiter is reached
    while ((ch = fgetc(file)) != EOF){
        // If the current character is a delimiter and the previous position was not a delimiter,
        // then increment words
        if (ch == '\t' || ch == ' ' || ch == '\n' || ch == '\0'){
            if (previous_delimiter == 0){
                previous_delimiter = 1;
                words++;  
            } 
        }
        else{
            previous_delimiter = 0;
        }
    }

    rewind(file); // Reset file pointer to beginning    
    return words;
}

/** 
 @brief Counts the number of bytes in a file
 @param FIlE* file The file to be read
 @return long bytes: The number of bytes
 @note Assumes that assignment description does not require full parsing of the file
*/
long count_bytes(FILE* file){
    long bytes;

    fseek(file, 0L, SEEK_END); // Move file pointer to end of file
    bytes = ftell(file);

    rewind(file); // Reset file pointer to beginning
    return bytes;
}


int main(void){
    // File is automatically opened when passed through standard input

    int l = count_lines(stdin);
    int w = count_words(stdin);
    long int b = count_bytes(stdin);

    printf("%d %d %ld\n", l,w,b);
    
    fclose(stdin);

    return 0;
}