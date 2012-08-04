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
#ifndef GAME_H_
#define GAME_H_

#include <lua.hpp>
#include <irrlicht.h>
#include "ILuaEnginePlugin.h"

namespace Script
{
    class LuaEngine;
}

class Game: public Script::ILuaEnginePlugin
{
public:

    Game();

    virtual ~Game();

    void init(int argc, const char* argv[]);

    int runGame();

    void closeGame();

    irr::IrrlichtDevice* getIrrlichtDevice() const;

    irr::video::IVideoDriver* getVideoDriver() const;

    static Game* getThisPointer(lua_State* pLua);

    virtual void registerFunktions(lua_State* pLua);

    virtual void run();

    virtual bool OnEvent(const irr::SEvent&);

    //---- Lua funktions ------

    static int lua_ExitGame(lua_State* pLua);

    //---- Lua Constants ------

    static const char * lua_libName;

    static const luaL_reg lua_lib[];

    static const char* Lua_Object_Key;

private:

    Script::LuaEngine* m_script;

    irr::IrrlichtDevice* m_device;

    irr::video::IVideoDriver* m_driver;
};

#endif /* GAME_H_ */
