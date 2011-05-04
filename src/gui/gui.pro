
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
#QMAKE_CXXFLAGS_DEBUG += -pg
#QMAKE_LFLAGS_DEBUG += -pg


# Input
HEADERS += Camera.h ElementRenderer.h util.h  KeyManager.h Stage.h ParticleRenderer.h Renderer.h
SOURCES += Camera.cc ElementRenderer.cc util.cc KeyManager.cc Stage.cc ParticleRenderer.cc Main.cc 
