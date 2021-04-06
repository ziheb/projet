#include "enquete.h"

#include <QSqlQuery>
#include <QtDebug>
#include <QObject>
enquete::enquete()
{
idm=0;
description=" ";
typem=" ";
}

enquete::enquete(int idm ,QString description ,QString typem){
    this->idm=idm;
    this->description=description;
    this->typem=typem;
}

int enquete::getidm(){
return idm;
}
QString enquete::getdescription(){
return description;
}
QString enquete::gettypem(){
return typem;
}
void enquete::setidm(int idm ){
this->idm=idm;
}
void enquete::setdescription(QString description ){
this->description=description;
}

void enquete::settypem(QString typem){
this->typem=typem;
}
bool enquete::ajouter(){
    QSqlQuery query;
    QString idm_string= QString::number(idm);
          query.prepare("INSERT INTO enquete (idm, description, typem) "
                        "VALUES (:idm, :description, :typem)");
          query.bindValue(":idm", idm_string);
          query.bindValue(":description", description);
          query.bindValue(":typem", typem);
         return query.exec();

                        }

QSqlQueryModel * enquete::afficher(){
    QSqlQueryModel * model=new QSqlQueryModel();
         model->setQuery("select * from enquete");
         model->setHeaderData(0, Qt::Horizontal, QObject::tr("idm"));
         model->setHeaderData(1, Qt::Horizontal, QObject::tr("description"));
         model->setHeaderData(2, Qt::Horizontal, QObject::tr("typem"));

    return model;

}
bool enquete::supprimer(int idm){
    QSqlQuery query;
          query.prepare("Delete from enquete where idm=:idm ");
          query.bindValue(0, idm);

         return query.exec();
}

bool enquete::modifier(int idm,QString description, QString typem)
{
    QSqlQuery query;
    //QString id= QString::number(idm);

    query.prepare("update enquete set idm=:idm, description=:description,typem=:typem where idm=:idm");
    query.bindValue(":idm", idm);
    query.bindValue(":description",description);
    query.bindValue(":typem",typem);


    return query.exec();
}
QSqlQueryModel * enquete::Trier(QString choix1){
    QSqlQueryModel *model=new QSqlQueryModel();


    if (choix1=="idm"){
         model->setQuery("SELECT * FROM enquete ORDER BY idm ASC ");
    }
    else if(choix1=="description"){
         model->setQuery("SELECT * FROM enquete ORDER BY description ");
    }
    else if(choix1=="typem"){
        model->setQuery("SELECT * FROM enquete ORDER BY typem  ");
    }


    model->setHeaderData(0, Qt::Horizontal, QObject::tr("idm"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("description"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("typem"));

return model;
}


QSqlQueryModel * enquete::rechercher(int idm)
{
    QSqlQueryModel* model = new QSqlQueryModel();
     model->setQuery("select * from enquete where (id LIKE id='"+QString::number(idm)+"'");
     model->setHeaderData(0, Qt::Horizontal, QObject::tr("idm"));
     model->setHeaderData(1, Qt::Horizontal, QObject::tr("description "));
     model->setHeaderData(2, Qt::Horizontal, QObject::tr("typem"));
         return model;
}
