
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
  int mode = 0;                   // 0 = encode, 1 = decode
  int inputFreqArray[26] = {0};    // Number of times each letter occurs in text
  int outputFreqArray[26] = {0};  // Number of time each letter occurs in cipher
  char * inputFile = NULL;        // File location to read
  char * outputFile = NULL;       // File location to write results
  char * buffer = NULL;           //Buffer to hold text file input
  char * key = NULL;              //Key for Vigenere Cipher encryption
  char * outputText = NULL;       //Text after encryption
  char ** memManager[5] = {&buffer, &key, &outputText, &inputFile, &outputFile};
 


  //Parse command line arguments
  switch(argc){

    case 2:   // Help menu or text file only input
      if(argv[1][0] == '-'){
        if(strcmp(argv[1], "--help") == 0) {
          help();
          return 0;
        }
        else {
          fprintf(stderr, "%s", "Invalid Number of Arguments: Use --help for usage information\n");
          return -1;
        }
      }
      
      inputFile = (char*)malloc(sizeof(argv[1]));
      assert(inputFile);
      strcpy(inputFile, argv[1]);
      break;

    case (4):   // Encode or decode a text file
      if(strcmp(argv[1], "-e") == 0 || strcmp(argv[1], "-d") == 0) {
        inputFile = (char*)malloc(sizeof(argv[2]));
        assert(inputFile);
        strcpy(inputFile, argv[2]);

        key = (char*)malloc(sizeof(argv[3]));
        assert(key);
        strcpy(key, argv[3]);

        if(argv[1][1] == 'e'){mode = 0;}
        else if(argv[1][1] == 'd'){mode = 1;}
        break;

      }
      else {
        fprintf(stderr, "%s", "Unkown Flag Found: Use --help for usage information");
        return -1;
      }
      break;

    case (5):
      if(strcmp(argv[1], "-e") == 0 || strcmp(argv[1], "-d") == 0) {
        inputFile = (char*)malloc(sizeof(argv[2]));
        assert(inputFile);
        strcpy(inputFile, argv[2]);

        key = (char*)malloc(sizeof(argv[3]));
        assert(key);
        strcpy(key, argv[3]);

        if(argv[1][1] == 'e'){mode = 0;}
        else if(argv[1][1] == 'd'){mode = 1;}

        outputFile = (char*)malloc(sizeof(argv[4]));
        assert(outputFile);
        strcpy(outputFile, argv[4]);
      }
      else {
        fprintf(stderr, "%s", "Unkown Flag Found: Use --help for usage information");
        return -1;
      }
      break;

    default:
      fprintf(stderr, "%s", "Invalid Number of Arguments: Use --help for usage information\n");
      return -1;
  }



  //Read file into buffer, exit on failure
  if(readFile(inputFile, &buffer) == -1){return -1;};

  //Print original text scanned
  printf("ORIGINAL TEXT:\n%s\n", buffer);

  //Build frequency table from original text
  buildFreqArray(inputFreqArray, buffer);

  //Display the frequency table stored in freqArray
  printTable(inputFreqArray);


  //If encryption/decryption option is used
  if(key){
    //Encrypt/decrypt text in buffer
    vigCipher(&outputText, key, buffer, mode);

    //If encryption produces text ... 
    if(outputText){
      //Print output text
      printf("KEY: %s\n\n", key);
      printf("ENCRYPTED TEXT:\n%s\n", outputText);

      //Build frequency table from encryption
      buildFreqArray(outputFreqArray, outputText);

      //Display the encrypted frequency table
      printTable(outputFreqArray);


      //Optionally output to provided file name
      if(outputFile){
        writeFile(outputFile, outputText);
      }
    }
  }

  //Release memory
  for(int i=0; i<5; ++i){
    if(*memManager[i]){
      free(*memManager[i]);
      *memManager[i] = NULL;
    }
  }

  return 0;
}
