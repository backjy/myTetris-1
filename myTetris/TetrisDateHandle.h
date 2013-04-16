//
//  TetrisDateHandle.h
//  myTetris
//
//  Created by CpyShine on 13-4-5.
//
//

#ifndef __myTetris__TetrisDateHandle__
#define __myTetris__TetrisDateHandle__

#include <iostream>

#include "cocos2d.h"

using namespace cocos2d;

class TetrisDateHandle {
    int t_cloum;
    int t_row;
    int t_Counts;
    CCPoint * positionArray;
    int * tetrisStateArray;
    
    CCSize t_contentSize;
public:
    
    static TetrisDateHandle * getSharedTetrisDateHandle();
    
    TetrisDateHandle();
    ~TetrisDateHandle();
    
    // functions 
    inline void initWithT_C_R(int c,int r,CCSize _size){
        t_cloum = c;
        t_row = r;
        t_Counts = t_cloum*t_row;
        t_contentSize = _size;
        h_initTetrisState_PositionArray();
    }
    
    void h_initTetrisState_PositionArray();
    
    void h_ShowDebug();
    
#pragma mark - Getters
    
    inline unsigned int h_get_T_Cloum(){// 得到 列数
        return t_cloum;
    }
    
    inline unsigned int h_get_T_Row(){//得到 行数
        return t_row;
    }
    
    inline unsigned int h_get_T_TotalCounts(){//得到总数
        return t_Counts;
    }
    
    inline CCSize h_get_T_ContentSize(){//得到 content size
        return t_contentSize;
    }
    
    inline CCPoint h_getPositionAtIndex(int _index){// 得到position 在数组的index
        
        if (positionArray) {
            return positionArray[_index];
        }else
            CCLog("Positon array is NULL");
        return CCPointZero;
    }
    
    inline unsigned int h_getTetrisStateArrayAtIndex(int _index){// 得到当前状态数组在index位置的状态
        
        if (tetrisStateArray) {
            return tetrisStateArray[_index];
        }else
            CCLog("Tetris State Array is NULL");
        return -1;
    }
    
    inline int h_getIndexAt(int _cloum,int _row){//的到index 在数组中
        
        int index = (_row*t_cloum) + _cloum;
        
        if (index >= t_Counts || index<0) {
            CCLog("index out of range in Tetris State Array!");
            return -1;
        }
        return index;
    }
#pragma mark - update Tetris state array
    
    inline void h_updateTetrisStateArray(int _index,int _value){//更新状态数组在index位置的状态
        
        if (tetrisStateArray) {
            tetrisStateArray[_index] = _value;
        }else
            CCLog("Tetris State Array is NULL!");
    }
    
    inline void h_ClearTetrisStateArray(){//用0清空 数组中
        memset(tetrisStateArray, 0, sizeof(int)*t_Counts);
        //
    }
    
    bool h_checkWillDisappearBlocks();

    int h_checkTetrisStateArrayRow_State(int _index);
};

#endif /* defined(__myTetris__TetrisDateHandle__) */
