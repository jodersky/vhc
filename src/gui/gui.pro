
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
HEADERS += GLWidget.h Camera.h ElementRenderer.h util.h
SOURCES += Main.cc GLWidget.cc Camera.h ElementRenderer.cc util.cc
