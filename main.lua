local min = math.min
local max = math.max
local ball
local ball1
local camera

local LEFT = 263
local RIGHT = 262
local UP = 265
local DOWN = 264
local Q = 81

local vx = 0.0
local vz = 0.0

local ballvy = -1.0

local cam_rot_x = 0.0
local cam_rot_y = 0.0

local SPEED = 30

function init()
   camera = couch.Camera()
   camera:MakeCurrent()
   camera.transform:Translate(0.0, 0.0, 10.0)
   ball = couch.Ball()
   ball:SetupMesh()
   couch.Node.GetRoot().children:Append(ball)
   ball1 = couch.Ball()
   ball1:SetupMesh()
   couch.Node.GetRoot().children:Append(ball1)

   ball1.transform:Translate(0.0, 3.0, 0.0)
end

function update(delta)
   local cam_forwards = camera.transform:Forward()

   local move_vec = couch.Vector3()
   move_vec = camera.transform.position + cam_forwards * delta * vz * SPEED
   camera.transform.position = move_vec
   
   camera.transform.rotation.y = camera.transform.rotation.y - cam_rot_x * delta
   cam_rot_x = 0.0
   camera.transform.rotation.x = camera.transform.rotation.x - cam_rot_y * delta
   camera.transform.rotation.x = min(max(camera.transform.rotation.x, -3.14), 3.14)
   cam_rot_y = 0.0

   local loc = ball1.transform.position
   if loc.y > 4.0 then
      ballvy = -1.0
   elseif loc.y < 2.0 then
      ballvy = 1.0
   end
   ball1.transform.position.y = ball1.transform.position.y + ballvy * delta

   ball.transform.rotation.z = ball.transform.rotation.z + 1.0 * delta;
   ball.transform.rotation.y = ball.transform.rotation.y + 1.0 * delta;
   ball.transform.rotation.x = ball.transform.rotation.x + 1.0 * delta;
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
      vz = 1.0
   elseif key == DOWN and action == 1 then
      vz = -1.0
   elseif (key == DOWN or key == UP) and action == 0 then
      vz = 0.0
   end

   if key == Q then
      if action == 1 then
	 cam_rot_x = 1.0
      elseif action == 0 then
	 cam_rot_x = 0.0
      end
   end
end

function onmousemotion(_, _, relx, rely)
   cam_rot_x = relx
   cam_rot_y = rely
end
