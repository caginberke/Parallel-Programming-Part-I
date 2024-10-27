#include<windows.h>
#include"icb_gui.h"

int MLE1, MLE2;
	

int F1, F2, F3, F4, F5, F6;



ICBYTES ArcherNow, ArrowR, MonsterR;
ICBYTES Forest, Archer, Arrow, Monster, Background, Temp, Hurt , HurtR , Dead, DeadR;
ICBYTES Standing, ShieldingUp, Shield, Dashing, Dying;
ICBYTES StandingR, ShieldingUpR, ShieldR, DashingR, DyingR;


bool thread_continue = false;
bool thread2_continue = false;

bool isShooting = false;
bool thread_dead = false;

int monsterx = 480;
int arrowx = 50;


void ICGUI_Create()
{
	ICG_MWSize(660, 450);
	ICG_MWTitle("SHOOT UP");

}

VOID* Animation(PVOID lpParam)
{

	while (thread2_continue) {


		Copy(Background, 1, 1, 574, 322, Forest);
		Copy(Archer, 38, 54, 54, 74, ArcherNow);
		PasteNon0(ArcherNow, 10, 250, Forest);
		DisplayImage(F3, Forest);


		ICBYTES standing{ {28, 3, 53, 61}, {129, 2, 52, 62}, {229, 1, 52, 63}, {329, 2, 52, 62} };

		for (int s = 1; s < 5; s++) {
			Copy(Background, 1, 1, 574, 322, Forest);
			Copy(Standing, standing.I(1, s), standing.I(2, s), standing.I(3, s), standing.I(4, s), StandingR);
			PasteNon0(StandingR, 480, 265, Forest);

			PasteNon0(ArcherNow, 10, 250, Forest);

		DisplayImage(F3, Forest);
	}


	if (arrowx > 400) {
		ICBYTES shieldingup{ {28, 7, 56, 57}, {128, 7, 61, 57}, {229, 7, 57, 57}, {326, 7, 61, 57}, {425, 5, 66, 59}, {528, 2, 63, 62}, {632, 2, 59, 32} };
		for (int d = 1; d < 8;  d++) {
			Copy(Background, 1, 1, 574, 322, Forest);
			Copy(ShieldingUp, shieldingup.I(1, d), shieldingup.I(2, d), shieldingup.I(3, d), shieldingup.I(4, d), ShieldingUpR);
			DisplayImage(F3, Forest);
		}
		if (arrowx > 350) {
			ICBYTES shieldingup{ {28, 7, 56, 57}, {128, 7, 61, 57}, {229, 7, 57, 57}, {326, 7, 61, 57}, {425, 5, 66, 59}, {528, 2, 63, 62}, {632, 2, 59, 32} };
			for (int d = 1; d < 8; d++) {
				Copy(Background, 1, 1, 574, 322, Forest);
				Copy(ShieldingUp, shieldingup.I(1, d), shieldingup.I(2, d), shieldingup.I(3, d), shieldingup.I(4, d), ShieldingUpR);

				PasteNon0(ShieldingUp, 480, 265, Forest);
				PasteNon0(ArcherNow, 10, 250, Forest);

				DisplayImage(F3, Forest);
				Sleep(110);
			}
		}

		return NULL;
	}
}

VOID* Shoot(PVOID lpParam)
{

	if (thread_continue) {

		//Shoot arrow
		ICBYTES cordinat{ {38, 54, 54, 74},{96,54,67,74},{100,54,63,74},{161,54,70,74},{230,54,73,74},
		{300,54,71,74},{375,54,73,74},{446,54,93,74},{540,54,94,74},{636,54,90,74},{726,54,82,74},{808,54,74,74},{952,54,69,74} };


		isShooting = true;
		for (int i = 1; i <= 13; i++) {
			Copy(Background, 1, 1, 574, 322, Forest);
			Copy(Archer, cordinat.I(1, i), cordinat.I(2, i), cordinat.I(3, i), cordinat.I(4, i), ArcherNow);
			//DisplayImage(F3, Forest);
			Sleep(120);

		}
		isShooting = false;

		//ICBYTES shield{ {28, 7, 62, 57}, {127, 7, 62, 57}, {228, 7, 63, 57}, {329, 7, 61, 57}};
		//ICBYTES dashing{{30, 7, 62, 57}, {134, 5, 62, 59}, {230, 10, 52, 54}, {332, 9, 53, 55}};
		//ICBYTES dying{ {25, 40, 70, 24}, {125, 40, 70, 24}, {225, 25, 70, 39}, {340, 15, 60, 49}, {435, 5, 65, 59}, {530, 4, 46, 60}};

		DisplayImage(F3, Forest);
		Sleep(30);
		
	}
	return NULL;
}




void butonfonk()
{
	DWORD dw;
	if (!thread_continue){
		thread_continue = true;
		CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Shoot, NULL, 0, &dw);
		thread2_continue = true;
		CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Animation, NULL, 0, &dw);
		//CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)DeadAnimation, NULL, 0, &dw);

		SetFocus(ICG_GetMainWindow());
	}
	else thread_continue = false;
}



void ICGUI_main()
{
	F3 = ICG_FrameMedium(20, 50, 574, 322);

	ICG_Button(265, 5, 90, 40, "Start the Animation", butonfonk);
	
	//Background
	ReadImage("forest.bmp", Background);
	Copy(Background, 1, 1, 574, 322, Forest);
	DisplayImage(F3, Forest);

	//Archer 
	ReadImage("archer.bmp", Archer);
	ReadImage("arrow.bmp", Arrow);

	ReadImage("monsternew.bmp", Monster);
	ReadImage("hurt.bmp", Hurt);
	ReadImage("dead.bmp", Dead);

	ReadImage("standing.bmp", Standing);
	ReadImage("shieldingup.bmp", ShieldingUp);
	ReadImage("shield.bmp", Shield);
	ReadImage("dashing.bmp", Dashing);
	ReadImage("dying.bmp", Dying);


}