#########################################################################
#                         Makefile récursif                             #
#=======================================================================#
# Les variables suivantes sont définies dans un makefile plus haut.     #
# BASEDIR   répertoire de base du projet                                #
# SRCDIR    répertoire contenant le code source                         #
# BINDIR    répertoire où sont placés tous les objets compilé           #
#########################################################################

# Nom du répertoire contenant ce makefile
LOCALDIR = main

# ==> Ajouter ici les objets à compiler
# Si un objet nécessite une compilation non-standard (i.e. pas de règle du style Foo.o : Foo.cc Foo.h), rajouter
# cette règle.
LOCALOBJS = Vector3D.o Particle.o Printable.o Element.o CurvedElement.o StraightElement.o \
			CompositeElement.o Dipole.o Quadrupole.o FODO.o ElementVisitor.o Cloneable.o Accelerator.o exceptions.o Stepper.o Beam.o

OBJS=$(addprefix $(BINDIR)/$(LOCALDIR)/,$(LOCALOBJS))
.PHONY = all checkdirs lib

all: checkdirs lib

# Vérifie l'existence du répertoire de sortie
checkdirs: $(BINDIR)/$(LOCALDIR)

# Crée le répertoire de sortie
$(BINDIR)/$(LOCALDIR):
	@mkdir -p $@

# Crée une librairie statique des fichiers objets 
lib: $(OBJS)
	@echo "Packing library..."
	ar rcs $(BINDIR)/$(LOCALDIR)/libvhc.a $(OBJS)
	@echo "Done packing library."  

# Règle implicite qui modifie le répertoire de destination des fichiers .o
$(BINDIR)/$(LOCALDIR)/%.o: %.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@
