#define _CRT_SECURE_NO_WARNINGS

#include <bangtal.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//전역변수 선언
SceneID gamemain, mainmenu; //메인 게임화면 세팅

ObjectID startbutton; 
ObjectID mainchar, heart[3], order, emotion, LevelShow, LevelClear, nextbutton, restartbutton, exitbutton;

TimerID jumpUP, jumpDown, jumpMove; //점프 올라갈때/내려갈때 타이머

TimerID WaitOrder, inTimer; //이 타이머가 끝나면 오더를 표시
TimerID emotionTimer;

int poseNum = 0; //초깃값 0
int charY = 180; //캐릭터 x좌표 변수
int Level = 1; //초기 단계 1
int orderNum = 0;
int orderClearCount = 0; //오더 점수 매기는 변수 (겉으로는 보이지 않는다)

bool sitdown = false; //깃발, 앉은상태의 bool 변수
bool jumpup = true; //초기에는 위로 올라감.
bool doOrder = false; //조작가능한 시간.
bool Heart_ex[3] = { true, true, true };

SoundID bgm, win, lose, sit, flag, jump, orderS, right, wrong, pop; //사운드

//0번이 모두 내림, 1번은 백기만 올림, 2번은 청기만 올림, 3번은 둘다 올림이다.

//청기, 백기, 점프, 앉아, 일어나
bool KeyboradInput[5] = { false, false, false, false, false };

struct Order_Lv1
{
    const char* orderfile; //오더 파일명
    int key;
};

struct Order_Lv2
{
    const char* orderfile; //오더 파일명
    int key1;
    int Key2;
};

struct Order_Lv3
{
    const char* orderfile; //오더 파일명
    int key1;
    int Key2;
    int Key3; 
};

struct Order_Lv1 orderList_Lv1[7] = {
    {"images/order/Lv1/청기올려.png", 0 },
    {"images/order/Lv1/백기올려.png", 1 },
    {"images/order/Lv1/청기내려.png", 0 },
    {"images/order/Lv1/백기내려.png", 1 },
    {"images/order/Lv1/점프.png", 2 },
    {"images/order/Lv1/앉아.png", 3 },
    {"images/order/Lv1/일어나.png", 4 }
};

struct Order_Lv2 orderList_Lv2[16] = {
    {"images/order/Lv2/백기내리고앉아.png", 1, 3 },
    {"images/order/Lv2/백기내리고점프.png", 1, 2 },
    {"images/order/Lv2/백기올리고앉아.png", 1, 3 },
    {"images/order/Lv2/백기올리고점프.png", 1, 2 },
    {"images/order/Lv2/백기올리고청기내려.png", 0, 1 },
    {"images/order/Lv2/일어나고백기내려.png", 4, 1 },
    {"images/order/Lv2/일어나고백기올려.png", 4, 1 },
    {"images/order/Lv2/일어나고청기내려.png", 4, 0 },
    {"images/order/Lv2/일어나고청기올려.png", 0, 4 },
    {"images/order/Lv2/청기내리고백기내려.png", 1, 0 },
    {"images/order/Lv2/청기내리고앉아.png", 0, 3 },
    {"images/order/Lv2/청기내리고점프.png", 0, 2 },
    {"images/order/Lv2/청기올리고백기내려.png", 0, 1 },
    {"images/order/Lv2/청기올리고백기올려.png", 0, 1 },
    {"images/order/Lv2/청기올리고앉아.png", 0, 3 },
    {"images/order/Lv2/청기올리고점프.png", 0, 2 }
};

struct Order_Lv3 orderList_Lv3[34] = {

    //LV2와 같은 항목
    {"images/order/Lv2/백기내리고앉아.png", 1, 1, 3 },
    {"images/order/Lv2/백기내리고점프.png", 1, 1, 2 },
    {"images/order/Lv2/백기올리고앉아.png", 1, 1, 3 },
    {"images/order/Lv2/백기올리고점프.png", 1, 1, 2 },
    {"images/order/Lv2/백기올리고청기내려.png", 0, 0, 1 },
    {"images/order/Lv2/일어나고백기내려.png", 4, 4, 1 },
    {"images/order/Lv2/일어나고백기올려.png", 4, 4, 1 },
    {"images/order/Lv2/일어나고청기내려.png", 4, 4, 0 },
    {"images/order/Lv2/일어나고청기올려.png", 0, 0, 4 },
    {"images/order/Lv2/청기내리고백기내려.png", 1, 1, 0 },
    {"images/order/Lv2/청기내리고앉아.png", 0, 0, 3 },
    {"images/order/Lv2/청기내리고점프.png", 0, 0, 2 },
    {"images/order/Lv2/청기올리고백기내려.png", 0, 0, 1 },
    {"images/order/Lv2/청기올리고백기올려.png", 0, 0, 1 },
    {"images/order/Lv2/청기올리고앉아.png", 0, 0, 3 },
    {"images/order/Lv2/청기올리고점프.png", 0, 0, 2 },

    //LV3에서 추가된 항목
    {"images/order/Lv3/백기올리지말고앉아.png", 3, 3, 3 },
    {"images/order/Lv3/백기올리지말고청기올려.png", 0, 0, 0 },
    {"images/order/Lv3/앉고점프하고백기내려.png", 3, 2, 1 },
    {"images/order/Lv3/앉고점프하고백기올려.png", 3, 2, 1 },
    {"images/order/Lv3/앉고점프하고청기내려.png", 3, 2, 0 },
    {"images/order/Lv3/앉고점프하고청기올려.png", 3, 2, 0 },
    {"images/order/Lv3/앉지말고백기내려.png", 1, 1, 1 },
    {"images/order/Lv3/앉지말고백기올려.png", 1, 1, 1 },
    {"images/order/Lv3/앉지말고점프.png", 2, 2, 2 },
    {"images/order/Lv3/앉지말고청기내려.png", 0, 0, 0 },
    {"images/order/Lv3/앉지말고청기올려.png", 0, 0, 0 },
    {"images/order/Lv3/점프하지말고백기내려.png", 1, 1, 1 },
    {"images/order/Lv3/점프하지말고백기올려.png", 1, 1, 1 },
    {"images/order/Lv3/점프하지말고앉아.png", 3, 3, 3 },
    {"images/order/Lv3/점프하지말고청기내려.png", 0, 0, 0 },
    {"images/order/Lv3/점프하지말고청기올려.png", 0, 0, 0 },
    {"images/order/Lv3/청기올리지말고백기올려.png", 1, 1, 1 },
    {"images/order/Lv3/청기올리지말고앉아.png", 3, 3, 3 }
};


//오브젝트 배치용 함수 선언(show여부는 제외함)
ObjectID CreateObject1(const char* Obimage, int x, int y) {
    ObjectID object = createObject(Obimage);
    locateObject(object, gamemain, x, y);
    return object;
}


//이미지 변경해주는 함수
void changeImagechar(const char *filename, int num) {
    setObjectImage(mainchar, filename); //2번으로 변경
    poseNum = num; //포즈번호 변경
}


//오더 표시하는 함수
void ShowCorrectOrder() {

    doOrder = true;
    playSound(orderS);

    if (Level == 1) { //1단계에서

        srand((unsigned int)time(NULL));
        int num = rand() % 7; // 0~6 난수 생성

        if (poseNum == 0) { //둘다 false인상태
            
            if (sitdown) {
                if (num == 2 || num == 3 || num == 5) {
                    num = rand() % 2;
                    setObjectImage(order, orderList_Lv1[num].orderfile);
                } //2,3,5일때는 0,1중 하나의 오더로....
                else {
                    setObjectImage(order, orderList_Lv1[num].orderfile); //오더 이미지를 생성하기
                }
            }
            else {
                if (num == 2 || num == 3 || num == 6) {
                    num = num - 2;
                    setObjectImage(order, orderList_Lv1[num].orderfile);
                }
                else {
                    setObjectImage(order, orderList_Lv1[num].orderfile); //오더 이미지를 생성하기
                }

            }
        }
        else if (poseNum == 1) {
            
            if (sitdown) {
                if (num == 1 || num == 2 || num == 5) {
                    num = (rand() % 2) + 3;
                    setObjectImage(order, orderList_Lv1[num].orderfile);
                }
                else {
                    setObjectImage(order, orderList_Lv1[num].orderfile); //오더 이미지를 생성하기
                }
            }
            else {
                if (num == 1 || num == 2 || num == 6) {
                    num = (rand() % 2) + 3;
                    setObjectImage(order, orderList_Lv1[num].orderfile);
                }
                else {
                    setObjectImage(order, orderList_Lv1[num].orderfile); //오더 이미지를 생성하기
                }

            }
        }
        else if (poseNum == 2) {
            
            if (sitdown) {
                if (num == 0 || num == 3 || num == 5) {
                    num = num + 1;
                    setObjectImage(order, orderList_Lv1[num].orderfile);
                }
                else {
                    setObjectImage(order, orderList_Lv1[num].orderfile); //오더 이미지를 생성하기
                }
            }
            else {
                if (num == 0 || num == 3 || num == 6) {
                    num = (rand() % 2) + 1;
                    setObjectImage(order, orderList_Lv1[num].orderfile);
                }
                else {
                    setObjectImage(order, orderList_Lv1[num].orderfile); //오더 이미지를 생성하기
                }

            }
        }
        else if (poseNum == 3) {
            
            if (sitdown) {
                if (num == 0 || num == 1 || num == 5) {
                    num = (rand() % 3) + 2;
                    setObjectImage(order, orderList_Lv1[num].orderfile);
                }
                else {
                    setObjectImage(order, orderList_Lv1[num].orderfile); //오더 이미지를 생성하기
                }
            }
            else {
                if (num == 0 || num == 1 || num == 6) {
                    num = (rand() % 4) + 2;
                    setObjectImage(order, orderList_Lv1[num].orderfile);
                }
                else {
                    setObjectImage(order, orderList_Lv1[num].orderfile); //오더 이미지를 생성하기
                }

            }
        }
        orderNum = num; //오더넘버에 숫자를 저장

        setTimer(WaitOrder, 3.0f); //1단계는 3초
        startTimer(WaitOrder);
    }

    if (Level == 2) { //2단계에서

        srand((unsigned int)time(NULL));

        if (poseNum == 0) { //둘다 false인상태 2,3,6,8,13 14 15

            if (sitdown) {
                int num[5] = { 3,6,8,13,15 };
                int pickNum = rand() % 5;
                orderNum = num[pickNum]; //오더넘버에 숫자를 저장
                setObjectImage(order, orderList_Lv2[num[pickNum]].orderfile);
                
            }
            else {
                int num[5] = { 2,3,13,14,15 };
                int pickNum = rand() % 5;
                orderNum = num[pickNum]; //오더넘버에 숫자를 저장
                setObjectImage(order, orderList_Lv2[num[pickNum]].orderfile);
            }
        }
        else if (poseNum == 1) {

            if (sitdown) {
                int num[5] = { 1,5,8,12,15 };
                int pickNum = rand() % 5;
                orderNum = num[pickNum]; //오더넘버에 숫자를 저장
                setObjectImage(order, orderList_Lv2[num[pickNum]].orderfile);

            }
            else {
                int num[5] = { 0,1,12,14,15 };
                int pickNum = rand() % 5;
                orderNum = num[pickNum]; //오더넘버에 숫자를 저장
                setObjectImage(order, orderList_Lv2[num[pickNum]].orderfile);
            }
        }
        else if (poseNum == 2) {

            if (sitdown) {
                int num[5] = { 3,4,6,7,11 };
                int pickNum = rand() % 5;
                orderNum = num[pickNum]; //오더넘버에 숫자를 저장
                setObjectImage(order, orderList_Lv2[num[pickNum]].orderfile);

            }
            else {
                int num[5] = { 2,3,4,10,11 };
                int pickNum = rand() % 5;
                orderNum = num[pickNum]; //오더넘버에 숫자를 저장
                setObjectImage(order, orderList_Lv2[num[pickNum]].orderfile);
            }
        }
        else if (poseNum == 3) {

            if (sitdown) {
                int num[5] = { 1,5,7,9,11 };
                int pickNum = rand() % 5;
                orderNum = num[pickNum]; //오더넘버에 숫자를 저장
                setObjectImage(order, orderList_Lv2[num[pickNum]].orderfile);

            }
            else {
                int num[5] = { 0,1,9,10,11 };
                int pickNum = rand() % 5;
                orderNum = num[pickNum]; //오더넘버에 숫자를 저장
                setObjectImage(order, orderList_Lv2[num[pickNum]].orderfile);
            }
        }

        setTimer(WaitOrder, 2.0f);
        startTimer(WaitOrder);
    }

    if (Level == 3) { //3단계에서

        srand((unsigned int)time(NULL));

        if (poseNum == 0) { //둘다 false인상태

            if (sitdown) {
                int num[9] = { 3,6,8,13,15,17,28,31,32 };
                int pickNum = rand() % 9;
                orderNum = num[pickNum]; //오더넘버에 숫자를 저장
                setObjectImage(order, orderList_Lv3[num[pickNum]].orderfile);

            }
            else {
                int num[13] = { 2,3,13,14,15,16,19,21,23,24,26,29,33 };
                int pickNum = rand() % 13;
                orderNum = num[pickNum]; //오더넘버에 숫자를 저장
                setObjectImage(order, orderList_Lv3[num[pickNum]].orderfile);
            }
        }
        else if (poseNum == 1) {

            if (sitdown) {
                int num[7] = { 1,5,8,12,15,27,31 };
                int pickNum = rand() % 7;
                orderNum = num[pickNum]; //오더넘버에 숫자를 저장
                setObjectImage(order, orderList_Lv3[num[pickNum]].orderfile);

            }
            else {
                int num[13] = { 0,1,12,14,15,18,21,22,24,26,27,29,33 };
                int pickNum = rand() % 13;
                orderNum = num[pickNum]; //오더넘버에 숫자를 저장
                setObjectImage(order, orderList_Lv3[num[pickNum]].orderfile);
            }
        }
        else if (poseNum == 2) {

            if (sitdown) {
                int num[8] = { 3,4,6,7,11,28,30 };
                int pickNum = rand() % 8;
                orderNum = num[pickNum]; //오더넘버에 숫자를 저장
                setObjectImage(order, orderList_Lv3[num[pickNum]].orderfile);

            }
            else {
                int num[12] = { 2,3,4,10,11,16,19,20,23,24,25,29 };
                int pickNum = rand() % 12;
                orderNum = num[pickNum]; //오더넘버에 숫자를 저장
                setObjectImage(order, orderList_Lv3[num[pickNum]].orderfile);
            }
        }
        else if (poseNum == 3) {

            if (sitdown) {
                int num[7] = { 1,5,7,9,11,27,30 };
                int pickNum = rand() % 7;
                orderNum = num[pickNum]; //오더넘버에 숫자를 저장
                setObjectImage(order, orderList_Lv3[num[pickNum]].orderfile);

            }
            else {
                int num[11] = { 0,1,9,10,11,18,20,22,24,25,29 };
                int pickNum = rand() % 11;
                orderNum = num[pickNum]; //오더넘버에 숫자를 저장
                setObjectImage(order, orderList_Lv3[num[pickNum]].orderfile);
            }
        }

        setTimer(WaitOrder, 2.0f);
        startTimer(WaitOrder);
    }
}


//상태가 요구에 맞는지 확인하는 함수
void CheckStatus() {

    for (int i = 0; i < 5; i++) {
        if (Level == 1) {
            if ((!KeyboradInput[i] && (i == orderList_Lv1[orderNum].key)) || (KeyboradInput[i] && (i != orderList_Lv1[orderNum].key))) {
                setObjectImage(emotion, "images/s_fail.png");
                playSound(wrong);

                if (Heart_ex[0]) {
                    setObjectImage(heart[0], "images/none.png");
                    Heart_ex[0] = false;
                }
                else if (Heart_ex[1]) {
                    setObjectImage(heart[1], "images/none.png");
                    Heart_ex[1] = false;
                }
                else if (Heart_ex[2]) { //게임 종료!
                    setObjectImage(heart[2], "images/none.png");
                    Heart_ex[2] = false;
                    doOrder = false;
                }

                break;
            }
            else {
                if (i == 4) {
                    setObjectImage(emotion, "images/success.png");
                    playSound(right);
                    orderClearCount++; //점수 추가
                }
            }
        }
        else if (Level == 2) {
            if ((KeyboradInput[i] && ((i == orderList_Lv2[orderNum].key1) || (i == orderList_Lv2[orderNum].Key2))) || 
                (!KeyboradInput[i] && ((i != orderList_Lv2[orderNum].key1) && (i != orderList_Lv2[orderNum].Key2)))) {
                if (i == 4) {
                    setObjectImage(emotion, "images/success.png");
                    playSound(right);
                    orderClearCount++; //점수 추가
                }
            }
            else {
                setObjectImage(emotion, "images/s_fail.png");
                playSound(wrong);

                if (Heart_ex[0]) {
                    setObjectImage(heart[0], "images/none.png");
                    Heart_ex[0] = false;
                }
                else if (Heart_ex[1]) {
                    setObjectImage(heart[1], "images/none.png");
                    Heart_ex[1] = false;
                }
                else if (Heart_ex[2]) { //게임 종료!
                    setObjectImage(heart[2], "images/none.png");
                    Heart_ex[2] = false;
                    doOrder = false;
                }

                break;
            }
        }
        else if (Level == 3) {
            if ((KeyboradInput[i] && ((i == orderList_Lv3[orderNum].key1) || (i == orderList_Lv3[orderNum].Key2) || (i == orderList_Lv3[orderNum].Key3))) ||
                (!KeyboradInput[i] && ((i != orderList_Lv3[orderNum].key1) && (i != orderList_Lv3[orderNum].Key2) && (i != orderList_Lv3[orderNum].Key3)))) {
                if (i == 4) {
                    setObjectImage(emotion, "images/success.png");
                    playSound(right);
                    orderClearCount++; //점수 추가
                }
            }
            else {
                setObjectImage(emotion, "images/s_fail.png");
                playSound(wrong);

                if (Heart_ex[0]) {
                    setObjectImage(heart[0], "images/none.png");
                    Heart_ex[0] = false;
                }
                else if (Heart_ex[1]) {
                    setObjectImage(heart[1], "images/none.png");
                    Heart_ex[1] = false;
                }
                else if (Heart_ex[2]) { //게임 종료!
                    setObjectImage(heart[2], "images/none.png");
                    Heart_ex[2] = false;
                    doOrder = false;
                }

                break;
            }
        }
        
    }
}


//스테이지 레벨 올리기 체크하는 함수
void CheckNextLevel() {

    if (Level == 1) { //1레벨이면
        if (orderClearCount > 10) {
            doOrder = false;
            setObjectImage(LevelClear, "images/stageClear.png"); 
            showObject(LevelClear);
            showObject(nextbutton); //버튼 보이기
            stopSound(bgm);
            playSound(win);
        }
        else {
            if (!Heart_ex[2]) { //게임이 오버되었다면
                doOrder = false;
                setObjectImage(LevelClear, "images/stagefail.png"); //실패로 이미지 바꿈
                showObject(LevelClear); showObject(exitbutton); showObject(restartbutton);
                stopSound(bgm);
                playSound(lose);

            }
            else {
                setObjectImage(emotion, "images/none.png");//감정 제거
                ShowCorrectOrder();
                doOrder = true;
            }
        }
    }
    else if (Level == 2) { //1레벨이면
        if (orderClearCount > 15) {
            doOrder = false;
            setObjectImage(LevelClear, "images/stageClear.png");
            showObject(LevelClear);
            showObject(nextbutton); //버튼 보이기
            stopSound(bgm);
            playSound(win);
        }
        else {
            if (!Heart_ex[2]) { //게임이 오버되었다면
                doOrder = false;
                setObjectImage(LevelClear, "images/stagefail.png"); //실패로 이미지 바꿈
                showObject(LevelClear); showObject(exitbutton); showObject(restartbutton);
                stopSound(bgm);
                playSound(lose);
            }
            else {
                setObjectImage(emotion, "images/none.png");//감정 제거
                ShowCorrectOrder();
                doOrder = true;
            }
        }
    }
    else if (Level == 3) { //마지막 스테이지
        if (orderClearCount > 25) {
            doOrder = false;
            setObjectImage(LevelClear, "images/stageClear.png");
            showObject(LevelClear);
            showObject(exitbutton);
            stopSound(bgm);
            playSound(win);
        }
        else {
            if (!Heart_ex[2]) { //게임이 오버되었다면
                doOrder = false;
                setObjectImage(LevelClear, "images/stagefail.png"); //실패로 이미지 바꿈
                showObject(LevelClear); showObject(exitbutton); showObject(restartbutton);
                stopSound(bgm);
                playSound(lose);
            }
            else {
                setObjectImage(emotion, "images/none.png");//감정 제거
                ShowCorrectOrder();
                doOrder = true;
            }
        }
    }
}


//키보드콜백
void keyboardCallback(KeyCode code, KeyState state)
{    
    if (doOrder) { //doOrder가 활성화될때만 입력 가능.
        if (code == KeyCode::KEY_A && state == KeyState::KEY_PRESSED) {	//청기
            
            if (KeyboradInput[0]) KeyboradInput[0] = false;
            else KeyboradInput[0] = true;
            playSound(flag);

            if (poseNum == 0) { //0번 상태라면
                if (!sitdown) changeImagechar("images/char_2.png", 2);
                else changeImagechar("images/Schar_2.png", 2);
            }
            else if (poseNum == 1) { //1번 상태라면
                if (!sitdown) changeImagechar("images/char_3.png", 3);
                else changeImagechar("images/Schar_3.png", 3);
            }
            else if (poseNum == 2) {//2번 상태라면
                if (!sitdown) changeImagechar("images/char_0.png", 0);
                else changeImagechar("images/Schar_0.png", 0);
            }
            else if (poseNum == 3) { //3번 상태라면
                if (!sitdown) changeImagechar("images/char_1.png", 1);
                else changeImagechar("images/Schar_1.png", 1);
            }
        }
        else if (code == KeyCode::KEY_D && state == KeyState::KEY_PRESSED) { //백기
            
            if (KeyboradInput[1]) KeyboradInput[1] = false;
            else KeyboradInput[1] = true;
            playSound(flag);

            if (poseNum == 0) { //0번 상태라면
                if (!sitdown) changeImagechar("images/char_1.png", 1);
                else changeImagechar("images/Schar_1.png", 1);
            }
            else if (poseNum == 1) { //1번 상태라면
                if (!sitdown) changeImagechar("images/char_0.png", 0);
                else changeImagechar("images/Schar_0.png", 0);
            }
            else if (poseNum == 2) {//2번 상태라면
                if (!sitdown) changeImagechar("images/char_3.png", 3);
                else changeImagechar("images/Schar_3.png", 3);
            }
            else if (poseNum == 3) { //3번 상태라면
                if (!sitdown) changeImagechar("images/char_2.png", 2);
                else changeImagechar("images/Schar_2.png", 2);
            }
        }
        else if (code == KeyCode::KEY_W && state == KeyState::KEY_PRESSED) { //일어나
            if (sitdown) {
                KeyboradInput[4] = true;
                playSound(sit);

                if (poseNum == 0) { //0번 상태라면
                    changeImagechar("images/char_0.png", 0);
                }
                else if (poseNum == 1) { //1번 상태라면
                    changeImagechar("images/char_1.png", 1);
                }
                else if (poseNum == 2) {//2번 상태라면
                    changeImagechar("images/char_2.png", 2);
                }
                else if (poseNum == 3) { //3번 상태라면
                    changeImagechar("images/char_3.png", 3);
                }
                sitdown = false;
                locateObject(emotion, gamemain, 585, 322);
            }
        }
        else if (code == KeyCode::KEY_S && state == KeyState::KEY_PRESSED) { //앉아
            if (!sitdown) {
                KeyboradInput[3] = true;
                playSound(sit);

                if (poseNum == 0) { //0번 상태라면
                    changeImagechar("images/Schar_0.png", 0);
                }
                else if (poseNum == 1) { //1번 상태라면
                    changeImagechar("images/Schar_1.png", 1);
                }
                else if (poseNum == 2) {//2번 상태라면
                    changeImagechar("images/Schar_2.png", 2);
                }
                else if (poseNum == 3) { //3번 상태라면
                    changeImagechar("images/Schar_3.png", 3);
                }
                sitdown = true;
                locateObject(emotion, gamemain, 583, 303);
            }
        }
        else if (code == KeyCode::KEY_SPACE && state == KeyState::KEY_PRESSED) { //점프
            KeyboradInput[2] = true;
            jumpMove = createTimer(0.01f);
            jumpUP = createTimer(0.12f);
            startTimer(jumpMove); //타이머 시작
            startTimer(jumpUP); //타이머 
            playSound(jump);
        }
    }
}


//타이머콜백
void TimercallBack(TimerID timer) {

    if (timer == inTimer) { //맨 초기 타이머
        WaitOrder = createTimer(1.0f);
        ShowCorrectOrder();
        showTimer(WaitOrder); //시간 타이머는 표시해준다
    }
    
    if (timer == WaitOrder) { //오더가 끝나면
        
        doOrder = false; 
        CheckStatus(); //성공 or 실패 체킹

        emotionTimer = createTimer(1.0f);
        startTimer(emotionTimer);

        for (int i = 0; i < 5; i++) {
            KeyboradInput[i] = false; //키보드인풋 초기화
        }
    }

    if (timer == emotionTimer) {
        CheckNextLevel(); //다음레벨로 가는지 체크
    }
    
    if (timer == jumpMove) { //그림 올렸다 내리는 함수
        if (jumpup) {
            charY += 7;
            locateObject(mainchar, gamemain, 230, charY); //이동

            setTimer(jumpMove, 0.01f);
            startTimer(jumpMove); //타이머 재설정하고 재시작하기.
        }
        else {
            charY -= 7;
            locateObject(mainchar, gamemain, 230, charY); //이동

            setTimer(jumpMove, 0.01f);
            startTimer(jumpMove); //타이머 재설정하고 재시작하기.
        }
    }

    if (timer == jumpUP) {
        jumpup = false; //점프업을 false로..

        setTimer(jumpMove, 0.02f);
        jumpDown = createTimer(0.12f);

        startTimer(jumpMove); //타이머 재설정하고 재시작하기.
        startTimer(jumpDown); //타이머 시작
    }

    if (timer == jumpDown) {
        jumpup = true; //점프를 true로
        stopTimer(jumpMove);
        charY = 180;
        locateObject(mainchar, gamemain, 230, charY);
    }
}

void mouseCallack1(ObjectID obj, int x, int y, MouseAction act) {

    playSound(pop); //클릭 소리
    
    if (obj == nextbutton) { //다음 레벨 버튼을 눌렀을 때
        
        //하트 갯수 초기화, 하트 bool변수 초기화, 레벨 숫자 올리기, 레벨 표시 올리기, 점수 카운트 초기화, 오더넘버 초기화, 캐릭터 셋팅 초기화, 재시작
        hideObject(LevelClear); hideObject(nextbutton); //오브젝트 숨기기

        //하트 초기화
        for (int i = 0; i < 3; i++) {
            setObjectImage(heart[i], "images/heart.png");
            Heart_ex[i] = true;
        }

        //레벨
        if (Level == 1) setObjectImage(LevelShow, "images/L2.png"); //레벨이미지 변경
        else if (Level == 2) setObjectImage(LevelShow, "images/L3.png");
        Level = Level + 1; //레벨 업

        orderClearCount = 0; //점수 초기화
        orderNum = 0; //오더번호 초기화

        setObjectImage(order, "images/none.png"); //이전 오더 숨기기
        setObjectImage(emotion, "images/none.png"); //감정 숨기기
        setObjectImage(mainchar, "images/char_0.png"); //캐릭터 포즈 초기화
        poseNum = 0; //포즈넘버 초기화
        sitdown = false; //앉은변수
        locateObject(emotion, gamemain, 585, 322);

        stopSound(win); stopSound(lose); playSound(bgm);

        inTimer = createTimer(1.0f);
        startTimer(inTimer); //타이머 재시작
    }

    if (obj == restartbutton) {
        //하트 갯수 초기화, 하트 bool변수 초기화, 레벨 숫자 올리기, 레벨 표시 올리기, 점수 카운트 초기화, 오더넘버 초기화, 캐릭터 셋팅 초기화, 재시작
        hideObject(restartbutton); hideObject(exitbutton); hideObject(LevelClear); //오브젝트 숨기기

        //하트 초기화
        for (int i = 0; i < 3; i++) {
            setObjectImage(heart[i], "images/heart.png");
            Heart_ex[i] = true;
        }

        //레벨
        Level = 1; //1단계부터 재시작.
        setObjectImage(LevelShow, "images/L1.png"); //레벨이미지 변경

        orderClearCount = 0; //점수 초기화
        orderNum = 0; //오더번호 초기화

        setObjectImage(order, "images/none.png"); //이전 오더 숨기기
        setObjectImage(emotion, "images/none.png"); //감정 숨기기
        setObjectImage(mainchar, "images/char_0.png"); //캐릭터 포즈 초기화
        poseNum = 0; //포즈넘버 초기화
        sitdown = false; //앉은변수
        locateObject(emotion, gamemain, 585, 322);

        stopSound(win); stopSound(lose); playSound(bgm);

        inTimer = createTimer(1.0f);
        startTimer(inTimer); //타이머 재시작
    }

    if (obj == exitbutton) endGame(); //게임 종료하기.

    if (obj == startbutton) {

        enterScene(gamemain);

        //초기 타이머 설정
        inTimer = createTimer(1.0f);
        startTimer(inTimer);
    }
}


//메인함수
int main()
{
    //메인 씬 생성
    gamemain = createScene("청기백기", "images/background.png");
    mainmenu = createScene("메인메뉴", "images/mainmenu.png");

    //오브젝트 생성
    startbutton = createObject("images/startbutton.png");
    locateObject(startbutton, mainmenu, 529, 50);
    showObject(startbutton);

    mainchar = CreateObject1("images/char_0.png", 230, charY); //캐릭터
    order = CreateObject1("images/none.png", 132, 516); //명령창_초기에는 투명
    emotion = CreateObject1("images/none.png", 585, 322); //감정표현
    LevelShow = CreateObject1("images/L1.png", 72, 35); //레벨
    LevelClear = CreateObject1("images/stageClear.png", 0, 0); //스테이지 클리어 시 표시화면
    nextbutton = CreateObject1("images/nextbutton.png", 537, 295); //다음스테이지 버튼
    restartbutton = CreateObject1("images/restartbutton.png", 474, 290); //재시작 버튼
    exitbutton = CreateObject1("images/exitbutton.png", 700, 290); //나가기 버튼

    heart[0] = CreateObject1("images/heart.png", 1050, 32);
    heart[1] = CreateObject1("images/heart.png", 1115, 32);
    heart[2] = CreateObject1("images/heart.png", 1180, 32);

    //오브젝트 보이기
    showObject(mainchar); showObject(order); showObject(emotion);
    showObject(heart[0]); showObject(heart[1]); showObject(heart[2]);
    showObject(LevelShow);

    //사운드
    bgm = createSound("audios/Dizzy.mp3"); //0
    win = createSound("audios/win.mp3");
    lose = createSound("audios/lose.mp3");
    right = createSound("audios/right.mp3"); //0
    wrong = createSound("audios/wrong.mp3"); //0
    sit = createSound("audios/sit.mp3");
    jump = createSound("audios/jump.mp3");
    flag = createSound("audios/flag.mp3");
    orderS = createSound("audios/order.mp3");
    pop = createSound("audios/pop.mp3"); //0

    //브금 재생 시작
    playSound(bgm);

    //기본 레이아웃 감추기
    setGameOption(GameOption::GAME_OPTION_INVENTORY_BUTTON, false);
    setGameOption(GameOption::GAME_OPTION_MESSAGE_BOX_BUTTON, false);
    setGameOption(GameOption::GAME_OPTION_ROOM_TITLE, false);

    //콜백함수 등록
    setKeyboardCallback(keyboardCallback);
    setTimerCallback(TimercallBack);
    setMouseCallback(mouseCallack1); 

    startGame(mainmenu);
}
