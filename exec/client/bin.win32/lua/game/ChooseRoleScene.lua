require "Actor"

local ChooseRoleScene  = class("ChooseRoleScene",function()
	  return cc.Scene:create()
end)

function ChooseRoleScene:ctor()
    self.visibleSize = cc.Director:getInstance():getVisibleSize()
    self.origin = cc.Director:getInstance():getVisibleOrigin()
end

function ChooseRoleScene.create()
    local scene = ChooseRoleScene.new()
    
    scene:initCamera()

    scene:createLayer()

    return scene
end

function ChooseRoleScene:initCamera()
		local camera_1 = cc.Camera:createOrthographic(960,640,0,1000)
		camera_1:setCameraFlag(cc.CameraFlag.USER1)
		self:addChild(camera_1)
		
		self._camera3d = cc.Camera:createPerspective(60, self.visibleSize.width/self.visibleSize.height, 1, 2000)
		self._camera3d:setCameraFlag(cc.CameraFlag.USER2)
		self._camera3d:setPosition3D(cc.vec3(self.visibleSize.width/2, self.visibleSize.height/2, 100))
		self._camera3d:setRotation3D(cc.vec3(-10, 0, 0))
    self:addChild(self._camera3d)
end

function ChooseRoleScene:createLayer()
    
    --create layer
    self.layer = cc.Layer:create()
    
    --create Background
    self:addBackground()

    --create heros
    self:addHeros()
    
    --create arrow
    --self:addButton()
    
    --create bag
    --self:addBag()
    
    self:addChild(self.layer)
end

function ChooseRoleScene:addBackground()
		local background = cc.Sprite:create("chooseRole/cr_bk.jpg")
    background:setAnchorPoint(0.5,0.5)
    background:setPosition(self.origin.x + self.visibleSize.width/2, self.origin.y + self.visibleSize.height/2)
    background:setCameraMask(cc.CameraFlag.USER1)
    self.layer:addChild(background)
end

function ChooseRoleScene:addHeros()
		local file = "model/knight/knight.c3b"
		local knight = Actor.create()
		knight:init3D(file)
    knight:setTag(2)
    knight:setRotation3D({x=0,y=0,z=0})
    knight:setPosition3D({x=self.visibleSize.width*0.5,y=self.visibleSize.height*0.35,z=-180})  
    knight:setScale(15)
    knight:setCameraMask(cc.CameraFlag.USER2)
    self.layer:addChild(knight)
end

return ChooseRoleScene