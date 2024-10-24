#include<windows.h>
#include"icb_gui.h"
#include <iostream>
using namespace std;

int MLE1, MLE2;
	

int F1, F2, F3, F4, F5;

ICBYTES ArcherShoot[13]; //For archer sprite sheet
ICBYTES MonsterWalk[32]; //For monster sprite sheet
ICBYTES MonsterHurt[4]; //For monster sprite sheet

ICBYTES ArcherStanding, ArrowR, MonsterR;
ICBYTES Forest, Archer, Arrow, Monster, Background, Temp, Hurt , HurtR;

bool thread_continue = false;
bool thread2_continue = false;

bool thread_dead = false;

int monsterx = 480;
int arrowx = 50;


void ICGUI_Create()
{
	ICG_MWSize(1180, 800);
	ICG_MWTitle("SHOOT UP");

}

VOID* LoadArcherShoot(PVOID lpParam)
{

	while (thread2_continue) {

	
	Copy(Background, 1, 1, 574, 322, Forest);
	Copy(Archer, 38, 54, 54, 74, ArcherStanding);
	PasteNon0(ArcherStanding, 10, 250, Forest);
	DisplayImage(F3, Forest);

	ICBYTES cordinat{ {30, 30, 79, 56},{215,30,86,56},{405,35,86,51},{20,165,90,43},{210,165,95,43},
	{405,165,91,43}, {20,280,86,46}, {215,280,81,46}, {30, 30, 79, 56},{215,30,86,56},{405,35,86,51},{20,165,90,43},{210,165,95,43},
	{405,165,91,43}, {20,280,86,46}, {215,280,81,46}, {30, 30, 79, 56},{215,30,86,56},{405,35,86,51},{20,165,90,43},{210,165,95,43},
	{405,165,91,43}, {20,280,86,46}, {215,280,81,46}, {30, 30, 79, 56},{215,30,86,56},{405,35,86,51},{20,165,90,43},{210,165,95,43},
	{405,165,91,43}, {20,280,86,46}, {215,280,81,46} };
	/*for (int i = 1; i <= 13; i++)
	{
		Copy(Archer, cordinat.I(1, i), cordinat.I(2, i), cordinat.I(3, i), cordinat.I(4, i), ArcherShoot[i - 1]);
		PasteNon0(ArcherShoot[i - 1], 33 * i, 230, Forest);
	}*/


	for (int i = 0; i <= 32; i++) {
		Copy(Background, 1, 1, 574, 322, Forest);

		if (arrowx <= monsterx) {
			Copy(Monster, cordinat.I(1, i), cordinat.I(2, i), cordinat.I(3, i), cordinat.I(4, i), MonsterR);
			PasteNon0(MonsterR, monsterx, 280, Forest);
			monsterx = monsterx - 10;

		}


		PasteNon0(ArcherStanding, 10, 250, Forest);

		DisplayImage(F3, Forest);

		Sleep(110);

	}

	}
	return NULL;
}

VOID* Shoot(PVOID lpParam)
{
	DWORD dw;

	if (thread_continue) {
		Copy(Background, 1, 1, 574, 322, Forest);

		ICBYTES cordinat{ {38, 54, 54, 74},{96,54,67,74},{100,54,63,74},{161,54,70,74},{230,54,73,74},
		{300,54,71,74},{375,54,73,74},{446,54,93,74},{540,54,94,74},{636,54,90,74},{726,54,82,74},{808,54,74,74},{952,54,69,74} };
		/*for (int i = 1; i <= 13; i++)
		{
			Copy(Archer, cordinat.I(1, i), cordinat.I(2, i), cordinat.I(3, i), cordinat.I(4, i), ArcherShoot[i - 1]);
			PasteNon0(ArcherShoot[i - 1], 33 * i, 230, Forest);
		}*/

		for (int i = 0; i <= 13; i++) {
			Copy(Background, 1, 1, 574, 322, Forest);
			Copy(Archer, cordinat.I(1, i), cordinat.I(2, i), cordinat.I(3, i), cordinat.I(4, i), ArcherStanding);
			PasteNon0(ArcherStanding, 10, 250, Forest);
			//DisplayImage(F3, Forest);
			Sleep(120);

		}

		Sleep(0);
		for (int b = 0; b <= 40; b++) {
			if(arrowx < monsterx){
				Copy(Arrow, 5, 5, 40, 40, ArrowR);
				PasteNon0(ArrowR, arrowx , 270, Forest);
				arrowx =  arrowx + 10;
			}
			if (monsterx <= arrowx) {
				thread2_continue = false;
				thread_dead = true;
				//Copy(Background, 1, 1, 574, 322, Forest);
				CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)DeadAnimation, NULL, 0, &dw);
			}

			DisplayImage(F3, Forest);
			Sleep(30);

		}
		
	}
	return NULL;
}

VOID* DeadAnimation(PVOID lpParam) {
	while (thread_dead) {
		ICBYTES cordinat{ {25, 45, 150 ,49}, {220, 40, 135 ,54}, {410, 35, 125 ,59}, {600, 35, 103 ,59} };
		for (int i = 0; i <= 4; i++) {
			Copy(Background, 1, 1, 574, 322, Forest);
			Copy(Hurt, cordinat.I(1, i), cordinat.I(2, i), cordinat.I(3, i), cordinat.I(4, i), HurtR);
			PasteNon0(HurtR, monsterx, 280, Forest);
			Sleep(120);

		}


	}

}


void butonfonk()
{
	DWORD dw;
	if (!thread_continue){
		thread_continue = true;
		CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Shoot, NULL, 0, &dw);
		SetFocus(ICG_GetMainWindow());
	}
	else thread_continue = false;
}

void butonfonk2()
{
	DWORD dw;

	if (!thread2_continue)
	{
		thread2_continue = true;
		CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)LoadArcherShoot, NULL, 0, &dw);
		SetFocus(ICG_GetMainWindow());
	}
	else thread2_continue = false;
}


void ICGUI_main()
{
	F1 = ICG_FrameMedium(10, 56, 56, 72);
	F2 = ICG_FrameMedium(600, 200, 50, 20);
	F3 = ICG_FrameMedium(10, 200, 574, 322);
	F4 = ICG_FrameMedium(600,200, 50, 50);

	ICG_Button(5, 5, 90, 40, "Start the Animation", butonfonk2);
	ICG_Button(105, 5, 90, 40, "Shoot Arrow Animation", butonfonk);
	
	//MLE1 = ICG_MLEditSunken(500, 20, 200, 100, "awdaw", SCROLLBAR_V);
	//MLE2 = ICG_MLEditSunken(700, 120, 200, 100, "awdaw", SCROLLBAR_V);

	ReadImage("archer.bmp", Archer);
	DisplayImage(F1, Archer);

	ReadImage("arrow.bmp", Arrow);
	DisplayImage(F2, Arrow);

	ReadImage("forest.bmp", Background);
	Copy(Background, 1, 1, 574, 322, Forest);
	DisplayImage(F3, Forest);

	ReadImage("monsternew.bmp", Monster);
	DisplayImage(F4, Monster);

	ReadImage("HURT.bmp", Hurt);
	DisplayImage(F5, Hurt);

}