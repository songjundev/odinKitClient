
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

function Actor:createModel3D(file)
    self._sprite3d = cc.Sprite3D:create(file)
    self:addChild(self._sprite3d)
end

function Actor:playAnimation(name, action, loop)
    if self._curAnimation ~= name then
        self._sprite3d:stopAllActions()
        if loop then
            self._sprite3d:runAction(cc.RepeatForever:create(action))
        else
            self._sprite3d:runAction(action)
        end
        self._curAnimation = name
    end
end

return Actor