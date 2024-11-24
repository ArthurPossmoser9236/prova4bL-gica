#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_CONTATOS 50
#define MAX_MENSAGENS 50

struct Contato {
    char nome[100];
    char telefone[15];
};

struct Mensagem {
    char destinatario[100];
    char conteudo[200];
};

int bateria = 100;
int creditos = 10;
struct Contato agenda[MAX_CONTATOS];
int totalContatos = 0;
struct Mensagem mensagens[MAX_MENSAGENS];
int totalMensagens = 0;

void reduzirBateria() {
    bateria--;
    if (bateria < 0) bateria = 0;
}

void menuBateria() {
    printf("Nível de bateria: %d%%\n", bateria);
    printf("Previsão de duração: %.1f horas\n", bateria / 2.0);
    printf("1. Voltar ao menu principal\n");
    getchar();
}

void menuMensagens() {
    printf("Mensagens recebidas:\n");
    for (int i = 0; i < totalMensagens; i++) {
        printf("%d. Para: %s - Conteúdo: %s\n", i + 1, mensagens[i].destinatario, mensagens[i].conteudo);
    }
    printf("1. Voltar ao menu principal\n");
    getchar();
}

void menuHistoricoChamadas() {
    printf("Chamadas recentes:\n");
    printf("1. Ligação para 12345 - Duração: 5s\n");
    printf("1. Voltar ao menu principal\n");
    getchar();
}

void menuAgenda() {
    printf("Contatos da agenda:\n");
    for (int i = 0; i < totalContatos; i++) {
        printf("%d. Nome: %s - Telefone: %s\n", i + 1, agenda[i].nome, agenda[i].telefone);
    }
    printf("1. Adicionar novo contato\n");
    printf("2. Voltar ao menu principal\n");
    int opcao;
    scanf("%d", &opcao);
    getchar();
    if (opcao == 1) {
        if (totalContatos < MAX_CONTATOS) {
            printf("Digite o nome do contato: ");
            fgets(agenda[totalContatos].nome, 100, stdin);
            agenda[totalContatos].nome[strcspn(agenda[totalContatos].nome, "\n")] = 0;
            printf("Digite o telefone do contato: ");
            fgets(agenda[totalContatos].telefone, 15, stdin);
            agenda[totalContatos].telefone[strcspn(agenda[totalContatos].telefone, "\n")] = 0;
            totalContatos++;
        } else {
            printf("Agenda cheia!\n");
        }
    }
}

void menuOperadora() {
    printf("Operadora: Exemplo Mobile\n");
    printf("1. Voltar ao menu principal\n");
    getchar();
}

void menuCreditos() {
    printf("Créditos disponíveis: %d reais\n", creditos);
    printf("Pode enviar %d mensagens ou realizar %d ligações\n", creditos, creditos / 2);
    printf("1. Voltar ao menu principal\n");
    getchar();
}

void realizarLigacao() {
    if (creditos >= 2) {
        printf("Digite o número para ligar: ");
        char numero[15];
        fgets(numero, 15, stdin);
        numero[strcspn(numero, "\n")] = 0;
        printf("Ligando para %s...\n", numero);
        sleep(5);
        printf("Chamada finalizada.\n");
        creditos -= 2;
        reduzirBateria();
    } else {
        printf("Créditos insuficientes para realizar uma ligação.\n");
    }
}

void enviarMensagem() {
    if (creditos >= 1) {
        if (totalMensagens < MAX_MENSAGENS) {
            printf("Digite o destinatário: ");
            fgets(mensagens[totalMensagens].destinatario, 100, stdin);
            mensagens[totalMensagens].destinatario[strcspn(mensagens[totalMensagens].destinatario, "\n")] = 0;
            printf("Digite a mensagem: ");
            fgets(mensagens[totalMensagens].conteudo, 200, stdin);
            mensagens[totalMensagens].conteudo[strcspn(mensagens[totalMensagens].conteudo, "\n")] = 0;
            totalMensagens++;
            creditos--;
            reduzirBateria();
            printf("Mensagem enviada!\n");
        } else {
            printf("Caixa de mensagens cheia!\n");
        }
    } else {
        printf("Créditos insuficientes para enviar mensagem.\n");
    }
}

int main() {
    int opcao;
    while (1) {
        printf("\n=== Menu Principal ===\n");
        printf("1. Ver nível de bateria\n");
        printf("2. Mensagens\n");
        printf("3. Histórico de ligações\n");
        printf("4. Realizar ligação\n");
        printf("5. Agenda\n");
        printf("6. Operadora\n");
        printf("7. Créditos\n");
        printf("8. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1: menuBateria(); break;
            case 2: enviarMensagem(); break;
            case 3: menuHistoricoChamadas(); break;
            case 4: realizarLigacao(); break;
            case 5: menuAgenda(); break;
            case 6: menuOperadora(); break;
            case 7: menuCreditos(); break;
            case 8: printf("Saindo...\n"); exit(0);
            default: printf("Opção inválida!\n"); break;
        }
    }
    return 0;
}
