#include "list.h"
#include "stack.h"
#include "evaluation.h"
#include<stdio.h>
#include<stdlib.h>

int main(){
    char expr[100];
    char c, operator;
    int i = 0, count, flag = 0, flag1 = 0, flag2 = 0, bracket = 0;
    int j = 0;
    int sign = 1, sign1 = 1;

    list *operand1, *operand2, *res;
    list* temp[50];

    op_stack s1;
    od_stack s2;
    op_sinit(&s1);
    od_sinit(&s2);								
						/*flag1 indicates expression contain -(*/
    fgets(expr, 100, stdin);
							/*flag2 indicates -()*/
    while(expr[i] != '\0'){
        c = expr[i];
        flag = 0;

        if(expr[i] == '-' && flag2 == 0){
            if(expr[i + 1] != '('){
                sign = -1;
            }
            else{
                sign1 = -1;
                flag1 = 1;
            }
            flag2 = 1;
        }

        else if(c == '('){
            op_push(&s1, c);
            if(expr[i + 1] == '-'){
                sign = -1;
                i++;
            }
            if(flag1 == 1){
                bracket++;
            }
            flag2 = 1;
        }
        else if(is_digit(c) || c == '.'){
            count = 0;
            temp[j] = (list*)malloc(sizeof(list));
            linit(temp[j]);

            while(is_digit(expr[i]) || expr[i] == '.'){
                if(expr[i] == '.'){
                    if(flag == 1){
                        printf("Invalid..!");
                        exit(0);
                    }
                    else{
                        flag = 1;
                    }
                }
                else{
                    append(temp[j], (int)(expr[i] - '0'));
                    if(flag == 1)
                        count++;
                }
                i++;
            }
            i--;
            temp[j] -> dec = count;
            if(sign == -1){
                temp[j] -> sign = -1;
                sign = 1;
            }
            od_push(&s2, temp[j]);
            j++;
            flag2 = 1;
        }
        else if(c == ')'){
            while(!op_empty(s1) && op_peek(s1) != '('){
                operator = op_pop(&s1);
                operand2 = od_pop(&s2);
                operand1 = od_pop(&s2);

                if(operator == '-' && op_peek(s1) == '-'){
                    res = add(operand1, operand2);
                }
                else{
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
                                if(operand1 -> sign == -1 && operand2 -> sign == -1){
                                    res = sub(operand1, operand2);
                                    if(compare(operand1, operand2) > 0)
                                        res -> sign = -1;
                                }
                                else if(operand1 -> sign == 1){
                                    res = add(operand1, operand2);  ////
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
                    //res = operation(operand1, operand2, operator);
                }
                if(flag1 == 1){
                    if(bracket == 1){
                        res -> sign = (res -> sign) * sign1;
                        flag1 = 0;
                    }
                    else{
                        bracket--;
                    }
                }
                od_push(&s2, res);
            }
            if(op_peek(s1) == '('){
                op_pop(&s1);
            }
        }
        else if((c == '*' || c == '/' || c == '+' || c == '-' || c == '%' || c == '^') && i != 0){
            if(op_empty(s1)){
                op_push(&s1, c);
            }
            else{
                while(!op_empty(s1) && precedence(op_peek(s1)) >= precedence(c)){
                    operator = op_pop(&s1);
                    operand2 = od_pop(&s2);
                    operand1 = od_pop(&s2);

                    if(operator == '-' && op_peek(s1) == '-'){
                        res = add(operand1, operand2);
                    }

                    else{
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
                        //res = operation(operand1, operand2, operator);
                    }

                    od_push(&s2, res);
                }
                op_push(&s1, c);
            }
        }
        i++;
    }
    while(!op_empty(s1)){
        operator = op_pop(&s1);
        operand2 = od_pop(&s2);
        operand1 = od_pop(&s2);

        if(operator == '-' && op_peek(s1) == '-'){
            res = add(operand1, operand2);
        }
        else{

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
                            res = add(operand1, operand2);  ////
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
            //res = operation(operand1, operand2, operator);
        }
        od_push(&s2, res);
    }
    remove_zero(res);
    traverse(*res);
    return 0;
}




