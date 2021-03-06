#include "EntryScene.h"

#include "SpineScene.h"
#include "ParallaxScene.h"

USING_NS_CC;

Scene* EntrySceneMainLayer::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
	auto layer = EntrySceneMainLayer::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool EntrySceneMainLayer::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
										   CC_CALLBACK_1(EntrySceneMainLayer::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1, "menu");

	{
		auto spineSceneButton = MenuItemLabel::create(
			Label::createWithTTF("# Spine Test", CommonTTF, 15)
			, CC_CALLBACK_1(EntrySceneMainLayer::ChangeSceneMenuCallback, this)
			);
		spineSceneButton->setPosition(Vec2(100.f, visibleSize.height - 50.f));
		spineSceneButton->setColor(Color3B::RED);
		menu->addChild(spineSceneButton, 2, "spine");

		auto parallaxSceneButton = MenuItemLabel::create(
			Label::createWithTTF("# ParallaxNode Test", CommonTTF, 15)
			, CC_CALLBACK_1(EntrySceneMainLayer::ChangeSceneMenuCallback, this)
			);
		parallaxSceneButton->setPosition(Vec2(100.f, visibleSize.height - 75.f));
		parallaxSceneButton->setColor(Color3B::RED);
		menu->addChild(parallaxSceneButton, 2, "parallax");
	}

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
	auto label = Label::createWithTTF("Cocos2d-X", CommonTTF, 24);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
	this->addChild(sprite, 0);
    
    return true;
}

void EntrySceneMainLayer::menuCloseCallback(Ref* pSender)
{
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}

void EntrySceneMainLayer::ChangeSceneMenuCallback(cocos2d::Ref *__sender)
{
	Menu *menu = (Menu *)this->getChildByName("menu");

	Scene *scene = nullptr;
	if (__sender == menu->getChildByName("spine"))
	{
		scene = SpineSceneMainLayer::createScene();
	}
	else if (__sender == menu->getChildByName("parallax"))
	{
		scene = ParallaxSceneLayer::createScene();
	}

	Director::getInstance()->replaceScene(scene);
}
