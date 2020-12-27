#pragma once
#include "../render/include/window.hpp"

namespace td {
namespace graphic {


class main_window
{
	public:
		window m_window;

		user_interface(SDL_Rect _windowPos) : m_window(_window) {}

};

}
}

#endif // USER_INTERFACE_HPP
