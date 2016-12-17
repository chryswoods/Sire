###
### CMake file to install boost::python
### in the Sire bundle
###

unset(BOOST_PYTHON_LIBRARY CACHE)

if ( ANACONDA_BUILD )
  find_library( BOOST_PYTHON_LIBRARY
                NAMES boost_python
                PATHS ${BUNDLE_STAGEDIR}/lib NO_DEFAULT_PATH )

elseif ( MSYS )
  message( STATUS "Looking for MSYS version of boost::python..." )
  set (BOOST_ALL_DYN_LINK "YES")
  find_package( Boost 1.31 COMPONENTS python3 REQUIRED )
  set ( BOOST_PYTHON_LIBRARY "${Boost_LIBRARIES}" )
  set ( BOOST_PYTHON_HEADERS "${Boost_INCLUDE_DIR}" )

else()
  find_library( BOOST_PYTHON_LIBRARY 
                NAMES boost_python
                PATHS ${BUNDLE_STAGEDIR}/lib NO_DEFAULT_PATH )
endif()

if ( BOOST_PYTHON_LIBRARY )
  message( STATUS "Have already compiled a bundled version of boost::python")
else()
  message( STATUS "Compiling and installing a bundled version of boost::python" )

  set( BOOST_PYTHON_ZIPFILE "${CMAKE_SOURCE_DIR}/bundled/boost_python.tar.gz" )

  if (EXISTS "${BOOST_PYTHON_ZIPFILE}")
    set( BOOST_PYTHON_BUILD_DIR "${BUNDLE_BUILDDIR}/boost_python/build" )

    if (NOT EXISTS "${BOOST_PYTHON_BUILD_DIR}")
      message( STATUS "Unzipping ${BOOST_PYTHON_ZIPFILE} to ${BOOST_PYTHON_BUILD_DIR}" )
      execute_process(
          COMMAND ${CMAKE_COMMAND} -E tar xzf ${BOOST_PYTHON_ZIPFILE}
          WORKING_DIRECTORY ${BUNDLE_BUILDDIR}
          OUTPUT_QUIET ERROR_QUIET
      )
    endif()
  endif()

  message( STATUS "Patience... Configuring boost::python" )
  if (MSYS)
    list( APPEND COMPILE_OPTIONS "-G" )
    list( APPEND COMPILE_OPTIONS "MSYS Makefiles" )
  endif()

  list( APPEND COMPILE_OPTIONS "-DCMAKE_CXX_COMPILER=${CMAKE_CXX_COMPILER}" )
  list( APPEND COMPILE_OPTIONS "-DPYTHON_LIBRARIES=${PYTHON_LIBRARIES}" )
  list( APPEND COMPILE_OPTIONS "-DPYTHON_INCLUDE_DIR=${PYTHON_INCLUDE_DIR}" )
  list( APPEND COMPILE_OPTIONS "-DCMAKE_INSTALL_PREFIX=${BUNDLE_STAGEDIR}" )
  list( APPEND COMPILE_OPTIONS "-DCMAKE_CXX_FLAGS=${SIRE_CXX11_FLAGS} -O2" )
  list( APPEND COMPILE_OPTIONS "../src" )

  message( STATUS "${CMAKE_COMMAND} ${COMPILE_OPTIONS}" )

  execute_process(
          COMMAND ${CMAKE_COMMAND} ${COMPILE_OPTIONS}
          WORKING_DIRECTORY ${BOOST_PYTHON_BUILD_DIR}
          OUTPUT_QUIET ERROR_QUIET
  )

  message( STATUS "Patience... Building boost::python" )
  execute_process(
          COMMAND ${CMAKE_MAKE_PROGRAM} -k -j ${NCORES}
          WORKING_DIRECTORY ${BOOST_PYTHON_BUILD_DIR}
          OUTPUT_QUIET ERROR_QUIET
  )

  message( STATUS "Patience... Installing boost::python" )
  execute_process(
          COMMAND ${CMAKE_MAKE_PROGRAM} install
          WORKING_DIRECTORY ${BOOST_PYTHON_BUILD_DIR}
          OUTPUT_QUIET ERROR_QUIET
  )

  if (APPLE)
    set( BOOST_PYTHON_LIBRARY "${BUNDLE_STAGEDIR}/lib/libboost_python.dylib" )
  else()
    set( BOOST_PYTHON_LIBRARY "${BUNDLE_STAGEDIR}/lib/libboost_python.so" )
  endif()

endif()

if ( MSYS )
  if ( BOOST_PYTHON_LIBRARY )
    message( STATUS "Using boost::python in ${BOOST_PYTHON_LIBRARY} | ${BOOST_PYTHON_HEADERS}" )
  else()
    message( FATAL_ERROR "Cannot find boost::python in MSYS!" )
  endif()
else()
  if ( BOOST_PYTHON_LIBRARY )
    set( BOOST_PYTHON_HEADERS "${BUNDLE_STAGEDIR}/include" )
    message( STATUS "Using bundled boost::python in ${BOOST_PYTHON_LIBRARY} | ${BOOST_PYTHON_HEADERS}" )
    set( SIRE_FOUND_BOOST_PYTHON TRUE )
  else()
    message( STATUS "Strange? Cannot find the installed boost::python library. We cannot compile it, so will need to rely on the system version..." )
  endif()
endif()
