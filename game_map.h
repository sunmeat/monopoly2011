#ifndef GAME_MAP_H_
#define GAME_MAP_H_

#include "space.h"

class GameMap
{
public:
	GameMap();

	const Space *GetSpace(int index) const;	// TODO: Устарело.
	Space *GetSpace(int index);							// TODO: Устарело.

	// Что это за поле?
	Space::Type Type(int space) const;
	// Продается ли вообще это поле?
	bool IsOnSale(int space) const;
	// Владелец участка. Если нет владельца - возвращает -1.
	int Owner(int space) const;
	// К какой группе относится это поле?
	// Если оно не входит в какую либо группу - возвращает -1.
	int Group(int space) const;
	// Является ли это поле частью монополии?
	bool IsMonopoly(int space) const;
	// Можно ли сейчас купить это поле?
	// Если оно вообще не продается или у него уже есть владелец - возвращает false.
	bool IsPossibleBuySpace(int space) const;
	// Стоимость покупки поля.
	// Если поле вообще не продается - возвращает 0.
	int Cost(int space) const;
	// Можно ли сейчас строить на этом поле?
	// Если оно вообще не является участоком для застройки или не является частью монополии
	// или будет нарушена равномерность застройки монополии - возвращает false.
	bool IsPossibleBuyBuilding(int space) const;
	// Стоимость постройки на этом поле.
	// Если оно вообще не является участоком для застройки - возвращает 0.
	int CostOfBuilding(int space) const;
	// Сколько домов построено на этом поле?
	// Если оно вообще не является участоком для застройки или на этом поле нет строений - 
	// возвращает 0.
	int HowManyBuildings(int space) const;
	// Можно ли сейчас продать это поле?
	// Если оно вообще не продается или у него нет владелеца, является частью монополии на
	// полях которой есть постройки - возвращает false.
	bool IsPossibleSell(int space) const;
	// Можно ли сейчас продать дом или отель на этом поле?
	// Если на поле нет строений или будет нарушена равномерность застройки монополии -
	// возвращает false.
	bool IsPossibleSellBuilding(int space) const;
	// Владеет ли пользователь недвижимостью?
	bool ThereIsRealEstate(int user) const;
	// Сколько домов и отелей у пользователя?
	void HowManyBuildingsAtUser(int user, int &houses, int &hotels) const;

	// Купить поле.
	bool BuySpace(int space, int user);
	// Купить дом или отель.
	bool BuyBuilding(int space, int user);
	// Продать поле.
	bool SellSpace(int space, int user);
	// Продать дом или отель.
	bool SellBuilding(int space, int user);
	// Подобрать недвижимость для продажи. what имеет значение 1, если рекомендуется продать
	// поле и 2, если рекомендуется продать дом или отель. Если пользователю нечего продать
	// - возвращает -1.
	int GetRealEstateForSale(int user) const;

	// Рентная плата, штрафы, налоги.
	// Если на этом поле нет рентной платы - возвращает 0.
	int Rent(int space, int points_on_dices) const;
	// Переиндексирует владельцев перед удалением игрока.
	void ReindexOwners(int deleted_user);

	bool Load(FILE *file);
	bool Save(FILE *file);

private:
	Space spaces_list_[40];
};

#endif