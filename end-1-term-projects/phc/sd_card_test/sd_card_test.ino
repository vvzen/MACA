/*
 * SD card attached to SPI bus as follows:
 ** MOSI - pin 11
 ** MISO - pin 12
 ** CLK - pin 13
 ** CS - pin 4
*/

// PINS
#define CS_PIN 4

// libs
#include <SPI.h>
#include <SD.h>

// SD vars
File encouraging_words_file;

// CSV stuff
const unsigned int num_of_words = 48;
//char words[num_of_words][33];
//String words[num_of_words];

void setup(){

  Serial.begin(9600);
  
  // initialize the sd
  if (!SD.begin(CS_PIN)){
    Serial.println("begin failed!");
  }

  /*
  for (int wi = 0; wi < num_of_words; wi++){
    Serial.print("current index: ");
    Serial.print(wi);
    Serial.print(", word: ");
    Serial.println(words[wi]);
    delay(50);
  }
  */
}


void loop() {

  print_random_adj();
  delay(1000);
  
}


void print_random_adj(){
  
  // read file
  encouraging_words_file = SD.open("words.txt");

  // at which word we should stop
  int random_word_index = random(48);
  
  if (!encouraging_words_file){
    Serial.println("opening of file failed");
  }
  else {
    Serial.println("--------------------------");
    Serial.println("    looping inside csv    ");
    Serial.println("--------------------------");
  
    char line[33];
    int i = 0; // counter of the current char
    int w = 0; // counter for the words array
    while (encouraging_words_file.available()){
  
      char current_char = encouraging_words_file.read();
      //Serial.println(current_char);
  
      // when we encounter the end of the line
      // we know the current line has ended
      if (current_char == '\n' && i > 0){
        // add null char to end of word
        line[i] = '\0';
  
        // now we tokenize based on comma
        char * ptoken;
        ptoken = strtok(line, ",");
        // when we use NULL as parameter,
        // the function continues scanning from the last previous successfull call
        ptoken = strtok(NULL, ",");
        
        if (w == random_index){
          Serial.println(ptoken);
          break;
        }
        else {
          w++;
          
          i = 0;  
        }
      }
      // append char to array
      else {
        line[i] = current_char;
      }
  
      i++;
    }
    
    encouraging_words_file.close();
  }
}

