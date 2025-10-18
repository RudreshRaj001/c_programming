#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(){
    int a, b;
    char operator;

    
    while(1){
        printf("nano Calculator\n");
        printf("Enter operator (+, -, *, /, ^, %% , or 'q' to quite: ");
        scanf("%c\n",&operator);
        printf("Enter 1st operand: ");
        scanf("%d", &a);
        printf("Enter 2nd operand: ");
        scanf("%d", &b);


        if (operator == '+' || operator == '-' || operator == '*' || operator == '/' || operator == '^' || operator == '%') {
            printf("You selected operator: %c\n", operator);
        } else if (operator == 'q') {
            printf("Exiting calculator.\n");
            return 0;
        } else {
            printf("Invalid operator. Please enter one of +, -, *, /, ^, %%: ");
            continue;
        }

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
             case '%':
                printf("%d mod %d = %d\n", a, b, (a % b));
                break;
            case '^':
                printf("%d pow %d = %d\n", a, b, pow(a, b));
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
    }

    return 0;
}