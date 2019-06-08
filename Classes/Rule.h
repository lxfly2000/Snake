#pragma once
class Rule
{
public:
	Rule();
	virtual ~Rule();
	void ReadData();
	//成功保存返回 1, 否则返回 0
	bool SaveData();
	int room;
	int score;
	int lifes;
	int highestscore[10];
	unsigned speed;
	void Reset();
	int GetOneup();
	void AddScore(int s);
private:
	int oneupDelta;
	int oneupScore;
	int leftoneup;
};

