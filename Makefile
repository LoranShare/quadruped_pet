CC					:= arm-none-eabi-gcc
OUTPUT_DIR			:= Output
PROGRAMM_NAME		:= Quadruped


# Location of source file directories
APP_SOURCE_PATH		:= Submodules/cmsis_device_f1/Source/Templates
APP_SOURCE_PATH		+= Src/


# Location of include file directories
APP_INCLUDE_PATH	:= Inc/
APP_INCLUDE_PATH	+= Submodules/CMSIS_5/CMSIS/Core/Include/
APP_INCLUDE_PATH	+= Submodules/cmsis_device_f1/Include/


# Location of startup file directories
# APP_STARTUP_PATH	:= Submodules/cmsis_device_f1/Source/Templates/gcc/


# Defenition all defines
DEFS				:= STM32F103xB


# Finding all files and their paths
SOURCES				:= $(shell find $(APP_SOURCE_PATH)  -maxdepth 1 -type f -name "*.c")
INCLUDES			:= $(shell find $(APP_INCLUDE_PATH)	-maxdepth 1 -type f -name "*.h")


INCLUDES_PATH		:= $(addprefix -I , $(APP_INCLUDE_PATH))
DEFINES				:= $(addprefix -D , $(DEFS))
OBJS				:= $(patsubst %.c, %.o, $(SOURCES))
OBJS				:= $(addprefix $(OUTPUT_DIR)/, $(OBJS))


########### Build info ########################################################

$(info -----------------------)
$(info Build info)
$(info Compilator: $(CC))
$(info Include paths: $(APP_INCLUDE_PATH))
$(info Source files: $(SOURCES))
$(info -----------------------)


########### Debug info ########################################################

$(info Debug info)
$(info OBJS: $(OBJS))
$(info SOURCES_DIR: $(SOURCES_DIR))
$(info Source files: $(SOURCES))
$(info -----------------------)


########### Make targets ######################################################

.PHONY: all
all: make_dir $(PROGRAMM_NAME)
	@echo "Programm \"$(PROGRAMM_NAME)\" successfully built"


$(PROGRAMM_NAME): $(OBJS)
	@echo "Сompilation was successful"


$(OUTPUT_DIR)/%.o : %.c
	@mkdir -p $(dir $@)
	$(CC) $(INCLUDES_PATH) $(DEFINES) -c $< -o $@


.PHONY: clean
clean:
	rm -r -f $(OUTPUT_DIR)
	rm -f $(OBJS)


.PHONY: make_dir
make_dir:
	@mkdir -p $(OUTPUT_DIR)