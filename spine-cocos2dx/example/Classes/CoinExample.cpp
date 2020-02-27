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
    skeletonNode = SkeletonAnimation::createWithJsonFile("cha_1649.json", "", 1.0f);
    int sh = skeletonNode->getBoundingBox().size.height;
    
    skeletonNode->setAnimation(0, "stand", true);
    //skeletonNode->addAnimation(0, "attack", true, 0);
	skeletonNode->setPosition(Vec2(_contentSize.width / 2, _contentSize.height / 2- sh/2));
	addChild(skeletonNode);
    //skeletonNode->scheduleUpdate();
    
    Sprite *sp = Sprite::createWithSpriteFrameName("cha_1649/head.png");
    sp->setPosition(Vec2(80, 150));
//    sp->setFlippedX(true);
//    sp->setRotation(100);
    addChild(sp);
    
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
		else
			Director::getInstance()->replaceScene(MixAndMatchExample::scene());
		return true;
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	return true;
}
