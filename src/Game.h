/*
 * Game.h
 *
 *  Created on: 03.04.2010
 *      Author: Max
 */

#ifndef GAME_H_
#define GAME_H_

#include <lua.hpp>
#include <irrlicht.h>

namespace Gui
{
    class TestcaseEngine;
}

class Game
{
public:

	Game();
	virtual ~Game();

	void init(int argc, const char* argv[]);

	int run();

	void closeGame();

	Gui::TestcaseEngine* getUserInterface() const;

	irr::IrrlichtDevice* getIrrlichtDevice() const;

	irr::video::IVideoDriver* getVideoDriver() const;

private:

    Gui::TestcaseEngine* m_script;

	irr::IrrlichtDevice* m_device;

	irr::video::IVideoDriver* m_driver;
};

#endif /* GAME_H_ */
