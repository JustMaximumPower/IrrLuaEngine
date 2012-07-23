#include "GuiWidget.h"
#include "LuaEngine.h"
#include "GuiPlugin.h"
#include "IrrlichtDevice.h"
#include "IGUIEnvironment.h"
#include "GuiButton.h"
#include "IGUIElement.h"



namespace Gui 
{

    const char* GuiWidget::lua_libName = "Widget";

    const char* GuiWidget::lua_metatableName = "Lua.Widget";

    const struct luaL_reg GuiWidget::lua_lib_m [] = {
        {"__gc",lua_GC},
        {"__index",lua_index},
        {"__newindex",lua_newindex},
        {"addElement",lua_addElement},
        {NULL, NULL}  /* sentinel */
    };

    const struct luaL_reg GuiWidget::lua_lib_f [] = {
        {"new",lua_new},
        {NULL, NULL}  /* sentinel */
    };

    void GuiWidget::createMatatable(lua_State* pLua)
    {
        luaL_newmetatable(pLua, lua_metatableName);
    
        luaL_openlib(pLua, NULL, lua_lib_m, 0);
        luaL_openlib(pLua, lua_libName, lua_lib_f, 0);
    }


    GuiWidget::GuiWidget(GuiPlugin* plugin, lua_State* plua):GuiElement(plugin, plua)
    {
        m_irrElement = NULL;
        m_type = lua_metatableName;
    }
    
    GuiWidget::~GuiWidget()
    {
        printf("GuiWidget::~GuiWidget\n");

        for(irr::u32 i = 0; i < m_children.size(); i++)
        {
            m_children[i]->drop();
        }
        m_children.clear();
       

        if(m_irrElement)
        {
/*            Script::LuaEngine* engine = Script::LuaEngine::getThisPointer(m_lua);
            engine->getIrrlichtDevice()->getGUIEnvironment()->getRootGUIElement()->removeChild(m_irrElement);
  */          
            m_irrElement->remove();
            //m_irrElement->drop();
            m_irrElement = NULL;
        }
    }

    const luaL_reg* GuiWidget::getMethods()
    {
        return lua_lib_m;
    }
        
    const luaL_reg* GuiWidget::getFunktions()
    {
        return lua_lib_f;
    }

    const char* GuiWidget::getTableName()
    {
        return lua_libName;
    }

    const char* GuiWidget::getMetaTableName()
    {
        return lua_metatableName;
    }


    int GuiWidget::lua_GC(lua_State* pLua)
    {
        printf("GuiWidget::lua_GC\n");
        GuiWidget* pthis = *static_cast<GuiWidget**>(luaL_checkudata(pLua, 1, lua_metatableName));
        
        pthis->onLuaGC();

        return 0;
    }

    int GuiWidget::lua_new(lua_State* pLua)
    {
        GuiPlugin* plugin = GuiPlugin::getThisPointer(pLua);
        Script::LuaEngine* engine = Script::LuaEngine::getThisPointer(pLua);
        GuiWidget* pthis = new GuiWidget(plugin,pLua);

        pthis->pushToStack();

        pthis->drop();

        int x = (int)lua_tonumber(pLua,1);
        int y = (int)lua_tonumber(pLua,2);
        int w = (int)lua_tonumber(pLua,3);
        int h = (int)lua_tonumber(pLua,4);

        size_t len;
        const char* text    = luaL_optlstring(pLua,5,"",&len);
        wchar_t* textw      =  new wchar_t[++len];
        mbstowcs(textw, text, len);


        irr::gui::IGUIWindow* b = engine->getIrrlichtDevice()->getGUIEnvironment()->addWindow(
                irr::core::recti(x,y,x+w,y+h),
                false,
                textw,
                NULL,
                pthis->getId()
            );

        pthis->m_irrElement = b;

        delete textw;

        return 1;
    }

    
    int GuiWidget::lua_index(lua_State* pLua)
    {
        GuiWidget* pthis = *static_cast<GuiWidget**>(luaL_checkudata(pLua, 1, lua_metatableName));
        const char* key = luaL_checkstring(pLua, 2);

        if(!strcmp("toolTip",key))
        {
            const irr::core::stringw& wtip = pthis->m_irrElement->getToolTipText();
            char* tip = new char[wtip.size()+1];
            wcstombs(tip,wtip.c_str(),wtip.size()+1);
            lua_pushstring(pLua,tip);
            delete tip;
            return 1;
        }
        else if(!strcmp("text",key))
        {
            const irr::core::stringw& wtip = pthis->m_irrElement->getText();
            char* tip = new char[wtip.size()+1];
            wcstombs(tip,wtip.c_str(),wtip.size()+1);
            lua_pushstring(pLua,tip);
            delete tip;
            return 1;
        }
        else if(!strcmp("enabled",key))
        {
            lua_pushboolean(pLua,pthis->m_irrElement->isEnabled());
            return 1;
        }
        else if(!strcmp("visible",key))
        {
            lua_pushboolean(pLua,pthis->m_irrElement->isVisible());
            return 1;
        }


        pthis->onLuaIndex();
        return 1;
    }


    int GuiWidget::lua_newindex(lua_State* pLua)
    {
        GuiWidget* pthis = *static_cast<GuiWidget**>(luaL_checkudata(pLua, 1, lua_metatableName));
        const char* key = luaL_checkstring(pLua, 2);

        if(!strcmp("toolTip",key))
        {
            const char* text = luaL_checkstring(pLua, 3);
            irr::core::stringw wtext(text);
            pthis->m_irrElement->setToolTipText(wtext.c_str());

            return 0;
        }
        else if(!strcmp("text",key))
        {
            const char* text = luaL_checkstring(pLua, 3);
            irr::core::stringw wtext(text);
            pthis->m_irrElement->setText(wtext.c_str());

            return 0;
        }
        else if(!strcmp("enabled",key))
        {
            bool b = lua_toboolean(pLua,3) != 0;
            pthis->m_irrElement->setEnabled(b);

            return 0;
        }
        else if(!strcmp("visible",key))
        {
            bool b = lua_toboolean(pLua,3) != 0;
            pthis->m_irrElement->setVisible(b);

            return 0;
        }


        pthis->onLuaNewIndex();
        return 0;
    }
    
    int GuiWidget::lua_addElement(lua_State* pLua)
    {
        GuiWidget* pthis = *static_cast<GuiWidget**>(luaL_checkudata(pLua, 1, lua_metatableName));
        GuiElement* e = NULL;
        lua_getfield(pLua,2,"type");

        const char* type = lua_tostring(pLua,-1);

        GuiElement* pother = *static_cast<GuiElement**>(luaL_checkudata(pLua, 2, type));

        pthis->m_children.push_back(pother);
        pother->grab();

        irr::gui::IGUIElement* irrE = pother->getIrrlichtElement();

        if(irrE)
        {
            pthis->m_irrElement->addChild(irrE);
        }

        return 0;
    }

    void GuiWidget::draw()
    {
        if(m_irrElement)
        {
            m_irrElement->draw();
        }

        for(irr::u32 i = 0; i < m_children.size(); i++)
        {
            m_children[i]->draw();
        }
    }

    irr::gui::IGUIElement* GuiWidget::getIrrlichtElement()
    {
        return m_irrElement;
    }
   

} /* End of namespace Gui */

