local ball
local camera

local LEFT = 263
local RIGHT = 262
local UP = 265
local DOWN = 264

local vx = 0.0
local vz = 0.0

local ballvy = -1.0

function init()
   camera = couch.Camera()
   camera:MakeCurrent()
   ball = couch.Ball()
   ball:SetupMesh()
   couch.AddMeshToList(ball)
   ball1 = couch.Ball()
   ball1:SetupMesh()
   couch.AddMeshToList(ball1)

   ball1.transform:Translate(0.0, 3.0, 0.0)
end

function update(delta)
   camera.transform:Translate(vx * delta, 0.0, vz * delta)

   local loc = ball1.transform.position
   if loc.y > 4.0 then
      ballvy = -1.0
   elseif loc.y < 2.0 then
      ballvy = 1.0
   end
   ball1.transform:Translate(0.0, ballvy * delta, 0.0)  
end

function onkey(key, code, action, mod)
   if key == LEFT and action == 1 then
      vx = -1.0
   elseif key == RIGHT and action == 1 then
      vx = 1.0
   elseif (key == LEFT or key == RIGHT) and action == 0 then
      vx = 0.0
   end

   if key == UP and action == 1 then
      vz = -1.0
   elseif key == DOWN and action == 1 then
      vz = 1.0
   elseif (key == DOWN or key == UP) and action == 0 then
      vz = 0.0
   end
end
