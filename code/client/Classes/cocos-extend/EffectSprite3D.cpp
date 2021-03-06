/****************************************************************************
Copyright (c) 2012 cocos2d-x.org
Copyright (c) 2013-2014 Chukong Technologies Inc.

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/

#include "EffectSprite3D.h"
#include "base/CCAsyncTaskPool.h"
#include "3d/CCAnimation3D.h"
#include "3d/CCAnimate3D.h"
#include "3d/CCAttachNode.h"
#include "3d/CCRay.h"
#include "3d/CCSprite3D.h"
#include "renderer/CCVertexIndexBuffer.h"
#include "DrawNode3D.h"
#include <algorithm>


static int tuple_sort(const std::tuple<ssize_t, Effect3D*, CustomCommand> &tuple1, const std::tuple<ssize_t, Effect3D*, CustomCommand> &tuple2)
{
	return std::get<0>(tuple1) < std::get<0>(tuple2);
}

EffectSprite3D* EffectSprite3D::createFromObjFileAndTexture(const std::string &objFilePath, const std::string &textureFilePath)
{
	auto sprite = new (std::nothrow) EffectSprite3D();
	if (sprite && sprite->initWithFile(objFilePath))
	{
		sprite->autorelease();
		if (textureFilePath.size() > 0)
			sprite->setTexture(textureFilePath);
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}

EffectSprite3D* EffectSprite3D::create(const std::string &path)
{
	if (path.length() < 4)
		CCASSERT(false, "improper name specified when creating Sprite3D");

	auto sprite = new (std::nothrow) EffectSprite3D();
	if (sprite && sprite->initWithFile(path))
	{
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}

EffectSprite3D::EffectSprite3D()
: _defaultEffect(nullptr)
{

}

EffectSprite3D::~EffectSprite3D()
{
	for (auto effect : _effects)
	{
		CC_SAFE_RELEASE_NULL(std::get<1>(effect));
	}
	CC_SAFE_RELEASE(_defaultEffect);
}

void EffectSprite3D::setEffect3D(Effect3D *effect)
{
	if (_defaultEffect == effect) return;
	CC_SAFE_RETAIN(effect);
	CC_SAFE_RELEASE(_defaultEffect);
	_defaultEffect = effect;
}

void EffectSprite3D::addEffect(Effect3DOutline* effect, ssize_t order)
{
	if (nullptr == effect) return;
	effect->retain();
	effect->setTarget(this);

	_effects.push_back(std::make_tuple(order, effect, CustomCommand()));

	std::sort(std::begin(_effects), std::end(_effects), tuple_sort);
}

const std::string Effect3DOutline::_vertShaderFile = "Shaders3D/OutLine.vert";
const std::string Effect3DOutline::_fragShaderFile = "Shaders3D/OutLine.frag";
const std::string Effect3DOutline::_keyInGLProgramCache = "Effect3DLibrary_Outline";

const std::string Effect3DOutline::_vertSkinnedShaderFile = "Shaders3D/SkinnedOutline.vert";
const std::string Effect3DOutline::_fragSkinnedShaderFile = "Shaders3D/OutLine.frag";
const std::string Effect3DOutline::_keySkinnedInGLProgramCache = "Effect3DLibrary_Outline";
GLProgram* Effect3DOutline::getOrCreateProgram(bool isSkinned /* = false */)
{
	if (isSkinned)
	{
		auto program = GLProgramCache::getInstance()->getGLProgram(_keySkinnedInGLProgramCache);
		if (program == nullptr)
		{
			program = GLProgram::createWithFilenames(_vertSkinnedShaderFile, _fragSkinnedShaderFile);
			GLProgramCache::getInstance()->addGLProgram(program, _keySkinnedInGLProgramCache);
		}
		return program;
	}
	else
	{
		auto program = GLProgramCache::getInstance()->getGLProgram(_keyInGLProgramCache);
		if (program == nullptr)
		{
			program = GLProgram::createWithFilenames(_vertShaderFile, _fragShaderFile);
			GLProgramCache::getInstance()->addGLProgram(program, _keyInGLProgramCache);
		}
		return program;
	}

}

Effect3DOutline* Effect3DOutline::create()
{
	Effect3DOutline* effect = new (std::nothrow) Effect3DOutline();
	if (effect && effect->init())
	{
		effect->autorelease();
		return effect;
	}
	else
	{
		CC_SAFE_DELETE(effect);
		return nullptr;
	}
}

bool Effect3DOutline::init()
{

	return true;
}

Effect3DOutline::Effect3DOutline()
: _outlineColor(1, 1, 1)
, _outlineWidth(1.0f)
, _sprite(nullptr)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_WP8 || CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	_backToForegroundListener = EventListenerCustom::create(EVENT_RENDERER_RECREATED,
		[this](EventCustom*)
	{
		auto glProgram = _glProgramState->getGLProgram();
		glProgram->reset();
		glProgram->initWithFilenames(_vertShaderFile, _fragShaderFile);
		glProgram->link();
		glProgram->updateUniforms();
	}
	);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(_backToForegroundListener, -1);
#endif
}

Effect3DOutline::~Effect3DOutline()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_WP8 || CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	Director::getInstance()->getEventDispatcher()->removeEventListener(_backToForegroundListener);
#endif
}

void Effect3DOutline::setOutlineColor(const Vec3& color)
{
	if (_outlineColor != color)
	{
		_outlineColor = color;
		if (_glProgramState)
			_glProgramState->setUniformVec3("OutLineColor", _outlineColor);
	}
}

void Effect3DOutline::setOutlineWidth(float width)
{
	if (_outlineWidth != width)
	{
		_outlineWidth = width;
		if (_glProgramState)
			_glProgramState->setUniformFloat("OutlineWidth", _outlineWidth);
	}
}

void Effect3DOutline::setTarget(EffectSprite3D *sprite)
{
	CCASSERT(nullptr != sprite && nullptr != sprite->getMesh(), "Error: Setting a null pointer or a null mesh EffectSprite3D to Effect3D");

	if (sprite != _sprite)
	{
		GLProgram* glprogram;
		if (!sprite->getMesh()->getSkin())
			glprogram = GLProgram::createWithFilenames(_vertShaderFile, _fragShaderFile);
		else
			glprogram = GLProgram::createWithFilenames(_vertSkinnedShaderFile, _fragSkinnedShaderFile);

		_glProgramState = GLProgramState::create(glprogram);

		_glProgramState->retain();
		_glProgramState->setUniformVec3("OutLineColor", _outlineColor);
		_glProgramState->setUniformFloat("OutlineWidth", _outlineWidth);


		_sprite = sprite;

		auto mesh = sprite->getMesh();
		long offset = 0;
		for (auto i = 0; i < mesh->getMeshVertexAttribCount(); i++)
		{
			auto meshvertexattrib = mesh->getMeshVertexAttribute(i);

			_glProgramState->setVertexAttribPointer(s_attributeNames[meshvertexattrib.vertexAttrib],
				meshvertexattrib.size,
				meshvertexattrib.type,
				GL_FALSE,
				mesh->getVertexSizeInBytes(),
				(void*)offset);
			offset += meshvertexattrib.attribSizeBytes;
		}

		Color4F color(_sprite->getDisplayedColor());
		color.a = _sprite->getDisplayedOpacity() / 255.0f;
		_glProgramState->setUniformVec4("u_color", Vec4(color.r, color.g, color.b, color.a));
	}

}

static void MatrixPalleteCallBack(GLProgram* glProgram, Uniform* uniform, int paletteSize, const float* palette)
{
	glUniform4fv(uniform->location, (GLsizei)paletteSize, (const float*)palette);
}

void Effect3DOutline::draw(const Mat4 &transform)
{
	//draw
	Color4F color(_sprite->getDisplayedColor());
	color.a = _sprite->getDisplayedOpacity() / 255.0f;
	_glProgramState->setUniformVec4("u_color", Vec4(color.r, color.g, color.b, color.a));
	if (_sprite && _sprite->getMesh())
	{
		glEnable(GL_CULL_FACE);
		glCullFace(GL_FRONT);
		glEnable(GL_DEPTH_TEST);

		auto mesh = _sprite->getMesh();
		glBindBuffer(GL_ARRAY_BUFFER, mesh->getVertexBuffer());

		auto skin = _sprite->getMesh()->getSkin();
		if (_sprite && skin)
		{
			auto function = std::bind(MatrixPalleteCallBack, std::placeholders::_1, std::placeholders::_2,
				skin->getMatrixPaletteSize(), (float*)skin->getMatrixPalette());
			_glProgramState->setUniformCallback("u_matrixPalette", function);
		}

		if (_sprite)
			_glProgramState->apply(transform);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->getIndexBuffer());
		glDrawElements(mesh->getPrimitiveType(), (GLsizei)mesh->getIndexCount(), mesh->getIndexFormat(), 0);
		CC_INCREMENT_GL_DRAWN_BATCHES_AND_VERTICES(1, mesh->getIndexCount());

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glDisable(GL_DEPTH_TEST);
		glCullFace(GL_BACK);
		glDisable(GL_CULL_FACE);
	}
}

void EffectSprite3D::draw(cocos2d::Renderer *renderer, const cocos2d::Mat4 &transform, uint32_t flags)
{
	for (auto &effect : _effects)
	{
		if (std::get<0>(effect) >= 0)
			break;
		CustomCommand &cc = std::get<2>(effect);
		cc.func = CC_CALLBACK_0(Effect3D::draw, std::get<1>(effect), transform);
		renderer->addCommand(&cc);

	}

	if (!_defaultEffect)
	{
		Sprite3D::draw(renderer, transform, flags);
	}
	else
	{
		_command.init(_globalZOrder, transform, flags);
		_command.func = CC_CALLBACK_0(Effect3D::draw, _defaultEffect, transform);
		renderer->addCommand(&_command);
	}

	for (auto &effect : _effects)
	{
		if (std::get<0>(effect) <= 0)
			continue;
		CustomCommand &cc = std::get<2>(effect);
		cc.func = CC_CALLBACK_0(Effect3D::draw, std::get<1>(effect), transform);
		renderer->addCommand(&cc);

	}
}
