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
    TMXTiledMap *map = TMXTiledMap::create("TMX/stage1.tmx");
    TMXLayer *mapLayer = map->getLayer("layer1");
    
    // マップのサイズ
    Size mapSize = Size(map->getTileSize().width  * map->getMapSize().width,
                        map->getTileSize().height * map->getMapSize().height);
    
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
    map->setScale(3);
    innerLayer->addChild(map);
    
    // キャラクターを表示
    Sprite *character = Sprite::create("TMX/character.png");
    character->setAnchorPoint(Vec2(0.5f, 0.25f));
    character->setPosition(mapLayer->getPositionAt(Vec2(0, 0)) + map->getTileSize()/2);
    map->addChild(character);
    
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
