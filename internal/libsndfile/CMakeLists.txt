include(FetchContent)
include(functions/NovelRTDeps_Populate)
message(STATUS "Fetching libsndfile...")

if(NOVELRT_SHARED_SNDFILE OR NOVELRT_BUILD_SHARED_LIBS)
  set(type SHARED)
else()
  set(type STATIC)
endif()

set(ENABLE_PACKAGE_CONFIG OFF CACHE BOOL "" FORCE)

FetchContent_Declare(sndfile
  URL https://github.com/libsndfile/libsndfile/archive/refs/tags/1.1.0.tar.gz
  URL_HASH SHA512=5e530c33165a2d2be1c22d3a4bd96f0f1817dded3a45d24bad0e3f2c7908ccc1f19327a91d5040c3ea4d591845876019180747a125bf2a6f8bd49a6f67eadacd

  PREFIX "${CMAKE_CURRENT_BINARY_DIR}"
  TMP_DIR "${CMAKE_CURRENT_BINARY_DIR}/tmp"
  STAMP_DIR "${CMAKE_CURRENT_BINARY_DIR}/stamp"
  DOWNLOAD_DIR "${CMAKE_CURRENT_BINARY_DIR}/dl"
  SOURCE_DIR "${CMAKE_CURRENT_BINARY_DIR}/src"
  SUBBUILD_DIR "${CMAKE_CURRENT_BINARY_DIR}/build"
  BINARY_DIR "${CMAKE_CURRENT_BINARY_DIR}/bin"
  INSTALL_DIR "${CMAKE_CURRENT_BINARY_DIR}/inst"
  LOG_DIR "${CMAKE_CURRENT_BINARY_DIR}/log"

  PATCH_COMMAND git apply "${CMAKE_CURRENT_LIST_DIR}/v1.1.0.patch"
)

NovelRTDeps_PopulateExplicit(sndfile SHARED)

add_library (SNDFILE ${type}
	${sndfile_SOURCE_DIR}/src/sfconfig.h
	${sndfile_SOURCE_DIR}/src/sfendian.h
	${sndfile_SOURCE_DIR}/src/sf_unistd.h
	${sndfile_SOURCE_DIR}/src/common.h
	${sndfile_SOURCE_DIR}/src/common.c
	${sndfile_SOURCE_DIR}/src/file_io.c
	${sndfile_SOURCE_DIR}/src/command.c
	${sndfile_SOURCE_DIR}/src/pcm.c
	${sndfile_SOURCE_DIR}/src/ulaw.c
	${sndfile_SOURCE_DIR}/src/alaw.c
	${sndfile_SOURCE_DIR}/src/float32.c
	${sndfile_SOURCE_DIR}/src/double64.c
	${sndfile_SOURCE_DIR}/src/ima_adpcm.c
	${sndfile_SOURCE_DIR}/src/ms_adpcm.c
	${sndfile_SOURCE_DIR}/src/gsm610.c
	${sndfile_SOURCE_DIR}/src/dwvw.c
	${sndfile_SOURCE_DIR}/src/vox_adpcm.c
	${sndfile_SOURCE_DIR}/src/interleave.c
	${sndfile_SOURCE_DIR}/src/strings.c
	${sndfile_SOURCE_DIR}/src/dither.c
	${sndfile_SOURCE_DIR}/src/cart.c
	${sndfile_SOURCE_DIR}/src/broadcast.c
	${sndfile_SOURCE_DIR}/src/audio_detect.c
 	${sndfile_SOURCE_DIR}/src/ima_oki_adpcm.c
	${sndfile_SOURCE_DIR}/src/ima_oki_adpcm.h
	${sndfile_SOURCE_DIR}/src/alac.c
	${sndfile_SOURCE_DIR}/src/chunk.c
	${sndfile_SOURCE_DIR}/src/ogg.h
	${sndfile_SOURCE_DIR}/src/ogg.c
	${sndfile_SOURCE_DIR}/src/chanmap.h
	${sndfile_SOURCE_DIR}/src/chanmap.c
	${sndfile_SOURCE_DIR}/src/id3.h
	${sndfile_SOURCE_DIR}/src/id3.c
	$<$<BOOL:${WIN32}>:${sndfile_SOURCE_DIR}/src/windows.c>
	${sndfile_SOURCE_DIR}/src/sndfile.c
	${sndfile_SOURCE_DIR}/src/aiff.c
	${sndfile_SOURCE_DIR}/src/au.c
	${sndfile_SOURCE_DIR}/src/avr.c
	${sndfile_SOURCE_DIR}/src/caf.c
	${sndfile_SOURCE_DIR}/src/dwd.c
	${sndfile_SOURCE_DIR}/src/flac.c
	${sndfile_SOURCE_DIR}/src/g72x.c
	${sndfile_SOURCE_DIR}/src/htk.c
	${sndfile_SOURCE_DIR}/src/ircam.c
	${sndfile_SOURCE_DIR}/src/macos.c
	${sndfile_SOURCE_DIR}/src/mat4.c
	${sndfile_SOURCE_DIR}/src/mat5.c
	${sndfile_SOURCE_DIR}/src/nist.c
	${sndfile_SOURCE_DIR}/src/paf.c
	${sndfile_SOURCE_DIR}/src/pvf.c
	${sndfile_SOURCE_DIR}/src/raw.c
	${sndfile_SOURCE_DIR}/src/rx2.c
	${sndfile_SOURCE_DIR}/src/sd2.c
	${sndfile_SOURCE_DIR}/src/sds.c
	${sndfile_SOURCE_DIR}/src/svx.c
	${sndfile_SOURCE_DIR}/src/txw.c
	${sndfile_SOURCE_DIR}/src/voc.c
	${sndfile_SOURCE_DIR}/src/wve.c
	${sndfile_SOURCE_DIR}/src/w64.c
	${sndfile_SOURCE_DIR}/src/wavlike.h
	${sndfile_SOURCE_DIR}/src/wavlike.c
	${sndfile_SOURCE_DIR}/src/wav.c
	${sndfile_SOURCE_DIR}/src/xi.c
	${sndfile_SOURCE_DIR}/src/mpc2k.c
	${sndfile_SOURCE_DIR}/src/rf64.c
	${sndfile_SOURCE_DIR}/src/ogg_vorbis.c
	${sndfile_SOURCE_DIR}/src/ogg_speex.c
	${sndfile_SOURCE_DIR}/src/ogg_pcm.c
	${sndfile_SOURCE_DIR}/src/ogg_opus.c
	${sndfile_SOURCE_DIR}/src/ogg_vcomment.h
	${sndfile_SOURCE_DIR}/src/ogg_vcomment.c
	${sndfile_SOURCE_DIR}/src/nms_adpcm.c
	${sndfile_SOURCE_DIR}/src/mpeg.c
	${sndfile_SOURCE_DIR}/src/mpeg_decode.c
	${sndfile_SOURCE_DIR}/src/mpeg_l3_encode.c
	${sndfile_SOURCE_DIR}/src/GSM610/config.h
	${sndfile_SOURCE_DIR}/src/GSM610/gsm.h
	${sndfile_SOURCE_DIR}/src/GSM610/gsm610_priv.h
	${sndfile_SOURCE_DIR}/src/GSM610/add.c
	${sndfile_SOURCE_DIR}/src/GSM610/code.c
	${sndfile_SOURCE_DIR}/src/GSM610/decode.c
	${sndfile_SOURCE_DIR}/src/GSM610/gsm_create.c
	${sndfile_SOURCE_DIR}/src/GSM610/gsm_decode.c
	${sndfile_SOURCE_DIR}/src/GSM610/gsm_destroy.c
	${sndfile_SOURCE_DIR}/src/GSM610/gsm_encode.c
	${sndfile_SOURCE_DIR}/src/GSM610/gsm_option.c
	${sndfile_SOURCE_DIR}/src/GSM610/long_term.c
	${sndfile_SOURCE_DIR}/src/GSM610/lpc.c
	${sndfile_SOURCE_DIR}/src/GSM610/preprocess.c
	${sndfile_SOURCE_DIR}/src/GSM610/rpe.c
	${sndfile_SOURCE_DIR}/src/GSM610/short_term.c
	${sndfile_SOURCE_DIR}/src/GSM610/table.c
	${sndfile_SOURCE_DIR}/src/G72x/g72x.h
	${sndfile_SOURCE_DIR}/src/G72x/g72x_priv.h
	${sndfile_SOURCE_DIR}/src/G72x/g721.c
	${sndfile_SOURCE_DIR}/src/G72x/g723_16.c
	${sndfile_SOURCE_DIR}/src/G72x/g723_24.c
	${sndfile_SOURCE_DIR}/src/G72x/g723_40.c
	${sndfile_SOURCE_DIR}/src/G72x/g72x.c
	${sndfile_SOURCE_DIR}/src/ALAC/ALACAudioTypes.h
	${sndfile_SOURCE_DIR}/src/ALAC/ALACBitUtilities.h
	${sndfile_SOURCE_DIR}/src/ALAC/EndianPortable.h
	${sndfile_SOURCE_DIR}/src/ALAC/aglib.h
	${sndfile_SOURCE_DIR}/src/ALAC/dplib.h
	${sndfile_SOURCE_DIR}/src/ALAC/matrixlib.h
	${sndfile_SOURCE_DIR}/src/ALAC/alac_codec.h
	${sndfile_SOURCE_DIR}/src/ALAC/shift.h
	${sndfile_SOURCE_DIR}/src/ALAC/ALACBitUtilities.c
	${sndfile_SOURCE_DIR}/src/ALAC/ag_dec.c
	${sndfile_SOURCE_DIR}/src/ALAC/ag_enc.c
	${sndfile_SOURCE_DIR}/src/ALAC/dp_dec.c
	${sndfile_SOURCE_DIR}/src/ALAC/dp_enc.c
	${sndfile_SOURCE_DIR}/src/ALAC/matrix_dec.c
	${sndfile_SOURCE_DIR}/src/ALAC/matrix_enc.c
	${sndfile_SOURCE_DIR}/src/ALAC/alac_decoder.c
	${sndfile_SOURCE_DIR}/src/ALAC/alac_encoder.c
	${sndfile_SOURCE_DIR}/include/sndfile.hh
	${sndfile_BINARY_DIR}/include/sndfile.h
	${sndfile_BINARY_DIR}/src/config.h
)

add_library (Sndfile::sndfile ALIAS SNDFILE)
set_target_properties(SNDFILE
  PROPERTIES
    OUTPUT_NAME "sndfile")
target_include_directories (SNDFILE
	PUBLIC
		$<BUILD_INTERFACE:${sndfile_SOURCE_DIR}/include>
		$<BUILD_INTERFACE:${sndfile_BINARY_DIR}/include>
		$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
	PRIVATE
		$<BUILD_INTERFACE:${sndfile_BINARY_DIR}/src>
    $<BUILD_INTERFACE:${sndfile_SOURCE_DIR}/src>
)
target_link_libraries (SNDFILE
	PRIVATE
		$<$<BOOL:${LIBM_REQUIRED}>:m>
		Vorbis::vorbisenc
		FLAC::FLAC
		Opus::Opus
)
