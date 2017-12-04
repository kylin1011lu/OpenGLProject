#include "ShaderNode.h"
#include "cocos2d.h"

USING_NS_CC;
USING_NS_CC_EXT;

///---------------------------------------
// 
// ShaderNode
// 
///---------------------------------------
enum 
{
    SIZE_X = 256,
    SIZE_Y = 256,
};

ShaderNode::ShaderNode()
:_center(Vec2(0.0f, 0.0f))
,_resolution(Vec2(0.0f, 0.0f))
,_time(0.0f)
{
}

ShaderNode::~ShaderNode()
{
}

ShaderNode* ShaderNode::shaderNodeWithVertex(const std::string &vert, const std::string& frag)
{
    auto node = new (std::nothrow) ShaderNode();
    node->initWithVertex(vert, frag);
    node->autorelease();

    return node;
}

bool ShaderNode::initWithVertex(const std::string &vert, const std::string &frag)
{
    _vertFileName = vert;
    _fragFileName = frag;
#if CC_ENABLE_CACHE_TEXTURE_DATA
    auto listener = EventListenerCustom::create(EVENT_RENDERER_RECREATED, [this](EventCustom* event){
            this->setGLProgramState(nullptr);
            loadShaderVertex(_vertFileName, _fragFileName);
        });

    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
#endif

    loadShaderVertex(vert, frag);
	auto size = Director::getInstance()->getWinSize();
    _time = 0;
    _resolution = Vec2(size.width, size.height);

    scheduleUpdate();

    //setContentSize(Size(SIZE_X, SIZE_Y));
    //setAnchorPoint(Vec2(0.5f, 0.5f));
    

    return true;
}

void ShaderNode::loadShaderVertex(const std::string &vert, const std::string &frag)
{
    auto fileUtiles = FileUtils::getInstance();

    // frag
    auto fragmentFilePath = fileUtiles->fullPathForFilename(frag);
    auto fragSource = fileUtiles->getStringFromFile(fragmentFilePath);

    // vert
    std::string vertSource;
    if (vert.empty()) {
        vertSource = ccPositionTextureColor_vert;
    } else {
        std::string vertexFilePath = fileUtiles->fullPathForFilename(vert);
        vertSource = fileUtiles->getStringFromFile(vertexFilePath);
    }

    auto glprogram = GLProgram::createWithByteArrays(vertSource.c_str(), fragSource.c_str());
    auto glprogramstate = GLProgramState::getOrCreateWithGLProgram(glprogram);
    setGLProgramState(glprogramstate);
}

void ShaderNode::update(float dt)
{
    _time += dt;
}

void ShaderNode::setPosition(const Vec2 &newPosition)
{
    Node::setPosition(newPosition);
    auto position = getPosition();
    auto frameSize = Director::getInstance()->getOpenGLView()->getFrameSize();
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto retinaFactor = Director::getInstance()->getOpenGLView()->getRetinaFactor();
    _center = Vec2(position.x * frameSize.width / visibleSize.width * retinaFactor, position.y * frameSize.height / visibleSize.height * retinaFactor);
}

void ShaderNode::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags)
{
    _customCommand.init(_globalZOrder, transform, flags);
    _customCommand.func = CC_CALLBACK_0(ShaderNode::onDraw, this, transform, flags);
    renderer->addCommand(&_customCommand);
}

void ShaderNode::onDraw(const Mat4 &transform, uint32_t flags)
{
	auto size = Director::getInstance()->getWinSize();
    float w = size.width, h = size.height;
    GLfloat vertices[12] = {0,0, w,0, w,h, 0,0, 0,h, w,h};

	auto glProgramState = getGLProgramState();
	glProgramState->setVertexAttribPointer("a_position", 2, GL_FLOAT, GL_FALSE, 0, vertices);
	glProgramState->setUniformVec2("iResolution", Vec2(w,h));
	// Right: normal sprite
	//auto right = Sprite::create("Images/grossinis_sister2.png");
	//glProgramState->setUniformTexture("u_texture1", right->getTexture());

    glProgramState->apply(transform);

    glDrawArrays(GL_TRIANGLES, 0, 6);
    
    CC_INCREMENT_GL_DRAWN_BATCHES_AND_VERTICES(1,6);

	//float w = SIZE_X, h = SIZE_Y;
	//GLfloat vertices[54] = { 0, 0, 10, 10, w, 0,
	//	10, 10, w - 10, 10, w, 0,
	//	w, 0, w - 10, 10, w, h,
	//	w - 10, 10, w, h, w - 10, h - 10,
	//	w, h, w - 10, h - 10, 10, h - 10,
	//	w, h, 10, h - 10, 0, h,
	//	10, h - 10, 0, h, 0, 0,
	//	10, h - 10, 0, 0, 10, 10 };

	//auto glProgramState = getGLProgramState();
	//glProgramState->setUniformVec2("resolution", _resolution);
	//glProgramState->setUniformVec2("center", _center);
	//glProgramState->setVertexAttribPointer("a_position", 2, GL_FLOAT, GL_FALSE, 0, vertices);

	//glProgramState->apply(transform);

	//glDrawArrays(GL_TRIANGLES, 0, 24);

	//CC_INCREMENT_GL_DRAWN_BATCHES_AND_VERTICES(1, 24);
}

