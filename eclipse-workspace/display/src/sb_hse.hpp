
#ifndef __SB_HSE_H_
#define __SB_HSE_H_

#include "sb_clk_src.hpp"

namespace SB
{

class Hse: public ClkSrc
{
protected:
	Hse();
public:
	~Hse();

	bool setEnabled( bool en );
	bool enabled();
protected:
	int type() const;
};

}

#endif
