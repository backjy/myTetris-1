//
//  TetrisBlockType.cpp
//  myTetris
//
//  Created by CpyShine on 13-4-13.
//  Copyright 2013年 __MyCompanyName__. All rights reserved.
//

#include "TetrisBlockType.h"

#include "TetrisBlock.h"
#include "TetrisDateHandle.h"
#include "TetrisGameLayer.h"

bool TetrisBlockType::T_playerHandle(PlayerHandle _handleType){
    bool _flag = false;
    switch (_handleType) {
        case DROPDOWN:
            _flag = T_checkDropDown();
            if (_flag) {
                T_updateTetrisStateArray(0);
                T_dropDown();
                T_updateTetrisStateArray(1);
            }
            break;
        case LEFTMOVE:
            _flag = T_checkLeftMove();
            if (_flag) {
                T_updateTetrisStateArray(0);
                T_leftMove();
                T_updateTetrisStateArray(1);
            }
            break;
        case RIGHTMOVE:
            _flag = T_checkRightMove();
            if (_flag) {
                T_updateTetrisStateArray(0);
                T_rightMove();
                T_updateTetrisStateArray(1);
            }
            break;
        case ROTATE:
                T_updateTetrisStateArray(0);
                T_rotate();
                T_updateTetrisStateArray(1);
            break;
        default:
            break;
    }
    TetrisDateHandle::getSharedTetrisDateHandle()->h_ShowDebug();
    return _flag;
}

#pragma mark -  LongBlock_Type ......

void LongBlock_Type::init(){
    
    TetrisBlockType::init();
    
    t_count = 4;
    t_typeIndex = 0;
    
    if (!t_childBlockArray) {
        CCLog(" t_childBlockArray is NULL");
        return;
    }
    
    int _cloum = TetrisDateHandle::getSharedTetrisDateHandle()->h_get_T_Cloum()/2-1;
    int _row   = TetrisDateHandle::getSharedTetrisDateHandle()->h_get_T_Row()-1;
    
    for (int i=0; i<t_count; i++) {
        TetrisBlock * _block = TetrisBlock::create();
        _block->b_initWithType(0);
        t_childBlockArray->addObject(_block);
        TetrisGameLayer::getSharedTetrisGameLayer()->G_g_b_blockParentAddChild(_block);
    }
    
    TetrisBlock * _bk = (TetrisBlock*)t_childBlockArray->objectAtIndex(0);
    _bk->b_Update_C_R(_cloum, _row-1);
    T_rotate();
    T_updateTetrisStateArray(1);
}

bool LongBlock_Type::T_checkDropDown(){
//    CCLog("long block check drop down !");
    if (t_typeIndex==0) {//横向
        TetrisBlock * _block1 = (TetrisBlock*)t_childBlockArray->objectAtIndex(0);
        TetrisBlock * _block2 = (TetrisBlock*)t_childBlockArray->objectAtIndex(1);
        TetrisBlock * _block3 = (TetrisBlock*)t_childBlockArray->objectAtIndex(2);
        TetrisBlock * _block4 = (TetrisBlock*)t_childBlockArray->objectAtIndex(3);
        if (_block1->b_checkWithDirection(0)&&_block2->b_checkWithDirection(0)&&_block3->b_checkWithDirection(0)&&_block4->b_checkWithDirection(0)) {
            return true;
        }
    }
    if (t_typeIndex==1) {//竖着
        TetrisBlock * _block4 = (TetrisBlock*)t_childBlockArray->objectAtIndex(3);
        return _block4->b_checkWithDirection(0);
    }
    return false;
}

void LongBlock_Type::T_dropDown(){
    
    for (int i=0; i<t_count; i++) {
        TetrisBlock * _block = (TetrisBlock*)t_childBlockArray->objectAtIndex(i);
        _block->b_DropDown();
    }
}

bool LongBlock_Type::T_checkLeftMove(){
//    CCLog("long block check left move !");
    if (t_typeIndex==0) {//横向
        TetrisBlock * _block4 = (TetrisBlock*)t_childBlockArray->objectAtIndex(1);//数组里面第二块作为横着左边的那一块
        return _block4->b_checkWithDirection(1);
    }
    if (t_typeIndex==1) {//竖着
        TetrisBlock * _block1 = (TetrisBlock*)t_childBlockArray->objectAtIndex(0);
        TetrisBlock * _block2 = (TetrisBlock*)t_childBlockArray->objectAtIndex(1);
        TetrisBlock * _block3 = (TetrisBlock*)t_childBlockArray->objectAtIndex(2);
        TetrisBlock * _block4 = (TetrisBlock*)t_childBlockArray->objectAtIndex(3);
        if (_block1->b_checkWithDirection(1)&&_block2->b_checkWithDirection(1)&&_block3->b_checkWithDirection(1)&&_block4->b_checkWithDirection(1)) {
            return true;
        }
    }
    return false;
}

void LongBlock_Type::T_leftMove(){
    
    for (int i=0; i<t_count; i++) {
        TetrisBlock * _block = (TetrisBlock*)t_childBlockArray->objectAtIndex(i);
        _block->b_LeftMove();
    }
}

bool LongBlock_Type::T_checkRightMove(){
//    CCLog("long block check right move !");
    if (t_typeIndex==0) {//横向
        TetrisBlock * _block4 = (TetrisBlock*)t_childBlockArray->objectAtIndex(3);//数组里面最后一块作为横着右边的那一块
        return _block4->b_checkWithDirection(2);
    }
    if (t_typeIndex==1) {//竖着
        TetrisBlock * _block1 = (TetrisBlock*)t_childBlockArray->objectAtIndex(0);
        TetrisBlock * _block2 = (TetrisBlock*)t_childBlockArray->objectAtIndex(1);
        TetrisBlock * _block3 = (TetrisBlock*)t_childBlockArray->objectAtIndex(2);
        TetrisBlock * _block4 = (TetrisBlock*)t_childBlockArray->objectAtIndex(3);
        if (_block1->b_checkWithDirection(2)&&_block2->b_checkWithDirection(2)&&_block3->b_checkWithDirection(2)&&_block4->b_checkWithDirection(2)) {
            return true;
        }
    }
    return false;
}

void LongBlock_Type::T_rightMove(){
    for (int i=0; i<t_count; i++) {
        TetrisBlock * _block = (TetrisBlock*)t_childBlockArray->objectAtIndex(i);
        _block->b_RightMove();
    }
}

void LongBlock_Type::T_rotate(){//旋转
    
//    CCLog("long block check rotate !");
    
    TetrisDateHandle * _sharedHandle = TetrisDateHandle::getSharedTetrisDateHandle();
    int _t_cloum = _sharedHandle->h_get_T_Cloum();//一共多少列 需要转换 -1
//    int _t_row   = _sharedHandle->h_get_T_Row();  //一共多少行 需要转换 -1
    
    TetrisBlock * _block1 = (TetrisBlock*)t_childBlockArray->objectAtIndex(0);
    
    int _fristblock_cloum = _block1->b_get_B_Cloum();//第一块的列位置 不需要转换
    int _fristblock_row = _block1->b_get_B_Row();    //第一块的行位置 不需要转换
    
    if (t_typeIndex==1) {//转为横向
        
        if (_fristblock_cloum-1<0 || _fristblock_cloum+2>(_t_cloum-1)) {
            return;
        }
        
        int _index_left = _sharedHandle->h_getIndexAt(_fristblock_cloum -1, _fristblock_row);//左边的位置
        int _index_right = _sharedHandle->h_getIndexAt(_fristblock_cloum + 2, _fristblock_row);//右边的位置
        
        if (_sharedHandle->h_getTetrisStateArrayAtIndex(_index_left) ||
            _sharedHandle->h_getTetrisStateArrayAtIndex(_index_right)) {
            return;// 当左边或者右边的 state array 返回值都为0时才能旋转
        }
        
        TetrisBlock * _block2 = (TetrisBlock*)t_childBlockArray->objectAtIndex(1);
        _block2->b_Update_C_R(_fristblock_cloum-1, _fristblock_row);
        
        TetrisBlock * _block3 = (TetrisBlock*)t_childBlockArray->objectAtIndex(2);
        _block3->b_Update_C_R(_fristblock_cloum+1, _fristblock_row);
        
        TetrisBlock * _block4 = (TetrisBlock*)t_childBlockArray->objectAtIndex(3);
        _block4->b_Update_C_R(_fristblock_cloum+2, _fristblock_row);
        
        t_typeIndex = 0;
        return;
    }
    if (t_typeIndex==0) {//转为竖向
        
        if (_fristblock_row-2<0) {
            return;
        }
        
        int _index_down = _sharedHandle->h_getIndexAt(_fristblock_cloum, _fristblock_row-2);
        
        if (_sharedHandle->h_getTetrisStateArrayAtIndex(_index_down)) {
            return;
        }
        
        TetrisBlock * _block2 = (TetrisBlock*)t_childBlockArray->objectAtIndex(1);
        _block2->b_Update_C_R(_fristblock_cloum, _fristblock_row+1);
        
        TetrisBlock * _block3 = (TetrisBlock*)t_childBlockArray->objectAtIndex(2);
        _block3->b_Update_C_R(_fristblock_cloum, _fristblock_row-1);
        
        TetrisBlock * _block4 = (TetrisBlock*)t_childBlockArray->objectAtIndex(3);
        _block4->b_Update_C_R(_fristblock_cloum, _fristblock_row-2);
        
        t_typeIndex = 1;
        return;
    }
}

void LongBlock_Type::T_updateTetrisStateArray(int _value){
    for (int i=0; i<t_count; i++) {
        TetrisBlock * _block = (TetrisBlock*)t_childBlockArray->objectAtIndex(i);
        _block->b_UpdateTetrisStateArray(_value);
    }
}

#pragma mark - other blocks ......

