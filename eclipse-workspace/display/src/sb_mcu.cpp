
#include "sb_mcu.hpp"

namespace SB
{

Mcu::Mcu()
{

}

Mcu::~Mcu()
{

}

Mcu * Mcu::signleton()
{
	static Mcu mcu;
	return &mcu;
}

}
