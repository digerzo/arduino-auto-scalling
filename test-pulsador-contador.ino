int pulsadorPinIncremento = 4; // Variable que guarda el número del pin al que conectamos el pulsador.
int pulsadorPinDecremento = 5;

int vPulsadorIncremento = LOW;
int vPulsadorIncrementoAnterior = HIGH; //inicio asi
int vPulsadorDecremento = LOW;
int vPulsadorDecrementoAnterior = HIGH; //inicio asi

int contador = 0;

void setup() {
  Serial.begin(9600); // Inicializamos el puerto serie.
  pinMode(pulsadorPinIncremento, INPUT);
  pinMode(pulsadorPinIncremento, INPUT); 
}
 
void loop(){
  vPulsadorIncrementoAnterior = vPulsadorIncremento;
  vPulsadorIncremento = digitalRead(pulsadorPinIncremento);

  vPulsadorDecrementoAnterior = vPulsadorDecremento;
  vPulsadorDecremento = digitalRead(pulsadorPinDecremento);
 
  if (vPulsadorIncremento == HIGH && vPulsadorIncrementoAnterior == LOW) contador ++;
  if (vPulsadorDecremento == HIGH && vPulsadorDecrementoAnterior == LOW) contador --;
  Serial.println(contador);
  delay(100); // Espera un segundo al final del bucle
}