// Define encoder pins
const int encoderA = 2; // Connect to the yellow wire (Encoder A)
const int encoderB = 3; // Connect to the green wire (Encoder B)

// Variables to track encoder position
volatile long encoderPosition = 0;
int lastEncoded = 0;

void setup() {
  // Initialize serial communication
  Serial.begin(9600);

  // Set encoder pins as inputs
  pinMode(encoderA, INPUT);
  pinMode(encoderB, INPUT);

  // Attach interrupts for encoder pins
  attachInterrupt(digitalPinToInterrupt(encoderA), updateEncoder, CHANGE);
  attachInterrupt(digitalPinToInterrupt(encoderB), updateEncoder, CHANGE);
}

void loop() {
  // Print the encoder position to the Serial Monitor
  Serial.print("Encoder Position: ");
  Serial.println(encoderPosition);
  delay(100); // Small delay for readability
}

// Interrupt service routine to update encoder position
void updateEncoder() {
  int MSB = digitalRead(encoderA); // Most significant bit
  int LSB = digitalRead(encoderB); // Least significant bit

  int encoded = (MSB << 1) | LSB; // Combine the two bits
  int sum = (lastEncoded << 2) | encoded; // Track state changes

  // Update position based on state changes
  if (sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011) {
    encoderPosition++;
  } else if (sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000) {
    encoderPosition--;
  }

  lastEncoded = encoded; // Store the current state
}
