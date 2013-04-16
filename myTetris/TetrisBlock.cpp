//
//  TetrisBlock.cpp
//  myTetris
//
//  Created by CpyShine on 13-4-8.
//  Copyright 2013年 __MyCompanyName__. All rights reserved.
//

#include "TetrisBlock.h"
#include "TetrisDateHandle.h"
using namespace std;

bool TetrisBlock::init(void){
    if (!CCSprite::init()) {
        return false;
    }
    
    this->setVisible(false);
    b_cloum = 0;
    b_row = 0;
    
    return true;
}

void TetrisBlock::draw(void){
    CCSprite::draw();
}

void TetrisBlock::b_initWithType(int _type){
    CCSize cs = TetrisDateHandle::getSharedTetrisDateHandle()->h_get_T_ContentSize();
    cs = CCSizeMake(cs.width-1, cs.height-1);
    this->setContentSize(cs);
    string  s;
    switch (_type) {
        case 0:
            s = "blue.png";
            break;
            
        case 1:
            s = "blue2.png";
            break;
            
        case 2:
            s = "red.png";
            break;
            
        case 3:
            s = "red2.png";
            break;
        default:
            s = "blue.png";
            break;
    }
    // 好像这里会crash ......
    CCTexture2D * texture = CCTextureCache::sharedTextureCache()->addImage(s.c_str());
//    this->setTexture(texture);
    CCSpriteFrame * frame = CCSpriteFrame::createWithTexture(texture, this->boundingBox());
    this->setDisplayFrame(frame);
}

void TetrisBlock::b_LeftMove(){
    
//    this->b_UpdateTetrisStateArray(0);
    --b_cloum;
//    this->b_UpdateTetrisStateArray(1);
}

void TetrisBlock::b_RightMove(){
    
//    this->b_UpdateTetrisStateArray(0);
    ++b_cloum;
//    this->b_UpdateTetrisStateArray(1);
}

void TetrisBlock::b_DropDown(){
    
//    this->b_UpdateTetrisStateArray(0);
    --b_row;
//    this->b_UpdateTetrisStateArray(1);
}

bool TetrisBlock::b_checkWithDirection(int _direction){
    
    int _tag = 0;
    int _index = 0;
    
    TetrisDateHandle * _tetrisDateHandle = TetrisDateHandle::getSharedTetrisDateHandle();
    
    switch (_direction) {
        case 0:{//check with down
            if (b_row-1<0) {
                return false;
            }
            _index =_tetrisDateHandle->h_getIndexAt(b_cloum, b_row-1);
            _tag = _tetrisDateHandle->h_getTetrisStateArrayAtIndex(_index);
        }
            break;
            
        case 1:{//check with left
            if (b_cloum-1<0) {
                return false;
            }
            _index =_tetrisDateHandle->h_getIndexAt(b_cloum-1, b_row);
            _tag = _tetrisDateHandle->h_getTetrisStateArrayAtIndex(_index);
        }
            break;
            
        case 2:{//check with right
            if (b_cloum+1>19) {
                return false;
            }
            _index =_tetrisDateHandle->h_getIndexAt(b_cloum+1, b_row);
            _tag = _tetrisDateHandle->h_getTetrisStateArrayAtIndex(_index);
        }
            break;
            
        default:
            break;
    }
    
    return !(bool)_tag;
}

void TetrisBlock::b_UpdateTetrisStateArray(int _value){
    
    TetrisDateHandle * _tetrisDateHandle = TetrisDateHandle::getSharedTetrisDateHandle();
    
    int _index = _tetrisDateHandle->h_getIndexAt(b_cloum, b_row);//得到——index
    
    if (_index == -1) {//当返回为-1时，设置为隐藏
        this->setVisible(false);
        return;
    }
    
    _tetrisDateHandle->h_updateTetrisStateArray(_index, _value);//重置 tetris state array 中状态
    
    if (_value) {
        
        CCPoint _pos = _tetrisDateHandle->h_getPositionAtIndex(_index);
        this->setPosition(_pos);//重置位置
//        CCLog("pos x:%f,y:%f",_pos.x,_pos.y);
//        CCLog("c:%d,r:%d",b_cloum,b_row);
        if (!this->isVisible()) {
            this->setVisible(true);
        }
    }
}

void TetrisBlock::b_Update_C_R(int _cloum, int _row){
//    this->b_UpdateTetrisStateArray(0);
    b_cloum = _cloum;
    b_row = _row;
//    this->b_UpdateTetrisStateArray(1);
}

void TetrisBlock::b_disappear(){
    b_UpdateTetrisStateArray(0);
    this->removeFromParent();
}