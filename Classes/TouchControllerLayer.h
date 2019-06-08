#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"

class TouchControllerLayer :public cocos2d::Layer
{
public:
	static cocos2d::Layer* createScene();
	static cocos2d::Layer* createScene(cocos2d::ui::Widget::ccWidgetClickCallback cb);
	static void SetLayerOpacity(GLubyte o);

	virtual bool init()override;

	CREATE_FUNC(TouchControllerLayer);

	void SetArrowsPosition(cocos2d::Vec2 cpos);
	cocos2d::Vec2 GetArrowsPosition();
	void SetFireButtonsPosition(cocos2d::Vec2 cpos);
	cocos2d::Vec2 GetFireButtonsPosition();
private:
	static void SetAllChildsOpacity(cocos2d::Node* node, GLubyte o);
};