#ifndef RISCGUIC_PARSER_H
#define RISCGUIC_PARSER_H

#include <cstdio>

class Parser {
    public:
        char* str;
    private:
        char* opcode;
        char* arg1;
        char* arg2;
        char* arg3;
    public:
        Parser(char* str);
        void pars();
        char* getOpcode();
        char* getArg1();
        char* getArg2();
        char* getArg3();
};
#endif //RISCGUIC_PARSER_H
