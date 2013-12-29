#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "game.h"

class GameLayer : public cocos2d::CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
    static cocos2d::CCScene* scene(bool isBlackStart);
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);

    void menuLeftCallback(CCObject* pSender);
    void menuRightCallback(CCObject* pSender);
    void menuUpCallback(CCObject* pSender);
    void menuDownCallback(CCObject* pSender);
    void menuOkCallback(CCObject* pSender);
    void menuBlackStartCallback(CCObject* pSender);
    void menuWhiteStartCallback(CCObject* pSender);

    virtual void keyBackClicked(void);
    virtual void keyMenuClicked(void);

    virtual void registerWithTouchDispatcher(void);
    virtual void ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);

    // implement the "static node()" method manually
    CREATE_FUNC(GameLayer);

private:
	cocos2d::CCSprite *m_board;
	cocos2d::CCSprite *m_black_piece[15][15];
	cocos2d::CCSprite *m_white_piece[15][15];
	cocos2d::CCSprite *m_select_piece;
	cocos2d::CCSprite *m_game_draw;
	cocos2d::CCSprite *m_game_white;
	cocos2d::CCSprite *m_game_black;

	cocos2d::CCMenuItemImage *m_start_black_button;
	cocos2d::CCMenuItemImage *m_start_white_button;
	cocos2d::CCMenuItemImage *m_up_button;
	cocos2d::CCMenuItemImage *m_down_button;
	cocos2d::CCMenuItemImage *m_left_button;
	cocos2d::CCMenuItemImage *m_right_button;
	cocos2d::CCMenuItemImage *m_ok_button;

	int m_select_i, m_select_j;

	Game m_game;
private:
	void testBoard(void);
	void gameLoop(bool isPlayer);
	void startGame(bool isBlackStart);
};

#endif // __GAME_SCENE_H__
