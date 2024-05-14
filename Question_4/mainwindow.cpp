#include "mainwindow.h"
#include <QAction>
#include <QFileDialog>
#include <QFile>
#include <QMenuBar>
#include <QTextStream>
#include <QTextCursor>
#include <QRegularExpression>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) {
    setWindowTitle("Regex Checker");
    resize(800, 600);

    textEdit = new QTextEdit(this);
    setCentralWidget(textEdit);

    QAction *openAction = new QAction("&Open", this);
    connect(openAction, &QAction::triggered, this, &MainWindow::openFile);
    menuBar()->addMenu("&File")->addAction(openAction);
}

void MainWindow::openFile() {
    QString fileName = QFileDialog::getOpenFileName(this, "Open File", "", "Text Files (*.txt)");
    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream in(&file);
            QString text = in.readAll();
            textEdit->setPlainText(text);
            highlightText(text);
            file.close();
        }
    }
}

void MainWindow::highlightText(const QString &text) {
    QTextCharFormat emailFormat;
    emailFormat.setForeground(Qt::blue);
    emailFormat.setFontWeight(QFont::Bold);
    QRegularExpression emailPattern("\\b[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\\.[A-Za-z]{2,}\\b");

    QTextCharFormat phoneFormat;
    phoneFormat.setForeground(Qt::darkGreen);
    phoneFormat.setFontWeight(QFont::Bold);
    QRegularExpression phonePattern("\\b(?:\\d{3}[-.]?){2}\\d{4}\\b|\\(\\d{3}\\)\\d{3}-\\d{4}|\\(\\d{3}\\)\\d{7}\\b");

    QTextCursor cursor(textEdit->document());
    cursor.beginEditBlock();

    // Email highlighting
    QRegularExpressionMatchIterator emailMatches = emailPattern.globalMatch(text);
    while (emailMatches.hasNext()) {
        QRegularExpressionMatch match = emailMatches.next();
        cursor.setPosition(match.capturedStart());
        cursor.movePosition(QTextCursor::Right, QTextCursor::KeepAnchor, match.capturedLength());
        cursor.mergeCharFormat(emailFormat);
    }

    // Phone number highlighting
    QRegularExpressionMatchIterator phoneMatches = phonePattern.globalMatch(text);
    while (phoneMatches.hasNext()) {
        QRegularExpressionMatch match = phoneMatches.next();
        cursor.setPosition(match.capturedStart());
        cursor.movePosition(QTextCursor::Right, QTextCursor::KeepAnchor, match.capturedLength());
        cursor.mergeCharFormat(phoneFormat);
    }

    cursor.endEditBlock();
}
