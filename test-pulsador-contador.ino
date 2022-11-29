int pulsadorPinIncremento = 4; // Variable que guarda el número del pin al que conectamos el pulsador.
int pulsadorPinDecremento = 5;
int pinLed = 6;
int pinLedV = 7;
int pinLedCooldown = 2;

int vPulsadorIncremento = LOW;
int vPulsadorIncrementoAnterior = HIGH; //inicio asi
int vPulsadorDecremento = LOW;
int vPulsadorDecrementoAnterior = HIGH; //inicio asi


int contador = 0;
int tiempoDelay = 100;

void setup() {
  Serial.begin(9600); // Inicializamos el puerto serie.
  pinMode(pulsadorPinIncremento, INPUT);
  pinMode(pulsadorPinIncremento, INPUT);
  
  pinMode(pinLed, OUTPUT);
  digitalWrite(pinLed, LOW);
  pinMode(pinLedV, OUTPUT);
  digitalWrite(pinLedV, LOW);
  pinMode(pinLedCooldown, OUTPUT);
  digitalWrite(pinLedCooldown, LOW);
  
}

void controlarLed(int led, int limite) {
    if (contador > limite) {
      digitalWrite(led, HIGH);    
    }
    else {
      digitalWrite(led, LOW);   
    }
  }

void actualizarContador() {
  vPulsadorIncrementoAnterior = vPulsadorIncremento;
  vPulsadorIncremento = digitalRead(pulsadorPinIncremento);

  vPulsadorDecrementoAnterior = vPulsadorDecremento;
  vPulsadorDecremento = digitalRead(pulsadorPinDecremento);
 
  if (vPulsadorIncremento == HIGH && vPulsadorIncrementoAnterior == LOW) contador ++;
  if (vPulsadorDecremento == HIGH && vPulsadorDecrementoAnterior == LOW) contador --;
}

bool enCooldown(){
  return contador > 20;  
}

void loop(){

  actualizarContador();
  if (!enCooldown()) {
    controlarLed(pinLed, 10);
    controlarLed(pinLedV, 15);
    digitalWrite(pinLedCooldown, LOW);
  }
  else {
    digitalWrite(pinLedCooldown, HIGH);    
  }

  Serial.println(contador);
  delay(tiempoDelay); // Espera un segundo al final del bucle
}