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

const int tiempoCooldown = 20000; // 20 segundos
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

int cantidadInstancias = 5;
int instancias[5][2] = {{pinLed1,0},{pinLed2,0},{pinLed3,0},{pinLed4,0},{pinLed5,0}};

void encenderInstancia(int posicion) {
  int pin = instancias[posicion][0];
  digitalWrite(pin, HIGH);
  instancias[posicion][1] = 1;
}
void apagarInstancia(int posicion) {
  int pin = instancias[posicion][0];
  digitalWrite(pin, LOW);
  instancias[posicion][1] = 0;
}


void setup() {
  Serial.begin(9600); // Inicializamos el puerto serie.
  pinMode(pulsadorPinIncremento, INPUT);
  pinMode(pulsadorPinIncremento, INPUT);

  pinMode(pinLedCooldown, OUTPUT);
  digitalWrite(pinLedCooldown, LOW);
  pinMode(pinLed1, OUTPUT);
  pinMode(pinLed2, OUTPUT);
  pinMode(pinLed3, OUTPUT);
  pinMode(pinLed4, OUTPUT);
  pinMode(pinLed5, OUTPUT);
  encenderInstancia(0);
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
  for (int i=0; i < cantidadInstancias; i++) {
    int activa = instancias[i][1];
    if (activa == 1) res ++;
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
    //recorro las instancias chequeando si estan activas o no
    int activa = instancias[i][1];
    if (activa == 0) {
      encenderInstancia(i);
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
  int apagadas = 0;
  int activas = instanciasActivas();
  if (activas == 1){
    Serial.println("No puedo apagar instancias, minimo alcanzado");
    return;    
  }
  if (cantidad >= activas){
    cantidad = activas - 1; //puedo apagar todas menos 1
  }
  for (int i=0; i < cantidadInstancias; i++){
    //recorro las instancias chequeando si estan activas o no
    int activa = instancias[i][1];
    if (activa == 1) {
      apagarInstancia(i);
      apagadas ++;
    }
    if (apagadas == cantidad){
      Serial.print("Apague: ");
      Serial.println(apagadas);
      break;      
    }
  }
  if (apagadas < cantidad){
    Serial.print("Apague solo: ");
    Serial.println(apagadas);
    Serial.println("Minimo de instancias alcanzado");           
  }
}
void printCargaTotalEInstanciasActivas(){
  Serial.print("Carga total: ");
  Serial.println(cargaTotal);
  Serial.print("Instancias activas: ");
  Serial.println(instanciasActivas());
}

int acum = 0;

void loop(){
  actualizarContador();
  //solidarizar contador con porcentaje de utilizacion total
  cargaTotal = contador * factorContadorCarga;
  float f = cargaTotal / instanciasActivas();
  //calcular error
  float e = -(porcentajeReferencia - f);
  if (acum == 1000) {
    printCargaTotalEInstanciasActivas();
    printf(f);
    printe(e);
    acum = 0;
  }
  //chequear si estoy en cooldown
  if (!enCooldown()) {
    digitalWrite(pinLedCooldown, LOW); // no estoy en cooldown
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
  acum = acum + tiempoDelay;  
  delay(tiempoDelay);
}
int cont = 0;
void loop1() {

  encenderInstancias(1);
  int c = instanciasActivas();
  Serial.println(c); 
  
  delay(1000);
  if (cont == 3) {
    apagarInstancias(3);
    cont = 0;
  }
  delay(1000);
  cont ++;
  Serial.println("fin");
}