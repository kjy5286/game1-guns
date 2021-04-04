#define _CRT_SECURE_NO_WARNINGS
#include <bangtal.h>
#include <iostream>
#include <time.h>
#include <stdlib.h>

#define L1Time 15
#define L2Time 20
#define L3Time 26

SceneID scene[5];
ObjectID start, gunsletter,notice,soundstick,message,home,change1,change2;
ObjectID level[3], target[3], background[3];
TimerID timer1, timer2, timer3, timer4, timer5;
SoundID fire, fire2, unfire, changed, BGM;
Second count2 = 0;
int x_pos[3] = { 0,0,0 };
int y_pos[3] = { 0,0,0 };
int score = 0;
int clearC[3] = { 0,0,0 };
int time2 = 0;
char L1[256],L2[256],L3[256],T[256];
int changeNum = 0;

//소리 생성 함수
SoundID createSound2(const char* sound, bool que) {
    SoundID music = createSound(sound);
    if (que == true) {
        playSound(music);
    }
    return music;
}

//타이머 생성 함수
TimerID createTimer2(Second second) {
    TimerID timer = createTimer(second);
    return timer;
}

//게임 시작 함수
void gamestart(int SceneNumber, int x, int y, int index, TimerID timer) {
    enterScene(scene[SceneNumber]);
    stopSound(BGM);
    x_pos[index] = rand() % x;
    y_pos[index] = rand() % y;
    time2 = 0;
    locateObject(target[index], scene[SceneNumber], x_pos[index], y_pos[index]);
    showObject(target[index]);
    if (changeNum == 0) {
        showTimer(timer);
        startTimer(timer);
    }
    else {
        setTimer(timer5, 0);
        showTimer(timer5);
        startTimer(timer);
    }
    startTimer(timer2);
}

//1단계 종료 함수
void checkend1() {
    if (score == 39 || count2 == 39) {
        enterScene(scene[1]);
        if (clearC[0] == 0) {
            showMessage(L1);
            showObject(level[1]);
        }
        else {
            showMessage(T);
        }
        showObject(message);
        clearC[0]++;
        hideTimer();
        stopTimer(timer1);
        stopTimer(timer2);
        setTimer(timer1, L1Time);
        setTimer(timer2, 1);
        setTimer(timer5, 0);
        playSound(BGM);
        count2 = 0;
        score = 0;
        time2 = 0;
    }
}

//2단계 종료 함수
void checkend2() {
    if (score == 39 || count2 == 39) {
        enterScene(scene[1]);
        if (clearC[1] == 0) {
            showMessage(L2);
            showObject(level[2]);
        }
        else {
            showMessage(T);
        }
        showObject(message);
        clearC[1]++;
        hideTimer();
        stopTimer(timer3);
        stopTimer(timer2);
        setTimer(timer3, L2Time);
        setTimer(timer2, 1);
        setTimer(timer5, 0);
        playSound(BGM);
        count2 = 0;
        score = 0;
        time2 = 0;
    }
}

//3단계 종료 함수
void checkend3() {
    if (score == 39 || count2 == 39) {
        enterScene(scene[1]);
        if (clearC[2] == 0) {
            showMessage(L3);
        }
        else {
            showMessage(T);
        }
        showObject(message);
        clearC[2]++;
        hideTimer();
        stopTimer(timer4);
        stopTimer(timer2);
        setTimer(timer4, L3Time);
        setTimer(timer2, 1);
        setTimer(timer5, 0);
        playSound(BGM);
        count2 = 0;
        score = 0;
        time2 = 0;
    }
}

//종료 메세지 지정 함수
void endMessage() {
    sprintf(L1, "총 %d초가 걸렸습니다!\n 2단계가 열렸습니다!", time2);
    sprintf(L2, "총 %d초가 걸렸습니다!\n 3단계가 열렸습니다!", time2);
    sprintf(L3, "총 %d초가 걸렸습니다!\n 축하합니다! 모두 클리어 하셨습니다!", time2);
    sprintf(T, "총 %d초가 걸렸습니다!", time2);
}

//감점 함수
void subtractPoint() {
    playSound(unfire);
    count2 = getTimer(timer5);
    if (count2 > 0) {
        decreaseTimer(timer5, 1);
    }
    if (score > 0) {
        score--;
    }
}

//타이머, 카운트 모드 변경 함수
void modeChange(int x) {
    if (x == 1) {
        playSound(changed);
        hideObject(change1);
        showObject(change2);
        changeNum = 1;
        showObject(message);
        showMessage("타이머는 작동하나 상단에 표적을 맞힌\n 횟수가 표기됩니다.");
    }
    else {
        playSound(changed);
        hideObject(change2);
        showObject(change1);
        changeNum = 0;
        showObject(message);
        showMessage("타이머가 작동하고 상단에 타이머가 표기됩니다.");
    }
}

//타겟 이동 함수
void movetarget(int SceneNumber, int index, int x, int y) {
    score++;
    increaseTimer(timer5, 1);
    count2 = getTimer(timer5);
    hideObject(target[index]);
    x_pos[index] = rand() % x;
    y_pos[index] = rand() % y;
    locateObject(target[index], scene[SceneNumber], x_pos[index], y_pos[index]);
    showObject(target[index]);
}

//타임오버로 인한 게임 종료 함수
void Timeover(TimerID timer, int sec) {
    enterScene(scene[1]);
    hideTimer();
    setTimer(timer, sec);
    stopTimer(timer);
    showMessage("시간이 초과되었습니다.");
    playSound(BGM);
    showObject(message);
    setTimer(timer5, 0);
    count2 = 0;
    time2 = 0;
    score = 0;
}

//마우스 콜백 함수
void mouseCallback(ObjectID object, int x, int y, MouseAction action) {
    if (object == start) {
        enterScene(scene[1]);
        playSound(fire2);
    }
    if (object == level[0]) {
        gamestart(2, 1080, 510, 0, timer1);
        playSound(fire2);
    }
    if (object == level[1]) {
        gamestart(3, 1160, 590, 1, timer3);
        playSound(fire2);
    }
    if (object == level[2]) {
        gamestart(4, 1240, 680, 2, timer4);
        playSound(fire2);
    }
    if (object == target[0]) {
        checkend1();
        movetarget(2, 0, 1080, 510);
        playSound(fire);
    }
    if (object == target[1]) {
        checkend2();
        movetarget(3, 1, 1160, 590);
        playSound(fire);
    }
    if (object == target[2]) {
        checkend3();
        movetarget(4, 2, 1240, 680);
        playSound(fire);
    }
    if (object == background[0]) {
        subtractPoint();
    }
    if (object == background[1]) {
        subtractPoint();
    }
    if (object == background[2]) {
        subtractPoint();
    }
    if (object == soundstick) {
        playSound(fire);
        hideObject(message);
    }
    if (object == home || object == notice || object == message) {
        hideObject(message);
    }
    if (object == change1) {
        modeChange(1);
    }
    if (object == change2) {
        modeChange(2);
    }
}

//사운드 콜백 함수
void soundCallback(SoundID sound) {
    if (sound == BGM) {
        playSound(BGM);
    }
}

//타이머 콜백 함수
void timerCallback(TimerID timer) {
    if (timer == timer1) {
        Timeover(timer1, L1Time);
    }
    if (timer == timer2) {
        time2++;
        endMessage();
        setTimer(timer2, 1);
        startTimer(timer2);
    }
    if (timer == timer3) {
        Timeover(timer3, L2Time);
    }
    if (timer == timer4) {
        Timeover(timer4, L3Time);
    }
}

//오브젝트 생성 함수
ObjectID createObject(const char* image, SceneID scene, int x, int y, bool shown) {
    ObjectID object = createObject(image);
    locateObject(object, scene, x, y);
    if (shown == true) {
        showObject(object);
    }
    return object;
}

//메인 함수
int main()
{
    //인벤토리와 메세지 상자 삭제
    setGameOption(GameOption::GAME_OPTION_INVENTORY_BUTTON, false);
    setGameOption(GameOption::GAME_OPTION_MESSAGE_BOX_BUTTON, false);

    //콜백함수 호출
    setMouseCallback(mouseCallback);
    setTimerCallback(timerCallback);
    setSoundCallback(soundCallback);

    //랜덤함수의 시간 시드
    srand(time(NULL));

    //장면 생성
    scene[0] = createScene("GUNS", "guns.jpg");
    scene[1] = createScene("GUNS ready", "guns.jpg");
    scene[2] = createScene("LEVEL-1", "guns3.png");
    scene[3] = createScene("LEVEL-2", "guns3.png");
    scene[4] = createScene("LEVEL-3", "guns3.png");

    //타이머 생성
    timer1 = createTimer2(L1Time);
    timer2 = createTimer2(1);
    timer3 = createTimer2(L2Time);
    timer4 = createTimer2(L3Time);
    timer5 = createTimer2(0);

    //배경을 오브젝트로 생성
    home = createObject("guns.jpg", scene[1], 0, 0, true);
    
    for (int i = 0; i < 3; i++) {
        background[i] = createObject("guns3.png", scene[i + 2], 0, 0, true);
    }

    //주요 오브젝트 생성
    gunsletter = createObject("guns2.png", scene[0], 370, 500, true);
    start = createObject("start.png", scene[0], 510, 70, true);
    scaleObject(start, 0.3f);

    level[0] = createObject("level1.png", scene[1], 270, 100, true);
    level[1] = createObject("level2.png", scene[1], 570, 100, false);
    level[2] = createObject("level3.png", scene[1], 870, 100, false);
    notice = createObject("notice.png", scene[1], 20, 400, true);
    soundstick = createObject("stick.png", scene[1], 600, 288, true);
    scaleObject(soundstick, 0.03f);

    target[0] = createObject("target.png", scene[2], x_pos[0], y_pos[0], false);
    scaleObject(target[0], 0.25f);

    target[1] = createObject("target.png", scene[3], x_pos[1], y_pos[1], false);
    scaleObject(target[1], 0.15f);

    target[2] = createObject("target.png", scene[4], x_pos[2], y_pos[2], false);
    scaleObject(target[2], 0.05f);

    change1 = createObject("timermode.png", scene[1], 1150, 600, true);
    change2 = createObject("countmode.png", scene[1], 1150, 600, false);

    message = createObject("message.png", scene[1], 0, 0, false);

    //사운드 생성
    fire = createSound2("fire.mp3", false);
    fire2 = createSound2("fire2.mp3", false);
    unfire = createSound2("unfire.mp3", false);
    changed = createSound2("changed.mp3", false);
    BGM = createSound2("Sinking.mp3", true);

    startGame(scene[0]);
}
