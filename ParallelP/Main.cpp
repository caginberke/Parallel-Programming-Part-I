#include "icb_gui.h"


int F3;

ICBYTES ArcherStanding, ArrowR, MonsterR;
ICBYTES Forest, Archer, Arrow, Monster, Background, Temp, Hurt, HurtR, Dead, DeadR;
ICBYTES slimeFrame;
//2 Different Threads for Starting Animation and Shoot Animation
bool thread_continue = false;
bool thread2_continue = false;
//For Slime and Arrow Starting Poing
int slimeX = 480;
int slimeY = 280;
int arrowX = 50;
//For Opening Animation
int width = 660;
int height = 450;


//I didn't know it was going to work (Çaðýn)
void ICGUI_Create(int width, int height)
{
    ICG_MWSize(width, height);
    ICG_MWTitle("SHOOT UP");
}

void ICGUI_Create()
{
    ICG_MWSize(width, height);
    ICG_MWTitle("SHOOT UP");
}


VOID* Animation(PVOID lpParam) { //Starting Animation (Çaðýn)
    PasteNon0(ArcherStanding, 10, 250, Forest);

    //SLime Walking Animation Coordinates
    ICBYTES cordinat{ {30, 30, 79, 56},{215,30,86,56},{405,35,86,51},{20,165,90,43},{210,165,95,43},
                      {405,165,91,43}, {20,280,86,46}, {215,280,81,46} };

    //Monster Walking Left Animation
    while (thread2_continue) {
        for (int frame = 0; frame < 8; frame++) { 
            Copy(Background, 1, 1, 574, 322, Forest);  
            Copy(Monster, cordinat.I(1, frame + 1), cordinat.I(2, frame + 1), cordinat.I(3, frame + 1), cordinat.I(4, frame + 1), slimeFrame);
            PasteNon0(slimeFrame, slimeX, slimeY, Forest);
            PasteNon0(ArcherStanding, 10, 250, Forest);  
            DisplayImage(F3, Forest);  
            slimeX -= 10; //We need this for walking and check if the arrow hit
            Sleep(120);
        }
    }
    return NULL;
}

VOID* Shoot(PVOID lpParam) { //Archer Shooting Animation, Arrow Animation, Slime(Hurt, Dying, Vanishing) Animation (Çaðýn)
    ICBYTES cordinat{ {38, 54, 54, 74},{96,54,67,74},{100,54,63,74},{161,54,70,74},{230,54,73,74},
                      {300,54,71,74},{375,54,73,74},{446,54,93,74},{540,54,94,74},{636,54,90,74},
                      {726,54,82,74},{808,54,74,74},{952,54,69,74} };

    //Shooting the Arrow Animation
    for (int frame = 0; frame < 13; frame++) {
        Copy(Background, 1, 1, 574, 322, Forest);
        Copy(Archer, cordinat.I(1, frame + 1), cordinat.I(2, frame + 1), cordinat.I(3, frame + 1), cordinat.I(4, frame + 1), ArcherStanding);
        PasteNon0(ArcherStanding, 10, 250, Forest);
        PasteNon0(slimeFrame, slimeX, slimeY, Forest);

        //Shoting Sound (Enes)
        if (frame == 5) {
            PlaySound("shoot.wav", NULL, SND_FILENAME | SND_ASYNC);
        }

        DisplayImage(F3, Forest); 
        Sleep(120);
    }

    //Arrow Movement Animation 
    while (arrowX < slimeX) {
        Copy(Background, 1, 1, 574, 322, Forest);  
        PasteNon0(ArcherStanding, 10, 250, Forest);
        Copy(Arrow, 5, 5, 40, 40, ArrowR);
        PasteNon0(ArrowR, arrowX, 270, Forest);
        PasteNon0(slimeFrame, slimeX, slimeY, Forest);
        arrowX += 10;
        DisplayImage(F3, Forest);
        Sleep(30);
    }

    //Checking if Slime got Hit
    if (arrowX >= slimeX) {
        thread2_continue = false;

        //Slime got Hit Animation
        ICBYTES cor{ {25, 45, 150, 49}, {220, 40, 135, 54}, {410, 35, 125, 59}, {600, 35, 103, 59} };
        for (int frame = 0; frame < 4; frame++) {
            Copy(Background, 1, 1, 574, 322, Forest);
            PasteNon0(ArcherStanding, 10, 250, Forest);
            Copy(Hurt, cor.I(1, frame + 1), cor.I(2, frame + 1), cor.I(3, frame + 1), cor.I(4, frame + 1), HurtR);
            PasteNon0(HurtR, slimeX, slimeY, Forest);
            
            //Ending Sound (Enes)
            if (frame == 3) {
                PlaySound("finish.wav", NULL, SND_FILENAME | SND_ASYNC);
            }

            DisplayImage(F3, Forest);
            Sleep(350);
        }
    }

    //Slime Diying Animation
    ICBYTES cord{ {10, 15, 79 ,46}, {200, 25, 86 ,36}, {390, 30, 91 ,31} };
    for (int e = 1; e < 4; e++) {
        Copy(Archer, 38, 54, 54, 74, ArcherStanding);
        Copy(Background, 1, 1, 574, 322, Forest);
        PasteNon0(ArcherStanding, 10, 250, Forest);
        Copy(Dead, cord.I(1, e), cord.I(2, e), cord.I(3, e), cord.I(4, e), DeadR);
        PasteNon0(DeadR, slimeX, 295, Forest);
        DisplayImage(F3, Forest);
        Sleep(280);
    }

    //Slime Vanishing Animation
    for (int k = 1; k < 51; k++) {
        Copy(Archer, 38, 54, 54, 74, ArcherStanding);
        Copy(Background, 1, 1, 574, 322, Forest);
        PasteNon0(ArcherStanding, 10, 250, Forest);
        PasteNon0(DeadR, slimeX, 295 + k, Forest);
        DisplayImage(F3, Forest);
        Sleep(300);
    }

    return NULL;
}

//Animation Button and Thread Starters (Çaðýn)
void butonfonk()
{
    DWORD dw;
    if (!thread_continue) {
        thread_continue = true;
        thread2_continue = true;
        CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Shoot, NULL, 0, &dw);
        CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Animation, NULL, 0, &dw);
        SetFocus(ICG_GetMainWindow());
    }
    else thread_continue = false;
}

//Where the Magic Happens (Çaðýn)
void ICGUI_main()
{
    for (int a = 1; a < 20; a++) {
        Sleep(40);
        ICGUI_Create(a * 34, a * 23.5);
    }

    F3 = ICG_FrameMedium(20, 50, 574, 322);

    ICG_Button(265, 5, 90, 40, "Start the Animation", butonfonk);

    ReadImage("archer.bmp", Archer);
    ReadImage("arrow.bmp", Arrow);
    ReadImage("forest.bmp", Background);
    Copy(Background, 1, 1, 574, 322, Forest);
    DisplayImage(F3, Forest);

    ReadImage("monsternew.bmp", Monster);
    ReadImage("hurt.bmp", Hurt);
    ReadImage("dead.bmp", Dead);
}