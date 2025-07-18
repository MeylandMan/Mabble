file(READ "${CMAKE_SOURCE_DIR}/mabble.json" _mabble_json)

string(REGEX MATCH "\"name\"[ \t]*:[ \t]*\"([^\"]+)\"" _name_match "${_mabble_json}")
set(MABBLE_PROJECT_NAME "${CMAKE_MATCH_1}")

string(REGEX MATCH "\"major\"[ \t]*:[ \t]*([0-9]+)" _major_match "${_mabble_json}")
set(_major "${CMAKE_MATCH_1}")

string(REGEX MATCH "\"minor\"[ \t]*:[ \t]*([0-9]+)" _minor_match "${_mabble_json}")
set(_minor "${CMAKE_MATCH_1}")

string(REGEX MATCH "\"patch\"[ \t]*:[ \t]*([0-9]+)" _patch_match "${_mabble_json}")
set(_patch "${CMAKE_MATCH_1}")

set(MABBLE_VERSION "${_major}.${_minor}.${_patch}")