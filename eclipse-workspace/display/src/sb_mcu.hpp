
#ifndef __SB_MCU_H_
#define __SB_MCU_H_

namespace SB
{

enum CLKSRC
{
	HSI,
	LSI,
	HSE,
	LSE
};

class Mcu
{
private:
	Mcu();
public:
	~Mcu();
	static Mcu * signleton();

private:

	static Mcu g_mcu;
};

}

#endif

