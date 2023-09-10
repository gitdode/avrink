#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=avr-gcc
CCC=avr-g++
CXX=avr-g++
FC=gfortran
AS=avr-as

# Macros
CND_PLATFORM=AVR2.1-GCC13.2-Linux
CND_DLIB_EXT=so
CND_CONF=Custom
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include /home/dode/dev/avrink/Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/_ext/48b98c45/avrink.o \
	${OBJECTDIR}/_ext/48b98c45/bitmaps.o \
	${OBJECTDIR}/_ext/48b98c45/cmd.o \
	${OBJECTDIR}/_ext/48b98c45/dejavu.o \
	${OBJECTDIR}/_ext/48b98c45/display.o \
	${OBJECTDIR}/_ext/48b98c45/eink.o \
	${OBJECTDIR}/_ext/48b98c45/font.o \
	${OBJECTDIR}/_ext/48b98c45/spi.o \
	${OBJECTDIR}/_ext/48b98c45/sram.o \
	${OBJECTDIR}/_ext/48b98c45/unifont.o \
	${OBJECTDIR}/_ext/48b98c45/usart.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/avrink

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/avrink: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.c} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/avrink ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/_ext/48b98c45/avrink.o: /home/dode/dev/avrink/avrink.c
	${MKDIR} -p ${OBJECTDIR}/_ext/48b98c45
	$(COMPILE.c) -g -DBAUD=9600 -DF_CPU=8000000UL -D__AVR_ATmega328P__ -D__flash=volatile -I. -std=c99 -o ${OBJECTDIR}/_ext/48b98c45/avrink.o /home/dode/dev/avrink/avrink.c

${OBJECTDIR}/_ext/48b98c45/bitmaps.o: /home/dode/dev/avrink/bitmaps.c
	${MKDIR} -p ${OBJECTDIR}/_ext/48b98c45
	$(COMPILE.c) -g -DBAUD=9600 -DF_CPU=8000000UL -D__AVR_ATmega328P__ -D__flash=volatile -I. -std=c99 -o ${OBJECTDIR}/_ext/48b98c45/bitmaps.o /home/dode/dev/avrink/bitmaps.c

${OBJECTDIR}/_ext/48b98c45/cmd.o: /home/dode/dev/avrink/cmd.c
	${MKDIR} -p ${OBJECTDIR}/_ext/48b98c45
	$(COMPILE.c) -g -DBAUD=9600 -DF_CPU=8000000UL -D__AVR_ATmega328P__ -D__flash=volatile -I. -std=c99 -o ${OBJECTDIR}/_ext/48b98c45/cmd.o /home/dode/dev/avrink/cmd.c

${OBJECTDIR}/_ext/48b98c45/dejavu.o: /home/dode/dev/avrink/dejavu.c
	${MKDIR} -p ${OBJECTDIR}/_ext/48b98c45
	$(COMPILE.c) -g -DBAUD=9600 -DF_CPU=8000000UL -D__AVR_ATmega328P__ -D__flash=volatile -I. -std=c99 -o ${OBJECTDIR}/_ext/48b98c45/dejavu.o /home/dode/dev/avrink/dejavu.c

${OBJECTDIR}/_ext/48b98c45/display.o: /home/dode/dev/avrink/display.c
	${MKDIR} -p ${OBJECTDIR}/_ext/48b98c45
	$(COMPILE.c) -g -DBAUD=9600 -DF_CPU=8000000UL -D__AVR_ATmega328P__ -D__flash=volatile -I. -std=c99 -o ${OBJECTDIR}/_ext/48b98c45/display.o /home/dode/dev/avrink/display.c

${OBJECTDIR}/_ext/48b98c45/eink.o: /home/dode/dev/avrink/eink.c
	${MKDIR} -p ${OBJECTDIR}/_ext/48b98c45
	$(COMPILE.c) -g -DBAUD=9600 -DF_CPU=8000000UL -D__AVR_ATmega328P__ -D__flash=volatile -I. -std=c99 -o ${OBJECTDIR}/_ext/48b98c45/eink.o /home/dode/dev/avrink/eink.c

${OBJECTDIR}/_ext/48b98c45/font.o: /home/dode/dev/avrink/font.c
	${MKDIR} -p ${OBJECTDIR}/_ext/48b98c45
	$(COMPILE.c) -g -DBAUD=9600 -DF_CPU=8000000UL -D__AVR_ATmega328P__ -D__flash=volatile -I. -std=c99 -o ${OBJECTDIR}/_ext/48b98c45/font.o /home/dode/dev/avrink/font.c

${OBJECTDIR}/_ext/48b98c45/spi.o: /home/dode/dev/avrink/spi.c
	${MKDIR} -p ${OBJECTDIR}/_ext/48b98c45
	$(COMPILE.c) -g -DBAUD=9600 -DF_CPU=8000000UL -D__AVR_ATmega328P__ -D__flash=volatile -I. -std=c99 -o ${OBJECTDIR}/_ext/48b98c45/spi.o /home/dode/dev/avrink/spi.c

${OBJECTDIR}/_ext/48b98c45/sram.o: /home/dode/dev/avrink/sram.c
	${MKDIR} -p ${OBJECTDIR}/_ext/48b98c45
	$(COMPILE.c) -g -DBAUD=9600 -DF_CPU=8000000UL -D__AVR_ATmega328P__ -D__flash=volatile -I. -std=c99 -o ${OBJECTDIR}/_ext/48b98c45/sram.o /home/dode/dev/avrink/sram.c

${OBJECTDIR}/_ext/48b98c45/unifont.o: /home/dode/dev/avrink/unifont.c
	${MKDIR} -p ${OBJECTDIR}/_ext/48b98c45
	$(COMPILE.c) -g -DBAUD=9600 -DF_CPU=8000000UL -D__AVR_ATmega328P__ -D__flash=volatile -I. -std=c99 -o ${OBJECTDIR}/_ext/48b98c45/unifont.o /home/dode/dev/avrink/unifont.c

${OBJECTDIR}/_ext/48b98c45/usart.o: /home/dode/dev/avrink/usart.c
	${MKDIR} -p ${OBJECTDIR}/_ext/48b98c45
	$(COMPILE.c) -g -DBAUD=9600 -DF_CPU=8000000UL -D__AVR_ATmega328P__ -D__flash=volatile -I. -std=c99 -o ${OBJECTDIR}/_ext/48b98c45/usart.o /home/dode/dev/avrink/usart.c

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}

# Subprojects
.clean-subprojects:
