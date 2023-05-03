#ifndef GAME_MAP_H_
#define GAME_MAP_H_

#include "space.h"

class GameMap
{
public:
	GameMap();

	const Space *GetSpace(int index) const;	// TODO: ��������.
	Space *GetSpace(int index);							// TODO: ��������.

	// ��� ��� �� ����?
	Space::Type Type(int space) const;
	// ��������� �� ������ ��� ����?
	bool IsOnSale(int space) const;
	// �������� �������. ���� ��� ��������� - ���������� -1.
	int Owner(int space) const;
	// � ����� ������ ��������� ��� ����?
	// ���� ��� �� ������ � ����� ���� ������ - ���������� -1.
	int Group(int space) const;
	// �������� �� ��� ���� ������ ���������?
	bool IsMonopoly(int space) const;
	// ����� �� ������ ������ ��� ����?
	// ���� ��� ������ �� ��������� ��� � ���� ��� ���� �������� - ���������� false.
	bool IsPossibleBuySpace(int space) const;
	// ��������� ������� ����.
	// ���� ���� ������ �� ��������� - ���������� 0.
	int Cost(int space) const;
	// ����� �� ������ ������� �� ���� ����?
	// ���� ��� ������ �� �������� ��������� ��� ��������� ��� �� �������� ������ ���������
	// ��� ����� �������� ������������� ��������� ��������� - ���������� false.
	bool IsPossibleBuyBuilding(int space) const;
	// ��������� ��������� �� ���� ����.
	// ���� ��� ������ �� �������� ��������� ��� ��������� - ���������� 0.
	int CostOfBuilding(int space) const;
	// ������� ����� ��������� �� ���� ����?
	// ���� ��� ������ �� �������� ��������� ��� ��������� ��� �� ���� ���� ��� �������� - 
	// ���������� 0.
	int HowManyBuildings(int space) const;
	// ����� �� ������ ������� ��� ����?
	// ���� ��� ������ �� ��������� ��� � ���� ��� ���������, �������� ������ ��������� ��
	// ����� ������� ���� ��������� - ���������� false.
	bool IsPossibleSell(int space) const;
	// ����� �� ������ ������� ��� ��� ����� �� ���� ����?
	// ���� �� ���� ��� �������� ��� ����� �������� ������������� ��������� ��������� -
	// ���������� false.
	bool IsPossibleSellBuilding(int space) const;
	// ������� �� ������������ �������������?
	bool ThereIsRealEstate(int user) const;
	// ������� ����� � ������ � ������������?
	void HowManyBuildingsAtUser(int user, int &houses, int &hotels) const;

	// ������ ����.
	bool BuySpace(int space, int user);
	// ������ ��� ��� �����.
	bool BuyBuilding(int space, int user);
	// ������� ����.
	bool SellSpace(int space, int user);
	// ������� ��� ��� �����.
	bool SellBuilding(int space, int user);
	// ��������� ������������ ��� �������. what ����� �������� 1, ���� ������������� �������
	// ���� � 2, ���� ������������� ������� ��� ��� �����. ���� ������������ ������ �������
	// - ���������� -1.
	int GetRealEstateForSale(int user) const;

	// ������� �����, ������, ������.
	// ���� �� ���� ���� ��� ������� ����� - ���������� 0.
	int Rent(int space, int points_on_dices) const;
	// ��������������� ���������� ����� ��������� ������.
	void ReindexOwners(int deleted_user);

	bool Load(FILE *file);
	bool Save(FILE *file);

private:
	Space spaces_list_[40];
};

#endif