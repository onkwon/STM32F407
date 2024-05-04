# SPDX-License-Identifier: MIT

SDK_ROOT ?= external/STM32CubeF4
LD_SCRIPT ?= $(PORT_ROOT)/STM32F407VETx_FLASH.ld

ST_SRCS = \
	$(SDK_ROOT)/Drivers/CMSIS/Device/ST/STM32F4xx/Source/Templates/gcc/startup_stm32f407xx.s \
	$(SDK_ROOT)/Drivers/CMSIS/Device/ST/STM32F4xx/Source/Templates/system_stm32f4xx.c \
	\
	$(SDK_ROOT)/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pcd.c \
	$(SDK_ROOT)/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pcd_ex.c \
	$(SDK_ROOT)/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_ll_usb.c \
	$(SDK_ROOT)/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal.c \
	$(SDK_ROOT)/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rcc.c \
	$(SDK_ROOT)/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rcc_ex.c \
	$(SDK_ROOT)/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash.c \
	$(SDK_ROOT)/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash_ex.c \
	$(SDK_ROOT)/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash_ramfunc.c \
	$(SDK_ROOT)/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_gpio.c \
	$(SDK_ROOT)/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_exti.c \
	$(SDK_ROOT)/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dma.c \
	$(SDK_ROOT)/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dma_ex.c \
	$(SDK_ROOT)/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pwr.c \
	$(SDK_ROOT)/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pwr_ex.c \
	$(SDK_ROOT)/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_cortex.c \
	$(SDK_ROOT)/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_adc.c \
	$(SDK_ROOT)/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_adc_ex.c \
	$(SDK_ROOT)/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_ll_adc.c \
	$(SDK_ROOT)/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_can.c \
	$(SDK_ROOT)/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_i2c.c \
	$(SDK_ROOT)/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_i2c_ex.c \
	$(SDK_ROOT)/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_qspi.c \
	$(SDK_ROOT)/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_tim.c \
	$(SDK_ROOT)/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_tim_ex.c \
	$(SDK_ROOT)/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_uart.c \
	$(SDK_ROOT)/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_usart.c \
	\
	$(SDK_ROOT)/Middlewares/Third_Party/FreeRTOS/Source/croutine.c \
	$(SDK_ROOT)/Middlewares/Third_Party/FreeRTOS/Source/event_groups.c \
	$(SDK_ROOT)/Middlewares/Third_Party/FreeRTOS/Source/list.c \
	$(SDK_ROOT)/Middlewares/Third_Party/FreeRTOS/Source/queue.c \
	$(SDK_ROOT)/Middlewares/Third_Party/FreeRTOS/Source/stream_buffer.c \
	$(SDK_ROOT)/Middlewares/Third_Party/FreeRTOS/Source/tasks.c \
	$(SDK_ROOT)/Middlewares/Third_Party/FreeRTOS/Source/timers.c \
	$(SDK_ROOT)/Middlewares/Third_Party/FreeRTOS/Source/portable/MemMang/heap_4.c \
	$(SDK_ROOT)/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F/port.c \
	$(wildcard $(PORT_ROOT)/*.c) \
	$(wildcard $(PORT_ROOT)/*.cpp) \
	$(PORT_ROOT)/Core/Src/main.c \
	$(PORT_ROOT)/Core/Src/gpio.c \
	$(PORT_ROOT)/Core/Src/stm32f4xx_hal_msp.c \
	$(PORT_ROOT)/Core/Src/stm32f4xx_hal_timebase_tim.c \
	$(PORT_ROOT)/Core/Src/stm32f4xx_it.c \
	\
	$(LIBMCU_ROOT)/ports/freertos/board.c \
	$(LIBMCU_ROOT)/ports/freertos/pthread.c \
	$(LIBMCU_ROOT)/ports/freertos/pthread_mutex.c \
	$(LIBMCU_ROOT)/ports/freertos/semaphore.c \
	$(LIBMCU_ROOT)/ports/freertos/timext.c \
	$(LIBMCU_ROOT)/ports/stubs/syscall.c \
	$(SDK_ROOT)/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/cmsis_os2.c \

ST_INCS = \
	$(SDK_ROOT)/Drivers/STM32F4xx_HAL_Driver/Inc \
	$(SDK_ROOT)/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy \
	$(SDK_ROOT)/Drivers/CMSIS/Device/ST/STM32F4xx/Include \
	$(SDK_ROOT)/Drivers/CMSIS/Include \
	$(SDK_ROOT)/Middlewares/Third_Party/FreeRTOS/Source/include \
	$(SDK_ROOT)/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F \
	$(SDK_ROOT)/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 \
	\
	$(PORT_ROOT) \
	$(PORT_ROOT)/Core/Inc \

ST_DEFS = \
	USE_HAL_DRIVER \
	STM32F407xx \
	\
	asm=__asm__ \

$(addprefix $(OUTDIR)/, $(ST_SRCS:%=%.o)): CFLAGS+=-Wno-error

INCS += $(ST_INCS)
DEFS += $(ST_DEFS)

ST_OUTPUT := $(OUTDIR)/libstm32.a
ST_OBJS := $(addprefix $(OUTDIR)/, $(ST_SRCS:%=%.o))
$(eval $(call generate_lib, $(ST_OUTPUT), $(ST_OBJS)))

$(addprefix $(OUTDIR)/, $(SRCS:%=%.o)): $(BASEDIR)/external/STM32CubeF4
$(BASEDIR)/external/STM32CubeF4:
	$(info downloading  STM32CubeF4)
	$(Q)git clone --recurse-submodules https://github.com/STMicroelectronics/STM32CubeF4.git $@

.PHONY: flash flash_usb erase gdbserver
## flash_usb: flash with dfu-util
flash_usb: $(OUTBIN)
	dfu-util --alt 0 --dfuse-address 0x08000000 --download $<
## flash: flash with j-link
flash: $(OUTDIR)/$(PROJECT).jlink
	JLinkExe -if swd -device stm32f407ve -speed 4000 -CommanderScript $<
$(OUTDIR)/$(PROJECT).jlink: $(OUTBIN)
	echo "r\nloadbin $<, 0x08000000\nr\nq" > $@
## erase: erase flash with dfu-util
erase:
	dfu-util --alt 0 --dfuse-address 0x08000000:mass-erase:force
## gdbserver: open gdb server
gdbserver:
	$(Q)pyocd $@ -t stm32f407ve
