#include "logindlg.h"
#include "ui_logindlg.h"
#include <QMessageBox>
#include <QMouseEvent>
#include <QWheelEvent>

LoginDlg::LoginDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDlg)
{
    ui->setupUi(this);

    //将密码设置为输入时不可见
    ui->pwdlineEdit->setEchoMode(QLineEdit::Password);
}

LoginDlg::~LoginDlg()
{
    delete ui;
}

void LoginDlg::on_loginbtn_clicked()
{
    // 判断用户名和密码是否正确，
    // 如果错误则弹出警告对话框
        if(ui->userlineEdit->text() == tr("1") &&
               ui->pwdlineEdit->text() == tr("123"))
        {
           accept();
        }

        else
        {
           QMessageBox::warning(this, tr("Waring"),
                                 tr("user name or password error!"),
                                 QMessageBox::Yes);
           // 清空内容并定位光标
           ui->userlineEdit->clear();
           ui->pwdlineEdit->clear();
           ui->userlineEdit->setFocus();
        }
}


// 鼠标双击事件，双击全屏与恢复
void LoginDlg::mouseDoubleClickEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton) // 如果是鼠标左键按下
    {
        if(windowState() != Qt::WindowFullScreen)      // 如果现在不是全屏
            setWindowState(Qt::WindowFullScreen);      // 将窗口设置为全屏

        else setWindowState(Qt::WindowNoState);        // 否则恢复以前的大小
    }
}

// 滚轮事件，通过滚轮放大与缩小
void LoginDlg::wheelEvent(QWheelEvent *event)
{
    if(event->delta() > 0)
    {                              // 当滚轮远离使用者时
        ui->textEdit->zoomIn();
    }
    else
    {
        ui->textEdit->zoomOut();   // 当滚轮向使用者方向旋转时
    }
}

// 鼠标按下事件
void LoginDlg::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {       // 如果是鼠标左键按下
        QCursor cursor;
        cursor.setShape(Qt::ClosedHandCursor);
        QApplication::setOverrideCursor(cursor); // 使鼠标指针暂时改变形状
        offset = event->globalPos() - pos();    // 获取指针位置和窗口位置的差值
    }
    else if(event->button() == Qt::RightButton){ // 如果是鼠标右键按下
        QCursor cursor(QPixmap("college.png"));
        QApplication::setOverrideCursor(cursor);// 使用自定义的图片作为鼠标指针
   }
}

// 鼠标移动事件
void LoginDlg::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons() & Qt::LeftButton){      // 这里必须使用buttons()
    QPoint temp;
    temp = event->globalPos() - offset;
    move(temp);// 使用鼠标指针当前的位置减去差值，就得到了窗口应该移动的位置
    }
}

// 鼠标释放事件
void LoginDlg::mouseReleaseEvent(QMouseEvent *event)
{
    QApplication::restoreOverrideCursor();         // 恢复鼠标指针形状
}


