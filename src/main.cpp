#include <QApplication>
#include <QStyleFactory>
#include <QDir>
#include "MainWindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    
    // Set application properties
    app.setApplicationName("Qt Learning Application");
    app.setApplicationVersion("1.0.0");
    app.setOrganizationName("Qt Learning");
    
    // Create and show main window
    MainWindow window;
    window.show();
    
    return app.exec();
}