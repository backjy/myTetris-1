//
//  TetrisDateHandle.cpp
//  myTetris
//
//  Created by CpyShine on 13-4-5.
//
//

#include "TetrisDateHandle.h"

#include "TetrisGameLayer.h"


static TetrisDateHandle * _sharedTetrisDateHandle=NULL;

#pragma mark - sharedTetrisDateHandle 

TetrisDateHandle * TetrisDateHandle::getSharedTetrisDateHandle(){
    if (_sharedTetrisDateHandle==NULL) {
        _sharedTetrisDateHandle = new TetrisDateHandle();
    }
    return _sharedTetrisDateHandle;
}

TetrisDateHandle::TetrisDateHandle(){
    if (_sharedTetrisDateHandle==NULL) {
        _sharedTetrisDateHandle = this;
    }
}

TetrisDateHandle::~TetrisDateHandle(){
    _sharedTetrisDateHandle = NULL;
}


void TetrisDateHandle::h_initTetrisState_PositionArray(){
    tetrisStateArray = new int[t_Counts]();
    positionArray = new CCPoint[t_Counts]();
    
    if (tetrisStateArray==NULL || positionArray==NULL) {
        CCLog("Tetris State Array OR Position Array Initialize filed");
        return;
    }
    
    float h_width = t_contentSize.width/2;
    
    for (int r=0; r<t_row; r++) {
        for (int c=0; c<t_cloum; c++) {
            int index = (r*t_cloum) + c;
            tetrisStateArray[index] = 0;
            positionArray[index] = CCPointMake(t_contentSize.width*c+h_width, t_contentSize.height*r + h_width);
        }
    }
}

void TetrisDateHandle::h_ShowDebug(){
    printf("abcdefghijklmnopqrstuvwxyz\n");
    for (int r=t_row-1; r>=0; r--) {
        for (int i=0; i<t_cloum; i++) {
            int index = r*t_cloum +i;
            printf("%d",tetrisStateArray[index]);
        }
        printf("-----%02d\n",r);
    }
    printf("abcdefghijklmnopqrstuvwxyz\n");
}

bool TetrisDateHandle::h_checkWillDisappearBlocks(){
    bool _tag=false;
    int _index=0;
    for (int r=0; r<t_row; r++) {
        int _in = h_getIndexAt(0, r);
        int _flag = h_checkTetrisStateArrayRow_State(_in);
        
        if (_flag==1) {
            TetrisGameLayer::getSharedTetrisGameLayer()->G_g_b_blockParentRemoveChildWithRow(r-_index);
            _index++;
            _tag = true;
            continue;
        }
        if (_flag==0) {
            return _tag;
        }
        if (_flag==-1) {
            continue;
        }
    }
    return _tag;
}

int TetrisDateHandle::h_checkTetrisStateArrayRow_State(int _index){
    int flag = h_getTetrisStateArrayAtIndex(_index);
    for (int c=1; c<t_cloum; c++) {
        int _nextState = h_getTetrisStateArrayAtIndex(_index + c);
        if (flag==_nextState) {
            continue;
        }else
            return -1;
    }
    return flag;
}