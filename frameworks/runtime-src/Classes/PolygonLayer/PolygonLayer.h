#pragma once
#include "cocos2d.h"

USING_NS_CC;

/*
���layer�����ڴ�ɫ��layer�����Ͻ����οմ���
Ĭ�ϵ������ �м��ο�
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



