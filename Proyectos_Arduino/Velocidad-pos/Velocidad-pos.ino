//Pines para detectar los pulsos y la dirección
//de giro del motor
#define en_ch_A 2
#define en_ch_B 4
//Cantidad medida de pulsos manualmente
#define pulsos_medidos 500 
// True -> horario; false -> antihorario
boolean direccion_mt= true;
 
//Cuenta los pulsos a través de las interrupciones
//en el pin 2
volatile long conteo_pulsos = 0;
 
//Intevalo de tiempo para el muestro de los pulsos de 1s
int interval = 1000;
  
//Contadores en milisegundos durante el intervalo
long previousMillis = 0;
long currentMillis = 0;
 
//Medida de velocidad en rpm
float rpm_val = 0;
 
//Velocidad angular en grados y radianes
float vel_ang_rad = 0;
float vel_ang_deg = 0;
//Constantes de conversión a grados y radianes 
const float rpm_rad = 0.10471975512;
const float rad_deg = 57.29578;
 
void setup() {
 
  //Inicialización de la comunicación serie 
  Serial.begin(9600); 
 
  //Configuración de los pines del encoder
  pinMode(en_ch_A , INPUT_PULLUP);
  pinMode(en_ch_B , INPUT);
 
  //La interrupción detecta el flanco ascendente y llama al servicio de
  //interrupcción para irlos contando
  attachInterrupt(digitalPinToInterrupt(en_ch_A), contar_pulsos, RISING);
   
}
 
void loop() {
 
  //Se comienza a contar el tiempo de muestreo
  currentMillis = millis();
 
  //Se compara si ya pasó el segundo e imprime el número de pulsos 
  if (currentMillis - previousMillis > interval) {
    //Se actualiza el intervalo de tiempo anterior con el actual
    previousMillis = currentMillis;
 
    //Calcula los RPM
    rpm_val = (float)(conteo_pulsos * 60 / pulsos_medidos);
    vel_ang_rad = rpm_val * rpm_rad;   
    vel_ang_deg = vel_ang_rad * rad_deg;
     
    Serial.print("Pulsos: ");
    Serial.println(conteo_pulsos);
    Serial.print("Velocidad: ");
    Serial.print(rpm_val);
    Serial.println("RPM");
    Serial.print("Velocidad angular en rads: ");
    Serial.print(vel_ang_rad);
    Serial.print(" rads/s");
    Serial.print("\t");
    Serial.print("Velocidad angular en grados");
    Serial.print(vel_ang_rad);
    Serial.println("g/s");
    Serial.println();
 
    conteo_pulsos = 0;
   
  }
}
 
//Incrementa los pulsos en 1
void contar_pulsos() {
   
  //Lee el valor del canal B en el encoder
  int val = digitalRead(en_ch_B);
 
  if(val == LOW) {
    direccion_mt= false; // antihorario
    conteo_pulsos--;
  }
  else {
    direccion_mt= true; // horario
    conteo_pulsos++; 
  }
 }
   
 
