#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

/***********************************************/ 
/* Definicao dos Registros                     */
/***********************************************/ 
typedef struct arv { 
       struct arv* subd;  
       struct arv* sube;  
       char pergunta[200];
       char recomendacao[200];
       int eh_folha;
} ARVORE; 

/***********************************************/ 
/* Funcoes Auxiliares                          */
/***********************************************/

// Aloca memoria para um novo no
ARVORE* criar_no(const char* pergunta) {
    ARVORE* novo = (ARVORE*) malloc(sizeof(ARVORE));
    novo->subd = NULL;
    novo->sube = NULL;
    novo->eh_folha = 0;
    strcpy(novo->pergunta, pergunta);
    strcpy(novo->recomendacao, "");
    return novo;
}

// Cria uma folha (recomendacao)
ARVORE* criar_folha(const char* recomendacao) {
    ARVORE* folha = criar_no("");
    folha->eh_folha = 1;
    strcpy(folha->recomendacao, recomendacao);
    return folha;
}

// Constroi a arvore de decisao
ARVORE* construir_arvore() {
    // Nivel 8 - Folhas (recomendacoes finais)
    ARVORE* folha1 = criar_folha("Nike Air Force - Tenis esportivo masculino premium");
    ARVORE* folha2 = criar_folha("Adidas Ultraboost - Tenis esportivo masculino com suporte");
    ARVORE* folha3 = criar_folha("Nike Trail - Tenis masculino para hiking e trilha");
    ARVORE* folha4 = criar_folha("Salomon Quest - Bota de hiking masculina profissional");
    ARVORE* folha5 = criar_folha("Nike Air Max - Tenis esportivo feminino elegante");
    ARVORE* folha6 = criar_folha("Adidas Stan Smith - Tenis casual feminino classico");
    ARVORE* folha7 = criar_folha("Salomon Speedcross - Bota de hiking feminina agil");
    ARVORE* folha8 = criar_folha("Converse All Star - Sapatilha casual feminina iconica");

    // Nivel 7 - Perguntas de refinamento (Conforto vs Estilo)
    ARVORE* no_conforto_masc = criar_no("Voce PRIORIZA CONFORTO EXTREMO?");
    no_conforto_masc->subd = folha2;  // Sim: Adidas Ultraboost (maximo conforto)
    no_conforto_masc->sube = folha1;  // Nao: Nike Air Force (elegancia)

    // Nivel 6 - Perguntas sobre tipo de atividade (Hiking vs Dia a dia)
    ARVORE* no_hiking_masc = criar_no("Voce vai usar em TRILHAS RADICAIS com botas?");
    no_hiking_masc->subd = folha4;  // Sim: Salomon Quest (bota)
    no_hiking_masc->sube = folha3;  // Nao: Nike Trail (tenis para trilha)

    ARVORE* no_diaria_masc = criar_no("Voce VALORIZA ESTILO E ELEGANCIA?");
    no_diaria_masc->subd = no_conforto_masc;  // Sim: vai refinar com pergunta 7
    no_diaria_masc->sube = folha2;  // Nao: Adidas Ultraboost (conforto)

    // Nivel 7 - Perguntas de refinamento feminino
    ARVORE* no_conforto_fem = criar_no("Voce PRIORIZA CONFORTO E SUPORTE?");
    no_conforto_fem->subd = folha5;   // Sim: Nike Air Max (conforto + estilo)
    no_conforto_fem->sube = folha6;   // Nao: Adidas Stan Smith (minimalista)

    // Nivel 8 - Pergunta de refinamento feminino esportivo trilhas
    ARVORE* no_estilo_fem_trilha = criar_no("Voce PREFERE CONFORTO MAXIMO?");
    no_estilo_fem_trilha->subd = folha5;   // Sim: Nike Air Max (conforto + estilo)
    no_estilo_fem_trilha->sube = folha7;   // Nao: Salomon Speedcross (bota profissional)

    // Nivel 5 - Perguntas sobre tipo de atividade (Hiking vs Dia a dia) feminino
    ARVORE* no_hiking_fem = criar_no("Voce vai usar em TRILHAS RADICAIS com botas?");
    no_hiking_fem->subd = no_estilo_fem_trilha;   // Sim: vai refinar com pergunta 8
    no_hiking_fem->sube = folha5;   // Nao: Nike Air Max (esportivo para usar todo dia)

    // Nivel 8 - Pergunta de refinamento feminino casual classico
    ARVORE* no_estilo_fem_casual = criar_no("Voce PREFERE CONFORTO MAXIMO?");
    no_estilo_fem_casual->subd = folha6;   // Sim: Adidas Stan Smith (conforto minimalista)
    no_estilo_fem_casual->sube = folha8;   // Nao: All Star (classico/iconico)

    ARVORE* no_casual_fem = criar_no("Voce VALORIZA CLASSICO E MINIMALISMO?");
    no_casual_fem->subd = no_estilo_fem_casual;   // Sim: vai refinar com pergunta 8
    no_casual_fem->sube = folha5;   // Nao: Nike Air Max (moderno e colorido)

    // Nivel 4 - Pergunta sobre uso (Esportivo vs Casual)
    ARVORE* no_esportivo_masc = criar_no("Sera para TRILHAS E TERRENOS DIFICEIS?");
    no_esportivo_masc->subd = no_hiking_masc;    // Sim: Trilhas/radical
    no_esportivo_masc->sube = no_diaria_masc;    // Nao: Dia a dia

    // Nivel 7 - Pergunta de refinamento masculino casual
    ARVORE* no_estilo_masc_casual = criar_no("Voce PREFERE CONFORTO MAXIMO?");
    no_estilo_masc_casual->subd = folha2;  // Sim: Adidas Ultraboost (conforto total)
    no_estilo_masc_casual->sube = folha1;  // Nao: Nike Air Force (style descontraido)

    ARVORE* no_casual_masc = criar_no("Voce prefere um LOOK MAIS CLASSICO?");
    no_casual_masc->subd = folha1;   // Sim: Nike Air Force (classico)
    no_casual_masc->sube = no_estilo_masc_casual;  // Nao: vai refinar com pergunta 7

    // Nivel 3 - Pergunta sobre uso (Esportivo vs Casual) feminino
    ARVORE* no_esportivo_fem = criar_no("Sera para TRILHAS E TERRENOS DIFICEIS?");
    no_esportivo_fem->subd = no_hiking_fem;      // Sim: Trilhas/radical
    no_esportivo_fem->sube = no_casual_fem;      // Nao: Dia a dia (mas com estilo)

    ARVORE* no_casual_fem2 = criar_no("Voce PREFERE UM LOOK CLASSICO E ICONICO?");
    no_casual_fem2->subd = folha8;   // Sim: All Star (classico/iconico)
    no_casual_fem2->sube = folha6;   // Nao: Stan Smith (versatil)

    // Nivel 2 - Pergunta sobre uso geral (Esportivo vs Casual)
    ARVORE* no_uso_masc = criar_no("Voce prefere um tenis ESPORTIVO?");
    no_uso_masc->subd = no_esportivo_masc;       // Sim: Esportivo
    no_uso_masc->sube = no_casual_masc;          // Nao: Casual

    ARVORE* no_uso_fem = criar_no("Voce prefere um tenis ESPORTIVO?");
    no_uso_fem->subd = no_esportivo_fem;         // Sim: Esportivo
    no_uso_fem->sube = no_casual_fem2;           // Nao: Casual

    // Nivel 1 - Raiz (Genero)
    ARVORE* raiz = criar_no("Voce é HOMEM? (0 = Não, sou mulher / 1 = Sim, sou homem)");
    raiz->subd = no_uso_masc;       // Direita (1): Homem
    raiz->sube = no_uso_fem;        // Esquerda (0): Mulher

    return raiz;
}

// Percorre a arvore fazendo perguntas e coletando respostas
void percorrer_arvore(ARVORE* arv) {
    ARVORE* atual = arv;
    int resposta;

    while (atual != NULL && atual->eh_folha == 0) {
        printf("\n[PERGUNTA] %s\n", atual->pergunta);
        printf("   (0 = Nao / 1 = Sim): ");
        
        // Valida entrada: aceita apenas 0 ou 1
        while (scanf("%d", &resposta) != 1 || (resposta != 0 && resposta != 1)) {
            while (getchar() != '\n');  // Limpa buffer
            printf("   Entrada invalida! Digite apenas 0 (Nao) ou 1 (Sim): ");
        }

        // Limpa buffer
        while (getchar() != '\n');

        if (resposta == 1) {
            atual = atual->subd;  // Vai para a direita
        } else {
            atual = atual->sube;  // Vai para a esquerda
        }
    }

    // Chegou em uma folha
    if (atual != NULL && atual->eh_folha) {
        printf("\n");
        printf("=====================================\n");
        printf("     ? RECOMENDACAO PARA VOCE!      \n");
        printf("=====================================\n");
        printf("  %s\n", atual->recomendacao);
        printf("=====================================\n\n");
    }
}

// Libera a memoria da arvore
void liberar_arvore(ARVORE* arv) {
    if (arv == NULL) return;
    liberar_arvore(arv->sube);
    liberar_arvore(arv->subd);
    free(arv);
}

/***********************************************/ 
/* Funcao Principal                            */
/***********************************************/

int main(void) {
    setlocale(LC_ALL, "Portuguese");
    
    printf("\n");
    printf("+---------------------------------------+\n");
    printf("¦     BEM VINDO(A) AO TCHÊNIS!         ¦\n");
    printf("¦  Recomendador de Tenis Inteligente    ¦\n");
    printf("+---------------------------------------+\n\n");
    
    printf("Vamos descobrir qual é o tênis ideal para voce?\n");
    printf("Responda as perguntas com 0 (Não) ou 1 (Sim).\n");
    printf("---------------------------------------\n");

    // Constroi e percorre a arvore
    ARVORE* arvore = construir_arvore();
    percorrer_arvore(arvore);

    // Libera memoria
    liberar_arvore(arvore);

    printf("Obrigado por usar TCHENIS! Ate logo!\n\n");
	
    return 0;
}
