#include <stdint.h>
#include <stdio.h>
#include <netinet/in.h>
#include <vector>
using namespace std;

void closeFiles(vector<FILE*>& files) {
    for (FILE* f : files) {
        fclose(f);
    }
}

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
            closeFiles(files);
            return 1;
        }

        // 파일 크기 확인
        fseek(file, 0, SEEK_END);
        long fileSize = ftell(file);
        rewind(file);

        if (fileSize < sizeof(uint32_t)) {
            printf("파일 %s의 크기가 너무 작습니다. (필요한 크기: 4바이트 이상)\n", argv[i]);
            fclose(file);
            closeFiles(files);
            return 1;
        }

        files.push_back(file);
    }

    vector<uint32_t> fdata;
    uint32_t temp;
    for (FILE* f : files) {
        if (fread(&temp, sizeof(uint32_t), 1, f) != 1) {
            printf("파일에서 4바이트 읽기 실패\n");
            closeFiles(files);
            return 1;
        }
        fdata.push_back(temp);
    }

    closeFiles(files);

    uint32_t sum = 0;
    for (size_t i = 0; i < fdata.size(); i++) {
        fdata[i] = ntohl(fdata[i]);
        sum += fdata[i];

        if (i == fdata.size() - 1) {
            printf("%u(0x%08x)", fdata[i], fdata[i]);
        } else {
            printf("%u(0x%08x) + ", fdata[i], fdata[i]);
        }
    }
    printf(" = %u(0x%08x)\n", sum, sum);

    return 0;
}
