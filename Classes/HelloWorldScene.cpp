#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;

CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                        "CloseNormal.png",
                                        "CloseSelected.png",
                                        this,
                                        menu_selector(HelloWorld::menuCloseCallback) );
    pCloseItem->setPosition( ccp(CCDirector::sharedDirector()->getWinSize().width - 20, 20) );

    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition( CCPointZero );
    this->addChild(pMenu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    CCLabelTTF* pLabel = CCLabelTTF::create("Hello World, 你好世界", "Thonburi", 34);

    // ask director the window size
    CCSize size = CCDirector::sharedDirector()->getWinSize();

    // position the label on the center of the screen
    pLabel->setPosition( ccp(size.width / 2, size.height - 20) );

    // add the label as a child to this layer
    this->addChild(pLabel, 1);

    // add "HelloWorld" splash screen"
    m_splash = CCSprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
    m_splash->setPosition( ccp(size.width/2, size.height/2) );

    // add the sprite as a child to this layer
    this->addChild(m_splash, 0);
    m_splash->setScale(0.5);


    updateAspectQuotient(
    		CCDirector::sharedDirector()->getWinSize().width,
    		CCDirector::sharedDirector()->getWinSize().height,
    		m_splash->getContentSize().width,
    		m_splash->getContentSize().height);
    updateBasicZoomControl();
    invalidate();

    this->setTouchEnabled(true);

    return true;
}

void HelloWorld::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void HelloWorld::registerWithTouchDispatcher()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addStandardDelegate(this, 0);
}

void HelloWorld::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent)
{
//    CCSetIterator iter = pTouches->begin();
//    for (; iter != pTouches->end(); iter++)
//    {
//        CCTouch* pTouch = (CCTouch*)(*iter);
//        CCPoint location = pTouch->getLocation();
//        m_splash->setPosition(location);
//    }


	CCSetIterator iter = pTouches->begin();
    if (pTouches->count() >= 1)
    {
    	float x0 = ((CCTouch*)(*iter))->getLocation().x;
    	float y0 = ((CCTouch*)(*iter))->getLocation().y;
    	mDownX = x0;
    	mDownY = y0;
    	mX = x0;
    	mY = y0;
		if (pTouches->count() == 2)
		{
			iter++;
	    	float x1 = ((CCTouch*)(*iter))->getLocation().x;
	    	float y1 = ((CCTouch*)(*iter))->getLocation().y;
			mCount = 2;
    		float x_ = (x0 - x1) / CCDirector::sharedDirector()->getWinSize().width;
			float y_ = (y0 - y1) / CCDirector::sharedDirector()->getWinSize().height;
			mDownS = (float) sqrt(x_ * x_ + y_ * y_);
			mDownSX = (x0 + x1) / 2;
			mDownSY = (y0 + y1) / 2;
		}
    }
}

void HelloWorld::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent)
{
//    CCSetIterator iter = pTouches->begin();
//    for (; iter != pTouches->end(); iter++)
//    {
//        CCTouch* pTouch = (CCTouch*)(*iter);
//        CCPoint location = pTouch->getLocation();
//
//        m_splash->setPosition(location);
//    }


	CCSetIterator iter = pTouches->begin();
    if (pTouches->count() >= 1)
    {
    	float x0 = ((CCTouch*)(*iter))->getLocation().x;
    	float y0 = ((CCTouch*)(*iter))->getLocation().y;
		float dx = (x0 - mX) / CCDirector::sharedDirector()->getWinSize().width;
		float dy = (y0 - mY) / CCDirector::sharedDirector()->getWinSize().height;
		{
			switch(pTouches->count())
			{
			case 2:
				{
					iter++;
					float x1 = ((CCTouch*)(*iter))->getLocation().x;
					float y1 = ((CCTouch*)(*iter))->getLocation().y;
					float x_ = (x0 - x1) / CCDirector::sharedDirector()->getWinSize().width;
					float y_ = (y0 - y1) / CCDirector::sharedDirector()->getWinSize().height;
					float s_ = (float) sqrt(x_ * x_ + y_ * y_);
					if (mDownS == 0 || mCount != 2)
					{
						mDownS = s_;
						mDownSX = (x0 + x1) / 2;
						mDownSY = (y0 + y1) / 2;
					}
					mCount = 2;
					float ds = mDownS - s_;
					zoom((float)pow(20, -ds),
						mDownSX / CCDirector::sharedDirector()->getWinSize().width,
						mDownSY / CCDirector::sharedDirector()->getWinSize().height);
					mDownS = s_;
				}
				break;

			case 1:
				{
					bool enablePan = true;
					if (mCount != 1)
					{
						enablePan = false;
					}
					mCount = 1;
					if (enablePan)
					{
						pan(-dx, -dy);
					}
				}
				break;

			default:
				mCount = 0;
				break;
			}
		}
		mX = x0;
		mY = y0;
    }
}

void HelloWorld::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent)
{
//    CCSetIterator iter = pTouches->begin();
//    for (; iter != pTouches->end(); iter++)
//    {
//        CCTouch* pTouch = (CCTouch*)(*iter);
//        CCPoint location = pTouch->getLocation();
//        m_splash->setPosition(location);
//    }
	mDownS = 0;
	mCount = 0;
}

void HelloWorld::ccTouchesCancelled(CCSet *pTouches, CCEvent *pEvent)
{
    ccTouchesEnded(pTouches, pEvent);
}


void HelloWorld::zoom(float f, float x, float y) {
	float prevZoomX = getZoomX(m_aspectQuotient);
	float prevZoomY = getZoomY(m_aspectQuotient);
	setZoom(m_zoom * f);
	limitZoom();
	float newZoomX = getZoomX(m_aspectQuotient);
	float newZoomY = getZoomY(m_aspectQuotient);
	setPanX(m_panX + (x - .5f) * (1.0f / prevZoomX - 1.0f / newZoomX));
	setPanY(m_panY + (y - .5f) * (1.0f / prevZoomY - 1.0f / newZoomY));
	limitPan();
	invalidate();
}

void HelloWorld::pan(float dx, float dy)
{
	setPanX(m_panX + dx / getZoomX(m_aspectQuotient));
	setPanY(m_panY + dy / getZoomY(m_aspectQuotient));
	limitPan();
	invalidate();
}

float HelloWorld::getMaxPanDelta(float zoom)
{
	return MAX(0.0f, .5f * ((zoom - 1) / zoom));
}

void HelloWorld::limitZoom() {
	if (m_zoom < MIN_ZOOM) {
		setZoom(MIN_ZOOM);
	} else if (m_zoom > MAX_ZOOM) {
		setZoom(MAX_ZOOM);
	}
}

void HelloWorld::limitPan() {
	float zoomX = getZoomX(m_aspectQuotient);
	float zoomY = getZoomY(m_aspectQuotient);
	float panMinX = .5f - getMaxPanDelta(zoomX);
	float panMaxX = .5f + getMaxPanDelta(zoomX);
	float panMinY = .5f - getMaxPanDelta(zoomY);
	float panMaxY = .5f + getMaxPanDelta(zoomY);
	if (m_panX < panMinX) {
		setPanX(panMinX);
	}
	if (m_panX > panMaxX) {
		setPanX(panMaxX);
	}
	if (m_panY < panMinY) {
		setPanY(panMinY);
	}
	if (m_panY > panMaxY) {
		setPanY(panMaxY);
	}
}

void HelloWorld::updateBasicZoomControl() {
	limitZoom();
	limitPan();
}

void HelloWorld::setPanX(float panX)
{
	if (panX != m_panX)
	{
		m_panX = panX;
		invalidate();
	}
}

float HelloWorld::getPanX(void)
{
	return m_panX;
}

void HelloWorld::setPanY(float panY)
{
	if (panY != m_panY)
	{
		m_panY = panY;
		invalidate();
	}
}

float HelloWorld::getPanY(void)
{
	return m_panY;
}

void HelloWorld::setZoom(float zoom)
{
	if (zoom != m_zoom)
	{
		m_zoom = zoom;
		invalidate();
	}
}

float HelloWorld::getZoom(void)
{
	return m_zoom;
}

float HelloWorld::getZoomX(float aspectQuotient)
{
	return MIN(m_zoom, m_zoom * aspectQuotient);
}

float HelloWorld::getZoomY(float aspectQuotient)
{
	return MIN(m_zoom, m_zoom / aspectQuotient);
}

void HelloWorld::updateAspectQuotient(float viewWidth, float viewHeight, float contentWidth, float contentHeight)
{
	float aspectQuotient = (contentWidth / contentHeight) / (viewWidth / viewHeight);
	if (aspectQuotient != m_aspectQuotient)
	{
		m_aspectQuotient = aspectQuotient;
		updateBasicZoomControl();
	}
}

void HelloWorld::invalidate(void)
{
    int viewWidth = CCDirector::sharedDirector()->getWinSize().width;
    int viewHeight = CCDirector::sharedDirector()->getWinSize().height;
    int bitmapWidth = m_splash->getContentSize().width;
    int bitmapHeight = m_splash->getContentSize().height;
    float panX = m_panX;
    float panY = m_panY;
    float zoomX = getZoomX(m_aspectQuotient) * viewWidth / bitmapWidth;
    float zoomY = getZoomY(m_aspectQuotient) * viewHeight / bitmapHeight;

    m_splash->setScale(zoomX);
    m_splash->setPosition(ccp(
    	viewWidth * 0.5 - bitmapWidth * (panX - 0.5) * zoomX,
    	viewHeight * 0.5 - bitmapHeight * (panY - 0.5) * zoomY
    ));
}
