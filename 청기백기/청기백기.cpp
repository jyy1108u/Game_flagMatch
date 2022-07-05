#define _CRT_SECURE_NO_WARNINGS

#include <bangtal.h>
#include <stdio.h>

//전역변수 선언
SceneID gamemain; //메인 게임화면 세팅

ObjectID mainchar, flagB, flagW, heart, order;
ObjectID charjump[3]; //점프 애니메이팅
ObjectID orderList[10]; //오더 목록 넣을 배열


//오브젝트 배치용 함수 선언(show여부는 제외함)
ObjectID CreateObject1(const char* Obimage, int x, int y) {
    ObjectID object = createObject(Obimage);
    locateObject(object, gamemain, x, y);
    return object;
}


//깃발 올리고 내리는 함수
void flagMoving() {


}


//


//메인함수
int main()
{
    //메인 씬 생성
    gamemain = createScene("청기백기", "images/background.png");

    //오브젝트 생성
    mainchar = CreateObject1("images/mainchar_0.png", 485, 180); //캐릭터
    flagB = CreateObject1("images/flag_B.png", 268, 200); //깃발_청기
    flagW = CreateObject1("images/flag_W.png", 773, 200); //깃발_백기

    order = CreateObject1("images/orderwin.png", 132, 516); //명령창

    //오브젝트 보이기
    showObject(mainchar); showObject(flagB); showObject(flagW); showObject(order);

    //기본 레이아웃 감추기
    setGameOption(GameOption::GAME_OPTION_INVENTORY_BUTTON, false);
    setGameOption(GameOption::GAME_OPTION_MESSAGE_BOX_BUTTON, false);
    setGameOption(GameOption::GAME_OPTION_ROOM_TITLE, false);

    startGame(gamemain);
}
