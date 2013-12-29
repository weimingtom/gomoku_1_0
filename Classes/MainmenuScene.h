#ifndef __DEMO_SCENE_H__
#define __DEMO_SCENE_H__

#include "cocos2d.h"

class Mainmenu : public cocos2d::CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
    static cocos2d::CCScene* scene();

    void menuExitCallback(CCObject* pSender);
    void menuBlackCallback(CCObject* pSender);
    void menuWhiteCallback(CCObject* pSender);
    
    virtual void keyBackClicked(void);
    virtual void keyMenuClicked(void);

    // implement the "static node()" method manually
    CREATE_FUNC(Mainmenu);

private:
	cocos2d::CCSprite *m_bg;

	cocos2d::CCMenuItemImage *m_black_button;
	cocos2d::CCMenuItemImage *m_white_button;
	cocos2d::CCMenuItemImage *m_exit_button;
};

#endif // __DEMO_SCENE_H__
