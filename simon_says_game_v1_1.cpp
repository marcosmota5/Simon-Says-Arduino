// COMP 1045 Group Assignment - Simon Says Game
// Group: 5
// Student Id and Names: Marcos, Lucas, Sergio, Vinicius, Natália
// Created on: 2024-02-23
// Version v1.1

// Include the NeoPixel library 
#include <Adafruit_NeoPixel.h>

// Include the Liquid Cristal library
#include <LiquidCrystal.h>

// Define the NeoPixel pin and pixel count
#define PIXEL_PIN A3
#define PIXEL_COUNT 4

// Define the notes for the buzzer
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_G3  196
#define NOTE_F3  175
#define NOTE_A4  440
#define NOTE_B4  494
#define NOTE_C4  262
#define NOTE_D4  294
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_G4  392
#define NOTE_E5  659
#define NOTE_C5  523
#define NOTE_D5  587
#define NOTE_G5  784

// Variables declaration

// Declare the NeoPixel object passing the pixel count, pin and common properties
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(PIXEL_COUNT, PIXEL_PIN, NEO_GRB + NEO_KHZ800);

// Declare the pins that will be used for the LCD display
const int rs = 13, en = 12, d4 = 11, d5 = 10, d6 = 9, d7 = 8;

// Declare the LCD library by adding the used pins
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// Declare the buttons array that will be used to play the game
const int buttons[] = {4, 5, 6, 7};

// Declare the button to start or reset the game
const int buttonStart = 3;

// Declare the pin for used for the buzzer to play the sounds
const int buzzer = 2;

// Declare the pin for the potentiometers that control the difficulty and color pattern
const int potDifficulty = A1;
const int potSpeed = A4;
const int potColors = A2;

// Declare the current delay value and a new value to compare and change when it's needed
int delayValue = 0;
int newDelayValue = 0;

// Game console startup melody
const int arduinoStartNotes[] = {NOTE_E4, NOTE_G4, NOTE_E5, NOTE_C5, NOTE_D5, NOTE_G5};
const int arduinoStartDurations[] = {10, 10, 10, 10, 10, 4};

// Declare the notes and the duration that is used for each button/light
const int notes[] = {NOTE_G3, NOTE_A3, NOTE_C4, NOTE_D4};
const int notesDuration = 8;

// Declare the notes and durations arrays for the start sound
const int startSoundNotes[] = {NOTE_C4, NOTE_D4, NOTE_E4, NOTE_F4, NOTE_G4, NOTE_A4, NOTE_B4, NOTE_C5};
const int startSoundDurations[] = {8, 8, 8, 8, 8, 8, 8, 4};

// Declare the notes and durations for the correct answer sound
const int correctSoundNotes[] = {NOTE_C4, NOTE_E4, NOTE_G4, NOTE_C5};
const int correctSoundDurations[] = {8, 8, 8, 4};

// Declare the notes and durations for the game over sound
const int gameOverSoundNotes[] = {NOTE_C4, NOTE_B3, NOTE_AS3, NOTE_A3, NOTE_G3, NOTE_F3};
const int gameOverSoundDurations[] = {8, 8, 8, 8, 8, 4};
  
// Declare the notes and durations arrays for the game done sound
const int gameDoneNotes[] = {NOTE_G4, NOTE_E4, NOTE_G4, NOTE_C5, NOTE_D5, NOTE_E5, NOTE_G5};
const int gameDoneNotesDurations[] = {8, 8, 8, 8, 8, 8, 2};

// Declare the RGB colors of each light/button
int rgbColor1[] = {0, 255, 0};
int rgbColor2[] = {255, 0, 0};
int rgbColor3[] = {255, 255, 0};
int rgbColor4[] = {0, 0, 255};

// Declare the variable to store the current game state.  State 1 = Setup Mode, State 2 = Game running
int gameState = 1;

// Declare the variable to store how many seconds passed until the user clicked on a button
int secondsPassed = 0;

// Declare the variable to store the current score
int score = 0;

// Declare the variable to specify if the start sound should be played
bool shouldDisplayStartMessage = true;

// Declare the total levels that the game can have
const int totalLevels = 64;

// Declare the sequence array that will store the full random sequence of notes
int sequence[totalLevels + 1];

// Declare the max level variable that will be used to get how many levels the game will have based on the selected difficulty
int maxLevel = 10;

// Declare the current difficulty value and a new value to compare and change when it's needed
int difficultyPotValue = 0;
int newDifficultyPotValue = 0;

// Declare the variable to store the current position of the game
int currentPosition = 0;
 
// Variable to store the time 
unsigned long secondsSinceStart;

// Create a custom symbol for when the game is playing the sequence
byte playSymbol[8] = {
  0b00000,
  0b00100,
  0b00110,
  0b00111,
  0b00110,
  0b00100,
  0b00000,
  0b00000
};

// Create a custom symbol for when the game is waiting for the user to input their sequence
byte hourglassSymbol[8] = {
  0b11111,
  0b01110,
  0b00100,
  0b01110,
  0b11111,
  0b00000,
  0b00000,
  0b00000
};

// Create a custom symbol for when the user gets a correct answer
byte checkMark[8] = {
  0b00000,
  0b00001,
  0b00010,
  0b10100,
  0b01100,
  0b00100,
  0b00000,
  0b00000
};

// Function that runs one time
void setup()
{
  // Enable the Arduino to send data to the Serial monitor
  Serial.begin(9600);

  // Initialize the LCD
  lcd.begin(16, 2);
  
  // Setup the true random seed using a free analog pin
  randomSeed(analogRead(A0));
  
  // Call the function that sets the random sequence
  setRandomSequence();
  
  // Initialize the NeoPixels components
  pixels.begin();
  
  // Configure the button pins
  for (int i = 0; i < 4; i++)
  {
    pinMode(buttons[i], INPUT);
  }
  
  // Configure the potentiometers and buzzer pins
  pinMode(potDifficulty, INPUT);
  pinMode(potSpeed, INPUT);
  pinMode(potColors, INPUT);
  pinMode(buzzer, OUTPUT);
 
  // Attach the setGameState function to the start/reset button
  attachInterrupt(digitalPinToInterrupt(buttonStart), setGameState, RISING);
  
  // Print the game information and a starting message
  lcd.print("Simon Says v1.1");
  lcd.setCursor(0, 1);
  lcd.print("Starting...");
  
  // Delay for some seconds so the user is able to see the message
  delay(2000);
  
  // Loop through each note and play it
  for (int thisNote = 0; thisNote < 8; thisNote++) 
  {
    playNote(arduinoStartNotes[thisNote], arduinoStartDurations[thisNote]);
  }

  // Clear the cursor and print the Setup Mode text
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("-- Setup Mode --");

  // Create the custom characters for the play and waiting symbols
  lcd.createChar(0, playSymbol);
  lcd.createChar(1, hourglassSymbol);
  lcd.createChar(2, checkMark);
}

// Function that runs indefinetly
void loop()
{
  // If the game state is one, that means, in the Setup Mode, runs the code and return until the mode is changed
  if (gameState == 1)
  {
    // Get the new delay value by reading the speed potentiometer and mapping it so
    // its value is between 100 and 700
    newDelayValue = map(analogRead(potSpeed), 0, 1023, 700, 100);
    
    // If the new delay value is different than the old one, set the delay as the new one
    if (newDelayValue != delayValue)
    {
      delayValue = newDelayValue;
    }
    
    // Get the new max level by reading the difficulty potentiometer and mapping it so
    // its value is between 100 and 700
    difficultyPotValue = map(analogRead(potDifficulty), 0, 1023, 700, 100);
 
    // If the new max level is different than the old one, set the max level as the new one and print the diffculty name
    if (newDifficultyPotValue != difficultyPotValue)
    {
      getAndPrintDifficulty();
    }
    
    // Call the function that gets the selected colors from the potentiometers
    getPotentiometersColors();

    // Turn on all lights for the configuration mode
    turnOnAllPixels();
    
    // Return so the game doesn't run until the mode is changed
	  return;
  }
  
  // Check if the start message should be displayed and, if so, display it
  if (shouldDisplayStartMessage)
  {
    displayStartMessage();
  }
  
  // Delay some seconds before showing the sequence
  delay(1000);  
  
  // Show the current sequence to the user
  showSequence();
  
  // Gets the time passed using the function that get the miliseconds since the simulation started
  int timePassed = millis() / 1000;
  
  // Call the function that checks the user inputed sequence and, if it was correct,
  // show the correct options, otherwise, displays the game over message
  if(checkSequence())
  {

    // If the current position is greater than 0, meaning it's not the first run, play the correct sound and calculate
    // the seconds passed
    if (currentPosition > 0)
    {
      displayCorrectMessage();
      
      // Calculate how many seconds passed by getting again the miliseconds since the simulation started
      // and subtracting the one before the while started
      secondsPassed = (millis() / 1000) - timePassed;

    }
     
    // Clear the LCD and show the level and score
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Level: ");
    lcd.setCursor(7, 0);
    lcd.print(currentPosition + 1);

    lcd.setCursor(0, 1);
    calculateScore();
    lcd.print("Score: ");
    lcd.setCursor(7, 1);
    lcd.print(score);
     
    // Check if the current position is the last one and, if so, display the game done message and reset the current position
    // otherwise, increase the current position
    if (currentPosition == maxLevel)
    {
      displayGameDoneMessage();
      currentPosition = 0;
    }
    else
    {
      currentPosition++;
    }
  }
  else
  {
    displayGameOver();
  }
  
  // Delay the difficulty value
  delay(delayValue);
}

// Function that prints the difficulty name depending on the delay value
void getAndPrintDifficulty()
{
  // Set the cursor to the first column and second row
  lcd.setCursor(0, 1);
  
  if(difficultyPotValue <= 100)
  {
    maxLevel = 20;
    lcd.print("Dif.: Insane    ");
  }
  else if(difficultyPotValue <= 200)
  {
    maxLevel = 14;
    lcd.print("Dif.: Very Hard ");
  }
  else if(difficultyPotValue <= 300)
  {
    maxLevel = 10;
    lcd.print("Dif.: Hard      ");
  }
  else if(difficultyPotValue <= 400)
  {
    maxLevel = 8;
    lcd.print("Dif.: Normal    ");
  }
  else if(difficultyPotValue <= 500)
  {
    maxLevel = 5;
    lcd.print("Dif.: Easy      ");
  }
  else if(difficultyPotValue <= 600)
  {
    maxLevel = 4;
    lcd.print("Dif.: Very Easy ");
  }
  else
  {
    maxLevel = 3;
    lcd.print("Dif.: Baby      ");
  }
}

// Function that displays the start message and sound
void displayStartMessage()
{
  // Check if the message should be displayed and, if not, return
  if (!shouldDisplayStartMessage)
  {
    return;
  }
  
  // Turn off all pixels to let the user knows that it's going to start
  turnOffAllPixels();

  // Clear the LCD and print the message
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Get ready in");
  lcd.setCursor(0, 1);
  lcd.print("3, 2, 1...");
  
  // Set the variable that tells the function to display to false in order to
  // avoid the start message displaying multiple times
  shouldDisplayStartMessage = false;
  
  // Loop through each note and play it
  for (int thisNote = 0; thisNote < 8; thisNote++) 
  {
    playNote(startSoundNotes[thisNote], startSoundDurations[thisNote]);
  }
  
  // Clear the LCD again
  lcd.clear();
}

// Function that displays the correct message and sound
void displayCorrectMessage()
{
  // Display the waiting custom icon
  lcd.setCursor(15, 0);
  lcd.write(byte(2));

  // Loop through each note and play it
  for (int thisNote = 0; thisNote < 4; thisNote++) 
  {
    playNote(correctSoundNotes[thisNote], correctSoundDurations[thisNote]);
  }
}

// Function that displays the game over message and sound
void displayGameOver()
{
  // Clear the LCD and print the message
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("-- Game Over -- ");
  lcd.setCursor(0, 1);
  lcd.print("Your Score: ");
  lcd.setCursor(12, 1);
  lcd.print(score);
 
  // Loop through each note and play it
  for (int thisNote = 0; thisNote < 6; thisNote++) 
  {
    playNote(gameOverSoundNotes[thisNote], gameOverSoundDurations[thisNote]);
  }
  
  // Reset the current position
  currentPosition = 0;
  
  // Call the function that sets a new random sequence
  setRandomSequence();
}

// Function that displays the game done message
void displayGameDoneMessage()
{
  // Clear the LCD and print the message
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("-- Game Done -- ");
  lcd.setCursor(0, 1);
  lcd.print("Your Score: ");
  lcd.setCursor(12, 1);
  lcd.print(score);

  // Loop through each note and play it
  for (int thisNote = 0; thisNote < 7; thisNote++) 
  {
    playNote(gameDoneNotes[thisNote], gameDoneNotesDurations[thisNote]);
  }

  // Make the lights blink to simulate a light show
  turnOnAllPixels();
  delay(100);
  turnOffAllPixels();
  delay(100);

  turnOnAllPixels();
  delay(100);
  turnOffAllPixels();
  delay(100);

  turnOnAllPixels();
  delay(100);
  turnOffAllPixels();
  delay(100);

  turnOffAllPixels();
  
  // Call the function that sets a new random sequence
  setRandomSequence();
}

// Function that plays a given note by the given duration
// Paramaters:
// note: int value representing the note that should be played
// duration: int value representing the duration of the note
void playNote(int note, int duration)
{
    // Calculate the note duration, take one second divided by the note type
    // e.g., quarter note = 1000 / 4, eighth note = 1000/8, etc
    int noteDuration = 1000 / duration;

    // Play the note for the calculated duration
    tone(buzzer, note, noteDuration);

    // Pause between notes for a duration of 1/20 of the note's duration
    int pauseBetweenNotes = noteDuration * 1.20;
    delay(pauseBetweenNotes);

    // Stop the tone playing on the next loop iteration.
    noTone(8);
}

// Function that shows the sequence and turn the pixel and sound
void showSequence()
{
  // Display the waiting custom icon
  lcd.setCursor(15, 0);
  lcd.write(byte(0));
  
  // Present the sequence until the current position
  for (int i = 0; i < currentPosition; i++)
  {
    turnOnPixelAndSound(sequence[i]);
  }
}

// Function that calculates the score
void calculateScore() 
{
  // If the current position is equal to 0, set the score to 0 and return
  if (currentPosition == 0)
  {
    score = 0;
    return;
  }

  // Base score for a correct answer
  int baseScore;
  
  // Check the delay value and set the base score accordingly
  if(difficultyPotValue <= 100)
  {
    baseScore = 175;
  }
  else if(difficultyPotValue <= 200)
  {
    baseScore = 150;
  }
  else if(difficultyPotValue <= 300)
  {
    baseScore = 125;
  }
  else if(difficultyPotValue <= 400)
  {
    baseScore = 100;
  }
  else if(difficultyPotValue <= 500)
  {
    baseScore = 75;
  }
  else if(difficultyPotValue <= 600)
  {
    baseScore = 50;
  }
  else
  {
    baseScore = 25;
  }

  // The rate at which the score decreases per second
  int decreaseRate = 5;

  // Calculate the score for this answer
  int answerScore = baseScore - (secondsPassed * decreaseRate);

  // Ensure the score does not fall below 10
  if (answerScore < 10) {
      answerScore = 10;
  }

  // Add the answer score to the total score
  score += answerScore;
}

// Function that checks the sequence of the user
bool checkSequence()
{
  // Display the waiting button
  lcd.setCursor(15, 0);
  lcd.write(byte(1));
  
  // Loop through each position and return false if the pressed position is the wrong one
  for (int i = 0; i < currentPosition; i++)
  {
    // Set the correct button as the one in the sequence
    int correctButton = sequence[i];
    
    // Get the button pressed by calling the function
    int buttonPressed = getButtonPressed();
    
    // Turn the pixel of the button pressed and sound
    turnOnPixelAndSound(buttonPressed);
    
    // If the correct button is different from the one pressed, return false
    if (correctButton != buttonPressed)
    {
      return false;
    }
  }
  
  // As no button pressed was wrong, return true
  return true;
}

// Function that gets the button pressed and return the index of it
int getButtonPressed()
{
  // While that runs indefinetly in order to make the user able to press the desired button and then return it
  while (true)
  {
    // Loop through each button and check if it was pressed, if so, return it
    for (int i = 0; i < 4; i++)
    {
      // Set the button as the one in the position
      int button = buttons[i];

      // Check if the button was pressed and if so, return it
      if (digitalRead(button) == HIGH)
      {
        // Return the button
        return i;
      }
    }

    // Delay in order to have a time to process
    delay(1);
  }
}

// Function that sets the random sequence of buttons
void setRandomSequence()
{
  // Get the sequence with random numbers
  for (int i = 0; i < totalLevels + 1; i++)
  {
    sequence[i] = random(0, 4);
  }
}

// Function that turns the provided pixel id on and also play the specific sound
// Paramaters:
// buttonId: id of the button, pixel and note to be turned on and sound
void turnOnPixelAndSound(int id)
{
  // Turn off all pixels first
  turnOffAllPixels();
  
  // Switch that checks the id and turn the specific pixel on
  switch (id)
  {
    case 0:
      pixels.setPixelColor(0, rgbColor1[0], rgbColor1[1], rgbColor1[2]);
  	  break;
    
    case 1:
      pixels.setPixelColor(1, rgbColor2[0], rgbColor2[1], rgbColor2[2]);
      break;
    
    case 2:
      pixels.setPixelColor(2, rgbColor3[0], rgbColor3[1], rgbColor3[2]);
      break;
    
    case 3:
      pixels.setPixelColor(3, rgbColor4[0], rgbColor4[1], rgbColor4[2]);
      break;
    
    default:
      break;
  }
  
  // Make the buzzer sound the note
  tone(buzzer, notes[id], 1000 / notesDuration);
  
  // Turn on the pixel
  pixels.show();
  
  // Delay the delay value which is related to the difficulty
  delay(delayValue);
  
  // Turn off all pixels
  turnOffAllPixels();

  // Make the buzzer silent 
  noTone(buzzer);
  
  // Delay the delay value which is related to the difficulty
  delay(delayValue);
}

// Function that turns off all pixels
void turnOffAllPixels()
{
  pixels.setPixelColor(0, 0, 0, 0);
  pixels.setPixelColor(1, 0, 0, 0);
  pixels.setPixelColor(2, 0, 0, 0);
  pixels.setPixelColor(3, 0, 0, 0);

  pixels.show();
}

// Function that turns on all pixels
void turnOnAllPixels()
{
   pixels.setPixelColor(0, rgbColor1[0], rgbColor1[1], rgbColor1[2]);
   pixels.setPixelColor(1, rgbColor2[0], rgbColor2[1], rgbColor2[2]);
   pixels.setPixelColor(2, rgbColor3[0], rgbColor3[1], rgbColor3[2]);
   pixels.setPixelColor(3, rgbColor4[0], rgbColor4[1], rgbColor4[2]);

   pixels.show();
}

// Function that gets the potentiometer value and set the RGB colors
void getPotentiometersColors()
{
  int potValue = analogRead(potColors);
  
  if(potValue <= 150)
  {
    rgbColor1[0] = 0; rgbColor1[1] = 255; rgbColor1[2] = 0;
    rgbColor2[0] = 255; rgbColor2[1] = 0; rgbColor2[2] = 0;
    rgbColor3[0] = 255; rgbColor3[1] = 255; rgbColor3[2] = 0;
    rgbColor4[0] = 0; rgbColor4[1] = 0; rgbColor4[2] = 255;
  }
  else if(potValue <= 300)
  {
    rgbColor1[0] = 115; rgbColor1[1] = 51; rgbColor1[2] = 128;
    rgbColor2[0] = 233; rgbColor2[1] = 214; rgbColor2[2] = 107;
    rgbColor3[0] = 127; rgbColor3[1] = 23; rgbColor3[2] = 52;
    rgbColor4[0] = 93; rgbColor4[1] = 164; rgbColor4[2] = 147;
  }
  else if(potValue <= 450)
  {
    rgbColor1[0] = 19; rgbColor1[1] = 10; rgbColor1[2] = 143;
    rgbColor2[0] = 101; rgbColor2[1] = 0; rgbColor2[2] = 11;
    rgbColor3[0] = 206; rgbColor3[1] = 255; rgbColor3[2] = 0;
    rgbColor4[0] = 228; rgbColor4[1] = 0; rgbColor4[2] = 120;
  }
  else if(potValue <= 600)
  {
    rgbColor1[0] = 204; rgbColor1[1] = 160; rgbColor1[2] = 29;
    rgbColor2[0] = 86; rgbColor2[1] = 60; rgbColor2[2] = 92;
    rgbColor3[0] = 74; rgbColor3[1] = 65; rgbColor3[2] = 42;
    rgbColor4[0] = 208; rgbColor4[1] = 240; rgbColor4[2] = 192;
  }
  else if(potValue <= 750)
  {
    rgbColor1[0] = 76; rgbColor1[1] = 40; rgbColor1[2] = 130;
    rgbColor2[0] = 255; rgbColor2[1] = 240; rgbColor2[2] = 245;
    rgbColor3[0] = 108; rgbColor3[1] = 84; rgbColor3[2] = 30;
    rgbColor4[0] = 0; rgbColor4[1] = 15; rgbColor4[2] = 137;
  }
  else if(potValue <= 900)
  {
    rgbColor1[0] = 119; rgbColor1[1] = 136; rgbColor1[2] = 153;
    rgbColor2[0] = 107; rgbColor2[1] = 142; rgbColor2[2] = 35;
    rgbColor3[0] = 181; rgbColor3[1] = 51; rgbColor3[2] = 137;
    rgbColor4[0] = 227; rgbColor4[1] = 168; rgbColor4[2] = 87;
  }
  else
  {
    rgbColor1[0] = 255; rgbColor1[1] = 127; rgbColor1[2] = 0;
    rgbColor2[0] = 75; rgbColor2[1] = 0; rgbColor2[2] = 130;
    rgbColor3[0] = 0; rgbColor3[1] = 255; rgbColor3[2] = 255;
    rgbColor4[0] = 148; rgbColor4[1] = 0; rgbColor4[2] = 11;
  }
}

// Function that sets the game state by checking the current value
void setGameState()
{
  // If the game state is equal to 1, change it to 2, otherwise set it to 1 again and print a message
  if (gameState == 1)
  {
    gameState = 2;
    shouldDisplayStartMessage = true;
  }
  else
  {
    gameState = 1;
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Setup Mode");
    getAndPrintDifficulty();
  }
}
