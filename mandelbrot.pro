defineReplace(toWinSlashes) {
    1 ~= s,/,\\,g
    return($$quote($$1))
}

defineTest(post_copy_files) {
    DESTINATION_DIR = $${2}
    SOURCE_FILES = $${1}
    !exists($$DESTINATION_DIR) {
        return(false)
    }
    for(NEXT_FILE, SOURCE_FILES) {
        exists($$NEXT_FILE) {
            message (next file $$NEXT_FILE)
            !win* {
                QMAKE_POST_LINK += $${QMAKE_COPY} $${NEXT_FILE} $${DESTINATION_DIR}
            } else {
                FROM = $$toWinSlashes($${NEXT_FILE})
                TO = $$toWinSlashes($${DESTINATION_DIR})
                win*:QMAKE_POST_LINK += $${QMAKE_COPY} $${FROM} $${TO}$$escape_expand(\\n\\t)
            }
            message(postLinkAdded)
        }
    }

    export(QMAKE_POST_LINK)
    return(true)
}

DESTDIR += $$PWD/bin

HEADERS       = mandelbrotwidget.h \
                thread.h \
                computingthread.h \
                sigslot.h
SOURCES       = main.cpp \
                mandelbrotwidget.cpp \
                thread.cpp \
                computingthread.cpp

DEFINES += QT_NO_KEYWORDS


win*{
    INCLUDEPATH += $$PWD/Pthreads/include
    LIBS += $$PWD/Pthreads/pthreadVC2.lib
    post_copy_files($$PWD/Pthreads/pthreadVC2.dll, $$DESTDIR)
}

MOC_DIR += tmps
OBJECTS_DIR += tmps
UI_DIR += tmps

unix:!mac:!symbian:!vxworks:!integrity:LIBS += -lm
