#include <Adafruit_GFX.h>   // Core graphics library
#include <RGBmatrixPanel.h> // Hardware-specific library
#include <CountUpDownTimer.h> //Countdown Clock Library

/*
    The libraries Adafruit_GFX.h and RGBmatrixPanel.h are used to drive the LEDs on the 32x64 LED matrix.
    The library CountUpDownTimer.h is used to implement a count down timer used to time the matches.
*/

/*
    In order to use the LED panel the code needs to know which pin on the LED panel is mapped to which
    pin on the Arduino. More information about the physical connections can be found at:
    https://learn.adafruit.com/32x16-32x32-rgb-led-matrix/

    The following is a map of panel pins to Arduino pins.
*/

#define OE   9
#define LAT 10
#define CLK 11
#define A   A0
#define B   A1
#define C   A2
#define D   A3

/*
   Here the library RGBmatrixPanel is passed the values of the pins, so the function matrx can be used to draw on the panel.
   This initializes the panel object.
   The "64" passed to the function is indicating that this is for a 32x64 LED panel.
*/

RGBmatrixPanel matrix(A, B, C, D, CLK, LAT, OE, false, 64);

/*
   The following sets some variables to be used for handling physical button presses.
   As of 1.2, there is only one button defined.
   There needs to be a reset button, a "Player 1" button, and a "Player 2" button created.
   Old comment: TODO:define 4 buttons for time up, time down, start/pause time, and reset.

   The first iteration of the additional button presses should be the "Player 1" and
   "Player 2" logic. The idea is to only enable the countdown timer button once both the player
   buttons have been press. One idea would be to detect press state of two buttons, and once both
   hove been pressed, pause and enable the countdown timer button.

   Second interation should be to have a button that resets all button states.

*/

/*
   This is where the variables for the buttons will go.

   StartButtonPin is the button the starts the countdown matchTimer.
   StartButtonState is the state of the button.

   PlayerOneButtonPin is the button for player one to press to indicate ready-to-go.
   PlayerOneStartButtonState is the state of the button.
   PlayerOneReady is a store of the state to keep for looking for button presses once it's pressed

   PlayerTwoButtonPin is the button for player one to press to indicate ready-to-go.
   PlayerTwoButtonState is the state of the button.
   PlayerTwoReady is a store of the state to keep for looking for button presses once it's pressed

   ResetButtonPin is the button for player one to press to indicate ready-to-go.
   ResetButtonState is the state of the button.

*/

const int StartButtonPin = 7; //Sets the constant to the pin number on the Arduino
int StartButtonState = 0; //Sets the button state variable

/*
   ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
     IMPORTANT IMPORTANT IMPORTANT IMPORTANT IMPORTANT IMPORTANT IMPORTANT IMPORTANT IMPORTANT
     -----------------------------------------------------------------------------------------

     THE PINS MUST BE DEFINED HERE. THE VALUES THAT ARE IN NOW ARE ARBITRARY. SET THESE VALUES
     TO THE PIN NUMBERS THAT THE BUTTONS ARE GOING TO USE. (YES, I AM YELLING.)

   ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
*/

const int PlayerOneButtonPin = 2; //Sets the constant to the pin number on the Arduino
int PlayerOneButtonState = 0; //Sets the button state variable
int PlayerOneReady = 0; //Sets false to readiness of player

const int PlayerTwoButtonPin = 3; //Sets the constant to the pin number on the Arduino
int PlayerTwoButtonState = 0; //Sets the button state variable
int PlayerTwoReady = 0; //Sets false to readiness of player

const int ResetButtonPin = 4; //Sets the constant to the pin number on the Arduino
int ResetButtonState = 0; //Sets the button state variable

/*
   The following sets the variables to define the length of the countdown matchTimer.
   These had previously been in setup().
*/
int minute = 03; //Sets the minute variable
int second = 00; //Sets the second variable


/*
   Here the CountUpDownTimer library is passed the value "DOWN", so the countdown
   timer can be implemented.
*/

CountUpDownTimer matchTimer(DOWN);

void setup() {
  /*
     The Arduino needs to be told which pins are going to be used for buttons, so
     the pinMode command it used to tell it that the specified pins will be used as
     input.
  */

  /*
     +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
     NOTE: All of the commented-out code in setup() should be removed
     when the code is tested and working. The only thing that really
     belongs in here is setting the pins, and calling the resetClock()
     function.
     +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  */

  pinMode(StartButtonPin, INPUT);
  pinMode(PlayerOneButtonPin, INPUT);
  pinMode(PlayerTwoButtonPin, INPUT);
  pinMode(ResetButtonPin, INPUT);


  /* Upon startup or reset, the following fills the screen with green and then with black as
     as an indicator that the screen is working.
  */

  /*
      This is from version 1 code. This should be used by the reset button or called upon setup.
      It should be in a function outside of setup.

      matrix.begin();
      matrix.fillRect(0, 0, matrix.width(), matrix.height(), matrix.Color333(0, 7, 0));//fill screen with green
      delay(500);
      matrix.fillScreen(matrix.Color333(0, 0, 0)); //fill screen with black
  */

  /*
     This is from version 1 code. These variables should be declared outside of setup.
     int minute = 03;
     int second = 00;
  */

  /*
     This is from version 1 code. This should be called by the reset button.
     It should be outside of setup.

     matchTimer.SetTimer(0,minute,second);
  */

  /*
     This is from version 1 code. This should be called by the reset button.
     It should be outside of setup.

     matchStart(); //Green with "Match Start" printed on the screen. Countdown clock begins.
  */

  /*
    This is from version 1 code. This should be called by the reset button.
    It should be outside of setup.

    matrix.fillScreen(matrix.Color333(0, 0, 0));//black fill
    matrix.setTextColor(matrix.Color333(0,7,0)); //bright green
    matrix.setCursor(3, 1);
    matrix.setTextSize(2);
  */
  resetClock();
}

void resetClock() {
  //Clear the LED panel to show it has been reset
  matrix.begin();
  matrix.fillRect(0, 0, matrix.width(), matrix.height(), matrix.Color333(0, 7, 0));//fill screen with green
  delay(250);
  matrix.fillScreen(matrix.Color333(0, 0, 0)); //fill screen with black

  //Display message that clock has been reset
  matrix.setCursor(3, 1);
  matrix.setTextSize(2);
  matrix.setTextColor(matrix.Color333(0, 0, 0));
  matrix.fillScreen(matrix.Color333(0, 7, 0));
  matrix.println("CLOCK");
  matrix.setCursor(3, 17);
  matrix.println("RESET");
  delay(500);

  //Clear the LED again
  matrix.begin();
  matrix.fillRect(0, 0, matrix.width(), matrix.height(), matrix.Color333(0, 7, 0));//fill screen with green
  delay(250);
  matrix.fillScreen(matrix.Color333(0, 0, 0)); //fill screen with black

  //Set the time to match time. The default is 3 minutes and 0 seconds from the variables minute and second
  matchTimer.SetTimer(0, minute, second);

  //Call the matchStart function to show that the match is about to begin.
  matchStart(); //Green with "Match Start" printed on the screen. Countdown clock begins.

  //Get the display ready for the countdown clock to be displayed
  matrix.fillScreen(matrix.Color333(0, 0, 0));//black fill
  matrix.setTextColor(matrix.Color333(0, 7, 0)); //bright green
  matrix.setCursor(3, 1);
  matrix.setTextSize(2);

  //Reset the button states
  PlayerOneButtonState = 0;
  PlayerTwoButtonState = 0;
  ResetButtonState = 0;
  StartButtonState = 0;

  //Reset the player ready flags
  PlayerOneReady = 0;
  PlayerTwoReady = 0;

  matchTimer.StartTimer();

}

/*
   The countdown timer has been defined to indicate phases within the countdown
   with colors displayed on the LED panel.

   3:00 minutes, which is the start time, the display will flash green and being the countdown.
   At 1:30 minutes the display flashes yellow and the countdown continues.
   At 0:30 minutes the display flashes red and the countdown continues.
   At 0:05 minutes the display begins flashing red and the countdown continues.
   At 0:00 minutes the display goes solid red.

*/

void setClock() { //NOTE: It's not clear that this function ever gets called.
  //set the time, default is 3 minutes
  //header text
  matrix.setCursor(5, 2);   // start at top left, with one pixel of spacing
  matrix.setTextSize(1);    // size 1 == 8 pixels high
  matrix.setTextColor(matrix.Color333(7, 0, 0)); //bright red
  matrix.println("Countdown");
  matrix.setTextSize(2);
  matrix.setTextColor(matrix.Color333(0, 7, 0));
  matrix.println("0:00");
}

void matchStart() {
  //timer == started --> flash green and begin countdown
  matrix.setCursor(3, 1);
  matrix.setTextSize(2);
  matrix.setTextColor(matrix.Color333(0, 0, 0));
  matrix.fillScreen(matrix.Color333(0, 7, 0));
  matrix.println("MATCH");
  matrix.setCursor(3, 17);
  matrix.println("START");
  delay(500);
  //LED Strip == solid green
}

void countdownClock() { //Prints Countdown in Red and the Time in Green
  matrix.fillScreen(matrix.Color333(0, 0, 0));
  matrix.setCursor(5, 2);   // start at top left, with one pixel of spacing
  matrix.setTextSize(1);    // size 1 == 8 pixels high
  matrix.setTextColor(matrix.Color333(7, 0, 0)); //bright red

  matrix.println("Countdown");

  //countdown clock
  matrix.setCursor(9, 14);
  matrix.setTextSize(2);
  matrix.setTextColor(matrix.Color333(0, 7, 0)); //bright green
  matrix.print(matchTimer.ShowMinutes());
  matrix.print(":");
  matrix.print(matchTimer.ShowSeconds());
  delay(1000);

}



void flashYellow() {
  //time == 1:30 --> flash yellow and continue counting down
  matrix.fillScreen(matrix.Color333(7, 7, 0));
  //matrix.setTextColor(matrix.Color333(0, 0, 0));
  matrix.setCursor(5, 2);   // start at top left, with one pixel of spacing
  matrix.setTextSize(1);    // size 1 == 8 pixels high
  matrix.setTextColor(matrix.Color333(0, 0, 0));
  matrix.println("Countdown");

  //countdown clock
  matrix.setCursor(9, 14);
  matrix.setTextSize(2);
  //matrix.setTextColor(matrix.Color333(0,0,0));
  matrix.print(matchTimer.ShowMinutes());
  matrix.print(":");
  matrix.print(matchTimer.ShowSeconds());
  //LED Strip == solid yellow
}

void flashRed() {
  //time == 0:30 --> flash red and continue counting down
  matrix.fillScreen(matrix.Color333(7, 0, 0));
  //matrix.setTextColor(matrix.Color333(0, 0, 0));
  matrix.setCursor(5, 2);   // start at top left, with one pixel of spacing
  matrix.setTextSize(1);    // size 1 == 8 pixels high
  matrix.setTextColor(matrix.Color333(0, 0, 0));
  matrix.println("Countdown");

  //countdown clock
  matrix.setCursor(9, 14);
  matrix.setTextSize(2);
  //matrix.setTextColor(matrix.Color333(0,0,0));
  matrix.print(matchTimer.ShowMinutes());
  matrix.print(":");
  matrix.print(matchTimer.ShowSeconds());
  //LED Strip == solid Red
}

void lastChance() {
  //time == 0:05 --> flashing red and counting down
  matrix.fillScreen(matrix.Color333(7, 0, 0));
  matrix.setCursor(5, 2);   // start at top left, with one pixel of spacing
  matrix.setTextSize(1);    // size 1 == 8 pixels high
  matrix.setTextColor(matrix.Color333(0, 0, 0));
  matrix.println("Countdown");

  //countdown clock
  matrix.setCursor(9, 14);
  matrix.setTextSize(2);
  matrix.setTextColor(matrix.Color333(0, 0, 0));
  matrix.print(matchTimer.ShowMinutes());
  matrix.print(":");
  matrix.print(matchTimer.ShowSeconds());
  //LED Strip == flash red
}

void matchOver() {
  //time == 0:00 --> solid red
  matrix.setCursor(3, 1);
  matrix.setTextSize(2);
  matrix.setTextColor(matrix.Color333(0, 0, 0));
  matrix.fillScreen(matrix.Color333(7, 0, 0));
  matrix.println("MATCH");
  matrix.setCursor(9, 17);
  matrix.println("OVER");
  delay(1250);
  matrix.fillScreen(matrix.Color333(7, 0, 0));
  matrix.setCursor(3, 1);
  matrix.println("MATCH");
  matrix.setCursor(9, 17);
  matrix.println("OVER");
  delay(1250);
  matrix.fillScreen(matrix.Color333(7, 0, 0));
  matrix.setCursor(3, 1);
  matrix.println("MATCH");
  matrix.setCursor(9, 17);
  matrix.println("OVER");
  delay(5000);
  //LED Strip == solid red

}

void loop() {

  //Get the states of all the buttons except Start button, which is gotten after both players are flagged as ready.
  PlayerOneButtonState = digitalRead(PlayerOneButtonPin);
  PlayerTwoButtonState = digitalRead(PlayerTwoButtonPin);
  ResetButtonState = digitalRead(ResetButtonState);

  /*
     This is the implementation of the four button scheme.

     It first checks to see if the Reset button has been pressed. If it has, it calls resetClock().
     This will clear the LED screen, reset the clock, and reset the current state of all the buttons.

     Then it checks to see if Player One button has been pressed. If it has, it sets a flag to show
     that Player One is ready. This keeps the loop from getting a "LOW" state after the button has
     been pressed once. It does the same for Player Two.

     Ideally, it will write to the screen once a player is flagged as ready. "Ready Player One" and
     "Ready Player Two" respectively, but this will have to be implemented later.

     It then checks to see if Player One and Player Two have both been flagged as ready. If they have
     it checks to see the state of the Start Button. This makes it so the Start Button cannot be read
     unless both players have pressed their ready button.
  */

  if (ResetButtonState == HIGH) {
    resetClock();
  } else {
    if (PlayerOneReady != 1) { //Check to see if player is already flagged as ready.
      if (PlayerOneButtonState == HIGH) { //Check if the button has been pressed.
        PlayerOneReady = 1; //Flag player as ready.
        //Write "Ready Player One" to LED (Write this if there is time.)
      }
    }
    if (PlayerTwoReady != 1) { //Check to see if player is already flagged as ready.
      if (PlayerTwoButtonState == HIGH) { //Check if the button has been pressed.
        PlayerTwoReady = 1; //Flag player as ready.
        //Write "Ready Player Two" to LED (Write this if there is time.)
      }
    }
    /*
       Once both players are flagged as ready, the Start button can be checked. If it is "HIGH"
       the countdown timer can run.
    */
    if (PlayerOneReady == 1 && PlayerTwoReady == 1) { //Check to see that both players are flagged as ready.
      StartButtonState = digitalRead(StartButtonPin); //Get the status of the Start button pin.
      if (StartButtonState == HIGH) { //Check to see if the Start button has been pressed.
        matchTimer.Timer(); //Run the timer.
        //**
        if (matchTimer.TimeHasChanged() ) { // this prevents the time from being constantly shown.
          //**
          if (matchTimer.ShowMinutes() == 1 && matchTimer.ShowSeconds() == 30 or matchTimer.ShowMinutes() == 1 && matchTimer.ShowSeconds() == 29) { //Check to see if time is half over.
            flashYellow(); //Flash yellow twice to alert of the halfway point
          }
          else if (matchTimer.ShowMinutes() == 0 && matchTimer.ShowSeconds() == 30 or matchTimer.ShowMinutes() == 0 && matchTimer.ShowSeconds() == 29) {
            flashRed(); //Flash red when 30 seconds remain
          }
          else if (matchTimer.ShowMinutes() == 0 && matchTimer.ShowSeconds() <= 5) {
            lastChance(); //Flashing red and the word "Countdown" on clock
          }
          else {
            countdownClock();
          }
          if (matchTimer.TimeCheck(0, 0, 0)) { //When time has expired
            matchOver(); //Flashes that the match is over
            matchTimer.StopTimer();
            matrix.fillScreen(matrix.Color333(0, 0, 0)); //Fills the LED with black
          }
        }
      } //This is the end of the checking to see if time has changed.
    } //This is the end of getting the Start Button State.
  } //This is the end of checking the player flags.
} //This is the end of the else after checking the Reset button.
