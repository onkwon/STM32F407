# SPDX-License-Identifier: Apache-2.0

include projects/arch/cm4f.mk

app-src-dirs := src
APP_SRCS = $(foreach dir, $(addprefix $(BASEDIR)/, $(app-src-dirs)), \
	$(shell find $(dir) -type f \( -iname \*.c -o -iname \*.cpp \)))

# Platfrom
TARGET_PLATFORM := stm32
PORT_ROOT := ports/$(TARGET_PLATFORM)
PLATFORM_SPECIFIC := $(PORT_ROOT)/platform.mk

# Third Party
LIBMCU_ROOT ?= $(BASEDIR)/external/libmcu
LIBMCU_MODULES := button cli logging metrics
LIBMCU_INTERFACES := adc i2c l4 uart gpio
include $(LIBMCU_ROOT)/projects/modules.mk
include $(LIBMCU_ROOT)/projects/interfaces.mk

SRCS += $(APP_SRCS) \
	$(LIBMCU_MODULES_SRCS) \
	$(LIBMCU_INTERFACES_SRCS) \
	$(LIBMCU_ROOT)/ports/armcm/fault.c \
	$(LIBMCU_ROOT)/ports/armcm/assert.c \

INCS += $(BASEDIR)/include \
	$(LIBMCU_MODULES_INCS) \
	$(LIBMCU_INTERFACES_INCS) \
	$(LIBMCU_ROOT)/ports/armcm/include \
	$(PORT_ROOT) \

DEFS += $(PROJECT) \
	BUILD_DATE=$(BUILD_DATE) \
	VERSION_TAG=$(VERSION_TAG) \
	VERSION=$(VERSION) \
	\
	_POSIX_THREADS \
	_POSIX_C_SOURCE=200809L \
	\
	METRICS_USER_DEFINES=\"$(BASEDIR)/include/metrics.def\" \
	LOGGING_MESSAGE_MAXLEN=256 \

OBJS += $(addprefix $(OUTDIR)/, $(SRCS:%=%.o))
LIBDIRS += $(OUTDIR)
CFLAGS += -include libmcu/assert.h

include $(PLATFORM_SPECIFIC)
