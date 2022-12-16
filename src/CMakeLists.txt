add_executable(ECalc main.cpp parser.cpp resources.qrc)
target_link_libraries(ECalc Qt5::Quick Qt5::Qml Qt5::Gui Qt5::QuickControls2 Qt5::Widgets KF5::Kirigami2 KF5::I18n)
#target_compile_definitions(ECalc PRIVATE QT_QML_DEBUG)
