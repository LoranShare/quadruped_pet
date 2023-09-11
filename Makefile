# Common settings
CC                  := arm-none-eabi-gcc
LD                  := arm-none-eabi-gcc
CP                  := arm-none-eabi-objcopy
SIZE                := arm-none-eabi-size
OUTPUT_DIR          := Output
PROGRAMM_NAME       := Quadruped
ELF                 := $(OUTPUT_DIR)/$(PROGRAMM_NAME).elf
BIN                 := $(OUTPUT_DIR)/$(PROGRAMM_NAME).bin


# Optimization
OPT                 ?=


# Location of source file directories
LD_SCRIPT_PATH      := scripts/ld/STM32F103XB_FLASH.ld
STARTUP_SOURCE_PATH := Submodules/cmsis_device_f1/Source/Templates/gcc/startup_stm32f103xb.s
APP_SOURCE_PATH     := Submodules/cmsis_device_f1/Source/Templates
APP_SOURCE_PATH     += Src/


# Location of include file directories
APP_INCLUDE_PATH    := Inc/
APP_INCLUDE_PATH    += Submodules/CMSIS_5/CMSIS/Core/Include/
APP_INCLUDE_PATH    += Submodules/cmsis_device_f1/Include/


# Optional target
OPT_TARGETS         =


# Compilation setup
EN_PREPROCESSOR_OUT ?=
LDFLAGS             := -T $(LD_SCRIPT_PATH)
LDFLAGS             += -Wl,-Map=$(OUTPUT_DIR)/$(PROGRAMM_NAME).map,--gc-sections,--cref

CFLAGS              := -Wall -Werror -Wunused
CFLAGS              += -std=c11


# Target specific
CFLAGS              += -mcpu=cortex-m3
CFLAGS              += -mthumb
# CFLAGS              += -print-multi-lib


ifeq ($(OPT), O2)
    CFLAGS += -O2
else ifeq ($(OPT), O1)
    CFLAGS += -O1
else ifeq ($(OPT), O3)
    CFLAGS += -O3
else ifeq ($(OPT), Os)
    CFLAGS += -Os
else ifeq ($(OPT), Oz)
    CFLAGS += -Oz
else ifeq ($(OPT), Omax)
    CFLAGS += -Omax
else
    CFLAGS += -O0
endif


# Debug
ifdef DEBUG_ENABLED
    CFLAGS += -g
endif


# Defenition all defines
DEFS                := STM32F103xB


# Finding all files and their paths
SOURCES             := $(shell find $(APP_SOURCE_PATH)  -maxdepth 1 -type f -name "*.c")
INCLUDES            := $(shell find $(APP_INCLUDE_PATH) -maxdepth 1 -type f -name "*.h")

INCLUDES_PATH       := $(addprefix -I , $(APP_INCLUDE_PATH))
DEFINES             := $(addprefix -D , $(DEFS))
OBJS                := $(patsubst %.c, %.o, $(SOURCES))
OBJS                += $(patsubst %.s, %.o, $(STARTUP_SOURCE_PATH))
OBJS                := $(addprefix $(OUTPUT_DIR)/, $(OBJS))

ifdef EN_PREPROCESSOR_OUT
    OPT_TARGETS     += PREPROCESSOR_OUTPUT
    PREPROC_OBJS    := $(patsubst %.c, %.i, $(SOURCES))
    PREPROC_OBJS    := $(addprefix $(OUTPUT_DIR)/, $(PREPROC_OBJS))
else
    PREPROC_OBJS    :=
endif


########### Build info ########################################################

$(info -----------------------)
$(info Build info)
$(info Compilator: $(CC))
$(info Compilator flags: $(CFLAGS))
$(info Linker flags: $(LDFLAGS))
$(info Include paths: $(APP_INCLUDE_PATH))
$(info Source files: $(SOURCES))
$(info -----------------------)


########### Debug info ########################################################

$(info Debug info)
$(info OBJS: $(OBJS))
$(info SOURCES_DIR: $(SOURCES_DIR))
$(info Source files: $(SOURCES))
ifdef EN_PREPROCESSOR_OUT
$(info Preprocessed files: $(PREPROC_OBJS))
endif
$(info -----------------------)


########### Make targets ######################################################

.PHONY: all
all: make_dir $(PROGRAMM_NAME)
	@echo "#*****************************************"
	@echo -n "# Size of ${ELF} in bytes is: ${size} " & stat -L -c %s ${BIN}
	@echo -n "# Size of ${ELF} in bytes is: ${size} " & stat -L -c %s ${ELF}
	@echo "#*****************************************"
	$(SIZE) $(ELF)


$(PROGRAMM_NAME) : $(BIN)
	@echo "Сompilation was successful"


$(BIN) : $(ELF)
	$(CP) -O binary $< $@


$(ELF) : $(OBJS)
	$(LD) $(LDFLAGS) $^ $(LIBS) -o $@


PREPROCESSOR_OUTPUT: $(PREPROC_OBJS)
	@echo "Preprocessing was successful"


$(OUTPUT_DIR)/%.o : %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES_PATH) $(DEFINES) -c $< -o $@


$(OUTPUT_DIR)/%.i : %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES_PATH) $(DEFINES) -E $< -o $@


$(OUTPUT_DIR)/%.o : %.s
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES_PATH) $(DEFINES) -c $< -o $@


.PHONY: clean
clean:
	rm -r -f $(OUTPUT_DIR)
	rm -f $(OBJS)


.PHONY: make_dir
make_dir:
	@mkdir -p $(OUTPUT_DIR)
