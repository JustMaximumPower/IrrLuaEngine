#include "GuiElement.h"
#include "LuaEngine.h"
#include "GuiPlugin.h"
#include "IrrlichtDevice.h"
#include "IGUIEnvironment.h"
#include "GuiButton.h"
#include "IGUIElement.h"

namespace Gui
{
     const struct luaL_reg GuiElement::lua_lib_m[] =
     {
     { "remove", luaRemove },
     { NULL, NULL } /* sentinel */
     };

     const struct luaL_reg GuiElement::lua_lib_p[] =
     {
     { "toolTip", luaToolTip },
     { "text", luaText },
     { "enabled", luaEnabled },
     { "visible", luaVisible },
     { "id", luaId },
     { "tabOrder", luaTabOrder },
     { NULL, NULL } /* sentinel */
     };

     GuiElement::GuiElement(GuiPlugin* plugin, Script::LuaEngine* engine, lua_State* plua) :
               Script::LuaObject(engine)
     {
          m_plugin = plugin;
          m_parent = NULL;

          m_id = m_plugin->getFreeId(this);

          const struct luaL_reg* i = lua_lib_m;

          while(i->func && i->name)
          {
               addMethod(i->name, i->func);
               i++;
          }

          i = lua_lib_p;
          while(i->func && i->name)
          {
               addProperty(i->name, i->func);
               i++;
          }

     }

     GuiElement::~GuiElement()
     {
          printf("GuiElement::~GuiElement\n");

          if (m_irrelement)
          {
               m_irrelement->remove();
               m_irrelement = NULL;
          }
          m_plugin->freeElement(m_id);
     }

     const int GuiElement::getId() const
     {
          return m_id;
     }

     irr::gui::IGUIElement* GuiElement::getIrrlichtElement() const
     {
          return m_irrelement;
     }

     GuiElement* GuiElement::lua_toGuiElement(lua_State* pLua, int index)
     {
          GuiElement* pthis =
                    dynamic_cast<GuiElement*>(Script::LuaObject::lua_toLuaObject(pLua,
                              index));

          if (!pthis)
          {
               luaL_error(pLua, "Type missmatch for arg #%i", index);
          }
          return pthis;
     }

     int GuiElement::luaRemove(lua_State* pLua)
     {
          GuiElement* pthis = lua_toGuiElement(pLua);

          if (pthis->m_irrelement)
          {
               pthis->m_irrelement->remove();
               pthis->m_irrelement = NULL;
          }
          return 0;
     }

     int GuiElement::luaToolTip(lua_State* pLua)
     {
          GuiElement* pthis = lua_toGuiElement(pLua);
          const char* key = luaL_checkstring(pLua, 2);

          if (lua_gettop(pLua) == 2)
          {
               const irr::core::stringw& wtip = pthis->m_irrelement->getToolTipText();
               char* tip = new char[wtip.size() + 1];
               wcstombs(tip, wtip.c_str(), wtip.size() + 1);
               lua_pushstring(pLua, tip);
               delete tip;
               return 1;
          }
          else
          {
               const char* text = luaL_checkstring(pLua, 3);
               irr::core::stringw wtext(text);
               pthis->m_irrelement->setToolTipText(wtext.c_str());

               return 0;
          }

          return 0;
     }

     int GuiElement::luaText(lua_State* pLua)
     {
          GuiElement* pthis = lua_toGuiElement(pLua);
          const char* key = luaL_checkstring(pLua, 2);

          if (lua_gettop(pLua) == 2)
          {
               const irr::core::stringw& wtip = pthis->m_irrelement->getText();
               char* tip = new char[wtip.size() + 1];
               wcstombs(tip, wtip.c_str(), wtip.size() + 1);
               lua_pushstring(pLua, tip);
               delete tip;
               return 1;
          }
          else
          {
               const char* text = luaL_checkstring(pLua, 3);
               irr::core::stringw wtext(text);
               pthis->m_irrelement->setText(wtext.c_str());

               return 0;
          }

          return 0;
     }

     int GuiElement::luaEnabled(lua_State* pLua)
     {
          GuiElement* pthis = lua_toGuiElement(pLua);
          const char* key = luaL_checkstring(pLua, 2);

          if (lua_gettop(pLua) == 2)
          {
               lua_pushboolean(pLua, pthis->m_irrelement->isEnabled());
               return 1;
          }
          else
          {
               bool b = lua_toboolean(pLua, 3) != 0;
               pthis->m_irrelement->setEnabled(b);

               return 0;
          }

          return 0;
     }

     int GuiElement::luaVisible(lua_State* pLua)
     {
          GuiElement* pthis = lua_toGuiElement(pLua);
          const char* key = luaL_checkstring(pLua, 2);

          if (lua_gettop(pLua) == 2)
          {
               lua_pushboolean(pLua, pthis->m_irrelement->isVisible());
               return 1;
          }
          else
          {
               bool b = lua_toboolean(pLua, 3) != 0;
               pthis->m_irrelement->setVisible(b);

               return 0;
          }

          return 0;
     }

     int GuiElement::luaId(lua_State* pLua)
     {
          GuiElement* pthis = lua_toGuiElement(pLua);
          const char* key = luaL_checkstring(pLua, 2);

          if (lua_gettop(pLua) == 2)
          {
               lua_pushnumber(pLua, pthis->m_id);
               return 1;
          }
          else
          {
               return luaL_error(pLua, "property id is readonly");
          }

          return 0;
     }

     int GuiElement::luaTabOrder(lua_State* pLua)
     {
          GuiElement* pthis = lua_toGuiElement(pLua);
          const char* key = luaL_checkstring(pLua, 2);

          if (lua_gettop(pLua) == 2)
          {
               lua_pushnumber(pLua, pthis->m_irrelement->getTabOrder());
               return 1;
          }
          else
          {
               bool b = lua_toboolean(pLua, 3) != 0;
               pthis->m_irrelement->setVisible(b);

               return 0;
          }

          return 0;
     }

} /* End of namespace Gui */
