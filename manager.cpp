#include "manager.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>

#include "window_surface.h"
#include "dialog.h"
#include "user.h"

// ��������� �� �������� ������������.
#define CUSER USERS.GetUser(current_user_)
// ���� ��� ����������.
static const char *storage = "monopoly.dat";

Manager::Manager()
	: current_user_(-1), dice_1_(0), dice_2_(0), go_to_jail_(false), bankrupt_(false)
{
	srand((unsigned int)time(NULL));

	chance_.SetCard(Lottery::CollectingOnStreetRepair);
	chance_.SetCard(Lottery::GoToJail);
	chance_.SetCard(Lottery::Penalty20);
	chance_.SetCard(Lottery::GoToStart);
	chance_.SetCard(Lottery::Insurance);
	chance_.SetCard(Lottery::Plus150);
	chance_.SetCard(Lottery::Plus50);
	chance_.SetCard(Lottery::GoToStartPlus200);
	chance_.SetCard(Lottery::GoToStart);
	chance_.SetCard(Lottery::Penalty15);
	chance_.SetCard(Lottery::GoToStartPlus200);
	chance_.SetCard(Lottery::ToWinInALottery100);
	chance_.SetCard(Lottery::CollectingOnStreetRepair2);
	chance_.SetCard(Lottery::Minus50);
	chance_.SetCard(Lottery::Minus100);
	chance_.SetCard(Lottery::Plus250);
	chance_.Reshuffle();

	public_treasury_.SetCard(Lottery::Plus25);
	public_treasury_.SetCard(Lottery::InsurancePayment50);
	public_treasury_.SetCard(Lottery::Plus25);
	public_treasury_.SetCard(Lottery::GoToStart);
	public_treasury_.SetCard(Lottery::DoctorServices50);
	public_treasury_.SetCard(Lottery::Insurance);
	public_treasury_.SetCard(Lottery::DoctorServices100);
	public_treasury_.SetCard(Lottery::Plus25);
	public_treasury_.SetCard(Lottery::Penalty10);
	public_treasury_.SetCard(Lottery::Plus50);
	public_treasury_.SetCard(Lottery::Gift10);
	public_treasury_.SetCard(Lottery::BankMistake200);
	public_treasury_.SetCard(Lottery::Inheritance100);
	public_treasury_.SetCard(Lottery::ToWinInALottery10);
	public_treasury_.SetCard(Lottery::CollectingRent100);
	public_treasury_.SetCard(Lottery::GoToJail);
	public_treasury_.Reshuffle();
}

Manager::~Manager()
{
}

bool Manager::Load()
{
	bool b = false;
	FILE *fd = fopen(storage, "r");
	if (fd != 0) {
		b = DoLoad(fd);
		fclose(fd);
	}
	if (b) {
		WINSURF.DrawGameMap();
		for(int i = 0; i < USERS.GetUsersCount(); i++)
		{
			USERS.GetUser(i)->ShowInfo();
			WINSURF.DrawSmilie(i, 0, USERS.GetUser(i)->GetPosition());
		}
		current_user_--;
	}
	return b;
}

bool Manager::DoLoad(FILE *file)
{
	int a;
	if ((a = fread(&current_user_, sizeof(current_user_), 1, file)) != 1)
		return false;
	if (!map_.Load(file))
		return false;
	if (!USERS.Load(file))
		return false;
	return true;
}

bool Manager::Save()
{
	bool b = false;
	FILE *fd = fopen(storage, "w");
	if (fd != 0) {
		b = DoSave(fd);
		fclose(fd);
	}
	return b;
}

bool Manager::DoSave(FILE *file)
{
	if (fwrite(&current_user_, sizeof(current_user_), 1, file) != 1)
		return false;
	if (!map_.Save(file))
		return false;
	if (!USERS.Save(file))
		return false;
	return true;
}

void Manager::NewGame()
{
	Dialog d("������ ������ ����� ����?");
	d.SetRectangle(17, 30, 35, 10);
	FILE *fd = fopen(storage, "r");
	if(fd) {
		fclose(fd);
		d.SetButton("��", "���������");
	}
	else
		d.SetButton("��");
	int key = d.Show(0);
	d.Hide();
	if (key == 1) {
		while (!CreateUsers());
	}
	else {
		if (!Load()) {
			Dialog err("������ ������ �����!");
			err.SetRectangle(17, 30, 35, 10);
			err.SetButton("����������");
			err.Show(0);
			exit(0);
		}
	}
}

bool Manager::CreateUsers() const
{
	Dialog d1("������� ������");
	d1.SetRectangle(17, 30, 35, 10);
	d1.SetButton("�������", "���������");

	Dialog d2("������� ��� ������?");
	d2.SetRectangle(16, 30, 37, 10);
	d2.SetButton("�������", "���������", "���");

	for(int i = 0; i < 4; i++)
	{
		int key;
		if(i < 2) {
			key = d1.Show(0);
			d1.Hide();
		}
		else {
			key = d2.Show(0);
			d2.Hide();
			if(key == 3)
				break;
		}
		WINSURF.DrawRectangle(15, 35, 54, 5, LightGray);
		WINSURF.DrawString("������� ��� ������: ", 19, 37, LightGray);
		char name[256];
		std::cin>>name;
		name[12] = '\0';
		OemToCharA(name, name);
		WINSURF.ClearRectangle(15, 35, 54, 5);
		USERS.AddUser(name, key == 1 ? false : true);
	}

	bool b = true;
	for(int i = 0; i < USERS.GetUsersCount(); i++)
	{
		b = b && USERS.GetUser(i)->IsComputer();
	}
	if (b) {
		Dialog d3("���� �� ���� ����� ������ ���� \"�������\".\n��������� ���� ������� �������.");
		d3.SetRectangle(9, 30, 51, 10);
		d3.SetButton("����������");
		d3.Show(0);
		d3.Hide();
		USERS.DeleteAllUsers();
		return false;
	}
	WINSURF.DrawGameMap();
	for(int i = 0; i < USERS.GetUsersCount(); i++)
	{
		Color color;
		switch (i)
		{
		case 0: color = LightRed; break;
		case 1: color = LightGreen; break;
		case 2: color = Cyan; break;
		case 3: color = Yellow;
		}
		USERS.GetUser(i)->SetColor(color);
		USERS.GetUser(i)->ShowInfo();
		WINSURF.DrawSmilie(i, 0, 0);
	}
	return true;
}

void Manager::Run()
{
	while(1)
	{
		if(current_user_ == -1 || CUSER->GetDoubles() == 0)
			SetNextUser();
		ThrowDices();
		Moving();
		if(!bankrupt_ && CUSER->GetPasses() == 0) {
			PositionAnalysis();
		}
		bankrupt_ = false;
	}
}

void Manager::SetNextUser()
{
	if(current_user_ >= 0)
		CUSER->SetActive(false);
	current_user_++;
	if(current_user_ > USERS.GetUsersCount() - 1)
		current_user_ = 0;
	CUSER->SetActive(true);
}

void Manager::ThrowDices()
{
	if(!CUSER->IsComputer()) {
		char buf[256];
		sprintf(buf, "�����: %s", CUSER->GetName());
		Dialog d(buf);
		d.SetRectangle(17, 30, 35, 10);
		if(CUSER->GetDoubles() == 0)
			d.SetButton("������", "����������");
		else
			d.SetButton("������");
		int key = d.Show(map_);
		while (key != 1) {
			Save();
			key = d.Show(map_);
		}
	}

	dice_1_ = Rand();
	dice_2_ = Rand();

	if(dice_1_ == dice_2_)
		CUSER->IncDoubles();
	else
		CUSER->ResetDoubles();
}

void Manager::Moving()
{
	if(CUSER->GetPasses() == 0) {
		if(CUSER->GetDoubles() != 3) {
			if(!CUSER->IsComputer()) {
				char buf[256];
				sprintf(buf, "��� ��������� %i + %i", dice_1_, dice_2_);
				Dialog d2(buf);
				d2.SetRectangle(17, 30, 35, 10);
				d2.SetButton("����������");
				d2.Show(map_);
			}
			MoveUser();
		}
		else {
			char buf[256];
			if(!CUSER->IsComputer()) {
				sprintf(buf, "��� ��������� %i + %i\n"
					           "������������� � ������ �� ��� ����� ������\n"
										 "��� ��������� ����� 500$",
										 dice_1_, dice_2_);
			}
			else {
				buf[0] = '\0';
			}
			GoToJail(buf);
		}
	}
	else {
		if(CUSER->GetDoubles() > 0) {
			CUSER->ResetDoubles();
			CUSER->ResetPasses();
			if(!CUSER->IsComputer()) {
				char buf[256];
				sprintf(buf, "��� ��������� %i + %i\n"
					           "�� ��������� ��������� ������������",
										 dice_1_, dice_2_);
				Dialog d(buf);
				d.SetRectangle(14, 30, 41, 10);
				d.SetButton("����������");
				d.Show(map_);
			}
			MoveUser();
		}
		else if(CUSER->GetPasses() > 1) {
			CUSER->DecPasses();
			if(!CUSER->IsComputer()) {
				char buf[256];
				sprintf(buf, "��� ��������� %i + %i\n"
					           "�� ������ � ������ � ����������� ���� ���",
										 dice_1_, dice_2_);
				Dialog d(buf);
				d.SetRectangle(11, 30, 47, 10);
				d.SetButton("����������");
				d.Show(map_);
			}
		}
		else {
			CUSER->DecPasses();
			if(!CUSER->IsComputer()) {
				char buf[256];
				sprintf(buf, "��� ��������� %i + %i\n"
					           "���������� ���� ������ ����������\n"
										 "��������� ����� 50$",
										 dice_1_, dice_2_);
				Dialog d(buf);
				d.SetRectangle(14, 30, 40, 10);
				d.SetButton("����������");
				d.Show(map_);
			}
			ObligatoryPayment(50);
			if (!bankrupt_)
				MoveUser();
		}
	}
}

void Manager::GoToJail(char *msg)
{
	int key;
	go_to_jail_ = true;
	CUSER->ResetDoubles();
	MoveUser();

	if(!CUSER->IsComputer()) {
		Dialog d1(msg);
		d1.SetRectangle(10, 29, 49, 11);
		if(CUSER->HowManyInsurances() > 0)
			d1.SetButton("����������", "���������", "���������");
		else
			d1.SetButton("����������", "���������");
		key = d1.Show(map_);
	}
	else {
		key = GoToJail_Computer();
	}
	switch (key)
	{
	case 2:
		if(CUSER->Payment(500))
			break;
		else {
			if(!CUSER->IsComputer()) {
				Dialog d("� ��� ������������ ����� �� �����");
				d.SetRectangle(15, 30, 39, 10);
				d.SetButton("����������");
				d.Show(map_);
			}
		}
	case 1:
		CUSER->SetPasses();
		break;
	case 3:
		CUSER->GiveInsurance();
	}
}

int Manager::GoToJail_Computer() const
{
	if(CUSER->HowManyInsurances() > 0)
		return 3;
	else if(CUSER->GetMonopolies() > 0)
		return 1;
	else
		return 2;
}

void Manager::MoveUser()
{
	if(go_to_jail_) {
		WINSURF.DrawSmilie(current_user_, CUSER->SetPosition(10), 10);
		go_to_jail_ = false;
	}
	else {
		int pos = CUSER->GetPosition();
		for (int i = 0; i < dice_1_ + dice_2_; i++)
		{
			pos += 1;
			if(pos > 39) {
				CUSER->ReceiveMoney(200);
				pos = 0;
			}
			WINSURF.DrawSmilie(current_user_, CUSER->SetPosition(pos), pos);
			Sleep(300);
		}
	}
}

int Manager::Rand() const
{
	return rand() % 6 + 1;
}

void Manager::PositionAnalysis()
{
	int pos = CUSER->GetPosition();
	switch(map_.Type(pos))
	{
	case Space::Site:
		SpaceSiteAnalysis(pos);
		break;
	case Space::Service:
	case Space::Communication:
		SpaceServiceAnalysis(pos);
		break;
	case Space::Taxation:
		SpaceTaxationAnalysis(pos);
		break;
	case Space::Chance:
		CardAction(chance_.GetCard());
		break;
	case Space::PublicTreasury:
		CardAction(public_treasury_.GetCard());
		break;
	case Space::GoToJail:
		GoToJail("������������� � ������\n��� ��������� ����� 500$");
		break;
	case Space::Jail:
		SpaceJailAnalysis();
	}
}

void Manager::SpaceJailAnalysis()
{
	int key = 1;
	if(!CUSER->IsComputer()) {
			Dialog d("������ ������ �������� �� 250$?");
			d.SetRectangle(16, 30, 36, 10);
			d.SetButton("��", "���");
			key = d.Show(map_);
		}
	if(key == 1) {
		if(CUSER->Payment(250))
			CUSER->ReceiveInsurance();
	}
}

void Manager::CardAction(Lottery::Card c)
{
	switch (c)
	{
	case Lottery::Plus25:
		if(!CUSER->IsComputer()) {
			Dialog d("�������� ������� �����\n�������� 25$");
			d.SetRectangle(17, 30, 35, 10);
			d.SetButton("����������");
			d.Show(map_);
		}
		CUSER->ReceiveMoney(25);
		break;

	case Lottery::Plus50:
		if (!CUSER->IsComputer()) {
			Dialog d("�������� ������� ���������\n�������� 50$");
			d.SetRectangle(17, 30, 35, 10);
			d.SetButton("����������");
			d.Show(map_);
		}
		CUSER->ReceiveMoney(50);
		break;

	case Lottery::Plus150:
		if (!CUSER->IsComputer()) {
			Dialog d("���������� ������ � ���� ������\n�������� 150$");
			d.SetRectangle(16, 30, 37, 10);
			d.SetButton("����������");
			d.Show(map_);
		}
		CUSER->ReceiveMoney(150);
		break;

	case Lottery::Plus250:
		if (!CUSER->IsComputer()) {
			Dialog d("�� �������� ��������� �� ��������\n�������� 250$");
			d.SetRectangle(14, 30, 38, 10);
			d.SetButton("����������");
			d.Show(map_);
		}
		CUSER->ReceiveMoney(250);
		break;

	case Lottery::Gift10:
		if (!CUSER->IsComputer()) {
			Dialog d("� ���� ��������\n�������� 10$ �� ������� ������");
			d.SetRectangle(17, 30, 35, 10);
			d.SetButton("����������");
			d.Show(map_);
		}
		for (int i = 0; i < USERS.GetUsersCount(); i++)
		{
			if (i != current_user_)
				CUSER->ReceiveMoney(USERS.GetUser(i)->Payment(10));
		}
		break;

	case Lottery::ToWinInALottery10:
		if (!CUSER->IsComputer()) {
			Dialog d("�� �������� � �������\n�������� 10$");
			d.SetRectangle(17, 30, 35, 10);
			d.SetButton("����������");
			d.Show(map_);
		}
		CUSER->ReceiveMoney(10);
		break;

	case Lottery::Inheritance100:
		if (!CUSER->IsComputer()) {
			Dialog d("�� �������� ����������\n�������� 100$");
			d.SetRectangle(17, 30, 35, 10);
			d.SetButton("����������");
			d.Show(map_);
		}
		CUSER->ReceiveMoney(100);
		break;

	case Lottery::CollectingRent100:
		if (!CUSER->IsComputer()) {
			Dialog d("���� �����\n�������� 100$");
			d.SetRectangle(17, 30, 35, 10);
			d.SetButton("����������");
			d.Show(map_);
		}
		CUSER->ReceiveMoney(100);
		break;
		
	case Lottery::ToWinInALottery100:
		if (!CUSER->IsComputer()) {
			Dialog d("�� �������� � �������\n�������� 100$");
			d.SetRectangle(17, 30, 35, 10);
			d.SetButton("����������");
			d.Show(map_);
		}
		CUSER->ReceiveMoney(100);
		break;
	
	case Lottery::BankMistake200:
		if (!CUSER->IsComputer()) {
			Dialog d("���������� ������ � ���� ������\n�������� 200$");
			d.SetRectangle(16, 30, 37, 10);
			d.SetButton("����������");
			d.Show(map_);
		}
		CUSER->ReceiveMoney(200);
		break;
	
	case Lottery::Minus50:
		if (!CUSER->IsComputer()) {
			Dialog d("������ ������ ���������\n� ��� 50$");
			d.SetRectangle(17, 30, 35, 10);
			d.SetButton("����������");
			d.Show(map_);
		}
		ObligatoryPayment(50);
		break;

	case Lottery::Minus100:
		if (!CUSER->IsComputer()) {
			Dialog d("������ ������ ���������\n� ��� 100$");
			d.SetRectangle(17, 30, 35, 10);
			d.SetButton("����������");
			d.Show(map_);
		}
		ObligatoryPayment(100);
		break;

	case Lottery::Penalty10:
		if (!CUSER->IsComputer()) {
			Dialog d("��������� �����\n� ��� 10$");
			d.SetRectangle(17, 30, 35, 10);
			d.SetButton("����������");
			d.Show(map_);
		}
		ObligatoryPayment(10);
		break;

	case Lottery::Penalty15:
		if (!CUSER->IsComputer()) {
			Dialog d("��������� �����\n� ��� 15$");
			d.SetRectangle(17, 30, 35, 10);
			d.SetButton("����������");
			d.Show(map_);
		}
		ObligatoryPayment(15);
		break;

	case Lottery::Penalty20:
		if (!CUSER->IsComputer()) {
			Dialog d("��������� �����\n� ��� 20$");
			d.SetRectangle(17, 30, 35, 10);
			d.SetButton("����������");
			d.Show(map_);
		}
		ObligatoryPayment(20);
		break;

	case Lottery::InsurancePayment50:
		if (!CUSER->IsComputer()) {
			Dialog d("�������� ���������\n� ��� 50$");
			d.SetRectangle(17, 30, 35, 10);
			d.SetButton("����������");
			d.Show(map_);
		}
		ObligatoryPayment(50);
		break;

	case Lottery::DoctorServices50:
		if (!CUSER->IsComputer()) {
			Dialog d("�������� ����� �������\n� ��� 50$");
			d.SetRectangle(17, 30, 35, 10);
			d.SetButton("����������");
			d.Show(map_);
		}
		ObligatoryPayment(50);
		break;

	case Lottery::DoctorServices100:
		if (!CUSER->IsComputer()) {
			Dialog d("�������� ����� �������\n� ��� 100$");
			d.SetRectangle(17, 30, 35, 10);
			d.SetButton("����������");
			d.Show(map_);
		}
		ObligatoryPayment(100);
		break;

	case Lottery::CollectingOnStreetRepair:
		if (!CUSER->IsComputer()) {
			Dialog d("���� �� ������ ����� - 40$ �� ������\n��� � 115$ �� ������ �����");
			d.SetRectangle(12, 30, 45, 10);
			d.SetButton("����������");
			d.Show(map_);
		}
		{
			int houses = 0, hotels = 0;
			map_.HowManyBuildingsAtUser(current_user_, houses, hotels);
				ObligatoryPayment(houses * 40 + hotels * 115);
		}
		break;

	case Lottery::CollectingOnStreetRepair2:
		if (!CUSER->IsComputer()) {
			Dialog d("���� �� ������ ����� - 25$ �� ������\n��� � 100$ �� ������ �����");
			d.SetRectangle(12, 30, 45, 10);
			d.SetButton("����������");
			d.Show(map_);
		}
		{
			int houses = 0, hotels = 0;
			map_.HowManyBuildingsAtUser(current_user_, houses, hotels);
			ObligatoryPayment(houses * 25 + hotels * 100);
		}
		break;

	case Lottery::Insurance:
		if (!CUSER->IsComputer()) {
			Dialog d("�� ��������� ���������");
			d.SetRectangle(17, 30, 35, 10);
			d.SetButton("����������");
			d.Show(map_);
		}
		CUSER->ReceiveInsurance();
		break;

	case Lottery::GoToStart:
		if (!CUSER->IsComputer()) {
			Dialog d("�� ������������� �� �����");
			d.SetRectangle(17, 30, 35, 10);
			d.SetButton("����������");
			d.Show(map_);
		}
		WINSURF.DrawSmilie(current_user_, CUSER->SetPosition(0), 0);
		break;

	case Lottery::GoToStartPlus200:
		if (!CUSER->IsComputer()) {
			Dialog d("�� ������������� �� �����\n� ��������� 200$");
			d.SetRectangle(17, 30, 35, 10);
			d.SetButton("����������");
			d.Show(map_);
		}
		WINSURF.DrawSmilie(current_user_, CUSER->SetPosition(0), 0);
		CUSER->ReceiveMoney(200);
		break;

	case Lottery::GoToJail:
		GoToJail("������������� � ������\n��� ��������� ����� 500$");
	}
}

void Manager::SpaceSiteAnalysis(int pos)
{
	int key = 1;
	if(map_.IsPossibleBuySpace(pos)) {
		if(!CUSER->IsComputer()) {
			Dialog d("������ ������ �������?");
			d.SetRectangle(17, 30, 35, 10);
			d.SetButton("��", "���");
			key = d.Show(map_);
		}
		if(key == 1)
			map_.BuySpace(pos, current_user_);
	}
	else {
		// ���� ������� ��� ������.
		int rent = map_.Rent(pos, dice_1_ + dice_2_);
		if(map_.Owner(pos) == current_user_) {
			// ��� ��� �������. �������� �����.
			CUSER->ReceiveMoney(rent);
			if(map_.IsPossibleBuyBuilding(pos)) {
				// �� ����� �� ��� ��������� ���.
				if(!CUSER->IsComputer()) {
					Dialog d("������ ������ ���?");
					d.SetRectangle(17, 30, 35, 10);
					d.SetButton("��", "���");
					key = d.Show(map_);
				}
				if(key == 1)
					map_.BuyBuilding(pos, current_user_);
			}
		}
		else {
			// ��� �� ��� �������, ����������� �����.
			rent = ObligatoryPayment(rent);
			USERS.GetUser(map_.Owner(pos))->ReceiveMoney(rent);
		}
	}
}

void Manager::SpaceServiceAnalysis(int pos)
{
	int key = 1;
	if(map_.IsPossibleBuySpace(pos)) {
		if(!CUSER->IsComputer()) {
			Dialog d("������ ������ �����������?");
			d.SetRectangle(17, 30, 35, 10);
			d.SetButton("��", "���");
			key = d.Show(map_);
		}
		if(key == 1)
			map_.BuySpace(pos, current_user_);
	}
	else {
		// ��� ����������� ��� �������.
		int rent = map_.Rent(pos, dice_1_ + dice_2_);
		if(map_.Owner(pos) == current_user_) {
			// ��� ���� �����������. �������� �����.
			CUSER->ReceiveMoney(rent);
		}
		else {
			// ��� �� ���� �����������, ����������� �����.
			rent = ObligatoryPayment(rent);
			USERS.GetUser(map_.Owner(pos))->ReceiveMoney(rent);
		}
	}
}

void Manager::SpaceTaxationAnalysis(int pos)
{
	int rent = map_.Rent(pos, dice_1_ + dice_2_);
	if(!CUSER->IsComputer()) {
		char buf[256];
		sprintf(buf, "�� ������� �������� %i$", rent);
		Dialog d(buf);
		d.SetRectangle(17, 30, 35, 10);
		d.SetButton("����������");
		d.Show(map_);
	}
	ObligatoryPayment(rent);
}

int Manager::ObligatoryPayment(int is_required)
{
	while(!CUSER->Payment(is_required))
	{
		// ��������� ���� �� � ������ ��� �������.
		if(!map_.ThereIsRealEstate(current_user_)) {
			// �������� ��� ��������.
			is_required = CUSER->HowMuchMoney();
			bankrupt_ = true;
			{
				Dialog d("� ��� ������������ ����� �� �����\n�� ������������� � ��������� �� ����");
				d.SetRectangle(11, 30, 47, 10);
				d.SetButton("����������");
				d.Show(map_);
			}


			DeleteUser(current_user_);
			if (USERS.GetUsersCount() == 1) {
				char buf[256];
				sprintf(buf, "�������: %s!", USERS.GetUser(0)->GetName());
				Dialog d(buf);
				d.SetRectangle(17, 30, 35, 10);
				d.SetButton("����������");
				d.Show(0);
				// ���� ������� ����.
				remove(storage);
				exit(0);
			}
			else {
				bool b = true;
				for(int i = 0; i < USERS.GetUsersCount(); i++)
				{
					b = b && USERS.GetUser(i)->IsComputer();
				}
				if (b) {
					Dialog d("� ���� �� �������� �����\n���� ���������");
					d.SetRectangle(17, 30, 35, 10);
					d.SetButton("����������");
					d.Show(0);
					// ���� ������� ����.
					remove(storage);
					exit(0);
				}
			}
			current_user_--;
			return is_required;
		}
		else {
			int space = -1;
			if(!CUSER->IsComputer()) {
				Dialog d("� ��� ������������ ����� �� �����\n�������� ������������ ��� �������");
				d.SetRectangle(11, 30, 47, 10);
				int key = d.Show(1);
				while (key == 0 || key > 99)
				{
					if(key == 0)
						key = d.Show(1);
					d.Hide();
					space = key - 100;
					if(key > 99) {
						Dialog d21(map_.GetSpace(space));
						d21.SetRectangle(10, 8, 49, 22);
						if(map_.Owner(space) == current_user_ && (map_.IsPossibleSell(space) || map_.IsPossibleSellBuilding(space)))
							d21.SetButton("����������", "�������");
						else
							d21.SetButton("����������");
						key = d21.Show(1);
					}
					if (key == 1)
						key--;
				}
			}
			else {
				space = map_.GetRealEstateForSale(current_user_);
			}
			if(!map_.SellBuilding(space, current_user_))
				map_.SellSpace(space, current_user_);
		}
	}
	return is_required;
}

void Manager::DeleteUser(int deleted_user)
{
	for(int i = 0; i < USERS.GetUsersCount(); i++)
	{
		USERS.GetUser(i)->ClearInfo();
	}
	WINSURF.ClearSmilie(deleted_user);
	
	// ����� ����� ����� �������� ������ ������ �� ����
	// ����� ������������ ������ �������������.
	map_.ReindexOwners(deleted_user);
	USERS.DeleteUser(deleted_user);

	for(int i = 0; i < USERS.GetUsersCount(); i++)
	{
		USERS.GetUser(i)->ShowInfo();
	}
}
