// Remote sketch

// Purpose: Remote for Grandmother to better control TV with simple controls to reduce errors

// Constant Variables
const int ledPin   = 13;
const int dataSize = 9600;

// ints to determine digital pin state
int volUpState     = 0;
int volDownState   = 0;

// bool to determine if a button is being held
bool buttonHeld    = false;

// Enum for all button types and pins they use
enum ButtonType {
  VolumeUp   = 2,
  VolumeDown = 3
};

// Setup function
void setup() {
  
  // Set up serial monitor for debugging
  Serial.begin(dataSize);
  
  // Pin to light on-board LED
  pinMode(ledPin, OUTPUT);

  // Button pins read digitally (May need to change to analog based on button amount later)
  pinMode(VolumeUp, INPUT);
  pinMode(VolumeDown, INPUT);
}

// Main program loop
void loop() {
  volUpState = digitalRead(VolumeUp);
  volDownState = digitalRead(VolumeDown);
  
  if (volUpState == HIGH) {
    digitalWrite(ledPin, HIGH);

    if (buttonHeld == false) {
      buttonPressed(VolumeUp);
    }
  }
  else if (volDownState == HIGH) {
    digitalWrite(ledPin, HIGH);
    
    if (buttonHeld == false) {
      buttonPressed(VolumeDown);
    }
  }
  else {
    digitalWrite(ledPin, LOW);
    buttonHeld = false;
  } 
}

// Process all button presses
void buttonPressed(ButtonType button) {
  switch(button) {
    
    case VolumeDown:
      volumePressed(false);
      break;

    case VolumeUp:
      volumePressed(true);
      break;

    default:
      // Invalid button press
      break;
  }
}

// Process volume button presses
void volumePressed(bool dir) {
  String volType = dir ? "Up" : "Down";
  String volumeMsg = "Volume " + volType + " Pressed!\n";
  Serial.write(volumeMsg.c_str());
  buttonHeld = true;
}
