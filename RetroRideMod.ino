#include "lcdAndRelays.h"
#include "defsAndInputs.h"

// Arrays to store the start times (in milliseconds) when buttons are pressed.
unsigned long pressStartTimes[8] = {0, 0, 0, 0, 0, 0, 0, 0};

// Array to track the current pressed state (true or false) of each button.
bool pressedStates[8] = {false, false, false, false, false, false, false, false};

// Variables to store the segment data for a four-digit display. Initially set to 0 (all segments off).
uint8_t segments0 = 0;
uint8_t segments1 = 0;
uint8_t segments2 = 0;
uint8_t segments3 = 0;

// Threshold for detecting a long press, defined as 4 seconds.
const unsigned long pressThreshold = 4000;

// Threshold for activating a function after a button press, defined as 250 milliseconds.
const unsigned long pressActivationThreshold = 250;

void checkButton(int inIndex1, int inIndex2, int relayOffset, unsigned long currentTime);
void checkSingleButton(int inIndex, int relay, unsigned long currentTime);
void setCustomCharForIndex(int inIndex);
void clearSegmentDisplay();



/**
   Initializes the system. Sets up I/O pins and clears the LCD display.
   This function should be called once at the start of the program.
*/
void setup() {
  initIO(); // Initialize the I/O pins for inputs and relays
  clearLCD(); // Clear the LCD screen initially
}

  /**
    Main Loop to check the status of window-related inputs and handle them.
    This function should be called repeatedly in the main program loop.
  */
void loop() {

  readINPUTS(); // Update the state of all inputs
  unsigned long currentTime = millis(); // Get the current time in milliseconds

  // Check each pair of inputs and manage the corresponding relays
  checkButton(0, 1, 1, currentTime);
  checkButton(2, 3, 3, currentTime);
  checkButton(4, 5, 5, currentTime);
  checkButton(6, 7, 7, currentTime);
}

/**
   Checks the status of a pair of buttons and manages their corresponding relays.
   @param inIndex1 Index of the first input button.
   @param inIndex2 Index of the second input button.
   @param relayOffset The starting relay number to control based on input state.
   @param currentTime The current time captured from millis() for time-based actions.
*/
void checkButton(int inIndex1, int inIndex2, int relayOffset, unsigned long currentTime) {
  if (inValues[inIndex1] == IO_HIGH && inValues[inIndex2] == IO_HIGH) {
    resetRelay(relayOffset); // Reset the corresponding relay
    resetRelay(relayOffset + 1); // Reset the next relay
    pressedStates[inIndex1] = pressedStates[inIndex2] = false; // Update the pressed state
  } else {
    checkSingleButton(inIndex1, relayOffset, currentTime);
    checkSingleButton(inIndex2, relayOffset + 1, currentTime);
  }
}

/**
   Manages the state of a single button and its corresponding relay.
   @param inIndex Index of the button being checked.
   @param relay The relay associated with this button.
   @param currentTime The current time captured from millis() to manage timing functions.
*/
void checkSingleButton(int inIndex, int relay, unsigned long currentTime) {
  if (inValues[inIndex] == IO_HIGH) {
    if (!pressedStates[inIndex]) {
      pressStartTimes[inIndex] = currentTime; // Record the time when the button was first pressed
      pressedStates[inIndex] = true; // Mark the button as pressed
    } else if (currentTime - pressStartTimes[inIndex] >= pressThreshold) {
      resetRelay(relay); // Reset the relay after a long press
    } else if (currentTime - pressStartTimes[inIndex] >= pressActivationThreshold) {
      setRelay(relay); // Activate the relay shortly after the button is pressed
      setCustomCharForIndex(inIndex); // Update the custom character display based on button index
      TubeDisplay4Bit(); // Refresh the tube display to show new data
    }
  } else {
    if (pressedStates[inIndex]) {
      resetRelay(relay); // Reset the relay when the button is released
      pressedStates[inIndex] = false; // Mark the button as not pressed
      clearSegmentDisplay(); // Clear the segment display data
    }
  }
}

/**
   Function to set custom characters on the display based on the input index.
   @param inIndex Index of the input which determines the custom character setting.
*/
void setCustomCharForIndex(int inIndex) {
  switch (inIndex) {
    // Case statements for each input index setting different custom characters
    case 0: setCustomChar(0, 0, 0, 0, 0, 1, 1, 0); break;
    case 1: setCustomChar(0, 0, 1, 1, 0, 0, 0, 0); break;
    case 2: setCustomChar(1, 0, 0, 0, 0, 1, 1, 0); break;
    case 3: setCustomChar(1, 0, 1, 1, 0, 0, 0, 0); break;
    case 4: setCustomChar(2, 0, 0, 0, 0, 1, 1, 0); break;
    case 5: setCustomChar(2, 0, 1, 1, 0, 0, 0, 0); break;
    case 6: setCustomChar(3, 0, 0, 0, 0, 1, 1, 0); break;
    case 7: setCustomChar(3, 0, 1, 1, 0, 0, 0, 0); break;
    default:
      // Optionally handle unexpected index values
      break;
  }
}

/**
   Clears all segments of the display, typically called when inputs are reset.
*/
void clearSegmentDisplay() {
  for (int i = 0; i < 4; i++)
    setCustomChar(i, 0, 0, 0, 0, 0, 0, 0); // Clear all custom characters
}
