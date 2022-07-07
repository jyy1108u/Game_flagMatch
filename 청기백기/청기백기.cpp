#define _CRT_SECURE_NO_WARNINGS

#include <bangtal.h>
#include <stdio.h>

//전역변수 선언
SceneID gamemain; //메인 게임화면 세팅

ObjectID mainchar, heart, order;
ObjectID orderList[10]; //오더 목록 넣을 배열

TimerID jumpUP, jumpDown, jumpMove; //점프 올라갈때/내려갈때 타이머

int poseNum = 0; //초깃값 0
bool sitdown = false; //깃발, 앉은상태의 bool 변수

//0번이 모두 내림, 1번은 백기만 올림, 2번은 청기만 올림, 3번은 둘다 올림이다.


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


//키보드콜백
void keyboardCallback(KeyCode code, KeyState state)
{    
    if (code == KeyCode::KEY_A && state == KeyState::KEY_PRESSED) {	//청기
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
        
    }
}


//타이머콜백
void TimercallBack(TimerID timer) {



}


//메인함수
int main()
{
    //메인 씬 생성
    gamemain = createScene("청기백기", "images/background.png");

    //오브젝트 생성
    mainchar = CreateObject1("images/char_0.png", 230, 180); //캐릭터

    order = CreateObject1("images/orderwin.png", 132, 516); //명령창

    //오브젝트 보이기
    showObject(mainchar); showObject(order);

    //기본 레이아웃 감추기
    setGameOption(GameOption::GAME_OPTION_INVENTORY_BUTTON, false);
    setGameOption(GameOption::GAME_OPTION_MESSAGE_BOX_BUTTON, false);
    setGameOption(GameOption::GAME_OPTION_ROOM_TITLE, false);

    //콜백함수 등록
    setKeyboardCallback(keyboardCallback);
    setTimerCallback(TimercallBack);

    startGame(gamemain);
}
