###########################################################################
# GLFW top level Makefile
#
# This file works as a top level makefile for all supported systems and
# compilers. It builds both the GLFW link library and the supplied example
# programs.
###########################################################################

###########################################################################
# If your make program does not set the $(MAKE) variable correctly,
# uncomment the following line and make sure that the name of the make
# tool is correct.
###########################################################################
# MAKE = make


###########################################################################
# If no system/compiler is specified, display a list of available options
###########################################################################
default:
	@echo "This is the root makefile for the GLFW library."
	@echo ""
	@echo "Use one of the following commands:"
	@echo "-----------------------------------------------------------------------------"
	@echo "  $(MAKE) win32-mingw        to compile for Windows using MinGW"
	@echo "  $(MAKE) mingw-clean        to remove any files generated for this target"
	@echo "-----------------------------------------------------------------------------"
	@echo "  $(MAKE) win32-msys         to compile for Windows using MinGW and MSYS"
	@echo "  $(MAKE) msys-clean         to remove any files generated for this target"
	@echo "  $(MAKE) msys-install       to install the GLFW header and static library"
	@echo "-----------------------------------------------------------------------------"
	@echo "  $(MAKE) win32-lcc          to compile for Windows using LCC-Win32"
	@echo "  $(MAKE) win32-ow           to compile for Windows using OpenWatcom"
	@echo "  $(MAKE) win32-clean        to remove any files generated for this target"
	@echo "-----------------------------------------------------------------------------"
	@echo "  $(MAKE) cross-mgw          to compile for Windows using MinGW on Unix" 
	@echo "  $(MAKE) cross-mgw-clean    to remove any files generated for this target"
	@echo "  $(MAKE) cross-mgw-install  to install the GLFW library and header"
	@echo "-----------------------------------------------------------------------------"
	@echo "  $(MAKE) x11                to compile for X11 on Unix-like systems"
	@echo "  $(MAKE) x11-clean          to remove any files generated for this target"
	@echo "  $(MAKE) x11-dist-clean     to also removed the configuration files"
	@echo "  $(MAKE) x11-install        to install the GLFW header and static library"
	@echo "  $(MAKE) x11-dist-install   to also install the GLFW shared library"
	@echo "-----------------------------------------------------------------------------"
	@echo "  $(MAKE) cocoa              to compile GLFW for Cocoa on Mac OS X"
	@echo "  $(MAKE) cocoa-clean        to remove any files generated for this target"
	@echo "  $(MAKE) cocoa-install      to install the GLFW header and static library"
	@echo "  $(MAKE) cocoa-dist-install to also install the GLFW dynamic library"
	@echo "-----------------------------------------------------------------------------"
	@echo " There are also Microsoft Visual C++ 2008 and 2010 project files available in"
	@echo " the support/msvc90 and support/msvc100 directories, respectively."
	@echo "-----------------------------------------------------------------------------"


###########################################################################
# Bare MinGW on Windows
###########################################################################

win32-mingw:
	@cmd /c compile.bat $(MAKE) mingw

mingw-clean:
	@cmd /c compile.bat CLEAN


###########################################################################
# Cygwin on Windows
###########################################################################

CYGWIN=PREFIX=/bin TARGET=i686-pc-mingw32-

cygwin-install: win32-cygwin
	cd lib/win32 && env $(CYGWIN) $(MAKE) -f Makefile.win32.cross-mgw install

win32-cygwin:
	cd lib/win32 && env $(CYGWIN) $(MAKE) -f Makefile.win32.cross-mgw
	cd examples  && env $(CYGWIN) $(MAKE) -f Makefile.win32.cross-mgw
	cd tests     && env $(CYGWIN) $(MAKE) -f Makefile.win32.cross-mgw

cygwin-clean:
	cd lib/win32 && env $(CYGWIN) $(MAKE) -f Makefile.win32.cross-mgw clean
	cd examples  && env $(CYGWIN) $(MAKE) -f Makefile.win32.cross-mgw clean
	cd tests     && env $(CYGWIN) $(MAKE) -f Makefile.win32.cross-mgw clean


###########################################################################
# MSYS on Windows
###########################################################################

msys-install: win32-msys
	cd lib/win32 && $(MAKE) -f Makefile.win32.msys install

win32-msys:
	cd lib/win32 && $(MAKE) -f Makefile.win32.msys
	cd examples  && $(MAKE) -f Makefile.win32.msys
	cd tests     && $(MAKE) -f Makefile.win32.msys

msys-clean:
	cd lib/win32 && $(MAKE) -f Makefile.win32.msys clean
	cd examples  && $(MAKE) -f Makefile.win32.msys clean
	cd tests     && $(MAKE) -f Makefile.win32.msys clean


###########################################################################
# Various compilers on Windows
###########################################################################

# Windows, LCC-Win32
win32-lcc:
	@.\\compile.bat $(MAKE) lcc

# Windows, OpenWatcom
win32-ow:
	@.\\compile.bat $(MAKE) ow

# Cleanup for Windows
win32-clean:
	@.\\compile.bat CLEAN


###########################################################################
# MinGW cross-compile to Windows from Unix 
###########################################################################

cross-mgw-install: cross-mgw 
	cd lib/win32 && $(MAKE) -f Makefile.win32.cross-mgw install 

cross-mgw:
	cd lib/win32 && $(MAKE) -f Makefile.win32.cross-mgw
	cd examples  && $(MAKE) -f Makefile.win32.cross-mgw 
	cd tests     && $(MAKE) -f Makefile.win32.cross-mgw

cross-mgw-clean:
	cd lib/win32 && $(MAKE) -f Makefile.win32.cross-mgw clean 
	cd examples  && $(MAKE) -f Makefile.win32.cross-mgw clean
	cd tests     && $(MAKE) -f Makefile.win32.cross-mgw clean


###########################################################################
# X11 on Unix-like systems
###########################################################################

MAKEFILES_X11_IN = lib/x11/Makefile.x11.in examples/Makefile.x11.in \
		   tests/Makefile.x11.in

MAKEFILES_X11 = lib/x11/Makefile.x11 examples/Makefile.x11 tests/Makefile.x11

# Cleanup for X11 (must be here due to generated makefile)
x11-clean: $(MAKEFILES_X11)
	cd lib/x11  && $(MAKE) -f Makefile.x11 clean
	cd examples && $(MAKE) -f Makefile.x11 clean
	cd tests    && $(MAKE) -f Makefile.x11 clean

x11-dist-clean: x11-clean
	rm -f config.log
	rm -f $(MAKEFILES_X11)
	rm -f lib/x11/libglfw.pc.in

# Auto configuration for X11
$(MAKEFILES_X11) : compile.sh $(MAKEFILES_X11_IN)
	@sh ./compile.sh

# X11
x11: $(MAKEFILES_X11)
	cd lib/x11  && $(MAKE) -f Makefile.x11
	cd examples && $(MAKE) -f Makefile.x11
	cd tests    && $(MAKE) -f Makefile.x11

# X11 install
x11-install: x11
	cd lib/x11 && $(MAKE) -f Makefile.x11 install

# X11 dist install
x11-dist-install: x11
	cd lib/x11 && $(MAKE) -f Makefile.x11 dist-install


###########################################################################
# Cocoa on Mac OS X
###########################################################################

cocoa:
	cd lib/cocoa && $(MAKE) -f Makefile.cocoa
	cd examples  && $(MAKE) -f Makefile.cocoa
	cd tests     && $(MAKE) -f Makefile.cocoa

cocoa-clean:
	cd lib/cocoa && $(MAKE) -f Makefile.cocoa clean
	cd examples  && $(MAKE) -f Makefile.cocoa clean
	cd tests     && $(MAKE) -f Makefile.cocoa clean

cocoa-install: cocoa
	cd lib/cocoa && $(MAKE) -f Makefile.cocoa install

cocoa-dist-install: cocoa
	cd lib/cocoa && $(MAKE) -f Makefile.cocoa dist-install

