//
//  TetrisBlockType.h
//  myTetris
//
//  Created by CpyShine on 13-4-13.
//  Copyright 2013年 __MyCompanyName__. All rights reserved.
//

#ifndef _TetrisBlockType_H
#define _TetrisBlockType_H

#include "cocos2d.h"
#include "Config.h"

using namespace cocos2d;

class TetrisBlockType{
  
public:
    
    unsigned int t_count;
    
    int t_typeIndex;
    
    CCArray * t_childBlockArray;//用于存放当前形状包含的数组
public:
    TetrisBlockType(){this->init();}
    
    ~TetrisBlockType(){
        
        if (t_childBlockArray) {
            t_childBlockArray->removeAllObjects();
            t_childBlockArray->autorelease();
//            CC_SAFE_DELETE_ARRAY(t_childBlockArray);
        }
        
    }
public://functions
    
    virtual void init(){
        t_count = 4;
        t_typeIndex = 0;
        t_childBlockArray = new CCArray();
        t_childBlockArray->init();
    }
    
    virtual bool T_playerHandle(PlayerHandle _handleType);
    
    virtual bool T_checkLeftMove(){
        CCLog("TetrisBlockType check drop down !");return false;}
    virtual void T_leftMove(){}
    virtual bool T_checkRightMove(){
        CCLog("TetrisBlockType check drop down !");return false;}
    virtual void T_rightMove(){}
    virtual bool T_checkDropDown(){
        CCLog("TetrisBlockType check drop down !");return false;}
    virtual void T_dropDown(){}
    
    
    virtual void T_rotate(){
        CCLog("TetrisBlockType check drop down !");}
    
    
    virtual void T_updateTetrisStateArray(int _value){}
};


class LongBlock_Type : public TetrisBlockType {
    
public:
    virtual void init();
    
//    virtual void T_playerHandle(PlayerHandle _handleType);
    
    virtual bool T_checkLeftMove();
    virtual void T_leftMove();
    virtual bool T_checkRightMove();
    virtual void T_rightMove();
    virtual bool T_checkDropDown();
    virtual void T_dropDown();
    
    
    virtual void T_rotate();
    
    virtual void T_updateTetrisStateArray(int _value);
};

#endif