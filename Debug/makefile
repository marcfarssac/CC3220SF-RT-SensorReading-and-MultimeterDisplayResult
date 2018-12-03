################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := C:/ti/ccsv8/tools/compiler/ti-cgt-arm_18.9.0.STS

GEN_OPTS += C:/TICC3220SF/tirtos_builds_CC3220SF_LAUNCHXL_release_ccs/Debug/configPkg/compiler.opt
GEN_OPTS__FLAG := --cmd_file="C:/TICC3220SF/tirtos_builds_CC3220SF_LAUNCHXL_release_ccs/Debug/configPkg/compiler.opt"
GEN_CMDS += C:/TICC3220SF/tirtos_builds_CC3220SF_LAUNCHXL_release_ccs/Debug/configPkg/linker.cmd
GEN_CMDS__FLAG := -l"C:/TICC3220SF/tirtos_builds_CC3220SF_LAUNCHXL_release_ccs/Debug/configPkg/linker.cmd"

ORDERED_OBJS += \
"./ADCReading.obj" \
"./CC3220SF_LAUNCHXL.obj" \
"./adcReadWrite.obj" \
"./main_tirtos.obj" \
"../CC3220SF_LAUNCHXL_TIRTOS.cmd" \
-l"ti/display/lib/display.aem4" \
-l"ti/grlib/lib/ccs/m4/grlib.a" \
-l"third_party/spiffs/lib/ccs/m4/spiffs.a" \
-l"ti/drivers/lib/drivers_cc32xx.aem4" \
-l"third_party/fatfs/lib/ccs/m4/fatfs.a" \
-l"ti/dpl/lib/dpl_cc32xx.aem4" \
$(GEN_CMDS__FLAG) \
-l"ti/devices/cc32xx/driverlib/ccs/Release/driverlib.a" \
-llibc.a \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(INO_DEPS)),)
-include $(INO_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(SV7A_DEPS)),)
-include $(SV7A_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(PDE_DEPS)),)
-include $(PDE_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXE_OUTPUTS += \
adcReadWrite_CC3220SF_LAUNCHXL_tirtos_ccs.out \

EXE_OUTPUTS__QUOTED += \
"adcReadWrite_CC3220SF_LAUNCHXL_tirtos_ccs.out" \

BIN_OUTPUTS += \
adcReadWrite_CC3220SF_LAUNCHXL_tirtos_ccs.bin \

BIN_OUTPUTS__QUOTED += \
"adcReadWrite_CC3220SF_LAUNCHXL_tirtos_ccs.bin" \


# All Target
all: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@$(MAKE) --no-print-directory -Onone "adcReadWrite_CC3220SF_LAUNCHXL_tirtos_ccs.out"

dependents:
	-cd C:/TICC3220SF/tirtos_builds_CC3220SF_LAUNCHXL_release_ccs/Debug && $(MAKE) all

# Tool invocations
adcReadWrite_CC3220SF_LAUNCHXL_tirtos_ccs.out: $(OBJS) $(CMD_SRCS) $(GEN_CMDS) C:/TICC3220SF/tirtos_builds_CC3220SF_LAUNCHXL_release_ccs/Debug/tirtos_builds_CC3220SF_LAUNCHXL_release_ccs.lib
	@echo 'Building target: "$@"'
	@echo 'Invoking: ARM Linker'
	"C:/ti/ccsv8/tools/compiler/ti-cgt-arm_18.9.0.STS/bin/armcl" -mv7M4 --code_state=16 --float_support=vfplib -me -g --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on -z -m"adcReadWrite_CC3220SF_LAUNCHXL_tirtos_ccs.map" -i"C:/ti/simplelink_cc32xx_sdk_2_30_00_05/source" -i"C:/ti/simplelink_cc32xx_sdk_2_30_00_05/kernel/tirtos/packages" -i"C:/ti/ccsv8/tools/compiler/ti-cgt-arm_18.9.0.STS/lib" --diag_wrap=off --display_error_number --warn_sections --xml_link_info="adcReadWrite_CC3220SF_LAUNCHXL_tirtos_ccs_linkInfo.xml" --rom_model -o "adcReadWrite_CC3220SF_LAUNCHXL_tirtos_ccs.out" $(ORDERED_OBJS)
	@echo 'Finished building target: "$@"'
	@echo ' '
	@$(MAKE) --no-print-directory post-build

adcReadWrite_CC3220SF_LAUNCHXL_tirtos_ccs.bin: $(EXE_OUTPUTS)
	@echo 'Building files: $(strip $(EXE_OUTPUTS__QUOTED))'
	@echo 'Invoking: ARM Hex Utility'
	"C:/ti/ccsv8/tools/compiler/ti-cgt-arm_18.9.0.STS/bin/armhex"  -o "adcReadWrite_CC3220SF_LAUNCHXL_tirtos_ccs.bin" $(EXE_OUTPUTS__QUOTED)
	@echo 'Finished building: $(strip $(EXE_OUTPUTS__QUOTED))'
	@echo ' '
	@$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(BIN_OUTPUTS__QUOTED)$(EXE_OUTPUTS__QUOTED)
	-$(RM) "ADCReading.obj" "CC3220SF_LAUNCHXL.obj" "adcReadWrite.obj" "main_tirtos.obj" 
	-$(RM) "CC3220SF_LAUNCHXL.d" "adcReadWrite.d" "main_tirtos.d" 
	-$(RM) "ADCReading.d" 
	-@echo 'Finished clean'
	-@echo ' '

post-build:
	-C:/ti/ccsv8/utils/tiobj2bin/tiobj2bin adcReadWrite_CC3220SF_LAUNCHXL_tirtos_ccs.out adcReadWrite_CC3220SF_LAUNCHXL_tirtos_ccs.bin C:/ti/ccsv8/tools/compiler/ti-cgt-arm_18.9.0.STS/bin/armofd C:/ti/ccsv8/tools/compiler/ti-cgt-arm_18.9.0.STS/bin/armhex C:/ti/ccsv8/utils/tiobj2bin/mkhex4bin
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:
C:/TICC3220SF/tirtos_builds_CC3220SF_LAUNCHXL_release_ccs/Debug/tirtos_builds_CC3220SF_LAUNCHXL_release_ccs.lib:

-include ../makefile.targets

