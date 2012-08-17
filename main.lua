

image = Image.new(100,120,500,500,"image")
image:setColor(0)

textur = Textur.load("font1.png")

image:setTextur(textur)



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
	self.text = "3..."
	suspend("r",1000)
	self.text = "2..."
	suspend("r",1000)
	self.text = "1..."
	suspend("r",1000)
	self:remove()
end

timer = Button.new(430,10,100,100,"Time")
timer.time = 0
function timer:onButton() 
	if self.time ~= 0 then
		return
	end
	
	while true do
		self.time = self.time+1
		self.text = self.time
		suspend("r",10)
	end
end

timer2 = Button.new(430,120,100,100,"Time")
timer2.time = 0
function timer2:onButton() 
	if self.time ~= 0 then
		return
	end
	
	while true do
		self.time = self.time+1
		self.text = self.time
		self.height = self.time%100;
		self.drawBorder = self.time%5 ==1
		suspend("r",100)
	end
end


test = Button.new(100,120,100,100,"test","test!!!")

function test:onButton() 
	print("testbutton id is: " .. self:getId())
	print("testbutton taborder is: " .. self.tabOrder)
	local pos = self:getAbsolutePosition()
	print("absolut Position: x".. pos[1] .. " y"..pos[2])
	
	
	function f(t)
		print(t:getId())
	end
	
	self:remove()
	
	local status, err = pcall(f,self)
	print(status, err)

end

print("lua loaded")
