#include<windows.h>
#include"icb_gui.h"


int F1, F2, F3;

ICBYTES ArcherShoot[13]; //For archer sprite sheet

ICBYTES ArcherStanding;
ICBYTES Forest, Archer, Arrow;

int currentFrame = 0; // Animasyon çerçevesi

void ICGUI_Create()
{
	ICG_MWSize(1080, 700);
	ICG_MWTitle("SHOOT UP");
}

void LoadArcherShoot()
{
	Copy(Archer, 38, 54, 54, 74, ArcherStanding);
	PasteNon0(ArcherStanding, 10, 250, Forest);
	DisplayImage(F3, Forest);






}

void Shoot(void*)
{
	ICBYTES cordinat{ {38, 54, 54, 74},{96,54,67,74},{100,54,63,74},{161,54,70,74},{230,54,73,74},
	{300,54,71,74},{375,54,73,74},{446,54,93,74},{540,54,94,74},{636,54,90,74},{726,54,82,74},{808,54,74,74},{952,54,69,74} };
	/*for (int i = 1; i <= 13; i++)
	{
		Copy(Archer, cordinat.I(1, i), cordinat.I(2, i), cordinat.I(3, i), cordinat.I(4, i), ArcherShoot[i - 1]);
		PasteNon0(ArcherShoot[i - 1], 33 * i, 230, Forest);
	}*/

	for (int i = 0; i <= 13; i++) {
		Copy(Archer, cordinat.I(1, i), cordinat.I(2, i), cordinat.I(3, i), cordinat.I(4, i), ArcherStanding);
		Paste(ArcherStanding, 10, 250, Forest);
		DisplayImage(F3, Forest);
		Sleep(120);
	}
}


void ICGUI_main()
{
	F1 = ICG_FrameMedium(10, 56, 56, 72);
	F2 = ICG_FrameMedium(600, 200, 50, 20);
	F3 = ICG_FrameMedium(10, 200, 50, 20);

	ICG_Button(5, 5, 90, 40, "Load Archer", LoadArcherShoot);
	ICG_Button(105, 5, 90, 40, "Shoot Arrow", Shoot, NULL);

	ReadImage("archeryedek.bmp", Archer);
	DisplayImage(F1, Archer);

	ReadImage("arrow.bmp", Arrow);
	DisplayImage(F2, Arrow);

	ReadImage("forest.bmp", Forest);
	DisplayImage(F3, Forest);
}