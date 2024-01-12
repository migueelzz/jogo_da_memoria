#include <stdio.h> 
#include <stdlib.h>
#include <conio.h> 
#include <time.h>
#include <locale.h>
#include <windows.h>
#define MAX_NUMEROS 25 // Quantidade m�xima de n�meros aleat�rios

struct No{
	int valor; 					
	int linhaN;    	             
	int colunaN; 
	struct No *prox;
};
typedef struct No lista;


int numerosGerados[MAX_NUMEROS]; // Vetor para armazenar os n�meros gerados
int indice = 0; // �ndice gerar numero aleatorio
int posicaoLdefinida=0;//linha aleatoria escolhida
int posicaoCdefinida=0;//coluna aleatoria escolhida
int tamanhoLista=0;//definir o tamanho da matriz de acordo com a dificuldade

//mapeamento das teclas
enum 
{
	KEY_ESC     = 27,
    KEY_ENTER   = 13,
    ARROW_UP    = 256 + 72,
    ARROW_DOWN  = 256 + 80,
    ARROW_LEFT  = 256 + 75,
    ARROW_RIGHT = 256 + 77		
};


char menus[5][1000] = {
	"Jogar",
	"Como jogar?",
	"Sair do jogo"};
	
char menusDificuldade[5][1000] = {
"F�cil",
"M�dio",
"Dificil",
"Voltar"};

void generateMenu(int choice);
void generateMenuDificuldade(int choice);
void generateSobre();
void carregando();
void carregarJogo(int dificuldade);
void esolherNumero();
void tempoDecorarLista(int dificuldade);

void inicializarNumerosAleatorios() {
    // Inicializar a semente para a fun��o rand() usando o tempo atual
    srand((unsigned int)time(NULL));
}

int gerarNumeroAleatorio() {
    int novoNumero;
    int repetido;

    if (indice >= MAX_NUMEROS) {
        printf("Limite de n�meros atingido!\n");
        return -1; // Retorna -1 se atingir o limite m�ximo de n�meros gerados
    }

    do {
        repetido = 0; // Inicializa a vari�vel para indicar se o n�mero j� foi gerado

        // Gera um novo n�mero aleat�rio
        novoNumero = rand() % 100; // N�mero aleat�rio entre 0 e 99 (por exemplo)

        // Verifica se o n�mero j� foi gerado anteriormente
        for (int i = 0; i < indice; i++) {
            if (numerosGerados[i] == novoNumero) {
                repetido = 1; // Se for repetido, marca como verdadeiro
                break;
            }
        }
    } while (repetido);

    numerosGerados[indice] = novoNumero; // Armazena o novo n�mero no vetor
    indice++; // Incrementa o �ndice

    return novoNumero; // Retorna o n�mero aleat�rio gerado
}

void inicializa(lista *cartas)
{	
	cartas->prox = NULL;
}

int checa_lista(lista *cartas)
{
	if(cartas->prox == NULL) 
		return 1;
	else
		return 0;
}

void gerarCartas(lista *cartas,int linhaN, int colunaN)
{
	
	lista *novo = (lista *) malloc(sizeof(lista));
	if(!novo){
		printf("Impossivel alocar memoria \n");
		exit(1);
	}
	
	novo->valor = gerarNumeroAleatorio();
	novo->linhaN= linhaN;
	novo->colunaN= colunaN; 
	novo->prox = NULL;
	
	if(checa_lista(cartas)){
		cartas->prox = novo;
	}else{
		lista *aux = cartas->prox;
		while(aux->prox != NULL)
			aux = aux->prox;
		aux->prox = novo;
		
	}
	
		
}


void mostra_lista(lista *cartas)
{

	if(checa_lista(cartas))
	{
		printf("lista vazia \n");
		return ;
	}
	lista *aux = cartas->prox;
	int linha = aux->linhaN;
	
	if(tamanhoLista == 3){
		printf("\n\t\t\t\t\t   1\t 2\t 3");
	}
	
	if(tamanhoLista == 4){
		printf("\n\t\t\t\t\t   1\t 2\t 3\t 4");
	}
	
	if(tamanhoLista == 5){
		printf("\n\t\t\t\t\t   1\t 2\t 3\t 4\t 5");
	}
	
	
	printf("\n\t\t\t\t\t");
	printf("1 ");
	while(aux != NULL){
		if(linha != aux->linhaN){
			printf("\n\n\t\t\t\t\t");
			linha = aux->linhaN;
			printf("%d ", aux->linhaN);
		}
		
		if(aux->valor <= 9) {
			printf("[0%d]\t", aux->valor);
		} else {
			printf("[%d]\t", aux->valor);			
		}
		aux = aux->prox;
	}
	
}
	


void mostra_lista_escondido() {
	if(tamanhoLista == 3){
		printf("\n\t\t\t\t\t   1\t 2\t 3");
	}
	
	if(tamanhoLista == 4){
		printf("\n\t\t\t\t\t   1\t 2\t 3\t 4");
	}
	
	if(tamanhoLista == 5){
		printf("\n\t\t\t\t\t   1\t 2\t 3\t 4\t 5");
	}
	
	for(int l=1; l <= tamanhoLista; l++){
		printf("\n\t\t\t\t\t");
		for(int n=1; n <= tamanhoLista; n++){
			if(n == 1) {
				printf("%d ", l);
			}
			if(n == tamanhoLista) {
				
				printf("[X]\t");
				printf("\n");
			} else {
				printf("[X]\t");
			}
		}
	}
}

int esolherNumero(lista *cartas){
	 posicaoLdefinida = rand() % tamanhoLista+1;
	 posicaoCdefinida = rand() % tamanhoLista+1;
	 if(posicaoLdefinida == 0){
	 	 posicaoLdefinida++;
	 }
	 
	 if(posicaoCdefinida == 0){
	 	 posicaoCdefinida++;
	 }
	 
	if(checa_lista(cartas))
	{
		printf("erro lista vazia \n");
		return 0;
	}
	
	while(cartas->prox!= NULL){
		cartas = cartas->prox;
		if(cartas->colunaN == posicaoCdefinida && cartas->linhaN == posicaoLdefinida){
			return cartas->valor;
		}
	}
	printf("Error  \n");
getch();
	 
	 
	 
}

int verificarResposta(lista *cartas, int numeroE ){
	int respostaL, respostaC;
	printf("\n\t Linha: ");
	scanf("%d", &respostaL);
	
	printf("\n\t Coluna: ");
	scanf("%d", &respostaC);
	
	while(cartas->prox!= NULL){
	cartas = cartas->prox;
	if(cartas->colunaN == respostaC && cartas->linhaN == respostaL){
		if(cartas->valor == numeroE)
		return 1;
		
	}
	}
}

static int get_code(void)
{
    int ch = getch();
    if (ch == 0 || ch == 224)
        ch = 256 + getch();
    return ch;
}

void generateMenuDificuldade(int choice){
	system("cls");
	indice=0;
	int count;
	printf("\n\t ###################################################################################################");
	printf("\n\t ###################################################################################################");
	printf("\n\t ##\t\t\t\t\t  JOGO DA MEM�RIA \t\t\t\t\t  ##");
	printf("\n\t ###################################################################################################");
	printf("\n\t ###################################################################################################\n\n");
	printf("\n\t\t\t\t\t\tSELECIONE UMA OP��O:\n");
	for (count=0;count<3;count++){
		if(choice==count){
        	printf("\n\t\t\t\t\t\t[*] %s\n", menusDificuldade[count]);
		}else{
			printf("\n\t\t\t\t\t\t[ ] %s\n", menusDificuldade[count]);
		}
	}
	
	  int ch;
	  
	  while (( ch = get_code()) ){
        switch (ch)
        {
        case ARROW_UP:
            system("cls");
            if(choice>0){
            	choice=choice-1;
            }
           generateMenuDificuldade(choice);
            break;
        case ARROW_DOWN:
            system("cls");
            if(choice<2){
            	choice=choice+1;
            }
            generateMenuDificuldade(choice);
            break;
        case ARROW_LEFT:
            printf("LEFT\n");
            break;
        case ARROW_RIGHT:
            printf("RIGHT\n");
            break;
        case KEY_ENTER:
        	switch(choice){
        		case 0:
        			// F�cil
//				carregando();
				tamanhoLista =3;
				carregarJogo(5);
				
        			break;
        		case 1:
        			// M�dio
        			printf("medio");
//        			carregando();
					tamanhoLista=4;
        			carregarJogo(5);
        		
        			break;
        		case 2:
        			// Dificil
					printf("dificil");
//					carregando();
					tamanhoLista=5;
					carregarJogo(3);
					
        			break;
        		case 3:
        			// Voltar
        			generateMenu(0);
        			break;

        	}
        	break;
        }
    }	   
}

void generateMenu(int choice){
	setlocale(LC_ALL, "Portuguese");
	system("cls");
	int count;
	printf("\n\t ###################################################################################################");
	printf("\n\t ###################################################################################################");
	printf("\n\t ##\t\t\t\t\t  JOGO DA MEM�RIA \t\t\t\t\t  ##");
	printf("\n\t ###################################################################################################");
	printf("\n\t ###################################################################################################\n\n");
	printf("\n\t\t\t\t\t\tSELECIONE UMA OP��O:\n");
	for (count=0;count<3;count++){
		if(choice==count){
        	printf("\n\t\t\t\t\t\t[*] %s\n", menus[count]);
		}else{
			printf("\n\t\t\t\t\t\t[ ] %s\n", menus[count]);
		}
	}
    int ch;
    while (( ch = get_code()) != KEY_ESC ){
        switch (ch)
        {
        case ARROW_UP:
            system("cls");
            if(choice>0){
            	choice=choice-1;
            }
            generateMenu(choice);
            break;
        case ARROW_DOWN:
            system("cls");
            if(choice<2){
            	choice=choice+1;
            }
            generateMenu(choice);
            break;
        case ARROW_LEFT:
            printf("LEFT\n");
            break;
        case ARROW_RIGHT:
            printf("RIGHT\n");
            break;
        case KEY_ENTER:
        	switch(choice){
        		case 0:
        			// iniciar mmenu dificuldade
       			 generateMenuDificuldade(0);
        			break;
        		case 1:
        			// Sobre o jogo
        			generateSobre();
        			break;
        		case 2:
        			// Sair do jogo
        			printf("saindo....");
        			exit(0);
        			break;
        			break;
        		

        	}
        	break;
        }
    }	   
}

void generateSobre(){
	setlocale(LC_ALL, "Portuguese");
	system("cls");
	
	int count;
	
	
	printf("\n\n");
	printf("\n\t ###################################################################################################");
	printf("\n\t ##\t\t\t                   \t\t\t\t\t\t\t  ##");
	printf("\n\t ##\t\t\t\t\t  O QUE � O JOGO? \t\t\t\t\t  ##");
	printf("\n\t ##\t\t\t  O jogo da mem�ria constituido por uma matriz 4x4 \t\t\t  ##");
	printf("\n\t ##\t\t  Onde possui n�meros gerados aleatoriamente embaralhados na matriz. \t\t  ##");
	printf("\n\t ##\t\t\t                   \t\t\t\t\t\t\t  ##");
	printf("\n\t ###################################################################################################");
	printf("\n\t ##\t\t\t                   \t\t\t\t\t\t\t  ##");
	printf("\n\t ##\t\t\t\t\t  OBJTIVO  DO JOGO? \t\t\t\t\t  ##");
	printf("\n\t ##\t\t  Decorar onde est�o os n�meros e dizer qual � sua posi��o na matriz \t\t  ##");
	printf("\n\t ##\t\t\t\t  Seja rapido e decore suas posi��es! \t\t\t\t  ##");
	printf("\n\t ##\t\t\t                   \t\t\t\t\t\t\t  ##");
	printf("\n\t ###################################################################################################");
	printf("\n\t ##\t\t\t                   \t\t\t\t\t\t\t  ##");
	printf("\n\t ##\t\t\t\t\t  REGRAS DO JOGO \t\t\t\t\t  ##");
	printf("\n\t ##\t\t\t                   \t\t\t\t\t\t\t  ##");
	printf("\n\t ##\t\t\t\t\t  Como vencer? \t\t\t\t\t\t  ##");
	printf("\n\t ##\t\t Responda corretamente a posi��o onde se encontra o n�mero da carta \t\t  ##");
	printf("\n\t ##\t\t\t                   \t\t\t\t\t\t\t  ##");
	printf("\n\t ##\t\t\t\t     Niveis de Dificuldade \t\t\t\t\t  ##");
	printf("\n\t ##\t\t\t                   \t\t\t\t\t\t\t  ##");
	printf("\n\t ##\t\t\t  * Nivel: F�cil:\t\t\t\t\t\t\t  ##");
	printf("\n\t ##\t\t\t  -> tempo para decorar as cartas: 10 segundos\t\t\t\t  ##");
	printf("\n\t ##\t\t\t  -> N�mero de tentativas: 5 chances\t\t\t\t\t  ##");
	printf("\n\t ##\t\t\t                   \t\t\t\t\t\t\t  ##");
	printf("\n\t ##\t\t\t  * Nivel: M�dio:\t\t\t\t\t\t\t  ##");
	printf("\n\t ##\t\t\t  -> tempo para decorar as cartas: 7 segundos\t\t\t\t  ##");
	printf("\n\t ##\t\t\t  -> N�mero de tentativas: 3 chances\t\t\t\t\t  ##");
	printf("\n\t ##\t\t\t                   \t\t\t\t\t\t\t  ##");
	printf("\n\t ##\t\t\t  * Nivel: Dificil:\t\t\t\t\t\t\t  ##");
	printf("\n\t ##\t\t\t  -> tempo para decorar as cartas: 3 segundos\t\t\t\t  ##");
	printf("\n\t ##\t\t\t  -> N�mero de tentativas: 2 chances\t\t\t\t\t  ##");
	printf("\n\t ##\t\t\t                   \t\t\t\t\t\t\t  ##");
	printf("\n\t ###################################################################################################\n\n");
	
	printf("\n\t ##\t\t\tDesenvolvido por Miguel Lemes e Victor Samapaio. 2023 \t\t\t  ##");
	
	printf("\n\n\n\t Pressione qualquer tecla para continuar. . .");
	
	int ch;
	ch = get_code();
	if(ch = KEY_ENTER) {
		generateMenu(0);
	} 

}


void carregando(){
	
    for (int i = 0; i < 5; i++) {
        printf("Carregando  %d", i);
        for (int j = 0; j < 20; j++) {
            printf(".");
            Sleep(20);
        }
        printf("\r");
        for (int j = 0; j < 60; j++) {
            printf(" "); // apaga a linha anterior
        }
        printf("\r");
    }
 
}

void tempoDecorarLista(int dificuldade){
	printf("\n\n");
	for (int i = 0; i <= dificuldade+5; i++) {
        printf("\t  iniciando em: %d", i);
        for (int j = 0; j < 20; j++) {
//        	 printf(".");
            Sleep(20);
        }
       
        printf("\r");
        for (int j = 0; j < 60; j++) {
            printf(" "); // apaga a linha anterior
        }
        printf("\r");
    }
}

void menuBase(){
	printf("\n\t ###################################################################################################");
	printf("\n\t ###################################################################################################");
	printf("\n\t ##\t\t\t\t\t  JOGO DA MEM�RIA \t\t\t\t\t  ##");
	printf("\n\t ###################################################################################################");
	printf("\n\t ###################################################################################################\n\n");
}

void carregarJogo(int dificuldade){
	int chance = dificuldade;
	int contadorL; int contadorN; int numeroE;
	lista *cartas = (lista *) malloc(sizeof(lista));
	inicializa(cartas);
	for(contadorL=1; contadorL < tamanhoLista+1; contadorL++){
		for(contadorN=1; contadorN < tamanhoLista+1; contadorN++){
		
			gerarCartas(cartas, contadorL, contadorN);
		}
	}
	
	while(chance !=0){
	system("cls");
	menuBase();
	printf("\t chances: %d", chance);
	mostra_lista(cartas);
	tempoDecorarLista(dificuldade);
	system("cls");
	
	menuBase();
	printf("\t chances: %d", chance);
	 mostra_lista_escondido();
	 numeroE = esolherNumero(cartas);

	 printf("\n\t Informe em qual posi��o est� o numero: %d", numeroE);
	 if(verificarResposta(cartas, numeroE) == 1){
	 
	 	printf("\n\t\t\t\t  PARAB�NS !!! pressione qualquer tecla para voltar ao jogo... ");
	 	 getch();
	 	generateMenu(0);
	 }else{
	 	chance--;
	 }
	
	}
	
	printf("\n\t\t\t\t GAME OVER !!! pressione qualquer tecla para voltar ao jogo... ");
	 getch();
	generateMenu(0);
}

int main(){
	inicializarNumerosAleatorios();
	generateMenu(0);
}



