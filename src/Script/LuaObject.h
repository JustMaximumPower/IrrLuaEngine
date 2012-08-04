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
#ifndef LuaObject_h
#define LuaObject_h

#include <lua.hpp>
#include <IReferenceCounted.h>

namespace Script
{
     class LuaEngine;
}

namespace Script
{

     class LuaObject: public irr::IReferenceCounted
     {
     public:

          LuaObject(LuaEngine* engine);

          ~LuaObject();

          void pushToStack(lua_State* plua);

          void onEvent(const char* event);

          //----- Lua Constants ------

          static const char* Lua_Object_Metatable;

          static const struct luaL_reg s_methods[];

     protected:

          static LuaObject* lua_toLuaObject(lua_State* pLua, int index = 1);

          void addMethod(const char* name, lua_CFunction f);

          void addProperty(const char* name, lua_CFunction f);

          LuaEngine* m_engine;

     private:

          //----- Lua Funktions ------

          static int lua_GC(lua_State* pLua);

          static int lua_index(lua_State* pLua);

          static int lua_newindex(lua_State* pLua);

          int m_luaTableKey;

          lua_State* m_lua;

          const char* m_type;

     };

}

#endif 
