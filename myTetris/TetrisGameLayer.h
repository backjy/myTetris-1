//
//  TetrisGameLayer.h
//  myTetris
//
//  Created by CpyShine on 13-4-3.
//  Copyright 2013年 __MyCompanyName__. All rights reserved.
//

#ifndef _TetrisGameLayer_H
#define _TetrisGameLayer_H

#include "cocos2d.h"

using namespace cocos2d;

class TetrisBlockType;

class TetrisGameLayer :public CCLayer {
    CCRect drawRect;
public:
    
    int _c,_r;
    float _w,_h;
    
    CCNode * G_B_blockParent;
    
    TetrisBlockType * G_current_HandleType;
public:
    
    virtual bool init(void);
    virtual void onEnter(void);
    virtual void onExit(void);
    virtual void onEnterTransitionDidFinish(void);
    virtual void draw(void);
    
    // default implements are used to call script callback if exist
    
    void leftButtonPressed(cocos2d::CCNode *sender);
    void rightButtonPressed(cocos2d::CCNode *sender);
    void downButtonPressed(cocos2d::CCNode * sender);
    //
    
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);
    
    // default implements are used to call script callback if exist
    CREATE_FUNC(TetrisGameLayer);
    
    virtual ~TetrisGameLayer();
    

    void G_g_b_blockParentAddChild(cocos2d::CCNode * _node);
    void G_g_b_blockParentRemoveChildWithRow(const int _row);
    void G_g_b_blockParentChildDropDown();
    
    static TetrisGameLayer * getSharedTetrisGameLayer();
    
    void startGame();
};

#endif