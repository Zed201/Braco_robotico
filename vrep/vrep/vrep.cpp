#define PI 3.14
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern "C" {
#include "extApi.h"
}
// Funcao simples so para converter graus em Radiano
simxFloat Graus_Rad(float x) {
    return (x * PI) / 180;
}
// Funcao responsavel por mover determinada juntar
void MJ(simxInt clientID, int Junta, float graus) {
    // Handlers de cada junta(o path para cada junta); As comentadas sao as do primeiro exemplo, que tem so um robo
    char juntas[6][82] = {
        "/base_link_respondable[0]/joint_1",
        "/base_link_respondable[0]/joint_2",
        "/base_link_respondable[0]/joint_3",
        "/base_link_respondable[0]/joint_4",
        "/base_link_respondable[0]/joint_5",
        "/base_link_respondable[0]/joint_6",
        //"/NiryoOne/Joint",
        //"/NiryoOne/Joint/Link/Joint",
        //"/NiryoOne/Joint/Link/Joint/Link/Joint",
        //"/NiryoOne/Joint/Link/Joint/Link/Joint/Link/Joint",
        //"/NiryoOne/Joint/Link/Joint/Link/Joint/Link/Joint/Link/Joint",
        //"/NiryoOne/Joint/Link/Joint/Link/Joint/Link/Joint/Link/Joint/Link/Joint"
    };
    // Comandos para mover a juntar especificada
    int juntaAux = 0;
    simxGetObjectHandle(clientID, juntas[Junta - 1], &juntaAux, (simxInt)simx_opmode_oneshot_wait);
    simxSetJointTargetPosition(clientID, juntaAux, Graus_Rad(graus), (simxInt)simx_opmode_oneshot_wait);
}
// Funcoes de cada botao, com os angulos que eu testei para ver se dava certo, 1 a 9 esta dando certo, mas pode receber mais refino, os outros ainda precisa acertar
void Mum(simxInt ClientID) {
    MJ(ClientID, 1, -11);
    MJ(ClientID, 5, 76);
    extApi_sleepMs(800);
    MJ(ClientID, 2, -67);
}
void Mdois(simxInt ClientID) {
    MJ(ClientID, 1, -15);
    MJ(ClientID, 5, 72);
    extApi_sleepMs(800);
    MJ(ClientID, 2, -66);
}
void Mtres(simxInt ClientID) {
    MJ(ClientID, 1, -18.3);
    MJ(ClientID, 5, 58);
    extApi_sleepMs(800);
    MJ(ClientID, 2, -61.5);
}
void Mquatro(simxInt ClientID) {
    MJ(ClientID, 1, -12);
    MJ(ClientID, 5, 89);
    extApi_sleepMs(800);
    MJ(ClientID, 2, -74);
}
void Mcinco(simxInt ClientID) {
    MJ(ClientID, 1, -15);
    MJ(ClientID, 5, 85);
    extApi_sleepMs(800);
    MJ(ClientID, 2, -73);
}
void Mseis(simxInt ClientID) {
    MJ(ClientID, 1, -19);
    MJ(ClientID, 5, 74.6);
    extApi_sleepMs(800);
    MJ(ClientID, 2, -69);
}
void Msete(simxInt ClientID) {
    MJ(ClientID, 1, -12.5);
    MJ(ClientID, 3, -4.5);
    MJ(ClientID, 5, 90.5);
    extApi_sleepMs(800);
    MJ(ClientID, 2, -81);
}
void Moito(simxInt ClientID) {
    MJ(ClientID, 1, -16);
    MJ(ClientID, 3, -4.5);
    MJ(ClientID, 5, 86);
    extApi_sleepMs(800);
    MJ(ClientID, 2, -73);
}
void Mnove(simxInt ClientID) {
    MJ(ClientID, 1, -20);
    MJ(ClientID, 5, 86);
    extApi_sleepMs(800);
    MJ(ClientID, 2, -75);
}
void Mzero(simxInt ClientID) {
    MJ(ClientID, 2, -30);
    MJ(ClientID, 1, -17.5);
    MJ(ClientID, 3, -16);
    MJ(ClientID, 5, 100);
    extApi_sleepMs(800);
    MJ(ClientID, 2, -63);
    extApi_sleepMs(1200);
    MJ(ClientID, 5, 68);
}
void MBranco(simxInt ClientID) {
    MJ(ClientID, 2, -30);
    MJ(ClientID, 1, -12.5);
    MJ(ClientID, 3, -16);
    MJ(ClientID, 5, 100);
    extApi_sleepMs(800);
    MJ(ClientID, 2, -70);
    extApi_sleepMs(1200);
    MJ(ClientID, 5, 84);
}
void MCorrige(simxInt ClientID) {
    MJ(ClientID, 2, -30);
    MJ(ClientID, 1, -17.5);
    MJ(ClientID, 3, -16);
    MJ(ClientID, 5, 100);
    extApi_sleepMs(800);
    MJ(ClientID, 2, -69);
    extApi_sleepMs(1200);
    MJ(ClientID, 5, 80);
}
void MConfirma(simxInt ClientID) {
    MJ(ClientID, 2, -30);
    MJ(ClientID, 1, -22.6);
    MJ(ClientID, 3, -16);
    MJ(ClientID, 5, 100);
    extApi_sleepMs(800);
    MJ(ClientID, 2, -64);
    extApi_sleepMs(1200);
    MJ(ClientID, 5, 64);
}
// Funcao para colocar todos os angulos em zero
void Zerar(simxInt ClientId) {
    for (int x = 1; x <= 6; x++) {
        MJ(ClientId, x, 0);
    }
}
// Um ponto médio arbitrario apenas para nao zerar sempre dps de digitar um numero(essa movimentacao parece que nao bate em nada)
void medio(simxInt ClienteID) {
    MJ(ClienteID, 5, 100);
    extApi_sleepMs(500);
    MJ(ClienteID, 1, -17);
    extApi_sleepMs(500);
    MJ(ClienteID, 2, -60);
    MJ(ClienteID, 3, 0);
}

int main(int argc, char* argv[]){
    // Simplesmente pega os votos
        FILE* arq = NULL;
        arq = fopen("votos.txt", "r");
        char nome[100], votos[5][6];
        fscanf(arq, "%99[^','], %s %s %s %s %s", nome, votos[0], votos[1], votos[2], votos[3], votos[4]);
    //conecta com o coppelia
    int clientID = simxStart((simxChar*) "127.0.0.1", 19999, true, true, 2000, 5);
    extApi_sleepMs(500);
    //verifica conexao com simulador
    if (clientID == -1) {
        printf("Erro conectando ao Coppelia!\n");
        return 0;
    } else {
        printf("Conectado ao Coppelia!\n");
    }
    // Sistema de debug, tem as opcoes tando de ajustar a angulacao de cada junta como chamadas de funcoes para cada tecla(ainda por terminar os utlimos)
    // As funcos Mum, Mdois... sao para direcionar para clicar nos numeros e botoes correspondentes
    // No swicth as funcoes estao com a "escolha" meio estraha, mas e para representar, como 11 e Mum, 22 e Mdois...
    Zerar(clientID);
    extApi_sleepMs(3000);
    printf("Eleitor %s\n", nome);
    for (int i = 0; i < 5; i++)
    {
        printf("Voto a ser digitado %s\n", votos[i]);
        medio(clientID);
        extApi_sleepMs(2000);
        for (int z = 0; z < strlen(votos[i]); z++) {
            medio(clientID);
            
            if (votos[i][z] == '1')
            {
                Mum(clientID);
                extApi_sleepMs(2500);
            } else if (votos[i][z] == '2')
            {
                Mdois(clientID);
                extApi_sleepMs(2500);
            } else if (votos[i][z] == '3')
            {
                Mtres(clientID);
                extApi_sleepMs(2500);
            } else if (votos[i][z] == '4')
            {
                Mquatro(clientID);
                extApi_sleepMs(2500);
            }
            else if (votos[i][z] == '5')
            {
                Mcinco(clientID);
                extApi_sleepMs(2500);
            }
            else if (votos[i][z] == '6')
            {
                Mseis(clientID);
                extApi_sleepMs(2500);
            } else if (votos[i][z] == '7')
            {
                Msete(clientID);
                extApi_sleepMs(2500);
            }
            else if (votos[i][z] == '8')
            {
                Moito(clientID);
                extApi_sleepMs(2500);
            }
            else if (votos[i][z] == '9')
            {
                Mnove(clientID);
                extApi_sleepMs(2500);
            }
            else if (votos[i][z] == '0')
            {
                Mzero(clientID);
                extApi_sleepMs(3000);
            }
            medio(clientID);
        }
        extApi_sleepMs(2000);
        MConfirma(clientID);
        extApi_sleepMs(3000);
    }
    //int escolha = -1;
    //float junta1 = 0, junta2 = 0, junta3 = 0, junta4 = 0, junta5 = 0, junta6 = 0;
    //while (scanf("%d", &escolha) != EOF){
    //    switch (escolha){
    //    case 1:
    //        scanf("%f", &junta1);
    //        MJ(clientID, 1, junta1);
    //        break;
    //    case 2:
    //        scanf("%f", &junta2);
    //        MJ(clientID, 2, junta2);
    //        break;
    //    case 3:
    //        scanf("%f", &junta3);
    //        MJ(clientID, 3, junta3);
    //        break;
    //    case 4:
    //        scanf("%f", &junta4);
    //        MJ(clientID, 4, junta4);
    //        break;
    //    case 5:
    //        scanf("%f", &junta5);
    //        MJ(clientID, 5, junta5);
    //        break;
    //    case 6:
    //        scanf("%f", &junta1);
    //        MJ(clientID, 6, junta6);
    //        break;
    //    case 0:
    //        junta1 = 0, junta2 = 0, junta3 = 0, junta4 = 0, junta5 = 0, junta6 = 0;
    //        Zerar(clientID);
    //        break;
    //    case 7:
    //        medio(clientID);
    //        break;
    //    case 11:
    //        Mum(clientID);
    //        break;
    //    case 22:
    //        Mdois(clientID);
    //        break;
    //    case 33:
    //        Mtres(clientID);
    //        break;
    //    case 44:
    //        Mquatro(clientID);
    //        break;
    //    case 55:
    //        Mcinco(clientID);
    //        break;
    //    case 66:
    //        Mseis(clientID);
    //        break;
    //    case 77:
    //        Msete(clientID);
    //        break;
    //    case 88:
    //        Moito(clientID);
    //        break;
    //    case 99:
    //        Mnove(clientID);
    //        break;
    //    case 100:
    //        Mzero(clientID);
    //        break;
    //    case 101:
    //        MBranco(clientID);
    //        break;
    //    case 102:
    //        MCorrige(clientID);
    //        break;
    //    case 103:
    //        MConfirma(clientID);
    //        break;
    //    }
    //   /* extApi_sleepMs(2000);
    //    medio(clientID);*/
    //    // No fim ele printa as angulacos de cada junta para o debug
    //    printf("1- %.1f | 2- %.1f | 3- %.1f | 4- %.1f | 5- %.1f | 6- %.1f\n\n", junta1, junta2, junta3, junta4, junta5, junta6);
    //    extApi_sleepMs(200);
    //}
    // Fecha a conexao 
    simxFinish(clientID);
    
    return(0);
}
