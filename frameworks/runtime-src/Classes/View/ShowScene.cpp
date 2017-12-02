#include "ShowScene.h"
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

	addBubblesShaderSprite();

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
