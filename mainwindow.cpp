#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QPushButton>
#include <QFileDialog>
#include <QTextStream>
#include <QLabel>

//查找功能所需要的类库
#include <QLineEdit>
#include <QDialog>
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //文件状态初始化
    isUntitled=true;
    curFile=tr("NoName.txt");
    setWindowTitle(curFile);

    //查找功能初始化
    findDlg=new QDialog(this);
    findDlg->setWindowTitle("Find");
    findLineEdit=new QLineEdit(findDlg);                    //一个行编辑器
    QPushButton *btn=new QPushButton(tr("Next"),findDlg);   //一个下一个按钮
    QVBoxLayout *layout=new QVBoxLayout(findDlg);           //建立文本槽并放上面
    layout->addWidget(findLineEdit);
    layout->addWidget(btn);
    connect(btn,SIGNAL(clicked()),this,SLOT(showFindText()));    //单击信号关联到自定义的显示查找到的文本槽上

    //状态栏状态变更
    ui->statusBar->showMessage(tr("Welcome."));

    //    基于标签页实现
    //    statusLabel=new QLabel;
    //    statusLabel->setMinimumSize(150,20);
    //    statusLabel->setFrameShape(QFrame::WinPanel);    //设置标签形状
    //    statusLabel->setFrameShadow(QFrame::Sunken);
    //    ui->statusBar->addWidget(statusLabel);
    //    statusLabel->setText(tr("Hello,Welcome."));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::newFile(){
    if(maybeSave()){
        isUntitled=true;
        curFile=tr("NoName.txt");
        setWindowTitle(curFile);
        ui->textEdit->clear();          //清空文本编辑器
        ui->textEdit->setVisible(true);     //设置可见？
    }
}

bool MainWindow::maybeSave(){
    if(ui->textEdit->document()->isModified()){   //判断文本编辑器是否被更改
        QMessageBox box;
        box.setWindowTitle("Warning:");
        box.setIcon(QMessageBox::Warning);
        box.setText(curFile+tr(" not save, do you want to save it?"));
        QPushButton *yesBtn = box.addButton(tr("Yes(&Y)"),QMessageBox::YesRole);
        box.addButton(tr("No(&N)"),QMessageBox::NoRole);
        QPushButton *cancelBtn = box.addButton(tr("Cancel"),QMessageBox::RejectRole);
        box.exec();
        if (box.clickedButton()==yesBtn)
            return save();
        else if(box.clickedButton() == cancelBtn)
        {
            return false;
        }
    }
    return true;
}


bool MainWindow::save(){
    if(isUntitled){
        return saveAs();
    }
    else {
        return saveFile(curFile);
    }
}

bool MainWindow::saveAs(){
    QString fileName=QFileDialog::getSaveFileName(this,tr("Save as."),curFile);
    if (fileName.isEmpty())
        return false;
    return saveFile(fileName);
}

bool MainWindow::saveFile(const QString &fileName){
    QFile file(fileName);
    if(!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this,tr("Editor"),tr("Can't write file %1 :/n %2").arg(fileName).arg(file.errorString()));
        return false;
    }
    QTextStream out(&file);

    //鼠标变为等待状态
    QApplication::setOverrideCursor(Qt::WaitCursor);
    out << ui->textEdit->toPlainText();
    //鼠标恢复原来的状态
    QApplication::restoreOverrideCursor();
    isUntitled=false;

    //获取文件的标准路径
    curFile=QFileInfo(fileName).canonicalFilePath();
    setWindowTitle(curFile);
    return true;
}


bool MainWindow::loadFile(const QString &fileName){
    QFile file (fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this,tr("Editor"),tr("Can not read the file %1:\n%2.").arg(fileName).arg(file.errorString()));
        return false;
    }
    QTextStream in(&file);   //新建文本流对象
    QApplication::setOverrideCursor(Qt::WaitCursor);
    ui->textEdit->setPlainText(in.readAll());
    QApplication::restoreOverrideCursor();
    curFile=QFileInfo(fileName).canonicalFilePath();
    setWindowTitle(curFile);
    return true;
}


void MainWindow::on_actionNew_N_triggered()
{
    newFile();
}

void MainWindow::on_actionSave_S_triggered()
{
    save();
}

void MainWindow::on_actionSave_AS_A_triggered()
{
    saveAs();
}

void MainWindow::on_actionOpen_O_triggered()
{
    if(maybeSave()){
        QString fileName=QFileDialog::getOpenFileName(this);
        //文件名非空则加载文件
        if(!fileName.isEmpty()){
            loadFile(fileName);
            ui->textEdit->setVisible(true);
        }
    }
}

void MainWindow::on_actionQuit_Q_triggered()
{
    if(maybeSave()){
        ui->textEdit->setVisible(false);
    }
    qApp->quit();
}

void MainWindow::on_actionUndo_Z_triggered()
{
    ui->textEdit->undo();
}

void MainWindow::on_actionCut_C_triggered()
{
    ui->textEdit->cut();
}

void MainWindow::on_actionCopy_C_triggered()
{
    ui->textEdit->copy();
}

void MainWindow::on_actionPaste_P_triggered()
{
    ui->textEdit->paste();
}

void MainWindow::showFindText()
{
    QString str=findLineEdit->text();
    bool status;
    status=ui->textEdit->find(str);
    if(!status){
        QMessageBox::warning(this,tr("Find"),tr("Can not find %1").arg(str));
    }
}

void MainWindow::closeEvent(QCloseEvent *event){
    if(maybeSave()){
        event->accept();
    }
    else {
        event->ignore();
    }
}

void MainWindow::on_actionFind_F_triggered()
{
    findDlg->show();
}
