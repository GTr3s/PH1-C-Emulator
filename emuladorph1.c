#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{

    FILE *arq;
    int ac; //acumulador
    int rem; //registrador endereco de memoria
    int rdm; //registrador de dados de memoria
    int mem[256]; //tamanho maximo de memoria � 256bytes
    int backup[256]; //vetor utilizado para salvar a mem�ria inicial e comparar com a final
    int pc=0; //program counter
    int cont=0; //contador de instru��o
    int end; //endereco de memoria contido no arquivo
    int data; //dado contido na memoria do arquivo
    int ri; ///registrador de instru�oes
    int i,j; //variaveis auxiliares

    for(j=0; j<255; j++)
    {
        backup[j] = 0;
        mem[j] = 0;
    }


    if(argc != 2) //teste para checar entrada
    {
	printf("Argumento Invalido\n");
	return 0;
    }


    if(arq == NULL) //teste para ver se o arquivo � valido
    {
        printf("Nao conseguiu abrir o arquivo\n");
        exit(1);
    }

    arq = fopen(argv[1], "r"); ///abrindo arquivo


    printf("Input file: %s\n\n", argv[1]);

    do
    {
        fscanf( arq ,"%x %x", &end, &data);
        backup[end] = data;
		mem[end] = data;

    }while(!feof(arq)); //passando os dados de cada coluna para vetor at� o EOF

    fclose(arq); //fecha o arquivo

    do
    {
        rem = pc;
        rdm = mem[rem];
        ri = rdm;

        if(ri == 0x00)
        {
            pc++;
            cont++;
            printf("NOP\n");
            continue;
        }

        if(ri == 0x10)
        {
            pc = pc+2;
            cont++;
            rdm = mem[rem+1];
            printf("LDR %x ; ", rdm); ///opera��o load
            printf("AC <- MEM[%x]\n", rdm);
            rem = rdm;
            rdm = mem[rem];
            ac = rdm; /// dado contido no endere�o de mem�ria � carregado no acumulador
            continue;
        }

        if(ri == 0x20)
        {
            pc=pc+2;
            cont++;
            rdm = mem[rem+1];
            printf("STR %x ; ", rdm); /// opera��o store
            printf("MEM[%x] <- AC\n", rdm);
            rem = rdm;
            rdm = mem[rem];
            mem[rem] = ac;
            continue;

        }

        if(ri == 0x30)
        {
            pc=pc+2;
            cont++;
            rdm = mem[rem+1];
            printf("ADD %x ; ", rdm); ///opera��o adi��o
            printf("AC <- AC + MEM[%x]\n", rdm);
            rem = rdm;
            rdm = mem[rem];
            ac = ac + mem[rem];
            continue;
        }

        if(ri == 0x40)
        {
            pc=pc+2;
            cont++;
            rdm = mem[rem+1];
            printf("SUB %x ; ", rdm); ///opera��o subtra��o
            printf("AC <- AC - MEM[%x]\n", rdm);
            rem = rdm;
            rdm = mem[rem];
            ac = ac - mem[rem];
            continue;
        }

        if(ri == 0x50)
        {
            pc=pc+2;
            cont++;
            rdm = mem[rem+1];
            printf("MUL %x ; ",rdm); ///opera��o multiplica��o
            printf("AC <- AC * MEM[%x]\n", rdm);
            rem = rdm;
            rdm = mem[rem];
            ac = ac * mem[rem];
            continue;
        }

        if(ri == 0x60)
        {
            pc=pc+2;
            cont++;
            rdm = mem[rem+1];
            printf("DIV %x ; ", rdm); ///opera��o divis�o
            printf("AC <- AC / MEM[%x]\n", rdm);
            rem = rdm;
            rdm = mem[rem];
            ac = ac / mem[rem];
            continue;
        }

        if(ri == 0x70)
        {
            pc++;
            cont++;
            printf("NOT ; "); ///opera��o nega��o
            printf("AC <- !AC \n");
            rem = rdm;
            rdm = mem[rem];
            ac = !ac;
            continue;
        }

        if(ri == 0x80)
        {
            pc= pc+2;
            cont++;
            printf("AND %x ; ", rdm); ///opera��o and
            printf("AC <- AC & MEM[%x]\n", rdm);
            rem = rdm;
            rdm = mem[rem];
            ac = ac & mem[rem];
            continue;
        }

        if(ri == 0x90)
        {
            pc= pc+2;
            cont++;
            printf("OR %x ; ", rdm); ///opera��o or
            printf("AC <- AC | MEM[%x]\n", rdm);
            rem = rdm;
            rdm = mem[rem];
            ac = ac | mem[rem];
            continue;
        }

        if(ri == 0xA0)
        {
            pc= pc+2;
            cont++;
            printf("XOR %x ; ", rdm); ///opera��o xor
            printf("AC <- AC ^ MEM[%x]\n", rdm);
            rem = rdm;
            rdm = mem[rem];
            ac = ac ^ mem[rem];
            continue;
        }

        if(ri == 0xB0)
        {
            pc= pc+2;
            cont++;
            printf("JMP %x ; ", rdm); ///opera��o jump
            printf("PC <- %x\n", rdm);
            rem = rdm;
            rdm = mem[rem+1];
            pc = rdm;
            continue;
        }

        if(ri == 0xC0)
        {
            if(ac==0)
            {
            pc= pc+2;
            cont++;
            printf("JEQ %x ; ", rdm); ///opera��o Jeq
            printf("se (AC = 0)PC <- %x\n", rdm);
            rem = rdm;
            rdm = mem[rem+1];
            pc = rdm;
            }
            continue;
        }

        if(ri == 0xD0)
        {
            if(ac>0)
            {
            pc= pc+2;
            printf("JG %x ; ", rdm); ///opera��o JG
            printf("se (AC > 0)PC <- %x\n", rdm);
            rem = rdm;
            rdm = mem[rem+1];
            pc = rdm;
            }
            continue;
        }

        if(ri == 0xE0)
        {
             if(ac<0)
            {
            pc= pc+2;
            cont++;
            printf("JL %x ; ", rdm); ///opera��o JL
            printf("se (AC < 0)PC <- %x\n", rdm);
            rem = rdm;
            rdm = mem[rem+1];
            pc = rdm;
            }
            continue;
        }

        if(ri == 0xF0)
        {
            pc++;
            cont++;
            printf("HLT\n"); ///opera��o halt

            break;
        }

    }
    while(1); //executa o loop at� HLT


    printf("\n%d instructions executed\n\n", cont);

    printf("Registers:\n");

    printf("AC %02x\n", ac);

    printf("PC %02x\n", pc);

    printf("\nMemory:\n", pc);

    for(i=128; i<255; i++)
    {
        if(backup[i] != mem[i])
        {
            printf("%02x %02x\n",i,mem[i]);
        }
    }
}
