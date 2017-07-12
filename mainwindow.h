#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCloseEvent>

class QLineEdit;
class QDialog;
class QLabel;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    //基本功能的实现
    void newFile();         //新建文件
    bool maybeSave();       //判断是否需要保存
    bool save();            //保存
    bool saveAs();          //另存为
    bool saveFile(const QString &fileName);     //保存文件（新）
    //打开、关闭、退出、撤销、复制、粘贴
    bool loadFile(const QString &fileName);

protected:
    void closeEvent(QCloseEvent *event);

private slots:
    void on_actionNew_N_triggered();

    void on_actionSave_S_triggered();

    void on_actionSave_AS_A_triggered();

    void on_actionOpen_O_triggered();

    void on_actionQuit_Q_triggered();

    void on_actionUndo_Z_triggered();

    void on_actionCut_C_triggered();

    void on_actionCopy_C_triggered();

    void on_actionPaste_P_triggered();

    void showFindText();

    void on_actionFind_F_triggered();

private:
    Ui::MainWindow *ui;
    bool isUntitled;
    QString curFile;
    QLineEdit *findLineEdit;
    QDialog *findDlg;
    QLabel *statusLabel;

};


#endif // MAINWINDOW_H
