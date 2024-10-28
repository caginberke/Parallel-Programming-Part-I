#include<windows.h>
#include"icb_gui.h"

int MLE1, MLE2;

int F1, F2, F3, F4, F5, F6;

ICBYTES ArcherStanding, ArrowR, MonsterR;
ICBYTES Forest, Archer, Arrow, Monster, Background, Temp, Hurt, HurtR, Dead, DeadR;
ICBYTES slimeFrame;

bool thread_continue = false;
bool thread2_continue = false;

bool thread_dead = false;

int slimeX = 480;
int slimeY = 280;
int arrowX = 50;

int width = 660;
int height = 450;

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

VOID* Animation(PVOID lpParam) {
    PasteNon0(ArcherStanding, 10, 250, Forest);

    // Slime Yürüyüþ Animasyonu
    ICBYTES cordinat{ {30, 30, 79, 56},{215,30,86,56},{405,35,86,51},{20,165,90,43},{210,165,95,43},
                      {405,165,91,43}, {20,280,86,46}, {215,280,81,46} };

    while (thread2_continue) {
        for (int frame = 0; frame < 8; frame++) { // Slime için 8 adýmlýk yürüyüþ animasyonu
            Copy(Background, 1, 1, 574, 322, Forest);  // Arka planý yenile
            Copy(Monster, cordinat.I(1, frame + 1), cordinat.I(2, frame + 1), cordinat.I(3, frame + 1), cordinat.I(4, frame + 1), slimeFrame);
            PasteNon0(slimeFrame, slimeX, slimeY, Forest);
            PasteNon0(ArcherStanding, 10, 250, Forest);  // Okçuyu sabit tut
            DisplayImage(F3, Forest);  // Güncellenmiþ resmi görüntüle

            slimeX -= 10;  // Slime sola doðru hareket ediyor
            Sleep(120);
        }
    }
    return NULL;
}

VOID* Shoot(PVOID lpParam) {
    ICBYTES cordinat{ {38, 54, 54, 74},{96,54,67,74},{100,54,63,74},{161,54,70,74},{230,54,73,74},
                      {300,54,71,74},{375,54,73,74},{446,54,93,74},{540,54,94,74},{636,54,90,74},
                      {726,54,82,74},{808,54,74,74},{952,54,69,74} };

    // Okçunun ok fýrlatma animasyonu
    for (int frame = 0; frame < 13; frame++) {
        Copy(Background, 1, 1, 574, 322, Forest);  // Arka planý yenile
        Copy(Archer, cordinat.I(1, frame + 1), cordinat.I(2, frame + 1), cordinat.I(3, frame + 1), cordinat.I(4, frame + 1), ArcherStanding);
        PasteNon0(ArcherStanding, 10, 250, Forest);  // Okçuyu çiz
        PasteNon0(slimeFrame, slimeX, slimeY, Forest);
        DisplayImage(F3, Forest);  // Güncellenmiþ resmi görüntüle
        Sleep(120);
    }


    // Okun slime’a doðru hareket etmesi
    while (arrowX < slimeX) {
        Copy(Background, 1, 1, 574, 322, Forest);  // Arka planý yenile
        PasteNon0(ArcherStanding, 10, 250, Forest);
        Copy(Arrow, 5, 5, 40, 40, ArrowR);
        PasteNon0(ArrowR, arrowX, 270, Forest);
        PasteNon0(slimeFrame, slimeX, slimeY, Forest);
        arrowX += 10;
        DisplayImage(F3, Forest);
        Sleep(30);
    }

    if (arrowX >= slimeX) {
        thread2_continue = false;

        // Slime vurulma animasyonu
        ICBYTES cor{ {25, 45, 150, 49}, {220, 40, 135, 54}, {410, 35, 125, 59}, {600, 35, 103, 59} };
        for (int frame = 0; frame < 4; frame++) {
            Copy(Background, 1, 1, 574, 322, Forest);
            PasteNon0(ArcherStanding, 10, 250, Forest);
            Copy(Hurt, cor.I(1, frame + 1), cor.I(2, frame + 1), cor.I(3, frame + 1), cor.I(4, frame + 1), HurtR);
            PasteNon0(HurtR, slimeX, slimeY, Forest);
            DisplayImage(F3, Forest);
            Sleep(350);
        }
    }

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

void ICGUI_main()
{

    for (int a = 1; a < 20; a++) {
        Sleep(70);
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
