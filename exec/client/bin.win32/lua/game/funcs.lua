
-- cclog
cclog = function(...)
    print(string.format(...))
end

function createAnimation(file, begin, finish, speed)
    local animation3d = cc.Animation3D:create(file)
    local animate3d = cc.Animate3D:create(animation3d, begin/30,(finish-begin)/30)
    animate3d:setSpeed(speed)
    animate3d:retain()
    return animate3d
end