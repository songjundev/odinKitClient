require "lua.cocos.init"
require "lua.game.funcs"

-- for CCLuaEngine traceback
function __G__TRACKBACK__(msg)
    cclog("----------------------------------------")
    cclog("LUA ERROR: " .. tostring(msg) .. "\n")
    cclog(debug.traceback())
    cclog("----------------------------------------")
    return msg
end

local function main()
    collectgarbage("collect")
    -- avoid memory leak
    collectgarbage("setpause", 200)
    collectgarbage("setstepmul", 10000)

    cc.FileUtils:getInstance():addSearchPath("lua/game")
    cc.FileUtils:getInstance():addSearchPath("lua/game/actors")
    cc.FileUtils:getInstance():addSearchPath("res")
    
    --show frame
    cc.Director:getInstance():setDisplayStats(true)
    
    --adaptation
    local pEGLView = cc.Director:getInstance():getOpenGLView()
    local frameSize = pEGLView:getFrameSize()
    local winSize = {width=1136,height=640}

    local widthRate = frameSize.width/winSize.width
    local heightRate = frameSize.height/winSize.height
    resolutionRate = nil

    if widthRate > heightRate then
        pEGLView:setDesignResolutionSize(winSize.width,
            winSize.height*heightRate/widthRate, 1)
            resolutionRate = heightRate/widthRate
    else
        pEGLView:setDesignResolutionSize(winSize.width*widthRate/heightRate, winSize.height,
            1)
            resolutionRate = widthRate/heightRate
    end

    --create scene
    local scene = require("TownScene")
    --local scene = require("ChooseRoleScene")
    local activateGameScene = scene.create()
    --activateGameScene:playBgMusic()
    
    
    if cc.Director:getInstance():getRunningScene() then
        cc.Director:getInstance():replaceScene(activateGameScene)
    else
        cc.Director:getInstance():runWithScene(activateGameScene)
    end

end


local status, msg = xpcall(main, __G__TRACKBACK__)
if not status then
    error(msg)
end
