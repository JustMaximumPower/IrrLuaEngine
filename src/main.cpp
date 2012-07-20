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
#include "Game.h"
#include <iostream>

int main(int argc, const char* argv[])
{
#ifdef __debug__
	try
	{
#endif
#ifdef NO_STDOUT_BUFFERING
		setvbuf(stdout, NULL, _IONBF, 0);
#endif
		Game* game = new Game();

		game->init(argc, argv);

		int ret = game->run();

		delete game;

		return ret;

#ifdef __debug__
	} catch (std::exception& say)
	{
		printf("%s", say.what());
		return 1337;
	}
#endif
}
