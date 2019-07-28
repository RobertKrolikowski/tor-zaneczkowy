#include <time.h>
#include <stdio.h>
#include <conio.h>
#include <Windows.h>
//typedef int bool;
#define true 1
#define false 0

bool Koniec = false;
unsigned char Poziom = 0;
unsigned int ScianaLewa,Sanki,ScianaPrawa;
unsigned int PrzejechaneWiersze = 0;
signed int ZmianaKursu;
void Poczatek()
{
	ScianaLewa = 25;
	ScianaPrawa = 55;
	Sanki = 40;
	srand((int)time(NULL));
}
void KasujEkran()
{
	unsigned char i;
	for (i = 0; i< 60; ++i)printf("\n");
}
void Czekaj()
{
	unsigned long i;
	if(Poziom == 0) i = 350;
	else if(Poziom == 1) i = 280;
	else if(Poziom == 2) i = 220;
	else if(Poziom == 3) i = 140;
	else i = 90;
	Sleep(i);
}
void RuchWLewo()
{
	if(--Sanki < ScianaLewa) Sanki = ScianaLewa;
}
void RuchWPrawo()
{
	if(++Sanki > ScianaPrawa) Sanki = ScianaPrawa;
}
void ObsluzKlawiature()
{
	while(_kbhit())
	{
		char ch= _getch();
		if(ch == 27) Koniec = true;
		else if (ch == ',') RuchWLewo();
		else if	(ch == '.') RuchWPrawo();
	}
}
bool OrzelReszka()
{
	return((rand()%20) >= 10);
}
void LosujWierszToru()
{
	if(ZmianaKursu == 0)
	{
		ZmianaKursu =rand()% 30;
		if(OrzelReszka())ZmianaKursu = -ZmianaKursu;
	}
	else if (ZmianaKursu <0)
	{
		++ZmianaKursu;
		if(ScianaLewa > 5)
		{
			--ScianaLewa;
			--ScianaPrawa;
		}
		else ZmianaKursu = 0;
	}
	else
	{
		--ZmianaKursu;
		if(ScianaPrawa < 75)
		{
			++ScianaLewa;
			++ScianaPrawa;
		}
		else ZmianaKursu = 0;
	}
	if (OrzelReszka()) ++ScianaLewa;
	else --ScianaLewa;
	if((ScianaPrawa - ScianaLewa) < 8) --ScianaLewa;
	if((ScianaPrawa - ScianaLewa) > 15) ++ScianaLewa;
}
void RysujWiersz(const bool RysujSanki)
{
	unsigned int i;
	bool Zbocze = true;
	for(i = 0; i < 79; ++i)
	{
		if((i == ScianaLewa) || (i == ScianaPrawa))
		{
			printf("|");
			Zbocze = !Zbocze;
		}
		else if (i == Sanki)
		{
			if(RysujSanki) printf("#");
			else printf(".");
		}
		else
		{
			if(Zbocze) printf(":");
			else printf(" ");
		}
	}
	for(i = 0; i < 79; ++i) printf("\b");
}
void NastepnyWiersz()
{
	printf("\n");
	++PrzejechaneWiersze;
	if((PrzejechaneWiersze == 100) 
		|| (PrzejechaneWiersze == 200)
		|| (PrzejechaneWiersze == 300)
		|| (PrzejechaneWiersze == 400))
		++Poziom;
}
bool CzyKatastrofa()
{
	return((Sanki <= ScianaLewa) || (Sanki >= ScianaPrawa));
}
void Katastrofa()
{
	unsigned char i;
	for(i = 0; i < 10; ++i)
	{
		printf("\n");
		Sleep(100);
	}
	printf("                      K A T A S T R O F A ! ! !");
	for(i = 0; i < 10; ++i)
	{
		printf("\n");
		Sleep(100);
	}
}
int main()
{
	KasujEkran();
	Poczatek();
	while(!Koniec)
	{
		LosujWierszToru();
		ObsluzKlawiature();
		RysujWiersz(true);
		if(CzyKatastrofa())
		{
			Katastrofa();
			break;
		}
		Czekaj();
		ObsluzKlawiature();
		RysujWiersz(true);
		if(CzyKatastrofa())
		{
			Katastrofa();
			break;
		}
		Czekaj();
		RysujWiersz(false);
		NastepnyWiersz();
	}
	return 0;
}