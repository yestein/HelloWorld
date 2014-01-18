--=======================================================================
-- File Name    : physics_io.lua
-- Creator      : yestein (yestein86@gmail.com)
-- Date         : 
-- Description  : 读取/存储相关
-- Modify       :
--=======================================================================
if not Physics then
	Physics = {}
end

function Physics:LoadPList()
	for _, str_file_path in ipairs(self.tb_plist) do
		if (GamePhysicsWorld:GetInstance():LoadPolygonBodyFromFile(str_file_path) ~= 1) then
			return 0
		end
	end
	return 1
end