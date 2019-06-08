#pragma once
#include "cocos2d.h"

USING_NS_CC;

class TitleScene :public cocos2d::Scene
{
public:
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	// implement the "static create()" method manually
	CREATE_FUNC(TitleScene);

	void onEnterTransitionDidFinish();
private:
	//void End();
	void onKeyPressed(EventKeyboard::KeyCode, Event*);
	Label* menuEntries[3];
	Label* speedLabel;
	char speedstr[20];
	int choosedEntry;
	int choosedMenu;
};

