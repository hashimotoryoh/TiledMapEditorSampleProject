#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include <extensions/cocos-ext.h>

enum class CharacterDirection {
    Left,
    Down,
    Right,
    Up
};

class HelloWorld : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
    
    void dice(cocos2d::Ref *ref);
    void move(unsigned int cnt);
    
    cocos2d::TMXTiledMap *_map;
    cocos2d::TMXLayer *_mapLayer;
    cocos2d::Sprite *_character;
    cocos2d::Vec2 _charaPos;
    CharacterDirection _charaDirecction = CharacterDirection::Left;
    
    bool _isMoving;
};

#endif // __HELLOWORLD_SCENE_H__
