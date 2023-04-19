#include <SPI.h>
#include <SD.h>

#define DEBUG true

#define pinoTrig1 2
#define pinoEcho1 3
#define pinoTrig2 4
#define pinoEcho2 5

// variaveis para leitura dos sensores ultrasons
float duracao, distancia, duracao1, distancia1, duracao2, distancia2;

// variaveis para leitura do cartão SD
const int chipSelect = 10;
String stringDados1;

void setup()
{
  Serial.begin(9600);

  // sensores ultrasons
  pinMode(pinoTrig1, OUTPUT);
  pinMode(pinoEcho1, INPUT);
  pinMode(pinoTrig2, OUTPUT);
  pinMode(pinoEcho2, INPUT);
  digitalWrite(pinoTrig1, LOW); // Inicia com o pino em nível baixo
  digitalWrite(pinoTrig2, LOW); // Inicia com o pino em nível baixo

  // leitor cartão SD
  Serial.println("Arduino e Cia - Teste de Modulo cartao micro SD");
  Serial.println("Inicializando cartao SD...");
  // Inicia a comunicacao com o modulo SD
  if (!SD.begin(chipSelect))
  {
    Serial.println("Falha ao acessar o cartao !");
    Serial.println("Verifique o cartao/conexoes e reinicie o Arduino...");
    return;
  }
  Serial.println("Cartao iniciado corretamente !");
  Serial.println();
}

void loop()
{
  leituraDistancia(pinoTrig1, pinoEcho1);
  duracao1 = duracao;
  distancia1 = distancia;
  leituraDistancia(pinoTrig2, pinoEcho2);
  duracao2 = duracao;
  distancia2 = distancia;
  Serial.print(distancia1);
  Serial.print(" cm  ");
  Serial.print(distancia2);
  Serial.println(" cm");
  delay(100);

  // testa qual sensor detectou a presença primeiro e define a direção.
  if (distancia1 < 140)
  {
    Serial.println("entrou");
    gravarSd("entrou");
  }
  else if (distancia2 < 140)
  {
    Serial.println("saiu");
    gravarSd("saiu");
  }
  else if (distancia2 < 140 && distancia1 < 140)
  {
    Serial.println("parou");
    gravarSd("parou");
  }
}

// funcao para leitura dos sensores ultrasons
void leituraDistancia(int pinoTrig, int pinoEcho)
{
  digitalWrite(pinoTrig, LOW);
  delayMicroseconds(2);
  digitalWrite(pinoTrig, HIGH);
  delayMicroseconds(10);
  digitalWrite(pinoTrig, LOW);

  duracao = pulseIn(pinoEcho, HIGH);
  distancia = (duracao / 2) * 0.0345;
  delay(100);
}

// função gravar sd
void gravarSd(String stringDados)
{
  File dataFile = SD.open("datalog.txt", FILE_WRITE);
  if (dataFile)
  {
    dataFile.println(stringDados);
    dataFile.close();
    Serial.println("Dados gravados");
  }
  else
  {
    Serial.println("Falha ao gravar");
  }
}