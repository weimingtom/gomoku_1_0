#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class HelloWorld : public cocos2d::CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);

    virtual void registerWithTouchDispatcher(void);

    virtual void ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
    virtual void ccTouchesMoved(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
    virtual void ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
    virtual void ccTouchesCancelled(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);

    void zoom(float f, float x, float y);
    void pan(float dx, float dy);
    float getMaxPanDelta(float zoom);
    void limitZoom();
    void limitPan();
    void updateBasicZoomControl();

    void setPanX(float panX);
    float getPanX(void);
    void setPanY(float panY);
    float getPanY();

    void setZoom(float zoom);
    float getZoom(void);
    float getZoomX(float aspectQuotient);
    float getZoomY(float aspectQuotient);

    void updateAspectQuotient(float viewWidth, float viewHeight, float contentWidth, float contentHeight);

    void invalidate(void);

    // implement the "static node()" method manually
    CREATE_FUNC(HelloWorld);

private:
	cocos2d::CCSprite* m_splash;

	float m_aspectQuotient;
	float m_zoom;
	float m_panX;
	float m_panY;

	enum {
		MIN_ZOOM = 1,
		MAX_ZOOM = 16,
	};

	float mX;
	float mY;
	float mDownX;
	float mDownY;
	float mDownS;
	float mCount;
	float mDownSX;
	float mDownSY;
};

#endif // __HELLOWORLD_SCENE_H__
