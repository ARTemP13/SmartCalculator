QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    creditcalc.cpp \
    diff_calc_table.cpp \
    graphics.cpp \
    main.cpp \
    mainwindow.cpp rpn.c parsing.c calculating.c \
    qcustomplot.cpp

HEADERS += \
    creditcalc.h \
    diff_calc_table.h \
    graphics.h \
    mainwindow.h smartcalc.h \
    qcustomplot.h

FORMS += \
    creditcalc.ui \
    diff_calc_table.ui \
    graphics.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
