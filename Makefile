ADD_CFLAGS := $(shell pkg-config --cflags sfml-audio sfml-graphics sfml-system sfml-window fontconfig)
ADD_LDFLAGS := $(shell pkg-config --libs sfml-audio sfml-graphics sfml-system sfml-window fontconfig)

CXX = g++
CC = gcc
CXXFLAGS = -g $(ADD_CFLAGS)
LIBS = $(ADD_LDFLAGS)

OSTRICHRIDERS_OBJ = src/sfmlGame/Entity/MenuEntity.o src/sfmlGame/Entity/TextEntity.o src/sfmlGame/Entity/SurfaceEntity.o src/sfmlGame/Entity/SpriteEntity.o src/sfmlGame/Entity/ScoresEntity.o src/sfmlGame/Entity/TextInputEntity.o src/sfmlGame/Entity/GuiEntity.o src/sfmlGame/Entity/GameEntity.o src/sfmlGame/Entity/EntityManager.o src/sfmlGame/Entity/CollidingSpriteEntity.o src/main.o src/sfmlGame/Model/MenuEntry.o src/sfmlGame/Model/Menu.o src/sfmlGame/Model/GameScores.o src/sfmlGame/Model/GameMap.o src/sfmlGame/MediaManagers/SoundManager.o src/sfmlGame/MediaManagers/ImageManager.o src/sfmlGame/Game.o src/sfmlGame/Entity/TileMapEntity.o src/joust/JoustGameMap.o src/joust/JoustGame.o src/joust/GateEntity.o src/joust/GameConstants.o src/joust/FlyingScoreEntity.o src/joust/FallingRiderEntity.o src/joust/EggEntity.o src/joust/BurningJousterEntity.o src/joust/BotEntity.o src/joust/SelectorEntity.o src/joust/RotatingTextEntity.o src/joust/PlayerInput.o src/joust/PlayerEntity.o src/joust/MountEntity.o src/defaultfont.o src/joust/LogicEngine.o src/joust/LifeEntity.o src/joust/JousterEntity.o src/joust/JoustTileMapEntity.o
OSTRICHRIDERS_EXE = OstrichRiders

ifndef prefix
	prefix=
endif
BINDIR=${prefix}/usr/bin
DATADIR=${prefix}/usr/share

all: $(OSTRICHRIDERS_EXE)

$(OSTRICHRIDERS_EXE): $(OSTRICHRIDERS_OBJ)
	$(CXX) -o $(OSTRICHRIDERS_EXE) $(OSTRICHRIDERS_OBJ) $(LIBS)

%.o: %.C
	$(CXX) $(CXXFLAGS) -c -o $@ $<

install: all
	if test ! -d $(BINDIR); then mkdir -p $(BINDIR); fi
	if test ! -d $(DATADIR)/ostrichriders; then mkdir -p $(DATADIR)/ostrichriders; fi
	if test ! -d $(DATADIR)/appdata; then mkdir -p $(DATADIR)/appdata; fi
	if test ! -d $(DATADIR)/icons/hicolor; then mkdir -p $(DATADIR)/icons/hicolor; fi
	cp -R data/* $(DATADIR)/ostrichriders/
	cp -R ostrichriders.appdata.xml $(DATADIR)/appdata/
	cp -R icons/* $(DATADIR)/icons/hicolor/
	cp OstrichRiders $(BINDIR)
	desktop-file-install --dir=$(DATADIR)/applications ostrichriders.desktop

clean:
	rm -f $(OSTRICHRIDERS_OBJ) $(OSTRICHRIDERS_EXE)
