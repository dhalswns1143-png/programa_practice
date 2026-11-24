#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {

    srand((unsigned int)time(NULL));

    const char* dirName[7] = {
        "↖", "←", "↙", "↕", "↗", "→", "↘"
    };

    int restart;
    int gameMode;

    char p1Name[20];
    char p2Name[20];

    do {

        printf("Player 1 닉네임 입력: ");
        scanf("%19s", p1Name);

        printf("Player 2 닉네임 입력: ");
        scanf("%19s", p2Name);

        printf("\n[%s] VS [%s]\n", p1Name, p2Name);

        // 점수 및 라운드 초기화
        int p1Score = 0, p2Score = 0;
        int p1Saves = 0, p2Saves = 0;
        int round = 1;

        // 게임 모드 선택
        do {
            printf("\n===== 게임 모드 선택 =====\n");
            printf("1. 일반 모드 (5라운드)\n");
            printf("2. 신속 모드 (단판)\n");
            printf("모드 선택: ");

            if (scanf("%d", &gameMode) != 1) {
                printf("숫자를 입력하세요.\n");
                while (getchar() != '\n');
                gameMode = 0;
            }
            else if (gameMode != 1 && gameMode != 2) {
                printf("1 또는 2를 선택하세요.\n");
            }

        } while (gameMode != 1 && gameMode != 2);

        // 일반 모드
        if (gameMode == 1) {

            printf("\n########## 일반 게임 ##########\n");

            while (round <= 5 || p1Score == p2Score) {

                if (round > 5)
                    printf("\n[ 서든데스 %d라운드 ]\n", round);
                else
                    printf("\n[ ROUND %d / 5 ]\n", round);

                for (int turn = 0; turn < 2; turn++) {

                    int shot = 0, keep = 0;

                    if (turn == 0)
                        printf("\n[%s 키커 vs %s 골키퍼]\n", p1Name, p2Name);
                    else
                        printf("\n[%s 키커 vs %s 골키퍼]\n", p2Name, p1Name);

                    // 키커 입력
                    do {
                        printf("\n방향 번호: 1. ↖, 2. ←, 3. ↙, 4. ↕, 5. ↗, 6. →, 7. ↘\n");
                        printf("키커 슛 방향 입력 (1~7): ");

                        if (scanf("%d", &shot) != 1) {
                            printf("잘못된 입력입니다. 숫자를 입력하세요.\n");
                            while (getchar() != '\n');
                            shot = 0;
                        }
                        else if (shot < 1 || shot > 7) {
                            printf("1~7 사이의 숫자를 입력하세요.\n");
                        }

                    } while (shot < 1 || shot > 7);

                    // 화면 정리
                    for (int i = 0; i < 40; i++)
                        printf("\n");

                    // 골키퍼 입력
                    do {
                        printf("\n방향 번호: 1. ↖, 2. ←, 3. ↙, 4. ↕, 5. ↗, 6. →, 7. ↘\n");
                        printf("골키퍼 막을 방향 입력 (1~7): ");

                        if (scanf("%d", &keep) != 1) {
                            printf("잘못된 입력입니다. 숫자를 입력하세요.\n");
                            while (getchar() != '\n');
                            keep = 0;
                        }
                        else if (keep < 1 || keep > 7) {
                            printf("1~7 사이의 숫자를 입력하세요.\n");
                        }

                    } while (keep < 1 || keep > 7);

                    // 슛 결과
                    printf("\n<< 키커:[%s] vs 골키퍼:[%s]\n",
                        dirName[shot - 1], dirName[keep - 1]);

                    if (shot != keep) {
                        printf(">> GOAL!! <<\n");

                        if (turn == 0) p1Score++;
                        else p2Score++;
                    }
                    else {
                        printf(">> SAVED!! <<\n");

                        if (turn == 0) p2Saves++;
                        else p1Saves++;
                    }

                    // 골대 및 공 위치 출력
                    printf("\n-------------------------------------\n");

                    if (shot == 1)      printf("-   O                               -\n");
                    else if (shot == 5) printf("-                               O   -\n");
                    else                printf("-                                   -\n");

                    printf("-                                   -\n");

                    if (shot != keep) {
                        if (shot == 2)      printf("-   O          GOAL                 -\n");
                        else if (shot == 4) printf("-             O GOAL                -\n");
                        else if (shot == 6) printf("-              GOAL             O   -\n");
                        else                printf("-              GOAL                 -\n");
                    }
                    else {
                        if (shot == 2)      printf("-   O          SAVE                 -\n");
                        else if (shot == 4) printf("-             O SAVE                -\n");
                        else if (shot == 6) printf("-              SAVE             O   -\n");
                        else                printf("-              SAVE                 -\n");
                    }

                    printf("-                                   -\n");

                    if (shot == 3)      printf("-   O                               -\n");
                    else if (shot == 7) printf("-                               O   -\n");
                    else                printf("-                                   -\n");

                    printf("\n");

                    printf("\n현재 점수 -> %s: %d골(선방 %d) vs %s: %d골(선방 %d)\n",
                        p1Name, p1Score, p1Saves,
                        p2Name, p2Score, p2Saves);
                }

                round++;
            }
        }

        // 신속 모드
        else if (gameMode == 2) {

            printf("\n########## 신속 게임 ##########\n");

            int shot = 0, keep = 0;

            // 키커 랜덤 결정
            int kicker = rand() % 2;

            if (kicker == 0)
                printf("\n[%s 키커 vs %s 골키퍼]\n", p1Name, p2Name);
            else
                printf("\n[%s 키커 vs %s 골키퍼]\n", p2Name, p1Name);

            // 키커 입력
            do {
                printf("\n방향 번호: 1. ↖, 2. ←, 3. ↙, 4. ↕, 5. ↗, 6. →, 7. ↘\n");
                printf("키커 슛 방향 입력 (1~7): ");

                if (scanf("%d", &shot) != 1) {
                    printf("잘못된 입력입니다. 숫자를 입력하세요.\n");
                    while (getchar() != '\n');
                    shot = 0;
                }
                else if (shot < 1 || shot > 7) {
                    printf("1~7 사이의 숫자를 입력하세요.\n");
                }

            } while (shot < 1 || shot > 7);

            // 화면 정리
            for (int i = 0; i < 40; i++)
                printf("\n");

            // 골키퍼 입력
            do {
                printf("\n방향 번호: 1. ↖, 2. ←, 3. ↙, 4. ↕, 5. ↗, 6. →, 7. ↘\n");
                printf("골키퍼 막을 방향 입력 (1~7): ");

                if (scanf("%d", &keep) != 1) {
                    printf("잘못된 입력입니다. 숫자를 입력하세요.\n");
                    while (getchar() != '\n');
                    keep = 0;
                }
                else if (keep < 1 || keep > 7) {
                    printf("1~7 사이의 숫자를 입력하세요.\n");
                }

            } while (keep < 1 || keep > 7);

            // 슛 결과
            printf("\n<< 키커:[%s] vs 골키퍼:[%s]\n",
                dirName[shot - 1], dirName[keep - 1]);

            if (shot != keep) {
                printf(">> GOAL!! <<\n");

                if (kicker == 0) p1Score++;
                else p2Score++;
            }
            else {
                printf(">> SAVED!! <<\n");

                if (kicker == 0) p2Saves++;
                else p1Saves++;
            }

            // 골대 및 공 위치 출력
            printf("\n-------------------------------------\n");

            if (shot == 1)      printf("-   O                               -\n");
            else if (shot == 5) printf("-                               O   -\n");
            else                printf("-                                   -\n");

            printf("-                                   -\n");

            if (shot != keep) {
                if (shot == 2)      printf("-   O          GOAL                 -\n");
                else if (shot == 4) printf("-             O GOAL                -\n");
                else if (shot == 6) printf("-              GOAL             O   -\n");
                else                printf("-              GOAL                 -\n");
            }
            else {
                if (shot == 2)      printf("-   O          SAVE                 -\n");
                else if (shot == 4) printf("-             O SAVE                -\n");
                else if (shot == 6) printf("-              SAVE             O   -\n");
                else                printf("-              SAVE                 -\n");
            }

            printf("-                                   -\n");

            if (shot == 3)      printf("-   O                               -\n");
            else if (shot == 7) printf("-                               O   -\n");
            else                printf("-                                   -\n");

            printf("\n");

        }

        // 최종 결과
        printf("\n\n");

        if (p1Score > p2Score)
            printf("********** 최종 우승: %s!! (%d : %d) **********\n",
                p1Name, p1Score, p2Score);
        else if (p2Score > p1Score)
            printf("********** 최종 우승: %s!! (%d : %d) **********\n",
                p2Name, p1Score, p2Score);
        else
            printf("%s 승!!\n", p2Name);


        // 재시작 여부
        do {
            printf("\n0. 다시 하기  1. 게임 종료\n");
            printf("선택: ");

            if (scanf("%d", &restart) != 1) {
                printf("잘못된 입력입니다. 0 또는 1을 입력하세요.\n");
                while (getchar() != '\n');
                restart = -1;
            }
            else if (restart != 0 && restart != 1) {
                printf("0 또는 1만 입력할 수 있습니다.\n");
            }

        } while (restart != 0 && restart != 1);

    } while (restart == 0);

    printf("\n### 게임 종료 ###\n\n");

    return 0;
}
