# Qt Learning Desktop Application

A comprehensive Qt desktop application example designed for learning Qt development on Linux Mint and other Linux distributions.

## Features

This application demonstrates essential Qt concepts and features:

### Core Qt Features

- **Main Window Architecture**: Complete main window with menus, toolbars, and status bar
- **Widget System**: Custom widgets and layouts
- **Event Handling**: Mouse, keyboard, and window events
- **Signals and Slots**: Qt's communication mechanism
- **Settings Management**: Persistent application settings

### Application Features

- **Text Editor**: Rich text editing with formatting options
- **File Operations**: New, Open, Save, Save As functionality
- **Edit Operations**: Undo, Redo, Cut, Copy, Paste, Select All
- **Context Menus**: Right-click menus with formatting options
- **Preferences Dialog**: Tabbed dialog for application settings
- **About Dialog**: Custom about dialog
- **Status Bar**: Real-time cursor position and document statistics
- **Splitter Layout**: Resizable UI components

### Learning Highlights

- **CMake Integration**: Modern CMake build system
- **MVC Pattern**: Separation of concerns
- **Custom Dialogs**: Modal and non-modal dialogs
- **Resource System**: Qt resource files for assets
- **Internationalization Ready**: Structure supports i18n
- **Cross-platform Design**: Works on Linux, Windows, and macOS

## Prerequisites

### System Requirements

- Linux Mint (or other Linux distribution)
- Qt6 development libraries
- CMake 3.16 or higher
- C++17 compatible compiler (GCC 7+ or Clang 5+)

### Install Dependencies on Linux Mint/Ubuntu

```bash
# Update package list
sudo apt update

# Install Qt6 development packages
sudo apt install qt6-base-dev qt6-tools-dev cmake build-essential

# Optional: Install Qt Creator IDE
sudo apt install qtcreator

# Verify Qt6 installation
qmake6 --version
```

### Alternative: Install Qt6 via Qt Online Installer

1. Download from: https://www.qt.io/download-qt-installer
2. Run installer and select Qt 6.5+ with CMake support
3. Add Qt6 to your PATH

## Building the Application

### Method 1: Using CMake (Recommended)

```bash
# Navigate to project directory
cd "QT test Project"

# Create build directory
mkdir build
cd build

# Configure with CMake
cmake ..

# Build the application
make -j$(nproc)

# Run the application
./bin/QtLearningApp
```

### Method 2: Using Qt Creator

1. Open Qt Creator
2. File → Open File or Project
3. Select `CMakeLists.txt`
4. Configure project with Qt6 kit
5. Build and run (Ctrl+R)

### Method 3: Using VS Code

1. Install C++ and CMake extensions
2. Open project folder in VS Code
3. Configure CMake (Ctrl+Shift+P → "CMake: Configure")
4. Build (Ctrl+Shift+P → "CMake: Build")

## Project Structure

```
QT test Project/
├── CMakeLists.txt              # Build configuration
├── README.md                   # This file
├── src/                        # Source files
│   ├── main.cpp               # Application entry point
│   ├── MainWindow.h/.cpp      # Main window class
│   ├── TextEditor.h/.cpp      # Custom text editor widget
│   ├── AboutDialog.h/.cpp     # About dialog
│   └── PreferencesDialog.h/.cpp # Settings dialog
├── resources/                  # Application resources
│   └── resources.qrc          # Resource collection file
└── .github/
    └── copilot-instructions.md # Development guidelines
```

## Learning Path

### Beginner Concepts

1. **Basic Qt Application** (`main.cpp`)

   - QApplication lifecycle
   - Window creation and display

2. **Widget Fundamentals** (`MainWindow`)

   - QMainWindow architecture
   - Menu bar, toolbar, status bar
   - Layout management

3. **Event System** (`TextEditor`)
   - Signals and slots connection
   - Event handling (mouse, keyboard)
   - Custom event processing

### Intermediate Concepts

1. **Custom Widgets** (`TextEditor`)

   - Subclassing Qt widgets
   - Custom painting and behavior
   - Widget communication

2. **Dialog Management** (`AboutDialog`, `PreferencesDialog`)

   - Modal vs non-modal dialogs
   - Dialog lifecycle
   - Data exchange between dialogs

3. **File I/O and Settings** (`MainWindow`)
   - QSettings for persistent data
   - File operations with QFile
   - Error handling

### Advanced Concepts

1. **Resource Management** (`resources.qrc`)

   - Qt Resource System
   - Asset embedding
   - Resource optimization

2. **Application Architecture**
   - Separation of concerns
   - Model-View patterns
   - Plugin architecture (future extension)

## Key Qt Classes Demonstrated

| Class          | Purpose               | File             |
| -------------- | --------------------- | ---------------- |
| `QApplication` | Application object    | `main.cpp`       |
| `QMainWindow`  | Main window framework | `MainWindow.cpp` |
| `QTextEdit`    | Rich text editing     | `TextEditor.cpp` |
| `QDialog`      | Modal dialogs         | `*Dialog.cpp`    |
| `QMenuBar`     | Application menus     | `MainWindow.cpp` |
| `QToolBar`     | Tool buttons          | `MainWindow.cpp` |
| `QStatusBar`   | Status information    | `MainWindow.cpp` |
| `QSettings`    | Persistent settings   | `MainWindow.cpp` |
| `QSplitter`    | Resizable layouts     | `MainWindow.cpp` |
| `QFileDialog`  | File selection        | `MainWindow.cpp` |

## Customization Ideas

Extend this application to learn more Qt features:

### UI Enhancements

- Add themes and stylesheets
- Implement custom drawings with QPainter
- Create custom widgets from scratch
- Add animations with QPropertyAnimation

### Functionality Extensions

- Database integration with QtSql
- Network features with QtNetwork
- Multimedia support with QtMultimedia
- Web integration with QtWebEngine

### Advanced Features

- Plugin architecture with QPluginLoader
- Internationalization with Qt Linguist
- Unit testing with Qt Test Framework
- Packaging with Qt Installer Framework

## Troubleshooting

### Common Build Issues

**Qt6 not found:**

```bash
# Specify Qt6 path manually
cmake -DCMAKE_PREFIX_PATH=/usr/lib/x86_64-linux-gnu/cmake/Qt6 ..
```

**Missing development packages:**

```bash
# Install additional Qt6 modules
sudo apt install qt6-base-dev-tools qt6-declarative-dev
```

**Permission issues:**

```bash
# Ensure proper permissions
chmod +x build/bin/QtLearningApp
```

### Runtime Issues

**Application doesn't start:**

- Verify Qt6 libraries are installed
- Check LD_LIBRARY_PATH includes Qt6 libraries
- Run with debug output: `QT_LOGGING_RULES="*=true" ./QtLearningApp`

## Learning Resources

### Official Qt Documentation

- [Qt6 Documentation](https://doc.qt.io/qt-6/)
- [Qt6 Examples](https://doc.qt.io/qt-6/qtexamples.html)
- [Qt6 Tutorials](https://doc.qt.io/qt-6/tutorials.html)

### Recommended Books

- "C++ GUI Programming with Qt 5" by Jasmin Blanchette
- "Advanced Qt Programming" by Mark Summerfield
- "Qt5 Cadaques" (Free online book)

### Online Resources

- [Qt Learning](https://www.qt.io/learning)
- [Qt Forum](https://forum.qt.io/)
- [Qt Wiki](https://wiki.qt.io/)

## Contributing

This is a learning project. Feel free to:

- Add new features to explore Qt capabilities
- Improve code structure and documentation
- Share your modifications and learnings
- Report issues or suggest improvements

## License

This project is created for educational purposes. Feel free to use, modify, and distribute for learning Qt development.

---

**Happy Qt Learning!** 🚀

Start by building and running the application, then explore the code to understand how different Qt concepts work together.
