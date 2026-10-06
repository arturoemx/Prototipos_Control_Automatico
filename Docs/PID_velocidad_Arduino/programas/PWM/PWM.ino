// Pines
const int pwmPin = 9;
const int encoderPinA = 2;
const int potPin = A0;

// Parámetros del sistema
const float R_max = 120.0;  // Velocidad máxima deseada (ej. RPM)
const float R_min = 0.0;
const float dt = 0.05;      // Tiempo entre ciclos (50 ms)

// Encoder
volatile long encoderCount = 0;
long lastEncoderCount = 0;

// PID
float referencia = 0;
float error = 0;
float integral = 0;
float tmpInt = 0;
float derivada = 0;
float lastError = 0;

// Constantes PID	
float Kp = 1.08;   //original = 2.0, sintonizado 1.062
float Ki = 43.2;   //original = 1.0, sintonizado 28.320
float Kd = 0.00675;   //original = 1.0, sintonizado 0.010

unsigned long previousMillis = 0;

void setup() {
  Serial.begin(115200);  // Velocidad alta para graficar

  pinMode(pwmPin, OUTPUT);
  pinMode(encoderPinA, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(encoderPinA), encoderISR, RISING);
}

void loop() {
  unsigned long currentMillis = millis();         //Se inicia la captura de tiempo
  if (currentMillis - previousMillis >= 50) {     //Se capturan periodos de 50 ms
    previousMillis = currentMillis;               //Se actualiza el último periodo para comparar con el actual

    // Leer potenciómetro y escalar
    int lecturaPot = analogRead(potPin);
    referencia = map(lecturaPot, 0, 1023, R_min * 10, R_max * 10) / 10.0;

    // Calcular velocidad (en pulsos por 50ms)
    long currentEncoder = encoderCount;           //Se toma el valor actual del encoder con la interrupción
    float velocidad = (currentEncoder - lastEncoderCount) / dt; //Se calcula la velocidad con v= delta_x/dt
    lastEncoderCount = currentEncoder;                          //Actualizamos el último valor del encoder

    // Convertir pulsos a RPM
    float PPR = 408.0;                                //Pulsos por rev, del encoder obtenidos de su resolución y tamaño de reductor
    float rpm = (velocidad / PPR) * 60.0;             //Cálculo de la velocidad en RPM

    // PID
    error = referencia - rpm;                         //Se calcula el error con los rpm de referencia y los reales
    float P = Kp * error;                             //Cálculo de la constante proporcional
    float D = Kd * ((error-lastError)/dt);            //Cálculo de la constante derivativa
    tmpInt  = integral + (error * dt);                //Valor temporal en la integral para evitar saturación
    float I = Ki * tmpInt;                            //Cálculo de la contante integral
    lastError = error;                                //Se actualiza el valor del último error

    float salida = P + I + D;                         //Salida sin anti-windup
    
    if(salida >= 0 && salida <= 255){                 //Anti-windup implementado en caso de que se sature el
      integral = tmpInt;                              //valor de la integral
      }else if((salida > 255 && error < 0) || (salida < 0 && error > 0)){
        integral = tmpInt;
        }
 
    int salidaPWM = constrain((int)(P + Ki*integral + D), 0, 255);     //Salida final al pin PWM del Arduino

    
    analogWrite(pwmPin, salidaPWM);                                    // PWM constante en una sola dirección

    // Datos para graficar
    Serial.print(currentMillis);
    Serial.print(",");
    Serial.print(referencia);
    Serial.print(",");
    Serial.print(rpm);
    Serial.print(",");
    Serial.print(salidaPWM);
    Serial.print(",");
    Serial.print(error, 2);
    Serial.print(",");
    Serial.print((Ki*integral));
    Serial.print(",");
    Serial.println(D);
  }
}

void encoderISR() {
  encoderCount++;  // Siempre incrementa,   solo gira en un sentido
}
