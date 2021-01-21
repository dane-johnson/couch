local min = math.min
local max = math.max
local ball
local ball1
local camera

local vx = 0.0
local vz = 0.0

local ballvy = -1.0

local cam_rot_x = 0.0
local cam_rot_y = 0.0

local SPEED = 30

local RED = couch.Color(1.0, 0.0, 0.0)
local BLUE = couch.Color(0.0, 0.0, 1.0)

function init()
   local material
   
   camera = couch.Camera()
   camera:MakeCurrent()
   camera.transform:Translate(0.0, 0.0, 10.0)
   
   ball = couch.Mesh.FromFile("cube.glb")
   material = couch.Material()
   material.color = RED
   material.usesColor = true
   ball:SetMaterial(0, material)
   couch.Node.GetRoot().children:Append(ball)
   
   ball1 = couch.Mesh.FromFile("cube.glb")
   material = couch.Material()
   material.tex = couch.Texture.FromFile("container.png")
   material.usesTex = true
   ball1:SetMaterial(0, material)
   couch.Node.GetRoot().children:Append(ball1)

   ball1.transform:Translate(0.0, 3.0, 0.0)

   trough = couch.TexturedMesh("trough.glb", "wood_lowres.png")
   couch.Node.GetRoot().children:Append(trough)
   trough.transform:Translate(10.0, 0.0, 0.0)
   trough.transform.scale = trough.transform.scale * 3.0

   scaffold = couch.TexturedMesh("scaffold.glb", "grate_floor_lowres.png", "railing.png")
   
   material = scaffold:GetMaterial(0)
   material.alphaScissor = 0.9
   scaffold:SetMaterial(0, material)

   material = scaffold:GetMaterial(1)
   material.alphaScissor = 0.1
   scaffold:SetMaterial(1, material)
   
   couch.Node.GetRoot().children:Append(scaffold)
   scaffold.transform:Translate(-10.0, 0.0, 0.0)
end

function update(delta)
   local cam_forwards = camera.transform:Forward()
   local cam_rotation = camera.transform.rotation
   print (cam_forwards.x, cam_forwards.y, cam_forwards.z)
   print (cam_rotation.x, cam_rotation.y, cam_rotation.z)

   local move_vec = couch.Vector3()
   move_vec = camera.transform.position + cam_forwards * delta * vz * SPEED
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

function onkey(key, code, action, mod)
   if key == couch.KEY_W and action == couch.ACTION_PRESS then
      vz = 1.0
   elseif key == couch.KEY_S and action == couch.ACTION_PRESS then
      vz = -1.0
   elseif (key == couch.KEY_W or key == couch.KEY_S) and action == couch.ACTION_RELEASE then
      vz = 0.0
   end
end

function onmousemotion(_, _, relx, rely)
   cam_rot_x = relx
   cam_rot_y = rely
end
