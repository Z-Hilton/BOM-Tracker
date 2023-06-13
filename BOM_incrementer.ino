#define SPLASH_SCREEN_FRAME_COUNT 1
#define SPLASH_SCREEN_WIDTH 32
#define SPLASH_SCREEN_HEIGHT 63

const unsigned char splashScreen [] PROGMEM = {
0x00, 0x80, 0x80, 0x80, 0x80, 0xC0, 0x40, 0xA0, 0xA0, 0xA0, 0x90, 0x90, 0x50, 0x48, 0x48, 0x28,
0x24, 0xA4, 0xA2, 0xB2, 0x92, 0x91, 0x9F, 0x88, 0x78, 0x40, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00,
0xFF, 0x03, 0xFE, 0x06, 0x05, 0x05, 0x07, 0x07, 0x06, 0x06, 0x06, 0x06, 0x05, 0x05, 0x05, 0x05,
0x05, 0x05, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x07, 0xFC, 0x00, 0x00, 0x00, 0x00,
0xFF, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10,
0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x00,
0xFF, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x89, 0x89, 0x89, 0x76, 0x00, 0x7E, 0xC1, 0x81,
0xC1, 0x7E, 0x00, 0xFF, 0x03, 0x0E, 0x03, 0xFF, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x00,
0xFF, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04,
0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x00,
0xFF, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x00,
0x01, 0x02, 0x07, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04,
0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x07, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
};




#include <Bounce2.h>
#include <string.h>
#include <GyverOLED.h>

#define TOTAL_CHAPTERS 239.0
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define HOLD_TIME 1000
#define SHOW_PROGRESS 0
#define SHOW_TIMES 1
#define SHOW_STATS 2
//Initialize LCD by creating an OLED  object
GyverOLED<SSH1106_128x64> oled;


//define buttons and LED
const int incrementDecrementButtonPin = 8;
const int startPauseStopButtonPin = 7; // will be startPauseStopPin
const int statButtonPin = 9; // will be stat pin
const int ledPin = 10;
Bounce incrementDecrementButton = Bounce();
Bounce startPauseStopButton = Bounce();
Bounce statButton = Bounce();

//Book of Mormon constants and variables
const int numBooks = 15; // number of Books in th Book of Mormon
const int numChapters[] = {0, 22, 33, 7, 1, 1, 1, 1, 29, 63, 16, 30, 1, 9, 15, 10};
int currentBook = 1;    // the current book (starts with 1st Nephi)
int currentChapter = 1; // the current chapter (it starts with 1)
double portion = 0; // the percentage of the way through the Book of Mormon you are
double avg = 0;
// Define inc/dec timer variables
int holdCnt = 0;
bool incDecPressed = false;

//Define Timer State variables
bool timerRunning = false;
bool timerPaused = false;
bool flashLedFlag = false;  // Flag to trigger flashing mechanism
bool on = true;             // Flag to remember the current state of the LED
double startTime = 0.0;
double pauseTime = 0.0;
double elapsedTime = 0.0;
double weeklyTimes[] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
int timesIndex = 0;
int flashCnt = 0;
int mode = 0;

void setup() {
  // Set the pin modes
  pinMode(incrementDecrementButtonPin, INPUT_PULLUP);
  pinMode(startPauseStopButtonPin, INPUT_PULLUP);
  pinMode(statButtonPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);
  // start the serial communication
  Serial.begin(9600); 
  // attach the Bounce objects to the button pins and set debounce intervals
  incrementDecrementButton.attach(incrementDecrementButtonPin); 
  incrementDecrementButton.interval(20); 
  startPauseStopButton.attach(startPauseStopButtonPin);
  startPauseStopButton.interval(20);
  statButton.attach(statButtonPin);
  statButton.interval(20);
  //Initialize the OLED display
  oled.init();
  oled.clear();
  oled.update();
  printUI();
  printChapter();
  // oled.setCursorXY(28,26);
  // oled.print("Hello World!");
  // oled.rect(0,0,127,63,OLED_STROKE);
  // oled.update();
}

void loop() {
  incrementDecrementButton.update(); // update the bounce object for the inc. button
  startPauseStopButton.update();// etc.
  statButton.update();

  if (incrementDecrementButton.read() == LOW && incrementDecrementButton.duration() >= HOLD_TIME) {
    if (currentChapter == 1) { // if we are at the first chapter of any given book,
      currentBook = ((currentBook - 2 + numBooks) % numBooks) + 1; //move to the previous book (this line was hard)
      currentChapter = numChapters[currentBook]; //start at the last chapter 
    } else {
      currentChapter--; //decrement the current chapter
    }
    printChapter();
  }
  else if (incrementDecrementButton.fell()) {// if the increment button was pressed
    if (currentChapter == numChapters[currentBook]) {// if we are on the last chapter of a given book,
      currentBook = (currentBook % numBooks) + 1; // move on to the next book
      currentChapter = 1; // start at the first chapter of the book
    } else {
      currentChapter++; // increment the current chapter
    }
    printChapter();
  }

  //state machine for the timer

  // Check if stop button is pressed
  if (startPauseStopButton.read() == LOW && startPauseStopButton.duration() >= HOLD_TIME && timerRunning) {
    // Stop timer
    timerRunning = false;
    timerPaused = false;
    flashLedFlag = false;
    digitalWrite(ledPin, LOW);
    Serial.print("Elapsed time: ");

    printTime(elapsedTime/1000.0,2,false,false);
    pushElapsedTime();
    //delay(3000);
    //printChapter();
    
    elapsedTime = 0.0;
  }
  // Check if the start/pause button is pressed
  else if (startPauseStopButton.fell()) {
    if (!timerRunning) {
      // Start the timer
      timerRunning = true;
      startTime = millis();
      digitalWrite(ledPin, HIGH);
    } else if (timerPaused) {
      // Resume the timer
      timerPaused = false;
      flashLedFlag = false;
      startTime += millis() - pauseTime;
      digitalWrite(ledPin, HIGH);
    } else {
      // Pause Timer
      timerPaused = true;
      pauseTime = millis();
      flashLedFlag = true;
    }
  }

  //Update the elapsed time if timer is running
  if (timerRunning && !timerPaused) {
    elapsedTime = millis() - startTime;
  }
  // Flash the LED
  if (flashLedFlag) {
    flashCnt++;
    if (flashCnt >= 10000) {
      if(on) {
        digitalWrite(ledPin, LOW);
        on = false;
        flashCnt = 0;
      } else {
        digitalWrite(ledPin, HIGH);
        on = true;
        flashCnt = 0;
      }
    }
  }

  if (statButton.fell()) {
    switch (mode) {
      case SHOW_PROGRESS:
        printStats(); // if we are in progress mode, pressing the stat button will show us stats
      break;
      case SHOW_TIMES:
        printChapter(); // if we are in showTimes mode, pressing the stat button will go to the chapter progress
      break;
      case SHOW_STATS:
        printChapter(); // if we are in showStats mode, pressing the stat button will go back to chapter progress 
      break;
    }
  }

  //delay(10); //small delay to prevent bouncing
}
void printChapter() {
  mode = SHOW_PROGRESS;
  Serial.print("Ch ");
  Serial.print(currentChapter);
  Serial.print(" of ");
  Serial.println(bookName(currentBook));

  //clean slate with my BOM UI
  oled.clear();
  printUI();

  // chapter to oled
  oled.setScale(1);
  //We gotta fit Words of Mormon in there so here is the exception case
  if(currentBook == 7) {
    oled.setCursorXY(37, 10);
    oled.println(bookName(currentBook));
  } else {
    oled.setCursorXY(55, 10);
    oled.println(bookName(currentBook));
  }
  oled.setCursorXY(55, 25);
  oled.setScale(2);
  oled.print("Ch ");
  oled.print(currentChapter);

  // progress bar
  double sum = 0.0;
  for (int i = 0; i < currentBook; i++) {
    sum += numChapters[i];
  }
  sum += currentChapter;
  portion = sum/TOTAL_CHAPTERS;
  int progress = portion * SCREEN_WIDTH;
  oled.rect(0,54,127,60,OLED_STROKE);
  oled.rect(0,55,progress,59,OLED_FILL);
  oled.update();
}

void printTime( double val, byte precision, bool weeklyFlag, bool statFlag){
  // prints val with number of decimal places determine by precision
  // precision is a number from 0 to 6 indicating the desired decimial places
  // example: printDouble( 3.1415, 2); // prints 3.14 (two decimal places)
  mode = SHOW_TIMES;
  int minutes = 0;
  while(val > 60.0) {
    minutes++;
    val -= 60;
  }
  Serial.print(minutes);
  Serial.print(" min ");
  Serial.print(int(val));  //prints the int part
  //print to the OLED
  oled.clear();
  oled.setScale(1);
  oled.setCursorXY(10, 0);
  if(weeklyFlag && !statFlag) oled.print("Weekly Average:");
  else if(weeklyFlag && statFlag) oled.print("Last Week's Avg:");
  else oled.print("Reading Time:");
  oled.setScale(2);
  oled.setCursorXY(15,15);
  oled.print(minutes);
  oled.print("    min");
  oled.setCursorXY(15, 35);
  oled.print(int(val));

  if( precision > 0) {
    Serial.print("."); // print the decimal point
    oled.print("."); 
    unsigned long frac;
    unsigned long mult = 1;
    byte padding = precision -1;
    while(precision--)
       mult *=10;
       
    if(val >= 0)
      frac = (val - int(val)) * mult;
    else
      frac = (int(val)- val ) * mult;
    unsigned long frac1 = frac;
    while( frac1 /= 10 )
      padding--;
    while(  padding--) {
      Serial.print("0");
      oled.print("0");

    }
    Serial.print(frac,DEC);
    Serial.print(" sec\n");
    oled.print(frac,DEC);
    oled.print(" sec");
  }
  oled.update();
}

void pushElapsedTime() {
  weeklyTimes[timesIndex] = elapsedTime / 1000.0;
  if (timesIndex == 6) {
    double sum = 0.0;
    for (int i = 0; i < 7; i++) {
      sum += weeklyTimes[i];
      weeklyTimes[i] = 0;
    }
    avg = sum/7.0;
    Serial.print("Your weekly avg: ");

    oled.setScale(1);
    oled.setCursorXY(10, 10);
    printTime(avg,2,true,false);
    timesIndex = 0;
  } else {
    timesIndex++;
  }
}

String bookName(int book) {
  switch (book) {
    case 1: return "1st Nephi";
    case 2: return "2nd Nephi";
    case 3: return "Jacob";
    case 4: return "Enos";
    case 5: return "Jarom";
    case 6: return "Omni";
    case 7: return "Words of Mormon";
    case 8: return "Mosiah";
    case 9: return "Alma";
    case 10: return "Helaman";
    case 11: return "3rd Nephi";
    case 12: return "4th Nephi";
    case 13: return "Mormon";
    case 14: return "Ether";
    case 15: return "Moroni";
    default: return "";
  }
}
void printUI() {
  //oled.home();
  oled.drawBitmap(1,1,splashScreen,SPLASH_SCREEN_WIDTH,SPLASH_SCREEN_HEIGHT,0,0);
  //oled.update();
}
void printStats() {
  mode = SHOW_STATS;
  oled.clear();
  oled.setScale(1);
  oled.setCursorXY(20, 10);
  oled.print("Progress: ");
  oled.print(portion*100);
  oled.print("%");
  oled.update();
  delay(2000);
  //printTime(avg,2,true,true);
}
