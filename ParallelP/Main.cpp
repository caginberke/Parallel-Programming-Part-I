#include<windows.h>
#include"icb_gui.h"

int MLE1, MLE2;
	

int F1, F2, F3, F4, F5, F6;



ICBYTES ArcherStanding, ArrowR, MonsterR;
ICBYTES Forest, Archer, Arrow, Monster, Background, Temp, Hurt , HurtR , Dead, DeadR;

bool thread_continue = false;
bool thread2_continue = false;

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

	if (thread_continue) {

		//Shoot arrow
		ICBYTES cordinat{ {38, 54, 54, 74},{96,54,67,74},{100,54,63,74},{161,54,70,74},{230,54,73,74},
		{300,54,71,74},{375,54,73,74},{446,54,93,74},{540,54,94,74},{636,54,90,74},{726,54,82,74},{808,54,74,74},{952,54,69,74} };


		for (int i = 0; i <= 13; i++) {
			Copy(Background, 1, 1, 574, 322, Forest);
			Copy(Archer, cordinat.I(1, i), cordinat.I(2, i), cordinat.I(3, i), cordinat.I(4, i), ArcherStanding);
			PasteNon0(ArcherStanding, 10, 250, Forest);
			//DisplayImage(F3, Forest);
			Sleep(120);

		}

		//monster die
		for (int b = 0; b <= 40; b++) {
			if(arrowx < monsterx){
				Copy(Arrow, 5, 5, 40, 40, ArrowR);
				PasteNon0(ArrowR, arrowx , 270, Forest);
				arrowx =  arrowx + 10;
			}
			if (monsterx <= arrowx) {
				thread2_continue = false;
				//thread_dead = true;
				ICBYTES cor{{25, 45, 150 ,49}, {220, 40, 135 ,54}, {410, 35, 125 ,59}, {600, 35, 103 ,59} };
				for (int c = 0; c < 4; c++) {
					Copy(Archer, 38, 54, 54, 74, ArcherStanding);
					Copy(Background, 1, 1, 574, 322, Forest);
					PasteNon0(ArcherStanding, 10, 250, Forest);
					Copy(Hurt, cor.I(1, c), cor.I(2, c), cor.I(3, c), cor.I(4, c), HurtR);
					PasteNon0(HurtR, monsterx, 280, Forest);
					DisplayImage(F3, Forest);
					Sleep(350);
					
				}

				ICBYTES cord{ {10, 15, 79 ,46}, {200, 25, 86 ,36}, {390, 30, 91 ,31} };
				for (int e = 0; e < 3; e++) {
					Copy(Archer, 38, 54, 54, 74, ArcherStanding);
					Copy(Background, 1, 1, 574, 322, Forest);
					PasteNon0(ArcherStanding, 10, 250, Forest);
					Copy(Dead, cord.I(1, e), cord.I(2, e), cord.I(3, e), cord.I(4, e), DeadR);
					PasteNon0(DeadR, monsterx, 295, Forest);
					DisplayImage(F3, Forest);
					Sleep(300);

				}
				for (int k = 0; k < 50; k++) {
					Copy(Archer, 38, 54, 54, 74, ArcherStanding);
					Copy(Background, 1, 1, 574, 322, Forest);
					PasteNon0(ArcherStanding, 10, 250, Forest);
					PasteNon0(DeadR, monsterx, 295+k, Forest);
					DisplayImage(F3, Forest);
					Sleep(300);

				}


				b = 41;
				//Copy(Background, 1, 1, 574, 322, Forest);

			}

			DisplayImage(F3, Forest);
			Sleep(30);

		}
		
	}
	return NULL;
}

/*

ICBYTES cor{{10, 15, 79 ,46}, {200, 25, 86 ,36}, {390, 30, 91 ,31} };
				for (int e = 0; e < 3; e++) {
					Copy(Archer, 38, 54, 54, 74, ArcherStanding);
					Copy(Background, 1, 1, 574, 322, Forest);
					PasteNon0(ArcherStanding, 10, 250, Forest);
					Copy(Dead, cor.I(1, c), cor.I(2, c), cor.I(3, c), cor.I(4, c), DeadR);
					PasteNon0(DeadR, monsterx, 280, Forest);
					DisplayImage(F3, Forest);
					Sleep(150);

				}

*/

/*VOID* DeadAnimation(PVOID lpParam) {
	
	while (thread_dead) {
		Copy(Background, 1, 1, 574, 322, Forest);
		Copy(Hurt, 25, 45, 150, 49, HurtR);
		PasteNon0(HurtR, monsterx, 280, Forest);
		DisplayImage(F3, Forest);

		


	}
	return NULL;
}*/


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
	
	//MLE1 = ICG_MLEditSunken(500, 20, 200, 100, "awdaw", SCROLLBAR_V);
	//MLE2 = ICG_MLEditSunken(700, 120, 200, 100, "awdaw", SCROLLBAR_V);

	ReadImage("archer.bmp", Archer);

	ReadImage("arrow.bmp", Arrow);

	ReadImage("forest.bmp", Background);
	Copy(Background, 1, 1, 574, 322, Forest);
	DisplayImage(F3, Forest);

	ReadImage("monsternew.bmp", Monster);

	ReadImage("hurt.bmp", Hurt);

	ReadImage("dead.bmp", Dead);

}