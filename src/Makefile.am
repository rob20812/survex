## Process this file with automake to produce Makefile.in

noinst_HEADERS = cavern.h commands.h cmdline.h date.h datain.h debug.h\
 filelist.h filename.h getopt.h hash.h img.c img.h img_hosted.h ini.h\
 listpos.h matrix.h message.h namecmp.h namecompare.h netartic.h netbits.h\
 netskel.h network.h osalloc.h\
 osdepend.h ostypes.h out.h readval.h str.h useful.h validate.h whichos.h\
 glbitmapfont.h guicontrol.h gla.h gpx.h moviemaker.h exportfilter.h hpgl.h\
 cavernlog.h aboutdlg.h aven.h avenpal.h gfxcore.h log.h mainfrm.h\
 vector3.h wx.h aventypes.h aventreectrl.h export.h printwx.h avenprcore.h\
 img2aven.h

LDADD = $(LIBOBJS)

# dump3d is a test program
#
# findentrances needs libproj so is disabled by default for the moment -
# to enable it install the development stuff for libproj and build survex
# with:
#     make FINDENTRANCES=findentrances
#     make install FINDENTRANCES=findentrances
FINDENTRANCES =
EXTRA_PROGRAMS =\
	aven dump3d editwrap findentrances
# FIXME: base_progs in top level Makefile.am needs updating if this is
bin_PROGRAMS = cad3d cavern diffpos extend sorterr 3dtopos dump3d \
 aven $(WINPROGS) $(FINDENTRANCES)
bin_SCRIPTS = svxedit

COMMONSRC = cmdline.c message.c filename.c osdepend.c z_getopt.c getopt1.c

cavern_SOURCES = cavern.c date.c listpos.c commands.c datain.c netskel.c \
 network.c readval.c str.c matrix.c img_hosted.c netbits.c useful.c \
 validate.c netartic.c \
 $(COMMONSRC)

aven_SOURCES = aven.cc date.c img_hosted.c message.c filename.c osdepend.c \
 gfxcore.cc mainfrm.cc vector3.cc aboutdlg.cc useful.c cmdline.c z_getopt.c \
 getopt1.c namecompare.cc aventreectrl.cc export.cc guicontrol.cc gla-gl.cc \
 glbitmapfont.cc gpx.cc log.cc moviemaker.cc hpgl.cc cavernlog.cc \
 brotatemask.xbm brotate.xbm handmask.xbm hand.xbm \
 rotatemask.xbm rotate.xbm vrotatemask.xbm vrotate.xbm \
 rotatezoom.xbm rotatezoommask.xbm \
 avenprcore.cc printwx.cc ini.c hash.c \
 buttontaghandler.cc

dump3d_SOURCES = dump3d.c date.c img_hosted.c useful.c \
 $(COMMONSRC)

findentrances_SOURCES = findentrances.cc img_hosted.c useful.c \
 $(COMMONSRC)
findentrances_LDADD = -lproj

editwrap_SOURCES = editwrap.c
editwrap_LDFLAGS = -mwindows

if WIN32
aven_LDADD = avenrc.o $(LIBOBJS) $(AVEN_LIBS) $(WX_LIBS)

svxeditrc.o: $(srcdir)/svxedit.rc svxedit.ico
	pwd=`pwd` && cd $(srcdir) && `$(WX_CONFIG) --rescomp` -o "$$pwd/svxeditrc.o" svxedit.rc

svxedit.ico: ../lib/icons/svxedit.ico
	cp ../lib/icons/svxedit.ico .

editwrap_LDADD = svxeditrc.o

avenrc.o: $(srcdir)/aven.rc aven.ico
	pwd=`pwd` && cd $(srcdir) && `$(WX_CONFIG) --rescomp` -o "$$pwd/avenrc.o" aven.rc

aven.ico: ../lib/icons/aven.ico
	cp ../lib/icons/aven.ico .

CLEANFILES = aven.ico svxedit.ico
else
aven_LDADD = $(LIBOBJS) $(AVEN_LIBS) $(WX_LIBS)
endif

if MACOSX
# Aven must always be built into an application bundle to work correctly.
aven_CFLAGS = $(WX_CFLAGS) $(AM_CFLAGS) -DAVEN -DMACOSX_BUNDLE
aven_CXXFLAGS = $(WX_CXXFLAGS) $(AM_CXXFLAGS) -DMACOSX_BUNDLE
aven_LDFLAGS = $(WX_LDFLAGS) -lproj -framework OpenGL
else
aven_CFLAGS = $(WX_CFLAGS) $(AM_CFLAGS) -DAVEN
aven_CXXFLAGS = $(WX_CXXFLAGS) $(AM_CXXFLAGS)
aven_LDFLAGS = $(WX_LDFLAGS) -lproj
endif

diffpos_SOURCES = diffpos.c namecmp.c img_hosted.c useful.c hash.c \
 $(COMMONSRC)
sorterr_SOURCES = sorterr.c $(COMMONSRC)
3dtopos_SOURCES = 3dtopos.c namecmp.c img_hosted.c useful.c \
 $(COMMONSRC)
extend_SOURCES = extend.c img_hosted.c useful.c hash.c \
 $(COMMONSRC)

cad3d_SOURCES = cad3d.c useful.c img_hosted.c hash.c \
 $(COMMONSRC)

#testerr_SOURCES = testerr.c message.c filename.c useful.c osdepend.c
#imgtest_SOURCES = imgtest.c img.c

all_sources = \
	$(noinst_HEADERS) \
	$(COMMONSRC) \
	$(cavern_SOURCES) \
	$(aven_SOURCES) \
	$(dump3d_SOURCES) \
	$(editwrap_SOURCES) \
	$(diffpos_SOURCES) \
	$(sorterr_SOURCES) \
	$(3dtopos_SOURCES) \
	$(extend_SOURCES) \
	$(cad3d_SOURCES) \
	$(findentrances_SOURCES)

../lib/survex.pox: $(all_sources) ../lib/extract-msgs.pl
	cd $(srcdir)/../lib && ./extract-msgs.pl `echo $(all_sources)|perl -ne 'print "../src/$$_\n" for sort split'|uniq` > survex.pox

EXTRA_DIST = \
 aven.rc svxedit.rc getopt.c gettexttomsg.pl gradient.pov gdtconvert gen_img2aven

BUILT_SOURCES = z_getopt.c avenpal.h img2aven.h

z_getopt.c: getopt.c gettexttomsg.pl
	./gettexttomsg.pl `test -f getopt.c || echo '$(srcdir)/'`getopt.c > z_getopt.c~ && mv z_getopt.c~ z_getopt.c

avenpal.h: $(srcdir)/gdtconvert $(srcdir)/gradient.pov
	$(srcdir)/gdtconvert < $(srcdir)/gradient.pov > tmp-avenpal.h && mv tmp-avenpal.h avenpal.h

img2aven.h: $(srcdir)/gen_img2aven
	$(srcdir)/gen_img2aven > tmp-img2aven.h && mv tmp-img2aven.h img2aven.h

MAINTAINERCLEANFILES =\
 $(BUILT_SOURCES)
