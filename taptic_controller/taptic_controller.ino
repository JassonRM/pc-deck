  // Constants
const int knockSensor = 0;
const int threshold = 5;
const int knockFadeTime = 50;     // milliseconds we allow a knock to fade before we listen for another one. (Debounce timer.)
const int timeout = 500;

// Variables
int knockSensorValue = 0; 

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);                    
//  Serial.println("Program start.");   
}

void loop() {
  knockSensorValue = analogRead(knockSensor);
  if (threshold < knockSensorValue) {
       delay(knockFadeTime);
       listen();
  }
}

void listen() {
  int knockNumber=1;               // Counter
  int startTime=millis();          // Reference for when this knock started
  int now=millis();
  do {
    // Listen
    knockSensorValue = analogRead(knockSensor);
    if (threshold < knockSensorValue) {
       knockNumber++;
       delay(knockFadeTime);
    }
  
    now=millis();
   
  } while (now - startTime < timeout);

  Serial.println(knockNumber);
}
