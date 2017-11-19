INCLUDEPATH += $$PWD/../../include
DEPENDPATH += $$PWD/../../include

#>>>--------------------------------------------------------------------------------------------------------------------------------------------
# SSDK

INCLUDEPATH += $$PWD/../../include/SSDK
DEPENDPATH += $$PWD/../../include/SSDK

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../lib/release/ -lSSDK
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../lib/debug/ -lSSDK
else:unix: LIBS += -L$$PWD/../../lib/debug/ -lSSDK

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../lib/release/libSSDK.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../lib/debug/libSSDK.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../lib/release/SSDK.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../lib/debug/SSDK.lib
else:unix: PRE_TARGETDEPS += $$PWD/../../lib/debug/libSSDK.a

#<<<--------------------------------------------------------------------------------------------------------------------------------------------

include(SSDKDependencies.pri)


