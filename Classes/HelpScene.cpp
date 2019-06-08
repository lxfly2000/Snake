#include "HelpScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "TouchControllerLayer.h"

USING_NS_CC;

using namespace cocostudio::timeline;

Scene* HelpScene::createScene()
{
	return create();
}

// on "init" you need to initialize your instance
bool HelpScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Scene::init())
	{
		return false;
	}

	auto rootNode = CSLoader::createNode("HelpScene.csb");

	addChild(rootNode);

	auto returnEntry = rootNode->getChildByName("Text_Return");
	returnEntry->setColor(Color3B::YELLOW);
	auto keyListener = EventListenerKeyboard::create();
	keyListener->onKeyPressed = CC_CALLBACK_2(HelpScene::onKeyPressed, this);
	getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyListener, this);

	addChild(TouchControllerLayer::createScene());
	return true;
}

void HelpScene::onKeyPressed(EventKeyboard::KeyCode key, Event *event)
{
	switch (key)
	{
	case EventKeyboard::KeyCode::KEY_KP_ENTER:
	case EventKeyboard::KeyCode::KEY_ENTER:
	case EventKeyboard::KeyCode::KEY_T:
		Director::getInstance()->popScene();
		break;
	case EventKeyboard::KeyCode::KEY_ESCAPE:
		Director::getInstance()->end();
		break;
	default:
		break;
	}
}