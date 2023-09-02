/************************************************************************************************************

                                      configurações Mega ADK
************************************************************************************************************/

                                   /* Arquivos de Bibliotecas */

 // ========================================================================================================
// --- Bibliotecas Auxiliares --- //


#include <Adafruit_GFX.h>
#include <Adafruit_BusIO_Register.h>
#include <TCA9548A.h>
#include <LiquidCrystal_I2C.h>
#include <Adafruit_SSD1306.h>
#include <U8glib-HAL.h>


/**********************************************************************************************************/
                                        /* Arquivos de inclusão */


#include "Config_mcu.h"

TCA9548A I2CMux;                            // Address can be passed into the constructor


// ========================================================================================================
//                                   --- Definições e Objetos ---
 
#define buttonPin 41 // numero do pino onde o botao esta conectado
  
  


boolean buttonState;             // estado atual do botao
boolean lastButtonState = LOW;   // valor da ultima leitura do botao
boolean ledState = HIGH;         // estado atual do LED

// as variaveis a seguir sao do tipo long por conta que o tempo, medido 
// em milessegundos alcancara rapidamente um numero grande demais para 
// armazenar em uma variavel do tipo int
unsigned long lastDebounceTime = 0;  // tempo da ultima modificacao do estado do LED

// tempo de debounce; aumentar se o LED oscilar; espera-se que o LED acenda
// apenas se o botao for pressionado por mais de 50ms
unsigned long debounceDelay = 2;    

#define ledpin_MEGA_ADK    13                  // numero do pino onde o LED Verde supervisionamento do funcionamento do codigo

#define slaveAdress     0x07                   // ESP32

#define i2clcd       0                         // Display Lcd
#define i2cOled      1                         // Display Oled
#define i2cESP32     2






#define usalcd       I2CMux.openChannel(i2clcd)
#define usaOled     I2CMux.openChannel(i2cOled)
#define usaESP32   I2CMux.openChannel(i2cESP32)



#define OLED_RESET   3
Adafruit_SSD1306 display(OLED_RESET);               // configura tela de Oled

LiquidCrystal_I2C lcd(0x27,20,4);                   // set the LCD address to 0x27 for a 16 chars and 2 line display
 
U8GLIB_ST7920_128X64_1X u8g( 6,  //E
                             5,  //R/W
                             4,  //RS
                             7); //RST

void Config_mcu()
{
     
                                                    Wire.begin(); 
                                            Serial.begin(115200);
                                              I2CMux.begin(Wire);               // Wire instance is passed to the library                                             I2CMux.begin(Wire);               // Wire instance is passed to the library




                                                         usaESP32;
                                                       delay(100);
                                           I2CMux.closeChannel(2); 

                                                           usalcd;
                                                       lcd.init();
                                                      lcd.clear(); 
                                                  lcd.backlight();               
                                           I2CMux.closeChannel(0);

                                                           usalcd;
                                                      lcd.clear(); 
                                               lcd.setCursor(2,1);
                                    lcd.print("MRPRO TECNOLOGIA");
                                                       delay(200);
                                           I2CMux.closeChannel(0);                                           

                        display.begin(SSD1306_SWITCHCAPVCC, 0x3C);               // initialize with the I2C addr 0x3C (for the 128x64)
                                                      delay(3000);
                                           display.clearDisplay();

                                                          usaOled;
                        display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
                                           display.clearDisplay();
                                           I2CMux.closeChannel(1);          
 
                                                          usaOled;
                                           display.clearDisplay(); 
                                      display.setTextColor(WHITE);
                                          display.setCursor(25,1);
                                 display.println("Loja Saravati");
                                      display.setTextColor(WHITE);
                                         display.setCursor(25,15);
                                 display.println("Mestre Felipe");
                                                      delay(2000);
                                                display.display();
                                           I2CMux.closeChannel(1);
                                      
                                                           draw();                //função para desenho de string
                                                disp_graph_init();                //função de inicialização do display                                              

                                pinMode (ledpin_MEGA_ADK, OUTPUT);                // configura o pino do LED 13 como saida
                                digitalWrite(ledpin_MEGA_ADK,LOW);  


  // configura o pino do botao como entrada com resistor de pullup interno
                                 pinMode(buttonPin, INPUT_PULLUP);                             

}


// ======================================================================================================
// --- Função para desenho de strings ---
void draw() 
{
  
  u8g.setFont(u8g_font_unifont);
 
  u8g.drawStr( 0, 25, "MRPRO TECNOLOGIA");
  
} //end draw


// ======================================================================================================
// --- Função de inicialização do Display ---
void disp_graph_init()
{
  if ( u8g.getMode() == U8G_MODE_R3G3B2 ) {
    u8g.setColorIndex(255);     //branco
  }
  else if ( u8g.getMode() == U8G_MODE_GRAY2BIT ) {
    u8g.setColorIndex(3);         //máxima intensidade
  }
  else if ( u8g.getMode() == U8G_MODE_BW ) {
    u8g.setColorIndex(1);         // pixel on
  }
  else if ( u8g.getMode() == U8G_MODE_HICOLOR ) {
    u8g.setHiColorByRGB(255,255,255);
  }

    u8g.firstPage();  
  do {
                        draw();
     } while( u8g.nextPage() );
  
                    delay(100);

} //end disp_graph_init


// ======================================================================================================
// --- Função de Supervisionamento do programa ---

void Supervisionamento()
{
   
    


  //Acende o LED durante 1 segundo
  digitalWrite(ledpin_MEGA_ADK, HIGH);
  delay(1000);

  //Apaga o LED durante 1 segundo
  digitalWrite(ledpin_MEGA_ADK, LOW);
  delay(1000);

    
}


void comunicacao ()
{


   // le o estado do botao e salva em uma variavel local
  int reading = digitalRead(buttonPin);

  // verifica se voce apenas apertou o botao (i.e. se a entrada foi de LOW 
  // to HIGH), e se ja esperou tempo suficiente para ignorar qualquer ruido

  // se a entrada foi alterada devido ao ruido ou botao ter sido pressionado:
  if (reading != lastButtonState) {
    // reseta o tempo do debounce
    lastDebounceTime = millis();
  }
  
  if ((millis() - lastDebounceTime) > debounceDelay) {
    // qualquer que seja a leitura atual, ela se manteve por um tempo maior
    // que o nosso debounce delay, então atualizemos o estado atual:

    // se o estado do botao foi alterado:
    if (reading != buttonState) {
      buttonState = reading;

      // apenas altera o estado do LED se o novo estado do botao e HIGH
      if (buttonState == HIGH) {
        ledState = !ledState;
        // incia a transmissao para o endereco 0x07 (slaveAdress)
                                                              usaESP32;
                                   Wire.beginTransmission(slaveAdress);
                                                  Wire.write(ledState); // envia um byte contendo o estado do LED
                                                Wire.endTransmission(); // encerra a transmissao                      // pare de transmitir
                                                I2CMux.closeChannel(2); 
      }
    }
  }
  // salva a leitura. No proximo laco este sera o ultimo 
  // estado do botao (lastButtonState)
  lastButtonState = reading;
 
}