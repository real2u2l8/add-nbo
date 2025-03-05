#include <stdint.h>
#include <stdio.h>
#include <netinet/in.h>
#include <vector>
using namespace std;

/*
주요 수정사항:
1. 명령행 인자 검사 추가 - 최소 1개 파일 필요
2. fread() 수정 - vector에 직접 쓰지 않고 임시변수 사용
3. 메모리 누수 방지 - 에러 발생시 열린 파일들 정리
4. 부호없는 정수형(uint32_t) 출력 포맷 수정 - %u 사용
5. 16진수 출력 포맷 수정 - 0x 접두어 추가
6. sum 변수 초기화 추가
7. 반복문에서 데이터 변환과 출력을 통합하여 효율성 개선
*/

int main(int argc, char* argv[]) {
    // 명령행 인자 검사
    if (argc < 2) {
        printf("사용법: %s <파일1> [파일2 ...]\n", argv[0]);
        return 1;
    }

    // 파일 열기
    vector<FILE*> files;
    for (int i = 1; i < argc; i++) {
        FILE* file = fopen(argv[i], "rb");
        if (file == NULL) {
            printf("%s 파일이 존재하지 않습니다.\n", argv[i]);
            // 열린 파일들 정리
            for (FILE* f : files) {
                fclose(f);
            }
            return 1;
        }
        files.push_back(file);
    }

    // 파일에서 데이터 읽기
    vector<uint32_t> fdata;
    uint32_t temp;
    for (FILE* f : files) {
        if (fread(&temp, sizeof(uint32_t), 1, f) != 1) {
            printf("파일 읽기 실패\n");
            // 에러 발생시 열린 파일들 정리
            for (FILE* f : files) {
                fclose(f);
            }
            return 1;
        }
        fdata.push_back(temp);
    }

    // 사용이 끝난 파일들 닫기
    for (FILE* f : files) {
        fclose(f);
    }

    // 데이터 변환 및 합계 계산
    uint32_t sum = 0;  // 합계 변수 초기화
    for (int i = 0; i < fdata.size(); i++) {
        fdata[i] = ntohl(fdata[i]);  // 네트워크 바이트 순서에서 호스트 바이트 순서로 변환
        sum += fdata[i];
        
        // 결과 출력 형식 지정
        if (i == fdata.size() - 1) {
            printf("%u(0x%x)", fdata[i], fdata[i]);
        } else {
            printf("%u(0x%x) + ", fdata[i], fdata[i]);
        }
    }
    printf(" = %u(0x%x)\n", sum, sum);

    return 0;
}