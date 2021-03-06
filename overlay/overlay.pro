include (../compiler.pri)

VERSION = 1.3.0
TARGET_EXT = .dll
TEMPLATE = lib
CONFIG -= qt
CONFIG *= dll shared debug_and_release warn_on
CONFIG -= embed_manifest_dll
TARGET = mumble_ol
RC_FILE = mumble_ol.rc
SOURCES = lib.cpp d3d9.cpp dxgi.cpp d3d10.cpp d3d11.cpp ods.cpp opengl.cpp HardHook.cpp D11StateBlock.cpp
HEADERS = lib.h ods.h HardHook.h overlay_blacklist.h D11StateBlock.h ../3rdparty/GL/glext.h
EFFECTS = overlay.fx
DIST = overlay.h overlay.fx HardHook.h
FX11DIR = "../3rdparty/fx11-src"
FX11DIR_BUILD = $$replace(FX11DIR,-src,-build)

DEFINES -= UNICODE

QMAKE_CXXFLAGS_RELEASE	-= -MD
QMAKE_CXXFLAGS_DEBUG	-= -MDd

QMAKE_CXXFLAGS_RELEASE	*= -MT
QMAKE_CXXFLAGS_DEBUG	*= -MTd

INCLUDEPATH *= "$$FX11DIR/inc"

LIBS *= -ldxguid -luuid -lole32 -luser32 -ladvapi32
LIBS *= -ld3d9 -ld3d10 -ld3d11 -ld3dcompiler -ld3dx9 -ld3dx10 -ld3dx11 -ldxgi

equals(QMAKE_TARGET.arch, x86_64) {
  DEFINES += USE_MINHOOK
  INCLUDEPATH *= ../3rdparty/minhook-src/include
  LIBS *= -lminhook
}

CONFIG(release, debug|release) {
  DESTDIR = ../release
  QMAKE_LIBDIR += ../release
  LIBS *= -l$$FX11DIR_BUILD/release/effects11
}

CONFIG(debug, debug|release) {
  DESTDIR = ../debug
  QMAKE_LIBDIR += ../debug
  DEFINES *= DEBUG
  LIBS *= -l$$FX11DIR_BUILD/debug/effects11
}

fxc.output = ${QMAKE_FILE_BASE}.hex
fxc.commands = fxc /Tfx_4_0 /O3 /Fh${QMAKE_FILE_OUT} ${QMAKE_FILE_NAME}
fxc.input = EFFECTS
fxc.CONFIG *= no_link target_predeps
QMAKE_EXTRA_COMPILERS *= fxc

fxc11.output = ${QMAKE_FILE_BASE}11.hex
fxc11.commands = fxc /Tfx_5_0 /O3 /Fh${QMAKE_FILE_OUT} ${QMAKE_FILE_NAME}
fxc11.input = EFFECTS
fxc11.CONFIG *= no_link target_predeps
QMAKE_EXTRA_COMPILERS *= fxc11
