// Speed Detector using dual HC-SR04 sensors
// Pins for first sensor (Sensor A)
const int trigPinA = 9;
const int echoPinA = 10;

// Pins for second sensor (Sensor B)
const int trigPinB = 11;
const int echoPinB = 12;

// Buzzer pin
const int buzzerPin = 13;

// Constants
const float SENSOR_DISTANCE = 1.0; // Distance between sensors in meters
const float MAX_ALLOWED_SPEED = 2.0; // Maximum allowed speed in meters per second (adjust as needed)
const int BUZZER_FREQUENCY = 1000; // Buzzer frequency in Hz (adjust for desired sound)
const unsigned long SENSOR_TIMEOUT = 5000; // Timeout in milliseconds (5 seconds)

// Variables
unsigned long sensorATime = 0;
unsigned long sensorBTime = 0;
bool sensorATriggered = false;
bool sensorBTriggered = false;
bool personDetected = false;
String direction = "";

void setup() {
  // Initialize Serial Monitor
  Serial.begin(9600);
  
  // Configure pins
  pinMode(trigPinA, OUTPUT);
  pinMode(echoPinA, INPUT);
  pinMode(trigPinB, OUTPUT);
  pinMode(echoPinB, INPUT);
  pinMode(buzzerPin, OUTPUT);
  
  Serial.println("Speed Detector System Initialized");
}

void loop() {
  // Get distances from both sensors
  float distanceA = getDistance(trigPinA, echoPinA);
  float distanceB = getDistance(trigPinB, echoPinB);
  
  // Detection threshold (adjust based on corridor width)
  const float DETECTION_THRESHOLD = 100; // cm
  
  // Check for timeout on Sensor A (A to B direction)
  if (sensorATriggered && !personDetected && (millis() - sensorATime > SENSOR_TIMEOUT)) {
    Serial.println("Timeout: Person detected at Sensor A but not at Sensor B within 5 seconds");
    Serial.println("Direction: A to B - Movement not completed");
    sensorATriggered = false;
    personDetected = false;
  }
  
  // Check for timeout on Sensor B (B to A direction)
  if (sensorBTriggered && !personDetected && (millis() - sensorBTime > SENSOR_TIMEOUT)) {
    Serial.println("Timeout: Person detected at Sensor B but not at Sensor A within 5 seconds");
    Serial.println("Direction: B to A - Movement not completed");
    sensorBTriggered = false;
    personDetected = false;
  }
  
  // Check for simultaneous detection
  if (!sensorATriggered && !sensorBTriggered && 
      distanceA < DETECTION_THRESHOLD && distanceB < DETECTION_THRESHOLD) {
    Serial.println("WARNING: Both sensors triggered simultaneously - possible multiple people detected");
    delay(1000); // Wait a bit before next reading
    return; // Skip this loop iteration
  }
  
  // Check if person is detected by first sensor
  if (!sensorATriggered && !sensorBTriggered && distanceA < DETECTION_THRESHOLD) {
    sensorATime = millis();
    sensorATriggered = true;
    direction = "A to B";
    Serial.println("Person detected at sensor A");
    // Single beep for detection
    tone(buzzerPin, BUZZER_FREQUENCY);
    delay(100);
    noTone(buzzerPin);
  }
  
  // Check if person is detected by second sensor
  if (!sensorATriggered && !sensorBTriggered && distanceB < DETECTION_THRESHOLD) {
    sensorBTime = millis();
    sensorBTriggered = true;
    direction = "B to A";
    Serial.println("Person detected at sensor B");
    // Single beep for detection
    tone(buzzerPin, BUZZER_FREQUENCY);
    delay(100);
    noTone(buzzerPin);
  }
  
  // If first sensor was triggered, check second sensor
  if (sensorATriggered && !personDetected && distanceB < DETECTION_THRESHOLD) {
    sensorBTime = millis();
    personDetected = true;
    
    // Calculate speed
    float timeElapsed = (sensorBTime - sensorATime) / 1000.0; // Convert to seconds
    float speed = SENSOR_DISTANCE / timeElapsed;
    
    // Display results
    Serial.print("Direction: ");
    Serial.println(direction);
    Serial.print("Time elapsed: ");
    Serial.print(timeElapsed);
    Serial.println(" seconds");
    
    Serial.print("Speed: ");
    Serial.print(speed);
    Serial.println(" m/s");
    
    // Check if speed exceeds limit
    if (speed > MAX_ALLOWED_SPEED) {
      Serial.println("WARNING: Speed limit exceeded!");
      // Sound the buzzer alarm - 5 quick beeps
      for (int i = 0; i < 5; i++) {
        tone(buzzerPin, BUZZER_FREQUENCY); // Use constant for frequency
        delay(200);            // Beep duration
        noTone(buzzerPin);     // Stop beep
        delay(200);            // Pause between beeps
      }
    } else {
      Serial.println("Speed within acceptable range");
    }
    
    // Reset detection flags
    sensorATriggered = false;
    personDetected = false;
  }
  
  // If second sensor was triggered, check first sensor
  if (sensorBTriggered && !personDetected && distanceA < DETECTION_THRESHOLD) {
    sensorATime = millis();
    personDetected = true;
    
    // Calculate speed
    float timeElapsed = (sensorATime - sensorBTime) / 1000.0; // Convert to seconds
    float speed = SENSOR_DISTANCE / timeElapsed;
    
    // Display results
    Serial.print("Direction: ");
    Serial.println(direction);
    Serial.print("Time elapsed: ");
    Serial.print(timeElapsed);
    Serial.println(" seconds");
    
    Serial.print("Speed: ");
    Serial.print(speed);
    Serial.println(" m/s");
    
    // Check if speed exceeds limit
    if (speed > MAX_ALLOWED_SPEED) {
      Serial.println("WARNING: Speed limit exceeded!");
      // Sound the buzzer alarm - 5 quick beeps
      for (int i = 0; i < 5; i++) {
        tone(buzzerPin, BUZZER_FREQUENCY); // Use constant for frequency
        delay(200);            // Beep duration
        noTone(buzzerPin);     // Stop beep
        delay(200);            // Pause between beeps
      }
    } else {
      Serial.println("Speed within acceptable range");
    }
    
    // Reset detection flags
    sensorBTriggered = false;
    personDetected = false;
  }
  
  // Small delay to prevent too frequent readings
  delay(50);
}

float getDistance(int trigPin, int echoPin) {
  // Clear trigger pin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  // Send 10μs pulse
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Measure the response
  long duration = pulseIn(echoPin, HIGH);
  
  // Calculate distance in cm
  // Speed of sound = 343 m/s = 34300 cm/s
  // Distance = (Time × Speed) ÷ 2
  // The factor of 2 is because the sound travels to the object and back
  float distance = duration * 0.0343 / 2;
  
  return distance;
} 