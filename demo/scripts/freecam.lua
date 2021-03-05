local freecam = {}

local min = math.min
local max = math.max

freecam.camera = nil
freecam.speed = 30

local vx = 0.0
local vy = 0.0
local vz = 0.0

local cam_rot_x = 0.0
local cam_rot_y = 0.0

function freecam.init_camera()
   freecam.camera = couch.Camera()
   freecam.camera:MakeCurrent()
end

function freecam.update_camera(delta)
   local camera_transform = freecam.camera:GetTransform()

   local move_vec = couch.Vector3()
   move_vec = camera_transform.position + camera_transform:Forward() * delta * vz * freecam.speed
   move_vec = move_vec + camera_transform:Right() * delta * vx * freecam.speed
   move_vec = move_vec + camera_transform:Up() * delta * vy * freecam.speed
   camera_transform.position = move_vec

   camera_transform.rotation.y = camera_transform.rotation.y - cam_rot_x * delta
   cam_rot_x = 0.0
   camera_transform.rotation.x = camera_transform.rotation.x - cam_rot_y * delta
   camera_transform.rotation.x = min(max(camera_transform.rotation.x, -3.14 / 2.0), 3.13 / 2.0)
   cam_rot_y = 0.0

   freecam.camera:SetTransform(camera_transform)
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

function freecam.onkey(key, code, action, mod)
   vz = action_dir(key, action, couch.KEY_W, couch.KEY_S, vz)
   vx = action_dir(key, action, couch.KEY_D, couch.KEY_A, vx)
   vy = action_dir(key, action, couch.KEY_SPACE, couch.KEY_LEFT_CONTROL, vy)
end

function freecam.onmousemotion(relx, rely)
   cam_rot_x = relx
   cam_rot_y = rely
end

return freecam
