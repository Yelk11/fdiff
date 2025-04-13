#include <diff.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
    FILE* fp1;
    FILE* fp2;
    if(argc >= 2)
    {
        fp1 = fopen(argv[1], "r");
        fp2 = fopen(argv[2], "r");
    }
    else
    {
        fp1 = fopen("file1.txt", "r");
        fp2 = fopen("file2.txt", "r");
    }
    

    fseek(fp1, 0, SEEK_END);
    fseek(fp2, 0, SEEK_END);
    long length1 = ftell(fp1);
    long length2 = ftell(fp2);
    rewind(fp1);
    rewind(fp2);
    char* buffer1 = calloc(1,sizeof(char) * length1);
    char* buffer2 = calloc(1,sizeof(char) * length2);
    if(buffer1){
        fread (buffer1, 1, length1, fp1);
    }
    fread (buffer2, 1, length2, fp2);
    myer_diff(buffer1, buffer2);
    return 0;
}

