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
#ifndef GUI_GUIPLUGIN_h
#define GUI_GUIPLUGIN_h

#include "lua.hpp"
#include "GuiElement.h"
#include "ILuaEnginePlugin.h"
#include "IrrlichtDevice.h"

class Game;

namespace Gui
{
    class GuiElement;
}

namespace Gui
{
    class GuiPlugin : public Script::ILuaEnginePlugin
    {
    public:

        GuiPlugin(irr::IrrlichtDevice* irr);

        void init();

        void draw();

        void runFile(const irr::core::stringc& file);
        
        virtual void run();

        int getFreeId(Gui::GuiElement* e);

        void freeElement(int i);

        int doPCall(int args,int rets);

        irr::IrrlichtDevice* getIrrlichtDevice();

        virtual bool OnEvent(const irr::SEvent&);

        virtual void registerFunktions(lua_State* pLua);
        
        Gui::GuiElement* getElement(int id);

        static GuiPlugin* getThisPointer(lua_State* pLua);

        //---- Lua funktions ------


        //---- Lua Constants ------

        static const luaL_reg lua_globls [];

        static const char* Lua_Object_Key;


    protected:

        lua_State*           m_lua;
        irr::IrrlichtDevice* m_device; 

    private:
        irr::core::array<Gui::GuiElement*>
                            m_elements;

    };
}

#endif
