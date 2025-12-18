QT       += core gui sql \
    quick

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    databasemanager.cpp \
    ingredient.cpp \
    ingredientDAO.cpp \
    ingredientservice.cpp \
    instruction.cpp \
    instructionDAO.cpp \
    instructioncomposee.cpp \
    instructionservice.cpp \
    instructionsimple.cpp \
    main.cpp \
    mainwindow.cpp \
    recette.cpp \
    recetteDAO.cpp \
    recetteingredient.cpp \
    recetteingredientdao.cpp \
    recetteservice.cpp \
    test.cpp \
    unite.cpp

HEADERS += \
    databasemanager.h \
    ingredient.h \
    ingredientDAO.h \
    ingredientservice.h \
    instruction.h \
    instructionDAO.h \
    instructioncomposee.h \
    instructionservice.h \
    instructionsimple.h \
    mainwindow.h \
    recette.h \
    recetteDAO.h \
    recetteingredient.h \
    recetteingredientdao.h \
    recetteservice.h \
    unite.h

FORMS += \
    RecetteDetailDialog.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
