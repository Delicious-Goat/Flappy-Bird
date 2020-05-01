# Install script for directory: C:/Users/hartenc/source/repos/Delicious-Goat/Flappy-Bird/Vendor/eigen/Eigen

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Users/hartenc/Source/Repos/Delicious-Goat/Flappy-Bird/Vendor/eigen/out/install/x64-Debug")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
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

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xDevelx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/eigen3/Eigen" TYPE FILE FILES
    "C:/Users/hartenc/source/repos/Delicious-Goat/Flappy-Bird/Vendor/eigen/Eigen/Cholesky"
    "C:/Users/hartenc/source/repos/Delicious-Goat/Flappy-Bird/Vendor/eigen/Eigen/CholmodSupport"
    "C:/Users/hartenc/source/repos/Delicious-Goat/Flappy-Bird/Vendor/eigen/Eigen/Core"
    "C:/Users/hartenc/source/repos/Delicious-Goat/Flappy-Bird/Vendor/eigen/Eigen/Dense"
    "C:/Users/hartenc/source/repos/Delicious-Goat/Flappy-Bird/Vendor/eigen/Eigen/Eigen"
    "C:/Users/hartenc/source/repos/Delicious-Goat/Flappy-Bird/Vendor/eigen/Eigen/Eigenvalues"
    "C:/Users/hartenc/source/repos/Delicious-Goat/Flappy-Bird/Vendor/eigen/Eigen/Geometry"
    "C:/Users/hartenc/source/repos/Delicious-Goat/Flappy-Bird/Vendor/eigen/Eigen/Householder"
    "C:/Users/hartenc/source/repos/Delicious-Goat/Flappy-Bird/Vendor/eigen/Eigen/IterativeLinearSolvers"
    "C:/Users/hartenc/source/repos/Delicious-Goat/Flappy-Bird/Vendor/eigen/Eigen/Jacobi"
    "C:/Users/hartenc/source/repos/Delicious-Goat/Flappy-Bird/Vendor/eigen/Eigen/LU"
    "C:/Users/hartenc/source/repos/Delicious-Goat/Flappy-Bird/Vendor/eigen/Eigen/MetisSupport"
    "C:/Users/hartenc/source/repos/Delicious-Goat/Flappy-Bird/Vendor/eigen/Eigen/OrderingMethods"
    "C:/Users/hartenc/source/repos/Delicious-Goat/Flappy-Bird/Vendor/eigen/Eigen/PaStiXSupport"
    "C:/Users/hartenc/source/repos/Delicious-Goat/Flappy-Bird/Vendor/eigen/Eigen/PardisoSupport"
    "C:/Users/hartenc/source/repos/Delicious-Goat/Flappy-Bird/Vendor/eigen/Eigen/QR"
    "C:/Users/hartenc/source/repos/Delicious-Goat/Flappy-Bird/Vendor/eigen/Eigen/QtAlignedMalloc"
    "C:/Users/hartenc/source/repos/Delicious-Goat/Flappy-Bird/Vendor/eigen/Eigen/SPQRSupport"
    "C:/Users/hartenc/source/repos/Delicious-Goat/Flappy-Bird/Vendor/eigen/Eigen/SVD"
    "C:/Users/hartenc/source/repos/Delicious-Goat/Flappy-Bird/Vendor/eigen/Eigen/Sparse"
    "C:/Users/hartenc/source/repos/Delicious-Goat/Flappy-Bird/Vendor/eigen/Eigen/SparseCholesky"
    "C:/Users/hartenc/source/repos/Delicious-Goat/Flappy-Bird/Vendor/eigen/Eigen/SparseCore"
    "C:/Users/hartenc/source/repos/Delicious-Goat/Flappy-Bird/Vendor/eigen/Eigen/SparseLU"
    "C:/Users/hartenc/source/repos/Delicious-Goat/Flappy-Bird/Vendor/eigen/Eigen/SparseQR"
    "C:/Users/hartenc/source/repos/Delicious-Goat/Flappy-Bird/Vendor/eigen/Eigen/StdDeque"
    "C:/Users/hartenc/source/repos/Delicious-Goat/Flappy-Bird/Vendor/eigen/Eigen/StdList"
    "C:/Users/hartenc/source/repos/Delicious-Goat/Flappy-Bird/Vendor/eigen/Eigen/StdVector"
    "C:/Users/hartenc/source/repos/Delicious-Goat/Flappy-Bird/Vendor/eigen/Eigen/SuperLUSupport"
    "C:/Users/hartenc/source/repos/Delicious-Goat/Flappy-Bird/Vendor/eigen/Eigen/UmfPackSupport"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xDevelx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/eigen3/Eigen" TYPE DIRECTORY FILES "C:/Users/hartenc/source/repos/Delicious-Goat/Flappy-Bird/Vendor/eigen/Eigen/src" FILES_MATCHING REGEX "/[^/]*\\.h$")
endif()

