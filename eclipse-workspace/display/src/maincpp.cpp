/**
  ******************************************************************************
  * @file    main.c
  * @author  Ac6
  * @version V1.0
  * @date    01-December-2013
  * @brief   Default main function.
  ******************************************************************************
*/

#ifndef __MAIN_C_
#define __MAIN_C_

#include "stm32f4xx.h"
#include "stm32f429i_discovery.h"

extern "C"
{
	#include "cmsis_os.h"
}
#include "stm32f429i_discovery_lcd.h"
#include "stm32f429i_discovery_sdram.h"
extern "C"
{
	#include "lcd_log.h"
}

static void threadFunc( void * arg );
static void SystemClock_Config(void);
static void Display_DemoDescription(void);
static void sdramInit( void );
static void SDRAM_Initialization_Sequence(SDRAM_HandleTypeDef *hsdram, FMC_SDRAM_CommandTypeDef *Command);

int main(void)
{
	HAL_Init();

	BSP_LED_Init(LED3);
	BSP_LED_Init(LED4);

	SystemClock_Config();

	BSP_PB_Init( BUTTON_KEY, BUTTON_MODE_EXTI );

	sdramInit();

	BSP_LCD_Init();
	BSP_LCD_LayerDefaultInit(1, LCD_FRAME_BUFFER);

	LCD_LOG_Init();

	Display_DemoDescription();

	BSP_LCD_SetTextColor(LCD_COLOR_GREEN);
	BSP_LCD_DrawEllipse( 100, 100, 30, 50 );

#define LCD_LOG_DEFAULT_COLOR LCD_COLOR_LIGHTGRAY

	LCD_LOG_SetHeader( (uint8_t*)"Hi!" );
	LCD_LOG_SetFooter( (uint8_t*)"Bye!" );
	LCD_LOG_ClearTextZone();
	LCD_UsrLog( "Hello!" );
	LCD_DbgLog( "I\m alive!" );
	LCD_LOG_UpdateDisplay();

	//LCD_LOG_UpdateDisplay();

	//osThreadDef( threadName, threadFunc, osPriorityNormal, 0, 1024 );
	//osThreadId id = osThreadCreate( osThread( threadName ), 0);

	osKernelStart();

	for (;;);
}

static void threadFunc( void * arg )
{
	for( ;; );
}

static void SystemClock_Config(void)
{
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_OscInitTypeDef RCC_OscInitStruct;

  /* Enable Power Control clock */
  __HAL_RCC_PWR_CLK_ENABLE();

  /* The voltage scaling allows optimizing the power consumption when the device is
     clocked below the maximum system frequency, to update the voltage scaling value
     regarding system frequency refer to product datasheet.  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /* Enable HSE Oscillator and activate PLL with HSE as source */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 360;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  HAL_RCC_OscConfig(&RCC_OscInitStruct);

  /* Activate the Over-Drive mode */
  HAL_PWREx_EnableOverDrive();

  /* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2
     clocks dividers */
  RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;
  HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5);
}

static void Display_DemoDescription(void)
{
  uint8_t desc[50];

  /* Set LCD Foreground Layer  */
  BSP_LCD_SelectLayer(1);

  BSP_LCD_SetFont(&LCD_DEFAULT_FONT);

  /* Clear the LCD */
  BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
  BSP_LCD_Clear(LCD_COLOR_WHITE);

  /* Set the LCD Text Color */
  BSP_LCD_SetTextColor(LCD_COLOR_DARKBLUE);

  /* Display LCD messages */
  BSP_LCD_DisplayStringAt(0, 10, (uint8_t*)"STM32F429I BSP", CENTER_MODE);
  BSP_LCD_SetFont(&Font16);
  BSP_LCD_DisplayStringAt(0, 35, (uint8_t*)"Drivers examples", CENTER_MODE);

  /* Draw Bitmap */
  //BSP_LCD_DrawBitmap((BSP_LCD_GetXSize() - 80)/2, 65, (uint8_t *)stlogo);

  BSP_LCD_SetFont(&Font8);
  BSP_LCD_DisplayStringAt(0, BSP_LCD_GetYSize()- 20, (uint8_t*)"Copyright (c) STMicroelectronics 2014", CENTER_MODE);

  BSP_LCD_SetFont(&Font12);
  BSP_LCD_SetTextColor(LCD_COLOR_BLUE);
  BSP_LCD_FillRect(0, BSP_LCD_GetYSize()/2 + 15, BSP_LCD_GetXSize(), 60);
  BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
  BSP_LCD_SetBackColor(LCD_COLOR_BLUE);
  BSP_LCD_DisplayStringAt(0, BSP_LCD_GetYSize()/2 + 30, (uint8_t*)"Press USER Button to start:", CENTER_MODE);
  //sprintf((char *)desc,"%s example", BSP_examples[DemoIndex].DemoName);
  //BSP_LCD_DisplayStringAt(0, BSP_LCD_GetYSize()/2 + 45, (uint8_t *)desc, CENTER_MODE);
}


SDRAM_HandleTypeDef hsdram;
FMC_SDRAM_TimingTypeDef SDRAM_Timing;
FMC_SDRAM_CommandTypeDef command;

static void sdramInit( void )
{
	  /*##-1- Configure the SDRAM device #########################################*/
	  /* SDRAM device configuration */
	  hsdram.Instance = FMC_SDRAM_DEVICE;

	  /* Timing configuration for 90 MHz of SD clock frequency (180MHz/2) */
	  /* TMRD: 2 Clock cycles */
	  SDRAM_Timing.LoadToActiveDelay    = 2;
	  /* TXSR: min=70ns (6x11.90ns) */
	  SDRAM_Timing.ExitSelfRefreshDelay = 7;
	  /* TRAS: min=42ns (4x11.90ns) max=120k (ns) */
	  SDRAM_Timing.SelfRefreshTime      = 4;
	  /* TRC:  min=63 (6x11.90ns) */
	  SDRAM_Timing.RowCycleDelay        = 7;
	  /* TWR:  2 Clock cycles */
	  SDRAM_Timing.WriteRecoveryTime    = 2;
	  /* TRP:  15ns => 2x11.90ns */
	  SDRAM_Timing.RPDelay              = 2;
	  /* TRCD: 15ns => 2x11.90ns */
	  SDRAM_Timing.RCDDelay             = 2;

	  hsdram.Init.SDBank             = FMC_SDRAM_BANK2;
	  hsdram.Init.ColumnBitsNumber   = FMC_SDRAM_COLUMN_BITS_NUM_8;
	  hsdram.Init.RowBitsNumber      = FMC_SDRAM_ROW_BITS_NUM_12;
	  hsdram.Init.MemoryDataWidth    = SDRAM_MEMORY_WIDTH;
	  hsdram.Init.InternalBankNumber = FMC_SDRAM_INTERN_BANKS_NUM_4;
	  hsdram.Init.CASLatency         = FMC_SDRAM_CAS_LATENCY_3;
	  hsdram.Init.WriteProtection    = FMC_SDRAM_WRITE_PROTECTION_DISABLE;
	  hsdram.Init.SDClockPeriod      = SDCLOCK_PERIOD;
	  hsdram.Init.ReadBurst          = FMC_SDRAM_RBURST_DISABLE;
	  hsdram.Init.ReadPipeDelay      = FMC_SDRAM_RPIPE_DELAY_1;

	  /* Initialize the SDRAM controller */
	  if(HAL_SDRAM_Init(&hsdram, &SDRAM_Timing) != HAL_OK)
	  {
	    /* Initialization Error */
	    //Error_Handler();
		  return;
	  }

	  /* Program the SDRAM external device */
	  SDRAM_Initialization_Sequence(&hsdram, &command);

}

static void SDRAM_Initialization_Sequence(SDRAM_HandleTypeDef *hsdram, FMC_SDRAM_CommandTypeDef *Command)
{
  __IO uint32_t tmpmrd =0;
  /* Step 3:  Configure a clock configuration enable command */
  Command->CommandMode 			 = FMC_SDRAM_CMD_CLK_ENABLE;
  Command->CommandTarget 		 = FMC_SDRAM_CMD_TARGET_BANK2;
  Command->AutoRefreshNumber 	 = 1;
  Command->ModeRegisterDefinition = 0;

  /* Send the command */
  HAL_SDRAM_SendCommand(hsdram, Command, 0x1000);

  /* Step 4: Insert 100 ms delay */
  HAL_Delay(100);

  /* Step 5: Configure a PALL (precharge all) command */
  Command->CommandMode 			 = FMC_SDRAM_CMD_PALL;
  Command->CommandTarget 	     = FMC_SDRAM_CMD_TARGET_BANK2;
  Command->AutoRefreshNumber 	 = 1;
  Command->ModeRegisterDefinition = 0;

  /* Send the command */
  HAL_SDRAM_SendCommand(hsdram, Command, 0x1000);

  /* Step 6 : Configure a Auto-Refresh command */
  Command->CommandMode 			 = FMC_SDRAM_CMD_AUTOREFRESH_MODE;
  Command->CommandTarget 		 = FMC_SDRAM_CMD_TARGET_BANK2;
  Command->AutoRefreshNumber 	 = 4;
  Command->ModeRegisterDefinition = 0;

  /* Send the command */
  HAL_SDRAM_SendCommand(hsdram, Command, 0x1000);

  /* Step 7: Program the external memory mode register */
  tmpmrd = (uint32_t)SDRAM_MODEREG_BURST_LENGTH_2          |
                     SDRAM_MODEREG_BURST_TYPE_SEQUENTIAL   |
                     SDRAM_MODEREG_CAS_LATENCY_3           |
                     SDRAM_MODEREG_OPERATING_MODE_STANDARD |
                     SDRAM_MODEREG_WRITEBURST_MODE_SINGLE;

  Command->CommandMode = FMC_SDRAM_CMD_LOAD_MODE;
  Command->CommandTarget 		 = FMC_SDRAM_CMD_TARGET_BANK2;
  Command->AutoRefreshNumber 	 = 1;
  Command->ModeRegisterDefinition = tmpmrd;

  /* Send the command */
  HAL_SDRAM_SendCommand(hsdram, Command, 0x1000);

  /* Step 8: Set the refresh rate counter */
  /* (15.62 us x Freq) - 20 */
  /* Set the device refresh counter */
  HAL_SDRAM_ProgramRefreshRate(hsdram, REFRESH_COUNT);
}


#endif


