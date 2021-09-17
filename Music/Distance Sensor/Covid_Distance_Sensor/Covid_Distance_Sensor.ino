// available music notes
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

#define WHOLE 2000
#define HALF 1000
#define QUARTER 500
#define EIGTH 250
#define SIXTEENTH 125
#define THREE_SIXTEENTHS 375

class Note {
  public:
    int pitch;
    int duration;
    void play() {
      if(duration == 0) {
        return;
      }
      tone(8, pitch, duration); 
      delay(duration);
    }
    Note(int p, int d) {
      pitch = p;
      duration = d;
    }
};

// returns object distance in centimeters
// don't worry about understanding this piece of code
// it's specific to the sensor and you just need to use this function
int readUltrasonicDistance(int triggerPin, int echoPin)
{
  pinMode(triggerPin, OUTPUT);  // Clear the trigger
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  // Sets the trigger pin to HIGH state for 10 microseconds
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  pinMode(echoPin, INPUT);
  // Reads the echo pin, and returns the sound wave travel time in microseconds
  // then converts it into centimeters
  return pulseIn(echoPin, HIGH) * 0.01723;
}

void playSong(Note **song, int songLength) {
  for(int i = 0; i < songLength; i++){
    (*song[i]).play();
  }
}

const int songLength = 100;
Note **song1 = (Note**)malloc(songLength * sizeof(Note*));
Note **song2 = (Note**)malloc(songLength * sizeof(Note*));
int cm = 0;
int inches = 0;
int closeThreshold = 10;
int mediumThreshold = 30;

void setup() {
  Note *noNote = new Note(0, 0);
  for(int i = 0; i < songLength; i++){
    song1[i] = noNote;
    song2[i] = noNote;
  }

  int idx = 0;
  song1[idx++] = new Note(NOTE_G3, QUARTER);
  song1[idx++] = new Note(NOTE_G3, QUARTER);
  song1[idx++] = new Note(NOTE_G3, QUARTER);
  song1[idx++] = new Note(NOTE_DS2, THREE_SIXTEENTHS);
  song1[idx++] = new Note(NOTE_AS3, SIXTEENTH);
  
  song1[idx++] = new Note(NOTE_G3, QUARTER);
  song1[idx++] = new Note(NOTE_DS2, THREE_SIXTEENTHS);
  song1[idx++] = new Note(NOTE_AS3, SIXTEENTH);
  song1[idx++] = new Note(NOTE_G3, HALF);
  
  song1[idx++] = new Note(NOTE_D4, QUARTER);
  song1[idx++] = new Note(NOTE_D4, QUARTER);
  song1[idx++] = new Note(NOTE_D4, QUARTER);
  song1[idx++] = new Note(NOTE_DS4, THREE_SIXTEENTHS);
  song1[idx++] = new Note(NOTE_AS3, SIXTEENTH);
  
  song1[idx++] = new Note(NOTE_FS2, QUARTER);
  song1[idx++] = new Note(NOTE_DS2, THREE_SIXTEENTHS);
  song1[idx++] = new Note(NOTE_AS3, SIXTEENTH);
  song1[idx++] = new Note(NOTE_G3, HALF);

  idx = 0;
  song2[idx++] = new Note(NOTE_C4, SIXTEENTH);
  song2[idx++] = new Note(NOTE_B3, SIXTEENTH);
  song2[idx++] = new Note(NOTE_A3, SIXTEENTH);
  song2[idx++] = new Note(NOTE_G3, SIXTEENTH);
  song2[idx++] = new Note(NOTE_F3, SIXTEENTH);
  song2[idx++] = new Note(NOTE_E3, SIXTEENTH);
  song2[idx++] = new Note(NOTE_D3, SIXTEENTH);
  song2[idx++] = new Note(NOTE_C3, SIXTEENTH);
}

void loop() {
  // measure the ping time in cm
  cm = readUltrasonicDistance(12, 11);
  // convert to inches by dividing by 2.54
  inches = (cm / 2.54);
  Serial.print(cm);
  Serial.print("cm, ");
  Serial.print(inches);
  Serial.println("in");

  delay(500); // Wait for 500 millisecond(s)
  
  // TODO: changes the value ranges and messages per step #7
  if (inches >= 0 && inches <= closeThreshold){
    Serial.println("too close");
    playSong(song1, songLength);
  } else if (inches > closeThreshold && inches <= mediumThreshold) {
    Serial.println("middle");
    playSong(song2, songLength);
  } else {
    Serial.println("far");
  }
}