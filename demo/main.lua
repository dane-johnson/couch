local min = math.min
local max = math.max
local ball
local ball1
local camera

local vx = 0.0
local vy = 0.0
local vz = 0.0

local ballvy = -1.0

local cam_rot_x = 0.0
local cam_rot_y = 0.0

local SPEED = 30

local WHITE = couch.Color(1.0, 1.0, 1.0)
local RED = couch.Color(1.0, 0.0, 0.0)
local BLUE = couch.Color(0.0, 0.0, 1.0)

local light

function init()
   local material
   
   camera = couch.Camera()
   camera:MakeCurrent()
   camera.transform:Translate(0.0, 0.0, 10.0)

   light = couch.DirectionalLight.new()
   light.direction = couch.Vector3(0.0, -1.0, -1.0)
   light.color = couch.Vector3(1.0, 1.0, 1.0)
   light.ambient = 0.2
   light.diffuse = 1.0
   light.specular = 0.1
   couch.Node.GetRoot().children:Append(light)
   
   ball = couch.Mesh.FromFile("cube.obj")
   material = ball:GetMaterial(0)
   material.ambient = RED
   material.diffuse = RED
   ball:SetMaterial(0, material)
   couch.Node.GetRoot().children:Append(ball)
   
   ball1 = couch.Mesh.FromFile("ball.obj")
   print(material.diffuse.b)
   material = ball1:GetMaterial(0)
   ball1:SetMaterial(0, material)
   couch.Node.GetRoot().children:Append(ball1)

   ball1.transform:Translate(0.0, 3.0, 0.0)

   trough = couch.TexturedMesh("trough.obj", "wood_lowres.png")
   couch.Node.GetRoot().children:Append(trough)
   trough.transform:Translate(10.0, 0.0, 0.0)

   scaffold = couch.TexturedMesh("scaffold.obj", "grate_floor_lowres.png", "railing.png")
   material = scaffold:GetMaterial(0)
   material.alphaScissor = 0.9
   scaffold:SetMaterial(0, material)
   material = scaffold:GetMaterial(1)
   material.cullBack = false
   scaffold:SetMaterial(1, material)
   material = scaffold:GetMaterial(1)
   material.alphaScissor = 0.1
   scaffold:SetMaterial(1, material)
   couch.Node.GetRoot().children:Append(scaffold)
   scaffold.transform:Translate(-3.0, 3.0, 0.0)

   barn = couch.TexturedMesh("barn.obj", "paintedwood.jpg", "barnroof_lowres.png", "wood_lowres.png")
   material = barn:GetMaterial(0)
   material.cullBack = false
   barn:SetMaterial(0, material)
   material = barn:GetMaterial(1)
   material.cullBack = false
   barn:SetMaterial(1, material)
   couch.Node.GetRoot().children:Append(barn)
   barn.transform:Translate(-15.0, 0.0, 0.0)
end

function update(delta)
   local move_vec = couch.Vector3()
   move_vec = camera.transform.position + camera.transform:Forward() * delta * vz * SPEED
   move_vec = move_vec + camera.transform:Right() * delta * vx * SPEED
   move_vec = move_vec + camera.transform:Up() * delta * vy * SPEED
   camera.transform.position = move_vec
   
   camera.transform.rotation.y = camera.transform.rotation.y - cam_rot_x * delta
   cam_rot_x = 0.0
   camera.transform.rotation.x = camera.transform.rotation.x - cam_rot_y * delta
   camera.transform.rotation.x = min(max(camera.transform.rotation.x, -3.14 / 2.0), 3.14 / 2.0)
   cam_rot_y = 0.0

   local loc = ball1.transform.position
   if loc.y > 4.0 then
      ballvy = -1.0
   elseif loc.y < 2.0 then
      ballvy = 1.0
   end
   ball1.transform.position.y = ball1.transform.position.y + ballvy * delta

   ball.transform.rotation.z = ball.transform.rotation.z + 1.0 * delta;
end

function action_dir(key, action, pos, neg, curr)
   if key == pos and action == couch.ACTION_PRESS then
      return 1.0
   elseif key == neg and action == couch.ACTION_PRESS then
      return -1.0
   elseif (key == pos or key == neg) and action == couch.ACTION_RELEASE then
      return 0.0
   else
      return curr
   end
end

function onkey(key, code, action, mod)
   vz = action_dir(key, action, couch.KEY_W, couch.KEY_S, vz)
   vx = action_dir(key, action, couch.KEY_D, couch.KEY_A, vx)
   vy = action_dir(key, action, couch.KEY_SPACE, couch.KEY_LEFT_CONTROL, vy)
   if key == couch.KEY_DOWN and action == couch.ACTION_PRESS then
      light.ambient = max(light.ambient - 0.1, 0.0)
   elseif key == couch.KEY_UP and action == couch.ACTION_PRESS then
      light.ambient = light.ambient + 0.1
      print(light.ambient)
   end
end

function onmousemotion(_, _, relx, rely)
   cam_rot_x = relx
   cam_rot_y = rely
end
