#include "MainWindow.h"
#include "TextEditor.h"
#include "AboutDialog.h"
#include "PreferencesDialog.h"
#include <QApplication>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <QCloseEvent>
#include <QSettings>
#include <QStandardPaths>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , textEditor(nullptr)
    , splitter(nullptr)
    , fileListWidget(nullptr)
    , settings(nullptr)
{
    // Initialize settings
    settings = new QSettings(this);
    
    // Create UI components
    createCentralWidget();
    createActions();
    createMenus();
    createToolBars();
    createStatusBar();
    
    // Connect text editor signals
    connect(textEditor, &TextEditor::textChanged, this, &MainWindow::documentModified);
    connect(textEditor, &TextEditor::cursorPositionChanged, this, &MainWindow::updateStatusBar);
    
    // Set window properties
    setWindowTitle("Qt Learning Application");
    setMinimumSize(800, 600);
    
    // Read settings
    readSettings();
    
    // Update status bar
    updateStatusBar();
}

MainWindow::~MainWindow()
{
    writeSettings();
}

void MainWindow::createCentralWidget()
{
    // Create splitter for main layout
    splitter = new QSplitter(Qt::Horizontal, this);
    
    // Create file list widget
    fileListWidget = new QListWidget;
    fileListWidget->setMaximumWidth(200);
    fileListWidget->setMinimumWidth(150);
    
    // Add some sample items to the file list
    fileListWidget->addItem("Welcome.txt");
    fileListWidget->addItem("Example.txt");
    fileListWidget->addItem("Notes.txt");
    
    // Create text editor
    textEditor = new TextEditor;
    
    // Add widgets to splitter
    splitter->addWidget(fileListWidget);
    splitter->addWidget(textEditor);
    
    // Set splitter proportions
    splitter->setStretchFactor(0, 0);
    splitter->setStretchFactor(1, 1);
    
    setCentralWidget(splitter);
}

void MainWindow::createActions()
{
    // File actions
    newAction = new QAction(QIcon(":/icons/new.png"), "&New", this);
    newAction->setShortcuts(QKeySequence::New);
    newAction->setStatusTip("Create a new file");
    connect(newAction, &QAction::triggered, this, &MainWindow::newFile);

    openAction = new QAction(QIcon(":/icons/open.png"), "&Open...", this);
    openAction->setShortcuts(QKeySequence::Open);
    openAction->setStatusTip("Open an existing file");
    connect(openAction, &QAction::triggered, this, &MainWindow::openFile);

    saveAction = new QAction(QIcon(":/icons/save.png"), "&Save", this);
    saveAction->setShortcuts(QKeySequence::Save);
    saveAction->setStatusTip("Save the document to disk");
    connect(saveAction, &QAction::triggered, this, &MainWindow::saveFile);

    saveAsAction = new QAction("Save &As...", this);
    saveAsAction->setShortcuts(QKeySequence::SaveAs);
    saveAsAction->setStatusTip("Save the document under a new name");
    connect(saveAsAction, &QAction::triggered, this, &MainWindow::saveAsFile);

    exitAction = new QAction("E&xit", this);
    exitAction->setShortcuts(QKeySequence::Quit);
    exitAction->setStatusTip("Exit the application");
    connect(exitAction, &QAction::triggered, this, &MainWindow::exit);

    // Edit actions
    undoAction = new QAction(QIcon(":/icons/undo.png"), "&Undo", this);
    undoAction->setShortcuts(QKeySequence::Undo);
    undoAction->setStatusTip("Undo the last operation");
    connect(undoAction, &QAction::triggered, textEditor, &QTextEdit::undo);

    redoAction = new QAction(QIcon(":/icons/redo.png"), "&Redo", this);
    redoAction->setShortcuts(QKeySequence::Redo);
    redoAction->setStatusTip("Redo the last operation");
    connect(redoAction, &QAction::triggered, textEditor, &QTextEdit::redo);

    cutAction = new QAction(QIcon(":/icons/cut.png"), "Cu&t", this);
    cutAction->setShortcuts(QKeySequence::Cut);
    cutAction->setStatusTip("Cut the current selection's contents to the clipboard");
    connect(cutAction, &QAction::triggered, textEditor, &QTextEdit::cut);

    copyAction = new QAction(QIcon(":/icons/copy.png"), "&Copy", this);
    copyAction->setShortcuts(QKeySequence::Copy);
    copyAction->setStatusTip("Copy the current selection's contents to the clipboard");
    connect(copyAction, &QAction::triggered, textEditor, &QTextEdit::copy);

    pasteAction = new QAction(QIcon(":/icons/paste.png"), "&Paste", this);
    pasteAction->setShortcuts(QKeySequence::Paste);
    pasteAction->setStatusTip("Paste the clipboard's contents into the current selection");
    connect(pasteAction, &QAction::triggered, textEditor, &QTextEdit::paste);

    selectAllAction = new QAction("Select &All", this);
    selectAllAction->setShortcuts(QKeySequence::SelectAll);
    selectAllAction->setStatusTip("Select all text");
    connect(selectAllAction, &QAction::triggered, textEditor, &QTextEdit::selectAll);

    findAction = new QAction("&Find...", this);
    findAction->setShortcuts(QKeySequence::Find);
    findAction->setStatusTip("Find text");
    connect(findAction, &QAction::triggered, this, &MainWindow::find);

    replaceAction = new QAction("&Replace...", this);
    replaceAction->setShortcuts(QKeySequence::Replace);
    replaceAction->setStatusTip("Replace text");
    connect(replaceAction, &QAction::triggered, this, &MainWindow::replace);

    // View actions
    preferencesAction = new QAction("&Preferences...", this);
    preferencesAction->setStatusTip("Configure application preferences");
    connect(preferencesAction, &QAction::triggered, this, &MainWindow::showPreferences);

    // Help actions
    aboutAction = new QAction("&About", this);
    aboutAction->setStatusTip("Show the application's About box");
    connect(aboutAction, &QAction::triggered, this, &MainWindow::showAbout);

    aboutQtAction = new QAction("About &Qt", this);
    aboutQtAction->setStatusTip("Show the Qt library's About box");
    connect(aboutQtAction, &QAction::triggered, this, &MainWindow::showAboutQt);
}

void MainWindow::createMenus()
{
    // File menu
    fileMenu = menuBar()->addMenu("&File");
    fileMenu->addAction(newAction);
    fileMenu->addAction(openAction);
    fileMenu->addAction(saveAction);
    fileMenu->addAction(saveAsAction);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAction);

    // Edit menu
    editMenu = menuBar()->addMenu("&Edit");
    editMenu->addAction(undoAction);
    editMenu->addAction(redoAction);
    editMenu->addSeparator();
    editMenu->addAction(cutAction);
    editMenu->addAction(copyAction);
    editMenu->addAction(pasteAction);
    editMenu->addAction(selectAllAction);
    editMenu->addSeparator();
    editMenu->addAction(findAction);
    editMenu->addAction(replaceAction);

    // View menu
    viewMenu = menuBar()->addMenu("&View");
    viewMenu->addAction(preferencesAction);

    // Help menu
    helpMenu = menuBar()->addMenu("&Help");
    helpMenu->addAction(aboutAction);
    helpMenu->addAction(aboutQtAction);
}

void MainWindow::createToolBars()
{
    // File toolbar
    fileToolBar = addToolBar("File");
    fileToolBar->addAction(newAction);
    fileToolBar->addAction(openAction);
    fileToolBar->addAction(saveAction);

    // Edit toolbar
    editToolBar = addToolBar("Edit");
    editToolBar->addAction(undoAction);
    editToolBar->addAction(redoAction);
    editToolBar->addSeparator();
    editToolBar->addAction(cutAction);
    editToolBar->addAction(copyAction);
    editToolBar->addAction(pasteAction);
}

void MainWindow::createStatusBar()
{
    locationLabel = new QLabel("Line 1, Column 1");
    locationLabel->setAlignment(Qt::AlignHCenter);
    locationLabel->setMinimumSize(locationLabel->sizeHint());

    sizeLabel = new QLabel("0 characters");
    sizeLabel->setAlignment(Qt::AlignHCenter);
    sizeLabel->setMinimumSize(sizeLabel->sizeHint());

    statusBar()->addWidget(locationLabel);
    statusBar()->addPermanentWidget(sizeLabel);
    statusBar()->showMessage("Ready", 2000);
}

void MainWindow::newFile()
{
    if (saveChanges()) {
        textEditor->clear();
        setCurrentFile("");
    }
}

void MainWindow::openFile()
{
    if (saveChanges()) {
        QString fileName = QFileDialog::getOpenFileName(this,
                                                        "Open File",
                                                        QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation),
                                                        "Text Files (*.txt);;All Files (*)");
        if (!fileName.isEmpty()) {
            QFile file(fileName);
            if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
                QTextStream in(&file);
                textEditor->setPlainText(in.readAll());
                setCurrentFile(fileName);
                statusBar()->showMessage("File loaded", 2000);
            } else {
                QMessageBox::warning(this, "Qt Learning Application",
                                    QString("Cannot read file %1:\n%2.")
                                    .arg(fileName)
                                    .arg(file.errorString()));
            }
        }
    }
}

void MainWindow::saveFile()
{
    if (currentFile.isEmpty()) {
        saveAsFile();
    } else {
        QFile file(currentFile);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream out(&file);
            out << textEditor->toPlainText();
            textEditor->document()->setModified(false);
            statusBar()->showMessage("File saved", 2000);
        } else {
            QMessageBox::warning(this, "Qt Learning Application",
                                QString("Cannot write file %1:\n%2.")
                                .arg(currentFile)
                                .arg(file.errorString()));
        }
    }
}

void MainWindow::saveAsFile()
{
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    "Save File",
                                                    QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation),
                                                    "Text Files (*.txt);;All Files (*)");
    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream out(&file);
            out << textEditor->toPlainText();
            setCurrentFile(fileName);
            textEditor->document()->setModified(false);
            statusBar()->showMessage("File saved", 2000);
        } else {
            QMessageBox::warning(this, "Qt Learning Application",
                                QString("Cannot write file %1:\n%2.")
                                .arg(fileName)
                                .arg(file.errorString()));
        }
    }
}

void MainWindow::exit()
{
    if (saveChanges()) {
        qApp->quit();
    }
}

void MainWindow::undo()
{
    textEditor->undo();
}

void MainWindow::redo()
{
    textEditor->redo();
}

void MainWindow::cut()
{
    textEditor->cut();
}

void MainWindow::copy()
{
    textEditor->copy();
}

void MainWindow::paste()
{
    textEditor->paste();
}

void MainWindow::selectAll()
{
    textEditor->selectAll();
}

void MainWindow::find()
{
    // Placeholder for find dialog
    QMessageBox::information(this, "Find", "Find functionality would be implemented here.");
}

void MainWindow::replace()
{
    // Placeholder for replace dialog
    QMessageBox::information(this, "Replace", "Replace functionality would be implemented here.");
}

void MainWindow::showPreferences()
{
    PreferencesDialog dialog(this);
    dialog.exec();
}

void MainWindow::showAbout()
{
    AboutDialog dialog(this);
    dialog.exec();
}

void MainWindow::showAboutQt()
{
    QMessageBox::aboutQt(this, "About Qt");
}

void MainWindow::documentModified()
{
    setWindowModified(textEditor->document()->isModified());
    updateStatusBar();
}

void MainWindow::updateStatusBar()
{
    QTextCursor cursor = textEditor->textCursor();
    int line = cursor.blockNumber() + 1;
    int column = cursor.columnNumber() + 1;
    locationLabel->setText(QString("Line %1, Column %2").arg(line).arg(column));
    
    int characters = textEditor->toPlainText().length();
    sizeLabel->setText(QString("%1 characters").arg(characters));
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if (saveChanges()) {
        writeSettings();
        event->accept();
    } else {
        event->ignore();
    }
}

void MainWindow::readSettings()
{
    QByteArray geometry = settings->value("geometry").toByteArray();
    if (geometry.isEmpty()) {
        resize(1000, 700);
        move(100, 100);
    } else {
        restoreGeometry(geometry);
    }
    
    QByteArray state = settings->value("windowState").toByteArray();
    if (!state.isEmpty()) {
        restoreState(state);
    }
}

void MainWindow::writeSettings()
{
    settings->setValue("geometry", saveGeometry());
    settings->setValue("windowState", saveState());
}

bool MainWindow::saveChanges()
{
    if (textEditor->document()->isModified()) {
        QMessageBox::StandardButton ret;
        ret = QMessageBox::warning(this, "Qt Learning Application",
                                 "The document has been modified.\n"
                                 "Do you want to save your changes?",
                                 QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        if (ret == QMessageBox::Save)
            return saveFile(), true;
        else if (ret == QMessageBox::Cancel)
            return false;
    }
    return true;
}

void MainWindow::setCurrentFile(const QString &fileName)
{
    currentFile = fileName;
    textEditor->document()->setModified(false);
    setWindowModified(false);

    QString shownName = currentFile;
    if (currentFile.isEmpty())
        shownName = "untitled.txt";
    setWindowFilePath(shownName);
}

QString MainWindow::strippedName(const QString &fullFileName)
{
    return QFileInfo(fullFileName).fileName();
}