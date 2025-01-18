#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "head/materiel.h"


#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void create_linear(materiel, float, float);
    void create_degressif(materiel, float);
    void download_csv();
    void change_title(QString, QString,QString);
    void set_invisible_inputs(bool);
    void set_invisible_inputs_amort(bool);
    void set_materiel_table();
    bool msg_choix(QString);
    void update_action(QString, int);
    void insert_action(QString, int);
    void set_materiel_items();
    void update_row_materiel(QString, int);
private slots:
    void on_calculer_clicked();
    void on_download_clicked();
    void on_navigation_clicked();
    void on_ajout_clicked();
    void on_back_clicked();
private:
    Ui::MainWindow *ui;

};
#endif
