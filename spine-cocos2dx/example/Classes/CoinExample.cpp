/******************************************************************************
 * Spine Runtimes License Agreement
 * Last updated January 1, 2020. Replaces all prior versions.
 *
 * Copyright (c) 2013-2020, Esoteric Software LLC
 *
 * Integration of the Spine Runtimes into software or otherwise creating
 * derivative works of the Spine Runtimes is permitted under the terms and
 * conditions of Section 2 of the Spine Editor License Agreement:
 * http://esotericsoftware.com/spine-editor-license
 *
 * Otherwise, it is permitted to integrate the Spine Runtimes into software
 * or otherwise create derivative works of the Spine Runtimes (collectively,
 * "Products"), provided that each user of the Products must obtain their own
 * Spine Editor license and redistribution of the Products in any form must
 * include this license and copyright notice.
 *
 * THE SPINE RUNTIMES ARE PROVIDED BY ESOTERIC SOFTWARE LLC "AS IS" AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL ESOTERIC SOFTWARE LLC BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES,
 * BUSINESS INTERRUPTION, OR LOSS OF USE, DATA, OR PROFITS) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THE SPINE RUNTIMES, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *****************************************************************************/

#include "CoinExample.h"
#include "MixAndMatchExample.h"

USING_NS_CC;
using namespace spine;

Scene* CoinExample::scene () {
	Scene *scene = Scene::create();
	scene->addChild(CoinExample::create());
	return scene;
}

void myListener(TrackEntry* entry, spine::Event* event) {
    //if (event->getData().getName() == "audio")
    printf("-----event:%s\n", event->getData().getName().buffer());
}

bool CoinExample::init () {
	if (!LayerColor::initWithColor(Color4B(128, 128, 128, 255))) return false;

//	skeletonNode = SkeletonAnimation::createWithBinaryFile("coin-pro.skel", "coin.atlas", 1);
//	skeletonNode->setAnimation(0, "animation", true);
//    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("cha_1571.plist");
//    skeletonNode = SkeletonAnimation::createWithJsonFile("cha_1571.json", "", 1.0f);
//    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("ceshi/1/s_hua_1.plist");
//    skeletonNode = SkeletonAnimation::createWithJsonFile("ceshi/10/hua_11.json", "", 0.5f);
//    spine::SkeletonAnimation* skeletonNode2 = SkeletonAnimation::createWithJsonFile("ceshi/10/hua_11.json", "", 0.5f);
//    spine::SkeletonAnimation* skeletonNode3 = SkeletonAnimation::createWithJsonFile("ceshi/10/hua_11.json", "", 0.5f);
    
//    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("spine_fight_0973_attack_1.plist");
//    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("spine_fight_common_1.plist");
//    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("spine_fight_common_2.plist");
//    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("spine_common.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("cha_1649.plist");
    skeletonNode = SkeletonAnimation::createWithJsonFile("cha_1649.json", "", 0.5f);
    int sh = skeletonNode->getBoundingBox().size.height;
    
    skeletonNode->setAnimation(0, "stand", false);
    //skeletonNode->addAnimation(0, "attack", true, 0);
	skeletonNode->setPosition(Vec2(_contentSize.width / 4, _contentSize.height / 2- sh/2));
	addChild(skeletonNode);
    skeletonNode->scheduleUpdate();
    
    std::vector<std::string> anims = {
        "stand", "attack", "hurt", "dead"
    };
    for(int i=0;i<40;i++) {
        skeletonNode->addAnimation(0, anims[i%4], true, 0);
    }
    
//    skeletonNode2 = SkeletonAnimation::createWithJsonFile("cha_1649.json", "", 0.5f);
//    skeletonNode2->setAnimation(0, "dead", false);
//    curr_time = skeletonNode2->findAnimation("dead")->getDuration();
//    skeletonNode2->update(curr_time);
//    skeletonNode2->setPosition(Vec2(_contentSize.width * 3 / 4, _contentSize.height / 2- sh/2));
//    addChild(skeletonNode2);
//    TrackEntry* entry = skeletonNode2->addAnimation(0, "stand", true, 0);
//    entry->setMixTime(0.2f);
    //skeletonNode2->scheduleUpdate();
    
    
    
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("huahua.plist");
    skeletonNode3 = SkeletonAnimation::createWithJsonFile("hua_14.json", "", 0.5f);
    TrackEntry* track = skeletonNode3->setAnimation(0, "animation", true);
//    float etime = skeletonNode3->findAnimation("animation2")->getEventTime("fx");
//    printf("-----------event fx time:%f\n", etime);
    skeletonNode3->setPosition(Vec2(_contentSize.width * 3 / 4, _contentSize.height / 2));
    addChild(skeletonNode3);
    
    Rect rect = skeletonNode3->getSkeleton()->getAabbBoundingBox();
    auto dn = DrawNode::create();
    Vec2 p1 = rect.origin;
    Vec2 p2 = Vec2(rect.getMaxX(), rect.getMaxY());
    p1 = skeletonNode3->convertToWorldSpace(p1);
    p2 = skeletonNode3->convertToWorldSpace(p2);
    dn->drawRect(p1, p2, Color4F(1.0,0,0,1.0));
    addChild(dn);
    auto dn2 = DrawNode::create();
    Rect rect2 = skeletonNode3->getAabbBoundingBox();
    //rect2.origin = skeletonNode3->convertToWorldSpace(rect2.origin);
    dn2->drawRect(rect2.origin, Vec2(rect2.getMaxX(),rect2.getMaxY()), Color4F(0,1.0,0,1.0));
    addChild(dn2);
    
    Sprite *sp1 = Sprite::createWithSpriteFrameName("cha_1649/head.png");
    skeletonNode3->addChildFollowSlot("code_fx", sp1, true);
    //sp1->setPosition(10, 10);
    //skeletonNode3->addChild(sp1);
    
    skeletonNode3->setEventListener(myListener);
    skeletonNode3->scheduleUpdate();
    
    
    
    
//    skeletonNode2->setAnimation(0, "animation2", true);
//    skeletonNode2->update(1.0);
//    float du = skeletonNode2->findAnimation("animation")->getDuration();
//    printf("animation duration:%f", du);
//    //skeletonNode->addAnimation(0, "animation2", true, 0);
//    skeletonNode2->setPosition(Vec2(_contentSize.width / 2, _contentSize.height / 2- sh/2));
//    addChild(skeletonNode2);
//
//    skeletonNode3->setAnimation(0, "animation", true);
//    skeletonNode3->addAnimation(0, "animation2", true, 0);
//    skeletonNode3->setPosition(Vec2(_contentSize.width * 3 / 4, _contentSize.height / 2- sh/2));
//    addChild(skeletonNode3);

	scheduleUpdate();

	EventListenerTouchOneByOne* listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [this] (Touch* touch, cocos2d::Event* event) -> bool {
		if (!skeletonNode->getDebugBonesEnabled())
			skeletonNode->setDebugBonesEnabled(true);
		else if (skeletonNode->getTimeScale() == 1)
			skeletonNode->setTimeScale(0.3f);
        else {
			//Director::getInstance()->replaceScene(MixAndMatchExample::scene());
        }
        skeletonNode3->setSkin("black");
		return true;
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	return true;
}
void CoinExample::update(float delta) {
    if(!skeletonNode2) return;
    float anim_time = skeletonNode2->findAnimation("dead")->getDuration();
    curr_time -= delta;
    if(curr_time<0.0f) {
        curr_time += anim_time;
        //skeletonNode2->getCurrent()->setTrackTime(curr_time);
    }else if(curr_time >= anim_time) {
        curr_time -= anim_time;
        //skeletonNode2->getCurrent()->setTrackTime(curr_time);
    }
    skeletonNode2->getCurrent()->setTrackTime(0);
    skeletonNode2->update(curr_time);
    //printf("-------2 time:%f delta:%f", curr_time, delta);
}
