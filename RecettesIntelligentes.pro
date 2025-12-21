QT       += core gui sql \
    quick
QT += testlib sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
CONFIG += lrelease
CONFIG += embed_translations
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    dialog/ajouteringredientdialog.cpp \
    dialog/ajouterinstructiondialog.cpp \
    dialog/ajouterrecettedialog.cpp \
    backend.cpp \
    data/databasemanager.cpp \
    data/initialdata.cpp \
    imagedroplabel.cpp \
    metiers/ingredient.cpp \
    dao/ingredientDAO.cpp \
    models/ingredientmodel.cpp \
    service/ingredientservice.cpp \
    metiers/instruction.cpp \
    dao/instructionDAO.cpp \
    metiers/instructioncomposee.cpp \
    service/instructionservice.cpp \
    metiers/instructionsimple.cpp \
    models/instructiontreemodel.cpp \
    main.cpp \
    mainwindow.cpp \
    metiers/recette.cpp \
    dao/recetteDAO.cpp \
    metiers/recetteingredient.cpp \
    dao/recetteingredientdao.cpp \
    models/recetteingredientmodel.cpp \
    models/recettemodel.cpp \
    service/recetteservice.cpp \
    test.cpp \
    metiers/unite.cpp

HEADERS += \
    dialogHeader/ajouteringredientdialog.h \
    dialogHeader/ajouterinstructiondialog.h \
    dialogHeader/ajouterrecettedialog.h \
    backend.h \
    dataHeader/databasemanager.h \
    dataHeader/initialdata.h \
    imagedroplabel.h \
    metiersHeader/ingredient.h \
    daoHeader/ingredientDAO.h \
    modelsHeader/ingredientmodel.h \
    serviceHeader/ingredientservice.h \
    metiersHeader/instruction.h \
    daoHeader/instructionDAO.h \
    metiersHeader/instructioncomposee.h \
    serviceHeader/instructionservice.h \
    metiersHeader/instructionsimple.h \
    modelsHeader/instructiontreemodel.h \
    mainwindow.h \
    metiersHeader/recette.h \
    daoHeader/recetteDAO.h \
    metiersHeader/recetteingredient.h \
    daoHeader/recetteingredientdao.h \
    modelsHeader/recetteingredientmodel.h \
    modelsHeader/recettemodel.h \
    serviceHeader/recetteservice.h \
    metiersHeader/unite.h

FORMS += \
    RecetteDetailDialog.ui \
    ajouteringredientdialog.ui \
    ajouterinstructiondialog.ui \
    ajouterrecettedialog.ui \
    mainwindow.ui
RESOURCES += \
    resource.qrc \

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    StyleSheet/style.qss

TRANSLATIONS += \
    RecettesIntelligentes_en_AS.ts \
    RecettesIntelligentes_fr_FR.ts
