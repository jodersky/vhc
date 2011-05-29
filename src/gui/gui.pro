
TEMPLATE = app
TARGET = 
DESTDIR = $(BINDIR)/gui
OBJECTS_DIR = $(BINDIR)/gui
DEPENDPATH += .
INCLUDEPATH += .
INCLUDEPATH += $(SRCDIR)/main/
LIBS += -L$(BINDIR)/main -lvhc
QT += opengl

#CONFIG += DEBUG
#QMAKE_CXXFLAGS_DEBUG += -g
#QMAKE_LFLAGS_DEBUG += -g


# Input
HEADERS += Camera.h ElementRenderer.h util.h  KeyManager.h Stage.h BeamRenderer.h Renderer.h
SOURCES += Camera.cc ElementRenderer.cc util.cc KeyManager.cc Stage.cc BeamRenderer.cc Main.cc 
