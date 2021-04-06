#ifndef ENQUETE_H
#define ENQUETE_H


#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>

class enquete
{
public:
    enquete();
    enquete(int,QString,QString);
    int getidm();
    QString getdescription();
    QString gettypem();
    void setidm(int);
    void setdescription(QString);
    void settypem(QString);
    bool ajouter();
        QSqlQueryModel * afficher();
        bool supprimer(int);
        bool modifier(int idm,QString description, QString typem);
        QSqlQueryModel *Trier(QString );
        QSqlQueryModel * rechercher(int idm);



private:
    int idm;
    QString description,typem;
};

#endif // ENQUETE_H

