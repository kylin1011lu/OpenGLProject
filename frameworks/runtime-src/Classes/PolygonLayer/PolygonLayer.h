#pragma once
#include "cocos2d.h"

USING_NS_CC;

/*
多边layer，是在纯色的layer基础上进行镂空处理
默认的情况下 中间镂空
*/

class PolygonLayer :
	public LayerColor
{
public:
	static PolygonLayer* create();
	static PolygonLayer* create(const Color4B& color);
	//
	// Overrides
	//
	virtual void draw(Renderer *renderer, const Mat4 &transform, uint32_t flags) override;
protected:
	void onDraw(const Mat4& transform, uint32_t flags);
};



