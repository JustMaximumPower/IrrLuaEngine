#include "Game.h"
#include <fstream>
#include <time.h>
#include "TestcaseEngine.h"

using namespace irr;

Game::Game()
{
    m_script = NULL;
	m_device = NULL;
	m_driver = NULL;
}

Game::~Game()
{
    delete m_script;
}


void rand_seed()
{
	time_t timeval; /* Current time. */
	unsigned char *ptr; /* Type punned pointed into timeval. */
	unsigned seed; /* Generated seed. */
	size_t i;

	timeval = time(NULL);
	ptr = (unsigned char *) &timeval;

	seed = 0;
	for (i = 0; i < sizeof timeval; i++)
		seed = seed * (UCHAR_MAX + 2u) + ptr[i];

	printf("seeding with %i", seed);
	srand(seed);
}

void Game::init(int argc, const char* argv[])
{

	rand_seed();

	irr::SIrrlichtCreationParameters s;

	s.AntiAlias = 0;
	s.Bits = 32;
    s.DriverType = irr::video::EDT_OPENGL;
	s.Fullscreen = false;
	s.Vsync = true;
	s.Stencilbuffer = false;
    s.WindowSize = irr::core::dimension2di(800,600);

	m_device = createDeviceEx(s);
    m_driver = m_device->getVideoDriver();

	//assert(m_device != NULL);

	m_device->setWindowCaption(L"LuaGuiEngine Test");

	irr::gui::IGUIFont* font = m_device->getGUIEnvironment()->getFont(
			"font.xml");
	irr::gui::IGUISkin* skin = m_device->getGUIEnvironment()->getSkin();
	skin->setFont(font);
	m_device->getGUIEnvironment()->setSkin(skin);

    m_script = new Gui::TestcaseEngine(m_device,this);
    m_script->init();
    m_script->runFile("main.lua");

	m_device->setEventReceiver(m_script);
}

int Game::run()
{

	while (m_device->run())
	{
        m_script->run();

		m_driver->beginScene(true, true);
        m_script->draw();
		m_driver->endScene();
		m_device->yield();
	}

	return 0;
}

void Game::closeGame()
{
    m_device->closeDevice();
}

irr::IrrlichtDevice* Game::getIrrlichtDevice() const
{
	return m_device;
}

irr::video::IVideoDriver* Game::getVideoDriver() const
{
	return m_driver;
}


