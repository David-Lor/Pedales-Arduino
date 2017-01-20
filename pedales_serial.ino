/* PEDALES SERIAL
 * Se envía por SERIAL el valor de V y el estado de los pedales. Conectados dos pedales por dos hilos.
 * En equipo cliente, se pueden interpretar los valores de las dos formas (procesando valor o usando el estado procesado por Arduino).
 */

#define bps 115200
#define LED_IZQUIERDO 2
#define LED_DERECHO 3
#define ANALOGINPUT 0
//Sintaxis para valores serial
#define STR_ARRANQUE "ini"
#define STR_IZQUIERDA "izq"
#define STR_DERECHA "dch"
#define STR_AMBOS "amb"
#define STR_NADA "nad"
#define STR_ERROR "err"
//Valores de V para los pedales
#define NADA1 895
#define NADA2 905
#define IZQ1 935
#define IZQ2 945
#define DCH1 675
#define DCH2 685
#define AMBOS1 875
#define AMBOS2 885
byte prevPos = 0;
//Posiciones: 0=nada/err, 1=izquierda, 2=derecha, 3=ambos, 4=valor no reconocido
unsigned long count = 0;

void setup() {
  Serial.begin(bps);
  Serial.println(F("Arduino pedales arrancado"));
  Serial.println(F(STR_ARRANQUE));
  pinMode(LED_IZQUIERDO,OUTPUT);
  pinMode(LED_DERECHO,OUTPUT);
  digitalWrite(LED_IZQUIERDO,LOW);
  digitalWrite(LED_DERECHO,LOW);
}

void loop() {
  int v = analogRead(ANALOGINPUT);
  /*bool izq = false;
  bool dch = false;
  bool error = false;*/
  byte pos = 0;
  bool cambio = false;

  if (v >= NADA1 && v <= NADA2) { //nada (reposo) -No error
    pos = 0;
  } else if (v >= IZQ1 && v <= IZQ2) { //izquierda
    //izq = true;
    pos = 1;
  } else if (v >= DCH1 && v <= DCH2) { //derecha
    //dch = true;
    pos = 2;
  } else if (v >= AMBOS1 && v <= AMBOS2) { //ambos
    //izq = true;
    //dch = true;
    pos = 3;
  } else { //en caso de error (valor no reconocible), seguir con el valor previo
    pos = prevPos;
  }

  if (pos != prevPos) { cambio = true; }

  //DEBUG TIPO 1: transmisión constante - utiliza 3 bools
  //Sintaxis serial: vvv/ttt ; siendo vvv el valor analogRead, y ttt = izq, dch, amb o nad
  /*Serial.print(String(v));
  Serial.print('/');
  if (izq && !dch) { //pedal izquierdo
    Serial.println(F(STR_IZQUIERDA));
    digitalWrite(LED_IZQUIERDO,HIGH);
    digitalWrite(LED_DERECHO,LOW);
  } else if (!izq && dch) { //pedal derecho
    Serial.println(F(STR_DERECHA));
    digitalWrite(LED_IZQUIERDO,LOW);
    digitalWrite(LED_DERECHO,HIGH);
  } else if (izq && dch) { //ambos pedales
    Serial.println(F(STR_AMBOS));
    digitalWrite(LED_IZQUIERDO,HIGH);
    digitalWrite(LED_DERECHO,HIGH);
  } else if (!error) { //ningún pedal
    Serial.println(F(STR_NADA));
    digitalWrite(LED_IZQUIERDO,LOW);
    digitalWrite(LED_DERECHO,LOW);
  } else if (error) { //valor no reconocido
    Serial.println(F(STR_ERROR));
    digitalWrite(LED_IZQUIERDO,LOW);
    digitalWrite(LED_DERECHO,LOW);
  }*/

  //DEBUG TIPO 2: sólo transmite cuando hay un cambio. Usa 2 bytes (uno previo y otro presente)
  if (cambio) {
    switch (pos) {
      case 0: //Nada/error-no reconocido
        Serial.print(F(STR_NADA));
        digitalWrite(LED_IZQUIERDO,LOW);
        digitalWrite(LED_DERECHO,LOW);
        break;
      case 1: //Izquierda
        Serial.print(F(STR_IZQUIERDA));
        digitalWrite(LED_IZQUIERDO,HIGH);
        digitalWrite(LED_DERECHO,LOW);
        break;
      case 2: //Derecha
        Serial.print(F(STR_DERECHA));
        digitalWrite(LED_IZQUIERDO,LOW);
        digitalWrite(LED_DERECHO,HIGH);
        break;
      case 3: //Ambos
        Serial.print(F(STR_AMBOS));
        digitalWrite(LED_IZQUIERDO,HIGH);
        digitalWrite(LED_DERECHO,HIGH);
        break;
    }
    Serial.print(F("/v="));
    Serial.print(String(v));
    Serial.print(F("/#"));
    Serial.println(String(++count));
  }

  prevPos = pos;
}
