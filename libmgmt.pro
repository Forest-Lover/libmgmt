#-------------------------------------------------
#
# Project created by QtCreator 2017-04-21T15:59:58
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = libmgmt
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        mainwindow.cpp \
    dialog_purchase.cpp \
    dialog_login.cpp \
    dialog_borrow.cpp \
    dialog_return.cpp \
    dialog_log.cpp \
    dialog_inquiry.cpp \
    book.cpp \
    reader.cpp \
    global.cpp \
    dialog_reader_info.cpp \
    dialog_book_info.cpp \
    dialog_addreader.cpp \
    dialog_help.cpp

HEADERS  += mainwindow.h \
    dialog_purchase.h \
    dialog_login.h \
    dialog_borrow.h \
    dialog_return.h \
    dialog_log.h \
    dialog_inquiry.h \
    book.h \
    reader.h \
    common.h \
    global.h \
    dialog_reader_info.h \
    dialog_book_info.h \
    dialog_addreader.h \
    dialog_help.h

FORMS    += mainwindow.ui \
    dialog_purchase.ui \
    dialog_borrow.ui \
    dialog_return.ui \
    dialog_login.ui \
    dialog_log.ui \
    dialog_inquiry.ui \
    dialog_reader_info.ui \
    dialog_book_info.ui \
    dialog_addreader.ui \
    dialog_help.ui
