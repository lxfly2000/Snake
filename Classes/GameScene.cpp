#include"SimpleAudioEngine.h"
#include"GameScene.h"
#include"cocostudio/CocoStudio.h"
#include"ui/CocosGUI.h"
#include"Rule.h"
#include"MessageBoxLayer.h"
#include"TouchControllerLayer.h"

USING_NS_CC;

using namespace cocostudio::timeline;

extern Rule SnakeRule;

Scene* GameScene::createScene()
{
	return create();
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Scene::init())
	{
		return false;
	}

	auto rootNode = CSLoader::createNode("GameScene.csb");

	addChild(rootNode);

	pointx[0] = 10; pointx[1] = 78; pointx[2] = 146;
	pointx[3] = 214; pointx[4] = 282; pointx[5] = 350;
	pointx[6] = 418; pointx[7] = 486; pointx[8] = 554;
	pointy[0] = 18; pointy[1] = 86; pointy[2] = 154;
	pointy[3] = 222; pointy[4] = 290; pointy[5] = 358;
	pointy[6] = 426; pointy[7] = 494; pointy[8] = 562;
	memset(isBody, 0, 81);

	SnakeRule.Reset();
	SnakeHead = static_cast<Sprite*>(rootNode->getChildByName("Head"));
	SnakeDir = RIGHT;
	FoodItem = static_cast<Sprite*>(rootNode->getChildByName("Food"));
	SpeedLabelInNode = static_cast<Label*>(rootNode->getChildByName("Text_Speed"));
	LifeLabelInNode = static_cast<Label*>(rootNode->getChildByName("Text_Lifes"));
	ScoreLabelInNode = static_cast<Label*>(rootNode->getChildByName("Text_Score"));
	HiScoreLabelInNode = static_cast<Label*>(rootNode->getChildByName("Text_HiScore"));
	SpeedLabelInNode->setOpacity(0);
	LifeLabelInNode->setOpacity(0);
	ScoreLabelInNode->setOpacity(0);
	HiScoreLabelInNode->setOpacity(0);
	sprintf(SpeedStr, "速度：%5d", SnakeRule.speed);
	sprintf(LifeStr, "生命：%5d", SnakeRule.lifes);
	sprintf(ScoreStr, "分数：%5d", SnakeRule.score);
	sprintf(HiScoreStr, SnakeRule.highestscore[SnakeRule.speed] < 1000 ?
		"最高分：%3d" : "最高分:%4d", SnakeRule.highestscore[SnakeRule.speed]);
	SpeedLabel = Label::createWithSystemFont(SpeedStr, "SimSun", 48);
	LifeLabel = Label::createWithSystemFont(LifeStr, "SimSun", 48);
	ScoreLabel = Label::createWithSystemFont(ScoreStr, "SimSun", 48);
	HiScoreLabel = Label::createWithSystemFont(HiScoreStr, "SimSun", 48);
	SpeedLabel->setAnchorPoint(Point::ZERO);
	LifeLabel->setAnchorPoint(Point::ZERO);
	ScoreLabel->setAnchorPoint(Point::ZERO);
	HiScoreLabel->setAnchorPoint(Point::ZERO);
	SpeedLabel->setPosition(SpeedLabelInNode->getPosition());
	LifeLabel->setPosition(LifeLabelInNode->getPosition());
	ScoreLabel->setPosition(ScoreLabelInNode->getPosition());
	HiScoreLabel->setPosition(HiScoreLabelInNode->getPosition());
	addChild(SpeedLabel);
	addChild(LifeLabel);
	addChild(ScoreLabel);
	addChild(HiScoreLabel);
	addChild(TouchControllerLayer::createScene());

	auto keyListener = EventListenerKeyboard::create();
	keyListener->onKeyPressed = CC_CALLBACK_2(GameScene::onKeyPressed, this);
	getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyListener, this);
	this->schedule(schedule_selector(GameScene::snakeAction), 1.0f-SnakeRule.speed/10.0f);
	return true;
}

void GameScene::onKeyPressed(EventKeyboard::KeyCode key, Event *event)
{
	switch (key)
	{
	case EventKeyboard::KeyCode::KEY_ESCAPE:
		Director::getInstance()->end();
		break;
	case EventKeyboard::KeyCode::KEY_R:
		Director::getInstance()->replaceScene(GameScene::createScene());
		break;
	case EventKeyboard::KeyCode::KEY_T:
		Director::getInstance()->popScene();
		break;
	case EventKeyboard::KeyCode::KEY_P:
		addChild(MessageBoxLayer::createScene(this,"暂停\n\n[Enter] 继续","SimSun",36,TextHAlignment::CENTER));
		break;
	case EventKeyboard::KeyCode::KEY_UP_ARROW:
		if (SnakeDir != DOWN)
			SnakeDir = UP;
		break;
	case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
		if (SnakeDir != UP)
			SnakeDir = DOWN;
		break;
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		if (SnakeDir != RIGHT)
			SnakeDir = LEFT;
		break;
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		if (SnakeDir != LEFT)
			SnakeDir = RIGHT;
		break;
	default:
		break;
	}
}

void GameScene::snakeAction(float t)
{
	if (isBody[static_cast<int>(SnakeHead->getPositionX() - 10) / 68]
		[static_cast<int>(SnakeHead->getPositionY() - 18) / 68])
		UpdateLives(-1);
	switch (SnakeDir)
	{
	case GameScene::UP:
		if (SnakeHead->getPositionY() == pointy[8])
		{
			UpdateLives(-1);
		}
		else
		{
			MoveBody(SnakeHead);
			SnakeHead->setPositionY(SnakeHead->getPositionY() + 68);
		}
		break;
	case GameScene::DOWN:
		if (SnakeHead->getPositionY() == pointy[0])
		{
			UpdateLives(-1);
		}
		else
		{
			MoveBody(SnakeHead);
			SnakeHead->setPositionY(SnakeHead->getPositionY() - 68);
		}
		break;
	case GameScene::LEFT:
		if (SnakeHead->getPositionX() == pointx[0])
		{
			UpdateLives(-1);
		}
		else
		{
			MoveBody(SnakeHead);
			SnakeHead->setPositionX(SnakeHead->getPositionX() - 68);
		}
		break;
	case GameScene::RIGHT:
		if (SnakeHead->getPositionX() == pointx[8])
		{
			UpdateLives(-1);
		}
		else
		{
			MoveBody(SnakeHead);
			SnakeHead->setPositionX(SnakeHead->getPositionX() + 68);
		}
		break;
	default:
		break;
	}
	EatFood();
}

void GameScene::EatFood()
{
	if (SnakeHead->getPosition() == FoodItem->getPosition())
	{
		SnakeRule.AddScore(100);
		FoodItem->setPosition(pointx[cocos2d::random() % 9], pointy[cocos2d::random() % 9]);
		auto body = Sprite::create("Body.png");
		body->setAnchorPoint(Point::ZERO);
		body->setPosition(SnakeHead->getPosition());
		SnakeBody.pushBack(body);
		addChild(body);
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("SE/food.wav");
	}
}

void GameScene::MoveBody(Sprite *snakehead)
{
	if (SnakeBody.size())
	{
		isBody[(int)(SnakeBody.at(SnakeBodyCursor)->getPositionX() - 10) / 68][(int)(SnakeBody.at(SnakeBodyCursor)->getPositionY() - 10) / 68] = false;
		SnakeBody.at(SnakeBodyCursor)->setPosition(snakehead->getPosition());
		isBody[(int)(SnakeBody.at(SnakeBodyCursor)->getPositionX() - 10) / 68][(int)(SnakeBody.at(SnakeBodyCursor)->getPositionY() - 10) / 68] = true;
		SnakeBodyCursor = (SnakeBodyCursor + 1) % SnakeBody.size();
	}
	SnakeRule.AddScore(1);
	sprintf(ScoreStr, "分数：%5d", SnakeRule.score);
	ScoreLabel->setString(ScoreStr);
	if (SnakeRule.score > SnakeRule.highestscore[SnakeRule.speed])
	{
		sprintf(HiScoreStr, SnakeRule.score < 1000 ?
			"最高分：%3d" : "最高分:%4d", SnakeRule.score);
		HiScoreLabel->setString(HiScoreStr);
	}
	UpdateLives(SnakeRule.GetOneup());
}

void GameScene::onEnterTransitionDidFinish()
{
	FoodItem->setPosition(pointx[cocos2d::random() % 9], pointy[cocos2d::random() % 9]);
	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("BGM/bgm_game.mp3", true);
}

void GameScene::GameOver()
{
	CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
	char info[240] = "";
	if (SnakeRule.score > SnakeRule.highestscore[SnakeRule.speed])
	{
		SnakeRule.highestscore[SnakeRule.speed] = SnakeRule.score;
		sprintf(info, "新记录！\n");
	}
	SnakeRule.SaveData();
	sprintf(info, "%s你的得分：%d\n\n速度 最高分",info, SnakeRule.score);
	for (int i = 0; i < 10; i++)
		sprintf(info, "%s\n   %d %6d", info, i, SnakeRule.highestscore[i]);
	strcat(info, "\n\n[Enter] 关闭");
	auto scoreScene = MessageBoxLayer::createScene(this, info, "SimSun", 24);
	addChild(scoreScene);
	scoreScene->setOnExitCallback([]() {Director::getInstance()->popScene(); });
}

void GameScene::UpdateLives(int add)
{
	if (add == 0)
		return;
	if (add < 0)
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("SE/fail.wav");
	SnakeRule.lifes += add;
	if (SnakeRule.lifes < 0)
	{
		GameOver();
		return;
	}
	sprintf(LifeStr, "生命：%5d", SnakeRule.lifes);
	LifeLabel->setString(LifeStr);
}