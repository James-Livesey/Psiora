#include "mainwindow.h"
#include <QApplication>
#include <QCommandLineParser>
#include "emucore.h"
#include "global.h"
#include <stdio.h>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QCommandLineParser parser;

    parser.setApplicationDescription("Cross Platform - Psion Organiser II Emulator");
    parser.addHelpOption();

    QCommandLineOption romFileOption(
        {"r", "rom-file"},
        "Path to ROM file to boot",
        "file"
    );

    QCommandLineOption pakBFileOption(
        {"b", "pak-b-file"},
        "Path to OPK file to use for the slot B datapack",
        "file"
    );

    QCommandLineOption pakCFileOption(
        {"c", "pak-c-file"},
        "Path to OPK file to use for the slot C datapack",
        "file"
    );

    parser.addOption(romFileOption);
    parser.addOption(pakBFileOption);
    parser.addOption(pakCFileOption);

    parser.process(app);

    MainWindow mainWin;
    mainWin.show();

    emucore = new EmuCore(mainWin.getDrawingArea());
    emucore->startCore();

    QString romFile = parser.value(romFileOption);
    QString pakBFile = parser.value(pakBFileOption);
    QString pakCFile = parser.value(pakCFileOption);

    if (!romFile.isEmpty() || !pakBFile.isEmpty() || !pakCFile.isEmpty()) {
        if (!romFile.isEmpty()) emucore->load(romFile.toStdString());
        if (!pakBFile.isEmpty()) emucore->insertPak(1, pakBFile.toStdString());
        if (!pakCFile.isEmpty()) emucore->insertPak(0, pakCFile.toStdString());

        emucore->setPower(true);
    }

    app.exec();

    emucore->stopCore();
    delete emucore;

    return 0;
}
