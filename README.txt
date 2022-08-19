In order to run this game set C++ version settings to version 17.

After that, enter this path:
debug-> debug properties-> C/C++ -> preprocessor -> preprocessor defenition-> Edit (התחילו משמאל לימין)

Add the rows below:
WIN32
_DEBUG
_CONSOLE
_HAS_STD_BYTE=0
_SILENCE_CXX17_C_HEADER_DEPRECATION_WARNING
