EventController = {}

EventController.EventType = {
    BLOOD_MINUS = "BLOOD_MINUS",
    REDUCE_SCORE = "REDUCE_SCORE",
    KNOCKED = "KNOCKED",
    KNOCKEDAOE = "KNOCKEDAOE",
    SPECIAL_PERSPECTIVE = "SPECIAL_PERSPECTIVE",
    SPECIAL_KNIGHT = "SPECIAL_KNIGHT",
    SPECIAL_ARCHER = "SPECIAL_ARCHER",
    SPECIAL_MAGE = "SPECIAL_MAGE",
    ANGRY_CHANGE = "ANGRY_CHANGE",
}

EventController.EventQueue = {}

--function EventController:new(o)  
--    o = o or {}  
--    setmetatable(o,self)  
--    self.__index = self  
--    return o  
--end  
--
--function EventController:getInstance()  
--    if self.instance == nil then  
--        self.instance = self:new()  
--    end  
--    return self.instance  
--end  

--need param eventType and callback function
function EventController:registerEvent(eventType,callback)
    --if param is valid
    if self.EventType[eventType] == nil or type(callback) ~= "function" then
        print("param is invalid")
        return
    end
    
    --add event to eventQueue
    if self.EventQueue[eventType] == nil then
        self.EventQueue[eventType] = {}
    end
    local index = table.getn(self.EventQueue[eventType])
    self.EventQueue[eventType][index+1] = callback
    
--    for i,v in pairs(self.EventQueue) do
--        print(table.getn(v))
--        for ii,vv in pairs(v) do
--            print(ii,vv)
--        end
--    end
--    print("----------------------------")
end

function EventController:handleEvent(eventType,param)
    --if param is valid
    if self.EventType[eventType] == nil then
        print("param is invalid")
        return
    end
    
    --callback
    if self.EventQueue[eventType] == nil then
        return
    end
    for i,v in pairs(self.EventQueue[eventType]) do
        v(param)
    end
end

function EventController:removeEvent(eventType,callback)
    --if param is valid
    if self.EventType[eventType] == nil or type(callback) ~= "function" then
        print("param is invalid")
        return
    end
    
    --remove callback
    for i,v in pairs(self.EventQueue[eventType]) do
        if callback == v then
            table.remove(self.EventQueue[eventType],i)
            return
        end
    end
end

return EventController
