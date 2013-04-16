# Makefile for lg library
# GCC in MinGW32

.SUFFIXES:
.SUFFIXES: .o .cpp

srcdir = .

SH = sh

CC = g++
AR = ar
DLLWRAP = dllwrap

# _DARKGAME is not used here. The implementation of lgLib is universal
DEFINES = -DWINVER=0x0400 -D_WIN32_WINNT=0x0400 -DWIN32_LEAN_AND_MEAN

ARFLAGS = rc
LDFLAGS = -mwindows -L.
LIBS = -luuid
INCLUDEDIRS = -I. -I$(srcdir)
# If you care for this... # -Wno-unused-variable
# A lot of the callbacks have unused parameters, so I turn that off.
CXXFLAGS =  -W -Wall -Wno-unused-parameter -masm=intel $(INCLUDEDIRS)
LDFLAGS = -mwindows -L. -llg
DLLFLAGS = --def script.def --add-underscore --target i386-mingw32

ifdef DEBUG
CXXDEBUG = -g -DDEBUG
LDDEBUG = -g
else
CXXDEBUG = -O2 -DNDEBUG
LDDEBUG =
endif

LG_HEADERS = lg/actreact.h \
	lg/ai.h \
	lg/config.h \
	lg/convict.h \
	lg/data.h \
	lg/defs.h \
	lg/dlgs.h \
	lg/dynarray.h \
	lg/dynarray.hpp \
	lg/editor.h \
	lg/gen.h \
	lg/graphics.h \
	lg/iiddef.h \
	lg/iids.h \
	lg/input.h \
	lg/interface.h \
	lg/interfaceimp.h \
	lg/lg.h \
	lg/links.h \
	lg/loop.h \
	lg/malloc.h \
	lg/miss16.h \
	lg/net.h \
	lg/objects.h \
	lg/objstd.h \
	lg/propdefs.h \
	lg/properties.h \
	lg/quest.h \
	lg/res.h \
	lg/script.h \
	lg/scrmanagers.h \
	lg/scrmsgs.h \
	lg/scrservices.h \
	lg/shock.h \
	lg/sound.h \
	lg/tools.h \
	lg/types.h \
	lg/win.h

LG_SRCS = lg.cpp scrmsgs.cpp refcnt.cpp iids.cpp
IID_SRCS = \
	iids/acousticsproperty.cpp iids/actreacteditors.cpp iids/actreactloop.cpp \
	iids/actreactscriptservice.cpp iids/advpicksoundcfgproperty.cpp \
	iids/advpickstatecfgproperty.cpp iids/advpicktranscfgproperty.cpp \
	iids/aggregate.cpp iids/aggregatemembercontrol.cpp iids/ai.cpp iids/aiability.cpp \
	iids/aiaction.cpp iids/aiactor.cpp iids/aialertcapproperty.cpp \
	iids/aialertnessproperty.cpp iids/aialertresponseproperty.cpp \
	iids/aialertsensemultsproperty.cpp iids/aiappservices.cpp \
	iids/aiawarecapproperty.cpp iids/aiawaredelayproperty.cpp iids/aibehaviorset.cpp \
	iids/aibodyresponseproperty.cpp iids/aibroadcastproperty.cpp \
	iids/aicameraproperty.cpp iids/aicombattimingproperty.cpp iids/aicomponent.cpp \
	iids/aiconversation.cpp iids/aiconversationmanager.cpp \
	iids/aiconversationproperty.cpp iids/aiconverse.cpp iids/aideviceproperty.cpp \
	iids/aiefficiencyproperty.cpp iids/aifleeconditionsproperty.cpp \
	iids/aifrozenproperty.cpp iids/aifrustratedproperty.cpp \
	iids/aigrubcombatproperty.cpp iids/aigundescproperty.cpp iids/aiidledirsproperty.cpp \
	iids/aiidleoriginproperty.cpp iids/aiinform.cpp iids/aiinformresponseproperty.cpp \
	iids/aiinvestkindproperty.cpp iids/ailoop.cpp iids/aimanager.cpp iids/aimodeproperty.cpp \
	iids/aimoveenactor.cpp iids/aimoveregulator.cpp iids/ainetmanager.cpp \
	iids/ainetservices.cpp iids/ainoncombatdmgrespproperty.cpp \
	iids/ainonhostilityproperty.cpp iids/aiobjectavoidproperty.cpp iids/aipath.cpp \
	iids/aipathfindcontrol.cpp iids/aipathfinder.cpp iids/aipathquery.cpp iids/aiproperty.cpp \
	iids/airangedapplicabilitiesproperty.cpp iids/airangedfleeproperty.cpp \
	iids/airangedrangesproperty.cpp iids/airangedshootproperty.cpp \
	iids/airangedwoundproperty.cpp iids/airangedwoundsoundproperty.cpp \
	iids/airatingproperty.cpp iids/aireservedproperty.cpp iids/aiscriptservice.cpp \
	iids/aisensecombatresponseproperty.cpp iids/aisenses.cpp \
	iids/aisignalresponseproperty.cpp iids/aisoundenactor.cpp \
	iids/aisoundtypeproperty.cpp iids/aisubability.cpp iids/aisuspiciousresponseproperty.cpp \
	iids/aiswarmproperty.cpp iids/aithreatresponseproperty.cpp iids/aiturretproperty.cpp \
	iids/aivisctrlproperty.cpp iids/aivisibilitymodproperty.cpp \
	iids/aivisibilityproperty.cpp iids/aivisiondescproperty.cpp \
	iids/aiwanderproperty.cpp iids/aiwatchpointproperty.cpp iids/allclientsloop.cpp \
	iids/altlinkproperty.cpp iids/ambientproperty.cpp iids/ambientsoundproperty.cpp \
	iids/anglelimitproperty.cpp iids/animlightproperty.cpp iids/animtexproperty.cpp \
	iids/animtextureloop.cpp iids/animtexturescriptservice.cpp iids/appadvisesink.cpp \
	iids/application.cpp iids/armorproperty.cpp iids/asyncreadcontrol.cpp \
	iids/asyncreadfulfiller.cpp iids/asyncreadqueue.cpp iids/asyncstreamer.cpp \
	iids/automapclientloop.cpp iids/automapproperty.cpp iids/avatar.cpp \
	iids/basegundescproperty.cpp iids/baseloop.cpp iids/basemodeloop.cpp \
	iids/bashparamsproperty.cpp iids/beltlinkproperty.cpp iids/bipedlengthsproperty.cpp \
	iids/bipedloop.cpp iids/bipedmodelproperty.cpp iids/bipedproperty.cpp \
	iids/bitmapworldspaceproperty.cpp iids/boolproperty.cpp iids/bowscriptservice.cpp \
	iids/breathproperty.cpp iids/brushlistloop.cpp iids/brushproperty.cpp iids/cache.cpp \
	iids/cameraobjects.cpp iids/cameraobjproperty.cpp iids/camerascriptservice.cpp \
	iids/campaign.cpp iids/cannisterproperty.cpp iids/cdplayer.cpp iids/cheminfoproperty.cpp \
	iids/colorproperty.cpp iids/containdimsproperty.cpp iids/containerscriptservice.cpp \
	iids/containsys.cpp iids/coronaproperty.cpp iids/coverptproperty.cpp \
	iids/creatureposeproperty.cpp iids/creatureproperty.cpp iids/creatureweaponloop.cpp \
	iids/damagemodel.cpp iids/damagescriptservice.cpp iids/darkbaseclientsloop.cpp \
	iids/darkgameclientsloop.cpp iids/darkgamescriptservice.cpp \
	iids/darkoverlayscriptservice.cpp iids/darkpanelloop.cpp \
	iids/darkrenderloop.cpp iids/darksimloop.cpp iids/darkuiscriptservice.cpp \
	iids/dataops.cpp iids/dataopsfile.cpp iids/dataopsmemfile.cpp iids/datascriptservice.cpp \
	iids/datasource.cpp iids/debugmalloc.cpp iids/debugmodeloop.cpp \
	iids/debugscriptservice.cpp iids/devicebitmap.cpp iids/devicecomposebitmap.cpp \
	iids/dialogloop.cpp iids/dialogmodeloop.cpp iids/displaydevice.cpp iids/donorcache.cpp \
	iids/donorquery.cpp iids/doorscriptservice.cpp iids/drkinvscriptservice.cpp \
	iids/drkpowerupsscriptservice.cpp iids/dyntexture.cpp iids/ecologyinfoproperty.cpp \
	iids/editgeomloop.cpp iids/editmodeloop.cpp iids/editorapp.cpp iids/editorloop.cpp \
	iids/edittools.cpp iids/edittrait.cpp iids/enginefeaturesclientsloop.cpp \
	iids/enginefeaturesloop.cpp iids/enginefeaturesrendloop.cpp \
	iids/enginescriptservice.cpp iids/esndtagproperty.cpp \
	iids/expproperty.cpp iids/extralightproperty.cpp iids/faceproperty.cpp \
	iids/facestateproperty.cpp iids/filevarloop.cpp iids/floatproperty.cpp \
	iids/flowgroupproperty.cpp iids/frameanimationconfigproperty.cpp \
	iids/frameanimationstateproperty.cpp iids/frobinfoproperty.cpp \
	iids/froboldproperty.cpp iids/gameapp.cpp iids/gameloop.cpp iids/gamemodeloop.cpp \
	iids/gameshell.cpp iids/gameshelladvisesink.cpp iids/gamestrings.cpp iids/gametools.cpp \
	iids/ghostloop.cpp iids/globalidproperty.cpp iids/gr2dapp.cpp iids/gr3dapp.cpp \
	iids/gunanimproperty.cpp iids/gunkickproperty.cpp iids/gunreliabilityproperty.cpp \
	iids/gunstateproperty.cpp iids/heartbeatlistproperty.cpp iids/heatdiskproperty.cpp \
	iids/homingproperty.cpp iids/hostobjidproperty.cpp iids/inputbinder.cpp \
	iids/inputdevice.cpp iids/inputdevices.cpp iids/inputmanager.cpp iids/interfaceset.cpp \
	iids/internalai.cpp iids/intproperty.cpp iids/invdimsproperty.cpp iids/inventory.cpp \
	iids/invrenderproperty.cpp iids/invstringproperty.cpp iids/jointposproperty.cpp \
	iids/joystick.cpp iids/keyinfoproperty.cpp iids/keyscriptservice.cpp iids/keysys.cpp \
	iids/labelproperty.cpp iids/lgdd4surface.cpp iids/lgsurface.cpp iids/lightproperty.cpp \
	iids/lightscriptservice.cpp iids/linkdatastore.cpp iids/linkmanager.cpp \
	iids/linkmanagerinternal.cpp iids/linkmanloop.cpp iids/linkquery.cpp \
	iids/linkquerydatabase.cpp iids/linkscriptservice.cpp iids/linkstore.cpp \
	iids/linktoolsscriptservice.cpp iids/lockedscriptservice.cpp \
	iids/logdataproperty.cpp iids/loop.cpp iids/loopapp.cpp iids/loopclient.cpp \
	iids/loopclientfactory.cpp iids/loopdispatch.cpp iids/loopmanager.cpp iids/loopmode.cpp \
	iids/loopwatcher.cpp iids/lootinfoproperty.cpp iids/lootproperty.cpp \
	iids/maprefproperty.cpp iids/meshattachproperty.cpp iids/meshtexproperty.cpp \
	iids/messagedispatch.cpp iids/metagameclientsloop.cpp iids/metagameloop.cpp \
	iids/midisequence.cpp iids/midisequencer.cpp iids/missionloop.cpp \
	iids/motactortaglistproperty.cpp iids/motgaitdescproperty.cpp \
	iids/motphyslimitsproperty.cpp iids/motplayerlimboffsetsproperty.cpp \
	iids/movieclientloop.cpp iids/movieplayer1.cpp iids/movingterrainproperty.cpp \
	iids/net.cpp iids/netappservices.cpp iids/netmanager.cpp iids/netplayerproperty.cpp \
	iids/netstats.cpp iids/networkingscriptservice.cpp iids/networkloop.cpp \
	iids/networkresetloop.cpp iids/networksimloop.cpp iids/nullscriptservice.cpp \
	iids/objectnetworking.cpp iids/objectquery.cpp iids/objectscriptservice.cpp \
	iids/objectsystem.cpp iids/objeditor.cpp iids/objeditors.cpp iids/objiconproperty.cpp \
	iids/objidmanager.cpp iids/objidsink.cpp iids/objnameproperty.cpp iids/objnetloop.cpp \
	iids/objsoundnameproperty.cpp iids/objsysloop.cpp iids/panelloop.cpp iids/panelmode.cpp \
	iids/particlegroupproperty.cpp iids/periodicpropagator.cpp \
	iids/pgrouplaunchinfoproperty.cpp iids/pgroupscriptservice.cpp \
	iids/physattrproperty.cpp iids/physcontrolproperty.cpp iids/physdimsproperty.cpp \
	iids/physexplodeproperty.cpp iids/physicsbaseloop.cpp iids/physicsloop.cpp \
	iids/physicsscriptservice.cpp iids/physpplateproperty.cpp iids/physropeproperty.cpp \
	iids/physstateproperty.cpp iids/phystypeproperty.cpp iids/pickcfgproperty.cpp \
	iids/picklockscriptservice.cpp iids/pickstateproperty.cpp iids/playergun.cpp \
	iids/playergundescproperty.cpp iids/playerlimbsscriptservice.cpp iids/playerloop.cpp \
	iids/playerpsi.cpp iids/portalapp.cpp iids/positionproperty.cpp \
	iids/primaryinputdevicessink.cpp iids/projectileproperty.cpp iids/propagation.cpp \
	iids/propagator.cpp iids/propagatorquery.cpp iids/property.cpp iids/propertymanager.cpp \
	iids/propertynetworking.cpp iids/propertyscriptservice.cpp iids/propertystats.cpp \
	iids/propertystore.cpp iids/psiactiveiter.cpp iids/psipowerproperty.cpp \
	iids/psishieldproperty.cpp iids/psistateproperty.cpp iids/puppetproperty.cpp \
	iids/puppetscriptservice.cpp iids/questdata.cpp iids/questdataiter.cpp iids/questloop.cpp \
	iids/questscriptservice.cpp iids/questvarproperty.cpp iids/rangedcombatproperty.cpp \
	iids/reactionquery.cpp iids/reactions.cpp iids/receptronquery.cpp iids/recorder.cpp \
	iids/relation.cpp iids/renderbaseloop.cpp iids/renderloop.cpp iids/rendflashproperty.cpp \
	iids/repcontentsproperty.cpp iids/res.cpp iids/resapp.cpp iids/rescontrol.cpp iids/reshack.cpp \
	iids/resloop.cpp iids/resman.cpp iids/resmanhelper.cpp iids/resmem.cpp iids/resmemoverride.cpp \
	iids/resstats.cpp iids/restype.cpp iids/roomgravityproperty.cpp iids/roomloop.cpp \
	iids/roomscriptproperty.cpp iids/rotdoorproperty.cpp iids/scaleproperty.cpp \
	iids/schemaloop.cpp iids/schemaloopparamsproperty.cpp \
	iids/schemaplayparamsproperty.cpp iids/schematagconstraintproperty.cpp \
	iids/script.cpp iids/scriptman.cpp iids/scriptmodule.cpp iids/scriptnet.cpp \
	iids/scriptproperty.cpp iids/scrnmanloop.cpp iids/searchpath.cpp iids/sharedcache.cpp \
	iids/shockaiscriptservice.cpp iids/shockbaseclientsloop.cpp iids/shockcamera.cpp \
	iids/shockgameclientsloop.cpp iids/shockgamescriptservice.cpp \
	iids/shockloadingloop.cpp iids/shockmasterloop.cpp iids/shockobjscriptservice.cpp \
	iids/shockoverlayscriptservice.cpp iids/shockplayer.cpp \
	iids/shockpsiscriptservice.cpp iids/shockrangedproperty.cpp \
	iids/shockrender2loop.cpp iids/shockrenderloop.cpp iids/shocksimloop.cpp \
	iids/shockweaponscriptservice.cpp iids/simfinishloop.cpp iids/simmanager.cpp \
	iids/simtimeloop.cpp iids/sndapp.cpp iids/sndmixer.cpp iids/sndsample.cpp iids/sndsource.cpp \
	iids/song.cpp iids/songevent.cpp iids/songgoto.cpp iids/songplayer.cpp  iids/songsample.cpp \
	iids/songsection.cpp iids/soundloop.cpp iids/soundscriptservice.cpp \
	iids/sparkproperty.cpp iids/spawninfoproperty.cpp iids/speechproperty.cpp \
	iids/statsdescproperty.cpp iids/stimsensorquery.cpp iids/stimsensors.cpp \
	iids/stimsourcequery.cpp iids/stimsources.cpp iids/stimulator.cpp iids/stimuli.cpp \
	iids/store.cpp iids/storefactory.cpp iids/storehierarchy.cpp iids/storemanager.cpp \
	iids/storestream.cpp iids/stringproperty.cpp iids/stringres.cpp iids/structdesctools.cpp \
	iids/structeditor.cpp iids/suspiciousproperty.cpp iids/tagfile.cpp iids/tagfileiter.cpp \
	iids/techinfoproperty.cpp iids/techskillsproperty.cpp iids/testloop.cpp \
	iids/threadmanager.cpp iids/trait.cpp iids/traitmanager.cpp iids/traitsdescproperty.cpp \
	iids/transdoorproperty.cpp iids/tweqemitterproperty.cpp iids/tweqjointsproperty.cpp \
	iids/tweqjointsstateproperty.cpp iids/tweqlockproperty.cpp \
	iids/tweqlockstateproperty.cpp iids/tweqmodelsproperty.cpp \
	iids/tweqsimpleproperty.cpp iids/tweqsimplestateproperty.cpp \
	iids/tweqvectorproperty.cpp iids/tweqvectorstateproperty.cpp iids/uiapp.cpp \
	iids/uiloop.cpp iids/vantageptproperty.cpp iids/vectorproperty.cpp \
	iids/versionscriptservice.cpp iids/voiceoversys.cpp \
	iids/watercolorproperty.cpp iids/weaponoffsetproperty.cpp \
	iids/weaponscriptservice.cpp iids/weaponskillsproperty.cpp iids/weatherproperty.cpp \
	iids/winapp.cpp iids/winappadvisesink.cpp iids/windisplaydevice.cpp iids/winshell.cpp \
	iids/wrloop.cpp
IID_OBJS = $(IID_SRCS:%.cpp=%.o)

LG_LIB = liblg.a
LG_OBJS = lg.o scrmsgs.o refcnt.o iids.o

LG_LIBD = liblg-d.a
LG_OBJSD = lg-d.o scrmsgs-d.o refcnt-d.o iids.o

%.o: %.cpp
	$(CC) $(CXXFLAGS) $(CXXDEBUG) $(DEFINES) -o $@ -c $<

%-d.o: %.cpp
	$(CC) $(CXXFLAGS) $(CXXDEBUG) $(DEFINES) -o $@ -c $<


ALL:	$(LG_LIB) $(LG_LIBD)

clean:
	$(RM) $(LG_OBJS) $(LG_OBJSD) $(IID_OBJS) $(LG_LIB) $(LG_LIBD)

stamp: $(LG_SRCS) $(LG_HEADERS)
	$(RM) lg/stamp-*
	$(SH) timestamp.sh lg lg $(LG_SRCS)

$(LG_LIB): $(LG_OBJS) $(IID_OBJS)
	$(AR) $(ARFLAGS) $@ $?

$(LG_LIBD): CXXDEBUG = -g -DDEBUG
$(LG_LIBD): LDDEBUG = -g
$(LG_LIBD): $(LG_OBJSD) $(IID_OBJS)
	$(AR) $(ARFLAGS) $@ $?

lg.o: lg.cpp $(LG_HEADERS)
scrmsgs.o: scrmsgs.cpp lg/scrmsgs.h lg/defs.h lg/types.h lg/interfaceimp.h lg/interface.h lg/iiddef.h lg/objstd.h lg/config.h
refcnt.o: refcnt.cpp lg/interfaceimp.h lg/iiddef.h lg/objstd.h lg/config.h
lg-d.o: lg.cpp $(LG_HEADERS)
scrmsgs-d.o: scrmsgs.cpp lg/scrmsgs.h lg/defs.h lg/types.h lg/interfaceimp.h lg/interface.h lg/iiddef.h lg/objstd.h lg/config.h
refcnt-d.o: refcnt.cpp lg/interfaceimp.h lg/iiddef.h lg/objstd.h lg/config.h
