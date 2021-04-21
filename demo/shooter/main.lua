package.path = package.path .. ";../scripts/?.lua"
local freecam = require("freecam")
local Vector3 = couch.Vector3

function init()
   freecam.init_camera()

   local light = couch.DirectionalLight()
   light:SetDirection(Vector3(1.0, -2.0, -1.0))
   light:SetColor(Vector3(1.0, 1.0, 1.0))
   light:SetAmbient(0.2)
   light:SetDiffuse(1.0)
   light:SetSpecular(0.1)
   couch.Node.GetRoot():AddChild(light:Instance())

   local box_mesh = couch.TexturedMesh("../resources/cube.obj", "../resources/paintedwood.jpg")
   local box = couch.Rigidbody()
   box:SetCollisionShape(couch.BoxCollisionShape(1, 1, 1))
   box:AddChild(box_mesh)
   couch.Node.GetRoot():AddChild(box:Instance())

   local ground = couch.Rigidbody()
   ground:SetCollisionShape(couch.BoxCollisionShape(100, 0.1, 100))
   ground:Translate(Vector3(0.0, -1.0, 0.0))
   ground:SetMass(0.0)
   couch.Node.GetRoot():AddChild(ground:Instance())
end

function update(delta)
   freecam.update_camera(delta)
end

function onkey(key, code, action, mod)
   freecam.onkey(key, code, action, mod)
   local camera_transform = freecam.camera:GetTransform()
   if action == couch.ACTION_PRESS and key == couch.KEY_R then
      local res = couch.World.GetWorld():Raycast(camera_transform.position,
						 camera_transform.position + camera_transform:Forward() * 100.0)
      if (res.hit) then
	 res.object:ApplyImpulse(res.normal * -100.0)
      end
   end
end

function onmousemotion(_, _, relx, rely)
   freecam.onmousemotion(relx, rely)
end

