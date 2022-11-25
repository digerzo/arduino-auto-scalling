int pulsadorPin = 4; // Variable que guarda el número del pin al que conectamos el pulsador.


int valorPulsador = LOW;
int valorPulsadorAnterior = HIGH; //inicio asi
int contador = 0;

void setup() {
  Serial.begin(9600); // Inicializamos el puerto serie.
  pinMode(pulsadorPin, INPUT); // Declaramos la variable inputPin como entrada y activamos su resistencia interna Pullup.
}
 
void loop(){
  valorPulsadorAnterior = valorPulsador;
  valorPulsador = digitalRead(pulsadorPin);
 
  if (valorPulsador == HIGH && valorPulsadorAnterior == LOW) {
      Serial.println("Pulsado");
      contador ++;
  }
  else {
      Serial.println("No pulsado");
  }
  Serial.println(contador);
  delay(100); // Espera un segundo al final del bucle
}