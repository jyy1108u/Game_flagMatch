#define _CRT_SECURE_NO_WARNINGS

#include <bangtal.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//전역변수 선언
SceneID gamemain; //메인 게임화면 세팅

ObjectID mainchar, heart, order, emotion;

TimerID jumpUP, jumpDown, jumpMove; //점프 올라갈때/내려갈때 타이머

TimerID WaitOrder; //이 타이머가 끝나면 오더를 표시
TimerID emotionTimer;

int poseNum = 0; //초깃값 0
int charY = 180; //캐릭터 x좌표 변수
int Level = 1; //초기 단계 1
int orderNum = 0;

bool sitdown = false; //깃발, 앉은상태의 bool 변수
bool jumpup = true; //초기에는 위로 올라감.
bool doOrder = false; //조작가능한 시간.

//0번이 모두 내림, 1번은 백기만 올림, 2번은 청기만 올림, 3번은 둘다 올림이다.

//청기, 백기, 점프, 앉아, 일어나
bool KeyboradInput[5] = { false, false, false, false, false};

struct Order
{
    const char* orderfile; //오더 파일명
    int key;
};

struct Order orderList_Lv1[7] = {
    {"images/order/Lv1/청기올려.png", 0 },
    {"images/order/Lv1/백기올려.png", 0 },
    {"images/order/Lv1/청기내려.png", 0 },
    {"images/order/Lv1/백기내려.png",1},
    {"images/order/Lv1/점프.png",2},
    {"images/order/Lv1/앉아.png",3},
    {"images/order/Lv1/일어나.png",4}
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

    if (Level == 1) { //1단계에서

        srand((unsigned int)time(NULL));
        int num = rand() % 7; // 0~6 난수 생성
        orderNum = num; //오더넘버에 숫자를 저장

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
    }

    setTimer(WaitOrder, 3.0f);
    startTimer(WaitOrder);
}


//상태가 요구에 맞는지 확인하는 함수
void CheckStatus() {

    for (int i = 0; i < 5; i++) {
        if ((!KeyboradInput[i] && (i == orderList_Lv1[orderNum].key)) || (KeyboradInput[i] && (i != orderList_Lv1[orderNum].key))) {
            setObjectImage(emotion, "images/s_fail.png");
            break;
        }
        else {
            if (i == 4) {
                setObjectImage(emotion, "images/success.png");
            }
        }
    }

    for (int i = 0; i < 5; i++) {
        KeyboradInput[i] = false; //키보드인풋 초기화
    }
}


//키보드콜백
void keyboardCallback(KeyCode code, KeyState state)
{    
    if (doOrder) { //doOrder가 활성화될때만 입력 가능.
        if (code == KeyCode::KEY_A && state == KeyState::KEY_PRESSED) {	//청기
            KeyboradInput[0] = true;
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
            KeyboradInput[1] = true;
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
            KeyboradInput[4] = true;
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
        }
        else if (code == KeyCode::KEY_S && state == KeyState::KEY_PRESSED) { //앉아
            KeyboradInput[3] = true;
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
        }
        else if (code == KeyCode::KEY_SPACE && state == KeyState::KEY_PRESSED) { //점프
            KeyboradInput[2] = true;
            jumpMove = createTimer(0.01f);
            jumpUP = createTimer(0.12f);
            startTimer(jumpMove); //타이머 시작
            startTimer(jumpUP); //타이머 
        }
    }
}


//타이머콜백
void TimercallBack(TimerID timer) {
    
    if (timer == WaitOrder) { //오더가 끝나면
        
        doOrder = false; 
        CheckStatus(); //성공 or 실패 체킹
        emotionTimer = createTimer(1.0f);
        startTimer(emotionTimer);
    }

    if (timer == emotionTimer) {
        setObjectImage(emotion, "images/none.png");//감정 제거
        ShowCorrectOrder();
        doOrder = true;
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


//메인함수
int main()
{
    //메인 씬 생성
    gamemain = createScene("청기백기", "images/background.png");

    //오브젝트 생성
    mainchar = CreateObject1("images/char_0.png", 230, charY); //캐릭터
    order = CreateObject1("images/none.png", 132, 516); //명령창_초기에는 투명
    emotion = CreateObject1("images/none.png", 585, 322); //감정표현

    //오브젝트 보이기
    showObject(mainchar); showObject(order); showObject(emotion);

    WaitOrder = createTimer(1.0f); //기다리는 타이머_첫 오더는 1초 이후
    showTimer(WaitOrder);
    startTimer(WaitOrder);

    //기본 레이아웃 감추기
    setGameOption(GameOption::GAME_OPTION_INVENTORY_BUTTON, false);
    setGameOption(GameOption::GAME_OPTION_MESSAGE_BOX_BUTTON, false);
    setGameOption(GameOption::GAME_OPTION_ROOM_TITLE, false);

    //콜백함수 등록
    setKeyboardCallback(keyboardCallback);
    setTimerCallback(TimercallBack);

    startGame(gamemain);
}
