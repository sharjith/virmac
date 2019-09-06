TEMPLATE	= app
LANGUAGE	= C++

QT += core widgets opengl printsupport

CONFIG	+= opengl

HEADERS	+= \
	GCodeException.h \
	ListIteratorOfListOfCTriFacet.h \
	ListIteratorOfListOfNCBlock.h \
	ListNodeOfCTriFacet.h \
	ListNodeOfNCBlock.h \
	ListOfCTriFacet.h \
	ListOfNCBlock.h \
	MillCutter.h \
	NCBlock.h \
	TriFacet.h \
    AboutDialog.h \
    ToolLibrary.h \
    SimulSettings.h \
    RotAxisSetting.h \
    BlockEntry.h \
    MatlEditor.h \
    GridSettings.h \
    Transformations.h \
    SimulReport.h \
    CircEntryPara.h \
    RetractPara.h \
    MainWindow.h \
    VStLObject.h \
    VStLReader.h \
    VToolPath.h \
    VToolTrail.h \
    VGLDisplayContext.h \
    VirmacViewer.h \
    VToolViewer.h \
    BackgroundColor.h \
    VirmacMainWin.h \
    VirmacDocument.h \
    VirmacGLView.h \
    ToolDefinition.h

SOURCES	+= \
	ListIteratorOfListOfCTriFacet.cpp \
	ListIteratorOfListOfNCBlock.cpp \
	ListNodeOfCTriFacet.cpp \
	ListNodeOfNCBlock.cpp \
	ListOfCTriFacet.cpp \
	ListOfNCBlock.cpp \
	main.cpp \
	MillCutter.cpp \
	NCBlock.cpp \
	triangle_triangle_intersection.cpp \
    AboutDialog.cpp \
    ToolLibrary.cpp \
    SimulSettings.cpp \
    RotAxisSetting.cpp \
    BlockEntry.cpp \
    MatlEditor.cpp \
    GridSettings.cpp \
    Transformations.cpp \
    SimulReport.cpp \
    CircEntryPara.cpp \
    RetractPara.cpp \
    MainWindow.cpp \
    VStLObject.cpp \
    VStLReader.cpp \
    VToolPath.cpp \
    VToolTrail.cpp \
    VGLDisplayContext.cpp \
    VirmacViewer.cpp \
    VToolViewer.cpp \
    BackgroundColor.cpp \
    VirmacMainWin.cpp \
    VirmacDocument.cpp \
    VirmacGLView.cpp \
    ToolDefinition.cpp

FORMS	= BlockEntry.ui \
	CircEntryPara.ui \
	GCodeEditor.ui \
	GridSettings.ui \
	MatlEditor.ui \
	RetractPara.ui \
	RotAxisSetting.ui \
	SimulReport.ui \
	SimulSettings.ui \
	Splash.ui \
	ToolLibrary.ui \
	Transformations.ui \
    AboutDialog.ui \
    MainWindow.ui \
    BackgroundColor.ui \
    ToolDefinition.ui


win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../VKernel/VKGeom/release/ -lVKGeom
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../VKernel/VKGeom/debug/ -lVKGeom
else:unix: LIBS += -L$$OUT_PWD/../VKernel/VKGeom/ -lVKGeom

INCLUDEPATH += $$PWD/../VKernel/VKGeom
DEPENDPATH += $$PWD/../VKernel/VKGeom

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../VKernel/VKGraphic/release/ -lVKGraphic
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../VKernel/VKGraphic/debug/ -lVKGraphic
else:unix: LIBS += -L$$OUT_PWD/../VKernel/VKGraphic/ -lVKGraphic

INCLUDEPATH += $$PWD/../VKernel/VKGraphic
DEPENDPATH += $$PWD/../VKernel/VKGraphic

RESOURCES += \
    Virmac.qrc

mac: LIBS += -framework OpenGL
else:unix: LIBS += -lGL -lGLU
else:win32: LIBS += -lopengl32 -lglu32

win32{
    RC_FILE = Virmac.rc
}

mac{
    QMAKE_INFO_PLIST = Info.plist
    ICON = appicon.icns
}


QMAKE_MAC_SDK = macosx10.12
