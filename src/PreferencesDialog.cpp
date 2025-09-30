#include "PreferencesDialog.h"
#include <QApplication>
#include <QMessageBox>

PreferencesDialog::PreferencesDialog(QWidget *parent)
    : QDialog(parent)
    , settings(new QSettings(this))
    , backgroundColor(Qt::white)
    , textColor(Qt::black)
{
    setupUI();
    loadSettings();
    setWindowTitle("Preferences");
    setFixedSize(500, 400);
}

void PreferencesDialog::setupUI()
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    
    // Create tab widget
    tabWidget = new QTabWidget;
    
    // General tab
    generalTab = new QWidget;
    QFormLayout *generalLayout = new QFormLayout(generalTab);
    
    authorLineEdit = new QLineEdit;
    authorLineEdit->setPlaceholderText("Enter your name");
    generalLayout->addRow("Author Name:", authorLineEdit);
    
    autoSaveCheckBox = new QCheckBox("Enable auto-save");
    generalLayout->addRow(autoSaveCheckBox);
    
    autoSaveIntervalSpinBox = new QSpinBox;
    autoSaveIntervalSpinBox->setRange(1, 60);
    autoSaveIntervalSpinBox->setSuffix(" minutes");
    autoSaveIntervalSpinBox->setValue(5);
    generalLayout->addRow("Auto-save interval:", autoSaveIntervalSpinBox);
    
    showStatusBarCheckBox = new QCheckBox("Show status bar");
    showStatusBarCheckBox->setChecked(true);
    generalLayout->addRow(showStatusBarCheckBox);
    
    showToolBarCheckBox = new QCheckBox("Show toolbar");
    showToolBarCheckBox->setChecked(true);
    generalLayout->addRow(showToolBarCheckBox);
    
    tabWidget->addTab(generalTab, "General");
    
    // Editor tab
    editorTab = new QWidget;
    QFormLayout *editorLayout = new QFormLayout(editorTab);
    
    // Font settings
    QGroupBox *fontGroup = new QGroupBox("Font Settings");
    QFormLayout *fontLayout = new QFormLayout(fontGroup);
    
    fontComboBox = new QFontComboBox;
    fontLayout->addRow("Font Family:", fontComboBox);
    
    fontSizeSpinBox = new QSpinBox;
    fontSizeSpinBox->setRange(8, 72);
    fontSizeSpinBox->setValue(11);
    fontLayout->addRow("Font Size:", fontSizeSpinBox);
    
    editorLayout->addRow(fontGroup);
    
    // Color settings
    QGroupBox *colorGroup = new QGroupBox("Color Settings");
    QFormLayout *colorLayout = new QFormLayout(colorGroup);
    
    backgroundColorButton = new QPushButton("Choose Background Color");
    backgroundColorButton->setStyleSheet("QPushButton { background-color: white; border: 1px solid gray; padding: 5px; }");
    connect(backgroundColorButton, &QPushButton::clicked, this, &PreferencesDialog::selectBackgroundColor);
    colorLayout->addRow("Background:", backgroundColorButton);
    
    textColorButton = new QPushButton("Choose Text Color");
    textColorButton->setStyleSheet("QPushButton { background-color: black; color: white; border: 1px solid gray; padding: 5px; }");
    connect(textColorButton, &QPushButton::clicked, this, &PreferencesDialog::selectTextColor);
    colorLayout->addRow("Text:", textColorButton);
    
    editorLayout->addRow(colorGroup);
    
    // Editor options
    QGroupBox *optionsGroup = new QGroupBox("Editor Options");
    QFormLayout *optionsLayout = new QFormLayout(optionsGroup);
    
    wordWrapCheckBox = new QCheckBox("Enable word wrap");
    wordWrapCheckBox->setChecked(true);
    optionsLayout->addRow(wordWrapCheckBox);
    
    lineNumbersCheckBox = new QCheckBox("Show line numbers");
    optionsLayout->addRow(lineNumbersCheckBox);
    
    tabSizeSpinBox = new QSpinBox;
    tabSizeSpinBox->setRange(2, 8);
    tabSizeSpinBox->setValue(4);
    optionsLayout->addRow("Tab Size:", tabSizeSpinBox);
    
    editorLayout->addRow(optionsGroup);
    
    tabWidget->addTab(editorTab, "Editor");
    
    // Buttons
    QHBoxLayout *buttonLayout = new QHBoxLayout;
    
    okButton = new QPushButton("OK");
    cancelButton = new QPushButton("Cancel");
    applyButton = new QPushButton("Apply");
    resetButton = new QPushButton("Reset");
    
    connect(okButton, &QPushButton::clicked, this, &QDialog::accept);
    connect(cancelButton, &QPushButton::clicked, this, &QDialog::reject);
    connect(applyButton, &QPushButton::clicked, this, &PreferencesDialog::applySettings);
    connect(resetButton, &QPushButton::clicked, this, &PreferencesDialog::resetSettings);
    
    buttonLayout->addWidget(resetButton);
    buttonLayout->addStretch();
    buttonLayout->addWidget(applyButton);
    buttonLayout->addWidget(cancelButton);
    buttonLayout->addWidget(okButton);
    
    // Main layout
    mainLayout->addWidget(tabWidget);
    mainLayout->addLayout(buttonLayout);
    
    // Connect auto-save checkbox to enable/disable interval spinbox
    connect(autoSaveCheckBox, &QCheckBox::toggled, autoSaveIntervalSpinBox, &QSpinBox::setEnabled);
    autoSaveIntervalSpinBox->setEnabled(autoSaveCheckBox->isChecked());
}

void PreferencesDialog::selectBackgroundColor()
{
    QColor color = QColorDialog::getColor(backgroundColor, this, "Select Background Color");
    if (color.isValid()) {
        backgroundColor = color;
        backgroundColorButton->setStyleSheet(
            QString("QPushButton { background-color: %1; border: 1px solid gray; padding: 5px; }")
            .arg(color.name()));
    }
}

void PreferencesDialog::selectTextColor()
{
    QColor color = QColorDialog::getColor(textColor, this, "Select Text Color");
    if (color.isValid()) {
        textColor = color;
        textColorButton->setStyleSheet(
            QString("QPushButton { background-color: %1; border: 1px solid gray; padding: 5px; }")
            .arg(color.name()));
    }
}

void PreferencesDialog::applySettings()
{
    saveSettings();
    QMessageBox::information(this, "Preferences", "Settings applied successfully!\n"
                            "Some changes may require restarting the application.");
}

void PreferencesDialog::resetSettings()
{
    int ret = QMessageBox::question(this, "Reset Settings",
                                   "Are you sure you want to reset all settings to default values?",
                                   QMessageBox::Yes | QMessageBox::No);
    if (ret == QMessageBox::Yes) {
        // Reset to default values
        authorLineEdit->clear();
        autoSaveCheckBox->setChecked(false);
        autoSaveIntervalSpinBox->setValue(5);
        showStatusBarCheckBox->setChecked(true);
        showToolBarCheckBox->setChecked(true);
        
        fontComboBox->setCurrentFont(QFont("Arial"));
        fontSizeSpinBox->setValue(11);
        backgroundColor = Qt::white;
        textColor = Qt::black;
        backgroundColorButton->setStyleSheet("QPushButton { background-color: white; border: 1px solid gray; padding: 5px; }");
        textColorButton->setStyleSheet("QPushButton { background-color: black; color: white; border: 1px solid gray; padding: 5px; }");
        
        wordWrapCheckBox->setChecked(true);
        lineNumbersCheckBox->setChecked(false);
        tabSizeSpinBox->setValue(4);
        
        QMessageBox::information(this, "Reset Settings", "Settings have been reset to default values.");
    }
}

void PreferencesDialog::loadSettings()
{
    // Load general settings
    authorLineEdit->setText(settings->value("general/author", "").toString());
    autoSaveCheckBox->setChecked(settings->value("general/autoSave", false).toBool());
    autoSaveIntervalSpinBox->setValue(settings->value("general/autoSaveInterval", 5).toInt());
    showStatusBarCheckBox->setChecked(settings->value("general/showStatusBar", true).toBool());
    showToolBarCheckBox->setChecked(settings->value("general/showToolBar", true).toBool());
    
    // Load editor settings
    QString fontFamily = settings->value("editor/fontFamily", "Arial").toString();
    fontComboBox->setCurrentFont(QFont(fontFamily));
    fontSizeSpinBox->setValue(settings->value("editor/fontSize", 11).toInt());
    
    backgroundColor = settings->value("editor/backgroundColor", QColor(Qt::white)).value<QColor>();
    textColor = settings->value("editor/textColor", QColor(Qt::black)).value<QColor>();
    
    backgroundColorButton->setStyleSheet(
        QString("QPushButton { background-color: %1; border: 1px solid gray; padding: 5px; }")
        .arg(backgroundColor.name()));
    textColorButton->setStyleSheet(
        QString("QPushButton { background-color: %1; border: 1px solid gray; padding: 5px; }")
        .arg(textColor.name()));
    
    wordWrapCheckBox->setChecked(settings->value("editor/wordWrap", true).toBool());
    lineNumbersCheckBox->setChecked(settings->value("editor/lineNumbers", false).toBool());
    tabSizeSpinBox->setValue(settings->value("editor/tabSize", 4).toInt());
}

void PreferencesDialog::saveSettings()
{
    // Save general settings
    settings->setValue("general/author", authorLineEdit->text());
    settings->setValue("general/autoSave", autoSaveCheckBox->isChecked());
    settings->setValue("general/autoSaveInterval", autoSaveIntervalSpinBox->value());
    settings->setValue("general/showStatusBar", showStatusBarCheckBox->isChecked());
    settings->setValue("general/showToolBar", showToolBarCheckBox->isChecked());
    
    // Save editor settings
    settings->setValue("editor/fontFamily", fontComboBox->currentFont().family());
    settings->setValue("editor/fontSize", fontSizeSpinBox->value());
    settings->setValue("editor/backgroundColor", backgroundColor);
    settings->setValue("editor/textColor", textColor);
    settings->setValue("editor/wordWrap", wordWrapCheckBox->isChecked());
    settings->setValue("editor/lineNumbers", lineNumbersCheckBox->isChecked());
    settings->setValue("editor/tabSize", tabSizeSpinBox->value());
    
    settings->sync();
}