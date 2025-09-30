#ifndef PREFERENCESDIALOG_H
#define PREFERENCESDIALOG_H

#include <QDialog>
#include <QTabWidget>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>
#include <QSpinBox>
#include <QCheckBox>
#include <QComboBox>
#include <QPushButton>
#include <QGroupBox>
#include <QFontComboBox>
#include <QColorDialog>
#include <QSettings>

class PreferencesDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PreferencesDialog(QWidget *parent = nullptr);

private slots:
    void selectBackgroundColor();
    void selectTextColor();
    void applySettings();
    void resetSettings();

private:
    void setupUI();
    void loadSettings();
    void saveSettings();
    
    // UI Components
    QTabWidget *tabWidget;
    
    // General tab
    QWidget *generalTab;
    QLineEdit *authorLineEdit;
    QCheckBox *autoSaveCheckBox;
    QSpinBox *autoSaveIntervalSpinBox;
    QCheckBox *showStatusBarCheckBox;
    QCheckBox *showToolBarCheckBox;
    
    // Editor tab
    QWidget *editorTab;
    QFontComboBox *fontComboBox;
    QSpinBox *fontSizeSpinBox;
    QPushButton *backgroundColorButton;
    QPushButton *textColorButton;
    QCheckBox *wordWrapCheckBox;
    QCheckBox *lineNumbersCheckBox;
    QSpinBox *tabSizeSpinBox;
    
    // Buttons
    QPushButton *okButton;
    QPushButton *cancelButton;
    QPushButton *applyButton;
    QPushButton *resetButton;
    
    QSettings *settings;
    QColor backgroundColor;
    QColor textColor;
};

#endif // PREFERENCESDIALOG_H