#include "RiscMachine.h"
#include <iostream>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "string.h"
#include <cstdlib>
#include <QObject>
#include "Parser.h"
#include "qfile.h"
#include "math.h"
using namespace std;
short int toDec (char *binaryCode){
    short int decValue = 0;
    for (int i = 0; i < 3; i ++){
        if (binaryCode[i] == '1'){
            decValue = (short) (decValue + pow(2, 2 - i));
        }
    }
    return decValue;
}
short int toDecForImm (char *binaryCode){
    short int decValue = 0;
    short int sign = -1;
    for (int i = 1; i < 7; i ++){
        if (binaryCode[i] == '1'){
            decValue = (short) (decValue + pow(2, 6 - i));
        }
    }
    if (binaryCode[0] == '1'){
        decValue = decValue * sign;
    }
    return decValue;
}

RiscMachine::RiscMachine(int maxCommand, int memorySize){
    this->maxCommand = maxCommand;
    this->memorySize = memorySize;
}

short int RiscMachine::getMemory(int i) {
    return fixMemory[i];
}
void RiscMachine::initRegMemory() {
    for (int i = 0; i < REG; i++){
        regMemory[i] = 0;
    }
}
short int RiscMachine::getRegMemory(int i) {
    return regMemory[i];
}
void RiscMachine::setFixMemory(int index, short int value) {
    fixMemory[index] = value;
}
void RiscMachine::setRegMemory(int index, short int value) {
    regMemory[index] = value;
}
void RiscMachine:: setCommand(int index, int command, short int regA, short int regB, short int regCI) {
    comm[index].command = command;
    comm[index].regA = regA;
    comm[index].regB = regB;
    comm[index].regCI = regCI;
}
int RiscMachine:: getCommand(int index){
    return comm[index].command;
}
short int RiscMachine:: getRegA(int index){
    return comm[index].regA;
}
short int RiscMachine:: getRegB(int index){
    return comm[index].regB;
}
short int RiscMachine:: getRegCI(int index){
    return comm[index].regCI;
}


int RiscMachine::fullWork() {
    while (count != countCom) {
        switch (comm[count].command) {
            case 0 : {
                regMemory[comm[count].regA] = regMemory[comm[count].regB] + regMemory[comm[count].regCI];
                count++;
                break;
            }
            case 1 : {
                regMemory[comm[count].regA] = regMemory[comm[count].regB] + comm[count].regCI;
                count++;
                break;
            }
            case 2 : {
                regMemory[comm[count].regA] = (regMemory[comm[count].regB] & regMemory[comm[count].regCI]);
                count++;
                break;
            }
            case 3 : {
                break;
            }
            case 4 : {
                fixMemory[regMemory[comm[count].regB] + comm[count].regCI] = regMemory[comm[count].regA];
                count++;
                break;
            }
            case 5 : {
                regMemory[comm[count].regA] = fixMemory[regMemory[comm[count].regB] + comm[count].regCI];
                count++;
                break;
            }
            case 6 : {
                if (regMemory[comm[count].regA] == regMemory[comm[count].regB]) {
                    count = count + 1 + comm[count].regCI;
                } else {
                    count++;
                }
                break;
            }
            case 7 : {
                regMemory[comm[count].regA] = count + 1;
                count = regMemory[comm[count].regB];
                break;
            }
        }
    }
    return count;
}

int RiscMachine:: stepByStepWork(){
    if (stepByStep != countCom){
        switch (comm[stepByStep].command) {
            case 0 : {
                regMemory[comm[stepByStep].regA] = regMemory[comm[stepByStep].regB] + regMemory[comm[stepByStep].regCI];
                stepByStep++;
                break;
            }
            case 1 : {
                regMemory[comm[stepByStep].regA] = regMemory[comm[stepByStep].regB] + comm[stepByStep].regCI;
                stepByStep++;
                break;
            }
            case 2 : {
                regMemory[comm[stepByStep].regA] = (regMemory[comm[stepByStep].regB] & regMemory[comm[stepByStep].regCI]);
                stepByStep++;
                break;
            }
            case 3 : {
                break;
            }
            case 4 : {
                fixMemory[regMemory[comm[stepByStep].regB] + comm[stepByStep].regCI] = regMemory[comm[stepByStep].regA];
                stepByStep++;
                break;
            }
            case 5 : {
                regMemory[comm[stepByStep].regA] = fixMemory[regMemory[comm[stepByStep].regB] + comm[stepByStep].regCI];
                stepByStep++;
                break;
            }
            case 6 : {
                if (regMemory[comm[stepByStep].regA] == regMemory[comm[stepByStep].regB]) {
                    stepByStep = stepByStep + 1 + comm[stepByStep].regCI;
                } else {
                    stepByStep++;
                }
                break;
            }
            case 7 : {
                regMemory[comm[stepByStep].regA] = stepByStep + 1;
                stepByStep = regMemory[comm[stepByStep].regB];
                break;
            }
        }
    }
    countForStep++;
    return stepByStep;
}

void RiscMachine:: parseRisc(char *init, char *com){
    int line = 0;
        char inputCom[32];
        FILE *commandInput;
        FILE *initInput;
        //initInput = fopen("C:/Users/User/Documents/RISCGui/initMachine.txt", "rt");
        initInput = fopen(init, "rt");
        int a;
        fscanf(initInput,"%d", &a);
        int maxSize = a;
        for (int i = 0; i <= maxSize; i++){
            fscanf(initInput,"%d", &a);
            setFixMemory(i, a);
        }
        //commandInput = fopen("C:/Users/User/Documents/RISCGui/command.txt", "rt");
        commandInput = fopen(com, "rt");
        //считывание команд из файла и парсер их
        while (!feof(commandInput)){
            fgets(inputCom, sizeof(inputCom), commandInput);
            Parser pars(inputCom);
            pars.pars();
            if (!strcmp(pars.getOpcode(), "000")){ //ADD
                setCommand(line,ADD,toDec(pars.getArg1()), toDec(pars.getArg2()),toDec(pars.getArg3()));
                line++;
            }else if (!strcmp(pars.getOpcode(), "001")){ //ADDI
                setCommand(line,ADDI,toDec(pars.getArg1()), toDec(pars.getArg2()),toDecForImm(pars.getArg3()));
                line++;
            }else if (!strcmp(pars.getOpcode(), "010")){ //NAND
                setCommand(line,NAND,toDec(pars.getArg1()), toDec(pars.getArg2()),toDec(pars.getArg3()));
                line++;
            }else if (!strcmp(pars.getOpcode(), "011")){ //lui
                setCommand(line,LUI,toDec(pars.getArg1()), 0,toDec(pars.getArg3()));
                line++;
            }else if(!strcmp(pars.getOpcode(), "101")){ //sw
                setCommand(line,SW,toDec(pars.getArg1()), toDec(pars.getArg2()),toDecForImm(pars.getArg3()));
                line++;
            }else if (!strcmp(pars.getOpcode(), "100")){ //lw
                setCommand(line,LW,toDec(pars.getArg1()), toDec(pars.getArg2()),toDecForImm(pars.getArg3()));
                line++;

            }else if (!strcmp(pars.getOpcode(), "110")){ //beg
                setCommand(line,BEQ,toDec(pars.getArg1()), toDec(pars.getArg2()),toDecForImm(pars.getArg3()));
                line++;
            }else if (!strcmp(pars.getOpcode(), "111")){ //jair
                setCommand(line,JAIR,toDec(pars.getArg1()), toDec(pars.getArg2()),toDecForImm(pars.getArg3()));
                line++;
            }else if (!strcmp(pars.getOpcode(), "exit")){
                countCom = line;
            }
        }
}
int RiscMachine:: getCountForStep(){
    return countForStep;
}
int RiscMachine:: getstepByStep(){
    return stepByStep;
}
void RiscMachine:: exactStepWork(int countExactStep){
    if((countForStep < countExactStep) || (stepByStep != countCom)){
            switch (comm[stepByStep].command) {
                case 0 : {
                    regMemory[comm[stepByStep].regA] = regMemory[comm[stepByStep].regB] + regMemory[comm[stepByStep].regCI];
                    stepByStep++;
                    break;
                }
                case 1 : {
                    regMemory[comm[stepByStep].regA] = regMemory[comm[stepByStep].regB] + comm[stepByStep].regCI;
                    stepByStep++;
                    break;
                }
                case 2 : {
                    regMemory[comm[stepByStep].regA] = (regMemory[comm[stepByStep].regB] & regMemory[comm[stepByStep].regCI]);
                    stepByStep++;
                    break;
                }
                case 3 : {
                    break;
                }
                case 4 : {
                    fixMemory[regMemory[comm[stepByStep].regB] + comm[stepByStep].regCI] = regMemory[comm[stepByStep].regA];
                    stepByStep++;
                    break;
                }
                case 5 : {
                    regMemory[comm[stepByStep].regA] = fixMemory[regMemory[comm[stepByStep].regB] + comm[stepByStep].regCI];
                    stepByStep++;
                    break;
                }
                case 6 : {
                    if (regMemory[comm[stepByStep].regA] == regMemory[comm[stepByStep].regB]) {
                        stepByStep = stepByStep + 1 + comm[stepByStep].regCI;
                    } else {
                        stepByStep++;
                    }
                    break;
                }
                case 7 : {
                    regMemory[comm[stepByStep].regA] = stepByStep + 1;
                    stepByStep = regMemory[comm[stepByStep].regB];
                    break;
                }
            }
        }
        countForStep++;
}
void RiscMachine:: bPoint(int breakPoint){
    while (count != breakPoint) {
        switch (comm[count].command) {
            case 0 : {
                regMemory[comm[count].regA] = regMemory[comm[count].regB] + regMemory[comm[count].regCI];
                count++;
                break;
            }
            case 1 : {
                regMemory[comm[count].regA] = regMemory[comm[count].regB] + comm[count].regCI;
                count++;
                break;
            }
            case 2 : {
                regMemory[comm[count].regA] = (regMemory[comm[count].regB] & regMemory[comm[count].regCI]);
                count++;
                break;
            }
            case 3 : {
                break;
            }
            case 4 : {
                fixMemory[regMemory[comm[count].regB] + comm[count].regCI] = regMemory[comm[count].regA];
                count++;
                break;
            }
            case 5 : {
                regMemory[comm[count].regA] = fixMemory[regMemory[comm[count].regB] + comm[count].regCI];
                count++;
                break;
            }
            case 6 : {
                if (regMemory[comm[count].regA] == regMemory[comm[count].regB]) {
                    count = count + 1 + comm[count].regCI;
                } else {
                    count++;
                }
                break;
            }
            case 7 : {
                regMemory[comm[count].regA] = count + 1;
                count = regMemory[comm[count].regB];
                break;
            }
        }
    }
}
int RiscMachine:: getCount(){
    return count;
}







