#include <Arduino.h>

// Definição dos pinos
const int pinSensorLuz = A0; // Pino analógico para o sensor de luz
const int pinLED = 13;       // Pino digital para o LED

// Variáveis para armazenar a média da intensidade da luz
const int numLeituras = 10; // Número de leituras que serão usadas para calcular a média
int leiturasLuz[numLeituras]; // Array para armazenar as últimas leituras
int indiceLeitura = 0; // Índice para armazenar a próxima leitura no array
float mediaLuz = 0; // Variável para armazenar a média da intensidade da luz

void setup() {
  // Inicializa o pino do LED como saída
  pinMode(pinLED, OUTPUT);
  // Inicializa a comunicação serial
  Serial.begin(9600);
}

void loop() {
  // Lê o valor do sensor de luz
  int valorLuz = analogRead(pinSensorLuz);
  
  // Armazena a leitura atual no array de leituras
  leiturasLuz[indiceLeitura] = valorLuz;
  
  // Atualiza o índice para a próxima leitura
  indiceLeitura = (indiceLeitura + 1) % numLeituras;
  
  // Calcula a média da intensidade da luz
  float soma = 0;
  for (int i = 0; i < numLeituras; i++) {
    soma += leiturasLuz[i];
  }
  mediaLuz = soma / numLeituras;
  
  // Mostra o valor médio lido do sensor na comunicação serial
  Serial.print("Intensidade média da Luz: ");
  Serial.println(mediaLuz);
  
  // Decide se o LED deve ser ligado ou desligado
  if (mediaLuz < 500) {
    digitalWrite(pinLED, HIGH); // Liga o LED se estiver escuro
  } else {
    digitalWrite(pinLED, LOW); // Desliga o LED se estiver claro
  }
  
  // Aguarda um pouco antes da próxima leitura
  delay(1000);
}