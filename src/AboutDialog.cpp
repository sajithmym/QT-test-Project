#include "AboutDialog.h"
#include <QApplication>

AboutDialog::AboutDialog(QWidget *parent)
    : QDialog(parent)
{
    setupUI();
    setWindowTitle("About Qt Learning Application");
    setFixedSize(400, 300);
}

void AboutDialog::setupUI()
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    
    // Application icon (placeholder)
    QLabel *iconLabel = new QLabel;
    iconLabel->setAlignment(Qt::AlignCenter);
    iconLabel->setStyleSheet("QLabel { background-color: #4CAF50; color: white; "
                            "font-size: 24px; font-weight: bold; "
                            "border-radius: 5px; padding: 10px; }");
    iconLabel->setText("Qt");
    iconLabel->setFixedSize(60, 60);
    
    // Application name and version
    QLabel *nameLabel = new QLabel("Qt Learning Application");
    nameLabel->setAlignment(Qt::AlignCenter);
    nameLabel->setStyleSheet("font-size: 18px; font-weight: bold; margin: 10px;");
    
    QLabel *versionLabel = new QLabel("Version 1.0.0");
    versionLabel->setAlignment(Qt::AlignCenter);
    versionLabel->setStyleSheet("font-size: 12px; color: #666;");
    
    // Description
    QLabel *descriptionLabel = new QLabel(
        "A comprehensive Qt desktop application example for learning Qt development.\n\n"
        "This application demonstrates:\n"
        "• Window management and layouts\n"
        "• Menus, toolbars, and status bars\n"
        "• File operations and dialogs\n"
        "• Text editing and formatting\n"
        "• Settings and preferences\n"
        "• Custom dialogs and widgets"
    );
    descriptionLabel->setAlignment(Qt::AlignCenter);
    descriptionLabel->setWordWrap(true);
    descriptionLabel->setStyleSheet("margin: 15px; line-height: 1.4;");
    
    // Qt version info
    QLabel *qtLabel = new QLabel(QString("Built with Qt %1").arg(QT_VERSION_STR));
    qtLabel->setAlignment(Qt::AlignCenter);
    qtLabel->setStyleSheet("font-size: 10px; color: #888; margin-top: 10px;");
    
    // OK button
    QPushButton *okButton = new QPushButton("OK");
    okButton->setDefault(true);
    connect(okButton, &QPushButton::clicked, this, &QDialog::accept);
    
    // Layout
    QHBoxLayout *iconLayout = new QHBoxLayout;
    iconLayout->addStretch();
    iconLayout->addWidget(iconLabel);
    iconLayout->addStretch();
    
    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addStretch();
    buttonLayout->addWidget(okButton);
    buttonLayout->addStretch();
    
    mainLayout->addLayout(iconLayout);
    mainLayout->addWidget(nameLabel);
    mainLayout->addWidget(versionLabel);
    mainLayout->addWidget(descriptionLabel);
    mainLayout->addWidget(qtLabel);
    mainLayout->addStretch();
    mainLayout->addLayout(buttonLayout);
}