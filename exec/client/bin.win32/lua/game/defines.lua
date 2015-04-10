-- init model animations=============================
Knight_model = "person/knight/knight.c3b"
Knight_action = {
		idle = createAnimation(Knight_model,267,283,0.7),
    walk = createAnimation(Knight_model,227,246,0.7),
    attack1 = createAnimation(Knight_model,103,129,0.7),
    attack2 = createAnimation(Knight_model,130,154,0.7),
    specialattack1 = createAnimation(Knight_model,160,190,0.3),
    specialattack2 = createAnimation(Knight_model,191,220,0.4),
    defend = createAnimation(Knight_model,92,96,0.7),
    knocked = createAnimation(Knight_model,254,260,0.7),
    dead = createAnimation(Knight_model,0,77,1)
}

Dragon_model = "person/dragon/dragon.c3b"
Dragon_action = {
    idle = createAnimation(Dragon_model,0,24,0.7),
    knocked = createAnimation(Dragon_model,30,37,0.7),
    dead = createAnimation(Dragon_model,42,80,1),
    attack1 = createAnimation(Dragon_model,85,100,0.7),
    attack2 = createAnimation(Dragon_model,100,115,0.7),
    walk = createAnimation(Dragon_model,120,140,1)
}


cc.SpriteFrameCache:getInstance():addSpriteFrames("FX/FX.plist")