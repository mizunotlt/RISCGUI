#include "Parser.h"
#include "RiscMachine.h"
#include <iostream>
#include "string.h"
#include <cstdlib>

Parser:: Parser(char* str){
    this->str = str;

}
void Parser:: pars(){
    opcode= strtok(str, " ");
    if (!strcmp(opcode, "000")){ //ADD
        arg1 = strtok(NULL, " ");
        arg2 = strtok(NULL, " ");
        strtok(NULL, " ");
        arg3 = strtok(NULL, "\n");

    }else if (!strcmp(opcode, "001")){ //ADDI
        arg1 = strtok(NULL, " ");
        arg2 = strtok(NULL, " ");
        arg3 = strtok(NULL, "\n");

    }else if (!strcmp(opcode, "010")){ //NAND
        arg1 = strtok(NULL, " ");
        arg2 = strtok(NULL, " ");
        arg3 = strtok(NULL, "\n");

    }else if (!strcmp(opcode, "011")){ //lui
        arg1 = strtok(NULL, " ");
        arg3 = strtok(NULL, "\n");
    }else if(!strcmp(opcode, "101")){ //sw
        arg1 = strtok(NULL, " ");
        arg2 = strtok(NULL, " ");
        arg3 = strtok(NULL, "\n");
    }else if (!strcmp(opcode, "100")){ //lw
        arg1 = strtok(NULL, " ");
        arg2 = strtok(NULL, " ");
        arg3 = strtok(NULL, "\n");
    }else if (!strcmp(opcode, "110")){ //beg
        arg1 = strtok(NULL, " ");
        arg2 = strtok(NULL, " ");
        arg3 = strtok(NULL, "\n");
    }else if (!strcmp(opcode, "111")){ //jair
        arg1 = strtok(NULL, " ");
        arg2 = strtok(NULL, " ");
        arg3 = strtok(NULL, "\n");
    }else if (!strcmp(opcode, "exit")){
    }
}
char* Parser::getArg1() {
    return arg1;
}
char* Parser::getArg2() {
    return arg2;
}
char* Parser::getArg3() {
    return arg3;
}
char* Parser::getOpcode() {
    return opcode;
}

