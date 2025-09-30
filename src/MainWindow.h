#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include <QMenuBar>
#include <QToolBar>
#include <QStatusBar>
#include <QLabel>
#include <QAction>
#include <QFileDialog>
#include <QMessageBox>
#include <QCloseEvent>
#include <QSettings>
#include <QSplitter>
#include <QListWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QWidget>

class TextEditor;
class AboutDialog;
class PreferencesDialog;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void closeEvent(QCloseEvent *event) override;

private slots:
    void newFile();
    void openFile();
    void saveFile();
    void saveAsFile();
    void exit();
    void undo();
    void redo();
    void cut();
    void copy();
    void paste();
    void selectAll();
    void find();
    void replace();
    void showPreferences();
    void showAbout();
    void showAboutQt();
    void documentModified();
    void updateStatusBar();

private:
    void createActions();
    void createMenus();
    void createToolBars();
    void createStatusBar();
    void createCentralWidget();
    void readSettings();
    void writeSettings();
    bool saveChanges();
    void setCurrentFile(const QString &fileName);
    QString strippedName(const QString &fullFileName);

    // UI Components
    TextEditor *textEditor;
    QSplitter *splitter;
    QListWidget *fileListWidget;
    
    // Menus
    QMenu *fileMenu;
    QMenu *editMenu;
    QMenu *viewMenu;
    QMenu *helpMenu;
    
    // Toolbar
    QToolBar *fileToolBar;
    QToolBar *editToolBar;
    
    // Status bar
    QLabel *locationLabel;
    QLabel *sizeLabel;
    
    // Actions
    QAction *newAction;
    QAction *openAction;
    QAction *saveAction;
    QAction *saveAsAction;
    QAction *exitAction;
    QAction *undoAction;
    QAction *redoAction;
    QAction *cutAction;
    QAction *copyAction;
    QAction *pasteAction;
    QAction *selectAllAction;
    QAction *findAction;
    QAction *replaceAction;
    QAction *preferencesAction;
    QAction *aboutAction;
    QAction *aboutQtAction;
    
    QString currentFile;
    QSettings *settings;
};

#endif // MAINWINDOW_H