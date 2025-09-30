#include "TextEditor.h"
#include <QContextMenuEvent>
#include <QMenu>
#include <QFontDialog>
#include <QColorDialog>
#include <QTextCursor>

TextEditor::TextEditor(QWidget *parent)
    : QTextEdit(parent)
{
    setPlainText("Welcome to Qt Learning Application!\n\n"
                 "This is a complete Qt desktop application example that demonstrates:\n\n"
                 "• Main window with menus and toolbars\n"
                 "• Text editing capabilities\n"
                 "• File operations (New, Open, Save, Save As)\n"
                 "• Edit operations (Undo, Redo, Cut, Copy, Paste)\n"
                 "• Settings and preferences\n"
                 "• Status bar with cursor position\n"
                 "• About dialogs\n"
                 "• Context menus\n"
                 "• Rich text formatting\n\n"
                 "Try exploring the menus and toolbars to learn Qt features!\n\n"
                 "Right-click in this text area to see the context menu with formatting options.");

    // Connect to format changes
    connect(this, &QTextEdit::currentCharFormatChanged,
            this, &TextEditor::currentCharFormatChanged);

    // Set default font
    QFont font("Arial", 11);
    setFont(font);
}

void TextEditor::setFontBold(bool bold)
{
    QTextCharFormat format;
    format.setFontWeight(bold ? QFont::Bold : QFont::Normal);
    mergeFormatOnWordOrSelection(format);
}

void TextEditor::setFontItalic(bool italic)
{
    QTextCharFormat format;
    format.setFontItalic(italic);
    mergeFormatOnWordOrSelection(format);
}

void TextEditor::setFontUnderline(bool underline)
{
    QTextCharFormat format;
    format.setFontUnderline(underline);
    mergeFormatOnWordOrSelection(format);
}

void TextEditor::setFontSize(int size)
{
    QTextCharFormat format;
    format.setFontPointSize(size);
    mergeFormatOnWordOrSelection(format);
}

void TextEditor::setFontFamily(const QString &family)
{
    QTextCharFormat format;
    format.setFontFamily(family);
    mergeFormatOnWordOrSelection(format);
}

void TextEditor::setTextColor(const QColor &color)
{
    QTextCharFormat format;
    format.setForeground(color);
    mergeFormatOnWordOrSelection(format);
}

void TextEditor::changeFont()
{
    bool ok;
    QFont font = QFontDialog::getFont(&ok, currentFont(), this);
    if (ok) {
        QTextCharFormat format;
        format.setFont(font);
        mergeFormatOnWordOrSelection(format);
        emit fontChanged(font);
    }
}

void TextEditor::changeColor()
{
    QColor color = QColorDialog::getColor(textColor(), this);
    if (color.isValid()) {
        setTextColor(color);
        emit colorChanged(color);
    }
}

void TextEditor::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu *menu = createStandardContextMenu();
    
    menu->addSeparator();
    
    QAction *fontAction = menu->addAction("Change Font...");
    connect(fontAction, &QAction::triggered, this, &TextEditor::changeFont);
    
    QAction *colorAction = menu->addAction("Change Color...");
    connect(colorAction, &QAction::triggered, this, &TextEditor::changeColor);
    
    menu->addSeparator();
    
    QTextCharFormat format = currentCharFormat();
    
    QAction *boldAction = menu->addAction("Bold");
    boldAction->setCheckable(true);
    boldAction->setChecked(format.fontWeight() == QFont::Bold);
    connect(boldAction, &QAction::toggled, this, &TextEditor::setFontBold);
    
    QAction *italicAction = menu->addAction("Italic");
    italicAction->setCheckable(true);
    italicAction->setChecked(format.fontItalic());
    connect(italicAction, &QAction::toggled, this, &TextEditor::setFontItalic);
    
    QAction *underlineAction = menu->addAction("Underline");
    underlineAction->setCheckable(true);
    underlineAction->setChecked(format.fontUnderline());
    connect(underlineAction, &QAction::toggled, this, &TextEditor::setFontUnderline);
    
    menu->exec(event->globalPos());
    delete menu;
}

void TextEditor::currentCharFormatChanged(const QTextCharFormat &format)
{
    emit fontChanged(format.font());
    emit colorChanged(format.foreground().color());
}

void TextEditor::mergeFormatOnWordOrSelection(const QTextCharFormat &format)
{
    QTextCursor cursor = textCursor();
    if (!cursor.hasSelection())
        cursor.select(QTextCursor::WordUnderCursor);
    
    cursor.mergeCharFormat(format);
    mergeCurrentCharFormat(format);
}