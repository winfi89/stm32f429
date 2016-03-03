
#ifndef __SB_CLK_SRC_H_
#define __SB_CLK_SRC_H_

namespace SB
{

class Mcu;

class ClkSrc
{
protected:
	ClkSrc();
public:
	virtual ~ClkSrc();

	virtual bool setEnabled( bool en ) = 0;
	virtual bool enabled() = 0;
protected:
	virtual int type() const = 0;

	friend class Mcu;
};


}



#endif


