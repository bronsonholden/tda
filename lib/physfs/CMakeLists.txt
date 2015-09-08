SET(PHYSFS_MIRROR http://icculus.org/physfs/downloads/physfs-2.0.3.tar.bz2)
SET(PHYSFS_ARCHIVE ${CMAKE_CURRENT_LIST_DIR}/physfs-2.0.3.tar.bz2)
SET(PHYSFS_ROOT_DIR ${CMAKE_CURRENT_LIST_DIR}/physfs-2.0.3)

IF(NOT EXISTS ${PHYSFS_ARCHIVE} AND NOT EXISTS ${PHYSFS_ROOT_DIR})
	FILE(
		DOWNLOAD ${PHYSFS_MIRROR} ${PHYSFS_ARCHIVE}
		TIMEOUT 60
		STATUS PHYSFS_STATUS
		SHOW_PROGRESS
		)

	LIST(GET PHYSFS_STATUS 0 PHYSFS_ERROR)

	IF(NOT ${PHYSFS_ERROR_CODE} EQUAL 0)
		IF(EXISTS ${PHYSFS_ARCHIVE})
			FILE(REMOVE ${PHYSFS_ARCHIVE})
		ENDIF(EXISTS ${PHYSFS_ARCHIVE})

		LIST(GET PHYSFS_STATUS 1 PHYSFS_ERROR_DESC)

		MESSAGE(
			FATAL_ERROR
			"PhysicsFS download failed: ${PHYSFS_ERROR_DESC}"
			)
	ENDIF(NOT ${PHYSFS_ERROR_CODE} EQUAL 0)

	EXECUTE_PROCESS(
		COMMAND ${CMAKE_COMMAND} -E tar xvf ${PHYSFS_ARCHIVE}
		DEPENDS ${PHYSFS_ARCHIVE}
		WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
		OUTPUT_QUIET
		)

	FILE(REMOVE ${PHYSFS_ARCHIVE})
ENDIF(NOT EXISTS ${PHYSFS_ARCHIVE} AND NOT EXISTS ${PHYSFS_ROOT_DIR})

INCLUDE_DIRECTORIES(${PHYSFS_ROOT_DIR})

SET(
	TDA_LIB_INCLUDE_DIRS
	${TDA_LIB_INCLUDE_DIRS}
	${PHYSFS_ROOT_DIR}
	PARENT_SCOPE
	)

SET(
	PHYSFS_ZLIB_SRC
	${PHYSFS_ROOT_DIR}/zlib123/adler32.c
	${PHYSFS_ROOT_DIR}/zlib123/compress.c
	${PHYSFS_ROOT_DIR}/zlib123/crc32.c
	${PHYSFS_ROOT_DIR}/zlib123/deflate.c
	${PHYSFS_ROOT_DIR}/zlib123/gzio.c
	${PHYSFS_ROOT_DIR}/zlib123/infback.c
	${PHYSFS_ROOT_DIR}/zlib123/inffast.c
	${PHYSFS_ROOT_DIR}/zlib123/inflate.c
	${PHYSFS_ROOT_DIR}/zlib123/inftrees.c
	${PHYSFS_ROOT_DIR}/zlib123/trees.c
	${PHYSFS_ROOT_DIR}/zlib123/uncompr.c
	${PHYSFS_ROOT_DIR}/zlib123/zutil.c
	${PHYSFS_ROOT_DIR}/zlib123/crc32.h
	${PHYSFS_ROOT_DIR}/zlib123/deflate.h
	${PHYSFS_ROOT_DIR}/zlib123/inffast.h
	${PHYSFS_ROOT_DIR}/zlib123/inffixed.h
	${PHYSFS_ROOT_DIR}/zlib123/inflate.h
	${PHYSFS_ROOT_DIR}/zlib123/inftrees.h
	${PHYSFS_ROOT_DIR}/zlib123/trees.h
	${PHYSFS_ROOT_DIR}/zlib123/zconf.h
	${PHYSFS_ROOT_DIR}/zlib123/zlib.h
	${PHYSFS_ROOT_DIR}/zlib123/zutil.h
	)

SET(
	PHYSFS_LZMA_SRC
	${PHYSFS_ROOT_DIR}/lzma/C/7zCrc.c
	${PHYSFS_ROOT_DIR}/lzma/C/Archive/7z/7zBuffer.c
	${PHYSFS_ROOT_DIR}/lzma/C/Archive/7z/7zDecode.c
	${PHYSFS_ROOT_DIR}/lzma/C/Archive/7z/7zExtract.c
	${PHYSFS_ROOT_DIR}/lzma/C/Archive/7z/7zHeader.c
	${PHYSFS_ROOT_DIR}/lzma/C/Archive/7z/7zIn.c
	${PHYSFS_ROOT_DIR}/lzma/C/Archive/7z/7zItem.c
	${PHYSFS_ROOT_DIR}/lzma/C/Archive/7z/7zMethodID.c
	${PHYSFS_ROOT_DIR}/lzma/C/Compress/Branch/BranchX86.c
	${PHYSFS_ROOT_DIR}/lzma/C/Compress/Branch/BranchX86_2.c
	${PHYSFS_ROOT_DIR}/lzma/C/Compress/Branch/BranchX86.h
	${PHYSFS_ROOT_DIR}/lzma/C/Compress/Branch/BranchX86_2.h
	${PHYSFS_ROOT_DIR}/lzma/C/Compress/Lzma/LzmaDecode.c
	${PHYSFS_ROOT_DIR}/lzma/C/Compress/Lzma/LzmaDecode.h
	${PHYSFS_ROOT_DIR}/lzma/C/Compress/Lzma/LzmaStateDecode.h
	${PHYSFS_ROOT_DIR}/lzma/C/Compress/Lzma/LzmaTypes.h
	${PHYSFS_ROOT_DIR}/lzma/C/7zCrc.h
	${PHYSFS_ROOT_DIR}/lzma/C/Alloc.h
	${PHYSFS_ROOT_DIR}/lzma/C/CpuArch.h
	${PHYSFS_ROOT_DIR}/lzma/C/IStream.h
	${PHYSFS_ROOT_DIR}/lzma/C/Sort.h
	${PHYSFS_ROOT_DIR}/lzma/C/Threads.h
	${PHYSFS_ROOT_DIR}/lzma/C/Types.h
	)

SET(
	PHYSFS_SRC
	${PHYSFS_ROOT_DIR}/physfs.c
	${PHYSFS_ROOT_DIR}/physfs_byteorder.c
	${PHYSFS_ROOT_DIR}/physfs_unicode.c
	${PHYSFS_ROOT_DIR}/platform/os2.c
	${PHYSFS_ROOT_DIR}/platform/pocketpc.c
	${PHYSFS_ROOT_DIR}/platform/posix.c
	${PHYSFS_ROOT_DIR}/platform/unix.c
	${PHYSFS_ROOT_DIR}/platform/macosx.c
	${PHYSFS_ROOT_DIR}/platform/windows.c
	${PHYSFS_ROOT_DIR}/archivers/dir.c
	${PHYSFS_ROOT_DIR}/archivers/grp.c
	${PHYSFS_ROOT_DIR}/archivers/hog.c
	${PHYSFS_ROOT_DIR}/archivers/lzma.c
	${PHYSFS_ROOT_DIR}/archivers/mvl.c
	${PHYSFS_ROOT_DIR}/archivers/qpak.c
	${PHYSFS_ROOT_DIR}/archivers/wad.c
	${PHYSFS_ROOT_DIR}/archivers/zip.c
	)

INCLUDE_DIRECTORIES(${PHYSFS_ROOT_DIR}/zlib123)

IF(MSVC)
	ADD_DEFINITIONS(-D_CRT_SECURE_NO_WARNINGS)
ENDIF(MSVC)

ADD_DEFINITIONS(-DZ_PREFIX=1)
ADD_DEFINITIONS(-DPHYSFS_NO_CDROM_SUPPORT=1)

ADD_LIBRARY(
	TDA_lib_physfs
	STATIC
	${PHYSFS_SRC}
	${PHYSFS_ZLIB_SRC}
	${PHYSFS_LZMA_SRC}
	)
