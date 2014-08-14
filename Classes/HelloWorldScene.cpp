#include "HelloWorldScene.h"
#include "GameScene.h"

USING_NS_CC;

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
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    
    this->addChild(LayerColor::create(Color4B(0x0,0,0,0xFF)));
    
    
    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.
    
    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));
    
    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
    
    
    auto toGameItem = MenuItemImage::create(
                                            "button_end.png",
                                            "button_end.png",
                                            CC_CALLBACK_1(HelloWorld::menuToGameCallback, this));
    toGameItem->setPosition(origin.x + visibleSize.width - toGameItem->getContentSize().width / 2,
                            origin.y + closeItem->getContentSize().height + toGameItem->getContentSize().height / 2 + 10);
    menu->addChild(toGameItem);
    
    /////////////////////////////
    // 3. add your codes below...
    
    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = LabelTTF::create("Hello World", "Arial", 24);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));
    
    // add the label as a child to this layer
    this->addChild(label, 1);
    
    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("HelloWorld.png");
    CCLOG("--------------------------HellowWorldScene----------------------");
    CCLOG("sprite default position:(%.2f,%.2f)",sprite->getPosition().x,sprite->getPosition().y);
    CCLOG("sprite defaule anchor point (%.2f,%.2f),ignoreAnchor:%s" ,
          sprite->getAnchorPoint().x,sprite->getAnchorPoint().y,sprite->isIgnoreAnchorPointForPosition()?"TRUE":"FALSE");
    
    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    
    // add the sprite as a child to this layer
    this->addChild(sprite, 0);
    
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

void HelloWorld::menuToGameCallback(Ref *pSender){
    auto scene = Game::createScene();
    //auto tscene = TransitionCrossFade::create(1, scene);
    //auto tscene = TransitionJumpZoom::create(1,scene);
    
    auto tscene = TransitionFadeTR::create(1,scene);
    Director::getInstance()->replaceScene(tscene);
    
}
