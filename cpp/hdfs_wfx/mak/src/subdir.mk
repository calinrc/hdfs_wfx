################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/FileEnumerator.cpp \
../src/HDFSAccessor.cpp \
../src/JVMState.cpp \
../src/Logger.cpp \
../src/hdfs_wfx.cpp 

OBJS += \
./src/FileEnumerator.o \
./src/HDFSAccessor.o \
./src/JVMState.o \
./src/Logger.o \
./src/hdfs_wfx.o 

CPP_DEPS += \
./src/FileEnumerator.d \
./src/HDFSAccessor.d \
./src/JVMState.d \
./src/Logger.d \
./src/hdfs_wfx.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -DLINUX $(DEBUG_FLAG) -I../include -I${JAVA_HOME}/include -I${JAVA_HOME}/include/linux $(COMPILE_OPTIMIZE_PARAMS) -Wall -c -fmessage-length=0 -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


