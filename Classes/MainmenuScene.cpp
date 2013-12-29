#include "MainmenuScene.h"
#include "SimpleAudioEngine.h"
#include "GameScene.h"

using namespace cocos2d;
using namespace CocosDenshion;

CCScene* Mainmenu::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    Mainmenu *layer = Mainmenu::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool Mainmenu::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }

    /////////////////////////////

    this->setKeypadEnabled(true);

    m_black_button = CCMenuItemImage::create(
         "mainmenu_black.png", "mainmenu_black.png",
         this, menu_selector(Mainmenu::menuBlackCallback) );
    m_black_button->setPosition(ccp(176, 320 - 63));

    m_white_button = CCMenuItemImage::create(
         "mainmenu_white.png", "mainmenu_white.png",
         this, menu_selector(Mainmenu::menuWhiteCallback) );
    m_white_button->setPosition(ccp(196, 320 - 134));

    m_exit_button = CCMenuItemImage::create(
         "mainmenu_exit.png", "mainmenu_exit.png",
         this, menu_selector(Mainmenu::menuExitCallback) );
    m_exit_button->setPosition(ccp(215, 320 - 208));

    CCMenu* pMenu = CCMenu::create(m_black_button, m_white_button, m_exit_button, NULL);
    pMenu->setPosition(CCPointZero);

    CCSize size = CCDirector::sharedDirector()->getWinSize();

    m_bg = CCSprite::create("mainmenu_bg.png");
    m_bg->setPosition(ccp(size.width / 2, size.height / 2));
    this->addChild(m_bg, 0);
    m_bg->setScale(1.0f);
    if (m_bg->getContentSize().width / m_bg->getContentSize().height <
    	size.width / size.height)
    {
    	m_bg->setScale(size.height / m_bg->getContentSize().height * 1);
    }
    else
    {
    	m_bg->setScale(size.width / m_bg->getContentSize().width * 1);
    }
    m_bg->addChild(pMenu, 1);

    return true;
}

void Mainmenu::menuExitCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void Mainmenu::keyBackClicked(void)
{
	CCLayer::keyBackClicked();

	CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void Mainmenu::keyMenuClicked(void)
{
	CCLayer::keyMenuClicked();
}

void Mainmenu::menuBlackCallback(CCObject* pSender)
{
	CCDirector::sharedDirector()->pushScene(GameLayer::scene(true));
	//CCDirector::sharedDirector()->replaceScene(CCTransitionTurnOffTiles::create(5, GameLayer::scene(true)));
}

void Mainmenu::menuWhiteCallback(CCObject* pSender)
{
	CCDirector::sharedDirector()->pushScene(GameLayer::scene(false));
	//CCDirector::sharedDirector()->replaceScene(CCTransitionTurnOffTiles::create(5, GameLayer::scene(false)));
}
