#include "space.h"

bool SiteSpace::Save(FILE *file)
{
	if (fwrite(&owner, sizeof(owner), 1, file) != 1)
		return false;
	if (fwrite(&buildings, sizeof(buildings), 1, file) != 1)
		return false;
	return true;
}

bool SiteSpace::Load(FILE *file)
{
	if (fread(&owner, sizeof(owner), 1, file) != 1)
		return false;
	if (fread(&buildings, sizeof(buildings), 1, file) != 1)
		return false;
	return true;
}

bool ServiceSpace::Save(FILE *file)
{
	if (fwrite(&owner, sizeof(owner), 1, file) != 1)
		return false;
	return true;
}

bool ServiceSpace::Load(FILE *file)
{
	if (fread(&owner, sizeof(owner), 1, file) != 1)
		return false;
	return true;
}

bool CommunicationSpace::Save(FILE *file)
{
	if (fwrite(&owner, sizeof(owner), 1, file) != 1)
		return false;
	return true;
}

bool CommunicationSpace::Load(FILE *file)
{
	if (fread(&owner, sizeof(owner), 1, file) != 1)
		return false;
	return true;
}

///////////////////////////////////////////////////////////

bool Space::Load(FILE *file)
{
	if(type == Space::Site) {
		if(site.Load(file) == false)
			return false;
	}
	else if (type == Space::Service) {
		if(service.Load(file) == false)
			return false;
	}
	else if (type == Space::Communication) {
		if(communication.Load(file) == false)
			return false;
	}
	return true;
}

bool Space::Save(FILE *file)
{
	if(type == Space::Site) {
		if(site.Save(file) == false)
			return false;
	}
	else if (type == Space::Service) {
		if(service.Save(file) == false)
			return false;
	}
	else if (type == Space::Communication) {
		if(communication.Save(file) == false)
			return false;
	}
	return true;
}