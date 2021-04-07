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
//tt
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
     makePolt();
     makePolt_2();


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


void MainWindow::makePolt()
{

       QLinearGradient gradient(0, 0, 0, 400);
       gradient.setColorAt(0, QColor(90, 90, 90));
       gradient.setColorAt(0.38, QColor(105, 105, 105));
       gradient.setColorAt(1, QColor(70, 70, 70));
       ui->customPlot->setBackground(QBrush(gradient));


       QCPBars *regen = new QCPBars(ui->customPlot->xAxis,ui-> customPlot->yAxis);

       regen->setAntialiased(false);

       regen->setStackingGap(1);




       regen->setName("Nombre de accuse par rapport a la type");
       regen->setPen(QPen(QColor(0, 168, 140).lighter(130)));
       regen->setBrush(QColor(0, 168, 140));

       QVector<double> ticks;
       QVector<QString> labels;






       ticks << 1<<2<<3<<4;

      labels <<"drogue"<<"cambriolage"<<"querelle";
       QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);
       textTicker->addTicks(ticks, labels);
       ui->customPlot->xAxis->setTicker(textTicker);
       ui->customPlot->xAxis->setTickLabelRotation(60);
       ui->customPlot->xAxis->setSubTicks(false);
       ui->customPlot->xAxis->setTickLength(0, 3);
       ui->customPlot->xAxis->setRange(0, 8);
       ui->customPlot->xAxis->setBasePen(QPen(Qt::white));
       ui->customPlot->xAxis->setTickPen(QPen(Qt::white));
       ui->customPlot->xAxis->grid()->setVisible(true);
       ui->customPlot->xAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
       ui->customPlot->xAxis->setTickLabelColor(Qt::white);
       ui->customPlot->xAxis->setLabelColor(Qt::white);


       ui->customPlot->yAxis->setRange(0,10);
       ui->customPlot->yAxis->setPadding(10); // a bit more space to the left border
       ui->customPlot->yAxis->setLabel("Nombre de accuse");
       ui->customPlot->yAxis->setBasePen(QPen(Qt::white));
       ui->customPlot->yAxis->setTickPen(QPen(Qt::white));
       ui->customPlot->yAxis->setSubTickPen(QPen(Qt::white));
       ui->customPlot->yAxis->grid()->setSubGridVisible(true);
       ui->customPlot->yAxis->setTickLabelColor(Qt::white);
       ui->customPlot->yAxis->setLabelColor(Qt::white);
       ui->customPlot->yAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::SolidLine));
       ui->customPlot->yAxis->grid()->setSubGridPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));


       QVector<double> regenData;
       int n1=0;
       int n2=0;
       int n3=0;

           QSqlQuery q1("select count(*) from accuse where type='drogue'");
           while (q1.next())
           {
               n1 = q1.value(0).toInt();
               qDebug()<<"Nombre accuse : "<<n1<<endl;
           }

           QSqlQuery q2("select count(*) from accuse where type='cambriolage'");
           while (q2.next())
           {
                n2 = q2.value(0).toInt();
                qDebug()<<"Nombre accuse : "<<n2<<endl;
           }

           QSqlQuery q3("select count(*) from accuse where type='querelle'");
           while (q3.next())
           {
                n3 = q3.value(0).toInt();
                qDebug()<<"Nombre accuse : "<<n3<<endl;
           }




       regenData << n1<<n2<<n3;
       regen->setData(ticks, regenData);


       ui->customPlot->legend->setVisible(true);
       ui->customPlot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignTop|Qt::AlignHCenter);
       ui->customPlot->legend->setBrush(QColor(255, 255, 255, 100));
       ui->customPlot->legend->setBorderPen(Qt::NoPen);
       QFont legendFont = font();
       legendFont.setPointSize(10);
       ui->customPlot->legend->setFont(legendFont);
       ui->customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);


}





void MainWindow::makePolt_2()
{

       QLinearGradient gradient(0, 0, 0, 400);
       gradient.setColorAt(0, QColor(90, 90, 90));
       gradient.setColorAt(0.38, QColor(105, 105, 105));
       gradient.setColorAt(1, QColor(70, 70, 70));
       ui->customPlot_2->setBackground(QBrush(gradient));


       QCPBars *regen = new QCPBars(ui->customPlot_2->xAxis,ui-> customPlot_2->yAxis);

       regen->setAntialiased(false);

       regen->setStackingGap(1);




       regen->setName("Nombre de enquete par rapport a la typem");
       regen->setPen(QPen(QColor(0, 168, 140).lighter(130)));
       regen->setBrush(QColor(0, 168, 140));

       QVector<double> ticks;
       QVector<QString> labels;






       ticks << 1<<2<<3;

      labels <<"drogue"<<"querelle"<<"cambriolage";
       QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);
       textTicker->addTicks(ticks, labels);
       ui->customPlot_2->xAxis->setTicker(textTicker);
       ui->customPlot_2->xAxis->setTickLabelRotation(60);
       ui->customPlot_2->xAxis->setSubTicks(false);
       ui->customPlot_2->xAxis->setTickLength(0, 3);
       ui->customPlot_2->xAxis->setRange(0, 8);
       ui->customPlot_2->xAxis->setBasePen(QPen(Qt::white));
       ui->customPlot_2->xAxis->setTickPen(QPen(Qt::white));
       ui->customPlot_2->xAxis->grid()->setVisible(true);
       ui->customPlot_2->xAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
       ui->customPlot_2->xAxis->setTickLabelColor(Qt::white);
       ui->customPlot_2->xAxis->setLabelColor(Qt::white);


       ui->customPlot_2->yAxis->setRange(0,10);
       ui->customPlot_2->yAxis->setPadding(10); // a bit more space to the left border
       ui->customPlot_2->yAxis->setLabel("Nombre de accuse");
       ui->customPlot_2->yAxis->setBasePen(QPen(Qt::white));
       ui->customPlot_2->yAxis->setTickPen(QPen(Qt::white));
       ui->customPlot_2->yAxis->setSubTickPen(QPen(Qt::white));
       ui->customPlot_2->yAxis->grid()->setSubGridVisible(true);
       ui->customPlot_2->yAxis->setTickLabelColor(Qt::white);
       ui->customPlot_2->yAxis->setLabelColor(Qt::white);
       ui->customPlot_2->yAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::SolidLine));
       ui->customPlot_2->yAxis->grid()->setSubGridPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));


       QVector<double> regenData;
       int n1=0;
       int n2=0;
       int n3=0;

           QSqlQuery q1("select count(*) from enquete where typem='drogue'");
           while (q1.next())
           {
               n1 = q1.value(0).toInt();
               qDebug()<<"Nombre enquete : "<<n1<<endl;
           }

           QSqlQuery q2("select count(*) from enquete where typem='querelle'");
           while (q2.next())
           {
               n2 = q2.value(0).toInt();
               qDebug()<<"Nombre enquete : "<<n2<<endl;
           }

           QSqlQuery q3("select count(*) from enquete where typem='cambriolage'");
           while (q3.next())
           {
                n3 = q3.value(0).toInt();
                qDebug()<<"Nombre enquete : "<<n3<<endl;
           }






       regenData << n1<<n2<<n3;
       regen->setData(ticks, regenData);


       ui->customPlot_2->legend->setVisible(true);
       ui->customPlot_2->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignTop|Qt::AlignHCenter);
       ui->customPlot_2->legend->setBrush(QColor(255, 255, 255, 100));
       ui->customPlot_2->legend->setBorderPen(Qt::NoPen);
       QFont legendFont = font();
       legendFont.setPointSize(10);
       ui->customPlot_2->legend->setFont(legendFont);
       ui->customPlot_2->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);


}
