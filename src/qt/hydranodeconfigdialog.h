#ifndef HYDRANODECONFIGDIALOG_H
#define HYDRANODECONFIGDIALOG_H

#include <QDialog>

namespace Ui {
    class HydraNodeConfigDialog;
}

QT_BEGIN_NAMESPACE
class QModelIndex;
QT_END_NAMESPACE

/** Dialog showing transaction details. */
class HydraNodeConfigDialog : public QDialog
{
    Q_OBJECT

public:
    explicit HydraNodeConfigDialog(QWidget *parent = 0, QString nodeAddress = "123.456.789.123:19700", QString privkey="MASTERNODEPRIVKEY");
    ~HydraNodeConfigDialog();

private:
    Ui::HydraNodeConfigDialog *ui;
};

#endif // HYDRANODECONFIGDIALOG_H
