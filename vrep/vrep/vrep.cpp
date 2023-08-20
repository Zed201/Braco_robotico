#define PI 3.14
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern "C" {
#include "extApi.h"
}

simxFloat Graus_Rad(float x) {
    return (x * PI) / 180;
}
void MJ(simxInt clientID, int Junta, float graus) {
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
    int juntaAux = 0;
    simxGetObjectHandle(clientID, juntas[Junta - 1], &juntaAux, (simxInt)simx_opmode_oneshot_wait);
    simxSetJointTargetPosition(clientID, juntaAux, Graus_Rad(graus), (simxInt)simx_opmode_oneshot_wait);
}
void Zerar(simxInt ClientId) {
    // ver uma posicao diferente para zerar e ter como base
    for (int x = 1; x <= 6; x++) {
        MJ(ClientId, x, 0);
    }
}
int main(int argc, char* argv[])
{

    //variavei para handler das juntas
    int junta1 = 0, junta2 = 0, junta3 = 0, junta4 = 0, junta5 = 0, junta6 = 0;

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
    /*simxGetObjectHandle(clientID, "/NiryoOne/Joint", &junta1, (simxInt)simx_opmode_oneshot_wait);
    simxGetObjectHandle(clientID, "/NiryoOne/Joint/Link/Joint", &junta2, (simxInt)simx_opmode_oneshot_wait);
    simxGetObjectHandle(clientID, "/NiryoOne/Joint/Link/Joint/Link/Joint", &junta3, (simxInt)simx_opmode_oneshot_wait);
    simxGetObjectHandle(clientID, "/NiryoOne/Joint/Link/Joint/Link/Joint/Link/Joint", &junta4, (simxInt)simx_opmode_oneshot_wait);
    simxGetObjectHandle(clientID, "/NiryoOne/Joint/Link/Joint/Link/Joint/Link/Joint/Link/Joint", &junta5, (simxInt)simx_opmode_oneshot_wait);
    simxGetObjectHandle(clientID, "/NiryoOne/Joint/Link/Joint/Link/Joint/Link/Joint/Link/Joint/Link/Joint", &junta6, (simxInt)simx_opmode_oneshot_wait)*/;
    //    extApi_sleepMs(2000);

    //}
    // mexer para direta ou esquerda
    // Junta2 deve ter angulo negativo, cima e baixo 
    // junta3 deve ser postiva e bem pouco concertar um pouco o angulo da junta2
    // junta4 nem mexe
    // junta5 nem mexe
    // junta6 nem mexe
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
    /*int juntasN = 5;
    int juntaAux = 0;
    simxGetObjectHandle(clientID, juntas[juntasN - 1], &juntaAux, (simxInt)simx_opmode_oneshot_wait);
    simxSetJointTargetPosition(clientID, juntaAux, Graus_Rad(0), (simxInt)simx_opmode_oneshot_wait);*/
        printf("Iniciando\n");
        Zerar(clientID);
        extApi_sleepMs(6000);
        MJ(clientID, 1, -11);
        MJ(clientID, 2, -63);
        MJ(clientID, 5, 100);
        MJ(clientID, 2, -67);
        extApi_sleepMs(500);
        MJ(clientID, 5, 67);
        MJ(clientID, 3, 2);
        MJ(clientID, 4, 0);
        MJ(clientID, 6, 0);
        
        
    // Fecha a conexao 
    simxFinish(clientID);

    return(0);
}
