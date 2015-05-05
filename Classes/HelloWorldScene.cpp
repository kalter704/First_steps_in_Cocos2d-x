#include "HelloWorldScene.h"
#include "NewScene.h"
#include "PhysicsEx.h"

USING_NS_CC;

int angV;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
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
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + visibleSize.height - closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = Label::createWithTTF("Hello World, it is my first cocos!!!", "fonts/Marker Felt.ttf", 24);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("background_2.png");

    // position the sprite on the center of the screen
    //sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
	sprite->setPosition(Vec2(visibleSize.width/2, visibleSize.height/2));

    // add the sprite as a child to this layer
    this->addChild(sprite, 0);

	auto inYanSprite = Sprite::create("in_yan.png");
	inYanSprite->setPosition(Vec2(50, visibleSize.height - 50));
	auto actInYan = RotateBy::create(1, 360);
	auto foreverActInYan = RepeatForever::create(actInYan);
	this->addChild(inYanSprite);
	inYanSprite->runAction(foreverActInYan);

	
	auto sharingSprite = Sprite::create("sharing.png");
	sharingSprite->setPosition(Vec2(150, visibleSize.height - 50));
	auto actSharing = RotateBy::create(1, -1080);
	auto foreverActSharing = RepeatForever::create(actSharing);
	this->addChild(sharingSprite);
	sharingSprite->runAction(foreverActSharing);

	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);

	listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(HelloWorld::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
	auto menu_item_1 = MenuItemFont::create("Play", CC_CALLBACK_1(HelloWorld::Play, this));
	auto menu_item_2 = MenuItemFont::create("Go Physics Scene", CC_CALLBACK_1(HelloWorld::GoPhysicsScene, this));
	auto menu_item_3 = MenuItemFont::create("Setting", CC_CALLBACK_1(HelloWorld::Setting, this));
	auto menu_item_4 = MenuItemImage::create("in_yan.png", "sharing.png", CC_CALLBACK_1(HelloWorld::ImageButton, this));

	auto my_menu = Menu::create(menu_item_1, menu_item_2, menu_item_3, menu_item_4, NULL);
	my_menu->alignItemsVertically();
	//my_menu->setPosition(Vec2(0, 0));
	this->addChild(my_menu, 1);

    return true;
}

void HelloWorld::Play(cocos2d::Ref *pSender) {
	CCLOG("Play");

	auto new_scene = NewScene::createScene();
	Director::getInstance()->pushScene(new_scene);
}

void HelloWorld::GoPhysicsScene(cocos2d::Ref *pSender) {

	auto new_scene = PhysicsEx::createScene();
	Director::getInstance()->replaceScene(TransitionFlipX::create(1, new_scene));
}

void HelloWorld::Setting(cocos2d::Ref *pSender) {
	CCLOG("Setting");
}

void HelloWorld::ImageButton(cocos2d::Ref *pSender) {
	CCLOG("ImageButton");
}

bool HelloWorld::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event) {
	CCLOG("OnTouchBegan x = %f:5:2, y = %f:5:2", touch->getLocation().x, touch->getLocation().y);
	auto sharingSprite = Sprite::create("sharing.png");
	sharingSprite->setPosition(Vec2(touch->getLocation().x, touch->getLocation().y));
	auto actSharing = RotateBy::create(1, cocos2d::random(-1080, 0));
	auto foreverActSharing = RepeatForever::create(actSharing);
	this->addChild(sharingSprite, 1);
	sharingSprite->runAction(foreverActSharing);
	angV = cocos2d::random(0, 1080);
	return true;
}

void HelloWorld::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event) {
	CCLOG("OnTouchMoved x = %f:5:2, y = %f:5:2", touch->getLocation().x, touch->getLocation().y);
	auto inYanSprite = Sprite::create("in_yan.png");
	inYanSprite->setPosition(Vec2(touch->getLocation().x, touch->getLocation().y));
	auto actInYan = RotateBy::create(1, angV);
	auto foreverActInYan = RepeatForever::create(actInYan);
	this->addChild(inYanSprite, 1);
	inYanSprite->runAction(foreverActInYan);
}

void HelloWorld::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event) {
	auto inYanSprite = Sprite::create("in_yan.png");
	inYanSprite->setPosition(Vec2(touch->getLocation().x, touch->getLocation().y));
	auto actInYan = RotateBy::create(1, angV);
	auto foreverActInYan = RepeatForever::create(actInYan);
	this->addChild(inYanSprite, 1);
	inYanSprite->runAction(foreverActInYan);
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
