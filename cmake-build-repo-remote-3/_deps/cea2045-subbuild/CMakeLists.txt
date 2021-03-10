# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.18.4)

# We name the project and the target for the ExternalProject_Add() call
# to something that will highlight to the user what we are working on if
# something goes wrong and an error message is produced.

project(cea2045-populate NONE)

include(ExternalProject)
ExternalProject_Add(cea2045-populate
                     "UPDATE_DISCONNECTED" "False" "GIT_REPOSITORY" "https://github.com/epri-dev/CTA-2045-UCM-CPP-Library.git" "GIT_TAG" "master"
                    SOURCE_DIR          "/home/pi/Documents/EGoT-DCS/cmake-build-repo-remote-3/_deps/cea2045-src"
                    BINARY_DIR          "/home/pi/Documents/EGoT-DCS/cmake-build-repo-remote-3/_deps/cea2045-build"
                    CONFIGURE_COMMAND   ""
                    BUILD_COMMAND       ""
                    INSTALL_COMMAND     ""
                    TEST_COMMAND        ""
                    USES_TERMINAL_DOWNLOAD  YES
                    USES_TERMINAL_UPDATE    YES
)


