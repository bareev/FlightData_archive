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
    void setEdit(WhoEdit e){m_edit = e; emit newState((int) e); return;}
    WhoEdit getEdit(){return m_edit;}

public slots:

private:
    WhoEdit m_edit;

signals:
    void newState(int e);
};

#endif // EDITWINDOW_H
