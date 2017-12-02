#include "PolygonLayer.h"

USING_NS_CC;


PolygonLayer* PolygonLayer::create()
{
	PolygonLayer* ret = new (std::nothrow) PolygonLayer();
	if (ret && ret->init())
	{
		ret->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(ret);
	}
	return ret;
}

PolygonLayer * PolygonLayer::create(const Color4B& color)
{
	PolygonLayer * layer = new (std::nothrow) PolygonLayer();
	if (layer && layer->initWithColor(color))
	{
		layer->autorelease();
		return layer;
	}
	CC_SAFE_DELETE(layer);
	return nullptr;
}

void PolygonLayer::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags)
{
	_customCommand.init(_globalZOrder, transform, flags);
	_customCommand.func = CC_CALLBACK_0(PolygonLayer::onDraw, this, transform, flags);
	renderer->addCommand(&_customCommand);

	//for (unsigned int i = 0; i < 8; i++)
	//{
	//	_squareColors[i].r = _displayedColor.r / 255.0f;
	//	_squareColors[i].g = _displayedColor.g / 255.0f;
	//	_squareColors[i].b = _displayedColor.b / 255.0f;
	//	_squareColors[i].a = _displayedOpacity / 255.0f;
	//}

	//_customCommand.init(_globalZOrder, transform, flags);
	//_customCommand.func = CC_CALLBACK_0(MyLayerColor::onDraw, this, transform, flags);
	//renderer->addCommand(&_customCommand);

	//Size size = Director::getInstance()->getVisibleSize();
	//Rect rect = Rect(100, 100, 200, 200);

	//_squareVertices[0] = Vec2(0.0, 0.0);
	//_squareVertices[2] = Vec2(size.width, 0.0);
	//_squareVertices[1] = Vec2(rect.origin.x,rect.origin.y);
	//_squareVertices[3] = Vec2(rect.origin.x+rect.size.width, rect.origin.y);
	//_squareVertices[4] = Vec2(size.width, size.height);
	//_squareVertices[5] = Vec2(rect.origin.x + rect.size.width, rect.origin.y+rect.size.height);
	//_squareVertices[6] = Vec2(rect.origin.x, rect.origin.y + rect.size.height);
	//_squareVertices[7] = Vec2(0, size.height);

	//for (int i = 0; i < 8; ++i)
	//{
	//	Vec4 pos;
	//	pos.x = _squareVertices[i].x; 
	//	pos.y = _squareVertices[i].y; 
	//	pos.z = _positionZ;
	//	pos.w = 1;
	//	_modelViewTransform.transformVector(&pos);
	//	_noMVPVertices[i] = Vec3(pos.x, pos.y, pos.z) / pos.w;
	//}
}

void PolygonLayer::onDraw(const Mat4& transform, uint32_t /*flags*/)
{
	getGLProgram()->use();
	getGLProgram()->setUniformsForBuiltins(transform);

	GL::enableVertexAttribs(GL::VERTEX_ATTRIB_FLAG_POSITION | GL::VERTEX_ATTRIB_FLAG_COLOR);
	Vec3 vertices[24] = { Vec3(0, 0, 0), Vec3(10, 10, 0), Vec3(_contentSize.width, 0, 0),
		Vec3(10, 10, 0), Vec3(_contentSize.width - 10, 10, 0), Vec3(_contentSize.width, 0, 0),
		Vec3(_contentSize.width, 0, 0), Vec3(_contentSize.width - 10, 10, 0), Vec3(_contentSize.width, _contentSize.height, 0),
		Vec3(_contentSize.width - 10, 10, 0), Vec3(_contentSize.width, _contentSize.height, 0), Vec3(_contentSize.width - 10, _contentSize.height - 10, 0),
		Vec3(_contentSize.width, _contentSize.height, 0), Vec3(_contentSize.width - 10, _contentSize.height - 10, 0), Vec3(10, _contentSize.height - 10, 0),
		Vec3(_contentSize.width, _contentSize.height, 0), Vec3(10, _contentSize.height - 10, 0), Vec3(0, _contentSize.height, 0),
		Vec3(10, _contentSize.height - 10, 0), Vec3(0, _contentSize.height, 0), Vec3(0, 0, 0),
		Vec3(10, _contentSize.height - 10, 0), Vec3(0, 0, 0), Vec3(10, 10, 0) };

	Color4F  _squareColors[24];
	for (unsigned int i = 0; i < 24; i++)
	{
		_squareColors[i].r = _displayedColor.r / 255.0f;
		_squareColors[i].g = _displayedColor.g / 255.0f;
		_squareColors[i].b = _displayedColor.b / 255.0f;
		_squareColors[i].a = _displayedOpacity / 255.0f;
	}

	Vec3 positions[8] = { Vec3(0, 0, 0), Vec3(_contentSize.width, 0, 0), Vec3(10, 10, 0), Vec3(_contentSize.width - 10, 10, 0),
		Vec3(_contentSize.width, _contentSize.height, 0), Vec3(_contentSize.width - 10, _contentSize.height - 10, 0), Vec3(10, _contentSize.height - 10, 0), Vec3(0, _contentSize.height, 0) 
	};

	Color4F  colors[8];
	for (unsigned int i = 0; i < 8; i++)
	{
		colors[i].r = _displayedColor.r / 255.0f;
		colors[i].g = _displayedColor.g / 255.0f;
		colors[i].b = _displayedColor.b / 255.0f;
		colors[i].a = _displayedOpacity / 255.0f;
	}

	unsigned int _indices[24] = {0, 1, 2, 1, 2, 3, 1, 3, 4, 3, 4, 5, 4, 5, 6, 4, 6, 7, 6, 7, 2, 7, 2, 0 };
	
	//
	// Attributes
	//
	//glBindBuffer(GL_ARRAY_BUFFER, 0);
	glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 3, GL_FLOAT, GL_FALSE, 0, positions);
	glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_COLOR, 4, GL_FLOAT, GL_FALSE, 0, colors);

	GL::blendFunc(_blendFunc.src, _blendFunc.dst);

	GLuint _indexBuffer = 0;
	glGenBuffers(1, &_indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(_indices), _indices, GL_STATIC_DRAW);

	glDrawElements(GL_TRIANGLES, 24, GL_UNSIGNED_INT, NULL);
	//glDrawArrays(GL_TRIANGLES, 0, 24);

	CC_INCREMENT_GL_DRAWN_BATCHES_AND_VERTICES(1, 24);
}
