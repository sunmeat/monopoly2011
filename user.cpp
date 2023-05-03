#include "user.h"
#include <string.h>
#include <iostream>

#include "window_surface.h"

User::User(const char *name, bool is_computer)
	: name_(0), is_computer_(is_computer), color_(LightGray), position_on_map_(0),
	monetary_account_(500), insurances_(0), monopolies_(0),
	doubles_(0), pass_(0)
{
	name_ = new char[strlen(name)+1];
	strcpy(name_, name);
}

User::~User()
{
	delete[]name_;
}

int User::GetIndexInUsersList()
{
	int i;
	for(i = 0; i < USERS.GetUsersCount(); i++)
	{
		if(USERS.GetUser(i) == this)
			break;
	}
	return i;
}

void User::ShowInfo()
{
	char buf[256];
	WINSURF.DrawRectangle(69, 1 + GetIndexInUsersList() * 9, 39, 8, LightGray);
	WINSURF.DrawString("Игрок:\nСчет:\nСтраховка:\nСоздано монополий:", 71, 3 + GetIndexInUsersList() * 9, LightGray);
	WINSURF.DrawUserName(GetIndexInUsersList(), 91, 3 + GetIndexInUsersList() * 9);
	sprintf(buf, "%i$", monetary_account_);
	WINSURF.DrawString(buf, 91, 4 + GetIndexInUsersList() * 9, LightGray);
	sprintf(buf, "%i", insurances_);
	WINSURF.DrawString(buf, 91, 5 + GetIndexInUsersList() * 9, LightGray);
	sprintf(buf, "%i", monopolies_);
	WINSURF.DrawString(buf, 91, 6 + GetIndexInUsersList() * 9, LightGray);
}

void User::ClearInfo()
{
	WINSURF.ClearRectangle(69, 1 + GetIndexInUsersList() * 9, 39, 8);
}

void User::SetActive(bool b)
{
	if(b) {
		Color foreground = GetColor();
		WINSURF.DrawRectangle(69, 1 + GetIndexInUsersList() * 9, 39, 8, foreground);
	}
	else
		WINSURF.DrawRectangle(69, 1 + GetIndexInUsersList() * 9, 39, 8, LightGray);
}

const char * User::GetName() const
{
	return name_;
}

bool User::IsComputer() const
{
	return is_computer_;
}

void User::SetColor(Color color)
{
	color_ = color;
}

Color User::GetColor() const
{
	return color_;
}

int User::GetPosition() const
{
	return position_on_map_;
}

int User::SetPosition(int new_pos)
{
	int i = position_on_map_;
	position_on_map_ = new_pos;
	return i;
}

int User::HowMuchMoney() const
{
	return monetary_account_;
}

void User::ReceiveMoney(int how_much)
{
	monetary_account_ += how_much;
	// Печатаем в Info новое значение.
	char buf[256];
	sprintf(buf, "%i$", monetary_account_);
	WINSURF.DrawString(buf, 91, 4 + GetIndexInUsersList() * 9, LightGray);
}

bool User::Payment(int is_required)
{
	if(monetary_account_ >= is_required) {
		monetary_account_ -= is_required;
		// Печатаем в Info новое значение.
		char buf[256];
		sprintf(buf, "%i$", monetary_account_);
		WINSURF.DrawString("       ", 91, 4 + GetIndexInUsersList() * 9, LightGray);
		WINSURF.DrawString(buf, 91, 4 + GetIndexInUsersList() * 9, LightGray);
		return true;
	}
	else
		// На счету недостаточно денег.
		return false;
}

int User::HowManyInsurances() const
{
	return insurances_;
}

void User::ReceiveInsurance()
{
	insurances_++;
	// Печатаем в Info новое значение.
	char buf[256];
	sprintf(buf, "%i", insurances_);
	WINSURF.DrawString(buf, 91, 5 + GetIndexInUsersList() * 9, LightGray);
}

void User::GiveInsurance()
{
	insurances_--;
	// Печатаем в Info новое значение.
	char buf[256];
	sprintf(buf, "%i", insurances_);
	WINSURF.DrawString("       ", 91, 5 + GetIndexInUsersList() * 9, LightGray);
	WINSURF.DrawString(buf, 91, 5 + GetIndexInUsersList() * 9, LightGray);
}

int User::GetMonopolies() const
{
	return monopolies_;
}

void User::IncMonopolies()
{
	monopolies_++;
	// Печатаем в Info новое значение.
	char buf[256];
	sprintf(buf, "%i", monopolies_);
	WINSURF.DrawString(buf, 91, 6 + GetIndexInUsersList() * 9, LightGray);
}

void User::DecMonopolies()
{
	monopolies_--;
	// Печатаем в Info новое значение.
	char buf[256];
	sprintf(buf, "%i", monopolies_);
	WINSURF.DrawString("       ", 91, 6 + GetIndexInUsersList() * 9, LightGray);
	WINSURF.DrawString(buf, 91, 6 + GetIndexInUsersList() * 9, LightGray);
}

int User::GetDoubles() const
{
	return doubles_;
}

void User::IncDoubles()
{
	doubles_++;
}

void User::ResetDoubles()
{
	doubles_ = 0;
}

int User::GetPasses() const
{
	return pass_;
}

void User::DecPasses()
{
	pass_--;
}

void User::ResetPasses()
{
	pass_ = 0;
}

void User::SetPasses()
{
	pass_ = 3;
}

bool User::Load(FILE *file)
{
	if (fread(&color_, sizeof(color_), 1, file) != 1)
		return false;
	if (fread(&position_on_map_, sizeof(position_on_map_), 1, file) != 1)
		return false;
	if (fread(&monetary_account_, sizeof(monetary_account_), 1, file) != 1)
		return false;
	if (fread(&insurances_, sizeof(insurances_), 1, file) != 1)
		return false;
	if (fread(&monopolies_, sizeof(monopolies_), 1, file) != 1)
		return false;
	if (fread(&doubles_, sizeof(doubles_), 1, file) != 1)
		return false;
	if (fread(&pass_, sizeof(pass_), 1, file) != 1)
		return false;

	return true;
}

bool User::Save(FILE *file)
{
	if (fwrite(&color_, sizeof(color_), 1, file) != 1)
		return false;
	if (fwrite(&position_on_map_, sizeof(position_on_map_), 1, file) != 1)
		return false;
	if (fwrite(&monetary_account_, sizeof(monetary_account_), 1, file) != 1)
		return false;
	if (fwrite(&insurances_, sizeof(insurances_), 1, file) != 1)
		return false;
	if (fwrite(&monopolies_, sizeof(monopolies_), 1, file) != 1)
		return false;
	if (fwrite(&doubles_, sizeof(doubles_), 1, file) != 1)
		return false;
	if (fwrite(&pass_, sizeof(pass_), 1, file) != 1)
		return false;

	return true;
}

/////////////////////////////////////////////////

UserList::UserList()
	: list_(0), count_(0)
{
}

UserList::~UserList()
{
	DeleteAllUsers();
}

UserList &UserList::instance()
{
	static UserList single_instance;
	return single_instance;
}

int UserList::GetUsersCount() const
{
	return count_;
}

int UserList::AddUser(const char *name, bool is_computer)
{
	User *user = new User(name, is_computer);
	User **list = new User*[count_ + 1];
	for(int i = 0; i < count_; i++)
		list[i] = list_[i];
	list[count_] = user;
	delete[]list_;
	list_ = list;
	return ++count_;
}

void UserList::DeleteUser(int index)
{
	User **list = (count_ - 1) == 0 ? 0 : new User*[count_ - 1];
	for(int i = 0; i < count_; i++)
	{
		if(i < index) {
			list[i] = list_[i];
		}
		else if(i > index) {
			list[i - 1] = list_[i];
		}
		else {
			delete list_[i];
			list_[i] = 0;
		}
	}
	delete[]list_;
	list_ = list;
	count_--;
}

void UserList::DeleteAllUsers()
{
	for(int i = 0; i < count_; i++)
	{
		delete list_[i];
		list_[i] = 0;
	}

	delete[]list_;
	count_ = 0;
	list_ = 0;
}

User * UserList::GetUser(int index) const
{
	return list_[index];
}

bool UserList::Load(FILE *file)
{
	DeleteAllUsers();
	int count;
	if (fread(&count, sizeof(count), 1, file) != 1)
		return false;
	for(int i = 0; i < count; i++)
	{
		int len;
		if (fread(&len, sizeof(len), 1, file) != 1)
			return false;
		char buf[256];
		if (fread(buf, sizeof(char), len, file) != len)
			return false;
		bool b;
		if (fread(&b, sizeof(bool), 1, file) != 1)
			return false;
		AddUser(buf, b);
		if (!list_[i]->Load(file))
			return false;
	}
	return true;
}

bool UserList::Save(FILE *file)
{
	if (fwrite(&count_, sizeof(count_), 1, file) != 1)
		return false;
	for(int i = 0; i < count_; i++)
	{
		int len = strlen(list_[i]->GetName()) + 1;
		if (fwrite(&len, sizeof(len), 1, file) != 1)
			return false;
		if (fwrite(list_[i]->GetName(), sizeof(char), len, file) != len)
			return false;
		bool b = list_[i]->IsComputer();
		if (fwrite(&b, sizeof(bool), 1, file) != 1)
			return false;
		if (!list_[i]->Save(file))
			return false;
	}
	return true;
}