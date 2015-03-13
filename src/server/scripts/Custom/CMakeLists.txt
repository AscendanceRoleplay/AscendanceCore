# Copyright (C) 2008-2014 TrinityCore <http://www.trinitycore.org/>
#
# This file is free software; as a special exception the author gives
# unlimited permission to copy and/or distribute it, with or without
# modifications, as long as this notice is preserved.
#
# This program is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY, to the extent permitted by law; without even the
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

# file(GLOB_RECURSE sources_Custom Custom/*.cpp Custom/*.h)

set(scripts_STAT_SRCS
  ${scripts_STAT_SRCS}
#  ${sources_Custom}
Custom/chat.cpp
Custom/changer.cpp
Custom/visual.cpp
Custom/GMisland_Theme.cpp
Custom/skills.cpp
Custom/toggle.cpp
Custom/phasing.cpp
Custom/anim.cpp
Custom/refresh.cpp
Custom/misc.cpp
)

message("  -> Prepared: Custom")
