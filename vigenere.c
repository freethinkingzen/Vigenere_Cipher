
/* This program was created for CS491 Intro to Computer Security at
 * Portland State University by John Lewis, 10-13-2020.
 *
 * This program takes a text file as an argument and creates a frequency table
 * of the lower-case alphabetic letters as percentages of the total lower case
 * characters in the file.
 * 
 * To compile for first time, use type "make" into the command prompt
 *
 * Use "./vigenere --help" for usage information
 *
 */


#include "vigenere.h"

int main(int argc, char*argv[]) {

  int textFreqArray[26] = {0};    //Number of times each letter occurs in text
  int cipherFreqArray[26] = {0};  //Number of time each letter occurs in cipher
  char * buffer = NULL;           //Buffer to hold text file input
  char * key = NULL;              //Key for Vigenere Cipher encryption
  char * encryption = NULL;       //Text after encryption
  char ** memManager[3] = {&buffer, &key, &encryption};


  //Check arguments passed from command line
  switch(argc){

    case 2:   //Run with file only or help
      //If help, display info and exit
      if(strcmp(argv[1], "--help") == 0){
        help();
        return 0;
      }
      break;

    case 3:   //Run with file and key for encryption
      //Capture key in dynamic array and ensure lower-case
      key = (char*)malloc(sizeof(argv[2]));
      assert(key);
      strcpy(key, argv[2]);
      for(int i=0; i<strlen(key); ++i){
        if(isalpha(key[i]) == 0){
          fprintf(stderr, "%s", "Key Format: Key string must be alphabetic only\n");
          free(key);
          key = NULL;
          return -1;
        }
        key[i] = tolower(key[i]);
      }
      break;

    default:
      fprintf(stderr, "%s","Incorrect Number of Arguments: use --help for usage\n");
      return -1;
  }


  //Read file into buffer, exit on failure
  if(readFile(argv[1], &buffer) == -1){return -1;};

  //Print original text scanned
  printf("ORIGINAL TEXT:\n%s\n", buffer);

  //Build frequency table from original text
  buildFreqArray(textFreqArray, buffer);

  //Display the frequency table stored in freqArray
  printTable(textFreqArray);



  //If encryption option is used
  if(key){
    //Encrypt text in buffer
    vigCipher(&encryption, key, buffer);

    //Print encrypted text
    printf("KEY: %s\n\n", key);
    printf("ENCRYPTED TEXT:\n%s\n", encryption);
  
    //Build frequency table from encryption
    buildFreqArray(cipherFreqArray, encryption);

    //Display the encrypted frequency table
    printTable(cipherFreqArray);
    
  }

  //Release memory
  for(int i=0; i<3; ++i){
    if(*memManager[i]){
      free(*memManager[i]);
      *memManager[i] = NULL;
    }
  }

  return 0;
}
