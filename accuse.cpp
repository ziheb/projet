#include "accuse.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QObject>
#include <QDateEdit>


accuse::accuse()
{
id=0;
nom="";
prenom="";
type="";

}

accuse::accuse(int id ,QString nom ,QString prenom, QString type){
    this->id=id;
    this->nom=nom;
    this->prenom=prenom;
    this->type=type;
}

int accuse::getid(){
return id;
}
QString accuse::getnom(){
return nom;
}
QString accuse::getprenom(){
return prenom;
}
QString accuse::gettype(){
return type;
}
void accuse::setid(int id ){
this->id=id;
}
void accuse::setnom(QString nom ){
this->nom=nom;
}
void accuse::setprenom(QString prenom){
this->prenom=prenom;
}
void accuse::settype(QString type){
this->type=type;
}
bool accuse::ajouter(){
    QSqlQuery query;
    QString id_string= QString::number(id);
          query.prepare("INSERT INTO accuse (id, nom, prenom, type) "
                        "VALUES (:id, :nom, :prenom, :type)");
          query.bindValue(":id", id_string);
          query.bindValue(":nom", nom);
          query.bindValue(":prenom", prenom);
          query.bindValue(":type", type);
         return query.exec();

                        }

QSqlQueryModel * accuse::afficher(){
    QSqlQueryModel * model=new QSqlQueryModel();
         model->setQuery("select * from accuse");
         model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
         model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
         model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));
         model->setHeaderData(3, Qt::Horizontal, QObject::tr("type"));

    return model;

}
bool accuse::supprimer(int id){
    QSqlQuery query;
          query.prepare("Delete from accuse where id=:id ");
          query.bindValue(0, id);

         return query.exec();
}


bool accuse::modifier(int id,QString nom, QString prenom,QString type )
{
    QSqlQuery query;
    //QString id= QString::number(id);

    query.prepare("update accuse set id=:id, nom=:nom,prenom=:prenom,type=:type where id=:id");
    query.bindValue(":id", id);
    query.bindValue(":nom",nom);
    query.bindValue(":prenom",prenom);
    query.bindValue(":type",type);



    return query.exec();
}
QSqlQueryModel * accuse::rechercher(int id)
{
    QSqlQueryModel* model = new QSqlQueryModel();
     model->setQuery("select * from accuse where (id LIKE id='"+QString::number(id)+"'");
     model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
     model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom "));
     model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenomi"));
     model->setHeaderData(3, Qt::Horizontal, QObject::tr("type"));
         return model;
}



QSqlQueryModel * accuse::Trier(QString choix1){
    QSqlQueryModel *model=new QSqlQueryModel();


    if (choix1=="id"){
         model->setQuery("SELECT * FROM accuse ORDER BY id ASC ");
    }
    else if(choix1=="nom"){
         model->setQuery("SELECT * FROM accuse ORDER BY nom ");
    }
    else if(choix1=="prenom"){
        model->setQuery("SELECT * FROM accuse ORDER BY prenom  ");
    }
    else if(choix1=="type"){
        model->setQuery("SELECT * FROM accuse ORDER BY type DESC ");
    }


    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom "));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("type"));

return model;
}
