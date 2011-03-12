#########################################################################
#                         Makefile recursif                             #
#=======================================================================#
# Les variables suivantes sont definis dans un makefile plus haut.      #
# BASEDIR	repertoire de base du projet                                #
# SRCDIR	repertoire contenant le code source                         #
# BINDIR	repertoire ou sont places toutes objets compiles            #
#########################################################################

# Nom du repertoire contenant ce makefile
LOCALDIR = main

# ==> Ajouter ici les objets a compiler
# Si un objet necessite une compilation non-standard (i.e. pas de regle du style Foo.o : Foo.cc Foo.h), rajouter
# cette regle.
OBJS = Vector3D.o Particle.o

all: checkdirs lib

# Verifie l'existance du repertoire de sortie
checkdirs: $(BINDIR)/$(LOCALDIR)

# Cree le repertoire de sortie
$(BINDIR)/$(LOCALDIR):
	@mkdir -p $@

# Cree une librairie statique des fichiers objets 
lib: $(OBJS)
	@echo "Packing library..."
	ar rcs $(BINDIR)/$(LOCALDIR)/libvhc.a $(addprefix $(BINDIR)/$(LOCALDIR)/,$(OBJS))
	@echo "Done packing library."  

# Regle implicite qui modifie le repertoire de destination des fichiers .o
%.o: %.cc
	$(CXX) $(CXXFLAGS) -c $< -o $(BINDIR)/$(LOCALDIR)/$@