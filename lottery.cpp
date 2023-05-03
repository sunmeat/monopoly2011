#include "lottery.h"
#include <stdlib.h>

Lottery::Lottery()
	: index_(0)
{
}

Lottery::Card Lottery::GetCard()
{
	int i = index_;
	index_++;
	if (index_ > 15)
		index_ = 0;
	return list_[i];
}

void Lottery::SetCard(Lottery::Card c)
{
	list_[index_++] = c;
}

void Lottery::Reshuffle()
{
	index_ = 0;
	for (int i = 0; i < 250; i++)
	{
		int x, y;
		x = rand() % 16;
		while ((y = rand() % 16) == x);
		Card temp = list_[x];
		list_[x] = list_[y];
		list_[y] = temp;
	}
}