#pragma once
#define BITESET_8_SIZE 8 * 1

enum eBIT_KEY
{
	E_BIT_NONE = -1
	, E_BIT_LEFT = 0
	, E_BIT_RIGHT
	, E_BIT_UP
	, E_BIT_DOWN
	, E_BIT_FLIP
	, E_BIT_REPOS
	, E_BIT_ITEM
	, E_BIT_07
	, E_BIT_08
};


class cPlayerData
{
public:
	cPlayerData();
	~cPlayerData();

	cPlayerData(std::string IP, std::string ID, std::string CAR_NAME, bool IsAI);
public:
	bool IsAI;

	std::string IP;
	std::string ID;

	std::string CAR_NAME;
	std::bitset<BITESET_8_SIZE> INPUT_KEY;

	//0~11
	int ITEM_ID;
};

