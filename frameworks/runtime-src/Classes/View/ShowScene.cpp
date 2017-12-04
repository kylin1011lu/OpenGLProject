#include "ShowScene.h"
#include "ShaderNode.h"
#include "PolygonLayer/PolygonLayer.h"


USING_NS_CC;

Scene* ShowScene::createScene()
{
    return ShowScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool ShowScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    _visibleSize = Director::getInstance()->getVisibleSize();
    _origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(ShowScene::menuCloseCallback, this));

    if (closeItem == nullptr ||
        closeItem->getContentSize().width <= 0 ||
        closeItem->getContentSize().height <= 0)
    {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    }
    else
    {
		float x = _origin.x + _visibleSize.width - closeItem->getContentSize().width / 2;
		float y = _origin.y + closeItem->getContentSize().height / 2;
        closeItem->setPosition(Vec2(x,y));
    }

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...


	//¶à±ßÐÎïÎ¿Õlayer
	//auto polylayer = PolygonLayer::create(Color4B::BLUE);
	//this->addChild(polylayer);

	//addBubblesShaderSprite();

	//¶à²ÊÅÝÅÝÒÆ¶¯shader https://www.shadertoy.com/view/4dl3zn
	//auto sn = ShaderNode::shaderNodeWithVertex("Shaders/Common.vert", "Shaders/bubbles.frag");
	
	//ÀØÉä¼¤¹âshader https://www.shadertoy.com/view/XtBXW3
	//auto sn = ShaderNode::shaderNodeWithVertex("Shaders/Common.vert", "Shaders/Laser.frag");

	//Í¸Ã÷ÅÝÅÝ https://www.shadertoy.com/view/MlXBWM
	//auto sn = ShaderNode::shaderNodeWithVertex("Shaders/Common.vert", "Shaders/transparent_bubbles.frag");
	
	//ÏÂÓê²£Á§ https://www.shadertoy.com/view/MdfBRX
	//auto sn = ShaderNode::shaderNodeWithVertex("Shaders/Common.vert", "Shaders/rain.frag");

	//ÐÄÐÎÑÌ»¨ https://www.shadertoy.com/view/Xl2SRR
	//auto sn = ShaderNode::shaderNodeWithVertex("Shaders/Common.vert", "Shaders/fireworkslove.frag");
	//sn->getGLProgramState()->setUniformTexture("iChannel0", TextureCache::getInstance()->addImage("Textures/rgba_noise.png"));

	//²¨ÀËÈ¦ https://www.shadertoy.com/view/ldX3zr
	//auto sn = ShaderNode::shaderNodeWithVertex("Shaders/Common.vert", "Shaders/waves.frag");

	//¹âÈ¦ https://www.shadertoy.com/view/XdlSDs
	//auto sn = ShaderNode::shaderNodeWithVertex("Shaders/Common.vert", "Shaders/lightcircle.frag");
	
	//µ÷É«°å https://www.shadertoy.com/view/ll2GD3
	auto sn = ShaderNode::shaderNodeWithVertex("Shaders/Common.vert", "Shaders/Palettes.frag");
	sn->getGLProgramState()->setUniformTexture("iChannel0", TextureCache::getInstance()->addImage("Textures/rgba_noise.png"));

	addChild(sn);
    return true;
}


void ShowScene::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}

void ShowScene::addBubblesShaderSprite()
{
	// This is the display size of the quad where for the render beam (in pixels, not points)
	Size texSize(400, 80);

	auto sprite = Sprite::create();
	sprite->setPosition(Vec2(_origin.x + _visibleSize.width / 2, _origin.y + _visibleSize.height / 2));
	sprite->setTextureRect(Rect(0, 0, texSize.width, texSize.height));
	//sprite->setBlendFunc(BlendFunc::ADDITIVE);


	auto prog = GLProgram::createWithFilenames("Shaders/bubbles.vert", "Shaders/bubbles.frag");
	auto glprogramstate = GLProgramState::getOrCreateWithGLProgram(prog);
	sprite->setGLProgramState(glprogramstate);

	// note: iResolution is only "size of screen" because shadertoy applys to full view quad
	auto scale_factor = Director::getInstance()->getContentScaleFactor();
	Vec3 iResolution(texSize.width / (2.f / scale_factor),
		texSize.height / (2.f / scale_factor),
		scale_factor);
	glprogramstate->setUniformVec3("iResolution", iResolution);

	//auto move = MoveBy::create(5.0f, Vec2(100, 100));
	//auto seq = Sequence::create(move, move->reverse(), NULL);
	//sprite->runAction(RepeatForever::create(seq));
	//sprite->setPosition(400, 300);
	this->addChild(sprite);
}
