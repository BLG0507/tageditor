#ifndef TAGEDITORMAINWINDOW_H
#define TAGEDITORMAINWINDOW_H

#include "./filefilterproxymodel.h"
#include "./previousvaluehandling.h"

#include <tagparser/mediafileinfo.h>
#include <tagparser/tagvalue.h>

#include <QMainWindow>
#include <QByteArray>

#include <mutex>

QT_FORWARD_DECLARE_CLASS(QFileSystemModel)
QT_FORWARD_DECLARE_CLASS(QItemSelectionModel)

namespace Media {
DECLARE_ENUM(TagType, unsigned int)
}

namespace Dialogs {
class AboutDialog;
class SettingsDialog;
}

namespace QtGui {

namespace Ui {
class MainWindow;
}

class TagEditorWidget;
class RenameFilesDialog;

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = nullptr);
    virtual ~MainWindow();

    // file browser
    QString currentDirectory();
    void setCurrentDirectory(const QString &path);
    void startParsing(const QString &path);

protected:
    bool event(QEvent *event);

private slots:
    // file selection
    void pathEntered();
    void fileSelected();
    void selectNextFile();
    void selectNextFile(QItemSelectionModel *selectionModel, const QModelIndex &currentIndex, bool notDeeper);
    void showNextFileNotFound();
    void showOpenFileDlg();
    void saveFileInformation();
    void handleFileStatusChange(bool opened, bool hasTag);
    void handleFileSaved(const QString &currentPath);

    // settings
    void showSettingsDlg();
    void applySettingsFromDialog();

    // misc
    void showAboutDlg();
    void showRenameFilesDlg();
    void spawnExternalPlayer();

private:
    std::mutex &fileOperationMutex();
    Media::MediaFileInfo &fileInfo();

    // UI
    std::unique_ptr<Ui::MainWindow> m_ui;
    // models
    QFileSystemModel *m_fileModel;
    FileFilterProxyModel *m_fileFilterModel;
    // dialogs
    Dialogs::AboutDialog *m_aboutDlg;
    Dialogs::SettingsDialog *m_settingsDlg;
    std::unique_ptr<RenameFilesDialog> m_renameFilesDlg;
};

}

#endif // TAGEDITORMAINWINDOW_H
