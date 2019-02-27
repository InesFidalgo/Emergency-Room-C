#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "test.h"

List cria_lista(void){
    List lista;
    lista = (List) malloc(sizeof(List_node));
    if(lista != NULL){
        lista->info.id = 0;
        //protecção id nao pode ser 0
        lista->next=NULL;
    }
    return lista;
}


/*adicionar*/
List admite_triagem(List triagem,List verde,List laranja, List vermelho){
    char nome[TAM_NOME];
    long id, data1, data2;
    int hora,minuto,mes,dia,ano;
    List novo;
    List aux = triagem;
    novo = (List) malloc (sizeof(List_node));

    printf("Insira o nome:\n");
    fflush(stdin);
    fgets(nome, TAM_NOME, stdin);
    nome[strlen(nome)-1]='\0';
    while(verificanumeros(nome)==0){
        printf("Insira o nome:\n");
        fflush(stdin);
        fgets(nome, TAM_NOME, stdin);
        nome[strlen(nome)-1]='\0';
       }
    id = EscolhaID(triagem,verde,laranja,vermelho);
    fflush(stdin);
    printf("Insira a hora e data de chegada pela seguinte ordem: hora min dia mes ano\n");
    scanf("%d %d %d %d %d",&hora,&minuto,&dia,&mes,&ano);
    while(Protectdata(ano,mes,dia,hora,minuto) != 1){
        printf("Insira a hora e data de chegada pela seguinte ordem: hora min dia mes ano\n");
        scanf("%d %d %d %d %d",&hora,&minuto,&dia,&mes,&ano);
    }

    if (novo != NULL){

        strcpy(novo->info.nome,nome);
        novo->info.id = id;
        novo->info.d.hora = hora;
        novo->info.d.minuto = minuto;
        novo->info.d.dia = dia;
        novo->info.d.mes = mes;
        novo->info.d.ano = ano;

        //compara as datas para saber onde adicionar nos nós para ficar por ordem, mais antigo para recente
        data1 = (novo->info.d.ano * 100 + novo->info.d.mes) * 100 + (novo->info.d.dia * 100 + novo->info.d.hora) * 100 + novo->info.d.minuto;

        while(aux->next!=NULL){
            data2 = (aux->next->info.d.ano * 100 + aux->next->info.d.mes) * 100 + (aux->next->info.d.dia * 100 + aux->next->info.d.hora) * 100 + aux->next->info.d.minuto;
            if (data1 >= data2){
                aux=aux->next;
            }
             else{
                break;
            }
        }
        //só está a adicionar o último
        novo->next = aux->next;
        aux->next = novo;
        printf("PACIENTE ADICIONADO COM SUCESSO!!\n");
    }

}

List imprime_lista(List lista){
    List l = lista->next; /*vai directamente para o 2º elemento*/
    while(l){
        printf("Nome: %s\n",l->info.nome);
        printf("Id: %d\n",l->info.id);
        printf("Hora: %d Minutos: %d\n",l->info.d.hora, l->info.d.minuto);
        printf("Data de entrada: %d/%d/%d",l->info.d.dia,l->info.d.mes,l->info.d.ano);
        printf("\n");
        l=l->next;
    }
}

void cancelar_lista(List fila,long id){
    List l = fila->next;
    List ant = fila;
    while(l != NULL){
        if(l->info.id==id){
            ant->next = l->next;
            free(l);
            return;
        }
        ant = l;
        l = l->next;
    }
}

Doente procura_doente(List lista, long id){
    List lop = lista;
    while(lop){
        if (lop->info.id == id){
            return lop->info;
            }
            lop=lop->next;
    }
    return lista->info;
}



int Comparaid(List triagem, List verde, List laranja, List vermelho,long id){

    List aux = triagem;
    if(id!=0){
        while(aux!=NULL){
        if(aux->info.id==id){
            return 0;

        }
        else{
            aux = aux->next;
        }

    }

    aux = verde;
    while(aux!=NULL){
        if(aux->info.id==id){
            return 0;
        }
        else{
            aux = aux->next;
        }
    }

    aux= laranja;
    while(aux!=NULL){
        if(aux->info.id==id){
            return 0;
        }
        else{
            aux = aux->next;
        }

    }
    aux = vermelho;
    while(aux!=NULL){
        if(aux->info.id==id){
            return 0;
        }
        else{
            aux = aux->next;
        }

        }
    }

    return 1;
}

int Protectdata(int ano, int mes, int dia, int hora, int minuto)
{
    int res;
    if(ano < 2015 || dia > 31 || mes > 12 || dia <= 0 || mes <=0 || hora >= 24 || hora < 1 || minuto < 0 || minuto >59 )
    {
        printf("Data incorreta1\n");
        res = 1;
    }
	else if(mes==2 && dia>29)
    {
        printf("Data incorreta2\n");
        res= 1;
    }
	else if(mes==1 || mes==3 || mes==5 || mes==7 || mes==8 || mes==10 || mes==12)
    {
		if(dia>31)
        {
            printf("Data incorreta3\n");
            res= 1;
        }
        else
            res= 0;
	}
	else if (mes==4 || mes==6 || mes==9 || mes==11)
	{
		if(dia>30)
        {
            printf("Data incorreta4\n");
            res= 1;
        }
        else
            res= 0;
	}
	else
        res= 0;


    if(res==0){
        return 1;
    }
    else{
        return 0;
    }

}

List Escolha(List verde, List laranja, List vermelho){
    int opc;
    List cores;
    printf("Insira o tipo de consulta:\n1-verde\n2-laranja\n3-vermelho\n");
    scanf("%d", &opc);
    //fazer protecção

    if (opc==1){
        //vai adicionar à verde
        cores = verde;
    }
    else if(opc==2){
        cores = laranja;
    }
    else{
        cores = vermelho;
    }
    return cores;
}

long EscolhaID(List triagem, List verde, List laranja, List vermelho){
    char id[ID_MAX];
    int encontrou = 0;
    long idfinal;
    while(encontrou == 0){
        printf("Insira o id:\n");
        fgets(id,ID_MAX,stdin);
        if(verificaletras(id)==1){
            idfinal = atol(id);
            if(Comparaid(triagem,verde,laranja,vermelho,idfinal)==1){
                encontrou = 1;
            }
        }
    }
    return idfinal;
}

int verificaletras(char teste[]){
    int i;
    int tamanho = strlen(teste);
    for(i=0;i<tamanho;i++){
        if(teste[i] == '\n'){
            continue;
        }
        if (isdigit(teste[i]) == 0){
            return 0;
        }
    }
    //são todos digitos
    return 1;
}

int verificanumeros(char teste[]){
    int i;
    int tamanho = strlen(teste);
    for(i=0;i<tamanho;i++){
        //verifica se tem numeros e carateres estranhos
        if(isalpha(teste[i]) == 0){
            return 0;
        }
    }
    //só letras
    return 1;
}


List AtenderPacientes(List verde, List laranja, List vermelho, int cnt_laranja, int cnt_vermelho, List atendidos){
    List cores;

    if(cnt_vermelho<3 && (vermelho->next!=NULL)){
            cores = vermelho;
            adicionar_geral(cores,atendidos);
            cnt_vermelho+=1;
    }

    else if((vermelho->next == NULL) || (cnt_vermelho==3)){
        if((cnt_laranja<5) && (laranja->next !=NULL)){
            cores = laranja;
            adicionar_geral(cores,atendidos);
            cnt_laranja+=1;
        }
        else if((vermelho->next == NULL) && (laranja->next==NULL) && (verde->next==NULL)){
        printf("Nao ha pacientes prontos para serem atendidos");
        }

        else if((cnt_laranja==5) || (laranja->next==NULL)){
            if(verde->next!=NULL){
                cores = verde;
                adicionar_geral(cores,atendidos);
                cancelar_lista(verde,cores->info.id);
                cnt_laranja = 0;
            }
            else{
                 AtenderPacientes(verde,laranja,vermelho,cnt_laranja,cnt_vermelho,atendidos);
                }
        cnt_vermelho = 0;
            }
        }

}

List adicionar_geral(List inicial,List destino){
    List aux = inicial->next;
    int data1,data2;
    Doente novo;
    List nova;
    List aux2 = destino;


    //vais buscar o primeiro na lista e copia a sua info toda (first come first served), mas se não houver nada lá nada não faz nada
    if(aux!=NULL){
        strcpy(novo.nome,aux->info.nome);
        novo.id = aux->info.id;
        novo.d.hora = aux->info.d.hora;
        novo.d.minuto = aux->info.d.minuto;
        novo.d.dia = aux->info.d.dia;
        novo.d.mes = aux->info.d.mes;
        novo.d.ano = aux->info.d.ano;
        data1 = (novo.d.ano * 100 + novo.d.mes) * 100 + (novo.d.dia * 100 + novo.d.hora) * 100 + novo.d.minuto;
        while(aux2->next!=NULL){
            data2 = (aux2->next->info.d.ano * 100 + aux2->next->info.d.mes) * 100 + (aux2->next->info.d.dia * 100 + aux2->next->info.d.hora) * 100 + aux2->next->info.d.minuto;
            if (data1 >= data2){
                aux2=aux2->next;
            }
             else{
                break;
            }
        }
        //só está a adicionar o último
        nova = malloc(sizeof(List_node));
        nova->info = novo;
        nova->next = aux2->next;
        aux2->next = nova;

        //remove o id da lista de triagem
        cancelar_lista(inicial,aux->info.id);
        printf("ADICIONADO COM SUCESSO!!");
        }
    else{
        printf("nao está la ninguem");
    }

}

//função para eliminar listas
List eliminalista(List lista){
    List aux;
    while (lista!=NULL){
        aux = lista;
        lista = lista->next;
        free(aux);
    }
    free(lista);

}

List getno(int cnt, List lista){
    List l = lista;
    int i;
    for(i=0;i<cnt;i++){
        l = l->next;
    }
    return l;
}

void imprimeinverso(List lista){
    List l = lista->next;
    int cnt = 0;
    //vê o numero de elementos da lista
    while(l!=NULL){
        l = l->next;
        cnt+=1;

    }
    while(cnt!=0){
        //vai para essa posição
        l = getno(cnt,lista);
        printf("Nome: %s\n",l->info.nome);
        printf("Id: %d\n",l->info.id);
        printf("Hora: %d Minutos: %d\n",l->info.d.hora, l->info.d.minuto);
        printf("Data de entrada: %d/%d/%d",l->info.d.dia,l->info.d.mes,l->info.d.ano);
        printf("\n");
        cnt-=1;
        }
    }


//tem de ser ponteiro porque vai ser lido antes de correr o programa, senão não mudava os contadores
void FicheiroparaLista(List triagem,List verde,List laranja, List vermelho, List atendidos,int *cnt_vermelho, int *cnt_laranja) {
    int tipo;
    List aux;
    List aux2;
    char linha[100];
    FILE *file=fopen("Doentes.txt","r");
    if(file==NULL)
    {
        printf("O ficheiro Doentes.txt não existe, todas as listas estão vazias.\n");
        return;
    }
    fgets(linha,100,file);
    sscanf(linha,"%d %d\n", cnt_vermelho, cnt_laranja);
    while(fgets(linha,100,file))
   {
        aux = malloc(sizeof(List_node));
        aux->info.d.minuto = 10;
        sscanf(linha,"%d %[^0-9] %lu %d:%d %d/%d/%d\n",&tipo,aux->info.nome,&(aux->info.id), &(aux->info.d.hora), &(aux->info.d.minuto), &(aux->info.d.dia), &(aux->info.d.mes), &(aux->info.d.ano));
        aux->info.nome[strlen(aux->info.nome)-1] = '\0';
        if(tipo==0){
            aux2 = triagem;
        }
        else if(tipo==1){
            aux2 = verde;
        }
        else if(tipo==2){
            aux2 = laranja;
        }
        else if(tipo==3){
            aux2 = vermelho;
        }
        else if(tipo==4){
            aux2 = atendidos;
        }
        while(aux2->next!=NULL){
            aux2 = aux2->next;
        }

        aux->next = aux2->next;
        aux2->next = aux;

   }
}

void ListaparaFicheiro(List triagem,List verde,List laranja, List vermelho, List atendidos,int cnt_vermelho, int cnt_laranja){
    List aux = triagem->next;
    FILE *file=fopen("Doentes.txt","w");
    fprintf(file,"%d %d\n",cnt_vermelho,cnt_laranja);
    while (aux!=NULL){
        fprintf(file,"0 %s %lu %d:%d %d/%d/%d\n",&(aux->info.nome),aux->info.id,aux->info.d.hora,aux->info.d.minuto,aux->info.d.dia, aux->info.d.mes, aux->info.d.ano);
        aux = aux->next;
    }
    aux = verde->next;
    while (aux!=NULL){
        fprintf(file,"1 %s %lu %d:%d %d/%d/%d\n",&(aux->info.nome),aux->info.id,aux->info.d.hora,aux->info.d.minuto,aux->info.d.dia, aux->info.d.mes, aux->info.d.ano);
        aux = aux->next;
    }
    aux = laranja->next;
     while (aux!=NULL){
        fprintf(file,"2 %s %lu %d:%d %d/%d/%d\n",&(aux->info.nome),aux->info.id,aux->info.d.hora,aux->info.d.minuto,aux->info.d.dia, aux->info.d.mes, aux->info.d.ano);
        aux = aux->next;
    }
    aux = vermelho->next;
    while (aux!=NULL){
        fprintf(file,"3 %s %lu %d:%d %d/%d/%d\n",&(aux->info.nome),aux->info.id,aux->info.d.hora,aux->info.d.minuto,aux->info.d.dia, aux->info.d.mes, aux->info.d.ano);
        aux = aux->next;
    }
    aux = atendidos->next;
    while (aux!=NULL){
        fprintf(file,"4 %s %lu %d:%d %d/%d/%d\n",&(aux->info.nome),aux->info.id,aux->info.d.hora,aux->info.d.minuto,aux->info.d.dia, aux->info.d.mes, aux->info.d.ano);
        aux = aux->next;
    }
}
