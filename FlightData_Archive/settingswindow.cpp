#include "settingswindow.h"
#include <settings.h>

void SettingsWindow::settingsToWindow(GenSet _s)
{
    emit textChanged(_s.dataBasePath);
    emit textChangedpath(_s.dbFile);
}

void SettingsWindow::openDir()
{

    //QString res = QFileDialog::getExistingDirectory( this, trUtf8("Выбрать директорию с данными"), trUtf8("Директории"), QFileDialog::ShowDirsOnly );
    //if (!res.isEmpty())
    {
        //emit textChanged(res);
    }
}

void SettingsWindow::openDirDB()
{

    //QString res = QFileDialog::getOpenFileName( this, trUtf8("Выбрать файл с данными"), trUtf8("Базы данных"), "*.db" );
    //if (!res.isEmpty())
    {
        //emit textChangedDB(res);
    }
}

void SettingsWindow::saveSettings(QString _s, QString _s_dbFile)
{
    GenSet structs;
    structs = getValue();
    structs.dataBasePath = _s;
    structs.dbFile = _s_dbFile;
    setValue(structs);
    writeAll();
}


void SettingsWindow::openButtonSets(int n)
{
    emit winEnabled(false);

    ew.setEdit((WhoEdit)n);
    ew.text();
    ew.showE(); 
    return;
}

void SettingsWindow::slotWinEnabled()
{
    emit winEnabled(true);
}

