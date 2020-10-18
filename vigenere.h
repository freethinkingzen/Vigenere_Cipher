
/* This program was created for CS491 Intro to Computer Security at
 * Portland State University by John Lewis, 10-13-2020.
 *
 * This file includes the global constants, headers, and functions for the
 * Vigenere Cipher program.
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <assert.h>


const size_t BUFFER_START_SIZE = 1000;  // Initial size of read-in buffer




/* Reads text file and return success or failure with int
 * Arguments:
 *    - filename as string literal or array
 *    - NULL char* pointer that will be assigned text contents
 * Returns:
 *    - -1 if file is not opened
 *    - 0 on success
 * Aborts program if calloc() or realloc() fail */

int readFile(const char * filename, char ** buffer){
  char * tempbuffer = NULL;             // Temp buffer while reading file
  int buffLen = 0;                      // Keep track of text length
  size_t buffSize = BUFFER_START_SIZE;  // Start size of buffer from constant setting
  int ch;                               // Holds each letter as it's read in

  assert(!*buffer);

  //Try to open file
  //display error and return NULL on failure
  FILE * toread; 
  toread = fopen(filename, "rt");
  if(!toread){
    perror("ERROR: File Not Found");
    return -1;
  }
  
  //Initialize buffer to buffSize
  tempbuffer = (char*)calloc(buffSize, sizeof(char));
  assert(tempbuffer);

  do{
    ch = fgetc(toread);
    if(ch != EOF){
      //If the buffer will overflow, expand buffer memory
      if(buffLen >= buffSize){
        buffSize += buffSize;
        tempbuffer = (char*)realloc(tempbuffer, sizeof(char) * buffSize);
        assert(tempbuffer);
      }
      //Add character to buffer as lowercase and increment index
      tempbuffer[buffLen] = tolower(ch);
      ++buffLen;
    }
  }while(ch != EOF);

  //Close file
  fclose(toread);

  //Resize buffer to exact needed size
  tempbuffer = (char*)realloc(tempbuffer, sizeof(char) * (buffLen+1));
  assert(tempbuffer);
  tempbuffer[buffLen] = '\0';  //Add character manually instead of strcpy

  //Assign to passed in pointer and clean up pointers
  *buffer = tempbuffer;
  tempbuffer = NULL;
  printf("\n");

  return 0;
}



/* Fills the frequency array passed as argument
 * Arguments:
 *      - Int* pointer to frequency array
 *      - Char* pointer to text being anaylyzed */
void buildFreqArray(int * freqArray, const char * text){
  for(int i=0; i<strlen(text); ++i){
    if(text[i] >= 'a' && text[i] <= 'z'){
      freqArray[text[i] - 'a']++;
    }
  }
}



/* Encrypt input using Vigenere Cipher
 * Arguments:
        - Char** pointer, NULL char* pointer passed by reference
        - Char* pointer to character array to be used as key
        - Char* pointer to character array to be encrypted */
void vigCipher(char ** encryption, const char * key, const char * text){
  size_t textLen = strlen(text);
  size_t keyLen = strlen(key);
  char * temp = (char*)calloc(textLen+1, sizeof(char));
  assert(temp);

  for(int i=0; i<textLen; ++i){
    if(text[i] >= 'a' && text[i] <= 'z'){
      if((text[i]-'a') + (key[i%keyLen]-'a') >= 26){
        temp[i] = (text[i]-'a') + key[i%keyLen] - 26;
      }
      else {
        temp[i] = (text[i] - 'a') + key[i%keyLen];
      }
    }
    else {
      temp[i] = text[i];
    }
  }
  *encryption = temp;
  temp = NULL;
}


/* Print frequency arrays by leveraging ascii values
 * freqArrays are counts of instances, this function takes the total number of
 * alphabetic characters as an argument to convert these to percentages */
void printTable(const int * freqArray){

  int total = 0;
  for(int i=0; i<26; ++i){
    total += freqArray[i];
  }

  printf("FREQUENCY TABLE:\n");
  for(int i=0; i<26; ++i){
    printf("%c: %.3f%%\n",i+'a',(freqArray[i]/(float)total) *100);
  }
  printf("\n");
}



// Displays the help information when the --help flag is used from the command line
void help(){
  printf("\n* The default behavior of this program reads a text file and prints"
         " the contents\n* of the file followed by a character frequency table." 
         " Addition of a key string will\n* run the program with a Vigenere Cipher"
         ", display the original text and frequency\n* table, then display the "
         "encrypted text and it's frequency table.\n\nUSAGE: ./vigenere [Text File]"
         "\t\tPrint the text and character frequency table\n       ./vigenere [Text "
         "File] [Key]\tEncrypts text with Vigenere Cipher based on provid"
         "ed key \n       ./vigenere --help\t\tShow usage and help info\n\nARGUMENT"
         "S:\n       [Text File]\tValid text file location for program to read"
         "\n       [Key]\t\tLower-case alphabetic string to be used as a key in"
         " the Vigenere Cipher\n\n");
}
