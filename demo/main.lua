local min = math.min
local max = math.max
local cube
local ball
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

   local light = couch.DirectionalLight()
   light.direction = couch.Vector3(0.0, -1.0, -1.0)
   light.color = couch.Vector3(1.0, 1.0, 1.0)
   light.ambient = 0.2
   light.diffuse = 1.0
   light.specular = 0.1
   couch.Node.GetRoot().children:Append(light:Instance())

   local skybox = couch.Skybox.FromFiles(
      "skybox/px.png",
      "skybox/nx.png",
      "skybox/py.png",
      "skybox/ny.png",
      "skybox/pz.png",
      "skybox/nz.png"
   )
   couch.Node.GetRoot().children:Append(skybox:Instance())

   local physics_ball_prefab = couch.Rigidbody()
   local physics_ball_mesh = couch.Mesh.FromFile("ball.obj")
   material = physics_ball_mesh:GetMaterial(0)
   material.ambient = BLUE
   material.diffuse = BLUE
   physics_ball_mesh:SetMaterial(0, material)
   physics_ball_prefab.children:Append(physics_ball_mesh);
   physics_ball_prefab.transform.position = couch.Vector3(0.0, 30.0, -10.0)   
   local physics_ball = physics_ball_prefab:Instance()
   couch.Node.GetRoot().children:Append(physics_ball)

   make_ground()

   local cube_prefab = couch.Mesh.FromFile("cube.obj")
   material = cube_prefab:GetMaterial(0)
   material.ambient = RED
   material.diffuse = RED
   cube_prefab:SetMaterial(0, material)
   local orbiter = couch.Mesh.FromFile("ball.obj")
   orbiter.transform.scale = orbiter.transform.scale * 0.25;
   orbiter.transform:Translate(1.0, 0.0, 0.0)
   cube_prefab.children:Append(orbiter)
   cube = cube_prefab:Instance()
   couch.Node.GetRoot().children:Append(cube)
   
   local ball_prefab = couch.Mesh.FromFile("ball.obj")
   material = ball_prefab:GetMaterial(0)
   ball_prefab:SetMaterial(0, material)
   ball = ball_prefab:Instance()
   couch.Node.GetRoot().children:Append(ball)

   ball.transform:Translate(0.0, 3.0, 0.0)

   local trough_prefab = couch.TexturedMesh("trough.obj", "wood_lowres.png")
   trough = trough_prefab:Instance()
   couch.Node.GetRoot().children:Append(trough)
   trough.transform:Translate(10.0, 0.0, 0.0)

   local scaffold_prefab = couch.TexturedMesh("scaffold.obj", "grate_floor_lowres.png", "railing.png")
   local scaffold = scaffold_prefab:Instance()
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

   local barn_prefab = couch.TexturedMesh("barn.obj", "paintedwood.jpg", "barnroof_lowres.png", "wood_lowres.png")
   local barn = barn_prefab:Instance()
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

   local loc = ball.transform.position
   if loc.y > 4.0 then
      ballvy = -1.0
   elseif loc.y < 2.0 then
      ballvy = 1.0
   end
   ball.transform.position.y = ball.transform.position.y + ballvy * delta

   cube.transform.rotation.y = cube.transform.rotation.y + 2.0 * delta;
   cube.transform.rotation.z = cube.transform.rotation.z + 1.0 * delta;
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

function make_ground()
   local ground_prefab = couch.TexturedMesh("ground.obj", "grass_lowres.png")
   ground_prefab.transform.position = couch.Vector3(0.0, -2.0, 0.0)
   ground_prefab.transform.scale = couch.Vector3(3.0, 1.0, 3.0)

   ground = couch.Spatial():Instance()
   couch.Node.GetRoot().children:Append(ground)

   for x = -20, 20, 1 do
      for z = -20, 20, 1 do
	 local piece = ground_prefab:Instance()
	 piece.transform.position = couch.Vector3(6.0 * x, -2.0, 6.0 * z)
	 ground.children:Append(piece)
      end
   end
end
