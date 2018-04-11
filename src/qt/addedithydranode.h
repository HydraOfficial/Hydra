#ifndef ADDEDITHYDRANODE_H
#define ADDEDITHYDRANODE_H

#include <QDialog>
#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>

namespace Ui {
class AddEditHydraNode;
}


class AddEditHydraNode : public QDialog
{
    Q_OBJECT

public:
    explicit AddEditHydraNode(QWidget *parent = 0);
    ~AddEditHydraNode();

protected:

private slots:
    void on_okButton_clicked();
    void on_cancelButton_clicked();
    void on_AddEditAddressPasteButton_clicked();
    void on_AddEditPrivkeyPasteButton_clicked();
    void on_AddEditTxhashPasteButton_clicked();

signals:

private:
    Ui::AddEditHydraNode *ui;
};

#endif // ADDEDITHYDRANODE_H
