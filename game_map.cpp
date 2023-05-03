#include "game_map.h"
#include "user.h"
#include "dialog.h"
#include "window_surface.h"

GameMap::GameMap()
{
	// Старт.
	spaces_list_[0].type = Space::Start;
	// Старая дорога.
	spaces_list_[1].type = Space::Site;
	spaces_list_[1].site.street = "Старая дорога";
	spaces_list_[1].site.group = 0;
	spaces_list_[1].site.owner = -1;
	spaces_list_[1].site.cost = 60;
	spaces_list_[1].site.rent0 = 2;
	spaces_list_[1].site.rent1 = 10;
	spaces_list_[1].site.rent2 = 30;
	spaces_list_[1].site.rent3 = 90;
	spaces_list_[1].site.rent4 = 160;
	spaces_list_[1].site.rent5 = 250;
	spaces_list_[1].site.cost_building = 50;
	spaces_list_[1].site.buildings = 0;
	// Общественная казна.
	spaces_list_[2].type = Space::PublicTreasury;
	// Главное шоссе.
	spaces_list_[3].type = Space::Site;
	spaces_list_[3].site.street = "Главное шоссе";
	spaces_list_[3].site.group = 0;
	spaces_list_[3].site.owner = -1;
	spaces_list_[3].site.cost = 60;
	spaces_list_[3].site.rent0 = 4;
	spaces_list_[3].site.rent1 = 20;
	spaces_list_[3].site.rent2 = 60;
	spaces_list_[3].site.rent3 = 180;
	spaces_list_[3].site.rent4 = 320;
	spaces_list_[3].site.rent5 = 450;
	spaces_list_[3].site.cost_building = 50;
	spaces_list_[3].site.buildings = 0;
	// Налог с дохода.
	spaces_list_[4].type = Space::Taxation;
	spaces_list_[4].taxation.name = "Налог с дохода";
	spaces_list_[4].taxation.rent = 250;
	// Аэропорт
	spaces_list_[5].type = Space::Service;
	spaces_list_[5].service.name = "Аэропорт";
	spaces_list_[5].service.group = 8;
	spaces_list_[5].service.owner = -1;
	spaces_list_[5].service.cost = 200;
	spaces_list_[5].service.rent = 25;
	// Аквапарк.
	spaces_list_[6].type = Space::Site;
	spaces_list_[6].site.street = "Аквапарк";
	spaces_list_[6].site.group = 1;
	spaces_list_[6].site.owner = -1;
	spaces_list_[6].site.cost = 100;
	spaces_list_[6].site.rent0 = 6;
	spaces_list_[6].site.rent1 = 30;
	spaces_list_[6].site.rent2 = 90;
	spaces_list_[6].site.rent3 = 270;
	spaces_list_[6].site.rent4 = 400;
	spaces_list_[6].site.rent5 = 550;
	spaces_list_[6].site.cost_building = 50;
	spaces_list_[6].site.buildings = 0;
	// Шанс.
	spaces_list_[7].type = Space::Chance;
	// Городской парк.
	spaces_list_[8].type = Space::Site;
	spaces_list_[8].site.street = "Городской парк";
	spaces_list_[8].site.group = 1;
	spaces_list_[8].site.owner = -1;
	spaces_list_[8].site.cost = 100;
	spaces_list_[8].site.rent0 = 6;
	spaces_list_[8].site.rent1 = 30;
	spaces_list_[8].site.rent2 = 90;
	spaces_list_[8].site.rent3 = 270;
	spaces_list_[8].site.rent4 = 400;
	spaces_list_[8].site.rent5 = 550;
	spaces_list_[8].site.cost_building = 50;
	spaces_list_[8].site.buildings = 0;
	// Горнолыжный курорт.
	spaces_list_[9].type = Space::Site;
	spaces_list_[9].site.street = "Горнолыжный курорт";
	spaces_list_[9].site.group = 1;
	spaces_list_[9].site.owner = -1;
	spaces_list_[9].site.cost = 120;
	spaces_list_[9].site.rent0 = 8;
	spaces_list_[9].site.rent1 = 40;
	spaces_list_[9].site.rent2 = 100;
	spaces_list_[9].site.rent3 = 300;
	spaces_list_[9].site.rent4 = 450;
	spaces_list_[9].site.rent5 = 600;
	spaces_list_[9].site.cost_building = 50;
	spaces_list_[9].site.buildings = 0;
	// Тюрьма.
	spaces_list_[10].type = Space::Jail;
	// Спальный район.
	spaces_list_[11].type = Space::Site;
	spaces_list_[11].site.street = "Спальный район";
	spaces_list_[11].site.group = 2;
	spaces_list_[11].site.owner = -1;
	spaces_list_[11].site.cost = 140;
	spaces_list_[11].site.rent0 = 10;
	spaces_list_[11].site.rent1 = 50;
	spaces_list_[11].site.rent2 = 150;
	spaces_list_[11].site.rent3 = 450;
	spaces_list_[11].site.rent4 = 625;
	spaces_list_[11].site.rent5 = 750;
	spaces_list_[11].site.cost_building = 100;
	spaces_list_[11].site.buildings = 0;
	// Мобильная связь.
	spaces_list_[12].type = Space::Communication;
	spaces_list_[12].service.name = "Мобильная связь";
	spaces_list_[12].service.group = 10;
	spaces_list_[12].service.owner = -1;
	spaces_list_[12].service.cost = 150;
	spaces_list_[12].service.rent = 5;
	// Деловой квартал.
	spaces_list_[13].type = Space::Site;
	spaces_list_[13].site.street = "Деловой квартал";
	spaces_list_[13].site.group = 2;
	spaces_list_[13].site.owner = -1;
	spaces_list_[13].site.cost = 140;
	spaces_list_[13].site.rent0 = 10;
	spaces_list_[13].site.rent1 = 50;
	spaces_list_[13].site.rent2 = 150;
	spaces_list_[13].site.rent3 = 450;
	spaces_list_[13].site.rent4 = 625;
	spaces_list_[13].site.rent5 = 750;
	spaces_list_[13].site.cost_building = 100;
	spaces_list_[13].site.buildings = 0;
	// Торговая площадь.
	spaces_list_[14].type = Space::Site;
	spaces_list_[14].site.street = "Торговая площадь";
	spaces_list_[14].site.group = 2;
	spaces_list_[14].site.owner = -1;
	spaces_list_[14].site.cost = 160;
	spaces_list_[14].site.rent0 = 12;
	spaces_list_[14].site.rent1 = 60;
	spaces_list_[14].site.rent2 = 180;
	spaces_list_[14].site.rent3 = 500;
	spaces_list_[14].site.rent4 = 700;
	spaces_list_[14].site.rent5 = 900;
	spaces_list_[14].site.cost_building = 100;
	spaces_list_[14].site.buildings = 0;
	// Железнодорожный вокзал.
	spaces_list_[15].type = Space::Service;
	spaces_list_[15].service.name = "Железнодорожный вокзал";
	spaces_list_[15].service.group = 9;
	spaces_list_[15].service.owner = -1;
	spaces_list_[15].service.cost = 200;
	spaces_list_[15].service.rent = 25;
	// Улица Пушкина.
	spaces_list_[16].type = Space::Site;
	spaces_list_[16].site.street = "Улица Пушкина";
	spaces_list_[16].site.group = 3;
	spaces_list_[16].site.owner = -1;
	spaces_list_[16].site.cost = 180;
	spaces_list_[16].site.rent0 = 14;
	spaces_list_[16].site.rent1 = 70;
	spaces_list_[16].site.rent2 = 200;
	spaces_list_[16].site.rent3 = 550;
	spaces_list_[16].site.rent4 = 750;
	spaces_list_[16].site.rent5 = 950;
	spaces_list_[16].site.cost_building = 100;
	spaces_list_[16].site.buildings = 0;
	// Общественная казна.
	spaces_list_[17].type = Space::PublicTreasury;
	// Проспект Мира.
	spaces_list_[18].type = Space::Site;
	spaces_list_[18].site.street = "Проспект Мира";
	spaces_list_[18].site.group = 3;
	spaces_list_[18].site.owner = -1;
	spaces_list_[18].site.cost = 180;
	spaces_list_[18].site.rent0 = 14;
	spaces_list_[18].site.rent1 = 70;
	spaces_list_[18].site.rent2 = 200;
	spaces_list_[18].site.rent3 = 550;
	spaces_list_[18].site.rent4 = 750;
	spaces_list_[18].site.rent5 = 950;
	spaces_list_[18].site.cost_building = 100;
	spaces_list_[18].site.buildings = 0;
	// Проспект Победы.
	spaces_list_[19].type = Space::Site;
	spaces_list_[19].site.street = "Проспект Победы";
	spaces_list_[19].site.group = 3;
	spaces_list_[19].site.owner = -1;
	spaces_list_[19].site.cost = 200;
	spaces_list_[19].site.rent0 = 16;
	spaces_list_[19].site.rent1 = 80;
	spaces_list_[19].site.rent2 = 220;
	spaces_list_[19].site.rent3 = 600;
	spaces_list_[19].site.rent4 = 800;
	spaces_list_[19].site.rent5 = 1000;
	spaces_list_[19].site.cost_building = 100;
	spaces_list_[19].site.buildings = 0;
	// Беспплатная стоянка.
	spaces_list_[20].type = Space::FreeParking;
	// Бар.
	spaces_list_[21].type = Space::Site;
	spaces_list_[21].site.street = "Бар";
	spaces_list_[21].site.group = 4;
	spaces_list_[21].site.owner = -1;
	spaces_list_[21].site.cost = 220;
	spaces_list_[21].site.rent0 = 18;
	spaces_list_[21].site.rent1 = 90;
	spaces_list_[21].site.rent2 = 250;
	spaces_list_[21].site.rent3 = 700;
	spaces_list_[21].site.rent4 = 875;
	spaces_list_[21].site.rent5 = 1050;
	spaces_list_[21].site.cost_building = 150;
	spaces_list_[21].site.buildings = 0;
	// Шанс.
	spaces_list_[22].type = Space::Chance;
	// Ночной клуб.
	spaces_list_[23].type = Space::Site;
	spaces_list_[23].site.street = "Ночной клуб";
	spaces_list_[23].site.group = 4;
	spaces_list_[23].site.owner = -1;
	spaces_list_[23].site.cost = 220;
	spaces_list_[23].site.rent0 = 18;
	spaces_list_[23].site.rent1 = 90;
	spaces_list_[23].site.rent2 = 250;
	spaces_list_[23].site.rent3 = 700;
	spaces_list_[23].site.rent4 = 875;
	spaces_list_[23].site.rent5 = 1050;
	spaces_list_[23].site.cost_building = 150;
	spaces_list_[23].site.buildings = 0;
	// Ресторан.
	spaces_list_[24].type = Space::Site;
	spaces_list_[24].site.street = "Ресторан";
	spaces_list_[24].site.group = 4;
	spaces_list_[24].site.owner = -1;
	spaces_list_[24].site.cost = 240;
	spaces_list_[24].site.rent0 = 20;
	spaces_list_[24].site.rent1 = 100;
	spaces_list_[24].site.rent2 = 300;
	spaces_list_[24].site.rent3 = 750;
	spaces_list_[24].site.rent4 = 925;
	spaces_list_[24].site.rent5 = 1100;
	spaces_list_[24].site.cost_building = 150;
	spaces_list_[24].site.buildings = 0;
	// Аэропорт
	spaces_list_[25].type = Space::Service;
	spaces_list_[25].service.name = "Аэропорт";
	spaces_list_[25].service.group = 8;
	spaces_list_[25].service.owner = -1;
	spaces_list_[25].service.cost = 200;
	spaces_list_[25].service.rent = 25;
	// Улица Солнечная.
	spaces_list_[26].type = Space::Site;
	spaces_list_[26].site.street = "Улица Солнечная";
	spaces_list_[26].site.group = 5;
	spaces_list_[26].site.owner = -1;
	spaces_list_[26].site.cost = 260;
	spaces_list_[26].site.rent0 = 22;
	spaces_list_[26].site.rent1 = 110;
	spaces_list_[26].site.rent2 = 330;
	spaces_list_[26].site.rent3 = 800;
	spaces_list_[26].site.rent4 = 975;
	spaces_list_[26].site.rent5 = 1150;
	spaces_list_[26].site.cost_building = 150;
	spaces_list_[26].site.buildings = 0;
	// Улица Тенистая.
	spaces_list_[27].type = Space::Site;
	spaces_list_[27].site.street = "Улица Тенистая";
	spaces_list_[27].site.group = 5;
	spaces_list_[27].site.owner = -1;
	spaces_list_[27].site.cost = 260;
	spaces_list_[27].site.rent0 = 22;
	spaces_list_[27].site.rent1 = 110;
	spaces_list_[27].site.rent2 = 330;
	spaces_list_[27].site.rent3 = 800;
	spaces_list_[27].site.rent4 = 975;
	spaces_list_[27].site.rent5 = 1150;
	spaces_list_[27].site.cost_building = 150;
	spaces_list_[27].site.buildings = 0;
	// Интернет.
	spaces_list_[28].type = Space::Communication;
	spaces_list_[28].service.name = "Интернет";
	spaces_list_[28].service.group = 10;
	spaces_list_[28].service.owner = -1;
	spaces_list_[28].service.cost = 150;
	spaces_list_[28].service.rent = 5;
	// Улица Виноградная.
	spaces_list_[29].type = Space::Site;
	spaces_list_[29].site.street = "Улица Виноградная";
	spaces_list_[29].site.group = 5;
	spaces_list_[29].site.owner = -1;
	spaces_list_[29].site.cost = 280;
	spaces_list_[29].site.rent0 = 24;
	spaces_list_[29].site.rent1 = 120;
	spaces_list_[29].site.rent2 = 360;
	spaces_list_[29].site.rent3 = 850;
	spaces_list_[29].site.rent4 = 1025;
	spaces_list_[29].site.rent5 = 1200;
	spaces_list_[29].site.cost_building = 150;
	spaces_list_[29].site.buildings = 0;
	// Отправляйся в тюрьму.
	spaces_list_[30].type = Space::GoToJail;
	// Улица Кленовая.
	spaces_list_[31].type = Space::Site;
	spaces_list_[31].site.street = "Улица Кленовая";
	spaces_list_[31].site.group = 6;
	spaces_list_[31].site.owner = -1;
	spaces_list_[31].site.cost = 300;
	spaces_list_[31].site.rent0 = 26;
	spaces_list_[31].site.rent1 = 130;
	spaces_list_[31].site.rent2 = 390;
	spaces_list_[31].site.rent3 = 900;
	spaces_list_[31].site.rent4 = 1100;
	spaces_list_[31].site.rent5 = 1275;
	spaces_list_[31].site.cost_building = 200;
	spaces_list_[31].site.buildings = 0;
	// Улица Садовая.
	spaces_list_[32].type = Space::Site;
	spaces_list_[32].site.street = "Улица Садовая";
	spaces_list_[32].site.group = 6;
	spaces_list_[32].site.owner = -1;
	spaces_list_[32].site.cost = 300;
	spaces_list_[32].site.rent0 = 26;
	spaces_list_[32].site.rent1 = 130;
	spaces_list_[32].site.rent2 = 390;
	spaces_list_[32].site.rent3 = 900;
	spaces_list_[32].site.rent4 = 1100;
	spaces_list_[32].site.rent5 = 1275;
	spaces_list_[32].site.cost_building = 200;
	spaces_list_[32].site.buildings = 0;
	// Общественная казна.
	spaces_list_[33].type = Space::PublicTreasury;
	// Проспект Ломоносва.
	spaces_list_[34].type = Space::Site;
	spaces_list_[34].site.street = "Проспект Ломоносва";
	spaces_list_[34].site.group = 6;
	spaces_list_[34].site.owner = -1;
	spaces_list_[34].site.cost = 320;
	spaces_list_[34].site.rent0 = 28;
	spaces_list_[34].site.rent1 = 150;
	spaces_list_[34].site.rent2 = 450;
	spaces_list_[34].site.rent3 = 1000;
	spaces_list_[34].site.rent4 = 1200;
	spaces_list_[34].site.rent5 = 1400;
	spaces_list_[34].site.cost_building = 200;
	spaces_list_[34].site.buildings = 0;
	// Железнодорожный вокзал.
	spaces_list_[35].type = Space::Service;
	spaces_list_[35].service.name = "Железнодорожный вокзал";
	spaces_list_[35].service.group = 9;
	spaces_list_[35].service.owner = -1;
	spaces_list_[35].service.cost = 200;
	spaces_list_[35].service.rent = 25;
	// Шанс.
	spaces_list_[36].type = Space::Chance;
	// Приморский бульвар.
	spaces_list_[37].type = Space::Site;
	spaces_list_[37].site.street = "Приморский бульвар";
	spaces_list_[37].site.group = 7;
	spaces_list_[37].site.owner = -1;
	spaces_list_[37].site.cost = 350;
	spaces_list_[37].site.rent0 = 35;
	spaces_list_[37].site.rent1 = 175;
	spaces_list_[37].site.rent2 = 500;
	spaces_list_[37].site.rent3 = 1100;
	spaces_list_[37].site.rent4 = 1300;
	spaces_list_[37].site.rent5 = 1500;
	spaces_list_[37].site.cost_building = 200;
	spaces_list_[37].site.buildings = 0;
	// Налог на роскошь.
	spaces_list_[38].type = Space::Taxation;
	spaces_list_[38].taxation.name = "Налог на роскошь";
	spaces_list_[38].taxation.rent = 500;
	// Набережная.
	spaces_list_[39].type = Space::Site;
	spaces_list_[39].site.street = "Набережная";
	spaces_list_[39].site.group = 7;
	spaces_list_[39].site.owner = -1;
	spaces_list_[39].site.cost = 400;
	spaces_list_[39].site.rent0 = 50;
	spaces_list_[39].site.rent1 = 200;
	spaces_list_[39].site.rent2 = 600;
	spaces_list_[39].site.rent3 = 1400;
	spaces_list_[39].site.rent4 = 1700;
	spaces_list_[39].site.rent5 = 2000;
	spaces_list_[39].site.cost_building = 200;
	spaces_list_[39].site.buildings = 0;
}

////////////////////////////////////////////////////////////////////////////////
const Space *GameMap::GetSpace(int index) const
{
	return &spaces_list_[index];
}

Space *GameMap::GetSpace(int index)
{
	return &spaces_list_[index];
}
////////////////////////////////////////////////////////////////////////////////

Space::Type GameMap::Type(int space) const
{
	return spaces_list_[space].type;
}

bool GameMap::IsOnSale(int space) const
{
	switch (spaces_list_[space].type)	{
		case Space::Site:
		case Space::Service:
		case Space::Communication:
			return true;
	}
	return false;
}

int GameMap::Owner(int space) const
{
	switch (spaces_list_[space].type)	{
		case Space::Site:
			return spaces_list_[space].site.owner;
		case Space::Service:
			return spaces_list_[space].service.owner;
		case Space::Communication:
			return spaces_list_[space].communication.owner;
	}
	return -1;
}

int GameMap::Group(int space) const
{
	switch (spaces_list_[space].type) {
		case Space::Site:
			return spaces_list_[space].site.group;
		case Space::Service:
			return spaces_list_[space].service.group;
		case Space::Communication:
			return spaces_list_[space].communication.group;
	}
	return -1;
}

bool GameMap::IsMonopoly(int space) const
{
	// Если у поля нет владельца, то нет и никакой монополии.
	if (Owner(space) == -1)
		return false;
	
	bool b = true;
	for (int i = 0; i < 40; i++) {
		if (Group(i) == Group(space))
			b = b && Owner(i) == Owner(space);
	}
	return b;
}

bool GameMap::IsPossibleBuySpace(int space) const
{
	return IsOnSale(space) && Owner(space) == -1;
}

int GameMap::Cost(int space) const
{
	switch (spaces_list_[space].type)	{
		case Space::Site:
			return spaces_list_[space].site.cost;
		case Space::Service:
			return spaces_list_[space].service.cost;
		case Space::Communication:
			return spaces_list_[space].communication.cost;
	}
	return 0;
}

bool GameMap::IsPossibleBuyBuilding(int space) const
{
	// Если это не участок для застройки, то и строить здесь ничего нельзя.
	if (spaces_list_[space].type != Space::Site)
		return false;
	// Если уже построен отель больше строить нельзя.
	if(spaces_list_[space].site.buildings == 5)
		return false;
	// Теперь проверяем является ли это поле частью монополии и не нарушим ли мы равномерность
	// застройки, разрешив строительство на этом поле.
	bool b = true;
	for (int i = 0; i < 40; i++) {
		if (Group(i) == Group(space))
			b = b && Owner(i) == Owner(space) &&
			         spaces_list_[space].site.buildings - spaces_list_[i].site.buildings < 1;
	}
	return b;
}

int GameMap::CostOfBuilding(int space) const
{
	if (spaces_list_[space].type == Space::Site)
		return spaces_list_[space].site.cost_building;
	return 0;
}

int GameMap::HowManyBuildings(int space) const
{
	if (spaces_list_[space].type == Space::Site)
		return spaces_list_[space].site.buildings;
	return 0;
}

bool GameMap::IsPossibleSell(int space) const
{
	// Нельзя продать то, что никому не принадлежит.
	if (Owner(space) == -1)
		return false;
	// Услуги транспорта и коммуникации можно продавать сразу.
	if (spaces_list_[space].type == Space::Service ||
		  spaces_list_[space].type == Space::Communication)
		return true;
	// Теперь проверяем наличие домов или отелей в этой группе.
	bool b = true;
	for (int i = 0; i < 40; i++) {
		if (Group(i) == Group(space))
			b = b && spaces_list_[i].site.buildings  == 0;
	}
	return b;
}

bool GameMap::IsPossibleSellBuilding(int space) const
{
	// Нельзя продать то, что никто не купил.
	if (Owner(space) == -1)
		return false;
	// Если это не участок для застройки, то на нем нет и строений.
	if (spaces_list_[space].type != Space::Site)
		return false;
	// Проверяем есть ли вообще на этом поле строения.
	if (spaces_list_[space].site.buildings == 0)
		return false;
		// Проверяем не нарушим ли мы равномерность застройки, продав дом с этого поля.
		bool b = true;
		for (int i = 0; i < 40; i++) {
			if (Group(i) == Group(space))
				b = b && spaces_list_[i].site.buildings - spaces_list_[space].site.buildings < 1;
		}
		return b;
}

bool GameMap::ThereIsRealEstate(int user) const
{
	for (int i = 0; i < 40; i++) {
		if(Owner(i) == user)
			return true;
	}
	return false;
}

void GameMap::HowManyBuildingsAtUser(int user, int &houses, int &hotels) const
{
	for (int i = 0; i < 40; i++)
	{
		if (Owner(i) == user) {
			if (HowManyBuildings(i) < 5) {
				houses += HowManyBuildings(i);
			}
			else {
				hotels += 1;
			}
		}
	}
}

bool GameMap::BuySpace(int space, int user)
{
	if(!IsPossibleBuySpace(space))
		return false;
	if(USERS.GetUser(user)->Payment(Cost(space))) {
		switch (spaces_list_[space].type)	{
			case Space::Site:
				spaces_list_[space].site.owner = user; break;
			case Space::Service:
				spaces_list_[space].service.owner = user; break;
			case Space::Communication:
				spaces_list_[space].communication.owner = user;
		}
		if(IsMonopoly(space))
			USERS.GetUser(user)->IncMonopolies();
		WINSURF.RedrawSpace(space, USERS.GetUser(user)->GetColor());
		return true;
	}
	if(!USERS.GetUser(user)->IsComputer()) {
		Dialog d("У вас недостаточно денег на счету");
		d.SetRectangle(15, 30, 39, 10);
		d.SetButton("Продолжить");
		d.Show(*this);
	}
	return false;
}

bool GameMap::BuyBuilding(int space, int user)
{
	if(!IsPossibleBuyBuilding(space))
		return false;
	Dialog d("");
	if(USERS.GetUser(user)->Payment(CostOfBuilding(space))) {
		spaces_list_[space].site.buildings++;
		return true;
	}
	if(!USERS.GetUser(user)->IsComputer()) {
		Dialog d("У вас недостаточно денег на счету");
		d.SetRectangle(15, 30, 39, 10);
		d.SetButton("Продолжить");
		d.Show(*this);
	}
	return false;
}

bool GameMap::SellSpace(int space, int user)
{
	if(!IsPossibleSell(space))
		return false;
	bool b = IsMonopoly(space);
	switch (spaces_list_[space].type)	{
		case Space::Site:
			spaces_list_[space].site.owner = -1; break;
		case Space::Service:
			spaces_list_[space].service.owner = -1; break;
		case Space::Communication:
			spaces_list_[space].communication.owner = -1;
	}
	USERS.GetUser(user)->ReceiveMoney(Cost(space) / 2);
	if(b)
		USERS.GetUser(user)->DecMonopolies();
	WINSURF.RedrawSpace(space, LightGray);
	return true;
}

bool GameMap::SellBuilding(int space, int user)
{
	if(!IsPossibleSellBuilding(space))
		return false;
	spaces_list_[space].site.buildings--;
	USERS.GetUser(user)->ReceiveMoney(CostOfBuilding(space) / 2);
	return true;
}

int GameMap::GetRealEstateForSale(int user) const
{
	if(!ThereIsRealEstate(user))
		return -1;
	struct { int index; int rent; } items[25];
	int count = 0;
	for(int i = 0; i < 40; i++)
	{
		if(Owner(i) == user) {
			int j = 0;
			int rent = Rent(i, 6);
			for( ; j < count && items[j].rent < rent; j++);
			for(int k = count - 1; k >= j; k--)
				items[k + 1] = items[k];
			items[j].index = i;
			items[j].rent = rent;
			count++;
		}
	}
	for(int i = 0; i < count; i++)
	{
		if(IsPossibleSellBuilding(items[i].index))
			return items[i].index;
		if(IsPossibleSell(items[i].index))
			return items[i].index;
	}
	return -1;
}

int GameMap::Rent(int space, int points_on_dices) const
{
	int rent = 0;
	switch (spaces_list_[space].type)
	{
	case Space::Site:
		switch (spaces_list_[space].site.buildings)
		{
		case 0: rent = spaces_list_[space].site.rent0; break;
		case 1: rent = spaces_list_[space].site.rent1; break;
		case 2: rent = spaces_list_[space].site.rent2; break;
		case 3: rent = spaces_list_[space].site.rent3; break;
		case 4: rent = spaces_list_[space].site.rent4; break;
		case 5: rent = spaces_list_[space].site.rent5;
		}
		break;
	case Space::Service:
		rent = spaces_list_[space].service.rent;
		break;
	case Space::Communication:
		rent = points_on_dices * spaces_list_[space].communication.rent;
		break;
	case Space::Taxation:
		rent = spaces_list_[space].taxation.rent;
	}
	return IsMonopoly(space) ? 2 * rent : rent;
}

void GameMap::ReindexOwners(int deleted_user)
{
	if(deleted_user == USERS.GetUsersCount() - 1)
		return;
	for(int i = 0; i < 40; i++)
	{
		if(Owner(i) > deleted_user) {
			switch (spaces_list_[i].type)	{
			case Space::Site:
				spaces_list_[i].site.owner--; break;
			case Space::Service:
				spaces_list_[i].service.owner--; break;
			case Space::Communication:
				spaces_list_[i].communication.owner--;
			}
		}
	}
}

bool GameMap::Load(FILE *file)
{
	for(int i = 0; i < 40; i++)
	{
		if(spaces_list_[i].Load(file) == false)
				return false;
	}
	return true;
}

bool GameMap::Save(FILE *file)
{
	for(int i = 0; i < 40; i++)
	{
		if (spaces_list_[i].Save(file) == false)
				return false;
	}
	return true;
}
