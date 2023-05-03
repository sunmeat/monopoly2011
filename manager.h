#ifndef MANAGER_H_
#define MANAGER_H_

#include "game_map.h"
#include "lottery.h"

class Manager
{
public:
	Manager();
	~Manager();

	void NewGame();
	void Run();

private:
	bool Load();
	bool Save();
	bool DoLoad(FILE *file);
	bool DoSave(FILE *file);

	bool CreateUsers() const;
	void SetNextUser();
	void ThrowDices();
	void Moving();
	void GoToJail(char *msg);
	// ����������� ����� ��������� ������ �� ����� � ��������� ����������� ��������.
	void PositionAnalysis();
	void SpaceJailAnalysis();
	void CardAction(Lottery::Card c);
	void SpaceSiteAnalysis(int pos);
	void SpaceServiceAnalysis(int pos);
	void SpaceTaxationAnalysis(int pos);
	// ������������ ������� (��������, ����� ��� �����).
	// ���������� ����� ������� �������� �� ������. ���� � ������ ������������ ����� ��
	// �����, �� �� ������� ������������ � ���������� ��������� �����. ���� �� �� �����
	// ������� ��������� �����, �� �� ������ ��� ��������� � ���� ������ � ��������
	// �� ����.
	int ObligatoryPayment(int is_required);

	void MoveUser();
	int Rand() const;
	// ��������� ������� ����������� �����������.
	int GoToJail_Computer() const;
	// ������� ���������������� ������ �� ������.
	void DeleteUser(int deleted_user);

	int current_user_;
	int dice_1_;
	int dice_2_;
	bool go_to_jail_;
	bool bankrupt_;
	GameMap map_;
	Lottery chance_;
	Lottery public_treasury_;
};

#endif
