#include <stdint.h>
#include <stdio.h>
#include <netinet/in.h>

int main(int argc, char* argv[]){
    FILE *aFile = fopen(argv[1], "rb");
    FILE *bFile = fopen(argv[2], "rb");

    uint32_t aData;
    uint32_t bData;
    uint32_t sum;
    fread(&aData, 4, 1, aFile);
    fread(&bData, 4, 1, bFile);
    aData = ntohl(aData);
    bData = ntohl(bData);

    sum = aData + bData;

    printf("%d(%x) + %d(%x) = %d(%x)\n", aData, aData, bData, bData, sum, sum);
    return 0;
}