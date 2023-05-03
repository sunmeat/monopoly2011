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
	// Текущая позиция игрока на карте.
	int GetPosition() const;
	// Устанавить новую позицию (возвращает предыдущую).
	int SetPosition(int new_pos);
	// Сколько денег на счету
	int HowMuchMoney() const;
	// Получить деньги (например от продажи недвижимости).
	void ReceiveMoney(int how_much);
	// Оплата (например, штраф или покупка недвижимости).
	// Возвращает false если на счету недостаточно денег.
	bool Payment(int is_required);
	// Сколько страховых полисов у игрока.
	int HowManyInsurances() const;
	// Получить страховой полис.
	void ReceiveInsurance();
	// Отдать страховой полис.
	void GiveInsurance();
	// Сколько монополий у игрока.
	int GetMonopolies() const;
	// Игрок получил новую монополию.
	void IncMonopolies();
	// Игрок потерял монополию.
	void DecMonopolies();
	// Сколько раз подряд у этого игрока в течении одного хода на обоих
	// кубиках выпадало одинаковое число очков.
	int GetDoubles() const;
	// На обоих кубиках выпало одинаковое число очков. Увеличиваем счетчик.
	void IncDoubles();
	// Сбросить счетчик.
	void ResetDoubles();
	// Сколько еще ходов осталось пропустить игроку.
	int GetPasses() const;
	// Уменьшить счетчик пропускаемых ходов на 1.
	void DecPasses();
	// Сбросить счетчик.
	void ResetPasses();
	// Установить счетчик в значение 3 (игрок арестован).
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
