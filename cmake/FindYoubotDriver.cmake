# - Try to find YoubotDriver
#
# Sets the following variables:
#
#  youbotDriver_FOUND - if package found
#  youbotDriver_INCLUDE_DIRS - include directories
#  youbotDriver_LIBRARIES    - libraries
#  youbotDriver_CONFIG_DIR   - folder with (EtherCAT) configuration files
#
# The returned variables do not include settings for Boost.
# On Windows, this file also tries to locate WinPcap and adds 
# the corresponding settings to the returned variables.
#

find_path(youbotDriver_INCLUDE_DIR NAMES youbot_driver/youbot/YouBotBase.hpp
	PATH_SUFFIXES 
		youbot_driver/include
	PATHS 
		$ENV{YOUBOTDIR}/include
)

find_path(youbotDriver_CONFIG_DIR NAMES youbot-ethercat.cfg
	PATH_SUFFIXES 
		youbot_driver/config
	PATHS 
		$ENV{YOUBOTDIR}/config
)

find_library(youbotDriver_LIBRARY_YOUBOTDRIVER YouBotDriver
	PATH_SUFFIXES 
		youbot_driver/lib
	PATHS 
		$ENV{YOUBOTDIR}/build/Debug
)

find_library(youbotDriver_LIBRARY_SOEM soem
	PATH_SUFFIXES 
		youbot_driver/lib
	PATHS 
		$ENV{YOUBOTDIR}/build/src/soem/Debug
)

if (WIN32)
	find_package(WinPcap REQUIRED)
endif()

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(youbotDriver DEFAULT_MSG 
	youbotDriver_INCLUDE_DIR
	youbotDriver_CONFIG_DIR
	youbotDriver_LIBRARY_YOUBOTDRIVER
	youbotDriver_LIBRARY_SOEM
)

set(youbotDriver_FOUND ${YOUBOTDRIVER_FOUND})

if(youbotDriver_FOUND)
	if (WIN32)
		set(youbotDriver_INCLUDE_DIRS 
			${youbotDriver_INCLUDE_DIR}
			${youbotDriver_INCLUDE_DIR}/youbot_driver/soem/osal
			${youbotDriver_INCLUDE_DIR}/youbot_driver/soem/osal/win32
			${youbotDriver_INCLUDE_DIR}/youbot_driver/soem/oshw/win32
			${WINPCAP_INCLUDE_DIRS}
		)
		set(youbotDriver_LIBRARIES
			${youbotDriver_LIBRARY_YOUBOTDRIVER}
			${youbotDriver_LIBRARY_SOEM}
			${WINPCAP_LIBRARIES}
			WS2_32.lib
			Winmm.lib
		)
	else(WIN32)
		set(youbotDriver_INCLUDE_DIRS 
			${youbotDriver_INCLUDE_DIR}
			${youbotDriver_INCLUDE_DIR}/youbot_driver/soem/osal
			${youbotDriver_INCLUDE_DIR}/youbot_driver/soem/oshw/linux
		)
		set(youbotDriver_LIBRARIES
			${youbotDriver_LIBRARY_YOUBOTDRIVER}
			${youbotDriver_LIBRARY_SOEM}
		)
	endif(WIN32)
else()
	set(youbotDriver_INCLUDE_DIRS)
	set(youbotDriver_LIBRARIES)
	set(youbotDriver_CONFIG_DIR)
endif()

mark_as_advanced(youbotDriver_LIBRARIES youbotDriver_INCLUDE_DIRS youbotDriver_CONFIG_DIR)
