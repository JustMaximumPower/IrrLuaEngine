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
#ifndef Main_UserInterface_GuiButton_h
#define Main_UserInterface_GuiButton_h


#include "GuiElement.h"
#include <lua.hpp>
#include <IGUIButton.h>



namespace Script 
{   
    class LuaEngine;
} 

namespace Gui 
{

    class GuiButton : public GuiElement
    {

     public:

        static void createMatatable(lua_State* pLua);

        GuiButton(GuiPlugin* plugin, lua_State* plua);

        ~GuiButton();

        virtual void draw();

        virtual const luaL_reg* getMethods();
        
        virtual const luaL_reg* getFunktions();

        virtual const char* getTableName();

        virtual const char* getMetaTableName();

        virtual irr::gui::IGUIElement* getIrrlichtElement();

        //---- Lua funktions ------

        static int lua_new(lua_State* pLua);

        static int lua_GC(lua_State* pLua);

        static int lua_index(lua_State* pLua);

        static int lua_newindex(lua_State* pLua);

        //---- Lua Constants ------

        static const char* lua_libName;

        static const char* lua_metatableName;

        static const struct luaL_reg lua_lib_m [];

        static const struct luaL_reg lua_lib_f [];

    protected:
        irr::gui::IGUIButton *m_irrElement;
    };

}


#endif
