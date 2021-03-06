QT -= gui

CONFIG += c++11 console
CONFIG -= app_bundle

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        ../../lib/tinyxml2.cpp \
        GeneticAlgorithm.cpp \
        GeneticIndividual.cpp \
        GeneticPopulation.cpp \
        GeneticServer.cpp \
        main.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    ../../LinkedList/List.h \
    ../../LinkedList/Node.h \
    ../../lib/json.hpp \
    ../../lib/tinyxml2.h \
    GeneticAlgorithm.h \
    GeneticIndividual.h \
    GeneticPopulation.h \
    GeneticServer.h

INCLUDEPATH+=../../lib/