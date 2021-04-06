#ifndef MAINWINDOW_H
#define MAINWINDOW_H
//tt
#include <QMainWindow>
#include <QWidget>
#include <accuse.h>
#include <enquete.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pb_ajouter_clicked();

    void on_pb_supprimer_clicked();

    void on_pb_ajouter2_clicked();

    void on_pb_supprimer_1_clicked();

    void on_pb_modifier_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();


    void on_recherche_clicked();




    void on_trie_activated();

    void on_trie_2_activated();

    void on_recherche1_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

private:
    Ui::MainWindow *ui;
    accuse F;
    enquete M;
};

#endif // MAINWINDOW_H

