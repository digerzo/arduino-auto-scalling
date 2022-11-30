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

void iniciarPinLeds(){
  for (int i=pinLed1; i < pinLed1 + 5; i++) {
    pinMode(i, OUTPUT);
    digitalWrite(i, LOW);
    Serial.println(i);
  }
}

void setup() {
  Serial.begin(9600); // Inicializamos el puerto serie.
  pinMode(pulsadorPinIncremento, INPUT);
  pinMode(pulsadorPinIncremento, INPUT);

  pinMode(pinLedCooldown, OUTPUT);
  digitalWrite(pinLedCooldown, LOW);

  iniciarPinLeds();

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
  return tiempoCooldownRestante > 0;  
}

void actualizarCooldown(int tiempo){
  tiempoCooldownRestante = tiempoCooldownRestante - tiempo;
}

int len(int arrayInt[]) {
  return sizeof arrayInt / sizeof arrayInt[0];  
}

class Instancia {
  public:
    int pin;
    bool activa;

    void encender() {
      digitalWrite(pin, HIGH);
      activa = true;
    }
    void apagar() {
      digitalWrite(pin, LOW);
      activa = false;      
    }
    Instancia(int pin, bool activa){
      pin = pin;
      activa = activa;
    }    
};

void loop(){
  
  actualizarContador();
  if (!enCooldown()) {
    controlarLed(pinLed1, 10);
    controlarLed(pinLed2, 15);
    digitalWrite(pinLedCooldown, LOW); // no estoy en cooldown
  }
  else {
    digitalWrite(pinLedCooldown, HIGH);
    actualizarCooldown(tiempoDelay);
  }

  Serial.println(contador);
  
  delay(tiempoDelay); // Espera un segundo al final del bucle
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