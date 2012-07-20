/******************************************************************************
* Copyright (C) 2012 Moritz Kühner, Germany.
*
* Permission is hereby granted, free of charge, to any person obtaining
* a copy of this software and associated documentation files (the
* "Software"), to deal in the Software without restriction, including
* without limitation the rights to use, copy, modify, merge, publish,
* distribute, sublicense, and/or sell copies of the Software, and to
* permit persons to whom the Software is furnished to do so, subject to
* the following conditions:
*
* The above copyright notice and this permission notice shall be
* included in all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
******************************************************************************/
#ifndef GUI_CLIENTLUAENGINE_h
#define GUI_CLIENTLUAENGINE_h

#include "lua.hpp"
#include "GuiElement.h"
#include "IEventReceiver.h"
#include "IrrlichtDevice.h"

class Game;

namespace Gui
{
    class GuiElement;
}

namespace Gui
{

    class LuaEngine : public irr::IEventReceiver
    {
    public:

        LuaEngine(irr::IrrlichtDevice* irr);

        void init();

        void draw();

        void runFile(const irr::core::stringc& file);

        virtual const luaL_reg* getGlobals() = 0;

        virtual void addLibraries() = 0;
        
        void run();

        int getFreeId(GuiElement* e);

        void freeElement(int i);

        int doPCall(int args,int rets);

        irr::IrrlichtDevice* getIrrlichtDevice();

        template<class T>
        static T* getThisPointer(lua_State* pLua);

        virtual bool OnEvent(const irr::SEvent&);
        
        GuiElement* getElement(int id);

        //---- Lua funktions ------

        static int lua_Suspend(lua_State* pLua);

        //---- Lua Constants ------

        static const luaL_reg lua_globls [];


        

    protected:

        lua_State*           m_lua;
        irr::IrrlichtDevice* m_device; 


    private:
        irr::core::array<GuiElement*>
                            m_elements;
        int         m_errorhandler;

    };
}

#endif
