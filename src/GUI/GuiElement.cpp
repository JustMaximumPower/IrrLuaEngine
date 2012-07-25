#include "GuiElement.h"
#include "LuaEngine.h"
#include "GuiPlugin.h"


namespace Gui 
{


    GuiElement::GuiElement(GuiPlugin* plugin, lua_State* plua)
    {
        m_plugin = plugin;
        m_parent = NULL;
        m_type = "";
        m_lua = plua;

        m_id = m_plugin->getFreeId(this);
        lua_pushlightuserdata(m_lua, (void *)this);  /* push value */
        lua_newtable(m_lua);
        /* registry[&Key] = myNumber */
        lua_settable(m_lua, LUA_REGISTRYINDEX);
    }

    
    GuiElement::~GuiElement()
    {
        m_plugin->freeElement(m_id);

        lua_pushlightuserdata(m_lua, (void *)this);  /* push value */
        lua_pushnil(m_lua);
        /* registry[&Key] = myNumber */
        lua_settable(m_lua, LUA_REGISTRYINDEX);
    }
    
    void GuiElement::pushToStack()
    {
        GuiElement** otherThis = (GuiElement**)lua_newuserdata(m_lua,sizeof(void*));
        *otherThis = this;
        int index = lua_gettop(m_lua);
        luaL_getmetatable(m_lua, getMetaTableName());
        lua_setmetatable(m_lua, index);
        grab();
    }
    
    void GuiElement::onEvent(const char* event)
    {
        Script::LuaEngine* engine = Script::LuaEngine::getThisPointer(m_lua);

        lua_pushlightuserdata(m_lua, (void *)this);  /* push address */
        lua_gettable(m_lua, LUA_REGISTRYINDEX);  /* retrieve value */
        lua_pushfstring(m_lua,event);
        lua_gettable(m_lua, -2);

        if(lua_isfunction(m_lua,-1))
        {
            pushToStack();
            engine->doCall(1,0);
        }
    }

    void GuiElement::onLuaGC()
    {
        drop();
    }

    void GuiElement::onLuaIndex()
    {
        const char* key = luaL_checkstring(m_lua, 2);

        if(!strcmp("type",key))
        {
            lua_pushstring(m_lua,m_type);
            return;
        }

        lua_getmetatable(m_lua, 1);
        lua_getfield(m_lua, -1, key);

        if(!lua_isnil(m_lua, -1))
	        return;

        lua_settop(m_lua, 2);

        lua_pushlightuserdata(m_lua, (void *)this);  /* push address */
        lua_gettable(m_lua, LUA_REGISTRYINDEX);  /* retrieve value */
        lua_insert(m_lua,2);
        lua_gettable(m_lua, 2);
    }

    void GuiElement::onLuaNewIndex()
    {
        lua_pushlightuserdata(m_lua, (void *)this);  /* push address */
        lua_gettable(m_lua, LUA_REGISTRYINDEX);  /* retrieve value */
        lua_insert(m_lua,2);
        lua_settable(m_lua, 2);
    }


} /* End of namespace Gui */
