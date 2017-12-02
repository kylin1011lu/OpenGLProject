#ifndef __SHOW_SCENE_H__
#define __SHOW_SCENE_H__

#include "cocos2d.h"

class ShowScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(ShowScene);


	//´´½¨ÅÝÅÝshader ²Î¿¼https://www.shadertoy.com/view/4dl3zn
	void addBubblesShaderSprite();

private:
	cocos2d::Size _visibleSize;
	cocos2d::Vec2 _origin;
};

#endif // __HELLOWORLD_SCENE_H__
