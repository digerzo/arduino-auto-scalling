#include <Instancia.h>
int pulsadorPinIncremento = 4; // Variable que guarda el número del pin al que conectamos el pulsador.
int pulsadorPinDecremento = 5;
int pinLed1 = 6;
int pinLed2 = 7;
int pinLed3 = 8;
int pinLed4 = 9;
int pinLed5 = 10;

int leds [5] = {pinLed1,pinLed2,pinLed3,pinLed4,pinLed5};

int pinLedCooldown = 2;

int vPulsadorIncremento = LOW;
int vPulsadorIncrementoAnterior = HIGH; //inicio asi
int vPulsadorDecremento = LOW;
int vPulsadorDecrementoAnterior = HIGH; //inicio asi

const int tiempoCooldown = 30000; // 30 segundos
const int tiempoDelay = 100;
const int porcentajeReferencia = 60;
int instanciasActivas = 1;
int contador = 0;
int cargaTotal = 0;
int tiempoCooldownRestante = 0;

Instancia instancia1(pinLed1, true);
Instancia instancia2(pinLed2, false);
Instancia instancia3(pinLed3, false);
Instancia instancia4(pinLed4, false);
Instancia instancia5(pinLed5, false);

void setup() {
  Serial.begin(9600); // Inicializamos el puerto serie.
  pinMode(pulsadorPinIncremento, INPUT);
  pinMode(pulsadorPinIncremento, INPUT);

  pinMode(pinLedCooldown, OUTPUT);
  digitalWrite(pinLedCooldown, LOW);
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
  return tiempoCooldownRestante > 0;
}

void actualizarCooldown(int tiempo){
  tiempoCooldownRestante = tiempoCooldownRestante - tiempo;
}

void loop2(){
  actualizarContador();
  //solidarizar contador con porcentaje de utilizacion total
  cargaTotal = contador * 5;
  //chequear si estoy en cooldown
  if (!enCooldown()) {
    digitalWrite(pinLedCooldown, LOW); // no estoy en cooldown
    //calcular error
    // int f = cargaTotal / instanciasActivas();
    // int e = porcentajeReferencia - f;
    //determinar y ejecutar accion
    // if (e > )
    //establecer cooldown
  }
  else {
    //mostrar pin amarillo
    digitalWrite(pinLedCooldown, HIGH);
    //actualizar cooldown
    actualizarCooldown(tiempoDelay);
  }
  delay(tiempoDelay);
}

void loop_test() {
  instancia1.encender();
  delay(tiempoDelay);
  instancia1.apagar();
  delay(tiempoDelay);
  instancia2.encender();
  delay(tiempoDelay);
  instancia2.apagar();
  delay(tiempoDelay);
  instancia3.encender();
  delay(tiempoDelay);
  instancia3.apagar();
  delay(tiempoDelay);
  instancia4.encender();
  delay(tiempoDelay);
  instancia4.apagar();
  delay(tiempoDelay);
  instancia5.encender();
  delay(tiempoDelay);
  instancia5.apagar();
  delay(tiempoDelay);
}