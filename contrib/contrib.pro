QT -= qt

TARGET = seedcontrib
TEMPLATE = lib

CONFIG(debug, debug|release) {
	DESTDIR = ../lib/debug
	DEFINES += DEBUG
} else {
	DESTDIR = ../lib/release
	DEFINES += RELEASE
}

CONFIG += staticlib

SOURCES += yajl/yajl_buf.c \
	yajl/yajl_alloc.c \
	yajl/yajl.c \
	yajl/yajl_version.c \
	yajl/yajl_tree.c \
	yajl/yajl_parser.c \
	yajl/yajl_lex.c \
	yajl/yajl_gen.c \
	yajl/yajl_encode.c \
	vorbis/window.c \
	vorbis/vorbisfile.c \
	vorbis/vorbisenc.c \
	vorbis/synthesis.c \
	vorbis/smallft.c \
	vorbis/sharedbook.c \
	vorbis/res0.c \
	vorbis/registry.c \
	vorbis/psy.c \
	vorbis/mdct.c \
	vorbis/mapping0.c \
	vorbis/lsp.c \
	vorbis/lpc.c \
	vorbis/lookup.c \
	vorbis/info.c \
	vorbis/floor1.c \
	vorbis/floor0.c \
	vorbis/envelope.c \
	vorbis/codebook.c \
	vorbis/block.c \
	vorbis/bitrate.c \
	vorbis/analysis.c \
	theora/tokenize.c \
	theora/thinfo.c \
	theora/state.c \
	theora/rate.c \
	theora/quant.c \
	theora/mcenc.c \
	theora/mathops.c \
	theora/internal.c \
	theora/idct.c \
	theora/huffenc.c \
	theora/huffdec.c \
	theora/fragment.c \
	theora/fdct.c \
	theora/enquant.c \
	theora/encode.c \
	theora/encinfo.c \
	theora/encfrag.c \
	theora/encapiwrapper.c \
	theora/dequant.c \
	theora/decode.c \
	theora/decinfo.c \
	theora/decapiwrapper.c \
	theora/cpu.c \
	theora/bitpack.c \
	theora/apiwrapper.c \
	theora/analyze.c \
	physfs/physfs_unicode.c \
	physfs/physfs_byteorder.c \
	physfs/physfs.c \
	physfs/zlib123/zutil.c \
	physfs/zlib123/trees.c \
	physfs/zlib123/uncompr.c \
	physfs/zlib123/inftrees.c \
	physfs/zlib123/inflate.c \
	physfs/zlib123/deflate.c \
	physfs/zlib123/inffast.c \
	physfs/zlib123/infback.c \
	physfs/zlib123/gzio.c \
	physfs/zlib123/crc32.c \
	physfs/zlib123/compress.c \
	physfs/zlib123/adler32.c \
	physfs/platform/windows.c \
	physfs/platform/unix.c \
	physfs/platform/posix.c \
	physfs/platform/pocketpc.c \
	physfs/platform/os2.c \
	physfs/platform/macosx.c \
	physfs/platform/beos.cpp \
	physfs/archivers/zip.c \
	physfs/archivers/wad.c \
	physfs/archivers/qpak.c \
	physfs/archivers/mvl.c \
	physfs/archivers/lzma.c \
	physfs/archivers/hog.c \
	physfs/archivers/grp.c \
	physfs/archivers/dir.c \
	oggz/oggz_write.c \
	oggz/oggz_vector.c \
	oggz/oggz_table.c \
	oggz/oggz_stream.c \
	oggz/oggz_seek.c \
	oggz/oggz_read.c \
	oggz/oggz_io.c \
	oggz/oggz_dlist.c \
	oggz/oggz_comments.c \
	oggz/oggz_auto.c \
	oggz/oggz.c \
	oggz/metric_internal.c \
	oggz/dirac.c \
	oggplay/oggplay_yuv2rgb.c \
	oggplay/oggplay_tools.c \
	oggplay/oggplay_tcp_reader.c \
	oggplay/oggplay_seek.c \
	oggplay/oggplay_query.c \
	oggplay/oggplay_file_reader.c \
	oggplay/oggplay_data.c \
	oggplay/oggplay_callback_info.c \
	oggplay/oggplay_callback.c \
	oggplay/oggplay_buffer.c \
	oggplay/oggplay.c \
	oggplay/cpu.c \
	ogg/framing.c \
	ogg/bitwise.c \
	glew/glew.c \
	Box2D/Collision/b2TimeOfImpact.cpp \
	Box2D/Collision/b2DynamicTree.cpp \
	Box2D/Collision/b2Distance.cpp \
	Box2D/Collision/b2Collision.cpp \
	Box2D/Collision/b2CollidePolygon.cpp \
	Box2D/Collision/b2CollideCircle.cpp \
	Box2D/Collision/b2BroadPhase.cpp \
	Box2D/Collision/Shapes/b2PolygonShape.cpp \
	Box2D/Collision/Shapes/b2CircleShape.cpp \
	Box2D/Common/b2StackAllocator.cpp \
	Box2D/Common/b2Settings.cpp \
	Box2D/Common/b2Math.cpp \
	Box2D/Common/b2BlockAllocator.cpp \
	Box2D/Dynamics/b2WorldCallbacks.cpp \
	Box2D/Dynamics/b2World.cpp \
	Box2D/Dynamics/b2Island.cpp \
	Box2D/Dynamics/b2Fixture.cpp \
	Box2D/Dynamics/b2ContactManager.cpp \
	Box2D/Dynamics/b2Body.cpp \
	Box2D/Dynamics/Contacts/b2TOISolver.cpp \
	Box2D/Dynamics/Contacts/b2ContactSolver.cpp \
	Box2D/Dynamics/Contacts/b2PolygonContact.cpp \
	Box2D/Dynamics/Contacts/b2Contact.cpp \
	Box2D/Dynamics/Contacts/b2PolygonAndCircleContact.cpp \
	Box2D/Dynamics/Contacts/b2CircleContact.cpp \
	Box2D/Dynamics/Joints/b2WeldJoint.cpp \
	Box2D/Dynamics/Joints/b2RevoluteJoint.cpp \
	Box2D/Dynamics/Joints/b2PulleyJoint.cpp \
	Box2D/Dynamics/Joints/b2PrismaticJoint.cpp \
	Box2D/Dynamics/Joints/b2MouseJoint.cpp \
	Box2D/Dynamics/Joints/b2LineJoint.cpp \
	Box2D/Dynamics/Joints/b2Joint.cpp \
	Box2D/Dynamics/Joints/b2GearJoint.cpp \
	Box2D/Dynamics/Joints/b2FrictionJoint.cpp \
	Box2D/Dynamics/Joints/b2DistanceJoint.cpp \
	vectormath/vfpmath/vsinf.cpp \
	vectormath/vfpmath/matrix_impl.cpp \
	lua/lzio.c \
	lua/lvm.c \
	lua/lundump.c \
	lua/luac.c \
	lua/lua.c \
	lua/ltm.c \
	lua/ltablib.c \
	lua/ltable.c \
	lua/lstrlib.c \
	lua/lstring.c \
	lua/lstate.c \
	lua/lparser.c \
	lua/loslib.c \
	lua/lopcodes.c \
	lua/lobject.c \
	lua/loadlib.c \
	lua/lmem.c \
	lua/lmathlib.c \
	lua/llex.c \
	lua/liolib.c \
	lua/linit.c \
	lua/lgc.c \
	lua/lfunc.c \
	lua/ldump.c \
	lua/ldo.c \
	lua/ldebug.c \
	lua/ldblib.c \
	lua/lctype.c \
	lua/lcorolib.c \
	lua/lcode.c \
	lua/lbitlib.c \
	lua/lbaselib.c \
	lua/lauxlib.c \
	lua/lapi.c

HEADERS += yajl/api/yajl_version.h \
	yajl/api/yajl_tree.h \
	yajl/api/yajl_parse.h \
	yajl/api/yajl_gen.h \
	yajl/api/yajl_common.h \
	yajl/yajl_buf.h \
	yajl/yajl_alloc.h \
	yajl/yajl_parser.h \
	yajl/yajl_lex.h \
	yajl/yajl_encode.h \
	yajl/yajl_bytestack.h \
	vorbis/bitrate.h \
	vorbis/window.h \
	vorbis/vorbisfile.h \
	vorbis/vorbisenc.h \
	vorbis/smallft.h \
	vorbis/scales.h \
	vorbis/registry.h \
	vorbis/psy.h \
	vorbis/os.h \
	vorbis/misc.h \
	vorbis/mdct.h \
	vorbis/masking.h \
	vorbis/lsp.h \
	vorbis/lpc.h \
	vorbis/lookup_data.h \
	vorbis/lookup.h \
	vorbis/highlevel.h \
	vorbis/envelope.h \
	vorbis/codec_internal.h \
	vorbis/codec.h \
	vorbis/codebook.h \
	vorbis/backends.h \
	vorbis/modes/setup_X.h \
	vorbis/modes/setup_44u.h \
	vorbis/modes/setup_44p51.h \
	vorbis/modes/setup_44.h \
	vorbis/modes/setup_32.h \
	vorbis/modes/setup_22.h \
	vorbis/modes/setup_16.h \
	vorbis/modes/setup_11.h \
	vorbis/modes/setup_8.h \
	vorbis/modes/residue_44u.h \
	vorbis/modes/residue_44p51.h \
	vorbis/modes/residue_44.h \
	vorbis/modes/residue_16.h \
	vorbis/modes/residue_8.h \
	vorbis/modes/psych_44.h \
	vorbis/modes/psych_16.h \
	vorbis/modes/psych_11.h \
	vorbis/modes/psych_8.h \
	vorbis/modes/floor_all.h \
	vorbis/books/uncoupled/res_books_uncoupled.h \
	vorbis/books/floor/floor_books.h \
	vorbis/books/coupled/res_books_stereo.h \
	vorbis/books/coupled/res_books_51.h \
	theora/theoraenc.h \
	theora/theoradec.h \
	theora/theora.h \
	theora/quant.h \
	theora/ocintrin.h \
	theora/modedec.h \
	theora/mathops.h \
	theora/internal.h \
	theora/huffman.h \
	theora/huffenc.h \
	theora/huffdec.h \
	theora/enquant.h \
	theora/encint.h \
	theora/dequant.h \
	theora/decint.h \
	theora/dct.h \
	theora/cpu.h \
	theora/codec.h \
	theora/bitpack.h \
	theora/apiwrapper.h \
	physfs/physfs_platforms.h \
	physfs/physfs_internal.h \
	physfs/physfs_casefolding.h \
	physfs/physfs.h \
	physfs/zlib123/zutil.h \
	physfs/zlib123/trees.h \
	physfs/zlib123/zlib.h \
	physfs/zlib123/zconf.h \
	physfs/zlib123/inftrees.h \
	physfs/zlib123/inflate.h \
	physfs/zlib123/inffixed.h \
	physfs/zlib123/inffast.h \
	physfs/zlib123/deflate.h \
	physfs/zlib123/crc32.h \
	oggz/oggz_write.h \
	oggz/oggz_vector.h \
	oggz/oggz_table.h \
	oggz/oggz_stream_private.h \
	oggz/oggz_stream.h \
	oggz/oggz_seek.h \
	oggz/oggz_read.h \
	oggz/oggz_private.h \
	oggz/oggz_packet.h \
	oggz/oggz_off_t_generated.h \
	oggz/oggz_off_t.h \
	oggz/oggz_macros.h \
	oggz/oggz_io.h \
	oggz/oggz_dlist.h \
	oggz/oggz_deprecated.h \
	oggz/oggz_constants.h \
	oggz/oggz_compat.h \
	oggz/oggz_comments.h \
	oggz/oggz_byteorder.h \
	oggz/oggz_auto.h \
	oggz/oggz.h \
	oggz/dirac.h \
	oggz/config.h \
	oggplay/std_semaphore.h \
	oggplay/oggplay_yuv2rgb_template.h \
	oggplay/oggplay_tools.h \
	oggplay/oggplay_tcp_reader.h \
	oggplay/oggplay_seek.h \
	oggplay/oggplay_reader.h \
	oggplay/oggplay_query.h \
	oggplay/oggplay_private.h \
	oggplay/oggplay_file_reader.h \
	oggplay/oggplay_enums.h \
	oggplay/oggplay_data.h \
	oggplay/oggplay_config_win32.h \
	oggplay/oggplay_config.h \
	oggplay/oggplay_callback_info.h \
	oggplay/oggplay_callback.h \
	oggplay/oggplay_buffer.h \
	oggplay/oggplay.h \
	oggplay/cpu.h \
	oggplay/x86/yuv2rgb_x86_vs.h \
	oggplay/x86/yuv2rgb_x86.h \
	ogg/os_types.h \
	ogg/ogg.h \
	ogg/config_types.h.in \
	glew/wglew.h \
	glew/glxew.h \
	glew/glew.h \
	Box2D/Box2D.h \
	Box2D/Collision/b2TimeOfImpact.h \
	Box2D/Collision/b2DynamicTree.h \
	Box2D/Collision/b2Distance.h \
	Box2D/Collision/b2Collision.h \
	Box2D/Collision/b2BroadPhase.h \
	Box2D/Collision/Shapes/b2Shape.h \
	Box2D/Collision/Shapes/b2PolygonShape.h \
	Box2D/Collision/Shapes/b2CircleShape.h \
	Box2D/Common/b2StackAllocator.h \
	Box2D/Common/b2Settings.h \
	Box2D/Common/b2Math.h \
	Box2D/Common/b2BlockAllocator.h \
	Box2D/Dynamics/b2WorldCallbacks.h \
	Box2D/Dynamics/b2World.h \
	Box2D/Dynamics/b2TimeStep.h \
	Box2D/Dynamics/b2Island.h \
	Box2D/Dynamics/b2Fixture.h \
	Box2D/Dynamics/b2ContactManager.h \
	Box2D/Dynamics/b2Body.h \
	Box2D/Dynamics/Contacts/b2TOISolver.h \
	Box2D/Dynamics/Contacts/b2ContactSolver.h \
	Box2D/Dynamics/Contacts/b2PolygonContact.h \
	Box2D/Dynamics/Contacts/b2Contact.h \
	Box2D/Dynamics/Contacts/b2PolygonAndCircleContact.h \
	Box2D/Dynamics/Contacts/b2CircleContact.h \
	Box2D/Dynamics/Joints/b2WeldJoint.h \
	Box2D/Dynamics/Joints/b2RevoluteJoint.h \
	Box2D/Dynamics/Joints/b2PulleyJoint.h \
	Box2D/Dynamics/Joints/b2PrismaticJoint.h \
	Box2D/Dynamics/Joints/b2MouseJoint.h \
	Box2D/Dynamics/Joints/b2LineJoint.h \
	Box2D/Dynamics/Joints/b2Joint.h \
	Box2D/Dynamics/Joints/b2GearJoint.h \
	Box2D/Dynamics/Joints/b2FrictionJoint.h \
	Box2D/Dynamics/Joints/b2DistanceJoint.h \
	vectormath/c/vectormath_soa_v.h \
	vectormath/c/vectormath_soa.h \
	vectormath/c/vectormath_aos_v.h \
	vectormath/c/vectormath_aos.h \
	vectormath/cpp/vectormath_soa.h \
	vectormath/cpp/vectormath_aos.h \
	vectormath/ios/vectormath_aos.h \
	vectormath/ios/vec_aos.h \
	vectormath/ios/quat_aos.h \
	vectormath/ios/mat_aos.h \
	vectormath/ios/floatInVec.h \
	vectormath/ios/boolInVec.h \
	vectormath/ppu/c/vectormath_soa_v.h \
	vectormath/ppu/c/vectormath_soa.h \
	vectormath/ppu/c/vectormath_aos_v.h \
	vectormath/ppu/c/vectormath_aos.h \
	vectormath/ppu/c/vec_types.h \
	vectormath/ppu/c/vec_soa_v.h \
	vectormath/ppu/c/vec_soa.h \
	vectormath/ppu/c/vec_aos_v.h \
	vectormath/ppu/c/quat_aos_v.h \
	vectormath/ppu/c/quat_aos.h \
	vectormath/ppu/c/mat_soa_v.h \
	vectormath/ppu/c/vec_aos.h \
	vectormath/ppu/c/quat_soa_v.h \
	vectormath/ppu/c/quat_soa.h \
	vectormath/ppu/c/mat_soa.h \
	vectormath/ppu/c/mat_aos_v.h \
	vectormath/ppu/c/mat_aos.h \
	vectormath/ppu/cpp/vectormath_soa.h \
	vectormath/ppu/cpp/vectormath_aos.h \
	vectormath/ppu/cpp/quat_soa.h \
	vectormath/ppu/cpp/quat_aos.h \
	vectormath/ppu/cpp/mat_soa.h \
	vectormath/ppu/cpp/vecidx_aos.h \
	vectormath/ppu/cpp/vec_soa.h \
	vectormath/ppu/cpp/vec_aos.h \
	vectormath/ppu/cpp/mat_aos.h \
	vectormath/ppu/cpp/floatInVec.h \
	vectormath/ppu/cpp/boolInVec.h \
	vectormath/scalar/c/vec_aos_v.h \
	vectormath/scalar/c/vec_aos.h \
	vectormath/scalar/c/quat_aos_v.h \
	vectormath/scalar/c/vectormath_aos_v.h \
	vectormath/scalar/c/vectormath_aos.h \
	vectormath/scalar/c/quat_aos.h \
	vectormath/scalar/c/mat_aos_v.h \
	vectormath/scalar/c/mat_aos.h \
	vectormath/scalar/cpp/vectormath_aos.h \
	vectormath/scalar/cpp/vec_aos.h \
	vectormath/scalar/cpp/quat_aos.h \
	vectormath/scalar/cpp/mat_aos.h \
	vectormath/scalar/cpp/floatInVec.h \
	vectormath/scalar/cpp/boolInVec.h \
	vectormath/spu/c/vectormath_soa_v.h \
	vectormath/spu/c/vectormath_soa.h \
	vectormath/spu/c/vectormath_aos_v.h \
	vectormath/spu/c/vectormath_aos.h \
	vectormath/spu/c/vec_soa_v.h \
	vectormath/spu/c/vec_soa.h \
	vectormath/spu/c/vec_aos_v.h \
	vectormath/spu/c/quat_aos_v.h \
	vectormath/spu/c/quat_aos.h \
	vectormath/spu/c/mat_soa_v.h \
	vectormath/spu/c/vec_aos.h \
	vectormath/spu/c/quat_soa_v.h \
	vectormath/spu/c/quat_soa.h \
	vectormath/spu/c/mat_soa.h \
	vectormath/spu/c/mat_aos_v.h \
	vectormath/spu/c/mat_aos.h \
	vectormath/spu/cpp/vectormath_soa.h \
	vectormath/spu/cpp/vectormath_aos.h \
	vectormath/spu/cpp/quat_soa.h \
	vectormath/spu/cpp/quat_aos.h \
	vectormath/spu/cpp/mat_soa.h \
	vectormath/spu/cpp/vecidx_aos.h \
	vectormath/spu/cpp/vec_soa.h \
	vectormath/spu/cpp/vec_aos.h \
	vectormath/spu/cpp/mat_aos.h \
	vectormath/spu/cpp/floatInVec.h \
	vectormath/spu/cpp/boolInVec.h \
	vectormath/SSE/cpp/vec_aos.h \
	vectormath/SSE/cpp/quat_aos.h \
	vectormath/SSE/cpp/vectormath_aos.h \
	vectormath/SSE/cpp/vecidx_aos.h \
	vectormath/SSE/cpp/mat_aos.h \
	vectormath/SSE/cpp/floatInVec.h \
	vectormath/SSE/cpp/boolInVec.h \
	vectormath/vfpmath/vsinf.h \
	vectormath/vfpmath/vfp_clobbers.h \
	vectormath/vfpmath/matrix_impl.h \
	vectormath/vfpmath/common_macros.h \
	lua/lzio.h \
	lua/lvm.h \
	lua/lundump.h \
	lua/lualib.h \
	lua/luaconf.h \
	lua/lua.hpp \
	lua/lua.h \
	lua/ltm.h \
	lua/ltable.h \
	lua/lstring.h \
	lua/lstate.h \
	lua/lparser.h \
	lua/lopcodes.h \
	lua/lobject.h \
	lua/lmem.h \
	lua/llimits.h \
	lua/llex.h \
	lua/lgc.h \
	lua/lfunc.h \
	lua/ldo.h \
	lua/ldebug.h \
	lua/lctype.h \
	lua/lcode.h \
	lua/lauxlib.h \
	lua/lapi.h

OTHER_FILES += \
	physfs/CREDITS.txt \
	physfs/LICENSE.txt \
	physfs/zlib123/README \
	physfs/extras/makecasefoldhashtable.pl \
	physfs/extras/casefolding.txt \
	Box2D/License.txt \
	vectormath/SSE/cpp/readme_e.txt \
	lua/Makefile