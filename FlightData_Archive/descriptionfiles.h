#ifndef DESCRIPTIONFILES_H
#define DESCRIPTIONFILES_H

#include <wcore.h>

namespace Ui {
class descriptionFiles;
}

class descriptionFiles : public Wcore
{
    Q_OBJECT

public:
    descriptionFiles();
    void showResize(QStringList s, formType f);
    formType getftype(){return f_type;}
    void setftype(formType ft){f_type = ft; return;}
    void setInputOutput(int p){input_output = p; emit iochange(p); return;}
    int getInputOutput(){return input_output;}
    Q_INVOKABLE void writeNewDB(QString filesAndMessage);

public slots:
    void onNewDBName(QString name);

private:
    formType f_type;
    int input_output;
    bool readyWrite;
    QString basename;

signals:
    void addNewRow(QStringList s);
    void iochange(int p);
    void paramTextChanged(int ft);
    void recOrUp(int type, QString basename, QStringList param);
};

#endif // DESCRIPTIONFILES_H
