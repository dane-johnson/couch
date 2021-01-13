local ball
local camera

function init()
   camera = couch.Camera()
   camera:MakeCurrent()
   ball = couch.Ball()
   ball:SetupMesh()
   couch.AddMeshToList(ball)
end

function update(delta)
   camera.transform:Translate(0.0, 0.0, 1.0 * delta);
end
