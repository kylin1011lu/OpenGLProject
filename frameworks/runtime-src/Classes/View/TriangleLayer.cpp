#include "TriangleLayer.h"

USING_NS_CC;

TriangleLayer *TriangleLayer::create()
{
	TriangleLayer *ret = new (std::nothrow) TriangleLayer();
	if (ret && ret->init())
	{
		ret->autorelease();
		return ret;
	}
	else
	{
		CC_SAFE_DELETE(ret);
		return nullptr;
	}
}

//void TriangleLayer::visit(Renderer *renderer, const Mat4 &transform, uint32_t flags)
//{
//	Layer::visit(renderer, transform, flags);
//	_customCommand.init(_globalZOrder, transform, flags);
//	_customCommand.func = CC_CALLBACK_0(TriangleLayer::onDraw, this, transform, flags);
//	renderer->addCommand(&_customCommand);
//}

void TriangleLayer::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags)
{
	_customCommand.init(_globalZOrder, transform, flags);
	_customCommand.func = CC_CALLBACK_0(TriangleLayer::onDraw, this, transform, flags);
	renderer->addCommand(&_customCommand);
}

void TriangleLayer::onDraw(const Mat4& transform, uint32_t /*flags*/)
{
	getGLProgram()->use();
	getGLProgram()->setUniformsForBuiltins(transform);

	auto size = Director::getInstance()->getWinSize();

	float verteries[] = {
		0, 0,
		size.width, 0,
		size.width / 2, size.height
	};

	float color[] =
	{
		0, 1, 0, 1,
		1, 0, 0, 1,
		0, 0, 1, 1
	};

	GL::enableVertexAttribs(GL::VERTEX_ATTRIB_FLAG_POSITION | GL::VERTEX_ATTRIB_FLAG_COLOR);

	glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 2, GL_FLOAT, GL_FALSE, 0, verteries);
	glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_COLOR, 4, GL_FLOAT, GL_FALSE, 0, color);

	glDrawArrays(GL_TRIANGLES, 0, 3);

	CC_INCREMENT_GL_DRAWN_BATCHES_AND_VERTICES(1, 3);
	CHECK_GL_ERROR_DEBUG();
}
