#ifndef TEXTEDITOR_H
#define TEXTEDITOR_H

#include <QTextEdit>
#include <QFontDialog>
#include <QColorDialog>
#include <QTextCharFormat>
#include <QFont>
#include <QColor>

class TextEditor : public QTextEdit
{
    Q_OBJECT

public:
    explicit TextEditor(QWidget *parent = nullptr);

public slots:
    void setFontBold(bool bold);
    void setFontItalic(bool italic);
    void setFontUnderline(bool underline);
    void setFontSize(int size);
    void setFontFamily(const QString &family);
    void setTextColor(const QColor &color);
    void changeFont();
    void changeColor();

protected:
    void contextMenuEvent(QContextMenuEvent *event) override;

private slots:
    void currentCharFormatChanged(const QTextCharFormat &format);

private:
    void mergeFormatOnWordOrSelection(const QTextCharFormat &format);

signals:
    void fontChanged(const QFont &font);
    void colorChanged(const QColor &color);
};

#endif // TEXTEDITOR_H