#ifndef EDITWINDOW_H
#define EDITWINDOW_H
#include <wcore.h>

namespace Ui {
class EditWindow;
}

class EditWindow : public Wcore
{
    Q_OBJECT

public:
    EditWindow();
    void setEdit(WhoEdit e){m_edit = e; return;}
    WhoEdit getEdit(){return m_edit;}

public slots:

private:
    WhoEdit m_edit;

signals:

};

#endif // EDITWINDOW_H
