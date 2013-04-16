//
//  TetrisBlock.h
//  myTetris
//
//  Created by CpyShine on 13-4-8.
//  Copyright 2013年 __MyCompanyName__. All rights reserved.
//

#ifndef _TetrisBlock_H
#define _TetrisBlock_H

#include "cocos2d.h"

using namespace cocos2d;

class TetrisBlock :public CCSprite {
    
    int b_cloum;
    int b_row;
    
public:
    virtual bool init(void);
    virtual void draw(void);
    CREATE_FUNC(TetrisBlock);
    
#pragma mark -
    
    void b_initWithType(int _type);
    
    void b_LeftMove();//左移的时候调用
    void b_RightMove();//右移的时候调用
    void b_DropDown();//掉了时候调用
    
    void b_Update_C_R(int _cloum,int _row);//当 块旋转，等操作时 会调用
    void b_UpdateTetrisStateArray(int _value);//更新状态数组
    
    inline int b_get_B_Cloum(){return b_cloum;}
    inline int b_get_B_Row(){return b_row;}
    
    bool b_checkWithDirection(int _direction);
    
    void b_disappear();
};

#endif