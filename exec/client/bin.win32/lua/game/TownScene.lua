require "funcs"
require "Actor"
require "defines"
require "Camera3D"

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
		
		self._camera3d = Camera3D.create(60, self.visibleSize.width/self.visibleSize.height, 1, 2000)
		self._camera3d:setCameraFlag(cc.CameraFlag.USER2)
		self._camera3d:setPosition3D(cc.vec3(self.visibleSize.width/2, self.visibleSize.height/3, 100))
		self._camera3d:setRotation3D(cc.vec3(-20, 0, 0))
    self:addChild(self._camera3d)
end

function TownScene:createLayer()
    
    --create layer
    self.layer = cc.Layer:create()
    
    --create Background
    self:addBackground()

    --create map
    self:addMap3D()
    
    self:addHero()
    self:addMonster()
    
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
		local file = "map/map01/map02.tmx"
		
		self._map = cc.TMXTiledMap:create(file)
		--self._map:setAnchorPoint(0.5,0.5)
		--self._map:setPosition(self.origin.x + self.visibleSize.width/2, self.origin.y + self.visibleSize.height/2)
		self._map:setCameraMask(cc.CameraFlag.USER1)
		self.layer:addChild(self._map)
end

function TownScene:addMap3D()
		local file = "map/map001/map001.c3b"
		self._map = Actor.create(file)
    self._map:setTag(2)
    self._map:setRotation3D({x=0,y=0,z=0})
    self._map:setPosition3D({x=self.visibleSize.width*0.5,y=0,z=-180})  
    self._map:setScale(15)
    self._map:setCameraMask(cc.CameraFlag.USER2)
    self.layer:addChild(self._map)
end

function TownScene:addHero()
		self._hero = Actor.create(Knight_model)
    self._hero:setTag(2)
    self._hero:setRotation3D({x=0,y=0,z=0})
    self._hero:setPosition3D({x=300,y=0,z=-300})
    self._hero:setScale(15)
    self._hero:setCamera(self._camera3d)
    self._hero:setCameraMask(cc.CameraFlag.USER2)
    self.layer:addChild(self._hero)
    
    self._hero:playAnimation("idle", Knight_action["idle"], true)
end

function TownScene:addMonster()
		self._monster = Actor.create(Dragon_model)
    self._monster:setTag(2)
    self._monster:setRotation3D({x=0,y=0,z=0})
    self._monster:setPosition3D({x=400,y=0,z=-300})
    self._monster:setScale(15)
    self._monster:setCamera(self._camera3d)
    self._monster:setCameraMask(cc.CameraFlag.USER2)
    self.layer:addChild(self._monster)
    
    self._monster:playAnimation("idle", Dragon_action["idle"], true)
end

function TownScene:setEventListener()
    local listener = cc.EventListenerTouchAllAtOnce:create()
    --[[listener:registerScriptHandler(function(touchs, event)
        if #touchs == 1 then
            self._camera3d:onRotation(touchs[1])
        end
    end, cc.Handler.EVENT_TOUCHES_MOVED)]]
    
    listener:registerScriptHandler(function(touchs, event)
        for i,v in ipairs(touchs) do
            self:sceneMove(v)
        end
    end, cc.Handler.EVENT_TOUCHES_ENDED)

    local eventDispatcher = self:getEventDispatcher()
    eventDispatcher:addEventListenerWithSceneGraphPriority(listener, self)
end

function TownScene:sceneMove(touch)
    local location = touch:getLocationInView()
    local targetPos = self._camera3d:translateScreen2World(location)

    self._hero:startMove(targetPos)
end

function TownScene:selectTarget(touch)
		local location = touch:getLocationInView()
    local targetPos = self._camera3d:translateScreen2World(location)
    
		if (self._monster:getAABB():containPoint(targetPos)) then
				return true
		end
		
		return false
end

return TownScene