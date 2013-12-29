#include "GameScene.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;

#define PIECE_POSITION(i, j)  ccp((102.0f + (((378.0f - 102.0f) / 14) * (i))), (320.0f - (22.0f + (((298.0f - 22.0f) / 14) * (j)))))

CCScene* GameLayer::scene(bool isBlackStart)
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    GameLayer *layer = GameLayer::create();
    layer->startGame(isBlackStart);

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameLayer::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }

    this->setKeypadEnabled(true);
    this->setTouchEnabled(true);

    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                        "CloseNormal.png",
                                        "CloseSelected.png",
                                        this,
                                        menu_selector(GameLayer::menuCloseCallback) );
    pCloseItem->setPosition( ccp(/*CCDirector::sharedDirector()->getWinSize().width - */20, CCDirector::sharedDirector()->getWinSize().height - 20) );

    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition( CCPointZero );

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    //CCLabelTTF* pLabel = CCLabelTTF::create("Hello World, 你好世界", "Thonburi", 34);

    // ask director the window size
    CCSize size = CCDirector::sharedDirector()->getWinSize();

    // position the label on the center of the screen
    //pLabel->setPosition( ccp(size.width / 2, size.height - 20) );

    // add the label as a child to this layer
    //this->addChild(pLabel, 1);

    m_board = CCSprite::create("board.png");
    m_board->setPosition(ccp(size.width / 2, size.height / 2));
    this->addChild(m_board, 0);
    m_board->setScale(1.0f);
    if (m_board->getContentSize().width / m_board->getContentSize().height <
    	size.width / size.height)
    {
    	m_board->setScale(size.height / m_board->getContentSize().height * 1);
    }
    else
    {
    	m_board->setScale(size.width / m_board->getContentSize().width * 1);
    }

    m_board->addChild(pMenu, 1);

    int i, j;
    for (i = 0; i < 15; i++)
    {
    	for (j = 0; j < 15; j++)
    	{
    		//float x = (102.0f + (((378.0f - 102.0f) / 14) * i));
    		//float y = 320.0f - (22.0f + (((298.0f - 22.0f) / 14) * j));
			m_black_piece[i][j] = CCSprite::create("black_piece.png");
			m_black_piece[i][j]->setPosition(PIECE_POSITION(i, j));
			m_board->addChild(m_black_piece[i][j], 0);
			m_black_piece[i][j]->setScale(1.0);
			m_black_piece[i][j]->setVisible(false);
    	}
	}
    for (i = 0; i < 15; i++)
	{
		for (j = 0; j < 15; j++)
		{
			//float x = (102.0f + (((378.0f - 102.0f) / 14) * i));
			//float y = 320.0f - (22.0f + (((298.0f - 22.0f) / 14) * j));
			m_white_piece[i][j] = CCSprite::create("white_piece.png");
			m_white_piece[i][j]->setPosition(PIECE_POSITION(i, j));
			m_board->addChild(m_white_piece[i][j], 1);
			m_white_piece[i][j]->setScale(1.0);
			m_white_piece[i][j]->setVisible(false);
		}
	}

    m_game_draw = CCSprite::create("game_draw.png");
    m_game_draw->setPosition(ccp(436.0f, (320.0f - 263.0f)));
	m_board->addChild(m_game_draw, 1);
	m_game_draw->setScale(1.0);
	m_game_draw->setVisible(false);

    m_game_white = CCSprite::create("game_white.png");
    m_game_white->setPosition(ccp(436.0f, (320.0f - 263.0f)));
	m_board->addChild(m_game_white, 1);
	m_game_white->setScale(1.0);
	m_game_white->setVisible(false);

    m_game_black = CCSprite::create("game_black.png");
    m_game_black->setPosition(ccp(436.0f, (320.0f - 263.0f)));
	m_board->addChild(m_game_black, 1);
	m_game_black->setScale(1.0);
	m_game_black->setVisible(false);

    m_select_i = m_select_j = 7;
    m_select_piece = CCSprite::create("select_piece.png");
    m_select_piece->setPosition(PIECE_POSITION(m_select_i, m_select_j));
	m_board->addChild(m_select_piece, 2);
	m_select_piece->setScale(1.0);
	m_select_piece->setVisible(true);

    //testBoard();

    m_start_black_button = CCMenuItemImage::create(
    		"start_black_button.png", "start_black_button.png",
            this, menu_selector(GameLayer::menuBlackStartCallback));
    m_start_black_button->setPosition(ccp(42.0f, (320.0f - 89.0f)));
    pMenu->addChild(m_start_black_button, 3);
    m_start_black_button->setScale(1.0);
    m_start_black_button->setVisible(true);

    m_start_white_button = CCMenuItemImage::create(
    		"start_white_button.png", "start_white_button.png",
            this, menu_selector(GameLayer::menuWhiteStartCallback));
    m_start_white_button->setPosition(ccp(436.0f, (320.0f - 89.0f)));
    pMenu->addChild(m_start_white_button, 3);
    m_start_white_button->setScale(1.0);
    m_start_white_button->setVisible(true);

    m_up_button = CCMenuItemImage::create(
    		"up_button.png", "up_button.png",
            this, menu_selector(GameLayer::menuUpCallback));
    m_up_button->setPosition(ccp(42.0f, (320.0f - 149.0f)));
    pMenu->addChild(m_up_button, 3);
    m_up_button->setScale(1.0);
    m_up_button->setVisible(true);

    m_ok_button = CCMenuItemImage::create(
    		"ok_button.png", "ok_button.png",
            this, menu_selector(GameLayer::menuOkCallback));
    m_ok_button->setPosition(ccp(436.0f, (320.0f - 149.0f)));
    pMenu->addChild(m_ok_button, 3);
    m_ok_button->setScale(1.0);
    m_ok_button->setVisible(true);

    m_down_button = CCMenuItemImage::create(
    		"down_button.png", "down_button.png",
            this, menu_selector(GameLayer::menuDownCallback));
    m_down_button->setPosition(ccp(42.0f, (320.0f - 263.0f)));
    pMenu->addChild(m_down_button, 3);
    m_down_button->setScale(1.0);
    m_down_button->setVisible(true);

    m_left_button = CCMenuItemImage::create(
    		"left_button.png", "left_button.png",
            this, menu_selector(GameLayer::menuLeftCallback));
    m_left_button->setPosition(ccp(42.0f, (320.0f - 208.0f)));
    pMenu->addChild(m_left_button, 3);
    m_left_button->setScale(1.0);
    m_left_button->setVisible(true);

    m_right_button = CCMenuItemImage::create(
    		"right_button.png", "right_button.png",
            this, menu_selector(GameLayer::menuRightCallback));
    m_right_button->setPosition(ccp(436.0f, (320.0f - 208.0f)));
    pMenu->addChild(m_right_button, 3);
    m_right_button->setScale(1.0);
    m_right_button->setVisible(true);

    return true;
}

void GameLayer::startGame(bool isBlackStart)
{
	m_game_draw->setVisible(false);
	m_game_white->setVisible(false);
	m_game_black->setVisible(false);

	m_up_button->setVisible(true);
	m_down_button->setVisible(true);
	m_left_button->setVisible(true);
	m_right_button->setVisible(true);
	m_ok_button->setVisible(true);

    //0-player; 1-inner AI; 2-outer AI
    if (isBlackStart)
    {
		m_game.setPlayer(1, 0); //blackPlayer = player;
		m_game.setPlayer(2, 1); //whitePlayer = inner AI;
	}
    else
    {
		m_game.setPlayer(1, 1); //blackPlayer = inner AI;
		m_game.setPlayer(2, 0); //whitePlayer = player;
    }
    m_game.restart();
    gameLoop(false);
}

void GameLayer::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->popScene();
}

void GameLayer::keyBackClicked(void)
{
	CCLayer::keyBackClicked();

	CCDirector::sharedDirector()->popScene();
}

void GameLayer::keyMenuClicked(void)
{
	CCLayer::keyMenuClicked();
}

void GameLayer::testBoard(void)
{
	int i, j;
    int zimu[] =  {192,240,252,60,28,16,254,254,254,16,
    		16,16,16,0,0,0,32,32,33,33,
    		33,33,63,63,63,33,33,33,33,32,
    		32,0};
    bool zimuc[16][16] = {false};
    for (i = 0; i < 15; i++)
    {
    	for (j = 0; j < 15; j++)
    	{
			if (j < 8) {
				int k = zimu[i] & (1 << j);
				zimuc[i][j] = (k != 0);
			} else {
				int k = zimu[16 + i] & (1 << (j - 8));
				zimuc[i][j] = (k != 0);
			}
    	}
    }
    for (i = 0; i < 15; i++)
    {
    	for (j = 0; j < 15; j++)
    	{
    		if (zimuc[i][j])
    		{
    			m_black_piece[i][j]->setVisible(true);
    			m_white_piece[i][j]->setVisible(false);
    		}
    		else
    		{
				m_black_piece[i][j]->setVisible(false);
				m_white_piece[i][j]->setVisible(true);
    		}
    	}
    }
}

void GameLayer::menuLeftCallback(CCObject* pSender)
{
	m_select_i--;
	if (m_select_i < 0)
	{
		m_select_i = 0;
	}
	m_select_piece->setPosition(PIECE_POSITION(m_select_i, m_select_j));
}

void GameLayer::menuRightCallback(CCObject* pSender)
{
	m_select_i++;
	if (m_select_i > 14)
	{
		m_select_i = 14;
	}
	m_select_piece->setPosition(PIECE_POSITION(m_select_i, m_select_j));
}

void GameLayer::menuUpCallback(CCObject* pSender)
{
	m_select_j--;
	if (m_select_j < 0)
	{
		m_select_j = 0;
	}
	m_select_piece->setPosition(PIECE_POSITION(m_select_i, m_select_j));
}

void GameLayer::menuDownCallback(CCObject* pSender)
{
	m_select_j++;
	if (m_select_j > 14)
	{
		m_select_j = 14;
	}
	m_select_piece->setPosition(PIECE_POSITION(m_select_i, m_select_j));
}

void GameLayer::menuOkCallback(CCObject* pSender)
{
	gameLoop(true);
}

void GameLayer::menuBlackStartCallback(CCObject* pSender)
{
	startGame(true);
}

void GameLayer::menuWhiteStartCallback(CCObject* pSender)
{
	startGame(false);
}

void GameLayer::gameLoop(bool isPlayer)
{
	bool isIdle = false;
	int limit = 10;

	while (!isIdle)
	{
		int stage = m_game.getStage();
		switch (stage)
		{
		case 1:
			{
				int currentType = m_game.chess->getCurrentPieceType();
				int currentPlayer = m_game.getPlayer(currentType);
				if (currentPlayer == 1)
				{
					m_game.chess->AIWork(currentType);
					m_game.checkResult(currentType);
				}
				else if (currentPlayer == 0)
				{
					//cout << "[warning][stage 1] not AI work turn" << endl;
					//isIdle = true;
				}
			}
			break;
		}

		if (!isPlayer)
		{
			break;
		}

		stage = m_game.getStage();
		switch (stage)
		{
		case 0:
			isIdle = true;
			break;

		case 1:
			{
				int currentType = m_game.chess->getCurrentPieceType();
				int currentPlayer = m_game.getPlayer(currentType);

				if (currentPlayer == 1)
				{
					//cout << "[warning][stage 1] not human turn" << endl;
					isIdle = false;
				}
				else if (currentPlayer == 0)
				{
					if (m_game.chess->addPiece(m_select_i, m_select_j, currentType))
					{
						m_game.checkResult(currentType);
					}
				}
			}
			break;

		case 2:
			{
				isIdle = true;
			}
			break;
		}

		limit--;
		if (limit < 0)
		{
			break;
		}
	}

	for (int i = 0; i < 15 ; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			int type = m_game.chess->hasPiece(i, j);
			switch (type)
			{
			case 1:
				m_black_piece[i][j]->setVisible(true);
				m_white_piece[i][j]->setVisible(false);
				break;

			case 2:
				m_black_piece[i][j]->setVisible(false);
				m_white_piece[i][j]->setVisible(true);
				break;

			case 0:
				m_black_piece[i][j]->setVisible(false);
				m_white_piece[i][j]->setVisible(false);
				break;
			}
		}
	}
	if (m_game.getStage() == 2)
	{
		int winner = m_game.getWinner();
		if (winner >= 1 && winner <= 3)
		{
			switch (winner)
			{
			case 1:
				m_game_draw->setVisible(false);
				m_game_white->setVisible(false);
				m_game_black->setVisible(true);
				break;

			case 2:
				m_game_draw->setVisible(false);
				m_game_white->setVisible(true);
				m_game_black->setVisible(false);
				break;

			case 3:
				m_game_draw->setVisible(true);
				m_game_white->setVisible(false);
				m_game_black->setVisible(false);
				break;
			}
			m_up_button->setVisible(false);
			m_down_button->setVisible(false);
			m_left_button->setVisible(false);
			m_right_button->setVisible(false);
			m_ok_button->setVisible(false);
		}
	}
}

void GameLayer::registerWithTouchDispatcher()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addStandardDelegate(this, 0);
}

void GameLayer::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent)
{
	CCSetIterator iter = pTouches->begin();
	for (; iter != pTouches->end(); iter++)
	{
		CCTouch* pTouch = (CCTouch*)(*iter);
		CCPoint location = pTouch->getLocation();
		CCPoint loc = this->m_board->convertToNodeSpace(location);
		for (int i = 0; i < 15; i++)
		{
			for (int j = 0; j < 15; j++)
			{
				CCPoint piece = PIECE_POSITION(i, j);
				if (fabs(piece.x - loc.x) < (378.0f - 102.0f) / 14 / 2 &&
					fabs(piece.y - loc.y) < (298.0f - 22.0f) / 14 / 2)
				{
					m_select_i = i;
					m_select_j = j;
					m_select_piece->setPosition(PIECE_POSITION(m_select_i, m_select_j));
					break;
				}
			}
		}
	}
}
