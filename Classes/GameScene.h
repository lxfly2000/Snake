#pragma once
#include"cocos2d.h"

USING_NS_CC;

class GameScene:public cocos2d::Scene
{
public:
	static cocos2d::Scene *createScene();

	virtual bool init();

	CREATE_FUNC(GameScene);

	void onEnterTransitionDidFinish();
private:
	int pointx[9], pointy[9];
	bool isBody[9][9];
	void snakeAction(float);
	void GameOver();
	void UpdateLives(int add);
	void EatFood();

	void onKeyPressed(EventKeyboard::KeyCode, Event*);
	Vector<Sprite*> SnakeBody;
	int SnakeBodyCursor=0;
	Sprite *SnakeHead;
	Sprite *FoodItem;
	Label *SpeedLabel, *LifeLabel, *ScoreLabel, *HiScoreLabel,
		*SpeedLabelInNode, *LifeLabelInNode, *ScoreLabelInNode, *HiScoreLabelInNode;
	char SpeedStr[20], LifeStr[20], ScoreStr[20], HiScoreStr[20];
	void MoveBody(cocos2d::Sprite*);	//向头部移动
	enum Directions{ UP, DOWN, LEFT, RIGHT } SnakeDir;
};

