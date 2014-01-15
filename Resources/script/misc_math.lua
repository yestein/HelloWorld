--===================================================
-- File Name    : misc_math.lua
-- Creator      : yestein (yestein86@gmail.com)
-- Date         : 2013-12-31 13:06:59
-- Description  :
-- Modify       :
--===================================================

if not Misc then
	Misc = {}
end

if not Misc.nPrimeIndex then
	Misc.nPrimeIndex = 1
	Misc.nPrimeIndexIndex = 1
end
local tbProperty = {
	Attack  = 1,
	Defense = 2,
	Magic   = 3,
	MaxHP   = 4,
	MaxMP   = 5,
}

--2 3 5 7 11 13 17 19 23 29 31 37 41 43 47 53 59 61 67 71 73 79 83 89 97 101 103 107 109 113 127 131 137 139 149 151 157 163 167 173 179 181 191 193 197 199 
local tbPrimeForMod = {
	89, 97, 101, 103, 107
}
local PRIME_MAX_COUNT = #tbPrimeForMod


function Misc:CalcRandomProperyOffset(szProperty, nRandom)
	local nIndex = tbProperty[szProperty]
	if not nIndex then
		return 0
	end
	local nRet = nRandom % tbPrimeForMod[nIndex] - 50
	return nRet
end