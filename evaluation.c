#include<stdio.h>
#include<stdlib.h>
#include "list.h"
#include "stack.h"
#include "evaluation.h"

int is_digit(char d){
    if(d >= 48 && d <= 57)
        return 1;
    else
        return 0;
}

list* operation(list* operand1, list* operand2, char operator){
    list* res;

    switch(operator){
        case '+':
            if(operand1 -> sign ==-1 || operand2 -> sign == -1){
                if(operand1 -> sign ==-1 && operand2 -> sign == -1){
                    res = add(operand1, operand2);
                    res -> sign = -1;
                }
                else if(operand1 -> sign == 1){
                    res = sub(operand1, operand2);
                    if(compare(operand1, operand2) < 0)
                        res -> sign = -1;
                }
                else if(operand2 -> sign == 1){
                    res = sub(operand1, operand2);
                    if(compare(operand1, operand2) > 0)
                        res -> sign = -1;
                }
            }
            else{
                res = add(operand1, operand2);
            }
            break;

        case '-':
            if(operand1 -> sign ==-1 || operand2 -> sign == -1){
                if(operand1 -> sign ==-1 && operand2 -> sign == -1){
                    res = sub(operand1, operand2);
                    if(compare(operand1, operand2) > 0)
                        res -> sign = -1;
                }
                else if(operand1 -> sign == 1){
                    res = add(operand1, operand2);
                }
                else if(operand2 -> sign == 1){
                    res = add(operand1, operand2);
                    res -> sign = -1;
                }
            }
            else{
                res = sub(operand1, operand2);
                if(compare(operand1, operand2) < 0)
                    res -> sign = -1;
            }
            break;

        case '*':
            res = mul(operand1, operand2);
            if(operand1 -> sign != operand2 -> sign)
                res -> sign = -1;
            break;

        case '/':
            res = division(operand1, operand2);
            if(operand1 -> sign != operand2 -> sign)
                res -> sign = -1;
            break;
    }
    return res;
}

int precedence(char c){
    if(c == '+')
        return 10;
    else if(c == '-')
        return 10;
    else if(c == '*')
        return 20;
    else if(c == '/')
        return 20;
    else if(c == '%')
        return 20;
    else if(c == '^')
        return 30;
    else if(c == '(')
        return 5;
    return 0;
}

