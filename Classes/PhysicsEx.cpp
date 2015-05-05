#include "HelloWorldScene.h"
#include "PhysicsEx.h"
#include "SonarSystemsBodyParser.h"

USING_NS_CC;

Scene* PhysicsEx::createScene()
{
    // 'scene' is an autorelease object
    //auto scene = Scene::create();
    auto scene = Scene::createWithPhysics();
    scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    
    scene->getPhysicsWorld()->setGravity(Vec2(0, 0));

    // 'layer' is an autorelease object
    auto layer = PhysicsEx::create();
    layer->setPhysicsWorld(scene->getPhysicsWorld());

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool PhysicsEx::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

        auto sprite = Sprite::create("background_2.png");
	    sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
        this->addChild(sprite, 0);
    
	auto menu_item_1 = MenuItemFont::create("GoBack", CC_CALLBACK_1(PhysicsEx::GoBack, this));
	menu_item_1->setPosition(Vec2(origin.x + visibleSize.width - menu_item_1->getContentSize().width/2 , 
								  origin.y + visibleSize.height - menu_item_1->getContentSize().height/2));

	auto my_menu = Menu::create(menu_item_1, NULL);
	my_menu->setPosition(Vec2(0, 0));
	this->addChild(my_menu, 1);

            auto edge_body = PhysicsBody::createEdgeBox(visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 3);
    
            auto edge_node = Node::create();
            edge_node->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
            edge_node->setPhysicsBody(edge_body);

            this->addChild(edge_node);

        {
        auto sprite_mario = Sprite::create("mario_2.png");
        sprite_mario->setPosition(Vec2(visibleSize.width / 2 + origin.x + 100, visibleSize.height / 2 + origin.y + 100));
    
        auto body_mario = PhysicsBody::createBox(sprite_mario->getContentSize(), PhysicsMaterial(0, 1, 0));
        body_mario->setCollisionBitmask(1);
        body_mario->setContactTestBitmask(true);

        body_mario->applyForce(Vec2(-100, -500));

        sprite_mario->setPhysicsBody(body_mario);        

        this->addChild(sprite_mario);
        }

            auto sprite_mario_2 = Sprite::create("mario_2.png");
            sprite_mario_2->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y - 100));
        
            auto body_mario_2 = PhysicsBody::createBox(sprite_mario_2->getContentSize(), PhysicsMaterial(0, 1, 0));
            body_mario_2->setCollisionBitmask(2);
            body_mario_2->setContactTestBitmask(true);

            ////body_mario_2->setDynamic(false);
            //body_mario_2->setAngularVelocity(90);
            //body_mario_2->setAngularDamping(0.5);  
            body_mario_2->setVelocity(Vec2(400, 100));
            body_mario_2->setLinearDamping(0.5);

            sprite_mario_2->setPhysicsBody(body_mario_2);

            this->addChild(sprite_mario_2);   
        {
        auto sprite_mario = Sprite::create("mario_2.png");
        sprite_mario->setPosition(Vec2(visibleSize.width / 2 + origin.x + 100, visibleSize.height / 2 + origin.y + 170));
    
        auto body_mario = PhysicsBody::createBox(sprite_mario->getContentSize(), PhysicsMaterial(0, 1, 0));
        body_mario->setCollisionBitmask(1);
        body_mario->setContactTestBitmask(true);

        body_mario->applyTorque(150);

        sprite_mario->setPhysicsBody(body_mario);        

        this->addChild(sprite_mario);
        }

    {
        //auto sprite_sharing = Sprite::create("sharing.png");
        //sprite_sharing->setPosition(Point(150, visibleSize.height - 150));

        //auto body_sharing = PhysicsBody::createCircle(sprite_sharing->getContentSize().width / 2, PhysicsMaterial(0, 1, 0)); 
        //
        //body_sharing->applyTorque(1000);    

        //sprite_sharing->setPhysicsBody(body_sharing);

        //this->addChild(sprite_sharing);
    }
    
    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(PhysicsEx::onContactBegin, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);

    SonarSysBodyParser::getInstance()->parseJsonFile("in_yan.json");

    auto json_sprite = Sprite::create("in_yan.png");
    json_sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

    auto json_sprite_body = SonarSysBodyParser::getInstance()->bodyFormJson(json_sprite, "in_yan", PhysicsMaterial(1, 1, 0));

    if(json_sprite_body != NULL) {
        json_sprite_body->setDynamic(false);
        json_sprite->setPhysicsBody(json_sprite_body);
    } else {
        CCLOG("NO create body from Json File");
    }

    this->addChild(json_sprite);
    
    //auto json_mario = Sprite::create("mario_2.png");
    //json_mario->setPosition(Vec2(visibleSize.width / 4 + origin.x, visibleSize.height / 3 + origin.y));

    //auto json_mario_body = MyBodyParser::getInstance()->bodyFormJson(sprite, "mario", PhysicsMaterial(1, 1, 0));

    //if(json_mario_body != NULL) {
    //    json_mario_body->setDynamic(false);
    //    json_mario->setPhysicsBody(json_mario_body);
    //} else {
    //    CCLOG("NO create body from Json File");
    //}

    //this->addChild(json_mario);
    
    return true;
}

void PhysicsEx::GoBack(cocos2d::Ref *pSender) {

	auto hello_world = HelloWorld::createScene();
	Director::getInstance()->replaceScene(TransitionFlipX::create(1, hello_world));
}

bool PhysicsEx::onContactBegin(cocos2d::PhysicsContact &contact) {
    PhysicsBody *a = contact.getShapeA()->getBody();
    PhysicsBody *b = contact.getShapeB()->getBody();
    if((a->getCollisionBitmask() == 1 && b->getCollisionBitmask() == 2) || a->getCollisionBitmask() == 2 && b->getCollisionBitmask() == 1) {
        CCLOG("Detect collision!!!");
    }
    return true;
}