#define _CRT_SECURE_NO_WARNINGS
#include <bangtal.h>
#include <iostream>
#include <time.h>
#include <stdlib.h>

#define L1Time 18
#define L2Time 20
#define L3Time 21
#define endCount 34

SceneID shop;
SceneID scene[5];
ObjectID start, gunsletter,notice,soundstick,safe,home,change1,change2,telling,shopButton,shopExit,pistol,riple,sniper;
ObjectID level[3], target[3], background[3], select[3],selected[3];
TimerID timer1, timer2, timer3, timer4, timer5;
SoundID fire, fire2, unfire, changed, BGM,ripleSound, sniperSound;
Second count2 = 0;
int x_pos[3] = { 0,0,0 }, y_pos[3] = { 0,0,0 }, clearC[3] = { 0,0,0 }, select_x_pos[3] = { 120,520,920 };
int score = 0, time2 =0, changeNum = 0,endIndex = 0,clickCount = 0,gunSound = 0;
char L1[256],L2[256],L3[256],T[256],TIMEOUT[256];

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
    score = 0;
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
    if (score == endCount || count2 == endCount) {
        enterScene(scene[1]);
        showObject(safe);
        hideObject(shopButton);
        hideTimer();
        stopTimer(timer1);
        stopTimer(timer2);
        setTimer(timer1, L1Time);
        setTimer(timer2, 1);
        setTimer(timer5, 0);
        playSound(BGM);
        count2 = 0;
        time2 = 0;
        endIndex = 0;
    }
}

//2단계 종료 함수
void checkend2() {
    if (score == endCount || count2 == endCount) {
        enterScene(scene[1]);
        showObject(safe);
        hideObject(shopButton);
        hideTimer();
        stopTimer(timer3);
        stopTimer(timer2);
        setTimer(timer3, L2Time);
        setTimer(timer2, 1);
        setTimer(timer5, 0);
        playSound(BGM);
        count2 = 0;
        time2 = 0;
        endIndex = 1;
    }
}

//3단계 종료 함수
void checkend3() {
    if (score == endCount || count2 == endCount) {
        enterScene(scene[1]);
        showObject(safe);
        hideObject(shopButton);
        hideTimer();
        stopTimer(timer4);
        stopTimer(timer2);
        setTimer(timer4, L3Time);
        setTimer(timer2, 1);
        setTimer(timer5, 0);
        playSound(BGM);
        count2 = 0;
        time2 = 0;
        endIndex = 2;
    }
}

//종료 메세지 지정 함수
void endMessage() {
    sprintf(L1, "총 %d초가 걸렸습니다!\n 2단계가 열렸습니다!", time2);
    sprintf(L2, "총 %d초가 걸렸습니다!\n 3단계가 열렸습니다!", time2);
    sprintf(L3, "총 %d초가 걸렸습니다!\n 축하합니다! 모두 클리어 하셨습니다!", time2);
    sprintf(T, "총 %d초가 걸렸습니다!", time2);
    sprintf(TIMEOUT, "시간이 초과됐습니다.\n총 %d점을 획득했습니다.", score);
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
        showMessage("타이머는 작동하나 상단에 표적을 맞힌\n 횟수가 표기됩니다.");
    }
    else {
        playSound(changed);
        hideObject(change2);
        showObject(change1);
        changeNum = 0;
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
    showObject(safe);
    hideObject(shopButton);
    playSound(BGM);
    setTimer(timer5, 0);
    count2 = 0;
    time2 = 0;
    endIndex = 3;
}

//마우스 콜백 함수
void mouseCallback(ObjectID object, int x, int y, MouseAction action) {
    if (object == start) {
        enterScene(scene[1]);
        playSound(fire2);
    }
    if (object == level[0]) {
        gamestart(2, 1080, 510, 0, timer1);
        clickCount = 0;
        playSound(fire2);
    }
    if (object == level[1]) {
        gamestart(3, 1160, 590, 1, timer3);
        clickCount = 0;
        playSound(fire2);
    }
    if (object == level[2]) {
        gamestart(4, 1240, 680, 2, timer4);
        clickCount = 0;
        playSound(fire2);
    }
    if (object == target[0]) {
        checkend1();
        movetarget(2, 0, 1080, 510);
        if (gunSound == 0) {
            playSound(fire);
        }
        if (gunSound == 1) {
            playSound(sniperSound);
        }
        if (gunSound == 2) {
            playSound(ripleSound);
        }

    }
    if (object == target[1]) {
        checkend2();
        movetarget(3, 1, 1160, 590);
        if (gunSound == 0) {
            playSound(fire);
        }
        if (gunSound == 1) {
            playSound(sniperSound);
        }
        if (gunSound == 2) {
            playSound(ripleSound);
        }
    }
    if (object == target[2]) {
        checkend3();
        movetarget(4, 2, 1240, 680);
        if (gunSound == 0) {
            playSound(fire);
        }
        if (gunSound == 1) {
            playSound(sniperSound);
        }
        if (gunSound == 2) {
            playSound(ripleSound);
        }
    }
    for (int i = 0; i < 3; i++) {
        if (object == background[i]) {
            subtractPoint();
        }
    }
    if (object == soundstick) {
        playSound(fire);
    }
    if (object == change1) {
        modeChange(1);
    }
    if (object == change2) {
        modeChange(2);
    }
    if (object == telling) {
        hideObject(telling);
    }
    if (object == start) {
        showMessage("게임 전 README 파일을 꼭 참고해주세요!");
    }
    if (object == safe) {
        clickCount++;
        if (clickCount == 3) {
            hideObject(safe);
            showObject(shopButton);
            switch (endIndex)
            {
            case 0:
                if (clearC[0] == 0) {
                    showMessage(L1);
                    showObject(level[1]);
                    clearC[0]++;
                }
                else {
                    showMessage(T);
                }
                break;
            case 1:
                if (clearC[1] == 0) {
                    showMessage(L2);
                    showObject(level[2]);
                    clearC[1]++;
                }
                else {
                    showMessage(T);
                }
                break;
            case 2:
                if (clearC[2] == 0) {
                    showMessage(L3);
                    clearC[2]++;
                }
                else {
                    showMessage(T);
                }
                break;
            case 3:
                showMessage(TIMEOUT);
                break;
            }
        }
    }
    if (object == shopButton) {
        enterScene(shop);
        showMessage("여기서 총을 바꿀 수 있습니다. \n총을 눌러 직접 쏘아 보세요!");
    }
    if (object == shopExit) {
        enterScene(scene[1]);
    }
    for (int i = 0; i < 3; i++) {
        if (object == select[i]) {
            if (i == 0) {
                hideObject(select[i]);
                hideObject(selected[i + 1]);
                hideObject(selected[i + 2]);
                showObject(select[i + 1]);
                showObject(select[i + 2]);
                showObject(selected[i]);
                gunSound = 2;
            }
            if (i == 1) {
                hideObject(select[i]);
                hideObject(selected[i - 1]);
                hideObject(selected[i + 1]);
                showObject(select[i - 1]);
                showObject(select[i + 1]);
                showObject(selected[i]);
                gunSound = 1;
            }
            if (i == 2) {
                hideObject(select[i]);
                hideObject(selected[i -  1]);
                hideObject(selected[i - 2]);
                showObject(select[i - 1]);
                showObject(select[i - 2]);
                showObject(selected[i]);
                gunSound = 0;
            }
        }
    }
    if (object == riple) {
        playSound(ripleSound);
    }
    if (object == sniper) {
        playSound(sniperSound);
    }
    if (object == pistol) {
        playSound(fire);
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

//게임 최초 실행 함수
void gameInit() {
    //랜덤함수의 시간 시드
    srand(time(NULL));

    //장면 생성
    scene[0] = createScene("GUNS", "guns.jpg");
    scene[1] = createScene("GUNS ready", "guns.jpg");
    scene[2] = createScene("LEVEL-1", "guns3.png");
    scene[3] = createScene("LEVEL-2", "guns3.png");
    scene[4] = createScene("LEVEL-3", "guns3.png");
    shop = createScene("SHOP", "finish.png");

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
    gunsletter = createObject("guns2.png", scene[0], 400, 500, true);
    start = createObject("start.png", scene[0], 510, 70, true);
    scaleObject(start, 0.3f);

    level[0] = createObject("level1.png", scene[1], 270, 20, true);
    level[1] = createObject("level2.png", scene[1], 570, 20, false);
    level[2] = createObject("level3.png", scene[1], 870, 20, false);
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

    safe = createObject("safe.png", scene[1], 0, 0, false);
    telling = createObject("telling.png", scene[0], 0, 0, true);

    shopButton = createObject("shop.png", scene[1], 1030, 600, true);
    scaleObject(shopButton, 0.05f);

    shopExit = createObject("exit.png", shop, 1210, 650, true);
    scaleObject(shopExit, 0.06f);

    riple = createObject("riple.png", shop, 100, 300, true);
    scaleObject(riple, 0.1f);

    sniper = createObject("sniper.png", shop, 500, 300, true);
    scaleObject(sniper, 0.1f);

    pistol = createObject("pistol.png", shop, 900, 300, true);
    scaleObject(pistol, 0.1f);

    for (int i = 0; i < 3; i++) {
        if (i == 0 || i == 1) {
            select[i] = createObject("select.png", shop, select_x_pos[i], 250, true);
        }
        else {
            select[i] = createObject("select.png", shop, select_x_pos[i], 250, false);
        }
    }
    
    for (int i = 0; i < 3; i++) {
        if (i == 0 || i == 1) {
            selected[i] = createObject("selected.png", shop, select_x_pos[i], 250, false);
        }
        else {
            selected[i] = createObject("selected.png", shop, select_x_pos[i], 250, true);
        }
    }

    //사운드 생성
    fire = createSound2("fire.mp3", false);
    fire2 = createSound2("fire2.mp3", false);
    unfire = createSound2("unfire.mp3", false);
    changed = createSound2("changed.mp3", false);
    BGM = createSound2("Sinking.mp3", true);
    ripleSound = createSound2("riple.mp3", false);
    sniperSound = createSound2("sniper.mp3", false);
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

    //오브젝트, 사운드, 타이머 생성 
    gameInit();

    startGame(scene[0]);
}
