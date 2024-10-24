#include<windows.h>
#include"icb_gui.h"


int F1, F2, F3, F4;

ICBYTES ArcherShoot[13]; //For archer sprite sheet
ICBYTES MonsterWalk[32]; //For archer sprite sheet

ICBYTES ArcherStanding, ArrowR, MonsterR;
ICBYTES Forest, Archer, Arrow, Monster, Background;

bool thread_continue = false;


void ICGUI_Create()
{
	ICG_MWSize(1080, 700);
	ICG_MWTitle("SHOOT UP");

}

void LoadArcherShoot()
{


	while (true) {

		

	
	Copy(Background, 1, 1, 574, 322, Forest);
	Copy(Archer, 38, 54, 54, 74, ArcherStanding);
	PasteNon0(ArcherStanding, 10, 250, Forest);
	DisplayImage(F3, Forest);

	ICBYTES cordinat{ {40, 93, 53, 35},{162,93,60,35},{286,93,66,35},{413,93,67,35},{542,93,70,35},
	{670,93,72,35}, {800,93,70,35}, {938,93,56,35}, {40, 93, 53, 35},{162,93,60,35},{286,93,66,35},{413,93,67,35},{542,93,70,35},
	{670,93,72,35}, {800,93,70,35}, {938,93,56,35}, {40, 93, 53, 35},{162,93,60,35},{286,93,66,35},{413,93,67,35},{542,93,70,35},
	{670,93,72,35}, {800,93,70,35}, {938,93,56,35}, {40, 93, 53, 35},{162,93,60,35},{286,93,66,35},{413,93,67,35},{542,93,70,35},
	{670,93,72,35}, {800,93,70,35}, {938,93,56,35} };
	/*for (int i = 1; i <= 13; i++)
	{
		Copy(Archer, cordinat.I(1, i), cordinat.I(2, i), cordinat.I(3, i), cordinat.I(4, i), ArcherShoot[i - 1]);
		PasteNon0(ArcherShoot[i - 1], 33 * i, 230, Forest);
	}*/

	for (int i = 0; i <= 32; i++) {
		Copy(Background, 1, 1, 574, 322, Forest);
		Copy(Monster, cordinat.I(1, i), cordinat.I(2, i), cordinat.I(3, i), cordinat.I(4, i), MonsterR);
		PasteNon0(MonsterR, 480-i*13.5 , 290, Forest);
		PasteNon0(ArcherStanding, 10, 250, Forest);

		DisplayImage(F3, Forest);
		Sleep(160);

	}

	}

}

void Shoot(void*)
{
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
		DisplayImage(F3, Forest);
		Sleep(120);

	}

	Sleep(0);
	for (int b = 0; b <= 15; b++) {
		Copy(Arrow, 5, 5, 40, 40 , ArrowR);
		PasteNon0(ArrowR,50+b, 270, Forest);
		DisplayImage(F3, Forest);
	}
	



void ICGUI_main()
{
	F1 = ICG_FrameMedium(10, 56, 56, 72);
	F2 = ICG_FrameMedium(600, 200, 50, 20);
	F3 = ICG_FrameMedium(10, 200, 574, 322);

	ICG_Button(5, 5, 90, 40, "Load Archer", LoadArcherShoot);
	ICG_Button(105, 5, 90, 40, "Shoot Arrow", Shoot, NULL);
	

	ReadImage("archer.bmp", Archer);
	DisplayImage(F1, Archer);

	ReadImage("arrow.bmp", Arrow);
	DisplayImage(F2, Arrow);

	ReadImage("forest.bmp", Background);
	Copy(Background, 1, 1, 574, 322, Forest);
	DisplayImage(F3, Forest);

	ReadImage("monster.bmp", Monster);
	DisplayImage(F4, Monster);
}