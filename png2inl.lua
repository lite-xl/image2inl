--[[
Coded by: Ulhar (https://github.com/Ulhar)

This is the script I used to generate the inl file.
It uses love2d, and generates the inl from a
64x64 image file called `lite-xl.png` in the same directory.
The result is placed in a file called `icon.inl`, also in the same directory.

]]

local out = "static unsigned char icon_rgba[] = {\n  "
local img = love.image.newImageData("lite-xl.png")

local bytes = {}
local fmt = "0x%02x, 0x%02x, 0x%02x, 0x%02x"

for x = 63, 0, -1 do
	for y = 63, 0, -1 do
		table.insert(bytes, fmt:format(love.math.colorToBytes(img:getPixel(x, y))))
	end
end

local rows = {}
local row = {}

for i, v in ipairs(bytes) do
	table.insert(row, v)
	if #row == 3 or i == #bytes then
		table.insert(rows, table.concat(row, ", "))
		row[1], row[2], row[3] = nil
	end
end

out = out .. table.concat(rows, ",\n  ")

out = out .. "\n};\nstatic unsigned int icon_rgba_len = 16384;"

local fh = assert(io.open("icon.inl", "wb"))
fh:write(out)
fh:flush()
fh:close()

love.event.quit()
