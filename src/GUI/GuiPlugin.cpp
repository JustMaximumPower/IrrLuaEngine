#include "GuiPlugin.h"
#include "IrrlichtDevice.h"
#include "IGUIEnvironment.h"
#include "GuiButton.h"
#include "GuiWidget.h"
#include "GuiImage.h"
#include "GuiEditBox.h"
#include "Textur.h"

namespace Gui
{
    const char* GuiPlugin::Lua_Object_Key = "GuiPluginKey";

    const struct luaL_reg GuiPlugin::lua_globls[] =
    {
    { NULL, NULL } /* sentinel */
    };

    GuiPlugin::GuiPlugin(irr::IrrlichtDevice* irr)
    {
        m_device = irr;
    }

    void GuiPlugin::draw()
    {
        m_device->getGUIEnvironment()->drawAll();
    }

    void GuiPlugin::run()
    {

    }

    void GuiPlugin::init()
    {

    }

    int GuiPlugin::getFreeId(Gui::GuiElement* e)
    {
        m_elements.push_back(e);
        return m_elements.size();
    }

    void GuiPlugin::freeElement(int i)
    {
        m_elements[i - 1] = NULL;
    }

    irr::IrrlichtDevice* GuiPlugin::getIrrlichtDevice()
    {
        return m_device;
    }

    bool GuiPlugin::OnEvent(const irr::SEvent& e)
    {
        if (e.EventType == irr::EET_GUI_EVENT)
        {
            if (e.GUIEvent.Caller)
            {
                int id = e.GUIEvent.Caller->getID();
                Gui::GuiElement* element = getElement(id);
                if (element)
                {
                    switch (e.GUIEvent.EventType)
                    {

                        case irr::gui::EGET_BUTTON_CLICKED:
                            element->onEvent("onButton");
                            break;

                        case irr::gui::EGET_ELEMENT_HOVERED:
                            element->onEvent("onHover");
                            break;

                        case irr::gui::EGET_ELEMENT_FOCUSED:
                            element->onEvent("onFocused");
                            break;

                        case irr::gui::EGET_ELEMENT_FOCUS_LOST:
                            element->onEvent("onFocusLost");
                            break;

                        case irr::gui::EGDT_WINDOW_CLOSE:
                            element->onEvent("onWindowClose");
                            return true;
                            break;

                    }
                }
            }
        }
        return false;
    }

    Gui::GuiElement* GuiPlugin::getElement(int id)
    {
        if (id > 0 && id <= (int) m_elements.size() && m_elements[id - 1])
        {
            return m_elements[id - 1];
        }
        return NULL;
    }

    GuiPlugin* GuiPlugin::getThisPointer(lua_State* pLua)
    {
        lua_pushlightuserdata(pLua, (void *) Lua_Object_Key); /* push address */
        lua_gettable(pLua, LUA_REGISTRYINDEX); /* retrieve value */
        GuiPlugin* e = (GuiPlugin*) lua_touserdata(pLua, -1);
        lua_pop(pLua, 1);
        return e;
    }

    void GuiPlugin::registerFunktions(lua_State* pLua)
    {
        m_lua = pLua;
        /* store a number */
        lua_pushlightuserdata(m_lua, (void *) Lua_Object_Key); /* push address */
        lua_pushlightuserdata(m_lua, (void *) this); /* push value */
        /* registry[&Key] = myNumber */
        lua_settable(m_lua, LUA_REGISTRYINDEX);

        luaL_openlib(pLua, GuiButton::lua_libName, GuiButton::lua_lib_f, 0);
        luaL_openlib(pLua, GuiWidget::lua_libName, GuiWidget::lua_lib_f, 0);
        luaL_openlib(pLua, GuiEditBox::lua_libName, GuiEditBox::lua_lib_f, 0);
        luaL_openlib(pLua, GuiImage::lua_libName, GuiImage::lua_lib_f, 0);
        luaL_openlib(pLua, Video::Textur::lua_libName, Video::Textur::lua_lib_f, 0);
    }

}
