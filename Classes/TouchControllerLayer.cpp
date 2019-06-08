#include "TouchControllerLayer.h"

USING_NS_CC;

static ui::Widget::ccWidgetTouchCallback s_cb;
static Vector<TouchControllerLayer*>layers;

Layer* TouchControllerLayer::createScene()
{
	return createScene([](Ref* sender, ui::Widget::TouchEventType type)
		{
			if (type == ui::Widget::TouchEventType::BEGAN)
			{
				std::string name = ((ui::Button*)sender)->getName();
				Node* scene = ((Node*)sender)->getScene();
				if (name.compare("btnLeft") == 0)
					scene->getEventDispatcher()->dispatchEvent(new EventKeyboard(EventKeyboard::KeyCode::KEY_LEFT_ARROW, true));
				else if (name.compare("btnTop") == 0)
					scene->getEventDispatcher()->dispatchEvent(new EventKeyboard(EventKeyboard::KeyCode::KEY_UP_ARROW, true));
				else if (name.compare("btnRight") == 0)
					scene->getEventDispatcher()->dispatchEvent(new EventKeyboard(EventKeyboard::KeyCode::KEY_RIGHT_ARROW, true));
				else if (name.compare("btnBottom") == 0)
					scene->getEventDispatcher()->dispatchEvent(new EventKeyboard(EventKeyboard::KeyCode::KEY_DOWN_ARROW, true));
				else if (name.compare("btnFire") == 0)
					scene->getEventDispatcher()->dispatchEvent(new EventKeyboard(EventKeyboard::KeyCode::KEY_ENTER, true));
			}
		});
}

Layer* TouchControllerLayer::createScene(ui::Widget::ccWidgetTouchCallback cb)
{
	s_cb = cb;
	auto layer = create();
	layers.pushBack(layer);
	return layer;
}

void TouchControllerLayer::SetLayerOpacity(GLubyte o)
{
	for (size_t i = 0; i < layers.size(); i++)
	{
		if (layers.at(i)->getReferenceCount() <= 0)
			layers.erase(i);
		SetAllChildsOpacity(layers.at(i), o);
	}
}

void TouchControllerLayer::SetAllChildsOpacity(Node* node, GLubyte o)
{
	node->setOpacity(o);
	for (auto c : node->getChildren())
		SetAllChildsOpacity(c, o);
}

bool TouchControllerLayer::init()
{
	if (!Layer::init())
		return false;

	setZOrder(1);

	auto spL0 = new SpriteFrame;
	spL0->initWithTextureFilename("Arrows.png", Rect(0, 0, 160, 160));
	SpriteFrameCache::sharedSpriteFrameCache()->addSpriteFrame(spL0, "ArrowsL0");
	auto spT0 = new SpriteFrame;
	spT0->initWithTextureFilename("Arrows.png", Rect(160, 0, 160, 160));
	SpriteFrameCache::sharedSpriteFrameCache()->addSpriteFrame(spT0, "ArrowsT0");
	auto spR0 = new SpriteFrame;
	spR0->initWithTextureFilename("Arrows.png", Rect(320, 0, 160, 160));
	SpriteFrameCache::sharedSpriteFrameCache()->addSpriteFrame(spR0, "ArrowsR0");
	auto spB0 = new SpriteFrame;
	spB0->initWithTextureFilename("Arrows.png", Rect(480, 0, 160, 160));
	SpriteFrameCache::sharedSpriteFrameCache()->addSpriteFrame(spB0, "ArrowsB0");
	auto spL1 = new SpriteFrame;
	spL1->initWithTextureFilename("Arrows.png", Rect(0, 160, 160, 160));
	SpriteFrameCache::sharedSpriteFrameCache()->addSpriteFrame(spL1, "ArrowsL1");
	auto spT1 = new SpriteFrame;
	spT1->initWithTextureFilename("Arrows.png", Rect(160, 160, 160, 160));
	SpriteFrameCache::sharedSpriteFrameCache()->addSpriteFrame(spT1, "ArrowsT1");
	auto spR1 = new SpriteFrame;
	spR1->initWithTextureFilename("Arrows.png", Rect(320, 160, 160, 160));
	SpriteFrameCache::sharedSpriteFrameCache()->addSpriteFrame(spR1, "ArrowsR1");
	auto spB1 = new SpriteFrame;
	spB1->initWithTextureFilename("Arrows.png", Rect(480, 160, 160, 160));
	SpriteFrameCache::sharedSpriteFrameCache()->addSpriteFrame(spB1, "ArrowsB1");
	auto spFire0 = new SpriteFrame;
	spFire0->initWithTextureFilename("Arrows.png", Rect(640, 0, 160, 160));
	SpriteFrameCache::sharedSpriteFrameCache()->addSpriteFrame(spFire0, "Fire0");
	auto spFire1 = new SpriteFrame;
	spFire1->initWithTextureFilename("Arrows.png", Rect(640, 160, 160, 160));
	SpriteFrameCache::sharedSpriteFrameCache()->addSpriteFrame(spFire1, "Fire1");

	auto btnLeft = ui::Button::create("ArrowsL0", "ArrowsL1", "", ui::Widget::TextureResType::PLIST);
	auto btnTop = ui::Button::create("ArrowsT0", "ArrowsT1", "", ui::Widget::TextureResType::PLIST);
	auto btnRight = ui::Button::create("ArrowsR0", "ArrowsR1", "", ui::Widget::TextureResType::PLIST);
	auto btnBottom = ui::Button::create("ArrowsB0", "ArrowsB1", "", ui::Widget::TextureResType::PLIST);
	
	auto btnFire = ui::Button::create("Fire0", "Fire1", "", ui::Widget::TextureResType::PLIST);

	btnLeft->setName("btnLeft");
	btnTop->setName("btnTop");
	btnRight->setName("btnRight");
	btnBottom->setName("btnBottom");
	btnFire->setName("btnFire");

	auto spArrows = Sprite::create();
	spArrows->setName("spArrows");
	spArrows->addChild(btnLeft);
	spArrows->addChild(btnTop);
	spArrows->addChild(btnRight);
	spArrows->addChild(btnBottom);

	btnLeft->setPosition(Vec2(-btnLeft->getContentSize().width, 0));
	btnTop->setPosition(Vec2(0, btnTop->getContentSize().height));
	btnRight->setPosition(Vec2(btnRight->getContentSize().width, 0));
	btnBottom->setPosition(Vec2(0, -btnBottom->getContentSize().height));

	btnLeft->addTouchEventListener(s_cb);
	btnTop->addTouchEventListener(s_cb);
	btnRight->addTouchEventListener(s_cb);
	btnBottom->addTouchEventListener(s_cb);

	btnFire->addTouchEventListener(s_cb);

	addChild(spArrows);
	addChild(btnFire);

	spArrows->setScale(Director::getInstance()->getVisibleSize().height / (btnLeft->getContentSize().height * 3) / 2);
	btnFire->setScale(Director::getInstance()->getVisibleSize().height / btnFire->getContentSize().height / 4);

	SetArrowsPosition(btnLeft->getContentSize()*spArrows->getScale()*1.5);
	SetFireButtonsPosition(Vec2(Director::getInstance()->getVisibleSize().width - btnFire->getContentSize().width*btnFire->getScale() / 2, btnFire->getContentSize().height*btnFire->getScale() / 2));

	if (layers.size())
		SetAllChildsOpacity(this, layers.at(0)->getOpacity());
	else
		SetAllChildsOpacity(this, 0);
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [](Touch* touch, Event* e)
	{
		Node* target = e->getCurrentTarget();
		if (touch->getLocation().y > Director::getInstance()->getVisibleSize().height / 2)
			SetLayerOpacity(target->getOpacity() ^ 0xFF);
		return true;
	};
	getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
	return true;
}

void TouchControllerLayer::SetArrowsPosition(Vec2 cpos)
{
	getChildByName("spArrows")->setPosition(cpos);
}

Vec2 TouchControllerLayer::GetArrowsPosition()
{
	return getChildByName("spArrows")->getPosition();
}

void TouchControllerLayer::SetFireButtonsPosition(Vec2 cpos)
{
	getChildByName("btnFire")->setPosition(cpos);
}

Vec2 TouchControllerLayer::GetFireButtonsPosition()
{
	return getChildByName("btnFire")->getPosition();
}
