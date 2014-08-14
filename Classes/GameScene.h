//
//  GameScene.h
//  
//
//  Created by nova on 14-8-5.
//
//

#ifndef __study__GameScene__
#define __study__GameScene__
 
#include "cocos2d.h"

class Game : public cocos2d::Layer{
public:
    static cocos2d::Scene* createScene();
    
    enum{BG,MENU,LABEL};
    
    virtual bool init();
    
    bool onTouchBegan(cocos2d::Touch * touch, cocos2d::Event * event) override;
    void onTouchMoved(cocos2d::Touch * touch, cocos2d::Event * event) override;
    void onTouchEnded(cocos2d::Touch * touch, cocos2d::Event * event) override;
    
    void update(float t) override;
    void moveMenu(float t);
    void menuReturnCallback(cocos2d::Ref* pSender);
    
    CREATE_FUNC(Game);
};

#endif /* defined(__study__GameScene__) */
