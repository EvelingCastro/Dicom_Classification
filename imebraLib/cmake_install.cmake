# Install script for directory: /home/rcruz/workspace/Citesoft/dicom/imebra_4_2_1_1

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "0")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/doc/libimebra1" TYPE FILE PERMISSIONS OWNER_WRITE OWNER_READ GROUP_READ WORLD_READ FILES "/home/rcruz/workspace/Citesoft/dicom/imebraLib/copyright")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  foreach(file
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libimebra.so.1.0.0"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libimebra.so.1"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libimebra.so"
      )
    if(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      file(RPATH_CHECK
           FILE "${file}"
           RPATH "")
    endif()
  endforeach()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES
    "/home/rcruz/workspace/Citesoft/dicom/imebraLib/libimebra.so.1.0.0"
    "/home/rcruz/workspace/Citesoft/dicom/imebraLib/libimebra.so.1"
    "/home/rcruz/workspace/Citesoft/dicom/imebraLib/libimebra.so"
    )
  foreach(file
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libimebra.so.1.0.0"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libimebra.so.1"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libimebra.so"
      )
    if(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      if(CMAKE_INSTALL_DO_STRIP)
        execute_process(COMMAND "/usr/bin/strip" "${file}")
      endif()
    endif()
  endforeach()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xInclude filesx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/imebra" TYPE FILE FILES
    "/home/rcruz/workspace/Citesoft/dicom/imebra_4_2_1_1/library/include/imebra/VOILUT.h"
    "/home/rcruz/workspace/Citesoft/dicom/imebra_4_2_1_1/library/include/imebra/acse.h"
    "/home/rcruz/workspace/Citesoft/dicom/imebra_4_2_1_1/library/include/imebra/baseStreamInput.h"
    "/home/rcruz/workspace/Citesoft/dicom/imebra_4_2_1_1/library/include/imebra/baseStreamOutput.h"
    "/home/rcruz/workspace/Citesoft/dicom/imebra_4_2_1_1/library/include/imebra/codecFactory.h"
    "/home/rcruz/workspace/Citesoft/dicom/imebra_4_2_1_1/library/include/imebra/colorTransformsFactory.h"
    "/home/rcruz/workspace/Citesoft/dicom/imebra_4_2_1_1/library/include/imebra/dataSet.h"
    "/home/rcruz/workspace/Citesoft/dicom/imebra_4_2_1_1/library/include/imebra/definitions.h"
    "/home/rcruz/workspace/Citesoft/dicom/imebra_4_2_1_1/library/include/imebra/dicomDictionary.h"
    "/home/rcruz/workspace/Citesoft/dicom/imebra_4_2_1_1/library/include/imebra/dicomDir.h"
    "/home/rcruz/workspace/Citesoft/dicom/imebra_4_2_1_1/library/include/imebra/dicomDirEntry.h"
    "/home/rcruz/workspace/Citesoft/dicom/imebra_4_2_1_1/library/include/imebra/dimse.h"
    "/home/rcruz/workspace/Citesoft/dicom/imebra_4_2_1_1/library/include/imebra/drawBitmap.h"
    "/home/rcruz/workspace/Citesoft/dicom/imebra_4_2_1_1/library/include/imebra/exceptions.h"
    "/home/rcruz/workspace/Citesoft/dicom/imebra_4_2_1_1/library/include/imebra/fileStreamInput.h"
    "/home/rcruz/workspace/Citesoft/dicom/imebra_4_2_1_1/library/include/imebra/fileStreamOutput.h"
    "/home/rcruz/workspace/Citesoft/dicom/imebra_4_2_1_1/library/include/imebra/image.h"
    "/home/rcruz/workspace/Citesoft/dicom/imebra_4_2_1_1/library/include/imebra/imebra.h"
    "/home/rcruz/workspace/Citesoft/dicom/imebra_4_2_1_1/library/include/imebra/lut.h"
    "/home/rcruz/workspace/Citesoft/dicom/imebra_4_2_1_1/library/include/imebra/memoryPool.h"
    "/home/rcruz/workspace/Citesoft/dicom/imebra_4_2_1_1/library/include/imebra/memoryStreamInput.h"
    "/home/rcruz/workspace/Citesoft/dicom/imebra_4_2_1_1/library/include/imebra/memoryStreamOutput.h"
    "/home/rcruz/workspace/Citesoft/dicom/imebra_4_2_1_1/library/include/imebra/modalityVOILUT.h"
    "/home/rcruz/workspace/Citesoft/dicom/imebra_4_2_1_1/library/include/imebra/pipe.h"
    "/home/rcruz/workspace/Citesoft/dicom/imebra_4_2_1_1/library/include/imebra/readMemory.h"
    "/home/rcruz/workspace/Citesoft/dicom/imebra_4_2_1_1/library/include/imebra/readWriteMemory.h"
    "/home/rcruz/workspace/Citesoft/dicom/imebra_4_2_1_1/library/include/imebra/readingDataHandler.h"
    "/home/rcruz/workspace/Citesoft/dicom/imebra_4_2_1_1/library/include/imebra/readingDataHandlerNumeric.h"
    "/home/rcruz/workspace/Citesoft/dicom/imebra_4_2_1_1/library/include/imebra/streamReader.h"
    "/home/rcruz/workspace/Citesoft/dicom/imebra_4_2_1_1/library/include/imebra/streamWriter.h"
    "/home/rcruz/workspace/Citesoft/dicom/imebra_4_2_1_1/library/include/imebra/tag.h"
    "/home/rcruz/workspace/Citesoft/dicom/imebra_4_2_1_1/library/include/imebra/tagId.h"
    "/home/rcruz/workspace/Citesoft/dicom/imebra_4_2_1_1/library/include/imebra/tagsEnumeration.h"
    "/home/rcruz/workspace/Citesoft/dicom/imebra_4_2_1_1/library/include/imebra/tcpAddress.h"
    "/home/rcruz/workspace/Citesoft/dicom/imebra_4_2_1_1/library/include/imebra/tcpListener.h"
    "/home/rcruz/workspace/Citesoft/dicom/imebra_4_2_1_1/library/include/imebra/tcpStream.h"
    "/home/rcruz/workspace/Citesoft/dicom/imebra_4_2_1_1/library/include/imebra/transform.h"
    "/home/rcruz/workspace/Citesoft/dicom/imebra_4_2_1_1/library/include/imebra/transformHighBit.h"
    "/home/rcruz/workspace/Citesoft/dicom/imebra_4_2_1_1/library/include/imebra/transformsChain.h"
    "/home/rcruz/workspace/Citesoft/dicom/imebra_4_2_1_1/library/include/imebra/uidsEnumeration.h"
    "/home/rcruz/workspace/Citesoft/dicom/imebra_4_2_1_1/library/include/imebra/writingDataHandler.h"
    "/home/rcruz/workspace/Citesoft/dicom/imebra_4_2_1_1/library/include/imebra/writingDataHandlerNumeric.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "/home/rcruz/workspace/Citesoft/dicom/imebraLib/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
