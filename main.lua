
function newButton(x,y,number,w)
	local btn = Button.new(x,y,25,25,number)
	local edt = w.screen
	function btn:onButton()
		if edt.text == "0" then
			edt.text =  self.text
		else
			edt.text = edt.text .. self.text
		end
	end
	w:addElement(btn)
	return btn
end

open = Button.new(100,10,100,100,"Calculator","Open's new Calculator")
open.windows = {}

function open:onButton() 
	local window = Widget.new(100,100,150,190,"Calculator")
	local edt = EditBox.new("0",10,22,130,25)
	window:addElement(edt)
	window.screen = edt
	
	local num = 1
	for i=1, 3 do
		for y=1, 3 do
			local btn = newButton(35*y-25,50+35*(3-i),num,window)
			window:addElement(btn)
			num = num + 1
		end
	end
	
	newButton(10,155,0,window)
	newButton(45,155,".",window)
	newButton(115,155,"+",window)
	newButton(115,120,"-",window)
	newButton(115,85,"*",window)
	newButton(115,50,"/",window)
	
	local btn = Button.new(80,155,25,25,"=")
	function btn:onButton()
		local fun,err = loadstring("return ".. window.screen.text)
		if not fun then
			window.screen.text = err
			return
		end

		local good, value = pcall(fun)

		window.screen.text = value
	end
	window:addElement(btn)
	
	open.windows[#open.windows+1] = window
end

dogc = Button.new(210,10,100,100,"Do GC")
function dogc:onButton() 
	collectgarbage("collect")
end

rem = Button.new(320,10,100,100,"Remove this!")
function rem:onButton() 
	self:remove()
end

timer = Button.new(430,10,100,100,"Time")
timer.time = 0
function timer:onButton() 
	if timer.time ~= 0 then
		return
	end
	
	while true do
		timer.time = timer.time+1
		self.text = timer.time
		suspend()
	end

end

test = Button.new(100,120,100,100,"test","test!!!")

function test:onButton() 
	print("testbutton id is: " .. self.id)
	print("testbutton taborder is: " .. self.tabOrder)
	
	print(pcall(function() self.id = 1 end))

	print("dad")
	
end

print("lua loaded")
