ADD_CFLAGS := $(shell pkg-config --cflags sfml-audio sfml-graphics sfml-system sfml-window fontconfig)
ADD_LDFLAGS := $(shell pkg-config --libs sfml-audio sfml-graphics sfml-system sfml-window fontconfig)

CXX = g++
CC = gcc
CXXFLAGS ?= -g 
CXXFLAGS += $(ADD_CFLAGS)
LIBS = $(LDFLAGS) $(ADD_LDFLAGS)

OSTRICHRIDERS_OBJ = src/sfmlGame/Entity/MenuEntity.o src/sfmlGame/Entity/TextEntity.o src/sfmlGame/Entity/SurfaceEntity.o src/sfmlGame/Entity/SpriteEntity.o src/sfmlGame/Entity/ScoresEntity.o src/sfmlGame/Entity/TextInputEntity.o src/sfmlGame/Entity/GuiEntity.o src/sfmlGame/Entity/GameEntity.o src/sfmlGame/Entity/EntityManager.o src/sfmlGame/Entity/CollidingSpriteEntity.o src/main.o src/sfmlGame/Model/MenuEntry.o src/sfmlGame/Model/Menu.o src/sfmlGame/Model/GameScores.o src/sfmlGame/Model/GameMap.o src/sfmlGame/MediaManagers/SoundManager.o src/sfmlGame/MediaManagers/ImageManager.o src/sfmlGame/Game.o src/sfmlGame/Entity/TileMapEntity.o src/joust/JoustGameMap.o src/joust/JoustGame.o src/joust/GateEntity.o src/joust/GameConstants.o src/joust/FlyingScoreEntity.o src/joust/FallingRiderEntity.o src/joust/EggEntity.o src/joust/BurningJousterEntity.o src/joust/BotEntity.o src/joust/SelectorEntity.o src/joust/RotatingTextEntity.o src/joust/PlayerInput.o src/joust/PlayerEntity.o src/joust/MountEntity.o src/defaultfont.o src/joust/LogicEngine.o src/joust/LifeEntity.o src/joust/JousterEntity.o src/joust/JoustTileMapEntity.o
OSTRICHRIDERS_EXE = ostrichriders

DESTDIR ?=
PREFIX ?= /usr/local
BINDIR ?= $(PREFIX)/bin
DATADIR ?= $(PREFIX)/share
DESTBINDIR = $(DESTDIR)$(BINDIR)
DESTDATADIR = $(DESTDIR)$(DATADIR)

ifdef GAMEDATADIR
	CXXFLAGS += -DGAMEDATADIR=\"$(GAMEDATADIR)/\"
else
	GAMEDATADIR = $(DATADIR)/ostrichriders
endif
DESTGAMEDATADIR = $(DESTDIR)$(GAMEDATADIR)

all: $(OSTRICHRIDERS_EXE)

$(OSTRICHRIDERS_EXE): $(OSTRICHRIDERS_OBJ)
	$(CXX) -o $(OSTRICHRIDERS_EXE) $(OSTRICHRIDERS_OBJ) $(LIBS)

%.o: %.C
	$(CXX) $(CXXFLAGS) -c -o $@ $<

install: all
	if test ! -d $(DESTBINDIR); then mkdir -p $(DESTBINDIR); fi
	if test ! -d $(DESTGAMEDATADIR); then mkdir -p $(DESTGAMEDATADIR); fi
	if test ! -d $(DESTDATADIR)/appdata; then mkdir -p $(DESTDATADIR)/appdata; fi
	if test ! -d $(DESTDATADIR)/icons/hicolor; then mkdir -p $(DESTDATADIR)/icons/hicolor; fi
	cp -R data/* $(DESTGAMEDATADIR)/
	cp -R ostrichriders.appdata.xml $(DESTDATADIR)/appdata/
	cp -R icons/* $(DESTDATADIR)/icons/hicolor/
	cp $(OSTRICHRIDERS_EXE) $(DESTBINDIR)
	desktop-file-install --dir=$(DESTDATADIR)/applications ostrichriders.desktop

clean:
	rm -f $(OSTRICHRIDERS_OBJ) $(OSTRICHRIDERS_EXE)
