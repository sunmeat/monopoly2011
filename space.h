#ifndef SPACE_H_
#define SPACE_H_

#include <stdio.h>

//-----------------------------------------------------------
// ������� ��� ���������.

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
// ������ ����������: ��������, ��������������� ������.

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
// ������������: ��������� �����, ��������.

struct CommunicationSpace
{
	const char *name;
	int group;
	int owner;
	int cost;
	int rent; // �� ������� �������� ���� �� �������

	bool Load(FILE *file);
	bool Save(FILE *file);
};

//-----------------------------------------------------------
// ���� �������.

struct TaxationSpace
{
	const char *name;
	int rent;
};

//-----------------------------------------------------------
// ���� �� ������� �����.

struct Space
{
	enum Type
	{
		Site,						// ������� ��� ���������
		Service,				// ������ ����������
		Communication,	// ������������
		PublicTreasury,	// ������������ �����
		Chance,					// ����
		Taxation,				// ���� �������
		Start,					// ������
		FreeParking,		// ����������� �������
		GoToJail,				// ����������� � ������
		Jail						// ������
	};

	// ��� ��� �� ����?
	Type type;
	// �������� ����.
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
