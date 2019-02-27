#ifndef test_H_INCLUDED
#define test_H_INCLUDED
#define TAM_NOME 40
#define ID_MAX 9

typedef struct data{
    int ano;
    int mes;
    int dia;
    int hora;
    int minuto;
}Data;

typedef struct doente{
    char nome[TAM_NOME];
    long id;
    struct data d;
}Doente;

typedef struct lnode *List;
typedef struct lnode {
    Doente info;
    List next;
} List_node;


int main();
int Menuinicial(List triagem, List verde, List laranja, List vermelho,List atendidos, int cnt_vermelho, int cnt_laranja);
int Protectdata(int ano, int mes, int dia, int hora, int minuto);
int Comparaid(List triagem, List verde, List laranja, List vermelho,long id);
List cria_lista(void);
List admite_triagem(List triagem,List verde,List laranja, List vermelho);
List imprime_lista(List lista);
void cancelar_lista(List fila,long id);
Doente procura_doente(List lista, long id);
long EscolhaID(List triagem, List verde, List laranja, List vermelho);
List AtenderPacientes(List verde, List laranja, List vermelho, int cnt_laranja, int cnt_vermelho, List atendidos);
List adicionar_geral(List inicial,List destino);
List eliminalista(List lista);
void ListaparaFicheiro(List triagem,List verde,List laranja, List vermelho, List atendidos,int cnt_vermelho,int cnt_laranja);
void FicheiroparaLista(List triagem,List verde,List laranja, List vermelho, List atendidos,int *cnt_vermelho,int *cnt_laranja);
List Escolha(List verde, List laranja, List vermelho);
List getno(int cnt, List lista);
void imprimeinverso(List lista);


#endif // ER_H_INCLUDED
