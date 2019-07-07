#include <TimerOne.h>

//declaração da variaveis
float erro=0;
float erro_1=0;
float erro_2=0;

float sinalcontrol=0;
float sinalcontrol_1=0;
float sinalcontrol_2=0;

float sinalcontrol_norma = 0;


float saida = 0;



float set_point=0;


//declaração portas
int porta_pwm = 6; 
int port_analog_discovery = A1;
int port_saida = A0;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  // pwm mais rapidos
   TCCR0B = TCCR0B & B11111000 | B00000001;
   TCCR2B = TCCR2B & B11111000 | B00000001;
   //analogWriteResolution(12); só para o DUE
   pinMode(6, OUTPUT);

  //timer
  Timer1.initialize(1000); //Inicializa o Timer e configura para um período de 0.001s
  Timer1.attachInterrupt(callback); //garante que a função demore 0.001s 
  
}


void callback()
{
  //leitura set_point
  set_point = analogRead(A1);
  set_point = set_point/1023 * 5;
  //Serial.println("Leitura Analog Discovery");
  //Serial.println(set_point); 

  saida = analogRead(A0);
  saida = saida/1023 * 5;
  //Serial.println("Leitura Saida");
  //Serial.println(saida); 

  //Serial.println("Leitura erro");
  //Serial.println(erro); 

  //setup dos erros
  erro_2 = erro_1;
  erro_1 = erro;
  
  erro = set_point - saida;

    
  //setup das saidas
  sinalcontrol_2 = sinalcontrol_1;
  sinalcontrol_1 = sinalcontrol;

  //função discretizada (entradas passadas e saidas passadas) - Saida = entrada G(S)
  //saida= 46.04*erro - 86.31*erro_1 + 40.33*erro_2 + 1.927*saida_1 - 0.9273*saida_2;
  //saida = erro*20.24 - erro_1 * 40.08 + erro_2 * 19.84 + saida_1 * 1.979 - saida_2 * 0.979;
  sinalcontrol = erro*39.25 - erro_1 * 76.33 + erro_2 * 37.1 + sinalcontrol_1 * 1.935 - sinalcontrol_2 * 0.9355;
  Serial.println(sinalcontrol);


  //saida = set_point;
  //saida = constrain(saida,0,255);

  sinalcontrol_norma = sinalcontrol * 255/5; 


   if(sinalcontrol_norma > 255 )
   {
    sinalcontrol = 5;
    sinalcontrol_norma = 2.5 * 255 / 5;
   }
   if(sinalcontrol_norma <0 )
   {
    sinalcontrol = 0;
    sinalcontrol_norma = 2.5 * 255 / 5; 
   }
 
  //PWM
  //analogWrite(6,set_point * 255 /5);//malha aberta
  analogWrite(porta_pwm, sinalcontrol_norma);
  //Serial.println("Saida Controlador");
  //Serial.println(saida); 


}



void loop() {
  // put your main code here, to run repeatedly:
  
}
