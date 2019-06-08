#pragma once
#include "cocos2d.h"

class MessageBoxLayer : public cocos2d::Layer
{
public:
	static cocos2d::Layer* createScene(cocos2d::Node* parent,const char* msg,const char* font,int fontsize,
		cocos2d::TextHAlignment align,cocos2d::EventKeyboard::KeyCode keyOk);
	static cocos2d::Layer* createScene(cocos2d::Node* parent, const char* msg, const char* font, int fontsize,
		cocos2d::TextHAlignment align);
	static cocos2d::Layer* createScene(cocos2d::Node* parent, const char* msg, const char* font, int fontsize);

	virtual bool init()override;

	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);

	// implement the "static create()" method manually
	CREATE_FUNC(MessageBoxLayer);

private:
	void onKeyPressed(cocos2d::EventKeyboard::KeyCode, cocos2d::Event*);
};
