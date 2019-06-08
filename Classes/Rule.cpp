#include "Rule.h"
#include "cocos2d.h"

static const char data_name[] = "savedata.dat";
static bool data_loaded = false;


Rule::Rule()
{
	room = 0;
}


Rule::~Rule()
{
}

void Rule::ReadData()
{
	if (data_loaded)
		return;
	data_loaded = true;
	auto fu = cocos2d::FileUtils::getInstance();
	auto data = fu->getDataFromFile(fu->getWritablePath() + data_name);
	if (!data.isNull())
	{
		int i = 0;
		for (; i < 10; i++)
			memcpy(highestscore + i, data.getBytes() + i * sizeof(int), sizeof(int));
		memcpy(&speed, data.getBytes() + i * sizeof(int), sizeof(int));
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
	cocos2d::Data data;
	int buf[11];
	int i = 0;
	for (; i < 10; i++)
		memcpy(buf + i, highestscore + i, sizeof(int));
	memcpy(buf + i, &speed, sizeof(int));
	data.copy((unsigned char*)buf, sizeof(buf));
	auto fu = cocos2d::FileUtils::getInstance();
	return fu->writeDataToFile(data, fu->getWritablePath() + data_name);
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