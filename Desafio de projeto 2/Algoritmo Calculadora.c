#include <stdio.h>

int main() {
    char operacao;
    double num1, num2, resultado;

    // Solicita a operação desejada ao usuário
    printf("Escolha uma operacao matematica (+, -, *, /): ");
    scanf(" %c", &operacao);

    // Solicita os dois números ao usuário
    printf("Digite o primeiro numero: ");
    scanf("%lf", &num1);

    printf("Digite o segundo numero: ");
    scanf("%lf", &num2);

    // Realiza a operação escolhida e exibe o resultado
    switch (operacao) {
        case '+':
            resultado = num1 + num2;
            printf("Resultado: %.2lf\n", resultado);
            break;
        case '-':
            resultado = num1 - num2;
            printf("Resultado: %.2lf\n", resultado);
            break;
        case '*':
            resultado = num1 * num2;
            printf("Resultado: %.2lf\n", resultado);
            break;
        case '/':
            if (num2 != 0) {
                resultado = num1 / num2;
                printf("Resultado: %.2lf\n", resultado);
            } else {
                printf("Erro: Divisao por zero!\n");
            }
            break;
        default:
            printf("Operacao invalida.\n");
            break;
    }

    return 0;
}

