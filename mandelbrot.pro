HEADERS       = mandelbrotwidget.h \
                thread.h \
                computingthread.h \
                sigslot.h
SOURCES       = main.cpp \
                mandelbrotwidget.cpp \
                thread.cpp \
                computingthread.cpp

DEFINES += QT_NO_KEYWORDS

unix:!mac:!symbian:!vxworks:!integrity:LIBS += -lm
