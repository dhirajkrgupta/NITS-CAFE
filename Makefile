include config.mk

# Compiler and linker
CXX = cl

# Compiler flags
CXXFLAGS = /EHsc /MT /nologo \
 /I"$(MYSQL_INCLUDE_PATH)" \
 /I"$(MYSQL_INCLUDE_PATH)\jdbc" \
 /I"dependencies/include"

# Linker flags
LDFLAGS = /link /nologo \
 /LIBPATH:"$(MYSQL_LIB_PATH)" \
 mysqlcppconn.lib

# Project files
OBJS = main.obj utility.obj customerdetails.obj menu.obj order.obj bill.obj reservations.obj
TARGET = main.exe

# Targets
# The default target, builds the final executable
all: $(TARGET)

# Rule to link the final executable from all object files
$(TARGET): $(OBJS)
	$(CXX) $** $(LDFLAGS) /out:$@
	del /Q /F *.obj

# compile main.cpp into main.obj
main.obj: main.cpp
	$(CXX) $(CXXFLAGS) /c main.cpp /Fo$@

#compile dependency source files into object files
utility.obj: dependencies/src/utility.cpp
	$(CXX) $(CXXFLAGS) /c dependencies/src/utility.cpp /Fo$@

customerdetails.obj: dependencies/src/customerdetails.cpp
	$(CXX) $(CXXFLAGS) /c dependencies/src/customerdetails.cpp /Fo$@

menu.obj: dependencies/src/menu.cpp
	$(CXX) $(CXXFLAGS) /c dependencies/src/menu.cpp /Fo$@

order.obj: dependencies/src/order.cpp
	$(CXX) $(CXXFLAGS) /c dependencies/src/order.cpp /Fo$@

bill.obj: dependencies/src/bill.obj
	$(CXX) $(CXXFLAGS) /c dependencies/src/bill.cpp /Fo$@
	
reservations.obj: dependencies/src/reservations.cpp
	$(CXX) $(CXXFLAGS) /c dependencies/src/reservations.cpp /Fo$@

#clean up build files
clean:
	del /Q /F *.obj *.exe