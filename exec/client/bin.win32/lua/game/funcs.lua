
-- cclog
cclog = function(...)
    print(string.format(...))
end

function vecEqual(vec1, vec2)
		return ((vec1.x-vec2.x)<1.0 and (vec1.y-vec2.y)<1.0 and (vec1.z-vec2.z)<1.0 and (vec2.x-vec1.x)<1.0 and (vec2.y-vec1.y)<1.0 and (vec2.z-vec1.z)<1.0)
end

function createAnimation(file, begin, finish, speed)
    local animation3d = cc.Animation3D:create(file)
    local animate3d = cc.Animate3D:create(animation3d, begin/30,(finish-begin)/30)
    animate3d:setSpeed(speed)
    animate3d:retain()
    return animate3d
end