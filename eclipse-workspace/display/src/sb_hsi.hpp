
#ifndef __SB_HSI_H_
#define __SB_HSI_H_

#include "sb_clk_src.hpp"

namespace SB
{

class Hsi: public ClkSrc
{
protected:
	Hsi();
public:
	~Hsi();

	bool setEnabled( bool en );
	bool enabled();
protected:
	int type() const;
};

}

#endif
