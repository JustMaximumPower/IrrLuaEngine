/******************************************************************************
 * Copyright (C) 2012 Moritz K�hner, Germany.
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
#ifndef Main_UserInterface_GuiElement_h
#define Main_UserInterface_GuiElement_h

#include <IGUIElement.h>
#include <lua.hpp>
#include "LuaObject.h"

namespace Gui
{
    class GuiPlugin;
}

namespace Gui
{

    class GuiElement: public Script::LuaObject
    {

    public:

        GuiElement(GuiPlugin* plugin, Script::LuaEngine* engine, lua_State* plua);

        ~GuiElement();

        irr::gui::IGUIElement* getIrrlichtElement() const;

        const int getId() const;

        void validate(lua_State* pLua);

    protected:

        static GuiElement* lua_toGuiElement(lua_State* pLua, int index = 1);

        static int luaRemove(lua_State* pLua);

        static int luaToolTip(lua_State* pLua);

        static int luaText(lua_State* pLua);

        static int luaEnabled(lua_State* pLua);

        static int luaVisible(lua_State* pLua);

        static int luaId(lua_State* pLua);

        static int luaTabOrder(lua_State* pLua);

        static int luaGetType(lua_State* pLua);

        static int luaGetAbsolutePosition(lua_State* pLua);

        static int luaX(lua_State* pLua);

        static int luaY(lua_State* pLua);

        static int luaHeight(lua_State* pLua);

        static int luaWidth(lua_State* pLua);

        irr::gui::IGUIElement* m_irrelement;

        GuiElement *m_parent;

        GuiPlugin* m_plugin;

    private:

        int m_id;

        static const struct luaL_reg lua_lib_m[];

        static const struct luaL_reg lua_lib_p[];
    };

}

#endif 
