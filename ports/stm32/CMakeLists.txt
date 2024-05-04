# SPDX-License-Identifier: MIT

AUX_SOURCE_DIRECTORY(${CMAKE_CURRENT_LIST_DIR} PORT_SRCS)

set(SDK_ROOT ${CMAKE_SOURCE_DIR}/external/STM32CubeF4)
set(ST_SRCS
	${SDK_ROOT}/Drivers/CMSIS/Device/ST/STM32F4xx/Source/Templates/gcc/startup_stm32f407xx.s
	${SDK_ROOT}/Drivers/CMSIS/Device/ST/STM32F4xx/Source/Templates/system_stm32f4xx.c

	${SDK_ROOT}/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pcd.c
	${SDK_ROOT}/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pcd_ex.c
	${SDK_ROOT}/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_ll_usb.c
	${SDK_ROOT}/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal.c
	${SDK_ROOT}/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rcc.c
	${SDK_ROOT}/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rcc_ex.c
	${SDK_ROOT}/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash.c
	${SDK_ROOT}/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash_ex.c
	${SDK_ROOT}/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash_ramfunc.c
	${SDK_ROOT}/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_gpio.c
	${SDK_ROOT}/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_exti.c
	${SDK_ROOT}/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dma.c
	${SDK_ROOT}/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dma_ex.c
	${SDK_ROOT}/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pwr.c
	${SDK_ROOT}/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pwr_ex.c
	${SDK_ROOT}/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_cortex.c
	${SDK_ROOT}/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_adc.c
	${SDK_ROOT}/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_adc_ex.c
	${SDK_ROOT}/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_ll_adc.c
	${SDK_ROOT}/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_can.c
	${SDK_ROOT}/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_i2c.c
	${SDK_ROOT}/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_i2c_ex.c
	${SDK_ROOT}/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_qspi.c
	${SDK_ROOT}/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_tim.c
	${SDK_ROOT}/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_tim_ex.c
	${SDK_ROOT}/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_uart.c
	${SDK_ROOT}/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_usart.c

	${SDK_ROOT}/Middlewares/Third_Party/FreeRTOS/Source/croutine.c
	${SDK_ROOT}/Middlewares/Third_Party/FreeRTOS/Source/event_groups.c
	${SDK_ROOT}/Middlewares/Third_Party/FreeRTOS/Source/list.c
	${SDK_ROOT}/Middlewares/Third_Party/FreeRTOS/Source/queue.c
	${SDK_ROOT}/Middlewares/Third_Party/FreeRTOS/Source/stream_buffer.c
	${SDK_ROOT}/Middlewares/Third_Party/FreeRTOS/Source/tasks.c
	${SDK_ROOT}/Middlewares/Third_Party/FreeRTOS/Source/timers.c
	${SDK_ROOT}/Middlewares/Third_Party/FreeRTOS/Source/portable/MemMang/heap_4.c
	${SDK_ROOT}/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F/port.c

	${PORT_SRCS}
	${CMAKE_CURRENT_LIST_DIR}/Core/Src/main.c
	${CMAKE_CURRENT_LIST_DIR}/Core/Src/gpio.c
	${CMAKE_CURRENT_LIST_DIR}/Core/Src/stm32f4xx_hal_msp.c
	${CMAKE_CURRENT_LIST_DIR}/Core/Src/stm32f4xx_hal_timebase_tim.c
	${CMAKE_CURRENT_LIST_DIR}/Core/Src/stm32f4xx_it.c

	${CMAKE_SOURCE_DIR}/external/libmcu/ports/freertos/board.c
	${CMAKE_SOURCE_DIR}/external/libmcu/ports/freertos/pthread.c
	${CMAKE_SOURCE_DIR}/external/libmcu/ports/freertos/pthread_mutex.c
	${CMAKE_SOURCE_DIR}/external/libmcu/ports/freertos/semaphore.c
	${CMAKE_SOURCE_DIR}/external/libmcu/ports/freertos/timext.c
	${CMAKE_SOURCE_DIR}/external/libmcu/ports/stubs/syscall.c
	${SDK_ROOT}/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/cmsis_os2.c
)
set(ST_INCS
	${SDK_ROOT}/Drivers/STM32F4xx_HAL_Driver/Inc
	${SDK_ROOT}/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy
	${SDK_ROOT}/Drivers/CMSIS/Device/ST/STM32F4xx/Include
	${SDK_ROOT}/Drivers/CMSIS/Include
	${SDK_ROOT}/Middlewares/Third_Party/FreeRTOS/Source/include
	${SDK_ROOT}/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F
	${SDK_ROOT}/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2

	${CMAKE_CURRENT_LIST_DIR}
	${CMAKE_CURRENT_LIST_DIR}/Core/Inc
)
set(ST_DEFS
	USE_HAL_DRIVER
	STM32F407xx

	asm=__asm__
)

if (NOT EXISTS ${SDK_ROOT})
	message(INFO "Downloading STM32CubeF4")
	set(FETCHCONTENT_QUIET FALSE)
	include(FetchContent)
	FetchContent_Declare(stm32_sdk
		GIT_REPOSITORY "https://github.com/STMicroelectronics/STM32CubeF4.git"
		GIT_TAG "master"
		GIT_PROGRESS TRUE
		SOURCE_DIR "${SDK_ROOT}"
	)
	FetchContent_MakeAvailable(stm32_sdk)
endif()

add_library(stm32 OBJECT ${ST_SRCS})
target_include_directories(stm32 PUBLIC ${ST_INCS} ${APP_INCS})
target_compile_definitions(stm32 PUBLIC ${ST_DEFS})
