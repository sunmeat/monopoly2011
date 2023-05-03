#ifndef USER_H_
#define USER_H_

#include <stdio.h>
#include "color.h"

class User
{
public:
	User(const char *name, bool is_computer);
	~User();

	void ShowInfo();
	void ClearInfo();
	void SetActive(bool b);

	const char * GetName() const;
	bool IsComputer() const;
	void SetColor(Color color);
	Color GetColor() const;
	// ������� ������� ������ �� �����.
	int GetPosition() const;
	// ���������� ����� ������� (���������� ����������).
	int SetPosition(int new_pos);
	// ������� ����� �� �����
	int HowMuchMoney() const;
	// �������� ������ (�������� �� ������� ������������).
	void ReceiveMoney(int how_much);
	// ������ (��������, ����� ��� ������� ������������).
	// ���������� false ���� �� ����� ������������ �����.
	bool Payment(int is_required);
	// ������� ��������� ������� � ������.
	int HowManyInsurances() const;
	// �������� ��������� �����.
	void ReceiveInsurance();
	// ������ ��������� �����.
	void GiveInsurance();
	// ������� ��������� � ������.
	int GetMonopolies() const;
	// ����� ������� ����� ���������.
	void IncMonopolies();
	// ����� ������� ���������.
	void DecMonopolies();
	// ������� ��� ������ � ����� ������ � ������� ������ ���� �� �����
	// ������� �������� ���������� ����� �����.
	int GetDoubles() const;
	// �� ����� ������� ������ ���������� ����� �����. ����������� �������.
	void IncDoubles();
	// �������� �������.
	void ResetDoubles();
	// ������� ��� ����� �������� ���������� ������.
	int GetPasses() const;
	// ��������� ������� ������������ ����� �� 1.
	void DecPasses();
	// �������� �������.
	void ResetPasses();
	// ���������� ������� � �������� 3 (����� ���������).
	void SetPasses();
	
	bool Load(FILE *file);
	bool Save(FILE *file);

private:
	User();
	User(const User &);
	User &operator=(const User &);

	int GetIndexInUsersList();

	char *name_;
	Color color_;
	bool is_computer_;
	int position_on_map_;
	int monetary_account_;
	int insurances_;
	int monopolies_;
	int doubles_;
	int pass_;
};

#define USERS UserList::instance()

class UserList
{
public:
	static UserList &instance();

	int GetUsersCount() const;
	int AddUser(const char *name, bool is_computer);
	void DeleteUser(int index);
	void DeleteAllUsers();
	User * GetUser(int index) const;

	bool Load(FILE *file);
	bool Save(FILE *file);

private:
	UserList();
	UserList(const UserList &);
	~UserList();
	UserList &operator = (const UserList &) ;

	User **list_;
	int count_;
};

#endif
