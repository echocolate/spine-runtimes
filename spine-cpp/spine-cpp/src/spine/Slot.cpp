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

#ifdef SPINE_UE4
#include "SpinePluginPrivatePCH.h"
#endif

#include <spine/Slot.h>

#include <spine/SlotData.h>
#include <spine/Bone.h>
#include <spine/Skeleton.h>
#include <spine/Attachment.h>

using namespace spine;

Slot::Slot(SlotData &data, Bone &bone) :
		_data(data),
		_bone(bone),
		_skeleton(bone.getSkeleton()),
		_color(1, 1, 1, 1),
		_darkColor(0, 0, 0, 0),
		_hasDarkColor(data.hasDarkColor()),
		_attachment(NULL),
		_attachmentTime(0) {
	setToSetupPose();
}

void Slot::setToSetupPose() {
	_color.set(_data.getColor());

	const String &attachmentName = _data.getAttachmentName();
	if (attachmentName.length() > 0) {
		_attachment = NULL;
		setAttachment(_skeleton.getAttachment(_data.getIndex(), attachmentName));
	} else {
		setAttachment(NULL);
	}
}

SlotData &Slot::getData() {
	return _data;
}

Bone &Slot::getBone() {
	return _bone;
}

Skeleton &Slot::getSkeleton() {
	return _skeleton;
}

Color &Slot::getColor() {
	return _color;
}

Color &Slot::getDarkColor() {
	return _darkColor;
}

bool Slot::hasDarkColor() {
	return _hasDarkColor;
}

Attachment *Slot::getAttachment() {
	return _attachment;
}

void Slot::setAttachment(Attachment *inValue) {
	if (_attachment == inValue) {
		return;
	}

	_attachment = inValue;
	_attachmentTime = _skeleton.getTime();
	_deform.clear();
}

float Slot::getAttachmentTime() {
	return _skeleton.getTime() - _attachmentTime;
}

void Slot::setAttachmentTime(float inValue) {
	_attachmentTime = _skeleton.getTime() - inValue;
}

Vector<float> &Slot::getDeform() {
	return _deform;
}

void Slot::addFollowAttachment(cocos2d::Node *attachment, bool enabledFollowColor) {
    removeFollowAttachment();
    m_followAttachment = attachment;
    m_followAttachment->retain();
    m_enabledFollowColor = enabledFollowColor;
    
    m_followAttachmentColor = attachment->getColor();
    m_followAttachmentOpacity = attachment->getOpacity();
    m_followAttachment->setColor(m_followAttachmentColor);
    m_followAttachment->setOpacity(m_followAttachmentOpacity);
    m_followAttachmentScaleX = attachment->getScaleX();
    m_followAttachmentScaleY = attachment->getScaleY();
}

void Slot::removeFollowAttachment() {
    if (m_followAttachment) {
        //m_skeleton->removeSlotFollowAttachment(m_followAttachment);
        m_followAttachment->removeFromParent();
        m_followAttachment->release();
        m_followAttachment = nullptr;
    }
}

cocos2d::Node* Slot::getFollowAttachmentChild() {
    return m_followAttachment;
}

bool Slot::isEnabledFollowAttachment() {
    return m_followAttachment != nullptr;
}

bool Slot::updateFollowAttachment() {
    if (m_followAttachment){
        //    if (m_followAttachment && m_followAttachment->getOpacity() > 0) {
        //        if (m_followAttachment->getParent() && m_followAttachment->getChildrenCount()) {
        //            Vector<Node*>&  children = m_followAttachment->getChildren();
        //            Node* actualNode = children.at(0);
        cocos2d::Node* actualNode = m_followAttachment;
        Bone& bbone = getBone();
        Bone* bone = &bbone;
        Skeleton *m_skeleton = &_skeleton;
        
//        if (m_skeleton->isFlipX()) {
//            m_followAttachment->setPositionX(-bone->getWorldX());
//        }
//        else {
            m_followAttachment->setPositionX(bone->getWorldX());
//        }
        
//        if (m_skeleton->isFlipY()) {
//            m_followAttachment->setPositionY(-bone->m_worldY);
//        }
//        else {
            m_followAttachment->setPositionY(bone->getWorldY());
//        }
        
        m_followAttachment->setRotationSkewX(-bone->getWorldRotationX());
        m_followAttachment->setRotationSkewY(-bone->getWorldRotationY());
        
        
        //                    m_followAttachment->setScaleX(bone->m_worldScaleX);
        //                    m_followAttachment->setScaleY(bone->m_worldScaleY);
//        m_followAttachment->setScaleX(m_followAttachmentScaleX * bone->m_worldScaleX);
//        m_followAttachment->setScaleY(m_followAttachmentScaleY * bone->m_worldScaleY);
        
        if (m_enabledFollowColor) {
            if (m_followAttachmentColor != actualNode->getColor()) {
                m_followAttachment->setColor(actualNode->getColor());
            }
            if (m_followAttachmentOpacity != actualNode->getOpacity()) {
                m_followAttachment->setOpacity(actualNode->getOpacity());
            }
            
            cocos2d::Color3B color = cocos2d::Color3B(255,255,255);//m_followAttachment->getColor();
            GLubyte opacity = 255;//m_followAttachment->getOpacity();
            
            const cocos2d::Color4F& ownerColor = cocos2d::Color4F(m_skeleton->getColor().r, m_skeleton->getColor().g, m_skeleton->getColor().b, m_skeleton->getColor().a);
//            actualNode->setColor(Color3B(m_cr * ownerColor.r * color.r, m_cg * ownerColor.g * color.g, m_cb * ownerColor.b * color.b));
//            actualNode->setOpacity(m_ca * ownerColor.a * opacity);
            
            m_followAttachmentColor = actualNode->getColor();
            m_followAttachmentOpacity = actualNode->getOpacity();
        }
        
        return true;
        //        }
        //        else {
        //            removeFollowAttachment();
        //        }
    }
    return false;
}

void Slot::drawFollowAttachment(cocos2d::Renderer *renderer, const cocos2d::Mat4& transform, uint32_t flags) {
    if (m_followAttachment->getOpacity() > 0) {
        Bone& bbone = getBone();
        Bone* bone = &bbone;
        float sx = m_followAttachment->getScaleX();
        float sy = m_followAttachment->getScaleY();
        m_followAttachment->setScaleX(sx * bone->getWorldScaleX());
        m_followAttachment->setScaleY(sy * bone->getWorldScaleY());
        m_followAttachment->setLocalZOrder(100);
        //m_followAttachment->setPosition(10, 10);
        m_followAttachment->visit(renderer, transform, flags);
        m_followAttachment->setScaleX(sx);
        m_followAttachment->setScaleY(sy);
    }
}
