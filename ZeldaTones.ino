/* 
  This is an arduino project to play Zelda (NES/SNES/GBC) tones directly from the board without the need of any audio/power electronics.
  It plays the sounds in mono audio as 8bit tones.

  This project is based on the code by Robson Couto.
  Link to his project: https://github.com/robsoncouto/arduino-songs                                            
                                              
*/

#include <Adafruit_NeoPixel.h>

#define NeoPIN D5
#define NUM_LEDS 4
int brightness = 255;
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, NeoPIN, NEO_RGB + NEO_KHZ800);
//CRGB leds[NUM_LEDS];


#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978
#define REST 0


// change this to whichever pin you want to use
int buzzer = D8;

// constants won't change. They're used here to set pin numbers:
const int buttonPin = D2;  // the number of the pushbutton pin
//const int ledGreen=D5, ledWhite=D6;

//--------------------------
// constants won't change. They're used here to set pin numbers:
const int DEBOUNCE_DELAY = 50;   // the debounce time; increase if the output flickers

// Variables will change:
int lastSteadyState = LOW;       // the previous steady state from the input pin
int lastFlickerableState = LOW;  // the previous flickerable state from the input pin
int currentState;                // the current reading from the input pin

// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
//----------------

int boton=0;
int song=0;
int notesIntro=0, notesTitle=0, notesItem=0, notesSecret=0, notesEgg=0, notesDungeon=0, notesSword=0;
int tempoIntro=110, tempoTitle=110, tempoItem=120, tempoSecret=120, tempoDungeon=90, tempoSword=180; 
 


//------ Here we store the songs-------------
// notes of the moledy followed by the duration.
// a 4 means a quarter note, 8 an eighteenth , 16 sixteenth, so on
// !!negative numbers are used to represent dotted notes,
// so -4 means a dotted quarter note, that is, a quarter plus an eighteenth!!
int intro[] = { 
  //GBC bios startup - tempo=110
  NOTE_C6,16,   
  NOTE_C7,-8,
  REST,8 
};


int title[] = {
  // Zelda Link's awakening title screen song - tempo=110
  //Based on the arrangement at https://www.flutetunes.com/tunes.php?id=169
  
  NOTE_AS4,4,  NOTE_F4,-4,  NOTE_AS4,8,  NOTE_AS4,16,  NOTE_C5,16, NOTE_D5,16, NOTE_DS5,16,//7
  NOTE_F5,2,  NOTE_F5,8,  NOTE_F5,8,  NOTE_F5,8,  NOTE_FS5,16, NOTE_GS5,16,
  NOTE_AS5,-2,  NOTE_AS5,8,  NOTE_AS5,8,  NOTE_GS5,8,  NOTE_FS5,16,
  NOTE_GS5,-8,  NOTE_FS5,16,  NOTE_F5,2,  NOTE_F5,4, 

  NOTE_DS5,-8, NOTE_F5,16, NOTE_FS5,2, NOTE_F5,8, NOTE_DS5,8, //11
  NOTE_CS5,-8, NOTE_DS5,16, NOTE_F5,2, NOTE_DS5,8, NOTE_CS5,8,
  NOTE_C5,-8, NOTE_D5,16, NOTE_E5,2, NOTE_G5,8, 
  NOTE_F5,16, NOTE_F4,16, NOTE_F4,16, NOTE_F4,16,NOTE_F4,16,NOTE_F4,16,NOTE_F4,16,NOTE_F4,16,NOTE_F4,8, NOTE_F4,16,NOTE_F4,8,

  /*NOTE_AS4,4,  NOTE_F4,-4,  NOTE_AS4,8,  NOTE_AS4,16,  NOTE_C5,16, NOTE_D5,16, NOTE_DS5,16,//15
  NOTE_F5,2,  NOTE_F5,8,  NOTE_F5,8,  NOTE_F5,8,  NOTE_FS5,16, NOTE_GS5,16,
  NOTE_AS5,-2, NOTE_CS6,4,
  NOTE_C6,4, NOTE_A5,2, NOTE_F5,4,
  NOTE_FS5,-2, NOTE_AS5,4,
  NOTE_A5,4, NOTE_F5,2, NOTE_F5,4,

  NOTE_FS5,-2, NOTE_AS5,4,
  NOTE_A5,4, NOTE_F5,2, NOTE_D5,4,
  NOTE_DS5,-2, NOTE_FS5,4,
  NOTE_F5,4, NOTE_CS5,2, NOTE_AS4,4,
  NOTE_C5,-8, NOTE_D5,16, NOTE_E5,2, NOTE_G5,8, 
  NOTE_F5,16, NOTE_F4,16, NOTE_F4,16, //NOTE_F4,16,NOTE_F4,16,NOTE_F4,16,NOTE_F4,16,NOTE_F4,16,NOTE_F4,8, NOTE_F4,16,NOTE_F4,8,*/
  
  REST,8
};

int item[]={
  //Found an item - tempo=80
  NOTE_GS5,16, NOTE_A5,16, NOTE_AS5,16, NOTE_B5,-2, 
  REST,8
  };

int secret[]={
  //Found an secret - tempo=120
  NOTE_G5,16, NOTE_FS5,16, NOTE_DS5,16, NOTE_A4,16, NOTE_GS4,16, NOTE_E5,16, NOTE_GS5,16, NOTE_C6,16,
  REST,8
  };

int dungeon[]={
  //dungeon song - tempo=90
  NOTE_G4,16,NOTE_AS4,16,NOTE_D5,16,NOTE_DS5,16,
  NOTE_G4,16,NOTE_AS4,16,NOTE_D5,16,NOTE_DS5,16,
  NOTE_G4,16,NOTE_AS4,16,NOTE_D5,16,NOTE_DS5,16,
  NOTE_G4,16,NOTE_AS4,16,NOTE_D5,16,NOTE_DS5,16,

  NOTE_FS4,16,NOTE_A4,16,NOTE_D5,16,NOTE_DS5,16,
  NOTE_FS4,16,NOTE_A4,16,NOTE_D5,16,NOTE_DS5,16,
  NOTE_FS4,16,NOTE_A4,16,NOTE_D5,16,NOTE_DS5,16,
  NOTE_FS4,16,NOTE_A4,16,NOTE_D5,16,NOTE_DS5,16,
  
  NOTE_F4,16,NOTE_GS4,16,NOTE_D5,16,NOTE_DS5,16,
  NOTE_F4,16,NOTE_GS4,16,NOTE_D5,16,NOTE_DS5,16,
  NOTE_F4,16,NOTE_GS4,16,NOTE_D5,16,NOTE_DS5,16,
  NOTE_F4,16,NOTE_GS4,16,NOTE_D5,16,NOTE_DS5,16, 

  NOTE_E4,16,NOTE_G4,16,NOTE_D5,16,NOTE_DS5,16,
  NOTE_E4,16,NOTE_G4,16,NOTE_D5,16,NOTE_DS5,16,
  NOTE_E4,16,NOTE_G4,16,NOTE_D5,16,NOTE_DS5,16,
  NOTE_E4,16,NOTE_G4,16,NOTE_D5,16,NOTE_DS5,16,

  NOTE_DS5,16,NOTE_G4,16,NOTE_C5,16,NOTE_D5,16,
  NOTE_DS5,16,NOTE_G4,16,NOTE_C5,16,NOTE_D5,16,
  NOTE_DS5,16,NOTE_G4,16,NOTE_C5,16,NOTE_D5,16,
  NOTE_DS5,16,NOTE_G4,16,NOTE_C5,16,NOTE_D5,16,
  NOTE_DS5,16,NOTE_G4,16,NOTE_C5,16,NOTE_D5,16,
  NOTE_DS5,16,NOTE_G4,16,NOTE_C5,16,NOTE_D5,16,
  NOTE_DS5,16,NOTE_G4,16,NOTE_C5,16,NOTE_D5,16,
  NOTE_DS5,16,NOTE_G4,16,NOTE_C5,16,NOTE_D5,16,  

  NOTE_C4,16,NOTE_FS4,16,NOTE_A4,16,NOTE_C5,16,
  NOTE_FS4,16,NOTE_A4,16,NOTE_C5,16,NOTE_DS5,16,
  NOTE_A4,16,NOTE_C5,16,NOTE_DS5,16,NOTE_C5,16,
  NOTE_DS5,16,NOTE_FS5,16,NOTE_DS5,16,NOTE_FS5,16,
  NOTE_A5,16,NOTE_FS5,16,NOTE_A5,16,NOTE_C6,16,

  REST,8
  };

int sword[]={
  //searching the sword - tempo=180
  NOTE_E6,16, NOTE_DS6,16, NOTE_B5,16, NOTE_GS5,16, 
  NOTE_E5,16, NOTE_DS5,16, NOTE_B4,16, NOTE_GS4,16,
  NOTE_FS6,16,NOTE_E6,16, NOTE_CS6,16,NOTE_A5,16, 
  NOTE_FS5,16,NOTE_E5,16, NOTE_CS5,16, NOTE_A4,16,
  NOTE_GS6,16, NOTE_FS6,16, NOTE_DS6,16, NOTE_B5,16, 
  NOTE_GS5,16, NOTE_FS5,16, NOTE_DS5,16, NOTE_B4,16,
  NOTE_A6,16, NOTE_GS6,16, NOTE_E6,16, NOTE_CS6,16,
  NOTE_A5,16, NOTE_GS5,16, NOTE_E5,16, NOTE_CS5,16,

  NOTE_B3,8, NOTE_FS4,8, NOTE_A4,8, NOTE_B4,8,
  NOTE_DS5,8, NOTE_FS5,8, NOTE_A5,8, NOTE_B5,8,
  NOTE_B6,-4,
  
  REST,8
  };  
//---------------------



void setup() {
  Serial.begin(115200);
  Serial.println("hello...");
  strip.setBrightness(brightness);
  strip.begin();
  strip.show(); 
  delay(50);
  Serial.println("NeoPixel started");
  strip.setPixelColor(0, strip.Color(150,   0,   0));         //  Set pixel's color (in RAM)
  //strip.show(); 

  strip.setPixelColor(1, strip.Color(50,   50,   50));         //  Set pixel's color (in RAM)
  strip.show(); 
  
  strip.setPixelColor(2, strip.Color(50,   50,   50));         //  Set pixel's color (in RAM)
  strip.show(); 

  strip.setPixelColor(3, strip.Color(50,   50,   50));         //  Set pixel's color (in RAM)
  strip.show();

  //colorWipe(strip.Color(50,   50,   50), 15); 

  //Define switch button pin as input and set it up with pull up resistor
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(buzzer, OUTPUT);
  digitalWrite(buzzer, LOW);


  /*pinMode(ledGreen, OUTPUT);
  pinMode(ledWhite, OUTPUT);

  delay(1500);
  digitalWrite(ledGreen, HIGH);
  digitalWrite(ledWhite, HIGH);*/


  //Play Gameboy color intro sound when powering the project
  int notesIntro=sizeof(intro)/sizeof(intro[0])/2;
  playSong(intro, notesIntro, tempoIntro);

  //we need to create a seed for the random function to ensure that we get different numbers 
  randomSeed(analogRead(0));
  song=0;
  boton = 0;

}

void loop() {

 //With this switch I want to guarantee that the button only changes one song
 //I am including the debouncing of the button in the default case, where we only wait for the button to be pressed
 //Case 1 is when the button is pressed, so we select a random song to be played
  switch (boton) {
    case 1:  
      song = random(1,6);
      //Serial.println("Boton: caso 1 + Song: "+String(song)); 
      boton = 0;
      break;

    
    default:
      for (int i = 0; i < 5; i++) {
      ///*****************
      //debouncing the button when pressed
      //read the state of the switch/button:
          currentState = digitalRead(buttonPin);
        
          // check to see if you just pressed the button
          // (i.e. the input went from LOW to HIGH), and you've waited long enough
          // since the last press to ignore any noise:
        
          // If the switch/button changed, due to noise or pressing:
          if (currentState != lastFlickerableState) {
            // reset the debouncing timer
            lastDebounceTime = millis();
            // save the the last flickerable state
            lastFlickerableState = currentState;
          }
        
          if ((millis() - lastDebounceTime) > DEBOUNCE_DELAY) {
            // whatever the reading is at, it's been there for longer than the debounce
            // delay, so take it as the actual current state:
        
            // if the button state has changed:
            if (lastSteadyState == HIGH && currentState == LOW){
              Serial.println("The button is pressed");
              boton=1; //here we change the value of the button to select a song to be played
            }
            else if (lastSteadyState == LOW && currentState == HIGH){
              Serial.println("The button is released");
            }
        
            // save the the last steady state
            lastSteadyState = currentState;
          }
        ////***************************
        
        //Serial.println("Boton: default + valor: "+String(boton));
        delay(50);
        if (boton!=0){
          Serial.println("Boton break!");
          break;
        }
          
      }
  }

  //This switch plays a song depending on the random number selected on the button switch above
  switch (song) {
    case 1:   
      Serial.println("SONG= Item found");
      notesItem=sizeof(item)/sizeof(item[0])/2;
      playSong(item, notesItem, tempoItem);
      song = 0;
      break;
      
    case 2:   
      Serial.println("SONG= title screen");
      notesTitle=sizeof(title)/sizeof(title[0])/2;
      playSong(title, notesTitle, tempoTitle);
      song = 0;
      break; 

    case 3:   
      Serial.println("SONG= Secret");
      notesSecret=sizeof(secret)/sizeof(secret[0])/2;
      playSong(secret, notesSecret, tempoSecret);
      song = 0;
      break; 

    case 4:   
      Serial.println("SONG= Dungeon");
      notesDungeon=sizeof(dungeon)/sizeof(dungeon[0])/2;
      playSong(dungeon, notesDungeon, tempoDungeon);
      song = 0;
      break; 

    case 5:   
      Serial.println("SONG= Sword");
      notesSword=sizeof(sword)/sizeof(sword[0])/2;
      playSong(sword, notesSword, tempoSword);
      song = 0;
      break; 
      
    default:
      Serial.println("No Song"); //no song selected when the button is not pressed
      break;
  }

}


//Function to play any song.
//we need to input the song, the amount of notes and the tempo for each song

void playSong(int* melody, int notes, int tempo){ 
 // Serial.println("melody: "+String(sizeof(melody)));
  int wholenote = (60000 * 4) / tempo;
  int divider = 0, noteDuration = 0;
  
  for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) {
  
      // calculates the duration of each note
      divider = melody[thisNote + 1];
      if (divider > 0) {
        // regular note, just proceed
        noteDuration = (wholenote) / divider;
      } else if (divider < 0) {
        // dotted notes are represented with negative durations!!
        noteDuration = (wholenote) / abs(divider);
        noteDuration *= 1.5; // increases the duration in half for dotted notes
      }
  
      // we only play the note for 90% of the duration, leaving 10% as a pause
      tone(buzzer, melody[thisNote], noteDuration*0.9);
  
      // Wait for the specief duration before playing the next note.
      delay(noteDuration);
      
      // stop the waveform generation before the next note.
      noTone(buzzer);
      
    }
}



void colorWipe(uint32_t color, int wait) {
  Serial.println("el color es "+String(color));
  //if(color==0){
//    bandera=1;
    //}
  for(int i=0; i<strip.numPixels(); i++) { // For each pixel in strip...
    strip.setPixelColor(i, color);         //  Set pixel's color (in RAM)
    

    strip.show();                          //  Update strip to match
    delay(wait);                           //  Pause for a moment
  }
}
