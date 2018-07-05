//Porta ligada ao pino IN1 do modulo
int porta_rele1 = 7;
//Porta ligada ao pino IN2 do modulo
int porta_rele2 = 8;
//Porta ligada ao botao 2
int porta_botao1 = 2;
//Armazena o estado do rele - 0 (HIGH) ou 1 (LOW)  Um detalhe importante desse módulo é que os relés são ativados em nível baixo, ou seja, quando o estado da porta estiver em LOW, o relé será acionado.
int estadorele1 = 1;
int estadorele2 = 1;
//Armazena o valor lido dos botoes
int leitura1 = 0;
//Entrada do LM35
int tempPin = 0;
//Armazena a leitura do LM35
float temp;
//Saída dos ventiladores
int Fan= 10;
//Determina a temperatura mínima
float TempMin= 20 +1.5 ;
//Determina a temperatura máxima
float TempMax= 35 + 1.5;
//Armazena a velocidade do ventilador, em 8bits
int FanSpeed;
//Armazena o valor do PWM
int PWM;
//Saída do LED
int LED = 5;
void setup() {
    //Define pinos para o rele como saida
  pinMode(porta_rele1, OUTPUT); 
  pinMode(porta_rele2, OUTPUT);
  //Define o pino do botão como entrada
  pinMode(porta_botao1, INPUT);
  //Define o pino do LED como saída
  pinMode(LED,OUTPUT);
  //Define o ventilador como saída
  pinMode(Fan,OUTPUT);
  //Estado inicial dos reles - desligados
  digitalWrite(porta_rele1, HIGH);
  digitalWrite(porta_rele2, HIGH);
  //Define a taxa de dados em bits por segundo para a transmissão de dados em série.
  Serial.begin(9600);
  
  
}

void loop() {
//Se a temperatura estiver abaixo da mínima, o cooler ficará desligado
     if (temp < TempMin) {
   FanSpeed =0;
   digitalWrite(Fan,LOW);
      }
      //Se a velocidade for maior que a mínima e menor que a máxima, ajusta a velocidade de acordo com a temperatura
if ((temp >= TempMin) && (temp <= TempMax)){
  FanSpeed = map(temp,TempMin,TempMax,64,255);
  analogWrite(Fan,FanSpeed);
}
//Se a temperatura for maior que a máxima, não altera o sistema e liga um LED vermelho para sinalização. Se a temperatura se tornar mais baixa que a máxima, o LED apaga.
if (temp > TempMax){
  FanSpeed = 255;
  analogWrite(Fan,FanSpeed);
    digitalWrite(LED,HIGH);}
    else {
    digitalWrite(LED,LOW);
    }
    //Determina o valor do PWM em %
PWM = map(FanSpeed,0,255,0,100);
//Transforma a temperatura da leitura analógica do sensor para Celsius e a mostra.
  temp = analogRead(tempPin);
temp = temp * 0.48828125;
  Serial.print("Temperatura agora = ");
  Serial.print(temp);
  Serial.print("°C");
  Serial.println();
  //Mostra o valor do PWM
  Serial.print("PWM = ");
  Serial.println(PWM);
  //Aguarda por 2 segundos
  delay(2000);
  
 //Verifica o acionamento do botao 1
  leitura1 = digitalRead(porta_botao1);
  //Se o botão for acionado
  if (leitura1 != 0)
  {
    //Enquanto o botão estiver acionado
    while(digitalRead(porta_botao1) != 0)
    {
      //Espera 100 milissegundos
      delay(100);
    }
    //Inverte o estado da porta
    estadorele1 = !estadorele1;
    estadorele2 =!estadorele2;
       //Comandos para os reles
   digitalWrite(porta_rele1, estadorele1);  
   digitalWrite(porta_rele2, estadorele2); 

 
   

}
}
