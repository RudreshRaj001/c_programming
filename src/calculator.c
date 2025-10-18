#include <stdio.h>
#include <stdlib.h>

int main(){
    int a, b;
    char operator;

    printf("Simple Calculator\n");
    printf("Enter an expression (e.g., 3 + 4): ");
    scanf("%d %c %d", &a, &operator, &b);

    switch(operator) {
        case '+':
            printf("%d + %d = %d\n", a, b, a + b);
            break;
        case '-':
            printf("%d - %d = %d\n", a, b, a - b);
            break;
        case '*':
            printf("%d * %d = %d\n", a, b, a * b);
            break;
        case '/':
            if(b != 0) {
                printf("%d / %d = %.2f\n", a, b, (float)a / b);
            } else {
                printf("Error: Division by zero is not allowed.\n");
            }
            break;
        default:
            printf("Error: Unsupported operator '%c'.\n", operator);
    }

    return 0;
}