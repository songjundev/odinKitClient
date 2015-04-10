
Actor = class ("Actor", function(file)
    local node = cc.Sprite3D:create(file)
    node:setCascadeColorEnabled(true)
	  return node
end)

function Actor:ctor(file)
		self.schedulerMove = 0
end

function Actor.create(file)
    local base = Actor.new(file)
		return base
end

--[[function Actor:createShadow()
    self._circle = cc.Sprite:createWithSpriteFrameName("shadow.png")
    self._circle:setScale(0.1)
		self._circle:setOpacity(255*0.7)
		self:addChild(self._circle)
end]]

function Actor:createShadow(plane)
    -- use custom shader
    local shader = cc.GLProgram:createWithFilenames("shadow/simple_shadow.vert","shadow/simple_shadow.frag")
    local state = cc.GLProgramState:create(shader)
    plane:setGLProgramState(state)
    
    -- pass mesh's attribute to shader
    local offset = 0
    local attributeCount = plane:getMesh():getMeshVertexAttribCount()
    for i=0, attributeCount, 1 do
        local meshattribute = plane:getMesh():getMeshVertexAttribute(i)
        state:setVertexAttribPointer(s_attributeNames[meshattribute.vertexAttrib], meshattribute.size, meshattribute.type, _G.GL_FALSE, plane:getMesh():getVertexSizeInBytes(), offset)
        offset = offset + meshattribute.attribSizeBytes
    end
    state:setUniformMat4("u_model_matrix", plane:getNodeToWorldTransform())
end

function Actor:setCamera(camera)
		self._camera3d = camera
end

function Actor:playAnimation(name, action, loop)
    if self._curAnimation ~= name then
        self:stopAllActions()
        if loop then
            self:runAction(cc.RepeatForever:create(action))
        else
            self:runAction(action)
        end
        self._curAnimation = name
    end
end

function Actor:startMove(point)
		self._targetPos = point
		self:playAnimation("walk", Knight_action["walk"], true)
		
		cc.Director:getInstance():getScheduler():unscheduleScriptEntry(self.schedulerMove)
    self.schedulerMove = cc.Director:getInstance():getScheduler():scheduleScriptFunc(function(dt)
        self:move(dt)
    end, 0.0, false)
end

function Actor:move(dt)
		local speed = 100.0
		local curPos = self:getPosition3D()
    local newFaceDir = {x = self._targetPos.x - curPos.x, y = self._targetPos.y - curPos.y, z = self._targetPos.z - curPos.z }
    newFaceDir = cc.vec3normalize(newFaceDir)
    local offset = { x = newFaceDir.x * speed * dt, y = newFaceDir.y * speed * dt, z = newFaceDir.z * speed * dt  }
    curPos = { x = curPos.x + offset.x, y = curPos.y + offset.y, z = curPos.z + offset.z}
    self:rotateModel(self._targetPos)
    self:setPosition3D(curPos)
    self._camera3d:onTranslate(offset)
    
    if vecEqual(self:getPosition3D(), self._targetPos) then
    		cc.Director:getInstance():getScheduler():unscheduleScriptEntry(self.schedulerMove)
    		self:playAnimation("idle", Knight_action["idle"], true)
    end
end

function Actor:rotateModel(targetPos)
		local curPos = self:getPosition3D()
    local newFaceDir = {x = targetPos.x - curPos.x, y = targetPos.y - curPos.y, z = targetPos.z - curPos.z }
    newFaceDir = cc.vec3normalize(newFaceDir)

    local matTransform = self:getNodeToWorldTransform()
    local up = {x = matTransform[5], y = matTransform[6] ,z = matTransform[7] }
    up = cc.vec3normalize(up)
    local right = {x = -newFaceDir.y * up.z + newFaceDir.z * up.y, y = -newFaceDir.z * up.x + newFaceDir.x * up.z, z = -newFaceDir.x * up.y + newFaceDir.y * up.x}
    right = cc.vec3normalize(right)

    local pos = cc.vec3(0, 0, 0)
    local mat = {}
    mat[1] = right.x
    mat[2] = right.y
    mat[3] = right.z
    mat[4] = 0.0
    
    mat[5] = up.x
    mat[6] = up.y
    mat[7] = up.z
    mat[8] = 0.0
    
    mat[9]  = newFaceDir.x
    mat[10] = newFaceDir.y
    mat[11] = newFaceDir.z
    mat[12] = 0.0
    
    mat[13] = pos.x
    mat[14] = pos.y
    mat[15] = pos.z
    mat[16] = 1.0
    self:setAdditionalTransform(mat)
end

return Actor