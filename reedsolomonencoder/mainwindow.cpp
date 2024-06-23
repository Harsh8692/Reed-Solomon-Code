#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mytablewidget.h"
#include <QValidator>
#include <QTableWidget>
#include <QMessageBox>
#include <QDropEvent>
#include <QDrag>
#include <QMimeData>
#include <QHeaderView>
#include <QMouseEvent>
// #include <QAbstractItemView>
#include <QDebug>
#include <bits/stdc++.h>
using namespace std;
#define ll long long

using namespace std;

bool isPrime(int n)
{
    int count = 0;
    for(int i=1;i*i<=n;i++){
        if(n%i==0){
            count++;
            if(n/i!=i){
                count++;
            }
        }
    }
    if(count==2)return true;
    else return false;
}


ll power(ll a, ll b, ll mod){
    if(b==0)return 1%mod;
    ll result = 1;
    a = a%mod;
    while(b>0){
        if(b%2==1){
            result = (result * a)%mod;
        }
        a = (a*a)%mod;
        b/=2;
    }
    return result;
}

// time complexity : O(rows * columns)
MyTableWidget::MyTableWidget(int rows, int columns, QWidget */*parent*/) {
    setRowCount(rows);
    setColumnCount(columns);
    for(int row = 0; row < rows; ++row){
        for(int col = 0; col < columns; ++col){
            QString value = QString::number(power(col, row, columns));
            QTableWidgetItem* item = new QTableWidgetItem(value);
            setItem(row, col, item);
        }
    }

}




MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) {

    // setFixedWidth(500);

    // Create GUI elements
    QLabel *titleLabel = new QLabel("<html><body><h1>Reed-Solomon Encoder</h1></body></html>");
    QLabel *nLabel = new QLabel("Enter value for n(prime)/Length of the Codeword.");
    nLineEdit = new QLineEdit;
    QLabel *kLabel = new QLabel("Enter value for k(less than n)/Length of the Message");
    QLabel *pgm = new QLabel("<html><body><h3>Parity Generator Matrix</h3></body></html>");
    QLabel *srccol = new QLabel("Source Column");
    QLabel *destcol = new QLabel("Destination Column");
    QLabel *message = new QLabel("<html><body><h3>Original Message</h3></body></html>");
    QLabel *systematictext = new QLabel("Default Evaluation points are [0 .. K-1].\nGive different evaluation points for systematic input ? ");
    QLabel *originalcw = new QLabel("<html><body><h3>Original CodeWords</h3></body></html>");
    QLabel *errorneouscw = new QLabel("<html><body><h3>Errorneous CodeWords</h3></body></html>");
    QLabel *errfreecw = new QLabel("<html><body><h3>CodeWords after Error Removal</h3></body></html>");
    QLabel *footer = new QLabel("<html><body><p>Note: I have used Berlekamp-Welch Algorithm for decoding or removing errors from the codeword.</p><p>Resources used are: <ul><li><a href='https://www.jeremykun.com/2015/09/07/welch-berlekamp/#a-simple-example'>Math &cap; Programming</a></li><li><a href='https://en.wikipedia.org/wiki/Reed%E2%80%93Solomon_error_correction'>Wikipedia RS Code</a></li><li><a href='https://en.wikipedia.org/wiki/Berlekamp%E2%80%93Welch_algorithm'>Wikipedia Berlekamp-Welch Algorithm</a></li></ul></p></body></html>");
    footer->setTextInteractionFlags(Qt::TextBrowserInteraction);
    footer->setOpenExternalLinks(true);

    qlblstyle = "color: black; qproperty-alignment: AlignCenter; font-size: 16px; padding: 5px;";
    btnstyle = "QPushButton { font-size:16px; background-color: blue; border-radius: 5px; color: white; border: none; padding: 5px;}" "QPushButton:hover { background-color: lightblue; color: black;}";
    lneditstyle = "QLineEdit { border: 2px solid red; padding: 5px; color: blue; border-radius: 5px;}";

    classical = new QLabel("Classical Encoded Message");
    classicalencd = new QLabel;
    classicalencd->setTextInteractionFlags(Qt::TextSelectableByMouse);
    systematic = new QLabel("Systematic Encoded Message");
    systematicencd = new QLabel;
    systematicencd->setTextInteractionFlags(Qt::TextSelectableByMouse);
    intdErr = new QLabel("Enter a number specifying maximum no of erros to be introduced in each partition of the codeword");
    intdErrCl = new QLabel("Classical Codeword after introducing errors per segment.");
    intdErrClassical = new QLabel;
    intdErrClassical->setTextInteractionFlags(Qt::TextSelectableByMouse);
    intdErrSys = new QLabel("Systematic Codeword after introducting errors per segment.");
    intdErrSystematic = new QLabel;
    intdErrSystematic->setTextInteractionFlags(Qt::TextSelectableByMouse);
    removeErrCl = new QLabel("Classical codeword after removing the errors.");
    removeErrClassical = new QLabel;
    removeErrClassical->setTextInteractionFlags(Qt::TextSelectableByMouse);
    removeErrSys = new QLabel("Systematic Codeword after removing the errors.");
    removeErrSystematic = new QLabel;
    removeErrSystematic->setTextInteractionFlags(Qt::TextSelectableByMouse);


    kLineEdit = new QLineEdit;
    messageLineEdit = new QLineEdit;
    srccolEdit = new QLineEdit;
    destcolEdit = new QLineEdit;
    evalPts = new QLineEdit;
    intdErrPerSegEdit = new QLineEdit;

    createpgmButton = new QPushButton("Create PGM");
    systematicEncButton = new QPushButton("Systematic Encoding");

    encodeButton = new QPushButton("Classical Encoding");
    movecolButton = new QPushButton("Move");
    intdErrClassicalButton = new QPushButton("Introduce errors in Classical Coding");
    intdErrSystematicButton = new QPushButton("Introduce errors in Systematic Coding");

    removeErrClassicalButton = new QPushButton("Remove Erros from the Classical Codeword");
    removeErrSystematicButton = new QPushButton("Remove Errors from the Systematic Codeword");

    resultTextEdit = new QTextEdit;

    table = new MyTableWidget(0, 0); // create an empty table for now
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);

    QWidget *centralWidget = new QWidget(this);
    // Layout setup
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);

    mainLayout->setContentsMargins(100, 20, 100, 20);

    titleLabel->setStyleSheet(qlblstyle);
    titleLabel->setWordWrap(true);
    mainLayout->addWidget(titleLabel);
    nLabel->setStyleSheet(qlblstyle);
    nLabel->setWordWrap(true);
    mainLayout->addWidget(nLabel);
    nLineEdit->setStyleSheet(lneditstyle);
    mainLayout->addWidget(nLineEdit);
    kLabel->setStyleSheet(qlblstyle);
    kLabel->setWordWrap(true);
    mainLayout->addWidget(kLabel);
    kLineEdit->setStyleSheet(lneditstyle);
    mainLayout->addWidget(kLineEdit);

    createpgmButton->setStyleSheet(btnstyle);
    mainLayout->addWidget(createpgmButton);

    systematictext->setStyleSheet(qlblstyle);
    systematictext->setWordWrap(true);
    mainLayout->addWidget(systematictext);
    evalPts->setStyleSheet(lneditstyle);
    mainLayout->addWidget(evalPts);

    pgm->setStyleSheet(qlblstyle);
    pgm->setWordWrap(true);
    mainLayout->addWidget(pgm);
    srccol->setStyleSheet(qlblstyle);
    srccol->setWordWrap(true);
    mainLayout->addWidget(srccol);
    srccolEdit->setStyleSheet(lneditstyle);
    mainLayout->addWidget(srccolEdit);
    destcol->setStyleSheet(qlblstyle);
    destcol->setWordWrap(true);
    mainLayout->addWidget(destcol);
    destcolEdit->setStyleSheet(lneditstyle);
    mainLayout->addWidget(destcolEdit);
    movecolButton->setStyleSheet(btnstyle);
    mainLayout->addWidget(movecolButton);
    table->setStyleSheet(tblstyle);
    mainLayout->addWidget(table);

    message->setStyleSheet(qlblstyle);
    message->setWordWrap(true);
    mainLayout->addWidget(message);
    messageLineEdit->setStyleSheet(lneditstyle);
    mainLayout->addWidget(messageLineEdit);
    encodeButton->setStyleSheet(btnstyle);
    mainLayout->addWidget(encodeButton);
    systematicEncButton->setStyleSheet(btnstyle);
    mainLayout->addWidget(systematicEncButton);

    originalcw->setStyleSheet(qlblstyle);
    originalcw->setWordWrap(true);
    mainLayout->addWidget(originalcw);

    classical->setStyleSheet(qlblstyle);
    classical->setWordWrap(true);
    mainLayout->addWidget(classical);
    classicalencd->setStyleSheet("border: 2px solid #ffffff; padding: 5px; color: #007e0f; border-radius: 5px;");
    classicalencd->setWordWrap(true);
    mainLayout->addWidget(classicalencd);
    systematic->setStyleSheet(qlblstyle);
    systematic->setWordWrap(true);
    mainLayout->addWidget(systematic);
    systematicencd->setStyleSheet("border: 2px solid #ffffff; padding: 5px; color: #007e0f; border-radius: 5px;");
    systematicencd->setWordWrap(true);
    mainLayout->addWidget(systematicencd);
    intdErr->setStyleSheet(qlblstyle);
    intdErr->setWordWrap(true);
    mainLayout->addWidget(intdErr);
    intdErrPerSegEdit->setStyleSheet(lneditstyle);
    mainLayout->addWidget(intdErrPerSegEdit);
    intdErrClassicalButton->setStyleSheet(btnstyle);
    mainLayout->addWidget(intdErrClassicalButton);
    intdErrSystematicButton->setStyleSheet(btnstyle);
    mainLayout->addWidget(intdErrSystematicButton);

    errorneouscw->setStyleSheet(qlblstyle);
    errorneouscw->setWordWrap(true);
    mainLayout->addWidget(errorneouscw);

    intdErrCl->setStyleSheet(qlblstyle);
    intdErrCl->setWordWrap(true);
    mainLayout->addWidget(intdErrCl);
    intdErrClassical->setStyleSheet("border: 2px solid #ffffff; padding: 5px; color: #007e0f; border-radius: 5px;");
    intdErrClassical->setWordWrap(true);
    mainLayout->addWidget(intdErrClassical);
    intdErrSys->setStyleSheet(qlblstyle);
    intdErrSys->setWordWrap(true);
    mainLayout->addWidget(intdErrSys);
    intdErrSystematic->setStyleSheet("border: 2px solid #ffffff; padding: 5px; color: #007e0f; border-radius: 5px;");
    intdErrSystematic->setWordWrap(true);
    mainLayout->addWidget(intdErrSystematic);

    removeErrClassicalButton->setStyleSheet(btnstyle);
    mainLayout->addWidget(removeErrClassicalButton);
    removeErrSystematicButton->setStyleSheet(btnstyle);
    mainLayout->addWidget(removeErrSystematicButton);

    errfreecw->setStyleSheet(qlblstyle);
    errfreecw->setWordWrap(true);
    mainLayout->addWidget(errfreecw);

    removeErrCl->setStyleSheet(qlblstyle);
    removeErrCl->setWordWrap(true);
    mainLayout->addWidget(removeErrCl);
    removeErrClassical->setStyleSheet("border: 2px solid #ffffff; padding: 5px; color: #007e0f; border-radius: 5px;");
    removeErrClassical->setWordWrap(true);
    mainLayout->addWidget(removeErrClassical);
    removeErrSys->setStyleSheet(qlblstyle);
    removeErrSys->setWordWrap(true);
    mainLayout->addWidget(removeErrSys);
    removeErrSystematic->setStyleSheet("border: 2px solid #ffffff; padding: 5px; color: #007e0f; border-radius: 5px;");
    removeErrSystematic->setWordWrap(true);
    mainLayout->addWidget(removeErrSystematic);

    footer->setStyleSheet(qlblstyle);
    footer->setStyleSheet("background-color: #dedede; qproperty-alignment: AlignCenter; font-size: 16px; padding: 10px; border-radius: 5px;");
    footer->setWordWrap(true);
    mainLayout->addWidget(footer);


    setCentralWidget(centralWidget);

    scrollArea = new QScrollArea;
    scrollArea->setWidgetResizable(true); // Allow the scroll area to resize its widget
    scrollArea->setWidget(centralWidget);

    setCentralWidget(scrollArea);

    // Connect signals and slots
    connect(createpgmButton, &QPushButton::clicked, this, &MainWindow::createTable);
    connect(encodeButton, &QPushButton::clicked, this, &MainWindow::encode);
    connect(systematicEncButton, &QPushButton::clicked, this, &MainWindow::encodesys);
    connect(nLineEdit, &QLineEdit::editingFinished, this, &MainWindow::validateN);
    connect(kLineEdit, &QLineEdit::editingFinished, this, &MainWindow::validateK);
    connect(srccolEdit, &QLineEdit::editingFinished, this, &MainWindow::validateSrcCol);
    connect(destcolEdit, &QLineEdit::editingFinished, this, &MainWindow::validateDestCol);
    connect(movecolButton, &QPushButton::clicked, this, &MainWindow::swapCols);
    connect(intdErrPerSegEdit, &QLineEdit::editingFinished, this, &MainWindow::validateErr);
    connect(intdErrClassicalButton, &QPushButton::clicked, this, &MainWindow::intdErrPerSegInClassical);
    connect(intdErrSystematicButton, &QPushButton::clicked, this, &MainWindow::intdErrPerSegInSystematic);
    connect(removeErrClassicalButton, &QPushButton::clicked, this, &MainWindow::classicalRemoveErr);
    connect(removeErrSystematicButton, &QPushButton::clicked, this, &MainWindow::systematicRemoveErr);

}

// time complexity : O((log mod)^2)
ll modval(ll val, ll mod){
    val %= mod;
    if(val<0) val += mod;
    return val;
}

// time complexity : O(log(min(a, b))*(loga * logb))
ll gcdExtended(ll a, ll b, ll &x, ll &y)
{
    // Base Case
    if (a == 0)
    {
        x = 0;
        y = 1;
        return b;
    }

    ll x1, y1; // To store results of recursive call
    ll gcd = gcdExtended(b%a, a, x1, y1);

    x = y1 - (b/a) * x1;
    y = x1;
    return gcd;
}

// time complexity : O(log(min(a, b))*(loga * logb))
ll inverse(ll val, ll mod){
    ll a = val, b = mod;
    ll x, y;
    gcdExtended(a, b, x, y);
    return modval(x, mod);
}

// time complexity : O(k^2 * log(n)^3)
ll interpolate(vector<ll> &vec, vector<ll>&evalpts, ll xi, ll k, ll n){
    ll ans = 0;
    for(ll i=0; i<k; ++i){
        ll term = vec[i];
        for(ll j=0; j< k; j++){
            if(i!=j){
                term = ((term *(modval(xi - evalpts[j], n)))* inverse(modval(evalpts[i]-evalpts[j], n), n))%n;
            }
        }
        ans = (ans + term)%n;
    }
    return ans;
}

void MainWindow::intdErrPerSegInClassical(){
    QString cw = classicalencd->text();
    QStringList nums = cw.split(" ", Qt::SkipEmptyParts);
    ll n = nLineEdit->text().toInt();
    vector<ll>numbers;
    foreach(QString num, nums){
        numbers.push_back(num.toInt());
    }
    if(numbers.size()<=0||numbers.size()%n!=0){
        QMessageBox::warning(this, "Warning", "Update the Classical Codeword before procceding with error introduction!");
        return;
    }
    vector<bool>marker(numbers.size(), false);
    // max no. of erros to be introduced per segment
    ll nerr = intdErrPerSegEdit->text().toInt();
    // we want to select at max nerr indexed from each segment and assign those indexes a value different from their current value.

    // Creating a random device and we'll use it to seed the random number generator.
    random_device rd;
    mt19937 gen(rd());

    // Creating a uniform distribution in the range [0, nerr].
    uniform_int_distribution<> dis(0, nerr);

    // Generating the random number
    for(ll i=0; i<numbers.size(); i+=n){
        // Generating a random number
        ll rnderr = dis(gen);

        // create a vector with all possible values from 0 to n.
        vector<ll>nums(n);
        iota(nums.begin(), nums.end(), 0);

        vector<ll>selected_nums;

        sample(nums.begin(), nums.end(), back_inserter(selected_nums), rnderr, gen);
        for(auto it: selected_nums){
            numbers[i+it] = modval(numbers[i+it]+1, n); // introductin error i will check if we can randomize it.
            marker[i+it] = true;
        }
    }

    QString ans = "";
    for(ll i=0; i<numbers.size(); i++){
        ans += QString::number(numbers[i]);
        ans += " ";
    }

    intdErrClassical->setText(ans);

}

void MainWindow::intdErrPerSegInSystematic(){
    QString cw = systematicencd->text();
    QStringList nums = cw.split(" ", Qt::SkipEmptyParts);
    ll n = nLineEdit->text().toInt();
    vector<ll>numbers;
    foreach(QString num, nums){
        numbers.push_back(num.toInt());
    }

    if(numbers.size()<=0||numbers.size()%n!=0){
        QMessageBox::warning(this, "Warning", "Update the Systematic Codeword before procceding with error introduction!");
        return;
    }

    vector<bool>marker(numbers.size(), false);
    // max no. of erros to be introduced per segment
    ll nerr = intdErrPerSegEdit->text().toInt();
    // we want to select at max nerr indexed from each segment and assign those indexes a value different from their current value.

    // Creating a random device and we'll use it to seed the random number generator.
    random_device rd;
    mt19937 gen(rd());

    // Creating a uniform distribution in the range [0, nerr].
    uniform_int_distribution<> dis(0, nerr);

    // Generating the random number
    for(ll i=0; i<numbers.size(); i+=n){
        // Generating a random number
        ll rnderr = dis(gen);

        // create a vector with all possible values from 0 to n.
        vector<ll>nums(n);
        iota(nums.begin(), nums.end(), 0);

        vector<ll>selected_nums;

        sample(nums.begin(), nums.end(), back_inserter(selected_nums), rnderr, gen);
        for(auto it: selected_nums){
            numbers[i+it] = modval(numbers[i+it]+1, n); // introductin error i will check if we can randomize it.
            marker[i+it] = true;
        }
    }

    QString ans="";

    for(ll i=0; i<numbers.size(); i++){
        ans += QString::number(numbers[i]);
        ans += " ";
    }

    intdErrSystematic->setText(ans);

}

void MainWindow::validateErr(){
    int err = intdErrPerSegEdit->text().toInt();
    int n = nLineEdit->text().toInt();
    int k = kLineEdit->text().toInt();
    int maxErrs = (n-k)/2;
    QString msg = "No. of errors per segment should be between 0 to ";
    msg += QString::number(maxErrs);
    msg += "(both inclusive).";
    if(err<0){
        QMessageBox::warning(this, "Warning", msg);
        intdErrPerSegEdit->setText("");
    }
    else if(err>maxErrs){
        QMessageBox::warning(this, "Warning",  msg);
        intdErrPerSegEdit->setText("");
    }
}


// time complexity : O(rows * columns)
void MainWindow::swapCols(){
    int srccol = srccolEdit->text().toInt();
    int destcol = destcolEdit->text().toInt();

    if(srccol<destcol){
        QVector<QString>sCol;
        for(int row=0; row<table->rowCount(); ++row){
            sCol.push_back(table->item(row, srccol)->text());
        }
        for(int col=srccol+1;col<=destcol;++col){
            for(int row = 0; row<table->rowCount(); ++row){
                table->item(row, col-1)->setText(table->item(row,col)->text());
            }
        }
        for(int row = 0; row<table->rowCount(); ++row){
            table->item(row, destcol)->setText(sCol[row]);
        }
    }
    else if(srccol > destcol){
        QVector<QString>sCol;
        for(int row=0; row<table->rowCount(); ++row){
            sCol.push_back(table->item(row, srccol)->text());
        }
        for(int col=srccol;col>destcol;--col){
            for(int row=0; row<table->rowCount(); ++row){
                table->item(row, col)->setText(table->item(row, col-1)->text());
            }
        }
        for(int row = 0; row<table->rowCount(); ++row){
            table->item(row, destcol)->setText(sCol[row]);
        }
    }

}

void MainWindow::validateK(){
    ll k = kLineEdit->text().toInt();
    ll n = nLineEdit->text().toInt();
    QString msg = "Value of k should be greater than 0 and less than ";
    msg += QString::number(n);
    if(k<=0){
        QMessageBox::warning(this, "Warning",  msg);
        kLineEdit->setText("");
    }
    else if(k>=n){
        QMessageBox::warning(this, "Warning",  msg);
        kLineEdit->setText("");
    }
}

void MainWindow::validateSrcCol(){
    ll n = nLineEdit->text().toInt();
    ll srccol = srccolEdit->text().toInt();
    QString msg = "Value of source column should be between 0 to ";
    msg += QString::number(n-1);
    if(srccol<0 || srccol>=n){
        QMessageBox::warning(this, "Warning", msg);
        srccolEdit->setText("");
    }
}

void MainWindow::validateDestCol(){
    int n = nLineEdit->text().toInt();
    int destcol = destcolEdit->text().toInt();
    QString msg = "Value of destination column should be between 0 to ";
    msg += QString::number(n-1);
    if(destcol<0 || destcol>=n){
        QMessageBox::warning(this, "Warning", msg);
        destcolEdit->setText("");
    }
}

void MainWindow::validateN(){
    int n = nLineEdit->text().toInt();
    if(n<=0){
        QMessageBox::warning(this, "Warning",  "Value of n should be greater than 0");
        nLineEdit->setText("");
    }
    else if(!isPrime(n)){
        QMessageBox::warning(this, "Warning",  "Value of n should be prime");
        nLineEdit->setText("");
    }
}

// time complexity : O(k * n)
void MainWindow::createTable(){
    int k = kLineEdit->text().toInt();
    int n = nLineEdit->text().toInt();

    QVBoxLayout *mainLayout = dynamic_cast<QVBoxLayout*>(scrollArea->widget()->layout());
    int index = mainLayout->indexOf(table);
    if(table){
        mainLayout->removeWidget(table);
        delete table;
    }

    table = new MyTableWidget(k, n);
    int rowCount = 10; // Set the number of rows you want to display without scrolling
    int rowHeight = 30; // Set your desired row height in pixels
    int tableHeight = rowCount * rowHeight;
    table->setMinimumHeight(tableHeight);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    mainLayout->insertWidget(index,table);

}

// time complexity : O(k * n * (log n)^2)
vector<ll> MainWindow::classicalEncoder(vector<ll> &message){
    int n = nLineEdit->text().toInt();
    int k = kLineEdit->text().toInt();
    vector<ll> ans(n, 0ll);
    for(int j = 0; j < n; ++j){
        for(int i = 0; i < k; ++i){
            ans[j] = (ans[j] + (message[i] * table->item(i, j)->text().toInt())%n )%n;
        }
    }
    return ans;
}

// time complexity : O(n * k^2 * log(n)^3)
vector<ll> systematicEncoder(vector<ll>& message, vector<ll>&evaltnPts, int k, int n){

    vector<ll> ans;
    for(ll i=0; i<n; ++i){
        ans.push_back(interpolate(message, evaltnPts, i, k, n));
    }
    return ans;

}

// time complexity : O(nchunks * n * k^2 * log(n)^3)
void MainWindow::encodesys(){
    int n = nLineEdit->text().toInt();
    int k = kLineEdit->text().toInt();

    // Validating message
    QString msg = messageLineEdit->text();
    QStringList nums = msg.split(" ", Qt::SkipEmptyParts);
    vector<ll> numbers;

    if(nums.size()==0||nums.size()%k!=0){
        QMessageBox::warning(this, "Warning", "The length of message should be finite and multiple of k");
        return;
    }
    else{
        foreach(QString num, nums){
            for(QChar c: num){
                if(c>='0' && c<='9'){
                    continue;
                }
                else{
                    QMessageBox::warning(this, "Warning", "The message contains character other than digits");
                    return;
                }
            }
            numbers.push_back(num.toInt());
        }

        for(auto it: numbers){
            if(it<0 || it>=n){
                QString msg = "The numbers in message should be between 0 to ";
                msg += QString::number(n-1);
                QMessageBox::warning(this, "Warning", msg);
                return;
            }
        }
    }


    // Validating evaluation points
    QString evlpts = evalPts->text();
    QStringList nums2 = evlpts.split(" ", Qt::SkipEmptyParts);
    vector<ll> epts;
    if(nums2.size()==0){
        // default case where evaluation points are 0 to k-1
        for(int i=0; i<k; ++i){
            epts.push_back(i);
        }

    }
    else if(nums2.size()!=k){
        QMessageBox::warning(this, "Warning", "The length of evaluations points should be 0(default case) or k");
        return;
    }
    else{
        foreach(QString num, nums2){
            for(QChar c: num){
                if(c>='0' && c<='9'){
                    continue;
                }
                else{
                    QMessageBox::warning(this, "Warning", "The evaluation points contains character other than digits");
                    return;
                }
            }
            epts.push_back(num.toInt());
        }

        for(auto it: numbers){
            if(it<0 || it>=n){
                QString msg = "The numbers in message should be between 0 to ";
                msg += QString::number(n-1);
                QMessageBox::warning(this, "Warning", msg);
                return;
            }
        }
    }

    set<ll>st(epts.begin(), epts.end()); // to check if the evaluation points are unique
    if(st.size()<k){
        QMessageBox::warning(this, "Warning", "Evaluations points should be unique");
        return;
    }

    vector<vector<ll>>chunks;
    for(int i=0; i<numbers.size(); i+=k){
        chunks.push_back(vector<ll>(numbers.begin()+i, numbers.begin()+i+k));
    }

    QString str;
    for(auto vec: chunks){
        vector<ll> temp = systematicEncoder(vec, epts, k, n);
        for(auto num: temp){
            str += QString::number(num);
            str += " ";
        }
    }
    systematicencd->setText(str);
}


// time complexity : O(nchunks * k * n * (log n)^2)
void MainWindow::encode() {
    // Implement Reed-Solomon encoding here based on user input
    int n = nLineEdit->text().toInt();
    int k = kLineEdit->text().toInt();

    int rowcntpgm = table->rowCount();
    int colcntpgm = table->columnCount();

    if(rowcntpgm!=k || colcntpgm != n){
        QMessageBox::warning(this, "Warning", "Please update the Parity Generator Matrix before encoding");
        return;
    }

    QString msg = messageLineEdit->text();
    QStringList nums = msg.split(" ", Qt::SkipEmptyParts);
    vector<ll> numbers;

    if(nums.size()==0||nums.size()%k!=0){
        QMessageBox::warning(this, "Warning", "The length of message should be finite and multiple of k");
        return;
    }
    else{
        foreach(QString num, nums){
            for(QChar c: num){
                if(c>='0' && c<='9'){
                    continue;
                }
                else{
                    QMessageBox::warning(this, "Warning", "The message contains character other than digits");
                    return;
                }
            }
            numbers.push_back(num.toInt());

        }

        for(auto it: numbers){
            if(it<0 || it>=n){
                QString msg = "The numbers in message should be between 0 to ";
                msg += QString::number(n-1);
                QMessageBox::warning(this, "Warning", msg);
                return;
            }
        }
    }


    vector<vector<ll>>chunks;
    for(int i=0; i<numbers.size(); i+=k){
        chunks.push_back(vector<ll>(numbers.begin()+i, numbers.begin()+i+k));
    }
    QString str;
    for(auto vec: chunks){
        vector<ll>temp = classicalEncoder(vec);
        for(auto num: temp){
            str += QString::number(num);
            str += " ";
        }
    }
    classicalencd->setText(str);
}


// Decoder Code and correcting the errors
// We'll be using Berlekamp Welch Algorithm for that purpose


// we need to use gaussian elimination to solve the system of equation to get the coefficients.

void additiveInverse(vector<ll>&ans){
    ll n = ans.size();
    for(ll i=0; i<n; i++){
        ans[i] = modval((7-i),n);
    }
}

void multiplicativeInverse(vector<ll>&ans){
    ll n = ans.size();
    for(ll i=1; i<n; i++){
        ans[i]=inverse(i, n);
    }
}

void partial_pivot(vector<vector<ll>>&A){
    ll n = A.size();

    vector<ll>multpinv(n-1, 0ll);
    multiplicativeInverse(multpinv);

    for(ll i=0; i<n; i++){
        ll pivot_row = i;
        for (ll j = i+1; j < n; j++) {
            if (abs(A[j][i]) > abs(A[pivot_row][i])) {
                pivot_row = j;
            }
        }
        if (pivot_row != i) {
            for (ll j = i; j <= n; j++) {
                swap(A[i][j], A[pivot_row][j]);
            }
        }
        // we should calculate the additive and multiplicative inverses of all the field elements before, so that we can directly
        // use them instead of calculating same inverses again and again
        for (ll j = i+1; j < n; j++) {
            ll factor = modval(A[j][i]*multpinv[A[i][i]], n-1);
            for (int k = i; k <= n; k++) {
                A[j][k] = modval(A[j][k]-factor*A[i][k], n-1);
            }
        }
    }

}


void back_substitute(vector<vector<ll>>&A, vector<ll>&ans) {
    ll n = A.size();
    for(ll i=n-1; i>=0; i--){
        ll sum = 0;
        for(ll j=i+1; j<n; j++){
            sum = modval(sum+A[i][j]*ans[j], n-1);
        }
        ans[i] = modval(modval((A[i][n]-sum),n-1)*inverse(A[i][i], n-1), n-1);
    }

}

void polyDivision(vector<ll>&dividend, vector<ll>&divisor, vector<ll>&quotient, vector<ll>&remainder, ll mod){
    ll n = dividend.size();
    ll m = divisor.size();
    quotient.resize(n - m + 1, 0ll);
    remainder.resize(m - 1, 0ll);

    for(ll i=n-1; i>=m-1; i--){
        ll xtrpow = i-(m-1);
        ll factor = modval(dividend[i] * inverse(divisor[m-1], mod), mod);
        quotient[xtrpow] = factor;
        for(ll j=0; j<m; j++){
            dividend[j+xtrpow] = modval((dividend[j+xtrpow]-factor*divisor[j]), mod);
        }
    }

    for(ll i=0; i<m-1; i++){
        remainder[i] = dividend[i];
    }
    while(!remainder.empty()&&remainder.back()==0){
        remainder.pop_back();
    }
}

void MainWindow::classicalRemoveErr(){
    ll n = nLineEdit->text().toInt();
    ll k = kLineEdit->text().toInt();
    ll d = n-k+1;
    ll maxerrs = (d-1)/2;

    ll nCoeff = 2*(maxerrs+1)+k-1;

    QString temp = intdErrClassical->text();
    QStringList nums = temp.split(" ", Qt::SkipEmptyParts);
    vector<ll>numbers;

    foreach(QString num, nums){
        numbers.push_back(num.toLongLong());
    }

    if(numbers.size()<=0||numbers.size()%n!=0){
        QMessageBox::warning(this, "Warning", "Update the Classical Error Codeword before procceding with error removal");
        return;
    }

    // we need to find the evaluation points order because it might have got changed due to moving columns.
    vector<ll>evalpts(n, 0ll);
    if(k==1){
        for(ll i=0ll; i<n; i++){
            evalpts[i]=i;
        }
    }
    else{
        for(ll i=0ll; i<n; i++){
            evalpts[i] = table->item(1, i)->text().toInt();
        }
    }


    vector<vector<ll>>chunks;
    for(int i=0; i<numbers.size(); i+=n){
        chunks.push_back(vector<ll>(numbers.begin()+i, numbers.begin()+i+n));
    }

    QString res;
    for(ll c = 0; c < chunks.size(); c++){
        vector<vector<ll>>matrix(nCoeff, vector<ll>(nCoeff+1, 0ll));
        for(ll i=0; i<nCoeff-1; i++){
            for(ll j=0; j<=maxerrs; j++){
                matrix[i][j] = modval(chunks[c][i]*power(evalpts[i], j, n), n);
            }
        }
        matrix[nCoeff-1][maxerrs]=1;
        for(ll i=0; i<nCoeff-1; i++){
            for(ll j=maxerrs+1; j<nCoeff; j++){
                matrix[i][j] = modval(-power(evalpts[i], j-maxerrs-1, n), n);
            }
        }
        matrix[nCoeff-1][nCoeff]=1;

        partial_pivot(matrix);
        vector<ll>ans(n+1, 0ll);
        back_substitute(matrix, ans);

        vector<ll>polyE, polyQ;
        for(ll i=0; i<=maxerrs; i++)polyE.push_back(ans[i]);
        for(ll i=maxerrs+1; i<=n; i++)polyQ.push_back(ans[i]);
        vector<ll>quotient;
        vector<ll>remainder;
        polyDivision(polyQ, polyE, quotient, remainder, n);
        if(!remainder.empty()){
            cout<<"Uncorrectable error has detected"<<endl;
            QMessageBox::warning(this, "Warning", "You must have messed up with the steps of using this application!\nKindly fill all the input boxes from top to bottom. Secondly, make sure to click buttons in the same order as well :)");
            return;
        }
        else{
            cout<<"Quotient is:"<<endl;
            for(auto it:quotient)cout<<it<<" ";
            cout<<endl;

            // Using the message Polynomial to get the original codeword.
            for(ll i=0; i<n; i++){
                ll eval = 0;
                for(ll j=0; j<quotient.size(); j++){
                    eval = modval(eval + quotient[j]*power(evalpts[i], j, n), n);
                }
                res += QString::number(eval);
                res += " ";
            }
        }

    }

    removeErrClassical->setText(res);

}


void MainWindow::systematicRemoveErr(){
    ll n = nLineEdit->text().toInt();
    ll k = kLineEdit->text().toInt();
    ll d = n-k+1;
    ll maxerrs = (d-1)/2;

    ll nCoeff = 2*(maxerrs+1)+k-1;

    QString temp = intdErrSystematic->text();
    QStringList nums = temp.split(" ", Qt::SkipEmptyParts);
    vector<ll>numbers;

    foreach(QString num, nums){
        numbers.push_back(num.toLongLong());
    }

    if(numbers.size()<=0||numbers.size()%n!=0){
        QMessageBox::warning(this, "Warning", "Update the Systematic Error Codeword before procceding with error removal");
        return;
    }

    vector<vector<ll>>chunks;
    for(int i=0; i<numbers.size(); i+=n){
        chunks.push_back(vector<ll>(numbers.begin()+i, numbers.begin()+i+n));
    }

    QString res;

    for(ll c = 0; c < chunks.size(); c++){
        vector<vector<ll>>matrix(nCoeff, vector<ll>(nCoeff+1, 0ll));
        for(ll i=0; i<nCoeff-1; i++){
            for(ll j=0; j<=maxerrs; j++){
                matrix[i][j] = modval(chunks[c][i]*power(i, j, n), n);
            }
        }
        matrix[nCoeff-1][maxerrs]=1;
        for(ll i=0; i<nCoeff-1; i++){
            for(ll j=maxerrs+1; j<nCoeff; j++){
                matrix[i][j] = modval(-power(i, j-maxerrs-1, n), n);
            }
        }
        matrix[nCoeff-1][nCoeff]=1;

        partial_pivot(matrix);
        vector<ll>ans(n+1, 0ll);
        back_substitute(matrix, ans);

        vector<ll>polyE, polyQ;
        for(ll i=0; i<=maxerrs; i++)polyE.push_back(ans[i]);
        for(ll i=maxerrs+1; i<=n; i++)polyQ.push_back(ans[i]);
        vector<ll>quotient;
        vector<ll>remainder;
        polyDivision(polyQ, polyE, quotient, remainder, n);
        if(!remainder.empty()){
            cout<<"Uncorrectable error has detected"<<endl;
            QMessageBox::warning(this, "Warning", "You must have messed up with the steps of using this application!\nKindly fill all the input boxes from top to bottom. Secondly, make sure to click buttons in the same order as well :)");
            return;
        }
        else{
            cout<<"Quotient is:"<<endl;
            for(auto it:quotient)cout<<it<<" ";
            cout<<endl;
            // Using the message Polynomial to get the original codeword.
            for(ll i=0; i<n; i++){
                ll eval = 0;
                for(ll j=0; j<quotient.size(); j++){
                    eval = modval(eval + quotient[j]*power(i, j, n), n);
                }
                res += QString::number(eval);
                res += " ";
            }
        }

    }

    removeErrSystematic->setText(res);
}
