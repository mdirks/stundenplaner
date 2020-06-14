TEMPLATE = subdirs
CONFIG += build_all

android: {
    SUBDIRS += \
              app-qml\
              orm\
              datamodel
              #services
}

!android:{
    SUBDIRS += \
    app \
    app-qml \
    klfbackend \
    orm \
    datamodel \
    gui \
    orm/generator \
    orm/ormgui \
    services \
    main \
    tests

    main.depends= orm datamodel services klfbackend gui orm/ormgui
    tests.depends= orm datamodel services klfbackend gui
    app.depends= gui orm datamodel services klfbackend
    #gui.depends= orm datamodel services
    orm/generator.depends= orm

    INSTALLS += stundenplaner
}






