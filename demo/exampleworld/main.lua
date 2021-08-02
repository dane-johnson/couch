package.path = package.path .. ";../scripts/?.lua"
local freecam = require("freecam")

local min = math.min
local max = math.max
local cube
local physics_ball
local character
local ball
local die_cube

local total = 0.0
local character_move_vec = couch.Vector3(0.0, 0.0, 0.0)

local ballvy = -1.0

local SPEED = 30

local WHITE = couch.Vector3(1.0, 1.0, 1.0)
local RED = couch.Vector3(1.0, 0.0, 0.0)
local BLUE = couch.Vector3(0.0, 0.0, 1.0)

local light

function init()
   local material
   local transform

   couch.Input.GetInstance():SetMouseMode(couch.Input.CAPTURED)

   freecam.init_camera()
   freecam.camera:Translate(couch.Vector3(0.0, 0.0, 10.0))

   local light = couch.DirectionalLight()
   light:SetDirection(couch.Vector3(0.0, -1.0, -1.0))
   light:SetColor(couch.Vector3(1.0, 1.0, 1.0))
   light:SetAmbient(0.2)
   light:SetDiffuse(1.0)
   light:SetSpecular(0.1)
   couch.Node.GetRoot():AddChild(light:Instance())

   init_point_lights()

   local skybox = couch.Skybox.FromFiles(
      "../resources/skybox/px.png",
      "../resources/skybox/nx.png",
      "../resources/skybox/py.png",
      "../resources/skybox/ny.png",
      "../resources/skybox/pz.png",
      "../resources/skybox/nz.png"
   )
   couch.Node.GetRoot():AddChild(skybox:Instance())

   local physics_ball_prefab = couch.Rigidbody()
   local physics_ball_mesh = couch.Mesh.FromFile("../resources/ball.glb")
   material = physics_ball_mesh:GetMaterial(0)
   material.ambient = BLUE
   material.diffuse = BLUE
   physics_ball_mesh:SetMaterial(0, material)
   physics_ball_prefab:AddChild(physics_ball_mesh);
   physics_ball_prefab:Translate(couch.Vector3(-14.0, 30.0, -5.0))
   physics_ball = physics_ball_prefab:Instance()
   couch.Node.GetRoot():AddChild(physics_ball)

   make_ground()

   local character_prefab = couch.Mesh.FromFile("../resources/capsule.glb")
   material = character_prefab:GetMaterial(0)
   material.ambient = BLUE
   material.diffuse = BLUE
   material.specular = WHITE * 0.1
   character_prefab:SetMaterial(0, material)
   local character_body = couch.Rigidbody()
   character_body:SetMass(1.0)
   character_body:SetCollisionShape(couch.CapsuleCollisionShape(1.0, 1.0))
   character_body:SetCharacter(true)
   character_body:AddChild(character_prefab)
   character_body:Translate(couch.Vector3(-15.0, 3.0, 0.0))
   character = character_body:Instance()
   couch.Node.GetRoot():AddChild(character)

   local cube_prefab = couch.Mesh.FromFile("../resources/cube.glb")
   material = cube_prefab:GetMaterial(0)
   material.ambient = RED
   material.diffuse = RED
   cube_prefab:SetMaterial(0, material)
   local orbiter = couch.Mesh.FromFile("../resources/ball.glb")
   orbiter:UniformScale(0.25);
   orbiter:Translate(couch.Vector3(1.0, 0.0, 0.0))
   cube_prefab:AddChild(orbiter)
   cube = cube_prefab:Instance()
   couch.Node.GetRoot():AddChild(cube)
   die_cube = cube_prefab:Instance()
   couch.Node.GetRoot():AddChild(die_cube)
   die_cube:Translate(couch.Vector3(0.0, 0.0, 3.0))
   
   local ball_prefab = couch.Mesh.FromFile("../resources/ball.glb")
   material = ball_prefab:GetMaterial(0)
   ball_prefab:SetMaterial(0, material)
   ball = ball_prefab:Instance()
   couch.Node.GetRoot():AddChild(ball)

   ball:Translate(couch.Vector3(0.0, 3.0, 0.0))

   local trough_prefab = couch.TexturedMesh("../resources/trough.glb", "../resources/wood_lowres.png")
   trough = trough_prefab:Instance()
   couch.Node.GetRoot():AddChild(trough)
   trough:Translate(couch.Vector3(10.0, 0.0, 0.0))

   local scaffold_prefab = couch.TexturedMesh("../resources/scaffold.glb", "../resources/grate_floor_lowres.png", "../resources/railing.png")
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
   couch.Node.GetRoot():AddChild(scaffold)
   scaffold:Translate(couch.Vector3(-3.0, 3.0, 0.0))

   local barn_prefab = couch.TexturedMesh("../resources/barn.glb", "../resources/paintedwood.jpg", "../resources/barnroof_lowres.png", "../resources/wood_lowres.png")
   material = barn_prefab:GetMaterial(0)
   material.cullBack = false
   barn_prefab:SetMaterial(0, material)
   material = barn_prefab:GetMaterial(1)
   material.cullBack = false
   barn_prefab:SetMaterial(1, material)
   local barn_body = couch.Rigidbody()
   barn_body:SetCollisionShape(couch.MeshCollisionShape(barn_prefab))
   barn_body:SetMass(0.0)
   barn_body:AddChild(barn_prefab)
   local barn = barn_body:Instance()
   couch.Node.GetRoot():AddChild(barn)
   barn:Translate(couch.Vector3(-15.0, 0.0, 0.0))
end

function update(delta)
   total = total + delta

   freecam.update_camera(delta)

   local loc = ball:GetTransform().position
   if loc.y > 4.0 then
      ballvy = -1.0
   elseif loc.y < 2.0 then
      ballvy = 1.0
   end
   ball:Translate(couch.Vector3(0.0, ballvy * delta, 0.0))

   cube:RotateY(2.0 * delta)
   cube:RotateZ(1.0 * delta)

   character:ApplyForce(character_move_vec * 10.0)

   if total > 1.0 and die_cube then
      die_cube:QueueFree()
      die_cube = nil
   end
end

function init_point_lights()
   local colors = {couch.Vector3(1.0, 0.0, 0.0), couch.Vector3(0.0, 1.0, 0.0), couch.Vector3(0.0, 0.0, 1.0)}
   for i, color in ipairs(colors) do
      local pointLight = couch.PointLight();
      pointLight:Translate(couch.Vector3(i * -10.0, 0, -10))
      pointLight:SetRadius(10.0)
      pointLight:SetColor(color)
      pointLight:SetAmbient(0.2)
      pointLight:SetDiffuse(1.0)
      pointLight:SetSpecular(0.1)
      local lightBox = couch.Mesh.FromFile("../resources/cube.glb")
      lightBox:UniformScale(0.5);
      local material = lightBox:GetMaterial(0)
      material.ambient = color
      lightBox:SetMaterial(0, material)
      pointLight:AddChild(lightBox);
      couch.Node.GetRoot():AddChild(pointLight:Instance())
   end
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
   freecam.onkey(key, code, action, mod)
   
   if key == couch.KEY_J and action == couch.ACTION_PRESS then
      physics_ball:ApplyImpulse(couch.Vector3(0.0, 1.0, 0.0) * 10)
   end

   character_move_vec.z = action_dir(key, action, couch.KEY_DOWN, couch.KEY_UP, character_move_vec.z)
end

function onmousemotion(_, _, relx, rely)
   freecam.onmousemotion(relx, rely)
end

function make_ground()
   local ground_prefab = couch.TexturedMesh("../resources/ground.glb", "../resources/grass_lowres.png")
   
   local ground_prefab_transform = ground_prefab:GetTransform()
   ground_prefab_transform.position = couch.Vector3(0.0, -2.0, 0.0)
   ground_prefab_transform.scale = couch.Vector3(3.0, 1.0, 3.0)
   ground_prefab:SetTransform(ground_prefab_transform)

   ground = couch.Spatial():Instance()
   couch.Node.GetRoot():AddChild(ground)

   -- Add a collisionshape
   local ground_shape_prefab = couch.Rigidbody()
   ground_shape_prefab:SetMass(0.0)
   ground_shape_prefab:SetCollisionShape(couch.BoxCollisionShape(180.0, 1.0, 180.0))
   ground_shape_prefab:Translate(couch.Vector3(0.0, -2.5, 0.0))
   ground:AddChild(ground_shape_prefab:Instance())

   for x = -20, 20, 1 do
      for z = -20, 20, 1 do
	 local piece = ground_prefab:Instance()
	 piece:Translate(couch.Vector3(6.0 * x, -2.0, 6.0 * z))
	 ground:AddChild(piece)
      end
   end
end
