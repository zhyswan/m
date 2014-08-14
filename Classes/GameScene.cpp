//
//  GameScene.cpp
//  study
//
//  Created by nova on 14-8-5.
//
//

#include "GameScene.h"
#include "HelloWorldScene.h"

USING_NS_CC; 

Scene* Game::createScene(){
    auto scene = Scene::create();
    CCLOG("------------------------GameScene------------------------");
    CCLOG("scene default position:(%.2f,%.2f)",scene->getPosition().x,scene->getPosition().y);
    CCLOG("scene defaule anchor point (%.2f,%.2f),ignoreAnchor:%s" ,
          scene->getAnchorPoint().x,scene->getAnchorPoint().y,scene->isIgnoreAnchorPointForPosition()?"TRUE":"FALSE");
    
    
    
    //注册自身锚点，左下角（0，0），中点（0.5，0.5）
    //动画变形等根据锚点来处理，
    //如果不忽略锚点，则锚点与自身在父容器的position重合,否则0，0点与自身在父容器的position重合
    //scene->setAnchorPoint(Vec2(0.5,0.5));
    //忽略不忽略只影响位置，不影响动画等
    //scene->ignoreAnchorPointForPosition(false);
    
    auto layer = Game::create();
    CCLOG("------------------------GameScene------------------------");
    CCLOG("layer default position:(%.2f,%.2f)",layer->getPosition().x,layer->getPosition().y);
    CCLOG("layer defaule anchor point (%.2f,%.2f),ignoreAnchor:%s" ,
          layer->getAnchorPoint().x,layer->getAnchorPoint().y,layer->isIgnoreAnchorPointForPosition()?"TRUE":"FALSE");
    //layer->ignoreAnchorPointForPosition(false);
    //layer->setAnchorPoint(Vec2(0.5,0.5));
    scene->addChild(layer);
    
    return scene;
}

bool Game::onTouchBegan(Touch * touch, Event * event){
    CCLOG("OnTouchBegan");
    CCLOG("Position:(%.0f,%.0f)",touch->getLocation().x,touch->getLocation().y);
    return true;
}
void Game::onTouchMoved(Touch * touch, Event * event){
    CCLOG("onTouchMoved");
    
}
void Game::onTouchEnded(Touch * touch, Event * event){
    CCLOG("onTouchEnded");
}


//计划任务
void Game::update(float t){
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    static int move = 2;
    auto bgSprite = this->getChildByTag(BG);
    auto position = bgSprite->getPosition();
    bgSprite->setPosition(position.x + move,position.y);

    
    if(bgSprite->getPosition().x >= visibleSize.width-bgSprite->getContentSize().width / 2){
        move = -move;
    }
    if(bgSprite->getPosition().x <= bgSprite->getContentSize().width / 2){
        move = -move;
    }
}

//计划任务
void Game::moveMenu(float t){
    auto menu = this->getChildByTag(MENU);
    menu->runAction(MoveTo::create(0.2,Vec2(menu->getPosition().x - 100,menu->getPosition().y)));
    //menu->setPosition(menu->getPosition().x - 40,menu->getPosition().y);
}

bool Game::init(){
    if(!Layer::init()){
        return false;
    }
    
    this->setAnchorPoint(Vec2(0,0));
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    CCLOG("------------------------GameScene------------------------");
    CCLOG("origin(%.2f,%.2f),%.2f,%.2f",origin.x, origin.y, visibleSize.width,visibleSize.height);
    
    auto colorLayer = LayerColor::create(Color4B(0xFF, 0x00, 0xFF, 0xFF));
    colorLayer->setPosition(origin.x, origin.y);
    this->addChild(colorLayer);
    
    
    auto layerGradient = LayerGradient::create(Color4B(0xFF, 0x00, 0x00, 0xFF), Color4B(0xFF, 0xFF, 0x00, 0xFF)
                                               // ,Vec2(0, -1)    //只影响渐变角度，不影响渐变中间过度的位置,默认自顶向下 （0，－1）
                                               );
    layerGradient->setPosition(origin.x, origin.y);
    this->addChild(layerGradient);
    
    
    auto bgSprite = Sprite::create("kaluolin.jpg");
    bgSprite->setTag(BG);
    bgSprite->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);
    this->addChild(bgSprite);
    //触摸事件处理
    //创建触摸事件的侦听对象
    auto listener = EventListenerTouchOneByOne::create();
    
    //定义侦听对象的回调方法
    listener->onTouchBegan = CC_CALLBACK_2(Game::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(Game::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(Game::onTouchEnded, this);
    //在事件分发器中注册
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener,bgSprite);

    
    
    
    //添加计划任务
    this->scheduleUpdate();//添加update计划任务
    
    //Game::moveMenu(float)每隔2s执行一次，共4(1+3)次，5s后开始执行第一次
    this->schedule(schedule_selector(Game::moveMenu),2,3,5);
    
    auto returnItem = MenuItemImage::create("image.png","image.png",
                                            CC_CALLBACK_1(Game::menuReturnCallback, this));
    returnItem->setPosition(origin.x + visibleSize.width - returnItem->getContentSize().width / 2,
                            origin.y + returnItem->getContentSize().height / 2);
    auto menu = Menu::create(returnItem,nullptr);
    menu->setTag(MENU);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu);
    
    return true;
}


void Game::menuReturnCallback(Ref* pSender){
    auto scene = HelloWorld::createScene();
    //auto tscene = TransitionFadeTR::create(1, scene);
    auto tscene = TransitionZoomFlipY::create(1, scene);
    Director::getInstance()->replaceScene(tscene);
}
