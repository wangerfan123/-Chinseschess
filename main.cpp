#include <QApplication>
#include "ChooseDlg.h"
#include "MainWnd.h"
#include <QTime>
int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    QTime t = QTime::currentTime();
    qsrand(t.msec()+t.second()*1000);

    ChooseDlg dlg;//选择对话框
    if(dlg.exec() != QDialog::Accepted)
        return 0;

    MainWnd wnd(dlg._selected);//选择结果保存到_selected中，影响wnd对象的创建
    wnd.show();




    return app.exec();
}
