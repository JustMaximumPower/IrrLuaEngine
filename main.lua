


function createButton(x,y)
	btn = Button.new(x,y,100,100,"0","")

	btn.test = 0

	btn.onButton = function(this)
		Game.exit()
	end

	btn.onHover = function(this)
		this.test = this.test + 1
		
		this.text = this.test

	end


	return btn
end


print("lua loaded")

suspend()

buttons = {}

for i=0, 6 do
	buttons[i] = {}
	for y=0, 7 do
		buttons[i][y] = createButton(y*100,i*100)
	end
	
end



collectgarbage()
