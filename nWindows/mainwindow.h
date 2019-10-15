#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

//前置声明
class QLineEdit;
class QDialog;


namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();



/*——————————————————————————操作实现——————————————————————————*/
    void newFile();   // 新建操作
    bool maybeSave(); // 判断是否需要保存
    bool save();      // 保存操作
    bool saveAs();    // 另存为操作
    bool saveFile(const QString &fileName); // 保存文件

    void loadFile(QString fileName); //打开
    void closeEvent(QCloseEvent *e); //关闭
/*———————————————————————————————————————————————————————————*/



private:
    Ui::MainWindow *ui;


 /*——————————————————————————操作实现——————————————————————————*/
  bool isUntitled;    // 返回1表示文件没有保存过，返回0表示文件已经被保存过了
  QString curFile;    // 保存当前文件的路径
  QLineEdit *findLineEdit;  //查找
  QDialog *findDlg;         //查找
 /*———————————————————————————————————————————————————————————*/

private slots:
    void showFindText();
    void on_action_N_triggered();//新建
    void on_action_S_triggered();//保存
    void on_action_triggered();//另存为
    void on_action_F_triggered();//查找
    void on_action_O_triggered();//打开
    void on_action_2_triggered();//退出
    void on_action_C_2_triggered();//关闭
    void on_action_C_triggered();//复制
    void on_action_V_triggered();
    void on_action_X_triggered();
    void on_action_U_triggered();
    void on_action_6_triggered();
};

#endif // MAINWINDOW_H
