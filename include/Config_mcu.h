
/********************************Função que configura Pinos do MCU**************************************

                                   configuração para placa Mega ADK

********************************************************************************************************/
/*******************************************************************************************************/
                                      /* Arquivos de inclusão */

#ifndef Config_mcu_h_
#define Config_mcu_h_
               
               
// ======================================================================================================
// --- Protótipo das Funções ---

void       Config_mcu ();
void Supervisionamento(); 
void       comunicacao();

             void draw();             //função para desenho de string
  void disp_graph_init();             //função de inicialização do display
 void Comunicacao_Oled();

        void disp_umid();
        void disp_temp();

#endif