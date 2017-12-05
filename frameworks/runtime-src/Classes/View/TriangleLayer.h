#ifndef _TRIANGLE_LAYER_H_
#define _TRIANGLE_LAYER_H_

#include "cocos2d.h"

USING_NS_CC;


class TriangleLayer :
	public Layer
{
public:
	static TriangleLayer* create();
	//virtual void visit(Renderer *renderer, const Mat4& parentTransform, uint32_t parentFlags);
	virtual void draw(Renderer *renderer, const Mat4 &transform, uint32_t flags) override;
protected:
	void onDraw(const Mat4& transform, uint32_t flags);
private:
	CustomCommand _customCommand;
};

#endif



