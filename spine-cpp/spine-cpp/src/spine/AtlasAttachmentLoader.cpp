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

#include <spine/AtlasAttachmentLoader.h>
#include <spine/Skin.h>
#include <spine/RegionAttachment.h>
#include <spine/MeshAttachment.h>
#include <spine/BoundingBoxAttachment.h>
#include <spine/PathAttachment.h>
#include <spine/PointAttachment.h>
#include <spine/ClippingAttachment.h>

#include "cocos2d.h"
#include <spine/Atlas.h>
USING_NS_CC;

namespace spine {
RTTI_IMPL(AtlasAttachmentLoader, AttachmentLoader)

AtlasAttachmentLoader::AtlasAttachmentLoader(Atlas *atlas) : AttachmentLoader(){
}

RegionAttachment *AtlasAttachmentLoader::newRegionAttachment(Skin &skin, const String &name, const String &path) {
	SP_UNUSED(skin);

	//AtlasRegion *regionP = findRegion(path);
	//if (!regionP) return NULL;
    std::string spritePath = std::string(path.buffer()) + ".png";
    Sprite* region = Sprite::createWithSpriteFrameName(spritePath);
    if(!region) {
        return NULL;
    }
    const Size& regionSize = region->getContentSize();
    const V3F_C4B_T2F_Quad spriteQuad = region->getQuad();
	//AtlasRegion &region = *regionP;

	RegionAttachment *attachmentP = new(__FILE__, __LINE__) RegionAttachment(name);

	RegionAttachment &attachment = *attachmentP;
	attachment.setRendererObject(region);
	attachment.setUVs(spriteQuad.bl.texCoords.u, spriteQuad.tr.texCoords.v, spriteQuad.tr.texCoords.u, spriteQuad.bl.texCoords.v, 0);
	attachment._regionOffsetX = 0;
	attachment._regionOffsetY = 0;
	attachment._regionWidth = (float)regionSize.width;
	attachment._regionHeight = (float)regionSize.height;
	attachment._regionOriginalWidth = (float)regionSize.width;
	attachment._regionOriginalHeight = (float)regionSize.height;
	return attachmentP;
}

MeshAttachment *AtlasAttachmentLoader::newMeshAttachment(Skin &skin, const String &name, const String &path) {
	SP_UNUSED(skin);

	//AtlasRegion *regionP = findRegion(path);
	//if (!regionP) return NULL;
    std::string spritePath = std::string(path.buffer()) + ".png";
    Sprite* region = Sprite::createWithSpriteFrameName(spritePath);
    if(!region) {
        return NULL;
    }
    const Size& regionSize = region->getContentSize();
    const V3F_C4B_T2F_Quad spriteQuad = region->getQuad();
	//AtlasRegion &region = *regionP;

	MeshAttachment *attachmentP = new(__FILE__, __LINE__) MeshAttachment(name);

	MeshAttachment &attachment = *attachmentP;
	attachment.setRendererObject(region);
	attachment._regionU = spriteQuad.bl.texCoords.u;
	attachment._regionV = spriteQuad.tr.texCoords.v;
	attachment._regionU2 = spriteQuad.tr.texCoords.u;
	attachment._regionV2 =spriteQuad.bl.texCoords.v;
	attachment._regionRotate = 0;
	attachment._regionOffsetX = region->getOffsetPosition().x;
	attachment._regionOffsetY = region->getOffsetPosition().y;
	attachment._regionWidth = (float)regionSize.width;
	attachment._regionHeight = (float)regionSize.height;
	attachment._regionOriginalWidth = (float)regionSize.width;
	attachment._regionOriginalHeight = (float)regionSize.height;

	return attachmentP;
}

BoundingBoxAttachment *AtlasAttachmentLoader::newBoundingBoxAttachment(Skin &skin, const String &name) {
	SP_UNUSED(skin);
	return new(__FILE__, __LINE__) BoundingBoxAttachment(name);
}

PathAttachment *AtlasAttachmentLoader::newPathAttachment(Skin &skin, const String &name) {
	SP_UNUSED(skin);
	return new(__FILE__, __LINE__) PathAttachment(name);
}

PointAttachment *AtlasAttachmentLoader::newPointAttachment(Skin &skin, const String &name) {
	SP_UNUSED(skin);
	return new(__FILE__, __LINE__) PointAttachment(name);
}

ClippingAttachment *AtlasAttachmentLoader::newClippingAttachment(Skin &skin, const String &name) {
	SP_UNUSED(skin);
	return new(__FILE__, __LINE__) ClippingAttachment(name);
}

void AtlasAttachmentLoader::configureAttachment(Attachment* attachment) {
	SP_UNUSED(attachment);
}

AtlasRegion *AtlasAttachmentLoader::findRegion(const String &name) {
	return _atlas->findRegion(name);
}

}
