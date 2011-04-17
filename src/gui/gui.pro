
TEMPLATE = app
TARGET = 
DESTDIR = $(BINDIR)/gui
OBJECTS_DIR = $(BINDIR)/gui
DEPENDPATH += .
INCLUDEPATH += .
INCLUDEPATH += $(SRCDIR)/main/
LIBS += -L$(BINDIR)/main -lvhc
QT += opengl

# Input
HEADERS += Camera.h ElementRenderer.h util.h Stage.h ParticleRenderer.h Renderer.h
SOURCES += Camera.cc ElementRenderer.cc util.cc Stage.cc ParticleRenderer.cc Main.cc 
