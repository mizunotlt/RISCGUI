#ifndef RISCGUIC_RISCMACHINE_H
#define RISCGUIC_RISCMACHINE_H
#include <cstdlib>
#include <string>
#include <QObject>
class RiscMachine : public QObject {
    Q_OBJECT
    public:
        int countCom;
        int maxCommand;
        int memorySize;
        bool stepFlag = false;
        int breakPoint; //точка останова машины
        FILE *commandInput;
        FILE *initInput;
        static const int REG = 8;
        static const int ADD = 0;
        static const int ADDI = 1;
        static const int NAND = 2;
        static const int LUI = 3;
        static const int SW = 4;
        static const int LW = 5;
        static const int BEQ = 6;
        static const int JAIR = 7;
        static const int maxLengthLine = 32;
    private:
        struct Risccommand{
            int command;
            short int regA;
            short int regB;
            short int regCI;
        };
        short int *fixMemory = new short int (memorySize);
        Risccommand *comm = new struct Risccommand [maxCommand];
        short int *regMemory = new short int (REG);
        int stepByStep = 0; //переменная для пошаговой работы
        int countForStep = 0;//Отсчет шагов
        int count = 0; //базовый счетчик
    public:
        RiscMachine(int maxCommand, int memorySize);
        short int getMemory(int value);
        void initRegMemory();
        void setRegMemory(int index, short int value);
        void setFixMemory(int index, short int value);
        short int getRegMemory(int value);
        void setCommand(int index, int command , short int regA, short int regB, short int regCI);
        int fullWork();
        int stepByStepWork();
        void exactStepWork(int countExactStep);
        void bPoint(int breakPoint);
        void parseRisc(char *init, char *com);
        int getCommand(int index);
        short int getRegA(int index);
        short int getRegB(int index);
        short int getRegCI(int index);
        int getCountForStep();
        int getstepByStep();
        int getCount();

};
#endif //RISCGUIC_RISCMACHINE_H
