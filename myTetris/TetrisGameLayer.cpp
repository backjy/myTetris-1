//
//  TetrisGameLayer.cpp
//  myTetris
//
//  Created by CpyShine on 13-4-3.
//  Copyright 2013年 __MyCompanyName__. All rights reserved.
//

#include "TetrisGameLayer.h"

#include "Config.h"
#include "TetrisDateHandle.h"
#include "TetrisBlockType.h"
#include "TetrisBlock.h"

static TetrisGameLayer * _sharedTetrisGameLayer=NULL;

TetrisGameLayer * TetrisGameLayer::getSharedTetrisGameLayer(){
    if (!_sharedTetrisGameLayer) {
        _sharedTetrisGameLayer = TetrisGameLayer::create();//new TetrisGameLayer();
    }
    return _sharedTetrisGameLayer;
}

bool TetrisGameLayer::init(void){
    if (!CCLayer::init()) {
        return false;
    }
    
    _sharedTetrisGameLayer = this;
    
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    CCLog("size_width:%f_height:%f",size.width,size.height);
    int cl = 20;
    
    float width = size.width/20;
    
    int row = (size.height-50)/width;
    
    TetrisDateHandle * datehandle = TetrisDateHandle::getSharedTetrisDateHandle();
    
    CCSize cs = CCSizeMake(width, width);
    
    _c = cl;_r = row;
    _w = width;_h=width;
    
    datehandle->initWithT_C_R(cl, row, cs);
    
    drawRect = CCRect(20, 50, (cl-1)*width, row*width);
    
    G_B_blockParent = CCNode::create();
    G_B_blockParent->setAnchorPoint(ccp(0, 0));
    G_B_blockParent->setPosition(ccp(0, 0));
    this->addChild(G_B_blockParent);
    
    return true;
}

void TetrisGameLayer::onEnter(void){
    CCLayer::onEnter();
    
    //set touch enable = yes,and delegate is oneByone
    this->setTouchMode(kCCTouchesOneByOne);
    this->setTouchEnabled(true);
}

void TetrisGameLayer::startGame(){
    
    G_current_HandleType = new LongBlock_Type();
    G_current_HandleType->init();
    
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    
    CCMenuItemImage * left = CCMenuItemImage::create("left.png", "left.png");
    left->setTarget(this, menu_selector(TetrisGameLayer::leftButtonPressed));
    left->setScale(0.5);
    CCMenuItemImage * right = CCMenuItemImage::create("right.png", "right.png");
    right->setTarget(this, menu_selector(TetrisGameLayer::rightButtonPressed));
    left->setAnchorPoint(ccp(0, 0));
    right->setAnchorPoint(ccp(0, 0));
    right->setScale(0.5);
    right->setPosition(ccp(size.width/2+size.width/4, 0));
    
    CCMenuItemImage * down = CCMenuItemImage::create("down.png", "down.png");
    down->setTarget(this, menu_selector(TetrisGameLayer::downButtonPressed));
    down->setAnchorPoint(ccp(0,0));
    down->setScale(0.5);
    down->setPosition(ccp(size.width/2 -100,0));
    down->setOpacity(0.7*255);
    
    CCMenu * menu = CCMenu::create(left,down,right);
    menu->setAnchorPoint(ccp(0, 0));
    menu->setPosition(ccp(0, 0));
    this->addChild(menu);
}

void TetrisGameLayer::onEnterTransitionDidFinish(void){
    CCLayer::onEnterTransitionDidFinish();
}

void TetrisGameLayer::leftButtonPressed(cocos2d::CCNode *sender){
//    CCLog("left");
    G_current_HandleType->T_playerHandle(LEFTMOVE);
}

void TetrisGameLayer::rightButtonPressed(cocos2d::CCNode *sender){
//    CCLog("right");
    G_current_HandleType->T_playerHandle(RIGHTMOVE);
}

void TetrisGameLayer::downButtonPressed(cocos2d::CCNode *sender){
//    CCLog("down");
    if (!G_current_HandleType->T_playerHandle(DROPDOWN)) {
        delete G_current_HandleType;
        G_current_HandleType = NULL;
        while (TetrisDateHandle::getSharedTetrisDateHandle()->h_checkWillDisappearBlocks()) {
            G_g_b_blockParentChildDropDown();
            CCLog("do check ------------");
        }
        TetrisDateHandle::getSharedTetrisDateHandle()->h_checkWillDisappearBlocks();
        G_current_HandleType = new LongBlock_Type();
        G_current_HandleType->init();
    }
}

void TetrisGameLayer::onExit(void){
    CCLayer::onExit();
}

bool TetrisGameLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent){
    if (!G_current_HandleType) {
        return false;
    }
    G_current_HandleType->T_playerHandle(ROTATE);
    return false;
}
void TetrisGameLayer::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent){
    
}
void TetrisGameLayer::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent){
    
}
void TetrisGameLayer::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent){
    
}

void TetrisGameLayer::draw(void){
//    CCPoint s = ccp(drawRect.origin.x,drawRect.origin.y);
//    CCPoint e = ccp(drawRect.size.width,drawRect.size.height);
//    ccDrawRect(s,e);
    
    for (int i=0; i<_c; i++) {
        CCPoint s = ccp(i*_w,0);
        CCPoint e = ccp(i*_w,1136);
        ccDrawLine(s, e);
    }
    
    for (int j=0; j<_r; j++) {
        CCPoint s = ccp(0,j*_h);
        CCPoint e = ccp(640,j*_h);
        ccDrawLine(s, e);
    }
}

void TetrisGameLayer::G_g_b_blockParentAddChild(cocos2d::CCNode *_node){
    if (!G_B_blockParent) {
        CCLog("G_B_blockParent is NULL");
        return;
    }
    G_B_blockParent->addChild(_node);
//    this->addChild(_node);
}

void TetrisGameLayer::G_g_b_blockParentRemoveChildWithRow(const int _row){
    CCArray * _childArr = G_B_blockParent->getChildren();
    unsigned int count = _childArr->count();
    int _index = 0;
    for (unsigned int i=0; i<count; i++) {
        TetrisBlock * _block = (TetrisBlock*)_childArr->objectAtIndex(i-_index);
        if (_block->b_get_B_Row()==_row) {
            _block->b_disappear();
            _index++;
        }else if (_block->b_get_B_Row()>_row){//当方块的row>_row 时 掉下一格
            _block->b_DropDown();
        }
    }
}

void TetrisGameLayer::G_g_b_blockParentChildDropDown(){
    TetrisDateHandle::getSharedTetrisDateHandle()->h_ShowDebug();
    unsigned int count = G_B_blockParent->getChildrenCount();
    
    TetrisDateHandle::getSharedTetrisDateHandle()->h_ClearTetrisStateArray();//将statearray的全部清空

    for (int i=0; i<count; i++) {
        TetrisBlock * _block = (TetrisBlock*)G_B_blockParent->getChildren()->objectAtIndex(i);
        _block->b_UpdateTetrisStateArray(1);
    }
}

TetrisGameLayer::~TetrisGameLayer(){
    _sharedTetrisGameLayer = NULL;
}

