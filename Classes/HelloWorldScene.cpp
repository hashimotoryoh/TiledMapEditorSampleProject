#include "HelloWorldScene.h"

USING_NS_CC;
USING_NS_CC_EXT;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

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
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    // TiledMapEditorで生成したマップを表示する
    _map = TMXTiledMap::create("TMX/stage1.tmx");
    _mapLayer = _map->getLayer("layer1");
    
    // マップのサイズ
    Size mapSize = Size(_map->getTileSize().width  * _map->getMapSize().width,
                        _map->getTileSize().height * _map->getMapSize().height);
    
    // スクロールビュー
    ScrollView *scrollView = ScrollView::create(mapSize*3);
    scrollView->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    scrollView->setPosition(Vec2(100, 100));
    scrollView->setMaxScale(5.0f);
    scrollView->setBounceable(false);
    scrollView->setContentSize(mapSize*3);
    this->addChild(scrollView);
    
    // 中のレイヤー
    Layer *innerLayer = Layer::create();
    scrollView->addChild(innerLayer);
    
    // スクロールビューの背景
    Sprite *sprite = Sprite::create();
    sprite->setTextureRect(Rect(0, 0, scrollView->getContentSize().width, scrollView->getContentSize().height));
    sprite->setColor(Color3B(230,230,230));
    sprite->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
    innerLayer->addChild(sprite);
    
    // マップを表示
    _map->setScale(3);
    innerLayer->addChild(_map);
    
    // キャラクターを表示
    _character = Sprite::create("TMX/character.png");
    _character->setAnchorPoint(Vec2(0.5f, 0.25f));
    _charaPos = Vec2(0, 0);
    _character->setPosition(_mapLayer->getPositionAt(_charaPos) + _map->getTileSize()/2);
    _map->addChild(_character);
    
    // サイコロボタン
    _isMoving = false;
    MenuItemLabel *dice = MenuItemLabel::create(Label::createWithSystemFont("サイコロ", "arial", 30.0f),
                                                CC_CALLBACK_1(HelloWorld::dice, this));
    dice->setPosition(Vec2(600, 0));
    this->addChild(Menu::create(dice, NULL));
    
    // サイコロの目
    Label *pips = Label::createWithSystemFont("-", "arial", 30.0f);
    pips->setPosition(Vec2(1200, 300));
    pips->setTag(10);
    this->addChild(pips);
    
    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}


void HelloWorld::dice(cocos2d::Ref *ref)
{
    if (_isMoving) return;
    
    unsigned int distance = std::rand() % 6 + 1;
    
    // サイコロの目を表示
    Label *pips = dynamic_cast<Label*>(this->getChildByTag(10));
    std::stringstream strPips;
    strPips << distance;
    pips->setString(strPips.str());
    
    this->move(distance);
}


void HelloWorld::move(unsigned int cnt)
{
    if (cnt == 0) return;
    
    // 移動先の座標を計算
    if (_charaPos.x == 0 && _charaPos.y < 9)
        _charaPos = Vec2(0, _charaPos.y+1);
    else if (_charaPos.x < 9 && _charaPos.y == 9)
        _charaPos = Vec2(_charaPos.x+1, 9);
    else if (_charaPos.x == 9 && _charaPos.y > 0)
        _charaPos = Vec2(9, _charaPos.y-1);
    else
        _charaPos = Vec2(_charaPos.x-1, 0);
    
    MoveTo *move = MoveTo::create(0.5f, _mapLayer->getPositionAt(_charaPos) + _map->getTileSize()/2);
    CallFunc *func = CallFunc::create([this, cnt]() {
        this->move(cnt-1);
    });
    
    _character->runAction(Sequence::create(move, func, NULL));
}

