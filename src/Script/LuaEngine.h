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
#include "IEventReceiver.h"
#include "IrrlichtDevice.h"
#include <irrList.h>

class Game;

namespace Script
{
    class ILuaEnginePlugin;
}

namespace Script
{
    class YieldState
    {
    public:
        lua_State*  m_thread;
        int         m_refkey; 
    };

    class LuaEngine : public irr::IEventReceiver
    {
    public:

        LuaEngine(irr::IrrlichtDevice* irr);

        void init();

        void runFile(const irr::core::stringc& file);
        
        void run();

        int doCall(int args,int rets);

        irr::IrrlichtDevice* getIrrlichtDevice();

        static LuaEngine* getThisPointer(lua_State* pLua);

        virtual bool OnEvent(const irr::SEvent&);

        void addPlugin(ILuaEnginePlugin* p);

        lua_State* getLuaState() const
        {
            return m_lua;
        }

        static void stackdump(lua_State* l);

        //---- Lua funktions ------

        static int lua_Suspend(lua_State* pLua);

        static int lua_AtPanic(lua_State* pLua);

        //---- Lua Constants ------

        static const luaL_reg lua_globls [];

        static const char* Lua_Object_Key;


    private:
        irr::core::list<YieldState>  m_yieldlist;

        lua_State*           m_lua;
        irr::IrrlichtDevice* m_device; 
        irr::core::array<ILuaEnginePlugin*> m_plugins;
        int         m_errorhandler;

    };
}

#endif
