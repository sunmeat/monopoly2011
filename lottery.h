#ifndef LOTTERY_H_
#define LOTTERY_H_

class Lottery
{
public:
	enum Card
	{
		Plus25,											// +25
		Plus50,											// +50
		Plus150,										// +150
		Plus250,										// +250
		Gift10,											// +10 �� ������� ������
		ToWinInALottery10,					// +10
		Inheritance100,							// +100
		CollectingRent100,					// +100
		ToWinInALottery100,					// +100
		BankMistake200,							// +200
		Minus50,										// -50
		Minus100,										// -100
		Penalty10,									// -10
		Penalty15,									// -15
		Penalty20,									// -20
		InsurancePayment50,					// -50
		DoctorServices50,						// -50
		DoctorServices100,					// -100
		CollectingOnStreetRepair,		// -40 �� ������ ���, -115 �� �����
		CollectingOnStreetRepair2,	// -25 �� ������ ���, -100 �� �����
		Insurance,									// +���������
		GoToStart,
		GoToStartPlus200,						// � +200
		GoToJail,
	};

	Lottery();

	Card GetCard();
	void SetCard(Card c);

	// ������������ ������;
	void Reshuffle();

private:
	int index_;
	Card list_[16];
};

#endif