#ifndef SPACE_H_
#define SPACE_H_

#include <stdio.h>

//-----------------------------------------------------------
// Участок под застройку.

struct SiteSpace
{
	const char *street;
	int group;
	int owner;
	int cost;
	int rent0, rent1, rent2, rent3, rent4, rent5;
	int cost_building;
	int buildings;

	bool Load(FILE *file);
	bool Save(FILE *file);
};

//-----------------------------------------------------------
// Услуги транспорта: аэропорт, железнодорожный вокзал.

struct ServiceSpace
{
	const char *name;
	int group;
	int owner;
	int cost;
	int rent;

	bool Load(FILE *file);
	bool Save(FILE *file);
};

//-----------------------------------------------------------
// Коммуникации: мобильная связь, интернет.

struct CommunicationSpace
{
	const char *name;
	int group;
	int owner;
	int cost;
	int rent; // на сколько умножить очки на кубиках

	bool Load(FILE *file);
	bool Save(FILE *file);
};

//-----------------------------------------------------------
// Сбор налогов.

struct TaxationSpace
{
	const char *name;
	int rent;
};

//-----------------------------------------------------------
// Поле на игровой карте.

struct Space
{
	enum Type
	{
		Site,						// участок под застройку
		Service,				// услуги транспорта
		Communication,	// коммуникации
		PublicTreasury,	// общественная казна
		Chance,					// шанс
		Taxation,				// сбор налогов
		Start,					// вперед
		FreeParking,		// беспплатная стоянка
		GoToJail,				// отправляйся в тюрьму
		Jail						// тюрьма
	};

	// Что это за поле?
	Type type;
	// Карточка поля.
	union
	{
		SiteSpace site;
		ServiceSpace service;
		CommunicationSpace communication;
		TaxationSpace taxation;
	};

	bool Load(FILE *file);
	bool Save(FILE *file);
};

#endif
