#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int main(){
    char label[10], opcode[10], operand[10], mnemonic[10], code[10];
    int loctr, start, length, found;
    FILE *fp1, *fp2, *fp3, *fp4;

    fp1 = fopen("input.txt","r");
    fp2 = fopen("optab.txt","r");
    fp3 = fopen("symtab.txt","w");
    fp4 = fopen("out.txt","w");

    fscanf(fp1,"%s %s %s", label, opcode, operand);

    if(strcmp(opcode,"START")==0){
        start = (int)strtol(operand, NULL, 16);
        loctr = start;
        fprintf(fp4,"%04X\t%s\t%s\t%s\n", loctr, label, opcode, operand);
        fscanf(fp1,"%s %s %s", label, opcode, operand);
    }
    else{
        loctr = 0;
    }

    while(strcmp(opcode,"END")!=0){
        fprintf(fp4,"%04X\t%s\t%s\t%s\n", loctr, label, opcode, operand);

        if(strcmp(label,"**")!=0){
            fprintf(fp3,"%s\t%04X\n", label, loctr);
        }

        rewind(fp2);
        found = 0;
        while(fscanf(fp2,"%s %s", code, mnemonic) != -1){
            if(strcmp(opcode, code) == 0){
                loctr += 3;
                found = 1;
                break;
            }
        }

        if(!found){
            if(strcmp(opcode,"WORD")==0){
                loctr += 3;
            }
            else if(strcmp(opcode,"RESW")==0){
                loctr += 3 * atoi(operand);
            }
            else if(strcmp(opcode,"RESB")==0){
                loctr += atoi(operand);
            }
            else if(strcmp(opcode,"BYTE")==0){
                if(operand[0] == 'C'){
                    int len = strlen(operand) - 3;
                    loctr += len;
                }
                else if(operand[0] == 'X'){
                    int len = (strlen(operand) - 3) / 2;
                    loctr += len;
                }
            }
        }
        fscanf(fp1,"%s %s %s", label, opcode, operand);
    }

    fprintf(fp4,"%04X\t%s\t%s\t%s\n", loctr, label, opcode, operand);
    length = loctr - start;
    printf("The length of the program is %X hex\n", length);

    fclose(fp1);
    fclose(fp2);
    fclose(fp3);
    fclose(fp4);
    return 0;
}
