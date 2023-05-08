//
// Created by kaplc on 2023/5/8.
//

#include "../header/calculator.h"
#include "../header/stack.h"
#include <stdio.h>
#include <stdlib.h>


void convertSuffix(char expression[], STACK* expStack){

}

void operation(){

}

void run_calculator() {
    char expression[1024] = {0};
    fgets(expression, 1024, stdin);

    STACK *expStack = NULL;
    init_stack(&expStack);
    convertSuffix(expression, expStack);
}