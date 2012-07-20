


function createButton(w,x,y)
	btn = Button.new(x,y,100,100,"0","")

	btn.test = 0

	btn.onButton = function(this)
		this.enabled = not this.enabled
	end

	btn.onHover = function(this)
		this.test = this.test + 1
		
		this.text = this.test

	end

	w:addElement(btn)
	
	return btn
end


print("lua loaded")

w = Widget.new(100,100,500,200,"Hi")

suspend()

buttons = {}

for i=0, 3 do
	buttons[i] = {}
	for y=0, 3 do
		buttons[i][y] = createButton(w,y*100,i*100)
	end
	
end



collectgarbage()
