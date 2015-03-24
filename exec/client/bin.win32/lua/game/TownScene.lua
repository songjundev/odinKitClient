require "funcs"
require "Actor"
require "defines"

local TownScene  = class("TownScene",function()
	  return cc.Scene:create()
end)

function TownScene:ctor()
    self.visibleSize = cc.Director:getInstance():getVisibleSize()
    self.origin = cc.Director:getInstance():getVisibleOrigin()
end

function TownScene.create()
    local scene = TownScene.new()
    
    scene:initCamera()

    scene:createLayer()

    return scene
end

function TownScene:initCamera()
		local camera_1 = cc.Camera:createOrthographic(960,640,0,1000)
		camera_1:setCameraFlag(cc.CameraFlag.USER1)
		self:addChild(camera_1)
		
		self._camera3d = cc.Camera:createPerspective(60, self.visibleSize.width/self.visibleSize.height, 1, 2000)
		self._camera3d:setCameraFlag(cc.CameraFlag.USER2)
		self._camera3d:setPosition3D(cc.vec3(self.visibleSize.width/2, self.visibleSize.height/2, 100))
		self._camera3d:setRotation3D(cc.vec3(-10, 0, 0))
    self:addChild(self._camera3d)
end

function TownScene:createLayer()
    
    --create layer
    self.layer = cc.Layer:create()
    
    --create Background
    self:addBackground()

    --create map
    self:addMap()
    
    self:addHero()
    
    self:addChild(self.layer)
    
    self:setEventListener()
end

function TownScene:addBackground()
		local background = cc.Sprite:create("chooseRole/cr_bk.jpg")
    background:setAnchorPoint(0.5,0.5)
    background:setPosition(self.origin.x + self.visibleSize.width/2, self.origin.y + self.visibleSize.height/2)
    background:setCameraMask(cc.CameraFlag.USER1)
    self.layer:addChild(background)
end

function TownScene:addMap()
		local file = "map/map001/map001.c3b"
		self._map = Actor.create()
		self._map:createModel3D(file)
    self._map:setTag(2)
    self._map:setRotation3D({x=0,y=0,z=0})
    self._map:setPosition3D({x=self.visibleSize.width*0.5,y=0,z=-180})  
    self._map:setScale(15)
    self._map:setCameraMask(cc.CameraFlag.USER2)
    self.layer:addChild(self._map)
end

function TownScene:addHero()
		self._hero = Actor.create()
		self._hero:createModel3D(Knight_model)
    self._hero:setTag(2)
    self._hero:setRotation3D({x=0,y=0,z=0})
    self._hero:setPosition3D({x=self.visibleSize.width*0.5,y=0,z=-180})  
    self._hero:setScale(15)
    self._hero:setCameraMask(cc.CameraFlag.USER2)
    self.layer:addChild(self._hero)
    
    self._hero:playAnimation("idle", Knight_action["idle"], true)
end

function TownScene:setEventListener()
    local listener = cc.EventListenerTouchAllAtOnce:create()
    listener:registerScriptHandler(function(touchs, event)
        if #touchs == 1 then
            --if self._cameraType == CameraType.FreeCamera then
                self:cameraRotation(touchs[1])
            --end
        end
    end, cc.Handler.EVENT_TOUCHES_MOVED)
    
    listener:registerScriptHandler(function(touchs, event)
        for i,v in ipairs(touchs) do
        		cclog("heroPos:"..self._hero:getPosition3D().x..","..self._hero:getPosition3D().y..","..self._hero:getPosition3D().z)
            local touch = v
            local location = touch:getLocationInView()

            local nearP = cc.vec3(location.x, location.y, -1.0)
            local farP  = cc.vec3(location.x, location.y, 1.0)
                
            local size = cc.Director:getInstance():getWinSize()
            nearP = self._camera3d:unproject(size, nearP, nearP)
            nearP.y = self._hero:getPosition3D().y
            --nearP.z = self._hero:getPosition3D().z
            cclog("nearP:"..nearP.x..","..nearP.y..","..nearP.z)
            self._hero:setPosition3D(nearP)
            
            --[[farP  = self._camera3d:unproject(size, farP, farP)
            cclog("heroPos:"..farP.x..","..farP.y..","..farP.z)
            
            local dir = cc.vec3(farP.x - nearP.x, farP.y - nearP.y, farP.z - nearP.z)
            local dist=0.0
            local ndd = dir.x * 0 + dir.y * 1 + dir.z * 0
            if ndd == 0 then
                dist=0.0
            end

            local ndo = nearP.x * 0 + nearP.y * 1 + nearP.z * 0
            dist= (0 - ndo) / ndd
            local heroPos =   cc.vec3(nearP.x + dist * dir.x, nearP.y + dist * dir.y, nearP.z + dist * dir.z)
            cclog("heroPos:"..self._hero:getPosition3D().x..","..self._hero:getPosition3D().y..","..self._hero:getPosition3D().z)
            self._hero:setPosition3D(heroPos)
            cclog("heroPos:"..heroPos.x..","..heroPos.y..","..heroPos.z)]]
        end
    end, cc.Handler.EVENT_TOUCHES_ENDED)

    local eventDispatcher = self:getEventDispatcher()
    eventDispatcher:addEventListenerWithSceneGraphPriority(listener, self)
end

function TownScene:heroMove(touch)
		local newPos = touch:getLocationInView()
		cclog("touch point:"..newPos.x..","..newPos.y)
		
		local transformMat = self._camera3d:getNodeToWorldTransform()
    local cameraDir = { x = -transformMat[9], y = -transformMat[10], z = -transformMat[11] }
    cameraDir = cc.vec3normalize(cameraDir)
    cameraDir.y = 0
    cclog("cameraDir:"..cameraDir.x..","..cameraDir.y..","..cameraDir.z)
    
    transformMat = self._camera3d:getNodeToWorldTransform()
    local cameraRightDir = { x = transformMat[1], y = transformMat[2], z = transformMat[3]}
    cameraRightDir = cc.vec3normalize(cameraRightDir)
    cameraRightDir.y = 0
    cclog("cameraRightDir:"..cameraRightDir.x..","..cameraRightDir.y..","..cameraRightDir.z)
    
    local heroPos = self._hero:getPosition3D()
    cclog("heroPos:"..heroPos.x..","..heroPos.y..","..heroPos.z)
    heroPos = {x = heroPos.x - cameraDir.x * newPos.y * 0.1, y = heroPos.y - cameraDir.y * newPos.y * 0.1, z = heroPos.z - cameraDir.z * newPos.y * 0.1}
    heroPos = {x = heroPos.x + cameraRightDir.x * newPos.x * 0.1, y = heroPos.y + cameraRightDir.y * newPos.x * 0.1, z = heroPos.z + cameraRightDir.z * newPos.x * 0.1}
    self._hero:setPosition3D(heroPos)
    cclog("heroPos:"..heroPos.x..","..heroPos.y..","..heroPos.z)
end

function TownScene:cameraRotation(touch)
		local rotation3D = self._camera3d:getRotation3D()
		
		local prelocation = touch:getPreviousLocationInView()
    local location = touch:getLocationInView()

    if prelocation.x < location.x then rotation3D.y = rotation3D.y - 1 end
    if prelocation.x > location.x then rotation3D.y = rotation3D.y + 1 end
    if (prelocation.y < location.y and rotation3D.x > -60) then rotation3D.x = rotation3D.x - 1 end
    if (prelocation.y > location.y and rotation3D.x < 90) then rotation3D.x = rotation3D.x + 1 end

    self._camera3d:setRotation3D(rotation3D)
end

function TownScene:cameraMove(touch)
		local prelocation = touch:getPreviousLocationInView()
    local location = touch:getLocationInView()
    local newPos = cc.p(prelocation.x - location.x, prelocation.y - location.y)

    local transformMat = self._camera3d:getNodeToWorldTransform()
    local cameraDir = { x = -transformMat[9], y = -transformMat[10], z = -transformMat[11] }
    cameraDir = cc.vec3normalize(cameraDir)
    cameraDir.y = 0

    transformMat = self._camera3d:getNodeToWorldTransform()
    local cameraRightDir = { x = transformMat[1], y = transformMat[2], z = transformMat[3]}
    cameraRightDir = cc.vec3normalize(cameraRightDir)
    cameraRightDir.y = 0

    local cameraPos = self._camera3d:getPosition3D()
    cameraPos = {x = cameraPos.x - cameraDir.x * newPos.y * 0.1, y = cameraPos.y - cameraDir.y * newPos.y * 0.1, z = cameraPos.z - cameraDir.z * newPos.y * 0.1}
    cameraPos = {x = cameraPos.x + cameraRightDir.x * newPos.x * 0.1, y = cameraPos.y + cameraRightDir.y * newPos.x * 0.1, z = cameraPos.z + cameraRightDir.z * newPos.x * 0.1}
    self._camera3d:setPosition3D(cameraPos)
    
    local heroPos = self._hero:getPosition3D()
    heroPos = {x = heroPos.x - cameraDir.x * newPos.y * 0.1, y = heroPos.y - cameraDir.y * newPos.y * 0.1, z = heroPos.z - cameraDir.z * newPos.y * 0.1}
    heroPos = {x = heroPos.x + cameraRightDir.x * newPos.x * 0.1, y = heroPos.y + cameraRightDir.y * newPos.x * 0.1, z = heroPos.z + cameraRightDir.z * newPos.x * 0.1}
    self._hero:setPosition3D(heroPos)
    self._hero:setRotation3D(cameraDir)
    self._hero:playAnimation("walk", Knight_action["walk"], true)
end

return TownScene