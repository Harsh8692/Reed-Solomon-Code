#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QLineEdit>
#include <QCheckBox>
#include <QPushButton>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QScrollArea>
#include <bits/stdc++.h>
#include "mytablewidget.h"
#define ll long long
using namespace std;

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

private slots:
    void encode();
    void encodesys();
    void createTable();
    void validateN();
    void validateK();
    void validateSrcCol();
    void validateDestCol();
    void swapCols();
    vector<ll> classicalEncoder(vector<ll> &message);
    void validateErr();
    void intdErrPerSegInClassical();
    void intdErrPerSegInSystematic();

    void classicalRemoveErr();
    void systematicRemoveErr();

private:
    QLineEdit *nLineEdit;
    QLineEdit *kLineEdit;
    QLineEdit *messageLineEdit;
    QLineEdit *srccolEdit;
    QLineEdit *destcolEdit;
    QLineEdit* evalPts;
    QLineEdit* intdErrPerSegEdit;
    QLabel* classical;
    QLabel* classicalencd;
    QLabel* systematic;
    QLabel* systematicencd;
    QLabel* intdErr;
    QLabel* intdErrCl;
    QLabel* intdErrClassical;
    QLabel* intdErrSys;
    QLabel* intdErrSystematic;
    QLabel* removeErrCl;
    QLabel* removeErrClassical;
    QLabel* removeErrSys;
    QLabel* removeErrSystematic;
    // QLabel* footer;
    QScrollArea *scrollArea;
    QString qlblstyle;
    QString lneditstyle;
    QString tblstyle;
    QString btnstyle;

    QPushButton *systematicEncButton;
    MyTableWidget *table;
    QPushButton *encodeButton;
    QPushButton *createpgmButton;
    QPushButton *movecolButton;
    QPushButton *intdErrClassicalButton;
    QPushButton *intdErrSystematicButton;
    QPushButton *removeErrClassicalButton;
    QPushButton *removeErrSystematicButton;

    QTextEdit *resultTextEdit;
};

#endif // MAINWINDOW_H

