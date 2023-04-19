#include <SPI.h>
#include <SD.h>

#define DEBUG true

#define pinoTrig1 2  // Pino de comunicaçao ligado ao Trigger
#define pinoEcho1 3  // Pino de comunicaçao ligado ao Echo
float distancia1;    // Variavel de leitura da distancia

#define pinoTrig2 4  // Pino de comunicaçao ligado ao Trigger
#define pinoEcho2 5  // Pino de comunicaçao ligado ao Echo
float distancia2;    // Variavel de leitura da distancia

const int chipSelect = 10;
int segundos, minutos, horas;
String dataString1;

void setup() {
  Serial.begin(9600);  // Inicia a comunicação serial
  pinMode(pinoTrig1, OUTPUT);
  pinMode(pinoEcho1, INPUT);
  pinMode(pinoTrig2, OUTPUT);
  pinMode(pinoEcho2, INPUT);
  digitalWrite(pinoTrig1, LOW);  // Inicia com o pino em nível baixo
  digitalWrite(pinoTrig2, LOW);  // Inicia com o pino em nível baixo
  Serial.println("Arduino e Cia - Teste de Modulo cartao micro SD");
  Serial.println("Inicializando cartao SD...");
  //Inicia a comunicacao com o modulo SD
  if (!SD.begin(chipSelect)) {
    Serial.println("Falha ao acessar o cartao !");
    Serial.println("Verifique o cartao/conexoes e reinicie o Arduino...");
    return;
  }
  Serial.println("Cartao iniciado corretamente !");
  Serial.println();
}
void loop() {
  dataString1= millis() / 1000;
  /*
  segundos = millis() / 1000;

  if (segundos == 60) {
    segundos = 0 - millis() / 1000;
    minutos++;
  }
  if (minutos == 60) {
    minutos = 0;
    horas++;
  }
  Serial.println(String(horas) + ":" + String(minutos) + ":" + String(segundos));
*/  
  leitura1();
  leitura2();
  distancia1 = distancia1 / 2;         // Divide por 2 pois esse e o tempo da onda ir e voltar
  distancia1 = distancia1 * 0.034029;  // Multiplicamos por 0,034 por causa da velocidade do som (d=v*t)
  distancia2 = distancia2 / 2;         // Divide por 2 pois esse e o tempo da onda ir e voltar
  distancia2 = distancia2 * 0.034029;  // Multiplicamos por 0,034 por causa da velocidade do som (d=v*t)
  String estado = "nada";
  if (distancia1 < 140 && distancia2 > 140) {
    estado = "entrou";
    //Serial.println(estado);
    delay(800);
  }
  if (distancia1 > 140 && distancia2 < 140) {
    estado = "saiu";
    //Serial.println(estado);
    delay(800);
  }
  if (distancia1 < 140 && distancia2 < 140) {
    estado = "parou";
    //Serial.println(estado);
    delay(800);
  }
  if (estado != "nada") {
    // String dataString2 = String(distancia);
    String dataString2 = estado;
    Serial.println(dataString1 + "," + dataString2);
    File dataFile = SD.open("datalog.txt", FILE_WRITE);
    //Grava as informacoes no arquivo
    if (dataFile) {
      dataFile.println(dataString1 + "," + dataString2);
      dataFile.close();
    }
  }
}

void leitura1() {
  digitalWrite(pinoTrig1, HIGH);  // Manda um sinal de nível alto por 10 microssegundos
  delayMicroseconds(20);
  digitalWrite(pinoTrig1, LOW);
  distancia1 = pulseIn(pinoEcho1, HIGH);  // Le o comprimento de onda em alta
}
void leitura2() {
  digitalWrite(pinoTrig2, HIGH);  // Manda um sinal de nível alto por 10 microssegundos
  delayMicroseconds(20);
  digitalWrite(pinoTrig2, LOW);
  distancia2 = pulseIn(pinoEcho2, HIGH);  // Le o comprimento de onda em alta
}
