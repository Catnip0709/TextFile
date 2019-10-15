#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QPushButton>
#include <QFileDialog>
#include <QTextStream>

#include <QLineEdit>
#include <QDialog>
#include <QPushButton>
#include <QCloseEvent>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    /*————初始化记事本————*/
    isUntitled = true;           // 初始化文件为未保存状态
    curFile = tr("未命名.txt");   // 初始化文件名为"未命名.txt"
    setWindowTitle(curFile);     // 初始化窗口标题为文件名

    /*————初始化查找框————*/
    findDlg = new QDialog(this);
    findDlg->setWindowTitle(tr("查找"));
    findLineEdit = new QLineEdit(findDlg);
    QPushButton *btn= new QPushButton(tr("查找下一个"), findDlg);
    QVBoxLayout *layout= new QVBoxLayout(findDlg);
    layout->addWidget(findLineEdit);
    layout->addWidget(btn);
    connect(btn, SIGNAL(clicked()), this, SLOT(showFindText()));

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_action_N_triggered()
{
    newFile();
}

void MainWindow::on_action_S_triggered()
{
     save();
}

void MainWindow::on_action_triggered() //另存为
{
     saveAs();
}

void MainWindow::on_action_F_triggered()  //查找
{
    findDlg->show();
}

void MainWindow::on_action_O_triggered()  //打开
{
    if(maybeSave())
    {
        QString fileName = QFileDialog::getOpenFileName(this);

        if(!fileName.isEmpty())
        {
            loadFile(fileName);
        }
    }
}

void MainWindow::on_action_2_triggered() //退出
{
    if(maybeSave())
    {
        qApp->closeAllWindows();//关闭所有窗口
    }
}

void MainWindow::on_action_C_2_triggered() //关闭
{
   if (maybeSave())
   {
       ui->textEdit->setVisible(false);
   }
}



//新建
void MainWindow::newFile()
{
    //判断文档是否需要保存，如果已经保存完了，则新建文档，并进行初始化。
   if (maybeSave())
   {
       isUntitled = true;
       curFile = tr("未命名.txt");
       setWindowTitle(curFile);

       ui->textEdit->clear();
       ui->textEdit->setVisible(true);
   }
}

//判断文档是否需要保存
bool MainWindow::maybeSave()
{
   // 如果文档被更改了
    if (ui->textEdit->document()->isModified())
    {
    // 自定义一个警告对话框
       QMessageBox box;
       box.setWindowTitle(tr("警告"));
       box.setIcon(QMessageBox::Warning);

       box.setText(curFile + tr(" 尚未保存，是否保存？"));
       QPushButton *yesBtn = box.addButton(tr("是(&Y)"),QMessageBox::YesRole);
        box.addButton(tr("否(&N)"), QMessageBox::NoRole);
       QPushButton *cancelBut = box.addButton(tr("取消"),QMessageBox::RejectRole);
       box.exec();

       if (box.clickedButton() == yesBtn)
            return save();
       else if (box.clickedButton() == cancelBut)
            return false;
   }

   // 如果文档没有被更改，则直接返回true
   return true;
}

//保存
bool MainWindow::save()
{
   if (isUntitled)
   {
       return saveAs();
   }
   else
   {
       return saveFile(curFile);
   }
}

//另存为
bool MainWindow::saveAs()
{
   QString fileName = QFileDialog::getSaveFileName(this,tr("另存为"),curFile);

   if (fileName.isEmpty())
       return false;

   return saveFile(fileName);
}

//存储行为
bool MainWindow::saveFile(const QString &fileName)
{
   QFile file(fileName);

   if (!file.open(QFile::WriteOnly | QFile::Text))
   {

       // %1和%2分别对应后面arg两个参数，/n起换行的作用
       QMessageBox::warning(this, tr("多文档编辑器"),
                   tr("无法写入文件 %1：/n %2")
                  .arg(fileName).arg(file.errorString()));
       return false;
   }
   QTextStream out(&file);
   // 鼠标指针变为等待状态
   QApplication::setOverrideCursor(Qt::WaitCursor);
   out << ui->textEdit->toPlainText();
   // 鼠标指针恢复原来的状态
   QApplication::restoreOverrideCursor();
   isUntitled = false;
   // 获得文件的标准路径
   curFile = QFileInfo(fileName).canonicalFilePath();
   setWindowTitle(fileName);
   return true;
}

//打开
void MainWindow::loadFile(QString fileName)
{
    QFile file(fileName);
    if(!file.open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox::critical(this,
                              "critical",
                              "cannot read file"
                              );
    }
    else
    {
        QTextStream in(&file);
        ui->textEdit->setText(in.readAll());
        setWindowTitle(fileName);
    }
}

//退出
void MainWindow::closeEvent(QCloseEvent *e)
{
    if(maybeSave())
    {
        e->accept();
    }
    else
    {
       e->ignore();//忽略，直接关闭
    }
}

//查找
void MainWindow::showFindText()
{
   QString str = findLineEdit->text();
   if (!ui->textEdit->find(str, QTextDocument::FindBackward))
   {
      QMessageBox::warning(this, tr("查找"),tr("查找结束：%1").arg(str));
   }
}

//复制
void MainWindow::on_action_C_triggered()
{
    ui->textEdit->copy();
}

//粘贴
void MainWindow::on_action_V_triggered()
{
    ui->textEdit->paste();
}

//剪切
void MainWindow::on_action_X_triggered()
{
    ui->textEdit->cut();
}

//撤销
void MainWindow::on_action_U_triggered()
{
    ui->textEdit->undo();
}

//版本说明
void MainWindow::on_action_6_triggered()
{
    QMessageBox message(QMessageBox::NoIcon, "版本说明", "2018年夏季小学期 1613415 潘巧巧");
     message.setIconPixmap(QPixmap("college.png"));
     message.exec();
}
