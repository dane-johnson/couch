package.path = package.path .. ";../scripts/?.lua"
local freecam = require("freecam")
local Vector3 = couch.Vector3

function init()
   freecam.init_camera()
   local material

   local light = couch.DirectionalLight()
   light:SetDirection(couch.Vector3(1.0, 1.0, 1.0))
   light:SetColor(Vector3(1.0, 1.0, 1.0))
   light:SetAmbient(0.2)
   light:SetDiffuse(1.0)
   light:SetSpecular(0.1)
   couch.Node.GetRoot():AddChild(light:Instance())

   local ibox = couch.TexturedMesh("../resources/inverted_cube.obj", "../resources/paintedwood.jpg")
   ibox:UniformScale(0.0)
   couch.Node.GetRoot():AddChild(ibox:Instance())

   local box = couch.Mesh.FromFile("../resources/cube.obj")
   material = box:GetMaterial(0)
   material.ambient = Vector3(1.0, 0.0, 0.0)
   material.diffuse = Vector3(1.0, 0.0, 0.0)
   box:SetMaterial(0, material)
   couch.Node.GetRoot():AddChild(box:Instance())
end

function update(delta)
   freecam.update_camera(delta)
end

function onkey(key, code, action, mod)
   freecam.onkey(key, code, action, mod)
end

function onmousemotion(_, _, relx, rely)
   freecam.onmousemotion(relx, rely)
end
