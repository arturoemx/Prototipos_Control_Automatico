//Pines 2 y 3 de arduino con soporte para
//interrupciones, sirve para detectar los pulsos
#define en_CH_A 2
#define en_CH_B 3 
//Se cuentan los pulsos que hay en las vueltas
volatile long cont_pulsos= 0;
 
void setup() {
 
  //Se inicia la comunicación en serie con 9600bps
  Serial.begin(9600); 
 
  /*Se define como entrada el pin 2 para que detecte
  el estado del encoder y se define como entrada el pin 3
  para determinar si va en sentido horario o antihorario
  el motor*/
  pinMode(en_CH_A, INPUT_PULLUP);
  pinMode(en_CH_B, INPUT_PULLUP);
 
  //Cada flanco ascendente se detecta como un pulso
  attachInterrupt(digitalPinToInterrupt(en_CH_A), contar_pulsos, RISING);
  }
 
void loop() {
 
    Serial.print("Pulsos: ");
    Serial.println(cont_pulsos);  
}
 
//Incrementa o decrementa en 1 cada pulso detectado
void contar_pulsos() {
  if (digitalRead(en_CH_B) == HIGH){
    cont_pulsos++; //Sentido horario
  } else {
    cont_pulsos--; //Sentido antihorario
    }
}
