

function createButton(w,x,y)
	btn = Button.new(x,y+25,100,100,"0","")

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



function createWindow(k)
	w = Widget.new(100,100,k*100,k*100+25,"Hi")
	w.onWindowClose = function(this)
		window = createWindow(3)
		collectgarbage()
	end
	
	for i=0, k-1 do
		for y=0, k-1 do
			createButton(w,y*100,i*100)
		end
	end
end

window = createWindow(3)

suspend()

print("lua loaded")

collectgarbage()
