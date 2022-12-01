#include <Instancia.h>
int pulsadorPinIncremento = 4; // Variable que guarda el número del pin al que conectamos el pulsador.
int pulsadorPinDecremento = 5;
int pinLed1 = 6;
int pinLed2 = 7;
int pinLed3 = 8;
int pinLed4 = 9;
int pinLed5 = 10;
int pinLedCooldown = 2;

int vPulsadorIncremento = LOW;
int vPulsadorIncrementoAnterior = HIGH; //inicio asi
int vPulsadorDecremento = LOW;
int vPulsadorDecrementoAnterior = HIGH; //inicio asi

const int tiempoCooldown = 30000; // 30 segundos
const int tiempoDelay = 100;
const int factorContadorCarga = 5;
int contador = 12;
int cargaTotal = 0;
int tiempoCooldownRestante = 0;

const int porcentajeReferencia = 60;
const int segundaCotaSuperior = 80 - porcentajeReferencia;
const int primeraCotaSuperior = 70 - porcentajeReferencia;
const int segundaCotaInferior = 30 - porcentajeReferencia;
const int primeraCotaInferior = 40 - porcentajeReferencia;

Instancia instancia1(pinLed1, 0);
Instancia instancia2(pinLed2, 0);
Instancia instancia3(pinLed3, 0);
Instancia instancia4(pinLed4, 0);
Instancia instancia5(pinLed5, 0);

int cantidadInstancias = 5;
Instancia instancias[5] = {instancia1,instancia2,instancia3,instancia4,instancia5};


void setup() {
  Serial.begin(9600); // Inicializamos el puerto serie.
  pinMode(pulsadorPinIncremento, INPUT);
  pinMode(pulsadorPinIncremento, INPUT);

  pinMode(pinLedCooldown, OUTPUT);
  digitalWrite(pinLedCooldown, LOW);
  instancia1.encender();
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


int instanciasActivas(){
  //devuelve la cantidad de instancias activas
  int res = 0;
  Serial.println("Instancias activas");
  for (int i=0; i < cantidadInstancias; i++) {
    Instancia ins = instancias[i];
    Serial.println(i);
    Serial.println(ins.activa());
    if (ins.activa() == 1) res ++;
  }
  return res;
}

void printf(float f){
    Serial.print("Porcentaje de utilizacion: ");
    Serial.print(f);
    Serial.println("%");
}

void printe(float e){
    Serial.print("Señal error: ");
    Serial.print(e);
    Serial.println("%");
}

void encenderInstancias(int cantidad){
  int encendidas = 0;
  for (int i=0; i < cantidadInstancias; i++){
    Instancia ins = instancias[i];
    if (ins.activa() == 0) {
      ins.encender();
      encendidas ++;
    }
    if (encendidas == cantidad){
      Serial.print("Encendi: ");
      Serial.println(encendidas);
      break;      
    }
  }
  if (encendidas < cantidad){
    Serial.print("Encendi solo: ");
    Serial.println(encendidas);
    Serial.println("Maximo de instancias alcanzado");           
  }
}
void apagarInstancias(int cantidad){
  Serial.print("Apagar instancias: ");
  Serial.println(cantidad);  
}
void printCargaTotalEInstanciasActivas(){
  Serial.print("Carga total: ");
  Serial.println(cargaTotal);
  Serial.print("Instancias activas: ");
  Serial.println(instanciasActivas());
}

void loop1(){
  actualizarContador();
  //solidarizar contador con porcentaje de utilizacion total
  cargaTotal = contador * factorContadorCarga;
  printCargaTotalEInstanciasActivas();
  //chequear si estoy en cooldown
  if (!enCooldown()) {
    digitalWrite(pinLedCooldown, LOW); // no estoy en cooldown
    //calcular error
    float f = cargaTotal / instanciasActivas();
    printf(f);
    float e = -(porcentajeReferencia - f);
    printe(e);
    //determinar y ejecutar accion
    if (e <= primeraCotaSuperior && e >= primeraCotaInferior){
      Serial.println("todo bien, nada que hacer");
    }
    else {
      if (e > segundaCotaSuperior){
        encenderInstancias(2);
      }
      else if (e > primeraCotaSuperior && e <= segundaCotaSuperior){
        encenderInstancias(1);
      }
      else if (e < segundaCotaInferior){
        apagarInstancias(2);
      }
      else if (e < primeraCotaInferior && e >= segundaCotaInferior){
        apagarInstancias(1);
      }
      //establecer cooldown
      tiempoCooldownRestante = tiempoCooldown;      
    }

  }
  else {
    //mostrar pin amarillo
    digitalWrite(pinLedCooldown, HIGH);
    //actualizar cooldown
    actualizarCooldown(tiempoDelay);
  }
  delay(tiempoDelay);
}
int flag = 1;
void loop() {
  // if (flag>0){
  //   instancia2.encender();
  // }
  int c = instanciasActivas();
  Serial.println(c); 
  Serial.println("fin");
  flag = 0;
  delay(1000);
}