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
#ifndef Main_UserInterface_GuiElement_h
#define Main_UserInterface_GuiElement_h


#include <IGUIElement.h>
#include <lua.hpp>



namespace Script 
{   
    class LuaEngine;
} 

namespace Gui 
{

    class GuiElement : public irr::IReferenceCounted 
    {

    public:

        GuiElement(Script::LuaEngine* engine, GuiElement *parent, lua_State* plua);

        ~GuiElement();

        virtual void draw() = 0;

        virtual const luaL_reg* getMethods() = 0;
        
        virtual const luaL_reg* getFunktions() = 0;

        virtual const char* getTableName() = 0;

        virtual const char* getMetaTableName() = 0;

        void pushToStack();

        void onEvent(const char* event);

        const int getId() const
        {
            return m_id;
        }

    protected:

        void onLuaGC();
        void onLuaIndex();
        void onLuaNewIndex();

        GuiElement *m_parent;

        lua_State*  m_lua;

        Script::LuaEngine* m_engine;

    private:

        int m_id;
    };

} 


#endif 
