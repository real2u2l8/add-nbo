#include <stdint.h>
#include <stdio.h>
#include <netinet/in.h>

int main(int argc, char* argv[]){
    if (argc != 3) {
        printf("사용법: %s <파일1> <파일2>\n", argv[0]);
        return 1;
    }

    FILE *aFile = fopen(argv[1], "rb");
    FILE *bFile = fopen(argv[2], "rb");

    if (aFile == NULL || bFile == NULL) {
        printf("파일을 열 수 없습니다.\n");
        return 1;
    }

    uint32_t aData;
    uint32_t bData;
    uint32_t sum;
    
    if (fread(&aData, 4, 1, aFile) != 1 || fread(&bData, 4, 1, bFile) != 1) {
        printf("파일 읽기 실패\n");
        return 1;
    }

    fclose(aFile);
    fclose(bFile);

    aData = ntohl(aData);
    bData = ntohl(bData);

    sum = aData + bData;

    printf("%d(%x) + %d(%x) = %d(%x)\n", aData, aData, bData, bData, sum, sum);
    return 0;
}