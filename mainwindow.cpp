#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "accuse.h"
#include "enquete.h"
#include <QApplication>
#include <QMessageBox>
#include <QIntValidator>
#include "smtp.h"
#include <QTabWidget>
#include <QString>
#include <QFile>
#include <QSqlQuery>
#include <QPixmap>
#include <QDebug>
#include <QInputDialog>
#include "QSqlRecord"
#include "QSqlQuery"
#include <QSqlDatabase>
#include <QSqlError>
#include<QtPrintSupport/QPrinter>
#include<QPdfWriter>
#include <QFileDialog>
#include<QTextDocument>
#include<QFile>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
     ui->le_id->setValidator(new QIntValidator(0, 99999, this));
     ui->tab_accuse->setModel(F.afficher());
     ui->le_idm->setValidator(new QIntValidator(0, 99999, this));
     ui->tab_enquete->setModel(M.afficher());

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pb_ajouter_clicked()
{
    int  id=ui->le_id->text().toInt();
    QString nom=ui->le_nom->text();
    QString prenom=ui->le_prenom->text();
    QString  type=ui->le_type->text();

    accuse E(id,nom,prenom,type);

    bool test=E.ajouter();
    if(test){
        QMessageBox::information(nullptr, QObject::tr("OK"),
                    QObject::tr("ajout succesful.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
          ui->tab_accuse->setModel(F.afficher());
    }
    else{

        QMessageBox::critical(nullptr, QObject::tr("NOT OK"),
                    QObject::tr("ajout failed.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    }
}

void MainWindow::on_pb_supprimer_clicked()
{
accuse F1;
F1.setid(ui->le_id_supp->text().toInt());
bool test=F1.supprimer(F1.getid());
if(test){
    QMessageBox::information(nullptr, QObject::tr("OK"),
                QObject::tr("supprimer succesful.\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);
    ui->tab_accuse->setModel(F.afficher());
}
else{

    QMessageBox::critical(nullptr, QObject::tr("NOT OK"),
                QObject::tr("supprimer failed.\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);
}
}

void MainWindow::on_pb_ajouter2_clicked()
{
    int  idm=ui->le_idm->text().toInt();
    QString description=ui->le_description->text();
    QString typem=ui->le_typem->text();

    enquete M(idm,description,typem);

    bool test=M.ajouter();
    if(test){
        QMessageBox::information(nullptr, QObject::tr("OK"),
                    QObject::tr("ajout succesful.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
          ui->tab_enquete->setModel(M.afficher());
    }
    else{

        QMessageBox::critical(nullptr, QObject::tr("NOT OK"),
                    QObject::tr("ajout failed.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    }
}

void MainWindow::on_pb_supprimer_1_clicked()
{
    enquete M1;
    M1.setidm(ui->le_idm_supp->text().toInt());
    bool test=M1.supprimer(M1.getidm());
    if(test){
        QMessageBox::information(nullptr, QObject::tr("OK"),
                    QObject::tr("supprimer succesful.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
        ui->tab_enquete->setModel(M.afficher());
    }
    else{

        QMessageBox::critical(nullptr, QObject::tr("NOT OK"),
                    QObject::tr("supprimer failed.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    }
}

void MainWindow::on_pb_modifier_clicked()
{
    int row=ui->tab_accuse->selectionModel()->currentIndex().row();
    QString id=ui->tab_accuse->model()->index(row,0).data().toString(); //row = ligne / 0 : colonne
    QString nom=ui->tab_accuse->model()->index(row,1).data().toString();
    QString prenom=ui->tab_accuse->model()->index(row,2).data().toString();

    QString type=ui->tab_accuse->model()->index(row,3).data().toString();

    if(row==-1)
    {
        QMessageBox ::information(nullptr,QObject::tr("modifier un accuse"),
                                          QObject::tr("aucune selection.\n"
                                              "click ok to exit"),QMessageBox::Ok);
    }
    else
    {
        ui->le_id->setText(id);
        ui->le_nom->setText(nom);
        ui->le_prenom->setText(prenom);
      ui->le_type->setText(type);
    }
}

void MainWindow::on_pushButton_clicked()
{
    int id = ui->le_id->text().toInt();
    QString nom = ui->le_nom->text();
    QString prenom= ui->le_prenom->text();
    QString type= ui->le_type->text();

    accuse F(id,nom,prenom,type);
    bool test =F.modifier(id,nom,prenom,type);

    if(test)
    {ui->tab_accuse->setModel(F.afficher());
        QMessageBox::information(nullptr, QObject::tr("modifier un accuse"),
                                 QObject::tr("accuse  modifié.\n"
                                             "Click Cancel to exit."), QMessageBox::Cancel);

    }
    else
        QMessageBox::critical(nullptr, QObject::tr("Modifier un accuse"),
                              QObject::tr("Erreur !.\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);
}

void MainWindow::on_pushButton_2_clicked()
{
    int row=ui->tab_enquete->selectionModel()->currentIndex().row();
    QString idm=ui->tab_enquete->model()->index(row,0).data().toString(); //row = ligne / 0 : colonne
    QString description=ui->tab_enquete->model()->index(row,1).data().toString();
    QString typem=ui->tab_enquete->model()->index(row,2).data().toString();

    QString prix=ui->tab_enquete->model()->index(row,3).data().toString();

    if(row==-1)
    {
        QMessageBox ::information(nullptr,QObject::tr("modifier enquete"),
                                          QObject::tr("aucune selection.\n"
                                              "click ok to exit"),QMessageBox::Ok);
    }
    else
    {
        ui->le_idm->setText(idm);
        ui->le_description->setText(description);
        ui->le_typem->setText(typem);
    }
}

void MainWindow::on_pushButton_3_clicked()
{
    int idm = ui->le_idm->text().toInt();
    QString description = ui->le_description->text();
    QString typem= ui->le_typem->text();

    enquete M(idm,description,typem);
    bool test =M.modifier(idm,description,typem);

    if(test)
    {ui->tab_enquete->setModel(M.afficher());
        QMessageBox::information(nullptr, QObject::tr("modifier enquete"),
                                 QObject::tr("enquete  modifié.\n"
                                             "Click Cancel to exit."), QMessageBox::Cancel);

    }
    else
        QMessageBox::critical(nullptr, QObject::tr("Modifier enquete"),
                              QObject::tr("Erreur !.\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);

}



void MainWindow::on_recherche_clicked()
{
    QSqlQueryModel *modal=new QSqlQueryModel();
                    QSqlQuery request;
                   QString type=ui->rechercher->currentText();
                   QString val=ui->le_recherche->text();
                   val="%"+val+"%";
                   if (type=="id"){
                       request.prepare("SELECT * FROM accuse WHERE id LIKE:val ");
                   }else if (type=="nom"){
                       request.prepare("SELECT * FROM accuse WHERE nom LIKE:val");
                   }else if (type=="prenom"){
                       request.prepare("SELECT * FROM accuse WHERE prenom LIKE:val");
                   }else if (type=="type"){
                       request.prepare("SELECT * FROM accuse WHERE type LIKE:val");
                   }
                   request.bindValue(":val",val);
                   request.exec();
                   modal->setQuery(request);
                   ui->tab_accuse->setModel(modal);

}




void MainWindow::on_trie_activated()
{
    accuse F;
    QString choix= ui->trie->currentText();
    ui->tab_accuse->setModel(F.Trier(choix));
}

void MainWindow::on_trie_2_activated()
{
    enquete M;
    QString choix= ui->trie_2->currentText();
    ui->tab_enquete->setModel(M.Trier(choix));
}

void MainWindow::on_recherche1_clicked()
{
    QSqlQueryModel *modal=new QSqlQueryModel();
                    QSqlQuery request;
                   QString type=ui->rechercher_2->currentText();
                   QString val=ui->le_recherche1->text();
                   val="%"+val+"%";
                   if (type=="idm"){
                       request.prepare("SELECT * FROM enquete WHERE idm LIKE:val ");
                   }else if (type=="description"){
                       request.prepare("SELECT * FROM enquete WHERE description LIKE:val");
                   }else if (type=="typem"){
                       request.prepare("SELECT * FROM enquete WHERE typem LIKE:val");
                   }

                   request.bindValue(":val",val);
                   request.exec();
                   modal->setQuery(request);
                   ui->tab_enquete->setModel(modal);

}

void MainWindow::on_pushButton_4_clicked()
{
    QTableView *table;
            table = ui->tab_enquete;
            QString filters("mdb files (.csv);;All files (.*)");
            QString defaultFilter("mdb files (*.csv)");
            QString fileName = QFileDialog::getSaveFileName(0, "Save file", QCoreApplication::applicationDirPath(),
                               filters, &defaultFilter);
            QFile file(fileName);
            QAbstractItemModel *model =  table->model();
            if (file.open(QFile::WriteOnly | QFile::Truncate)) {
                QTextStream data(&file);
                QStringList strList;
                for (int i = 0; i < model->columnCount(); i++) {
                    if (model->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString().length() > 0)
                        strList.append("\"" + model->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString() + "\"");
                    else
                        strList.append("");
                }
                data << strList.join(";") << "\n";
                for (int i = 0; i < model->rowCount(); i++) {
                    strList.clear();
                    for (int j = 0; j < model->columnCount(); j++) {
                        if (model->data(model->index(i, j)).toString().length() > 0)
                            strList.append("\"" + model->data(model->index(i, j)).toString() + "\"");
                        else
                            strList.append("");
                    }
                    data << strList.join(";") + "\n";
                }
                file.close();
                QMessageBox::information(this,"Exporter To  export","Exporter En  export Avec Succées ");
            }
}

void MainWindow::on_pushButton_5_clicked()
{
    QTableView *table;
            table = ui->tab_accuse;
            QString filters("mdb files (.csv);;All files (.*)");
            QString defaultFilter("mdb files (*.csv)");
            QString fileName = QFileDialog::getSaveFileName(0, "Save file", QCoreApplication::applicationDirPath(),
                               filters, &defaultFilter);
            QFile file(fileName);
            QAbstractItemModel *model =  table->model();
            if (file.open(QFile::WriteOnly | QFile::Truncate)) {
                QTextStream data(&file);
                QStringList strList;
                for (int i = 0; i < model->columnCount(); i++) {
                    if (model->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString().length() > 0)
                        strList.append("\"" + model->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString() + "\"");
                    else
                        strList.append("");
                }
                data << strList.join(";") << "\n";
                for (int i = 0; i < model->rowCount(); i++) {
                    strList.clear();
                    for (int j = 0; j < model->columnCount(); j++) {
                        if (model->data(model->index(i, j)).toString().length() > 0)
                            strList.append("\"" + model->data(model->index(i, j)).toString() + "\"");
                        else
                            strList.append("");
                    }
                    data << strList.join(";") + "\n";
                }
                file.close();
                QMessageBox::information(this,"Exporter To  export","Exporter En  export Avec Succées ");
            }
}
