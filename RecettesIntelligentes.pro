QT       += core gui sql \
    quick
QT += testlib sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Controller/ajouteringredientdialog.cpp \
    Controller/ajouterinstructiondialog.cpp \
    Controller/ajouterrecettedialog.cpp \
    models/ServiceLayer/backend.cpp \
    data/databasemanager.cpp \
    Controller/imagedroplabel.cpp \
    models/ingredient.cpp \
    data/ingredientDAO.cpp \
    models/ingredientmodel.cpp \
    models/ServiceLayer/ingredientservice.cpp \
    models/instruction.cpp \
    data/instructionDAO.cpp \
    models/instructioncomposee.cpp \
    models/ServiceLayer/instructionservice.cpp \
    models/instructionsimple.cpp \
    models/instructiontreemodel.cpp \
    main.cpp \
    Controller/mainwindow.cpp \
    models/recette.cpp \
    data/recetteDAO.cpp \
    models/recetteingredient.cpp \
    data/recetteingredientdao.cpp \
    models/recetteingredientmodel.cpp \
    models/recettemodel.cpp \
    models/ServiceLayer/recetteservice.cpp \
    models/unite.cpp

HEADERS += \
    ControllerHeader/ajouteringredientdialog.h \
    ControllerHeader/ajouterinstructiondialog.h \
    ControllerHeader/ajouterrecettedialog.h \
    modelsHeader/ServiceLayerHeader/backend.h \
    dataHeader/databasemanager.h \
    ControllerHeader/imagedroplabel.h \
    modelsHeader/ingredient.h \
    dataHeader/ingredientDAO.h \
    modelsHeader/ingredientmodel.h \
    modelsHeader/ServiceLayerHeader/ingredientservice.h \
    modelsHeader/instruction.h \
    dataHeader/instructionDAO.h \
    modelsHeader/instructioncomposee.h \
    modelsHeader/ServiceLayerHeader/instructionservice.h \
    modelsHeader/instructionsimple.h \
    modelsHeader/instructiontreemodel.h \
    ControllerHeader/mainwindow.h \
    modelsHeader/recette.h \
    dataHeader/recetteDAO.h \
    modelsHeader/recetteingredient.h \
    dataHeader/recetteingredientdao.h \
    modelsHeader/recetteingredientmodel.h \
    modelsHeader/recettemodel.h \
    modelsHeader/ServiceLayerHeader/recetteservice.h \
    modelsHeader/unite.h

FORMS += \
    RecetteDetailDialog.ui \
    ajouteringredientdialog.ui \
    ajouterinstructiondialog.ui \
    ajouterrecettedialog.ui \
    mainwindow.ui
RESOURCES += \
    StyleSheet/style.qss \
    resource.qrc


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
