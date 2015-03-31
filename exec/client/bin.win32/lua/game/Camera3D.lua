
Camera3D = class ("Camera3D", function(fieldOfView, aspectRatio, nearPlane, farPlane)
    local node = cc.Camera:createPerspective(fieldOfView, aspectRatio, nearPlane, farPlane)
    node:setCascadeColorEnabled(true)
	  return node
end)

function Camera3D:ctor(fieldOfView, aspectRatio, nearPlane, farPlane)

end

function Camera3D.create(fieldOfView, aspectRatio, nearPlane, farPlane)
    local base = Camera3D.new(fieldOfView, aspectRatio, nearPlane, farPlane)
		return base
end

function Camera3D:onTranslate(offset)
		local cameraPos = self:getPosition3D()
    cameraPos.x = cameraPos.x + offset.x
    cameraPos.z = cameraPos.z + offset.z
    self:setPosition3D(cameraPos)
end

function Camera3D:onRotation(touch)
		local prelocation = touch:getPreviousLocationInView()
    local location = touch:getLocationInView()

		local rotation3D = self:getRotation3D()
    if prelocation.x < location.x then rotation3D.y = rotation3D.y - 1 end
    if prelocation.x > location.x then rotation3D.y = rotation3D.y + 1 end
    if (prelocation.y < location.y and rotation3D.x > -60) then rotation3D.x = rotation3D.x - 1 end
    if (prelocation.y > location.y and rotation3D.x < 90) then rotation3D.x = rotation3D.x + 1 end

    self:setRotation3D(rotation3D)
end

function Camera3D:onZoom()

end

function Camera3D:translateScreen2World(location)
    local nearP = cc.vec3(location.x, location.y, -1.0)
    local farP  = cc.vec3(location.x, location.y, 1.0)
                
    local size = cc.Director:getInstance():getWinSize()
    nearP = self:unproject(size, nearP, nearP)
    farP  = self:unproject(size, farP, farP)
            
    local dir = cc.vec3(farP.x - nearP.x, farP.y - nearP.y, farP.z - nearP.z)
    local ndd = dir.x * 0 + dir.y * 1 + dir.z * 0
    local ndo = nearP.x * 0 + nearP.y * 1 + nearP.z * 0
    local dist = (0 - ndo) / ndd
    local worldPos = cc.vec3(nearP.x + dist * dir.x, nearP.y + dist * dir.y, nearP.z + dist * dir.z)
    return worldPos
end
