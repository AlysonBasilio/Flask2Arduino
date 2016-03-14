/*
 * Serial Relay Controller
 * 
 * Serial readings were extracted from
 * http://www.arduino.cc/en/Tutorial/SerialEvent
 * 
 * This code swiches pins according to a list of strings.
 */

String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete

//Relay channels
int ch1 = 12;
int ch2 = 11;
int ch3 = 10;
int ch4 = 9;
int array[] = {ch1, ch2, ch3, ch4};

void setup() {
  // Initialize pins
  for (int i = 0; i<4; i++){
   pinMode(array[i], OUTPUT);
  }

  // initialize serial:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  // reserve 200 bytes for the inputString:
  inputString.reserve(200);
}

void switchPin(int pin){
  if (digitalRead(pin)){
    digitalWrite(pin, LOW);
  }
  else {
    digitalWrite(pin, HIGH);
  }
}

void loop() {
  // print the string when a newline arrives:
  if (stringComplete) {
    inputString.trim();
    Serial.println(inputString);

    if (inputString.equalsIgnoreCase("luzes")){
      switchPin(ch1);
    };

    if (inputString.equalsIgnoreCase("cafeteira")){
      switchPin(ch2);
    };

    if (inputString.equalsIgnoreCase("ventilador")){
      switchPin(ch3);
    };

    if (inputString.equalsIgnoreCase("sabre de luz")){
      switchPin(ch4);
    };

    if (inputString.equalsIgnoreCase("todos")){
      for (int i = 0; i<4; i++){
       switchPin(array[i]);
      }
    };

    // clear the string:
    inputString = "";
    stringComplete = false;
  }
}

/*
  SerialEvent occurs whenever a new data comes in the
 hardware serial RX.  This routine is run between each
 time loop() runs, so using delay inside loop can delay
 response.  Multiple bytes of data may be available.
 */
void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if (inChar == '\n') {
      stringComplete = true;
    }
  }
}


