#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include"SimpleAudioEngine.h"
#include "TitleScene.h"
#include"HelpScene.h"
#include"GameScene.h"
#include"Rule.h"
#include"TouchControllerLayer.h"

USING_NS_CC;

using namespace cocostudio::timeline;

extern Rule SnakeRule;

Scene* TitleScene::createScene()
{
	return create();
}

// on "init" you need to initialize your instance
bool TitleScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Scene::init())
	{
		return false;
	}

	auto rootNode = CSLoader::createNode("Title.csb");

	addChild(rootNode);

	menuEntries[0] = static_cast<Label*>(rootNode->getChildByName("Text_Start"));
	menuEntries[1] = static_cast<Label*>(rootNode->getChildByName("Text_Help"));
	menuEntries[2] = static_cast<Label*>(rootNode->getChildByName("Text_Quit"));
	choosedEntry = 0;
	choosedMenu = 0;
	menuEntries[choosedEntry]->setColor(Color3B::YELLOW);
	sprintf(speedstr, "速度：<%d>", SnakeRule.speed);
	speedLabel = Label::createWithSystemFont(speedstr, "SimSun", 48);
	speedLabel->setPosition(menuEntries[0]->getPosition());
	speedLabel->setColor(Color3B::YELLOW);
	speedLabel->setString(speedstr);
	speedLabel->setName("Text_Speed");
	speedLabel->setOpacity(0);	//0x0为透明，0xFF为显示。
	addChild(speedLabel);
	addChild(TouchControllerLayer::createScene());
	auto keyListener = EventListenerKeyboard::create();
	keyListener->onKeyPressed = CC_CALLBACK_2(TitleScene::onKeyPressed, this);
	getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyListener, this);
	return true;
}

void TitleScene::onEnterTransitionDidFinish()
{
	if (SnakeRule.room != 1)
		CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("BGM/bgm_title.mp3");
	else
		SnakeRule.room = 0;
}

void TitleScene::onKeyPressed(EventKeyboard::KeyCode key, Event* event)
{
	Scene* nextScene;
	if (choosedMenu == 0)
		switch (key)
		{
		case EventKeyboard::KeyCode::KEY_KP_ENTER:case EventKeyboard::KeyCode::KEY_ENTER:
			switch (choosedEntry)
			{
			case 0:
				menuEntries[choosedEntry]->setOpacity(0);
				speedLabel->setOpacity(0xFF);
				choosedMenu = 1;
				break;
			case 1:
				SnakeRule.room = 1;
				nextScene = HelpScene::createScene();
				Director::getInstance()->pushScene(nextScene);
				break;
			case 2:
				Director::getInstance()->end();
				break;
			default:
				break;
			}
			break;
		case EventKeyboard::KeyCode::KEY_ESCAPE:
			Director::getInstance()->end();
			break;
		case EventKeyboard::KeyCode::KEY_UP_ARROW:
			menuEntries[choosedEntry]->setColor(Color3B::WHITE);
			choosedEntry = (choosedEntry + 2) % 3;
			menuEntries[choosedEntry]->setColor(Color3B::YELLOW);
			break;
		case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
			menuEntries[choosedEntry]->setColor(Color3B::WHITE);
			choosedEntry = (choosedEntry + 1) % 3;
			menuEntries[choosedEntry]->setColor(Color3B::YELLOW);
			break;
		default:
			break;
		}
	else
		switch (key)
		{
		case EventKeyboard::KeyCode::KEY_UP_ARROW:
			speedLabel->setOpacity(0);
			menuEntries[choosedEntry]->setOpacity(0xFF);
			choosedMenu = 0;
			menuEntries[choosedEntry]->setColor(Color3B::WHITE);
			choosedEntry = (choosedEntry + 2) % 3;
			menuEntries[choosedEntry]->setColor(Color3B::YELLOW);
			break;
		case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
			speedLabel->setOpacity(0);
			menuEntries[choosedEntry]->setOpacity(0xFF);
			choosedMenu = 0;
			menuEntries[choosedEntry]->setColor(Color3B::WHITE);
			choosedEntry = (choosedEntry + 1) % 3;
			menuEntries[choosedEntry]->setColor(Color3B::YELLOW);
			break;
		case EventKeyboard::KeyCode::KEY_ESCAPE:
		case EventKeyboard::KeyCode::KEY_T:
			speedLabel->setOpacity(0);
			menuEntries[choosedEntry]->setOpacity(0xFF);
			choosedMenu = 0;
			break;
		case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
			SnakeRule.speed = (SnakeRule.speed + 9) % 10;
			sprintf(speedstr, "速度：<%d>", SnakeRule.speed);
			speedLabel->setString(speedstr);
			break;
		case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
			SnakeRule.speed = (SnakeRule.speed + 1) % 10;
			sprintf(speedstr, "速度：<%d>", SnakeRule.speed);
			speedLabel->setString(speedstr);
			break;
		case EventKeyboard::KeyCode::KEY_ENTER:
		case EventKeyboard::KeyCode::KEY_KP_ENTER:
			nextScene = GameScene::createScene();
			Director::getInstance()->pushScene(nextScene);
			break;
		default:
			break;
		}
}
