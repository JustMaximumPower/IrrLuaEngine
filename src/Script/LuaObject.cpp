#include "LuaObject.h"
#include "LuaEngine.h"

namespace Script
{
    const char* LuaObject::Lua_Object_Metatable = "LuaObject.Metatable";

    const struct luaL_reg LuaObject::s_methods[] =
    {
    { "__gc", lua_GC },
    { "__index", lua_index },
    { "__newindex", lua_newindex },
    { NULL, NULL } /* sentinel */
    };

    LuaObject::LuaObject(LuaEngine* engine)
    {
        m_type = "";
        m_lua = engine->getLuaState();
        m_engine = engine;

        lua_newtable(m_lua);
        int table = lua_gettop(m_lua);
        lua_newtable(m_lua);
        lua_setfield(m_lua, table, "_methods");
        lua_newtable(m_lua);
        lua_setfield(m_lua, table, "_properties");
        m_luaTableKey = luaL_ref(m_lua, LUA_REGISTRYINDEX);
    }

    LuaObject::~LuaObject()
    {
        luaL_unref(m_lua, LUA_REGISTRYINDEX, m_luaTableKey);
    }

    void LuaObject::pushToStack(lua_State* plua)
    {
        LuaObject** other = (LuaObject**) lua_newuserdata(plua, sizeof(void*));
        *other = this;
        luaL_getmetatable(plua, Lua_Object_Metatable);
        lua_setmetatable(plua, -2);
        grab();
    }

    void LuaObject::onEvent(const char* event)
    {
        Script::LuaEngine* engine = Script::LuaEngine::getThisPointer(m_lua);

        lua_rawgeti(m_lua, LUA_REGISTRYINDEX, m_luaTableKey);
        lua_getfield(m_lua, -1, event);
        lua_remove(m_lua, -2);

        if (lua_isfunction(m_lua,-1))
        {
            pushToStack(m_lua);
            engine->doCall(1, 0);
        }
        else
        {
            lua_pop(m_lua, 1);
        }
    }

    int LuaObject::lua_GC(lua_State* pLua)
    {
        printf("LuaObject::lua_GC\n");
        LuaObject* pthis = lua_toLuaObject(pLua);

        pthis->drop();

        return 0;
    }

    int LuaObject::lua_index(lua_State* pLua)
    {
        LuaObject* pthis = lua_toLuaObject(pLua);
        const char* key = luaL_checkstring(pLua, 2);
        lua_rawgeti(pLua, LUA_REGISTRYINDEX, pthis->m_luaTableKey);

        lua_getfield(pLua, 3, "_methods");
        lua_getfield(pLua, 4, key);

        if (lua_isfunction(pLua,-1))
        {
            return 1;
        }

        lua_settop(pLua, 3);
        lua_getfield(pLua, 3, "_properties");
        lua_getfield(pLua, 4, key);

        if (lua_isfunction(pLua,-1))
        {
            lua_insert(pLua, 1);
            lua_settop(pLua, 3);
            lua_call(pLua, 2, 1);
            return 1;
        }

        lua_getfield(pLua, 3, key);
        return 1;
    }

    int LuaObject::lua_newindex(lua_State* pLua)
    {
        LuaObject* pthis = lua_toLuaObject(pLua);
        const char* key = luaL_checkstring(pLua, 2);
        lua_rawgeti(pLua, LUA_REGISTRYINDEX, pthis->m_luaTableKey);

        lua_settop(pLua, 4);
        lua_getfield(pLua, 4, "_properties");
        lua_getfield(pLua, 5, key);

        if (lua_isfunction(pLua,-1))
        {
            lua_insert(pLua, 1);
            lua_settop(pLua, 4);
            lua_call(pLua, 3, 0);
            return 0;
        }

        lua_pushvalue(pLua, 3);
        lua_setfield(pLua, 4, key);
        return 0;
    }

    LuaObject* LuaObject::lua_toLuaObject(lua_State* pLua, int index)
    {
        return *static_cast<LuaObject**>(luaL_checkudata(pLua, index,
                Lua_Object_Metatable));
    }

    void LuaObject::addMethod(const char* name, lua_CFunction f)
    {
        lua_rawgeti(m_lua, LUA_REGISTRYINDEX, m_luaTableKey);
        lua_getfield(m_lua, -1, "_methods");
        lua_pushcfunction(m_lua, f);
        lua_setfield(m_lua, -2, name);
        lua_pop(m_lua, 2);
    }

    void LuaObject::addProperty(const char* name, lua_CFunction f)
    {
        lua_rawgeti(m_lua, LUA_REGISTRYINDEX, m_luaTableKey);
        lua_getfield(m_lua, -1, "_properties");
        lua_pushcfunction(m_lua, f);
        lua_setfield(m_lua, -2, name);
        lua_pop(m_lua, 2);
    }

} /* End of namespace Gui */
