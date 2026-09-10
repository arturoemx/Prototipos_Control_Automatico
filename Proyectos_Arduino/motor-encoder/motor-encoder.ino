//Pin 2 de arduino con soporte para
//interrupciones, sirve para detectar los pulsos
#define en_CH_A 2
 
//Se cuentan los pulsos que hay en las vueltas
volatile long cont_pulsos= 0;
 
void setup() {
 
  //Se inicia la comunicación en serie con 9600bps
  Serial.begin(9600); 
 
  //Se define como entrada el pin 2 para que
  //el estado del encoder
  pinMode(en_CH_A, INPUT_PULLUP);
 
  //Cada flanco ascendente se detecta como un pulso
  attachInterrupt(digitalPinToInterrupt(en_CH_A), contar_pulsos, RISING);
   
}
 
void loop() {
  
    Serial.print(" Pulses: ");
    Serial.println(cont_pulsos);  
}
 
//Incrementa en 1 cada pulso detectado
void contar_pulsos() {
  if (en_CH_A > 0){
    cont_pulsos++;
  } else { cont_pulsos--}
}
