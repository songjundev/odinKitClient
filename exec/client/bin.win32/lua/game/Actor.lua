
Actor = class ("Actor", function()
    local node = cc.Node:create()
    node:setCascadeColorEnabled(true)
	  return node
end)

function Actor:ctor()

end

function Actor.create()
    local base = Actor.new()
		return base
end

function Actor:init3D(file)
    self._sprite3d = cc.Sprite3D:create(file)
    --self._sprite3d:addEffect(cc.V3(0,0,0),CelLine, -1)
    self:addChild(self._sprite3d)
    --self:setDefaultEqt()
end

return Actor