#include <stdint.h>
#include <stdio.h>
#include <netinet/in.h>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("사용법: %s <파일1> [파일2 ...]\n", argv[0]);
        return 1;
    }

    vector<FILE*> files;
    for (int i = 1; i < argc; i++) {
        FILE* file = fopen(argv[i], "rb");
        if (file == NULL) {
            printf("%s 파일이 존재하지 않습니다.\n", argv[i]);
            for (FILE* f : files) {
                fclose(f);
            }
            return 1;
        }
        files.push_back(file);
    }

    vector<uint32_t> fdata;
    uint32_t temp;
    for (FILE* f : files) {
        if (fread(&temp, sizeof(uint32_t), 1, f) != 1) {
            printf("파일 읽기 실패\n");
            for (FILE* f : files) {
                fclose(f);
            }
            return 1;
        }
        fdata.push_back(temp);
    }

    for (FILE* f : files) {
        fclose(f);
    }

    uint32_t sum = 0;
    for (int i = 0; i < fdata.size(); i++) {
        fdata[i] = ntohl(fdata[i]);
        sum += fdata[i];
        
        if (i == fdata.size() - 1) {
            printf("%u(0x%x)", fdata[i], fdata[i]);
        } else {
            printf("%u(0x%x) + ", fdata[i], fdata[i]);
        }
    }
    printf(" = %u(0x%x)\n", sum, sum);

    return 0;
}