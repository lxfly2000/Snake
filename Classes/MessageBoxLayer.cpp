#include "MessageBoxLayer.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

static const char* s_msg, * s_font;
static int s_fontsize;
static cocos2d::EventKeyboard::KeyCode s_keyOk;
static TextHAlignment s_align;

Layer* MessageBoxLayer::createScene(Node* parent,const char* msg, const char* font, int fontsize,
	TextHAlignment align,EventKeyboard::KeyCode keyOk)
{
	if (parent)
		parent->pause();
	s_msg = msg;
	s_font = font;
	s_fontsize = fontsize;
	s_keyOk = keyOk;
	s_align = align;
	return create();
}

Layer* MessageBoxLayer::createScene(Node* parent, const char* msg, const char* font, int fontsize,
	TextHAlignment align)
{
	return createScene(parent, msg, font, fontsize, align, EventKeyboard::KeyCode::KEY_ENTER);
}

Layer* MessageBoxLayer::createScene(Node* parent, const char* msg, const char* font, int fontsize)
{
	return createScene(parent,msg,font,fontsize,TextHAlignment::LEFT,EventKeyboard::KeyCode::KEY_ENTER);
}

bool MessageBoxLayer::init()
{
	if (!Layer::init())
		return false;

	auto pauseLabel = Label::createWithSystemFont(s_msg, s_font, s_fontsize,Size::ZERO,TextHAlignment::CENTER);
	pauseLabel->setColor(Color3B::WHITE);
	auto screenSize = Director::getInstance()->getVisibleSize();
	auto screenOrigin = Director::getInstance()->getVisibleOrigin();
	auto pauseBg = ui::Scale9Sprite::create("Board.png");
	pauseBg->setInsetLeft(6);
	pauseBg->setInsetTop(6);
	pauseBg->setInsetRight(6);
	pauseBg->setInsetBottom(6);
	pauseBg->setPosition(Vec2(screenOrigin.x + screenSize.width / 2, screenOrigin.y + screenSize.height / 2));
	auto ws = Director::getInstance()->getVisibleSize();
	float pd = MIN(ws.width, ws.height) / 8;
	auto sz = pauseLabel->getContentSize();
	sz.width += pd;
	sz.height += pd;
	pauseBg->setContentSize(sz);
	pauseLabel->setPosition(pauseBg->getPosition());
	pauseLabel->setAlignment(s_align);
	addChild(pauseBg);
	addChild(pauseLabel);

	auto keyListener = EventListenerKeyboard::create();
	keyListener->onKeyPressed = CC_CALLBACK_2(MessageBoxLayer::onKeyPressed, this);
	getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyListener, this);
	return true;
}

void MessageBoxLayer::onKeyPressed(EventKeyboard::KeyCode key, Event* event)
{
	if (key == s_keyOk)
	{
		getParent()->resume();
		removeFromParentAndCleanup(true);
	}
}
