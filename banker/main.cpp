///ALGORITMO ADAPTADO DISPON�VEL EM https://www.geeksforgeeks.org/program-bankers-algorithm-set-1-safety-algorithm/

#include<iostream>
using namespace std;
/// NUMERO DE PROCESSOS
const int P = 6;
/// NUMERO DE RECURSOS
const int R = 3;

void calculateNeed(int precisa[P][R], int maxm[P][R], int alocado[P][R])
{
    ///CALCULA O QUANTO CADA PROCESSO PRECISA
    for (int i = 0 ; i < P ; i++)
        for (int j = 0 ; j < R ; j++)
            precisa[i][j] = maxm[i][j] - alocado[i][j];
}

///FUN��O PARA VERIFICAR SE � SEGURO
bool isSafe(int process[], int dispo[], int maxm[][R],
            int alocado[][R])
{
    int precisa[P][R];

    /// RETORNA A MATRIX PRECISA[PROCESSO][RECURSO]retorna a matrix precisa[P][R]
    calculateNeed(precisa, maxm, alocado);

    ///INICIAMOS UM VETOR PARA SABER SE J� VIMOS ESSE PROCESSO COM FALSO
    bool finish[P] = {0};
    ///OUTRO VETOR PARA GUARDAR A SEQU�NCIA SEGURA
    int safeSeq[P];
    ///VETOR PARA GUARDAR OS RECURSOS DISPON�VEIS
    int work[R];
    for (int i = 0; i < R ; i++)
        work[i] = dispo[i];


    int count = 0;
    while (count < P)
    {
        ///PRECISAMOS DE UMA VARI�VEL PARA VER SE O SISTEMA EVENTUALMENTE VAI CHEGAR NUMA SEQU�NCIA SEGURA
        bool found = false;
        ///ACHANDO UM PROCESSO QUE PRECISA DE RECURSO.
        for (int p = 0; p < P; p++)
        {
            ///SE O PROCESSO J� TEVE O RECURSO ATENDIDO, FINISH = 1, PULAMOS ESSE TRECHO
            if (finish[p] == 0)
            {
                ///CHECAMOS SE O QUE TEMOS DISPON�VEL PODE SUPRIR OS RECURSOS QUE O PROCESSO P PRECISA
                int j;
                for (j = 0; j < R; j++)
                    if (precisa[p][j] > work[j])
                        break;

                /// TENDO ATENDIDO AS NECESSIDADES DE P
                if (j == R)
                {
                    /// LIBERAMOS MAIS ESPA�OS PARA O VETOR DE RECURSOS DISPON�VEIS
                    for (int k = 0 ; k < R ; k++)
                        work[k] += alocado[p][k];

                    /// ADICIONAMOS ESSE PROCESSO NA SEQU�NCIA SEGURA
                    safeSeq[count++] = p;

                    ///ESSE P J� N�O VAI SER MAIS AVALIADO, SETAMOS FINISH PARA 1
                    finish[p] = 1;

                    found = true;
                }
            }
        }

        ///SE DEPOIS DE TODAS AS INTERA��ES ELE N�O CHEGAR NUMA SEQU�NCIA SEGURA
        if (found == false)
        {
            cout << "System is not in safe state";
            return false;
        }
    }

    /// CASO TENHA UMA SEQUENCIA SEGURA
    cout << "System is in safe state.\nSafe"
         " sequence is: ";
    for (int i = 0; i < P ; i++)
        cout << safeSeq[i] << " ";

    return true;
}

int main()
{
    int processes[] = {0, 1, 2, 3, 4, 5};
    int disponibilidade[] = {2, 2, 2};

    int maxm[][R] = {{5, 6, 2},
                     {3, 2, 2},
                     {9, 0, 2},
                     {2, 2, 2},
                     {4, 3, 3},
                     {3, 3, 3}};

    int alocado[][R] = {{0, 1, 0},
                        {2, 0, 0},
                        {3, 0, 2},
                        {2, 1, 1},
                        {0, 0, 2},
                        {0, 2, 3}};

    isSafe(processes, disponibilidade, maxm, alocado);

    return 0;
}
