#ifndef MYTABLEWIDGET_H
#define MYTABLEWIDGET_H
#include <QTableWidget>

class MyTableWidget : public QTableWidget {
public:
    MyTableWidget(int rows, int columns, QWidget* parent = nullptr);

};


#endif // MYTABLEWIDGET_H
