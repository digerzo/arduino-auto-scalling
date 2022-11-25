int pulsadorPin = 4; // Variable que guarda el número del pin al que conectamos el pulsador.
int valorPulsador = LOW; // Variable donde almacenaremos la lectura del estado del pulsador.
int contador = 0;
int puedoSumar = 1; 

void setup() {
  Serial.begin(9600); // Inicializamos el puerto serie.
  pinMode(pulsadorPin, INPUT); // Declaramos la variable inputPin como entrada y activamos su resistencia interna Pullup.
}
 
void loop(){
  valorPulsador = digitalRead(pulsadorPin);
 
  if (valorPulsador == HIGH) {
      Serial.println("Pulsado");
      if (puedoSumar == 1) {
        puedoSumar = 0;
        contador ++;        
      }
  }
  else {
      Serial.println("No pulsado");
      puedoSumar = 1;
  }
  Serial.println(contador);
  delay(100); // Espera un segundo al final del bucle
}