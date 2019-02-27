#include <stdio.h>
#include <stdlib.h>
#include "test.h"

int main()
{
    List triagem,verde, laranja, vermelho,atendidos;
    int cnt_laranja, cnt_vermelho;
    triagem = cria_lista();
    verde = cria_lista();
    laranja = cria_lista();
    vermelho = cria_lista();
    atendidos = cria_lista();
    FicheiroparaLista(triagem,verde,laranja,vermelho,atendidos,&cnt_vermelho,&cnt_laranja);
    Menuinicial(triagem,verde,laranja,vermelho,atendidos,cnt_vermelho,cnt_laranja);
    ListaparaFicheiro(triagem,verde,laranja,vermelho,atendidos,cnt_vermelho,cnt_laranja);
    eliminalista(triagem);
    eliminalista(verde);
    eliminalista(laranja);
    eliminalista(vermelho);
    eliminalista(atendidos);
    return 0;
}

int Menuinicial(List triagem, List verde, List laranja, List vermelho, List atendidos, int cnt_vermelho, int cnt_laranja){
    int op,op2;
    char opchar[3];
    List cores;


    printf("-----------\n");
    printf(" URGENCIAS:  \n");
    printf("-----------\n");
    printf("1 - Adicionar a Lista de triagem\n");
    printf("2 - Atribuir Prioridade\n");
    printf("3 - Procurar Paciente\n");
    printf("4 - Atender Paciente\n");
    printf("5 - Listar Triagem\n");
    printf("6 - Listar por Prioridade Normal\n");
    printf("7 - Listar por Prioridade Inversa\n");
    printf("8 - Listar clientes ja atendidos\n");
    printf("9 - Cancelar Triagem\n");
    printf("10 - Cancelar Consulta\n");
    printf("11 - Sair\n");
    printf("\n\nA sua opçao: \n");

    fgets(opchar,3,stdin);
    fflush(stdin);
    if(verificaletras(opchar)==1){
        op = atoi(opchar);

        if (op==1){
            admite_triagem(triagem,verde,laranja,vermelho);
            printf("\n1 - Voltar ao Menu\n");
            printf("2 - Sair\n");
            scanf("%d",&op2);
            if(op2==1){
                Menuinicial(triagem,verde,laranja,vermelho,atendidos,cnt_vermelho, cnt_laranja);
            }
            else{
                return 0;
            }
        }

        else if (op ==2){
            fflush(stdin);
            cores = Escolha(verde,laranja,vermelho);
            adicionar_geral(triagem,cores);
            printf("\n1 - Voltar ao Menu\n");
            printf("2 - Sair\n");
            scanf("%d",&op2);
            if(op2==1){
                Menuinicial(triagem,verde,laranja,vermelho,atendidos,cnt_vermelho, cnt_laranja);

            }
            else{
                return 0;
            }
        }

       else if (op==3){
            int move2;
            Doente novo;
            printf("insira o id do paciente que pretende procurar: \n");
            scanf("%d",&move2);
            novo = procura_doente(triagem,move2);
            //retorna o cabeçalho se não encontrar
            if(novo.id == 0){
                novo = procura_doente(verde,move2);
                if(novo.id == 0){
                    novo = procura_doente(laranja,move2);
                    if(novo.id==0){
                        novo = procura_doente(vermelho,move2);
                        if(novo.id!=0){
                             printf("vermelho:\nNome: %s\nID: %lu\nh:m: %d:%d\nData: %d:%d:%d\n",novo.nome,novo.id,novo.d.hora, novo.d.minuto,novo.d.dia,novo.d.mes,novo.d.ano);

                        }
                        else{
                            printf("Esse paciente não existe!!");
                        }
                    }
                    else{
                        printf("laranja:\nNome: %s\nID: %lu\nh:m: %d:%d\nData: %d:%d:%d\n",novo.nome,novo.id,novo.d.hora, novo.d.minuto,novo.d.dia,novo.d.mes,novo.d.ano);
                    }
                }
                else{
                     printf("verde:\nNome: %s\nID: %lu\nh:m: %d:%d\nData: %d:%d:%d\n",novo.nome,novo.id,novo.d.hora, novo.d.minuto,novo.d.dia,novo.d.mes,novo.d.ano);
                }
            }
            else{
                 printf("triagem:\nNome: %s\nID: %lu\nh:m: %d:%d\nData: %d:%d:%d\n",novo.nome,novo.id,novo.d.hora, novo.d.minuto,novo.d.dia,novo.d.mes,novo.d.ano);
            }

            printf("\n1 - Voltar ao Menu\n");
            printf("2 - Sair\n");
            scanf("%d",&op2);
            if(op2==1){
                Menuinicial(triagem,verde,laranja,vermelho,atendidos,cnt_vermelho, cnt_laranja);
            }
            else{
                return 0;
            }
        }

        else if (op==4){
            AtenderPacientes(verde,laranja,vermelho,cnt_laranja,cnt_vermelho,atendidos);
            printf("\n1 - Voltar ao Menu\n");
            printf("2 - Sair\n");
            scanf("%d",&op2);
            if(op2==1){
                Menuinicial(triagem,verde,laranja,vermelho,atendidos,cnt_vermelho, cnt_laranja);
            }
            else{
                return 0;
            }
    }


       else if (op==5){
            imprime_lista(triagem);
            printf("\n1 - Voltar ao Menu\n");
            printf("2 - Sair\n");
            scanf("%d",&op2);
            if(op2==1){
                Menuinicial(triagem,verde,laranja,vermelho,atendidos,cnt_vermelho, cnt_laranja);
            }
            else{
                return 0;
            }
        }

      else  if(op==6){
            printf("verdes:\n");
            imprime_lista(verde);
            printf("\nlaranja:\n");
            imprime_lista(laranja);
            printf("\nvermelhos:\n");
            imprime_lista(vermelho);
            printf("\n1 - Voltar ao Menu\n");
            printf("2 - Sair\n");
            scanf("%d",&op2);
            if(op2==1){
                Menuinicial(triagem,verde,laranja,vermelho,atendidos,cnt_vermelho, cnt_laranja);
            }
            else{
                return 0;
                }
            }
        else if (op == 7){
            printf("verdes:\n");
            imprimeinverso(verde);
            printf("\nlaranja:\n");
            imprimeinverso(laranja);
            printf("\nvermelhos:\n");
            imprimeinverso(vermelho);
            printf("\n1 - Voltar ao Menu\n");
            printf("2 - Sair\n");
            scanf("%d",&op2);
            if(op2==1){
                Menuinicial(triagem,verde,laranja,vermelho,atendidos,cnt_vermelho, cnt_laranja);
            }
            else{
                return 0;
            }
        }
        else if (op == 8){
            imprime_lista(atendidos);
            printf("\n1 - Voltar ao Menu\n");
            printf("2 - Sair\n");
            scanf("%d",&op2);
            if(op2==1){
                Menuinicial(triagem,verde,laranja,vermelho,atendidos,cnt_vermelho, cnt_laranja);
            }
            else{
                return 0;
            }
        }
        else if (op == 9){
            long id;
            char idar[ID_MAX];
            printf("insira o id:\n");
            fgets(idar,ID_MAX,stdin);
            while(verificaletras(idar)==0){
                printf("insira o id:\n");
                fgets(idar,ID_MAX,stdin);
            }
            id = atol(idar);
            cancelar_lista(triagem,id);
            printf("\n1 - Voltar ao Menu\n");
            printf("2 - Sair\n");
            scanf("%d",&op2);

            if(op2==1){
                Menuinicial(triagem,verde,laranja,vermelho,atendidos,cnt_vermelho, cnt_laranja);
            }
            else{
                return 0;
            }
        }

         else if (op == 10){
            long id;
            char idar[ID_MAX];
            cores = Escolha(verde,laranja,vermelho);
            printf("insira o id:\n");
            fflush(stdin);
            fgets(idar,ID_MAX,stdin);
            while(verificaletras(idar)==0){
                printf("insira o id:\n");
                fgets(idar,ID_MAX,stdin);
            }
            id = atol(idar);
            fflush(stdin);
            cancelar_lista(cores,id);
            printf("\n1 - Voltar ao Menu\n");
            printf("2 - Sair\n");
            scanf("%d",&op2);


            if(op2==1){
                Menuinicial(triagem,verde,laranja,vermelho,atendidos,cnt_vermelho, cnt_laranja);
            }
            else{
                return 0;
            }
        }
        else if(op == 11){
            return 0;
        }

        else{//se forem numeros
            Menuinicial(triagem,verde,laranja,vermelho,atendidos,cnt_vermelho, cnt_laranja);
        }

    }
    else{
        printf("Insira uma opção válida!\n");
        Menuinicial(triagem,verde,laranja,vermelho,atendidos,cnt_vermelho, cnt_laranja);

    }


}



