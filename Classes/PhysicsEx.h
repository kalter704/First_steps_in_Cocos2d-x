#ifndef __PHYSICSEX_SCENE_H__
#define __PHYSICSEX_SCENE_H__

#include "cocos2d.h"

class PhysicsEx : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    //// a selector callback
    //void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(PhysicsEx);

	void GoBack(cocos2d::Ref *pSender);

private:

    cocos2d::PhysicsWorld *_scene_world;

    void setPhysicsWorld(cocos2d::PhysicsWorld *world) { _scene_world = world; }

    bool onContactBegin(cocos2d::PhysicsContact &contact);

};

#endif // __PHYSICSEX_SCENE_H__
