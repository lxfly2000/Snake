#include "Rule.h"
#include <fstream>

static const char data_name[] = "savedata.dat";


Rule::Rule()
{
	ReadData();
	room = 0;
}


Rule::~Rule()
{
}

void Rule::ReadData()
{
	std::ifstream save(data_name, std::ios_base::in | std::ios_base::binary);
	if (save)
	{
		for (int i = 0; i < 10; i++)
			save.read(reinterpret_cast<char*>(highestscore + i), sizeof(int));
		save.read(reinterpret_cast<char*>(&speed), sizeof(int));
		save.close();
	}
	else
	{
		for (int i = 0; i < 10; i++)
			highestscore[i] = 0;
		speed = 5;
	}
}

bool Rule::SaveData()
{
	std::ofstream save(data_name, std::ios_base::out | std::ios_base::binary);
	if (!save)
		return false;
	for (int i = 0; i < 10; i++)
		save.write(reinterpret_cast<char*>(highestscore + i), sizeof(int));
	save.write(reinterpret_cast<char*>(&speed), sizeof(int));
	save.close();
	return true;
}

void Rule::Reset()
{
	score = 0;
	lifes = 2;
	leftoneup = 0;
	oneupDelta = 1000;
	oneupScore = oneupDelta;
}

int Rule::GetOneup()
{
	int r = leftoneup;
	leftoneup = 0;
	return r;
}

void Rule::AddScore(int s)
{
	score += s;
	if (score >= oneupScore)
	{
		leftoneup = (score - oneupScore) / oneupDelta + 1;
		oneupScore += leftoneup * oneupDelta;
	}
}

Rule SnakeRule;