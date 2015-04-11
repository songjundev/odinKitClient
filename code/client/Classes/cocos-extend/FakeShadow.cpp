#include "FakeShadow.h"

using namespace cocos2d;

FakeShadow* FakeShadow::create(Sprite3D* plane)
{
	auto state = new (std::nothrow) FakeShadow();
	if (state)
	{
		// use custom shader
		auto shader = GLProgram::createWithFilenames("shadow/simple_shadow.vert", "shadow/simple_shadow.frag");
		state->init(shader);
		state->autorelease();

		//pass mesh's attribute to shader
		long offset = 0;
		auto attributeCount = plane->getMesh()->getMeshVertexAttribCount();
		for (auto i = 0; i < attributeCount; i++) {
			auto meshattribute = plane->getMesh()->getMeshVertexAttribute(i);
			state->setVertexAttribPointer(s_attributeNames[meshattribute.vertexAttrib],
				meshattribute.size,
				meshattribute.type,
				GL_FALSE,
				plane->getMesh()->getVertexSizeInBytes(),
				(GLvoid*)offset);
			offset += meshattribute.attribSizeBytes;
		}
		state->setUniformMat4("u_model_matrix", plane->getNodeToWorldTransform());

		//create shadow texture
		auto shadowTexture = Director::getInstance()->getTextureCache()->addImage("shadow/shadowCircle.png");
		Texture2D::TexParams tRepeatParams;//set texture parameters
		tRepeatParams.magFilter = GL_LINEAR;
		tRepeatParams.minFilter = GL_LINEAR;
		tRepeatParams.wrapS = GL_CLAMP_TO_EDGE;
		tRepeatParams.wrapT = GL_CLAMP_TO_EDGE;
		shadowTexture->setTexParameters(tRepeatParams);
		state->setUniformTexture("u_shadowTexture", shadowTexture);

		return state;
	}

	CC_SAFE_DELETE(state);
	return nullptr;
}

void FakeShadow::setPosition3D(const Vec3& position)
{
	this->setUniformVec3("u_target_pos", position);
}
